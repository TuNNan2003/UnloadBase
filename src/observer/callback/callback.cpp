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
#include "function/aggr_function.h"
#include "callbackSet.h"


void CallBack::callback(SQLStageEvent *sql_event,SessionEvent *event){
    ParsedSqlNode *sql_node = sql_event->sql_node().get();
    if(sql_node->flag==SCF_SELECT){
        SelectSqlNode select_sql= sql_node->selection;
        SqlResult* result=event->sql_result();
        CallbackSet* callbackSet=new CallbackSet();
        for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
            const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
            callbackSet->addFuncName(relation_attr.function_name);
            callbackSet->addSqlCalculateType(relation_attr.sql_type);
            callbackSet->addCallBackInfo(relation_attr.param);
        }
        result->setCallBackSet(callbackSet);
    }
}

std::vector<Value> CallBack::aggregate(SessionEvent *event,RC &rc){
  //根据聚合函数名称获得其指针
  std::vector<FunctionName> funcNames = *event->sql_result()->getCallbackSet()->getFuncNames();
  std::vector<AggregateFunction*> AggregateFuncs(funcNames.size());
  for(int i=0;i<AggregateFuncs.size();i++){
    AggregateFuncs[i] = AggregateFunctionFactory::CreateAggregateFunction(funcNames[i]);
  }

  //遍历每个row执行聚合函数
  SqlResult *sql_result = event->sql_result();
  Tuple *tuple = nullptr;
  std::vector<Value> aggregate_result(AggregateFuncs.size());

  rc = sql_result->next_tuple(tuple);
  int aggregate_num = funcNames.size();
  if (rc == RC::SUCCESS)
  {
    do
    {    
      int cell_num = tuple->cell_num();
      assert(aggregate_num == cell_num);
      for (int i = 0; i < cell_num; i++)
      {
        Value value;
        rc = tuple->cell_at(i, value);
        AggregateFuncs[i]->calc(value, aggregate_result[i]);
      }
    } while (RC::SUCCESS == (rc = sql_result->next_tuple(tuple)));
    for(int i = 0; i < funcNames.size(); i++){
      AggregateFuncs[i]->set(aggregate_result[i]);
    }
  }
  else
  {
    LOG_WARN("Attempt to use aggregate function on an empty table");
  }

  // 删除聚合函数对象
  for(AggregateFunction* func:AggregateFuncs){
    if(func!=nullptr){
      delete func;
    }
  }
  return aggregate_result;
}