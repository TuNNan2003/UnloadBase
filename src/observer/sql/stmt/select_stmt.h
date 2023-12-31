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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <memory>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "function/aggr_function.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt 
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override
  {
    return StmtType::SELECT;
  }

public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt);

public:
  const std::vector<Table *> &tables() const
  {
    return tables_;
  }
  std::vector<std::unique_ptr<Expression> > &query_exprs()
  {
    return exprs_;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }

  bool isAggr(){
    return this->exprState_==2;
  }

  bool isVal(){
    return this->exprState_==0;
  }

  std::vector<std::string> &names()
  {
    return names_;
  }

private:
  std::vector<std::unique_ptr<Expression> > exprs_;
  std::vector<std::string> names_;
  // 描述表达式类型，0:常量表达式 1:查询表达式，2:聚合表达式 
  int exprState_;
  std::vector<Table *> tables_;
  FilterStmt *filter_stmt_ = nullptr;
  bool joinFlag_=false;
};
