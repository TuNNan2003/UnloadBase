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
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

#include "date.h"
#include "common/log/log.h"
#include "algorithm/algorithm.h"


void formatDate(int year, int month, int day, char* formattedDate) {
    std::stringstream ss;
    // Format year
    ss << year;
    std::string yearString = ss.str();
    ss.str(""); 
    // Format month
    if (month < 10) {
        ss << '0'; 
    }
    ss << month;
    std::string monthString = ss.str();
    ss.str(""); 
    // Format day
    if (day < 10) {
        ss << '0'; 
    }
    ss << day;
    std::string dayString = ss.str();
    strcpy(formattedDate, (yearString + "-" + monthString + "-" + dayString).c_str());
}


std::shared_ptr<Date> Date::parseDate(const char *date_)
{
    char *ptr = (char *)date_;
    std::vector<std::string> dateParts=Algorithm::splitStr(std::string(date_),'-');
    if(dateParts.size()!=3){
        LOG_DEBUG("date format is incorrect or date is illegal");
        return std::make_shared<Date>();
    }
    int year = std::stoi(dateParts[0]);
    int month = std::stoi(dateParts[1]);
    int day = std::stoi(dateParts[2]);
    
    if(!validDate(year,month,day)){
        LOG_DEBUG("date format is incorrect or date is illegal");
        return std::make_shared<Date>();
    }
    LOG_DEBUG("success get year:%d,month:%d,day:%d",year,month,day);
    char* str=new char[DATE_LENGTH];
    formatDate(year,month,day,str);
    return std::make_shared<Date>(str,year,month,day,false);
}

Date::Date(const char* date,int year,int month,int day,const bool nullFlag)
:date(date),year(year),month(month),day(day),nullFlag(nullFlag){}


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