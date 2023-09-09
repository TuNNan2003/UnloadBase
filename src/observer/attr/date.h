/* 
 * Copyright (c) 2023 UnloadBase and/or its affiliates. All rights reserved.
 */

#pragma once

#define SEPERATOR '-'

#define DEFAULT_NULL "NULLDATA"

#define DATE_SIZE 4

#define DATE_LENGTH 11

#include <string>

typedef char date_num;

class Date{
    private:
        const char* date;
        const int year;
        const int month;
        const int day;
        const bool nullFlag;
        bool static parseDate(char* &ptr, int &segment,int len,const char* errorInfo);
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