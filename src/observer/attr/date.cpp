/*
 * Copyright (c) 2023 UnloadBase and/or its affiliates. All rights reserved.
 */

#include "date.h"


Date Date::parseDate(const char *date_)
{
    char *ptr = (char *)date_;
    char* year=new char[4];
    char* month=new char[2];
    char* day=new char[2];
    bool nullFlag_=false;
    if (!parseDate(ptr, year, 4, "year format error"))
    {
        nullFlag_=true;
    }
    if (!parseDate(ptr, month, 2, "month format error"))
    {
        nullFlag_=true;
    }
    if (!parseDate(ptr, day, 2, "day format error"))
    {
        nullFlag_=true;
    }
    if(nullFlag_){
        delete[] year;
        delete[] month;
        delete[] day;
        return Date();
    }
    return Date(year,month,day,false);
}

Date::Date(const char* year,const char* month,const char* day,const bool nullFlag)
:year(year),month(month),day(day),nullFlag(nullFlag){}

Date::Date(const Date &date):year(date.year),month(date.month),day(date.day),nullFlag(date.nullFlag){}

bool Date::parseDate(char* &ptr, char *segment, int len, const char *errorInfo)
{
    int i = 0;
    while (*ptr == '-')
    {
        ptr++;
    }
    for (i = 0; i < len; i++)
    {
        if (*ptr == '\0' || *ptr == '-')
        {
            segment[i] = '\0';
            break;
        }
        else
        {
            segment[i] = *ptr;
        }
        ptr++;
    }
    if (i == 0)
    {
        return false;
    }
    return true;
}

std::string Date::toString() const
{
    if (this->nullFlag)
    {
        return DEFAULT_NULL;
    }
    std::string res = std::string();
    const char *ptr = &year[0];
    while (*ptr != '\0')
    {
        res.push_back(*ptr);
        ptr++;
    }
    res.push_back('-');
    ptr = &month[0];
    while (*ptr != '\0')
    {
        res.push_back(*ptr);
        ptr++;
    }
    res.push_back('-');
    ptr = &day[0];
    while (*ptr != '\0')
    {
        res.push_back(*ptr);
        ptr++;
    }
    return res;
}

Date Date::operator=(const Date &date){
    this->~Date();
    return Date(date);
}

Date::~Date(){
    if(this->year!=nullptr){
        delete[] this->year;
    }
    if(this->month!=nullptr){
        delete[] this->month;
    }
    if(this->day!=nullptr){
        delete[] this->day;
    }
}

Date::Date():nullFlag(true),year(nullptr),month(nullptr),day(nullptr){}