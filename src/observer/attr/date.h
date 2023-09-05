/* 
 * Copyright (c) 2023 UnloadBase and/or its affiliates. All rights reserved.
 */

#pragma once

#define SEPERATOR '-'

#define DEFAULT_NULL "NULLDATA"

#define DATE_LENGTH 11

#include <string>

typedef char date_num;

class Date{
    private:
        const char* year;
        const char* month;
        const char* day;
        const bool nullFlag;
        bool static parseDate(char* &ptr, char* segment,int len,const char* errorInfo);
    public:
        Date(const char* year,const char* month,const char* day,const bool nullFlag);
        static Date* parseDate(const char* date_);
        const char* toString() const;
        static const char* parseBytes(char* data); 
        char* toBytes();
        Date(const Date &date);
        ~Date();
        Date();
};