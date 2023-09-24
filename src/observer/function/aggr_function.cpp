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
*   Created by wuhuua on 2023/9/24
*/

#include "aggr_function.h"

void (*AggrFunc::getAggrFunc(FunctionName name))(Value,Value&,int){
    switch(name){
        case FunctionName::AGGREGATE_MAX:{
            return &AggrFunc::max;
        }break;
        case FunctionName::AGGREGATE_MIN:{
            return &AggrFunc::min;
        }break;
        case FunctionName::AGGREGATE_AVG:{
            return &AggrFunc::avg;
        }break;
        case FunctionName::AGGREGATE_SUM:{
            return &AggrFunc::sum;
        }break;
        case FunctionName::AGGREGATE_COUNT:{
            return &AggrFunc::count;
        }break;
        default:{
            return &AggrFunc::nothing2do;
        }break;
    }
}


void AggrFunc::max(Value value,Value& res,int state){
    switch(state){
        case 0:{
            std::swap(res,value);
        }break;
        case 1:{
            if(res.compare(value)<=0){
                std::swap(res,value);
            }
        }break;
        case 2:{break;}
        default:{break;}
    }
}

void AggrFunc::min(Value value,Value& res,int state){
    switch(state){
        case 0:{
            std::swap(res,value);
        }break;
        case 1:{
            if(res.compare(value)>=0){
                std::swap(res,value);
            }
        }break;
        case 2:{break;}
        default:{break;}
    }
}

void AggrFunc::sum(Value value,Value& res,int state){
    switch(state){
        case 0:{
            std::swap(res,value);
        }break;
        case 1:{
            res.add(value);
        }break;
        case 2:{break;}
        default:{break;}
    }
}

void AggrFunc::avg(Value value,Value& res,int state){
    static int count=0;
    switch(state){
        case 0:{
            std::swap(res,value);
            count=0;
        }break;
        case 1:{
            res.add(value);
            count++;
        }break;
        case 2:{
            res.set_float(res.get_float() / count);
            count=0;
        }
        default:{break;}
    }
}

void AggrFunc::count(Value value,Value& res,int state){
    switch(state){
        case 0:{
            res.set_int(1);
        }break;
        case 1:{
            res.set_int(res.get_int()+1);
        }break;
        case 2:{break;}
        default:{break;}
    }
}

void AggrFunc::nothing2do(Value value,Value& res,int state){
    switch(state){
        case 0:{break;}
        case 1:{break;}
        case 2:{break;}
        default:{break;}
    }
}