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
*   Created by wuhuua on 2023/9/10
*/

#include "callback.h"


void CallBack::callback(SQLStageEvent *sql_event,SessionEvent *event){
    ParsedSqlNode *sql_node = sql_event->sql_node().get();
    if(sql_node->flag==SCF_SELECT){
        SelectSqlNode select_sql= sql_node->selection;
        event->initNames();
        for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
            const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
            event->addFuncName(relation_attr.function_name);
            event->addSqlCalculateType(relation_attr.sql_type);
            event->addCallBackInfo(relation_attr.param);
        }
    }
}