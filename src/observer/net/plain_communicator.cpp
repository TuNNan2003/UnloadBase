/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/06/25.
//

#include "net/plain_communicator.h"
#include "net/buffered_writer.h"
#include "sql/expr/tuple.h"
#include "event/session_event.h"
#include "session/session.h"
#include "common/io/io.h"
#include "common/log/log.h"

PlainCommunicator::PlainCommunicator()
{
  send_message_delimiter_.assign(1, '\0');
  debug_message_prefix_.resize(2);
  debug_message_prefix_[0] = '#';
  debug_message_prefix_[1] = ' ';
}

RC PlainCommunicator::read_event(SessionEvent *&event)
{
  RC rc = RC::SUCCESS;

  event = nullptr;

  int data_len = 0;
  int read_len = 0;

  const int max_packet_size = 8192;
  std::vector<char> buf(max_packet_size);

  // 持续接收消息，直到遇到'\0'。将'\0'遇到的后续数据直接丢弃没有处理，因为目前仅支持一收一发的模式
  while (true)
  {
    read_len = ::read(fd_, buf.data() + data_len, max_packet_size - data_len);
    if (read_len < 0)
    {
      if (errno == EAGAIN)
      {
        continue;
      }
      break;
    }
    if (read_len == 0)
    {
      break;
    }

    if (read_len + data_len > max_packet_size)
    {
      data_len += read_len;
      break;
    }

    bool msg_end = false;
    for (int i = 0; i < read_len; i++)
    {
      if (buf[data_len + i] == 0)
      {
        data_len += i + 1;
        msg_end = true;
        break;
      }
    }

    if (msg_end)
    {
      break;
    }

    data_len += read_len;
  }

  if (data_len > max_packet_size)
  {
    LOG_WARN("The length of sql exceeds the limitation %d", max_packet_size);
    return RC::IOERR_TOO_LONG;
  }
  if (read_len == 0)
  {
    LOG_INFO("The peer has been closed %s", addr());
    return RC::IOERR_CLOSE;
  }
  else if (read_len < 0)
  {
    LOG_ERROR("Failed to read socket of %s, %s", addr(), strerror(errno));
    return RC::IOERR_READ;
  }

  LOG_INFO("receive command(size=%d): %s", data_len, buf.data());
  event = new SessionEvent(this);
  event->set_query(std::string(buf.data()));
  return rc;
}

RC PlainCommunicator::write_state(SessionEvent *event, bool &need_disconnect)
{
  SqlResult *sql_result = event->sql_result();
  const int buf_size = 2048;
  char *buf = new char[buf_size];
  const std::string &state_string = sql_result->state_string();
  if (state_string.empty())
  {
    const char *result = RC::SUCCESS == sql_result->return_code() ? "SUCCESS" : "FAILURE";
    snprintf(buf, buf_size, "%s\n", result);
  }
  else
  {
    snprintf(buf, buf_size, "%s > %s\n", strrc(sql_result->return_code()), state_string.c_str());
  }

  RC rc = writer_->writen(buf, strlen(buf) + 1);
  if (OB_FAIL(rc))
  {
    LOG_WARN("failed to send data to client. err=%s", strerror(errno));
    need_disconnect = true;
    delete[] buf;
    return RC::IOERR_WRITE;
  }

  need_disconnect = false;
  delete[] buf;

  return RC::SUCCESS;
}

RC PlainCommunicator::write_debug(SessionEvent *request, bool &need_disconnect)
{
  if (!session_->sql_debug_on())
  {
    return RC::SUCCESS;
  }

  SqlDebug &sql_debug = request->sql_debug();
  const std::list<std::string> &debug_infos = sql_debug.get_debug_infos();
  for (auto &debug_info : debug_infos)
  {
    RC rc = writer_->writen(debug_message_prefix_.data(), debug_message_prefix_.size());
    if (OB_FAIL(rc))
    {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      need_disconnect = true;
      return RC::IOERR_WRITE;
    }

    rc = writer_->writen(debug_info.data(), debug_info.size());
    if (OB_FAIL(rc))
    {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      need_disconnect = true;
      return RC::IOERR_WRITE;
    }

    char newline = '\n';
    rc = writer_->writen(&newline, 1);
    if (OB_FAIL(rc))
    {
      LOG_WARN("failed to send new line to client. err=%s", strerror(errno));
      need_disconnect = true;
      return RC::IOERR_WRITE;
    }
  }

  need_disconnect = false;
  return RC::SUCCESS;
}

