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
// Created by WangYunlai on 2023/06/28.
//

#include <sstream>
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "attr/date.h"
#include "attr/typecast.h"
#include "algorithm/algorithm.h"

const char *ATTR_TYPE_NAME[] = {"undefined","dates", "chars", "ints", "floats", "booleans","null"};

#define  NULLTYPESTR "NULL"

const char *attr_type_to_string(AttrType type)
{
  if (type >= UNDEFINED && type <= NULLTYPE) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

Value::Value(int val)
{
  set_int(val);
}

Value::Value(float val)
{
  set_float(val);
}

Value::Value(bool val)
{
  set_boolean(val);
}

Value::Value(const char *s, int len /*= 0*/)
{
  set_string(s, len);
}
Value::Value(const char *date,bool dateFlag){
  set_date(date);
}
Value::Value(AttrType type){
  this->attr_type_=type;
}

void Value::set_data(char *data, int length)
{
  switch (attr_type_) {
    case DATES: {
      date_value_=Date::parseBytes(data);
      length_=DATE_SIZE;
    } break;
    case CHARS: {
      set_string(data, length);
    } break;
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_ = length;
    } break;
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_ = length;
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_ = length;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val)
{
  attr_type_ = INTS;
  num_value_.int_value_ = val;
  length_ = sizeof(val);
}

void Value::set_float(float val)
{
  attr_type_ = FLOATS;
  num_value_.float_value_ = val;
  length_ = sizeof(val);
}
void Value::set_date(const char *date){
  attr_type_ = DATES;
  date_value_=Date::parseDate(date);
  if(date_value_->isNull()){
    attr_type_=UNDEFINED;
  }
  length_=DATE_SIZE;
}
void Value::set_boolean(bool val)
{
  attr_type_ = BOOLEANS;
  num_value_.bool_value_ = val;
  length_ = sizeof(val);
}
void Value::set_string(const char *s, int len /*= 0*/)
{
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case DATES: {
      set_date(value.get_date()->toString());
    }break;
    case INTS: {
      set_int(value.get_int());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case NULLTYPE: {
      attr_type_=AttrType::NULLTYPE;
    } break;
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

const char *Value::data() const
{
  switch (attr_type_) {
    case DATES: {
      char* data=date_value_->toBytes();
      return data;
    }break;
    case CHARS: {
      return str_value_.c_str();
    } break;
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  std::stringstream os;
  switch (attr_type_) {
    case DATES: {
      return date_value_->toString();
    }
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    case NULLTYPE: {
      return NULLTYPESTR;
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

int Value::compare(const Value &other) const
{
  if(this->attr_type_==AttrType::NULLTYPE||other.attr_type_==AttrType::NULLTYPE){
    return -1;
  }
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case DATES: {
        return Date::compare(date_value_,other.date_value_);
      }break;
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS){
    int str2Int=TypeCast::castStr2Int(this->str_value_.c_str());
    return common::compare_int((void *)&str2Int,(void *)&other.num_value_.int_value_);
  } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS){
    int str2Int=TypeCast::castStr2Int(other.str_value_.c_str());
    return common::compare_int((void *)&this->num_value_.int_value_,(void *)&str2Int);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS){
    float str2Float=TypeCast::castStr2Float(this->str_value_.c_str());
    return common::compare_float((void *)&str2Float,(void*)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS){
    float str2Float=TypeCast::castStr2Float(other.str_value_.c_str());
    return common::compare_float((void *)&this->num_value_.float_value_,(void *)&str2Float);
  }
  LOG_WARN("not supported %d, %d", this->attr_type_, other.attr_type_);
  return -1;  // TODO return rc?
}

bool Value::like(const Value& other) const {
  std::string s = this->get_string();
  std::string p = other.get_string();
  return Algorithm::wildcardMatching(s,p);
}

void Value::add(const Value& other){
  switch (attr_type_){
    case INTS : {
      set_int(get_int() + other.get_int());
    }break;
    case FLOATS : {
      set_float(get_float() + other.get_float());
    }break;
    default : {
      LOG_WARN("NOT implemented");
    }break;
  }
}

int Value::get_int() const
{
  switch (attr_type_) {
    case DATES: {
      return date_value_->toInt();
    }break;
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case DATES: {
      return (float)date_value_->toInt();
    }break;
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::shared_ptr<Date> Value::get_date() const {
  if(this->attr_type_!=DATES && this->attr_type_!=CHARS){
    LOG_WARN("cannot change this type to date. type=%d", attr_type_);
    return std::make_shared<Date>();
  }
  switch(attr_type_){
    case CHARS:{
      return Date::parseDate(str_value_.c_str());
    }break;
    case DATES:{
        return date_value_;
    }break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return std::make_shared<Date>();
    }
  }
}

std::string Value::get_string() const
{
  return this->to_string();
}

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case DATES:{
      return !date_value_->isNull();
    }break;
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}

bool Value::tryCompare(AttrType left,AttrType right){
  return (
      (left == right)                       ||
      (left==NULLTYPE)                      ||
      (right==NULLTYPE)                     ||
      (left == INTS   &&  right== FLOATS)   ||
      (left ==FLOATS  &&  right==INTS)      ||
      (left==CHARS    &&  right==INTS)      || 
      (left==INTS     &&  right==CHARS)     ||
      (left==CHARS    &&  right==FLOATS)    ||
      (left==FLOATS   &&  right==CHARS)
      );
}