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
*   Created by wuhuua on 2023/8/28
*/

#pragma once

#define SEPERATOR '-'

#define DEFAULT_NULL "NULLDATA"

#define DATE_SIZE 4

#define DATE_LENGTH 11

#include <string>
#include <memory>

typedef char date_num;

class Date{
    private:
        const char* date;
        const int year;
        const int month;
        const int day;
        const bool nullFlag;
    public:
        Date(const char* date,int year,int month,int day,const bool nullFlag);
        static std::shared_ptr<Date> parseDate(const char* date_);
        static std::shared_ptr<Date> parseBytes(char* data); 
        static bool validDate(int year,int month,int day);
        bool isNull();
        static int compare(std::shared_ptr<Date> src,std::shared_ptr<Date> tgt);
        const char* toString() const;
        char* toBytes();
        ~Date();
        Date();
        int getYear();
        int getMonth();
        int getDay();
        int toInt();
};