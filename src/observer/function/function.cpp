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
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <cstdio>

#include "function.h"

void SQLFunction::calc(Value &value,FunctionName name,FunctionParams param){
    switch (name)
    {
    case FunctionName::LENGTH:{
        value.set_int(length(value.get_string().c_str()));
    }break;
    case FunctionName::ROUND:{
        if(param.type==ParamType::INT_PARAM){
            value.set_float(round(value.get_float(),param.num_info.int_value_));
        }
    }break;
    case FunctionName::DATE_FORMAT:{
        if(param.type==ParamType::STR_PARAM){
            std::string str=date_format(value.get_date(),param.str_info);
            value.set_string(str.c_str(),str.length());
        }
    }break;
    default:
        break;
    }
}


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

std::string SQLFunction::date_format(std::shared_ptr<Date> date,std::string fmt){
    std::string str=date_format(date->getYear(),date->getMonth(),date->getDay(),fmt.c_str());
    return str;
}

std::string SQLFunction::date_format(int year,int month,int day,const char* fmt){
    std::stringstream ss;
    int numCount=0;
    while(*fmt!='\0'){
        if(*fmt=='%'){
            fmt++;
            if(*fmt=='\0'){break;}
            switch (toBiggerCase(*fmt))
            {
            case DATE_FORMAT_YEAR:{
                ss<<year;
            }break;
            case DATE_FORMAT_MONTH:{
                if (month < 10) {
                    ss << '0'; 
                }
                ss << month;
            }break;
            case DATE_FORMAT_DAY:{
                if (day < 10){
                    ss << '0';
                }
                ss << day;
            }break;
            default:
                ss << '%';
                ss << *fmt;
            }
        }else{
            ss << *fmt;
        }
        fmt++;
    }
    return ss.str();
}

char SQLFunction::toBiggerCase(char ch){
    return ch<='z'&&ch>='a' ? ch+'A'-'a':ch;
}
