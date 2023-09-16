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
*   Created by wuhuua on 2023/9/16
*/
#pragma once

#include <string>
#include <vector>

enum ParamType{
    INT_PARAM,
    FLOAT_PARAM,
    BOOL_PARAM,
    STR_PARAM,
    UNDIFINED_PARAM
};

struct CallbackParams{
  union {
    int int_value_;
    float float_value_;
    bool bool_value_;
  } num_info;                             ///< 数字附加内容
  std::string str_info;                   ///< 文字附加内容
  ParamType type=ParamType::UNDIFINED_PARAM;
};



class CallbackInfo{
private:
    std::vector<CallbackParams> infos;
public:
    CallbackInfo();
    void addCallbackInfo(CallbackParams param);
    std::vector<CallbackParams>* getCallbackInfo();
};