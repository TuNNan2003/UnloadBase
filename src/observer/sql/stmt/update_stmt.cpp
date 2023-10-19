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

UpdateStmt::UpdateStmt(Table *table, std::vector<SetVariableSqlNode> setnode, FilterStmt *filter_stmt)
    : table_(table), setnode_(setnode), filter_stmt_(filter_stmt)
{
}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_)
  {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update_sql, Stmt *&stmt)
{
  if (nullptr == db)
  {
    LOG_WARN("invalud argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  Table *table = db->find_table(update_sql.relation_name.c_str());
  if (nullptr == table)
  {
    LOG_WARN("no such table. db = %s, table_name=%s", db->name(), update_sql.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(update_sql.relation_name, table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(
      db, table, &table_map, update_sql.conditions.data(), static_cast<int>(update_sql.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS)
  {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new UpdateStmt(table, update_sql.setnode, filter_stmt);
  return rc;
}

RC UpdateStmt::check(Table *table)
{
  TableMeta table_meta = table->table_meta();
  std::vector<FieldMeta> field = *(table_meta.field_metas());
  std::vector<std::string> attributes;
  for (int i = 0; i < field.size(); i++)
  {
    std::string s = std::string(field[i].name());
    attributes.emplace_back(s);
  }
  std::vector<SetVariableSqlNode> setnode = this->setnode();
  for (int i = 0; i < setnode.size(); i++)
  {
    int find = 0;
    for (int j = 0; j < attributes.size(); j++)
    {
      if (strcmp(setnode[i].name.c_str(), attributes[j].c_str()) == 0)
      {
        find = 1;
      }
    }
    if(find != 1){
      return RC::INTERNAL;
    }
  }
  return RC::SUCCESS;
}
