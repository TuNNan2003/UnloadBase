/*
 * Copyright (c) 2023 UnloadBase and/or its affiliates. All rights reserved.
 */

#include "date.h"

#include "common/log/log.h"


Date* Date::parseDate(const char *date_)
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
        return new Date();
    }
    LOG_DEBUG("success get year:%s,month:%s,day:%s",year,month,day);
    return new Date(year,month,day,false);
}

Date::Date(const char* year,const char* month,const char* day,const bool nullFlag)
:year(year),month(month),day(day),nullFlag(nullFlag){}

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
        LOG_ERROR("Date Parser error: %s", errorInfo);
        return false;
    }
    return true;
}

const char* Date::toString() const
{
    if (this->nullFlag)
    {
        return DEFAULT_NULL;
    }
    char* res = new char[DATE_LENGTH];
    const char *ptr = &year[0];
    for(int i=0;i<4;i++){
        res[i]=*ptr;
        ptr++;
    }
    res[4]='-';
    ptr = &month[0];
    for(int i=5;i<7;i++){
        res[i]=*ptr;
        ptr++;
    }
    res[7]='-';
    ptr = &day[0];
    for(int i=8;i<10;i++){
        res[i]=*ptr;
        ptr++;
    }
    res[10]='\0';
    return res;
}

char* Date::toBytes(){
    char* data=new char[4];
    date_num highVal;
    date_num lowVal;
    const date_num* ptr=year;
    for(int i=0;i<2;i++){
        highVal=((*ptr-'0')<<4);
        ptr++;
        lowVal=((*ptr-'0'))&(15);
        data[i]=lowVal|highVal;
        ptr++;
    }

    ptr=month;
    highVal=((*ptr-'0')<<4);
    ptr++;
    lowVal=((*ptr-'0'))&(15);
    data[2]=lowVal|highVal;

    ptr=day;
    highVal=((*ptr-'0')<<4);
    ptr++;
    lowVal=((*ptr-'0'))&(15);
    data[3]=lowVal|highVal;
    return data;
}

const char* Date::parseBytes(char* data){
    char* str=new char[11];
    date_num* ptr=data;
    date_num val;
    date_num highVal;
    date_num lowVal;
    for(int i=0;i<4;i+=2){
        val=*ptr;
        highVal=(val>>4)&(15);
        lowVal=(val)&(15);
        str[i]=highVal+'0';
        str[i+1]=lowVal+'0';
        ptr++;
    }
    str[4]='-';
    for(int i=5;i<7;i+=2){
        val=*ptr;
        highVal=(val>>4)&(15);
        lowVal=(val)&(15);
        str[i]=highVal+'0';
        str[i+1]=lowVal+'0';
        ptr++;
    }
    str[7]='-';
    for(int i=8;i<10;i+=2){
        val=*ptr;
        highVal=(val>>4)&(15);
        lowVal=(val)&(15);
        str[i]=highVal+'0';
        str[i+1]=lowVal+'0';
        ptr++;
    }
    str[10]='\0';
    return str;
}


Date::~Date(){
    /*
    if(this->year!=nullptr){
        delete[] this->year;
    }
    if(this->month!=nullptr){
        delete[] this->month;
    }
    if(this->day!=nullptr){
        delete[] this->day;
    }
    */
}

Date::Date():nullFlag(true),year(nullptr),month(nullptr),day(nullptr){}