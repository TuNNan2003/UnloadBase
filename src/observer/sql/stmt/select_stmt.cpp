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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "expr_factory.h"

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<std::unique_ptr<Expression>> &query_exprs)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    query_exprs.push_back(std::make_unique<FieldExpr>(Field(table, table_meta.field(i))));
  }
}

// 多表通配符处理
static RC dealWithWildcard(
  RelAttrSqlNode &relation_attr,
  std::vector<Table *> &tables,
  std::vector<std::unique_ptr<Expression>> &query_exprs)
{
  // 对于count(*)要特殊处理，如果有多张表选择第一张表去查询行数
  if(relation_attr.function_name==FunctionName::AGGREGATE_COUNT){
    std::unique_ptr<AggregateFunction> aggr = 
    AggregateFunctionFactory::CreateAggregateFunction(relation_attr.function_name);
    if(tables.size()==0){
      LOG_DEBUG("no table to count lines with '*' ");
      return RC::EMPTY;
    }
    Table* default_table=tables[0];
    const TableMeta &table_meta = default_table->table_meta();
    const FieldMeta* field_meta = table_meta.field(table_meta.sys_field_num());
    if (nullptr == field_meta) {
      LOG_WARN("no such field, in expr resolving field=%s.%s", default_table->name(), relation_attr.attribute_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
    query_exprs.push_back(std::make_unique<FieldExpr>(
      Field(default_table,field_meta),relation_attr.function_name,relation_attr.param,aggr));
  }else if(relation_attr.function_name==FunctionName::NULLFUNC){
    for (Table *table : tables) {
      wildcard_fields(table, query_exprs);
    }
  }else{
    return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}

// 单表通配符处理
static RC dealWithWildcard(
  RelAttrSqlNode &relation_attr,
  Table* &default_table,
  std::vector<std::unique_ptr<Expression>> &query_exprs)
{
  // 对于count(*)要特殊处理，如果有多张表选择第一张表去查询行数
  if(relation_attr.function_name==FunctionName::AGGREGATE_COUNT){
    std::unique_ptr<AggregateFunction> aggr = 
    AggregateFunctionFactory::CreateAggregateFunction(relation_attr.function_name);
    const TableMeta &table_meta = default_table->table_meta();
    const FieldMeta* field_meta = table_meta.field(table_meta.sys_field_num());
    if (nullptr == field_meta) {
      LOG_WARN("no such field, in expr resolving field=%s.%s", default_table->name(), relation_attr.attribute_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }
    query_exprs.push_back(std::make_unique<FieldExpr>(
      Field(default_table,field_meta),relation_attr.function_name,relation_attr.param,aggr));
  }else if(relation_attr.function_name==FunctionName::NULLFUNC){
    wildcard_fields(default_table, query_exprs);
  }else{
    return RC::INVALID_ARGUMENT;
  }
  return RC::SUCCESS;
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // collect query fields in `select` statement
  std::vector<std::unique_ptr<Expression>> query_exprs;
  std::unordered_map<std::string,std::shared_ptr<AggregateFunction>> query_aggrs;
  // 是否聚合，为0时代表常数表达式，为1代表普通字段表达式，为2代表聚合函数字段表达式
  int funcType=0;
  int exprNum=select_sql.attributes.size();
  std::vector<std::string> names=std::vector<std::string>(exprNum);
  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    ExpressionSqlNode* expr_attr = select_sql.attributes[i];

    // 设置展示的表头名称
    names[exprNum-i-1]=expr_attr->name;

    // 表达式内容为值
    if(expr_attr->type==EXPRTYPE::VAL){
      query_exprs.push_back(std::make_unique<ValueExpr>(expr_attr->value));
      free(expr_attr);
    }

    /*
    * 本质上来说如果sql未解析到二元运算表达式，程序会执行本分支
    * 此时Expression为FieldExpr也就是退化为Field
    */
    else if(expr_attr->type==EXPRTYPE::ATTR){
      RelAttrSqlNode relation_attr = expr_attr->attr;
      std::unique_ptr<AggregateFunction> aggr=nullptr;
      if(relation_attr.sql_type==SqlCalculateType::AGGREGATE){
        if(funcType==1){
          LOG_WARN("aggragate function cannot add with simple attr");
          free(expr_attr);
          return RC::VARIABLE_NOT_VALID;
        }
        aggr = AggregateFunctionFactory::CreateAggregateFunction(relation_attr.function_name);
        funcType=2;
      }else{
        if(funcType==2){
          LOG_WARN("aggragate function cannot add with simple attr");
          free(expr_attr);
          return RC::VARIABLE_NOT_VALID;
        }
        funcType=1;
      }
      if (common::is_blank(relation_attr.relation_name.c_str()) &&
          0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
        RC rc=dealWithWildcard(relation_attr,tables,query_exprs);
        if(rc!=RC::SUCCESS){
          free(expr_attr);
          return rc;
        }
      } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
        const char *table_name = relation_attr.relation_name.c_str();
        const char *field_name = relation_attr.attribute_name.c_str();

        if (0 == strcmp(table_name, "*")) {
          if (0 != strcmp(field_name, "*")) {
            LOG_WARN("invalid field name while table is *. attr=%s", field_name);
            free(expr_attr);
            return RC::SCHEMA_FIELD_MISSING;
          }
          RC rc=dealWithWildcard(relation_attr,tables,query_exprs);
          if(rc!=RC::SUCCESS){
            free(expr_attr);
            return rc;
          }
        } else {
          auto iter = table_map.find(table_name);
          if (iter == table_map.end()) {
            LOG_WARN("no such table in from list: %s", table_name);
            free(expr_attr);
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table *table = iter->second;
          if (0 == strcmp(field_name, "*")) {
            RC rc=dealWithWildcard(relation_attr,table,query_exprs);
            if(rc!=RC::SUCCESS){
              free(expr_attr);
              return rc;
            }
          } else {
            const FieldMeta *field_meta = table->table_meta().field(field_name);
            if (nullptr == field_meta) {
              LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
              free(expr_attr);
              return RC::SCHEMA_FIELD_MISSING;
            }
            query_exprs.push_back(std::make_unique<FieldExpr>(
              Field(table, field_meta),relation_attr.function_name,relation_attr.param,aggr));
          }
        }
      } else {
        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
          free(expr_attr);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = tables[0];
        const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
          free(expr_attr);
          return RC::SCHEMA_FIELD_MISSING;
        }
        query_exprs.push_back(std::make_unique<FieldExpr>(
          Field(table, field_meta),relation_attr.function_name,relation_attr.param,aggr));
      }
      free(expr_attr);
    }

    /*
    * 表达式的内容为运算表达式
    * 运算表达式的情况也需要验证字段名称的存在性，传默认表为第一张
    * 一旦表数量多于一张，应保证relation_name对于任意attr是存在的
    */ 
    else if(expr_attr->type==EXPRTYPE::EXPR){
      RC rc=RC::SUCCESS;
      query_exprs.push_back(makeArthExpr(expr_attr,table_map,funcType,rc));
      if(rc!=RC::SUCCESS){
        return rc;
      }
    }
    else{
      // 永远不应该到达，程序流向此处说明前端解析错误
      LOG_ERROR("ExpressionSqlNode resolve error, program should not get here");
      return RC::INVALID_ARGUMENT;
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_exprs.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->exprs_.swap(query_exprs);
  select_stmt->names_.swap(names);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->joinFlag_=select_sql.joinFlag;
  select_stmt->exprState_=funcType;
  stmt = select_stmt;
  return RC::SUCCESS;
}
