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
*   Created by wuhuua on 2023/10/29
*/

#pragma once

#include "storage/table/table.h"
#include "sql/expr/expression.h"

/*
*   解析单个ExpresssionSqlNode到表达式
*   funcType返回表达式类型,0:常量,1:普通字段,2:聚合函数,初始值应传入0
*   传入的ExpressionSqlNode会在解析时被逐层析构
*/
std::unique_ptr<Expression> makeArthExpr(
  ExpressionSqlNode* expr_attr,
  const std::unordered_map<std::string, Table *> &table_map,
  int &funcType,
  RC &rc
  );