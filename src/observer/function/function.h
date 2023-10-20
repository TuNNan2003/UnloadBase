/*
Copyright (c) 2023 UnloadHome and/or its affiliates. All rights reserved.
UnloadBase is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
 */

/*
*   Created by wuhuua on 2023/9/9
*/

#pragma once

#include "attr/date.h"
#include "sql/parser/value.h"

#include <string>

#define DATE_FORMAT_YEAR   'Y'
#define DATE_FORMAT_MONTH  'M'
#define DATE_FORMAT_DAY    'D'
#define DATE_FORMAT_ERROR  "DATEFORMATERROR"

enum FunctionName{
    NULLFUNC,
    LENGTH,
    ROUND,
    DATE_FORMAT,
    AGGREGATE_MAX,
    AGGREGATE_MIN,
    AGGREGATE_COUNT,
    AGGREGATE_AVG,
    AGGREGATE_SUM
};

enum ParamType{
    INT_PARAM,
    FLOAT_PARAM,
    BOOL_PARAM,
    STR_PARAM,
    UNDIFINED_PARAM
};

struct FunctionParams{
  union {
    int int_value_;
    float float_value_;
    bool bool_value_;
  } num_info;                             ///< 数字附加内容
  std::string str_info;                   ///< 文字附加内容
  ParamType type=ParamType::UNDIFINED_PARAM;
};

enum SqlCalculateType{
    NULLSql,
    AGGREGATE
};

class SQLFunction{
    public:
        static void calc(Value &value,FunctionName name,FunctionParams param);
        static int length(const char* str);
        static float round(float num,int mark);
    private:
        static std::string date_format(std::shared_ptr<Date> date,std::string fmt);
        static std::string date_format(int year,int day,int month,const char* fmt);
        static char toBiggerCase(char ch);
};