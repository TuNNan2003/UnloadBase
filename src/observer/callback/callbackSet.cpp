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
*   Created by wuhuua on 2023/10/9
*/

#include "callbackSet.h"

CallbackSet::CallbackSet(){
    this->callbackInfo=CallbackInfo();
    this->funcNames=std::vector<FunctionName>();
    this->sql_calculate_type=std::vector<SqlCalculateType>();
}

void CallbackSet::addFuncName(FunctionName funcName){funcNames.push_back(funcName);}

void CallbackSet::addSqlCalculateType(const SqlCalculateType sql_cal_type){
    sql_calculate_type.push_back(sql_cal_type);
}

void CallbackSet::addCallBackInfo(CallbackParams param){
    callbackInfo.addCallbackInfo(param);
}

std::vector<FunctionName>* CallbackSet::getFuncNames(){
    return &funcNames;
}

bool CallbackSet::checkSqlCalType(){
    return sql_calculate_type.size() != 0 && *sql_calculate_type.begin() == SqlCalculateType::AGGREGATE;
}

std::vector<CallbackParams>* CallbackSet::getParams(){
    return callbackInfo.getCallbackInfo();
}


void CallbackSet::calc(int index,Value &value){
    if(index>=funcNames.size()||index<0){
        return;
    }
    SqlCalculateType type=sql_calculate_type[index];
    if(type==SqlCalculateType::AGGREGATE){
        return;
    }
    FunctionName funcName=funcNames[index];
    if(funcName==FunctionName::NULLFUNC){
        return;
    }
    CallbackParams param=callbackInfo.getCallbackInfo()->at(index);
    SQLFunction::calc(value,funcName,param);
}