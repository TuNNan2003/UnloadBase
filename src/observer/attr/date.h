/* 
 * Copyright (c) 2023 UnloadBase and/or its affiliates. All rights reserved.
 */

#pragma once

#define SEPERATOR '-'

#define DEFAULT_NULL "NULLDATA"

#include <string>

class Date{
    private:
        const char* year;
        const char* month;
        const char* day;
        const bool nullFlag;
        bool static parseDate(char* &ptr, char* segment,int len,const char* errorInfo);
    public:
        Date(const char* year,const char* month,const char* day,const bool nullFlag);
        Date static parseDate(const char* date_);
        std::string toString() const;
        Date(const Date &date);
        Date operator=(const Date &);
        ~Date();
        Date();
};