RC PlainCommunicator::write_result(SessionEvent *event, bool &need_disconnect)
{
  RC rc = write_result_internal(event, need_disconnect);
  if (!need_disconnect)
  {
    (void)write_debug(event, need_disconnect);
  }
  writer_->flush(); // TODO handle error
  return rc;
}

RC PlainCommunicator::write_result_internal(SessionEvent *event, bool &need_disconnect)
{
  RC rc = RC::SUCCESS;
  need_disconnect = true;

  SqlResult *sql_result = event->sql_result();

  if (RC::SUCCESS != sql_result->return_code() || !sql_result->has_operator())
  {
    return write_state(event, need_disconnect);
  }

  rc = sql_result->open();
  if (OB_FAIL(rc))
  {
    sql_result->close();
    sql_result->set_return_code(rc);
    return write_state(event, need_disconnect);
  }


  const TupleSchema &schema = sql_result->tuple_schema();
  const int cell_num = schema.cell_num();

  for (int i = 0; i < cell_num; i++)
  {
    const TupleCellSpec &spec = schema.cell_at(i);
    const char *alias = spec.alias();
    if (nullptr != alias || alias[0] != 0)
    {
      if (0 != i)
      {
        const char *delim = " | ";
        rc = writer_->writen(delim, strlen(delim));
        if (OB_FAIL(rc))
        {
          LOG_WARN("failed to send data to client. err=%s", strerror(errno));
          return rc;
        }
      }

      int len = strlen(alias);
      rc = writer_->writen(alias, len);
      if (OB_FAIL(rc))
      {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        sql_result->close();
        return rc;
      }
    }
  }

  if (cell_num > 0)
  {
    char newline = '\n';
    rc = writer_->writen(&newline, 1);
    if (OB_FAIL(rc))
    {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      sql_result->close();
      return rc;
    }
  }

  rc = RC::SUCCESS;
  Tuple *tuple = nullptr;
  std::vector<FunctionName> funcNames = *event->getFuncNames();
  std::vector<SqlCalculateType> sql_cal_type = *event->getSqlCalType();
  std::vector<CallbackParams> params = *event->getParams();

  if (sql_cal_type.size() != 0 && *sql_cal_type.begin() == SqlCalculateType::AGGREGATE)
  {
    std::vector<Value> aggregate_result(funcNames.size());
    rc = sql_result->next_tuple(tuple);
    int aggregate_num = funcNames.size();
    int TupleNum = 0;
    if (rc == RC::SUCCESS)
    {
      bool begin_flag = true;
      do
      {
        TupleNum += 1;
        int cell_num = tuple->cell_num();
        assert(aggregate_num == cell_num);
        for (int i = 0; i < cell_num; i++)
        {
          Value value;
          rc = tuple->cell_at(i, value);
          FunctionName func_type = funcNames.at(i);
          switch (func_type)
          {
          case AGGREGATE_MAX:
          {
            if (begin_flag)
            {
              std::swap(aggregate_result.at(i), value);
            }
            else if (aggregate_result.at(i).compare(value) <= 0)
            {
              std::swap(aggregate_result.at(i), value);
            }
          }
          break;
          case AGGREGATE_MIN:
          {
            if (begin_flag)
            {
              std::swap(aggregate_result.at(i), value);
              begin_flag = false;
            }
            else if (aggregate_result.at(i).compare(value) >= 0)
            {
              std::swap(aggregate_result.at(i), value);
            }
          }
          break;
          case AGGREGATE_SUM:
          {
            if(begin_flag){
              std::swap(aggregate_result.at(i), value);
              begin_flag = false;
            }else{
              aggregate_result.at(i).add(value);
            }
          }
          break;
          case AGGREGATE_AVG:
          {
            if(begin_flag){
              std::swap(aggregate_result.at(i), value);
            }else{
              aggregate_result.at(i).add(value);
            }
          }
          break;
          case AGGREGATE_COUNT:
          {
            if(begin_flag){
              aggregate_result.at(i).set_int(1);
            }else{
              aggregate_result.at(i).set_int(aggregate_result.at(i).get_int() + 1);
            }
          }
          break;
          default:
          {
            LOG_ERROR("Can't classify this aggregation function");
          }
          break;
          }
        }
        begin_flag = false;
      } while (RC::SUCCESS == (rc = sql_result->next_tuple(tuple)));

      for(int i = 0; i < funcNames.size(); i++){
        if(funcNames.at(i) == AGGREGATE_AVG){
          Value avg = aggregate_result.at(i);
          aggregate_result.at(i).set_float(avg.get_float() / TupleNum);
        }
      }
    }
    else
    {
      LOG_WARN("Attempt to use aggregate function on an empty table");
    }

    for (int i = 0; i < aggregate_result.size(); i++)
    {
      if (i != 0)
      {
        const char *delim = " | ";
        rc = writer_->writen(delim, strlen(delim));
        if (OB_FAIL(rc))
        {
          LOG_WARN("failed to send data to client. err=%s", strerror(errno));
          sql_result->close();
          return rc;
        }
      }

      std::string agg_result_str = aggregate_result.at(i).to_string();
      rc = writer_->writen(agg_result_str.c_str(), agg_result_str.size());
      if (OB_FAIL(rc))
      {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        sql_result->close();
        return rc;
      }
    }
    rc = writer_->writen("\n", 2);
    if (OB_FAIL(rc))
    {
      LOG_WARN("failed to send data to client. err=%s", strerror(errno));
      sql_result->close();
      return rc;
    }
  }
  else
  {
    while (RC::SUCCESS == (rc = sql_result->next_tuple(tuple)))
    {
      assert(tuple != nullptr);

      int cell_num = tuple->cell_num();
      for (int i = 0; i < cell_num; i++)
      {
        if (i != 0)
        {
          const char *delim = " | ";
          rc = writer_->writen(delim, strlen(delim));
          if (OB_FAIL(rc))
          {
            LOG_WARN("failed to send data to client. err=%s", strerror(errno));
            sql_result->close();
            return rc;
          }
        }

        Value value;
        rc = tuple->cell_at(i, value);
        if (i < funcNames.size())
        {
          value.setFunctionName(funcNames[i]);
          value.setParam(params[i]);
        }
        if (rc != RC::SUCCESS)
        {
          sql_result->close();
          return rc;
        }

        std::string cell_str = value.to_string();
        rc = writer_->writen(cell_str.data(), cell_str.size());
        if (OB_FAIL(rc))
        {
          LOG_WARN("failed to send data to client. err=%s", strerror(errno));
          sql_result->close();
          return rc;
        }
      }

      char newline = '\n';
      rc = writer_->writen(&newline, 1);
      if (OB_FAIL(rc))
      {
        LOG_WARN("failed to send data to client. err=%s", strerror(errno));
        sql_result->close();
        return rc;
      }
    }
  }

  if (rc == RC::RECORD_EOF)
  {
    rc = RC::SUCCESS;
  }

  if (cell_num == 0)
  {
    // 除了select之外，其它的消息通常不会通过operator来返回结果，表头和行数据都是空的
    // 这里针对这种情况做特殊处理，当表头和行数据都是空的时候，就返回处理的结果
    // 可能是insert/delete等操作，不直接返回给客户端数据，这里把处理结果返回给客户端
    RC rc_close = sql_result->close();
    if (rc == RC::SUCCESS)
    {
      rc = rc_close;
    }
    sql_result->set_return_code(rc);
    return write_state(event, need_disconnect);
  }
  else
  {

    rc = writer_->writen(send_message_delimiter_.data(), send_message_delimiter_.size());
    if (OB_FAIL(rc))
    {
      LOG_ERROR("Failed to send data back to client. ret=%s, error=%s", strrc(rc), strerror(errno));
      sql_result->close();
      return rc;
    }

    need_disconnect = false;
  }

  RC rc_close = sql_result->close();
  if (OB_SUCC(rc))
  {
    rc = rc_close;
  }

  return rc;
}