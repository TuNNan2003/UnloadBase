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
// Created by Meiyi
//

#pragma once

#include <stddef.h>
#include <memory>
#include <vector>
#include <string>

#include "sql/parser/value.h"

#include "function/function.h"

#define ATTR_VAL_ERROR 5

class Expression;

struct SubQuerySqlNode;

/**
 * @defgroup SQLParser SQL Parser
 */

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct RelAttrSqlNode
{
  std::string relation_name;             ///< relation name (may be NULL) 表名
  std::string attribute_name;            ///< attribute name              属性名
  FunctionName function_name = NULLFUNC; ///< function name       函数名
  SqlCalculateType sql_type = NULLSql;
  FunctionParams param; ///< callback param              函数参数
  std::string name;            ///< raw expression text         原始表达式字符串
};

/**
 * @brief 描述比较运算符
 * @ingroup SQLParser
 */
enum CompOp
{
  EQUAL_TO,    ///< "="
  LESS_EQUAL,  ///< "<="
  NOT_EQUAL,   ///< "<>"
  LESS_THAN,   ///< "<"
  GREAT_EQUAL, ///< ">="
  GREAT_THAN,  ///< ">"
  LIKE_OP,     ///< "LIKE"
  NOT_LIKE_OP, ///< "NOT LIKE"
  NULL_OP,      ///< "IS NULL"
  NOT_NULL_OP,  ///< "IS NOT NULL"  
  NO_OP
};

enum SubQueryOp
{
  IN_SUB,     ///< in
  NOT_IN,     ///< not in
  EQ_SOME,    ///< = some
  EQ_ALL,     ///< = all
  GREAT_SOME, ///< > some
  GREAT_ALL,  ///< > all
  LESS_SOME,  ///< < some
  LESS_ALL,   ///< < all
  NO_SUB
};

/**
 * @brief 描述二元运算运算符
 * @ingroup SQLParser
 */
enum CalcOp
{
  ADD, ///< "+"
  SUB, ///< "-"
  MUL, ///< "*"
  DIV, ///< "/"
};

/**
 * @brief 递归类型表达式内容枚举
 * @ingroup SQLParser
 */
enum EXPRTYPE
{
  EXPR, ///< 子表达式
  VAL,  ///< 数值
  ATTR, ///< 字段
};

enum class WhereType
{
  Condition,
  SimpleSubQuery,
  NO_Type,
};

/**
 * @brief 表示一个字段表达式
 * @ingroup SQLParser
 * @details 字段表达式应该支持各种类型的表达式
 * 内容与上表示单值的时候应该left与right均为空，否则认为是表达式
 * 下面用枚举的方式来表示
 * ID OP ID
 * ID OP Value
 * Value OP Value
 * Function(ID) OP Function(ID)
 * Function(ID) OP Value
 */
struct ExpressionSqlNode{ 
  Value              value; 
  RelAttrSqlNode     attr;
  EXPRTYPE           type;
  ExpressionSqlNode* left=nullptr;
  ExpressionSqlNode* right=nullptr; 
  CalcOp             calc;
  std::string        name;
};

/**
 * @brief 表示一个条件比较
 * @ingroup SQLParser
 * @details 条件比较就是SQL查询中的 where a>b 这种。
 * 一个条件比较是有两部分组成的，称为左边和右边。
 * 左边和右边理论上都可以是任意的数据，比如是字段（属性，列），也可以是数值常量。
 * 这个结构中记录的仅仅支持字段和值。
 */
struct ConditionSqlNode
{
  ExpressionSqlNode *left;
  CompOp            comp;            ///< comparison operator
  ExpressionSqlNode *right;
  SubQuerySqlNode*  subquery;        ///< subquery 
};



/**
 * @brief 描述一个select语句
 * @ingroup SQLParser
 * @details 一个正常的select语句描述起来比这个要复杂很多，这里做了简化。
 * 一个select语句由三部分组成，分别是select, from, where。
 * select部分表示要查询的字段，from部分表示要查询的表，where部分表示查询的条件。
 * 比如 from 中可以是多个表，也可以是另一个查询语句，这里仅仅支持表，也就是 relations。
 * where 条件 conditions，这里表示使用AND串联起来多个条件。正常的SQL语句会有OR，NOT等，
 * 甚至可以包含复杂的表达式。
 */

struct SelectSqlNode
{
  std::vector<ExpressionSqlNode *> attributes; ///< attributes in select clause
  std::vector<std::string> relations;          ///< 查询的表
  std::vector<ConditionSqlNode> conditions;    ///< 查询条件，使用AND串联起来多个条件
  std::string selectRaw;                       ///< 查询字段原始字符串
  bool joinFlag = false;                       ///< Join flag，用于判断relation中表的关系
};

struct AggregateSqlNode
{
  std::string relation_name;
  int aggregateOP;
  std::string operate_attribute;
};

/**
 * @brief 算术表达式计算的语法树
 * @ingroup SQLParser
 */
struct CalcSqlNode
{
  std::vector<Expression *> expressions; ///< calc clause

  ~CalcSqlNode();
};

/**
 * @brief 描述一个insert语句
 * @ingroup SQLParser
 * @details 于Selects类似，也做了很多简化
 */
struct InsertSqlNode
{
  std::string relation_name; ///< Relation to insert into
  std::vector<std::vector<Value>> values; ///< 要插入的值
};

/**
 * @brief 描述一个delete语句
 * @ingroup SQLParser
 */
