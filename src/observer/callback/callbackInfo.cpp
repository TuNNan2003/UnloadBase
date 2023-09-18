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

#include "callbackInfo.h"

CallbackInfo::CallbackInfo(){
    this->infos=std::vector<CallbackParams>();
}

void CallbackInfo::addCallbackInfo(CallbackParams param){
    this->infos.push_back(param);
}

std::vector<CallbackParams>* CallbackInfo::getCallbackInfo(){
    return &this->infos;
}