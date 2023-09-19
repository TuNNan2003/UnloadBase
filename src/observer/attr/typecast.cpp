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
*   Created by wuhuua on 2023/9/19
*/


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