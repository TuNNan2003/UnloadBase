#include "function.h"
#include <cstdio>

int Function::length(const char* str){
    int len=0;
    const char * ptr=str;
    while(*ptr!='\0'){
        ptr++;
        len++;
    }
    return len;
}

float Function::round(float num, int mark){
    char str[8];
    char fmt[7];
    float res=0;
    sprintf(fmt,"%%0.%df",mark);
    sprintf(str,fmt,num);
    sscanf(str,"%f",&res);
    return res;
}

const char* Function::date_format(Value date,const char* fmt){
    if(date.attr_type()!=DATES){
        return DATE_FORMAT_ERROR;
    }
    return date_format(date.get_date()->getYear(),date.get_date()->getMonth(),date.get_date()->getDay(),fmt);
}

const char* Function::date_format(int year,int month,int day,const char* fmt){
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

char Function::toBiggerCase(char ch){
    return ch<='z'&&ch>='a' ? ch+'A'-'a':ch;
}
