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
#pragma once

#include <string>
#include <vector>
#include "function/function.h"

// 存放所有回调内容的集合
class CallbackSet{
  private:
    std::vector<FunctionName> funcNames;    ///< 回调函数名称
    std::vector<SqlCalculateType> sql_calculate_type;
    CallbackInfo callbackInfo;              ///< 回调函数其他参数

  public:
    CallbackSet();
  
  // 初始化回调内容
  public:
    void addFuncName(FunctionName funcName);
    void addSqlCalculateType(const SqlCalculateType sql_cal_type);
    void addCallBackInfo(CallbackParams param);
  
  // 获取回调内容
  public:
    std::vector<FunctionName>* getFuncNames();
    bool checkSqlCalType();
    std::vector<CallbackParams>* getParams();
  
  // 根据回调内容进行计算
  public:
    void calc(int index,Value &value);
};