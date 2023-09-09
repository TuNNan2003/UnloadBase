/*
 * Copyright (c) 2023 UnloadBase and/or its affiliates. All rights reserved.
 */

#include "date.h"

#include "common/log/log.h"


std::shared_ptr<Date> Date::parseDate(const char *date_)
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
        return std::make_shared<Date>();
    }
    LOG_DEBUG("success get year:%d,month:%d,day:%d",year,month,day);
    char* str=new char[DATE_LENGTH];
    memcpy(str,date_,DATE_LENGTH);
    return std::make_shared<Date>(str,year,month,day,false);
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

bool Date::validDate(int year,int month,int day)
{
    if (year <= 0) {
        return false;
    }
    if (month < 1 || month > 12) {
        return false;
    }
    int daysInMonth;
    switch (month) {
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                daysInMonth = 29;
            } else {
                daysInMonth = 28;
            }
            break;
        case 4: 
        case 6: 
        case 9: 
        case 11: 
            daysInMonth = 30;
            break;
        default: 
            daysInMonth = 31;
            break;
    }
    if (day < 1 || day > daysInMonth) {
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

std::shared_ptr<Date> Date::parseBytes(char* data){
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
    std::shared_ptr<Date> res=parseDate(str);
    delete[] str;
    return res;
}

int Date::toInt(){
    if(nullFlag){
        return 0;
    }
    return this->day+this->month*100+this->year*10000;
}

bool Date::isNull(){
    return nullFlag;
}

int Date::compare(std::shared_ptr<Date> src,std::shared_ptr<Date> tgt){
    if(src->isNull()||tgt->isNull()){
        LOG_ERROR("cannot compare date which has NULL value!");
        return 0;
    }
    return src->toInt()-tgt->toInt();
}


Date::~Date(){
    if(!nullFlag){
        delete[] date;
    }
    LOG_DEBUG("DATE released");
}

int Date::getYear(){return year;}
int Date::getMonth(){return month;}
int Date::getDay(){return day;}

Date::Date():nullFlag(true),year(0),month(0),day(0),date(DEFAULT_NULL){}