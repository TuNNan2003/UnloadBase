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

enum SqlCalculateType{
    NULLSql,
    AGGREGATE
};

class SQLFunction{
    public:
        static int length(const char* str);
        static float round(float num,int mark);
        static const char* date_format(std::shared_ptr<Date> date,const char* fmt);
    private:
        static const char* date_format(int year,int day,int month,const char* fmt);
        static char toBiggerCase(char ch);
};