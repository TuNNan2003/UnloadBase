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
// Created by Longda on 2021/4/13.
//

#include <string>
#include <sstream>

#include "sql/executor/execute_stage.h"

#include "common/log/log.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "storage/default/default_handler.h"
#include "sql/executor/command_executor.h"
#include "sql/operator/calc_physical_operator.h"
#include "algorithm/algorithm.h"

using namespace std;
using namespace common;

RC ExecuteStage::handle_request(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  const unique_ptr<PhysicalOperator> &physical_operator = sql_event->physical_operator();
  if (physical_operator != nullptr) {
    rc = handle_request_with_physical_operator(sql_event);
    return rc;
  }

  SessionEvent *session_event = sql_event->session_event();

  Stmt *stmt = sql_event->stmt();
  if (stmt != nullptr) {
    CommandExecutor command_executor;
    rc = command_executor.execute(sql_event);
    session_event->sql_result()->set_return_code(rc);
  } else {
    return RC::INTERNAL;
  }
  return rc;
}

RC ExecuteStage::handle_request_with_physical_operator(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;

  Stmt *stmt = sql_event->stmt();
  ASSERT(stmt != nullptr, "SQL Statement shouldn't be empty!");

  unique_ptr<PhysicalOperator> &physical_operator = sql_event->physical_operator();
  ASSERT(physical_operator != nullptr, "physical operator should not be null");

  // TODO 这里也可以优化一下，是否可以让physical operator自己设置tuple schema
  TupleSchema schema;
  std::vector<std::string> exprRawText;
  bool aggrFlag=false;
  switch (stmt->type()) {
    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      aggrFlag=select_stmt->isAggr();
      // 获取前端解析的内容
      exprRawText=select_stmt->names();
      // 特殊处理通配符
      if(exprRawText.size()==1&&exprRawText[0]=="*"){
        exprRawText.clear();
        const std::vector<Table*>&tables=select_stmt->tables();
        for(Table* table:tables){
          for(FieldMeta field:*table->table_meta().field_metas()){
            exprRawText.push_back(field.name());
          }
        }
      }
    } break;

    case StmtType::CALC: {
      CalcPhysicalOperator *calc_operator = static_cast<CalcPhysicalOperator *>(physical_operator.get());
      for (const unique_ptr<Expression> & expr : calc_operator->expressions()) {
        schema.append_cell(expr->name().c_str());
      }
    } break;

    case StmtType::UPDATE: {
      Session *session = sql_event->session_event()->session();
      SessionEvent *session_event = sql_event->session_event();
      SqlResult *sql_result = session_event->sql_result();
      Db* db = session->get_current_db();
      UpdateStmt * update_stmt = static_cast<UpdateStmt*>(stmt);
      Table* table = update_stmt->table();
      rc = update_stmt->check(table);
      if(rc != RC::SUCCESS){
        sql_result->set_return_code(rc);
        return rc;
      }
    } break;

    case StmtType::EXPLAIN: {
      schema.append_cell("Query Plan");
    } break;
    default: {
      // 只有select返回结果
    } break;
  }

  SqlResult *sql_result = sql_event->session_event()->sql_result();
  sql_result->set_tuple_schema(schema);
  sql_result->set_exprRawText(exprRawText);
  sql_result->set_operator(std::move(physical_operator));
  sql_result->setIsAggr(aggrFlag);
  return rc;
}
