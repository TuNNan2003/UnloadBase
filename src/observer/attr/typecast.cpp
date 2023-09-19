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