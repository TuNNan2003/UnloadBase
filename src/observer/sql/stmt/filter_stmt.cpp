/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "expr_factory.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_)
  {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                      ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++)
  {
    FilterUnit *filter_unit = nullptr;
    if(conditions->subquery == NULL){
      rc = create_condition_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    }
    else{
      rc = create_subquery_filter_unit(db, default_table, tables, *(conditions[i].subquery), filter_unit);
    }
    if (rc != RC::SUCCESS)
    {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}


RC FilterStmt::create_condition_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                                  ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP)
  {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }
  int funcType=0;
  std::unique_ptr<Expression> left=makeArthExpr(condition.left,*tables,funcType,rc);
  if(funcType==2||rc!=RC::SUCCESS){
    LOG_WARN("aggregate function is not allowed here");
    return RC::INVALID_ARGUMENT;
  }
  funcType=0;
  std::unique_ptr<Expression> right=makeArthExpr(condition.right,*tables,funcType,rc);
  if(funcType==2||rc!=RC::SUCCESS){
    LOG_WARN("aggregate function or contant value is not allowed here");
    return RC::INVALID_ARGUMENT;
  }

  // 这里会移交表达式的所有权到过滤器单元中
  ConditionFilterUnit* condition_filter_unit = new ConditionFilterUnit(left,right);

  condition_filter_unit->set_comp(comp);

  filter_unit = static_cast<FilterUnit*>(condition_filter_unit);
  return rc;
}

RC FilterStmt::create_subquery_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                             SubQuerySqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  SubQueryOp subquery_op = condition.queryOP;
  if(subquery_op < IN_SUB || subquery_op >= NO_SUB){
    LOG_WARN("invalid sub query operator: %d", subquery_op);
    return RC::INVALID_ARGUMENT;
  }

  int funcType=0;
  std::unique_ptr<Expression> left=makeArthExpr(condition.attr,*tables,funcType,rc);
  if(funcType!=1||rc!=RC::SUCCESS){
    LOG_WARN("aggregate function or contant value is not allowed here");
    return RC::INVALID_ARGUMENT;
  }

  SubQueryFilterUnit* SQ_filter = new SubQueryFilterUnit(left);

  Table* table = nullptr;
  const FieldMeta *field = nullptr;

  SQ_filter->set_queryop(condition.queryOP);
  
  Stmt* stmt = nullptr;
  rc = SelectStmt::create(db, condition.sub_query->selection, stmt);
  SQ_filter->set_stmt(stmt);

  filter_unit = static_cast<FilterUnit*>(SQ_filter);
  return rc;
}
