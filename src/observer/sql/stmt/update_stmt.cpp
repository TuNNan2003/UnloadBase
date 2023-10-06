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

#include "sql/stmt/update_stmt.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"

UpdateStmt::UpdateStmt(Table *table, Value values, std::string attribute, FilterStmt *filter_stmt)
    : table_(table), values_(values), attribute_(attribute), filter_stmt_(filter_stmt)
{}

UpdateStmt::~UpdateStmt(){
  if(nullptr != filter_stmt_){
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update_sql, Stmt *&stmt)
{
  if(nullptr == db){
    LOG_WARN("invalud argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  Table* table = db->find_table(update_sql.relation_name.c_str());
  if(nullptr == table){
    LOG_WARN("no such table. db = %s, table_name=%s", db->name(), update_sql.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(update_sql.relation_name, table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(
    db, table, &table_map,  update_sql.conditions.data(), static_cast<int>(update_sql.conditions.size()), filter_stmt);
  if(rc != RC::SUCCESS){
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new UpdateStmt(table, update_sql.value, update_sql.attribute_name, filter_stmt);
  return rc;
}
