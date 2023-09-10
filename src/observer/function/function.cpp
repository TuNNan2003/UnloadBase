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


#include "function.h"
#include <cstdio>

int SQLFunction::length(const char* str){
    int len=0;
    const char * ptr=str;
    while(*ptr!='\0'){
        ptr++;
        len++;
    }
    return len;
}

float SQLFunction::round(float num, int mark){
    char str[8];
    char fmt[7];
    float res=0;
    sprintf(fmt,"%%0.%df",mark);
    sprintf(str,fmt,num);
    sscanf(str,"%f",&res);
    return res;
}

const char* SQLFunction::date_format(std::shared_ptr<Date> date,const char* fmt){
    return date_format(date->getYear(),date->getMonth(),date->getDay(),fmt);
}

const char* SQLFunction::date_format(int year,int month,int day,const char* fmt){
    int len=length(fmt)+1;
    char* fmtDate=new char[len+6];
    char* ptr=fmtDate;
    int numCount=0;
    int nums[3];
    while(*fmt!='\0'){
        *ptr=*fmt;
        ptr++;
        if(*fmt=='%'){
            fmt++;
            switch (toBiggerCase(*fmt))
            {
            case DATE_FORMAT_YEAR:{
                nums[numCount]=year;
                *ptr='0';
                ptr++;
                *ptr='4';
                ptr++;
                *ptr='d';
                ptr++;
                numCount++;
            }break;
            case DATE_FORMAT_MONTH:{
                nums[numCount]=month;
                *ptr='0';
                ptr++;
                *ptr='2';
                ptr++;
                *ptr='d';
                ptr++;
                numCount++;
            }break;
            case DATE_FORMAT_DAY:{
                nums[numCount]=day;
                *ptr='0';
                ptr++;
                *ptr='2';
                ptr++;
                *ptr='d';
                ptr++;
                numCount++;
            }break;
            default:
                break;
            }
        }
        fmt++;
    }
    switch (numCount)
    {
        case 1:{
            sprintf(fmtDate,fmtDate,nums[0]);
        }break;
        case 2:{
            sprintf(fmtDate,fmtDate,nums[0],nums[1]);
        }break;
        case 3:{
            sprintf(fmtDate,fmtDate,nums[0],nums[1],nums[2]);
        }break;
        default:{          
        }break;
    }
    return fmtDate;
}

char SQLFunction::toBiggerCase(char ch){
    return ch<='z'&&ch>='a' ? ch+'A'-'a':ch;
}
