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
*   Created by wuhuua on 2023/10/12
*/


#include "algorithm.h"

#include <vector>
#include <string>

#define SPLITBYBF

#ifdef SPLITBYBF
std::vector<std::string> BFsplit(const char* raw,int part){
    std::vector<std::string> res;
    bool opFlag=false;
    while(*raw==' '&&*raw!='\0'){
        raw++;
    }
    while(*raw!='\0'&&part>0){
        if(*raw!=' '){
            raw++;
            continue;
        }else{
            part--;
        }
        while(*raw==' '&&*raw!='\0'){
            raw++;
        }
    }
    int count=0;
    int index=0;
    int len=0;
    bool endFlag=true;
    while(*raw==' '&&*raw!='\0'){
        raw++;
    }
    while(*(raw+index)!='\0'){
        if(*(raw+index)==','&&count==0){
            if(len==0){
                len=index;
            }
            res.push_back(std::string(raw,len));
            len=0;
            raw+=index+1;
            index=0;
            while(*raw!='\0'&& *raw==' '){
                raw++;
            }
        }else if(*(raw+index)==' '&&count==0){
            len=index;
            while(*(raw+index)!='\0'&&*(raw+index)==' '){
                index++;
            }
            if(*(raw+index)=='\0' || 
            (*(raw+index)!=','&&*(raw+index)!='+'&&*(raw+index)!='-'&&*(raw+index)!='*'&&*(raw+index)!=('/')) )
            {
                res.push_back(std::string(raw,len));
                break;
            }else{
                if(*(raw+index)!=','){
                    index++;
                }
                while(*(raw+index)!='\0'&&*(raw+index)==' '){
                    index++;
                }
            }
        }else{
            endFlag=true;
            if(*(raw+index)=='('){
                count++;
            }else if(*(raw+index)==')'){
                count==0?count=0:count--;
            }
            index++;
            if(*(raw+index)=='\0'){
                res.push_back(std::string(raw,index));
            }
        }
    }
    return res;
}
#endif


/*
*   从原始sql语句中分割出想要的原始某一段
*   part为分割段号，从0开始计数
*   逗号隔开的算作一部分的不同段，没有逗号则容器长度为1
*   某段内部被逗号隔开的内容保持不变，逗号左右的空格不保留
*/
std::vector<std::string> Algorithm::splitAttr(std::string raw,int part){
    #ifdef SPLITBYBF
        return BFsplit(raw.c_str(),part);
    #endif
}

