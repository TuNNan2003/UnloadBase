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

#pragma once

#include <vector>
#include <unordered_map>
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/expr/expression.h"
#include "sql/stmt/select_stmt.h"

class Db;
class Table;
class FieldMeta;

struct FilterObj
{
  std::unique_ptr<Expression> expr;

  FilterObj(std::unique_ptr<Expression> &expr){
    expr = std::move(expr);
  }
};

class FilterUnit
{
public:
  FilterUnit() = default;
  virtual ~FilterUnit()
  {
  }

  virtual WhereType type() const = 0;
private:
};

class SubQueryFilterUnit : public FilterUnit
{
public:
  SubQueryFilterUnit(std::unique_ptr<Expression> &leftExpr)
  :left_(FilterObj(leftExpr))
  {}
  ~SubQueryFilterUnit() {}

  void set_queryop(SubQueryOp queryop)
  {
    subqueryop_ = queryop;
  }

  Stmt *get_stmt()
  {
    return select_stmt_;
  }

  void set_stmt(Stmt* stmt){
    select_stmt_ = static_cast<SelectStmt*>(stmt);
  }

  FilterObj &left()
  {
    return left_;
  }

  SelectStmt* subquery() const {
    return select_stmt_;
  }

  SubQueryOp subqueryop() const {
    return subqueryop_;
  }

  WhereType type() const override
  {
  return WhereType::SimpleSubQuery;
  }

private:
  FilterObj left_;
  SubQueryOp subqueryop_ = NO_SUB;
  SelectStmt *select_stmt_ = nullptr;
};

class ConditionFilterUnit : public FilterUnit
{
public:

  ConditionFilterUnit(std::unique_ptr<Expression> &leftExpr,std::unique_ptr<Expression> &rightExpr)
  :left_(FilterObj(leftExpr)),right_(FilterObj(rightExpr))
  {}

  ~ConditionFilterUnit() {}
  void set_comp(CompOp comp)
  {
    comp_ = comp;
  }

  CompOp comp() const
  {
    return comp_;
  }

  FilterObj &left()
  {
    return left_;
  }
  FilterObj &right()
  {
    return right_;
  }

  WhereType type() const override
  {
    return WhereType::Condition;
  }
private:
  CompOp comp_ = NO_OP;
  FilterObj left_;
  FilterObj right_;
};

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt
{
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  const std::vector<FilterUnit *> &filter_units() const
  {
    return filter_units_;
  }

public:
  static RC create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                   ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt);

  static RC create_condition_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                               ConditionSqlNode &condition, FilterUnit *&filter_unit);

  static RC create_subquery_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
                               SubQuerySqlNode &condition, FilterUnit *&filter_unit);

private:
  std::vector<FilterUnit *> filter_units_; // 默认当前都是AND关系
};
