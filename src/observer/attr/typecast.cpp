#include "typecast.h"

int TypeCast::castStr2Int(const char * str){
    const char* ptr=str;
    int res=0;
    while(*ptr!='\0'&&*ptr>='0'&&*ptr<='9'){
        res*=10;
        res+=*ptr-'0';
        ptr++;
    }
    return res;
}

float TypeCast::castStr2Float(const char* str){
    const char* ptr=str;
    float intVal=0;
    float decVal=0;
    while(*ptr!='\0'&&*ptr>='0'&&*ptr<='9'){
        intVal*=10;
        intVal+=*ptr-'0';
        ptr++;
    }
    if(*ptr=='.'){
        ptr++;
        float mul=1;
        while(*ptr!='\0'&&*ptr>='0'&&*ptr<='9'){
            mul/=10;
            decVal+=(float)((float)(*ptr-'0'))*mul;
            ptr++;
        }
    }
    return intVal+decVal;
}