struct DeleteSqlNode
{
  std::string relation_name; ///< Relation to delete from
  std::vector<ConditionSqlNode> conditions;
};

/**
 * @brief 描述一个属性
 * @ingroup SQLParser
 * @details 属性，或者说字段(column, field)
 * Rel -> Relation
 * Attr -> Attribute
 */
struct AttrInfoSqlNode
{
  AttrType type;    ///< Type of attribute
  std::string name; ///< Attribute name
  int length;          ///< Length of attribute
  bool      nullable;     ///< Nullable of attribute
};

/**
 * @brief 描述一个create table语句
 * @ingroup SQLParser
 * @details 这里也做了很多简化。
 */
struct CreateTableSqlNode
{
  std::string relation_name;               ///< Relation name
  std::vector<AttrInfoSqlNode> attr_infos; ///< attributes
};

/**
 * @brief 描述一个drop table语句
 * @ingroup SQLParser
 */
struct DropTableSqlNode
{
  std::string relation_name; ///< 要删除的表名
};

/**
 * @brief 描述一个create index语句
 * @ingroup SQLParser
 * @details 创建索引时，需要指定索引名，表名，字段名。
 * 正常的SQL语句中，一个索引可能包含了多个字段，这里仅支持一个字段。
 */
struct CreateIndexSqlNode
{
  std::string index_name;                  ///< Index name
  std::string relation_name;               ///< Relation name
  std::vector<std::string> attribute_name; ///< Attribute name
  bool uniqueFlag=false;                    ///< unique flag
};

/**
 * @brief 描述一个drop index语句
 * @ingroup SQLParser
 */
struct DropIndexSqlNode
{
  std::string index_name;    ///< Index name
  std::string relation_name; ///< Relation name
};

/**
 * @brief 描述一个desc table语句
 * @ingroup SQLParser
 * @details desc table 是查询表结构信息的语句
 */
struct DescTableSqlNode
{
  std::string relation_name;
};

/**
 * @brief 描述一个load data语句
 * @ingroup SQLParser
 * @details 从文件导入数据到表中。文件中的每一行就是一条数据，每行的数据类型、字段个数都与表保持一致
 */
struct LoadDataSqlNode
{
  std::string relation_name;
  std::string file_name;
};

/**
 * @brief 设置变量的值
 * @ingroup SQLParser
 * @note 当前还没有查询变量
 */
struct SetVariableSqlNode
{
  std::string name;
  Value value;
};

/**
 * @brief 描述一个update语句
 * @ingroup SQLParser
 */
struct UpdateSqlNode
{
  std::string relation_name; ///< Relation to update
  std::vector<SetVariableSqlNode> setnode;
  std::vector<ConditionSqlNode> conditions;
};

class ParsedSqlNode;

/**
 * @brief 描述一个explain语句
 * @ingroup SQLParser
 * @details 会创建operator的语句，才能用explain输出执行计划。
 * 一个command就是一个语句，比如select语句，insert语句等。
 * 可能改成SqlCommand更合适。
 */
struct ExplainSqlNode
{
  std::unique_ptr<ParsedSqlNode> sql_node;
};

/**
 * @brief 解析SQL语句出现了错误
 * @ingroup SQLParser
 * @details 当前解析时并没有处理错误的行号和列号
 */
struct ErrorSqlNode
{
  std::string error_msg;
  int line;
  int column;
};

/**
 * @brief 表示一个SQL语句的类型
 * @ingroup SQLParser
 */
enum SqlCommandFlag
{
  SCF_ERROR = 0,
  SCF_CALC,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN, ///< 事务开始语句，可以在这里扩展只读事务
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_EXPLAIN,
  SCF_SET_VARIABLE, ///< 设置变量
  SCF_AGGREGATE,
};
/**
 * @brief 表示一个SQL语句
 * @ingroup SQLParser
 */
class ParsedSqlNode
{
public:
  enum SqlCommandFlag flag;
  ErrorSqlNode error;
  CalcSqlNode calc;
  SelectSqlNode selection;
  InsertSqlNode insertion;
  DeleteSqlNode deletion;
  UpdateSqlNode update;
  CreateTableSqlNode create_table;
  DropTableSqlNode drop_table;
  CreateIndexSqlNode create_index;
  DropIndexSqlNode drop_index;
  DescTableSqlNode desc_table;
  LoadDataSqlNode load_data;
  ExplainSqlNode explain;
  SetVariableSqlNode set_variable;
  AggregateSqlNode aggregate;

public:
  ParsedSqlNode();
  explicit ParsedSqlNode(SqlCommandFlag flag);
};

/**
 * @brief 表示语法解析后的数据
 * @ingroup SQLParser
 */
class ParsedSqlResult
{
public:
  void add_sql_node(std::unique_ptr<ParsedSqlNode> sql_node);
  std::vector<std::unique_ptr<ParsedSqlNode>> &sql_nodes()
  {
    return sql_nodes_;
  }

private:
  std::vector<std::unique_ptr<ParsedSqlNode>> sql_nodes_; ///< 这里记录SQL命令。虽然看起来支持多个，但是当前仅处理一个
};

/**
 * @brief 表示一个简单的嵌套子查询
 */
struct SubQuerySqlNode
{
  ExpressionSqlNode *attr;   ///< 子查询要查询的字段
  SubQueryOp queryOP;       ///< 子查询要做的操作符
  ParsedSqlNode* sub_query; ///< 子查询
};