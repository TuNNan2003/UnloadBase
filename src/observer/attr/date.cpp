/*
 * Copyright (c) 2023 UnloadBase and/or its affiliates. All rights reserved.
 */

#include "date.h"

#include "common/log/log.h"


Date* Date::parseDate(const char *date_)
{
    char *ptr = (char *)date_;
    int year=0;
    int month=0;
    int day=0;
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
    if(nullFlag_||!validDate(year,month,day)){
        LOG_ERROR("date format is incorrect or date is illegal");
        return new Date();
    }
    LOG_DEBUG("success get year:%d,month:%d,day:%d",year,month,day);
    char* str=new char[DATE_LENGTH];
    memcpy(str,date_,DATE_LENGTH);
    return new Date(str,year,month,day,false);
}

Date::Date(const char* date,int year,int month,int day,const bool nullFlag)
:date(date),year(year),month(month),day(day),nullFlag(nullFlag){}

bool Date::parseDate(char* &ptr, int &segment, int len, const char *errorInfo)
{
    int i = 0,multi=1;
    while (*ptr == '-')
    {
        ptr++;
    }

    for(int j=0;j<len-1;j++){
        multi*=10;
    }
    for (i = 0; i < len; i++)
    {
        if (*ptr == '\0' || *ptr == '-')
        {
            break;
        }
        else
        {
            segment+=(*ptr-'0')*multi;
            multi/=10;
        }
        ptr++;
    }
    if (i != len)
    {
        LOG_ERROR("Date Parser error: %s", errorInfo);
        return false;
    }
    return true;
}

bool Date::validDate(int year,int montn,int day)
{
    //todo
    return true;
}

const char* Date::toString() const
{
    if (this->nullFlag)
    {
        return DEFAULT_NULL;
    }
    return date;
}

char* Date::toBytes(){
    char* data=new char[4];
    if(nullFlag){
        data[0]=(char)0;
        return data;
    }
    date_num highVal;
    date_num lowVal;
    const date_num* ptr=date;
    for(int i=0;i<4;i++){
        if(*ptr=='-'){
            ptr++;
        }
        highVal=((*ptr-'0')<<4);
        ptr++;
        lowVal=((*ptr-'0'))&(15);
        data[i]=lowVal|highVal;
        ptr++;
    }
    return data;
}

Date* Date::parseBytes(char* data){
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
    //delete[] data;
    Date* res=parseDate(str);
    delete[] str;
    return res;
}


Date::~Date(){
    
}

int Date::getYear(){return year;}
int Date::getMonth(){return month;}
int Date::getDay(){return day;}

Date::Date():nullFlag(true),year(0),month(0),day(0),date(DEFAULT_NULL){}