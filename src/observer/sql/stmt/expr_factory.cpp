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

#include "expr_factory.h"
#include "common/lang/string.h"


ArithmeticExpr::Type getArthType(CalcOp op){
  switch(op){
    case CalcOp::ADD:{
      return ArithmeticExpr::Type::ADD;
    }break;
    case CalcOp::SUB:{
      return ArithmeticExpr::Type::SUB;
    }break;
    case CalcOp::MUL:{
      return ArithmeticExpr::Type::MUL;
    }break;
    case CalcOp::DIV:{
      return ArithmeticExpr::Type::DIV;
    }break;
    default:{
      return ArithmeticExpr::Type::NEGATIVE;
    }
  }
}

std::unique_ptr<Expression> makeArthExpr(
  ExpressionSqlNode* expr_attr,
  const std::unordered_map<std::string, Table *> &table_map,
  int &funcType,
  RC &rc){
  if(expr_attr->type==EXPRTYPE::EXPR){
    std::unique_ptr<ArithmeticExpr> arthExpr=std::make_unique<ArithmeticExpr>(
      getArthType(expr_attr->calc),
      makeArthExpr(expr_attr->left,table_map,funcType,rc),
      makeArthExpr(expr_attr->right,table_map,funcType,rc)
    );
    free(expr_attr);
    return arthExpr;
  }
  else if(expr_attr->type==EXPRTYPE::ATTR){
    RelAttrSqlNode relation_attr = expr_attr->attr;
    std::unique_ptr<AggregateFunction> aggr;
    if(relation_attr.sql_type==SqlCalculateType::AGGREGATE){
      if(funcType==1){
        LOG_WARN("aggragate function cannot add with simple attr");
        rc = RC::VARIABLE_NOT_VALID;
        free(expr_attr);
        return std::make_unique<ValueExpr>(Value(0));
      }
      aggr = AggregateFunctionFactory::CreateAggregateFunction(relation_attr.function_name);
      funcType=2;
    }else{
      if(funcType==2){
        LOG_WARN("aggragate function cannot add with simple attr");
        rc=RC::VARIABLE_NOT_VALID;
        free(expr_attr);
        return std::make_unique<ValueExpr>(Value(0));
      }
      funcType=1;
    }

    const Table* default_table = table_map.begin()->second;

    std::unique_ptr<FieldExpr> fieldExpr;
    // 没有表名且只有一张表则使用默认表名
    if(relation_attr.relation_name.empty()){
      if(table_map.size()>1){
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        rc=RC::SCHEMA_FIELD_MISSING;
        free(expr_attr);
        return std::make_unique<ValueExpr>(Value(0));
      }
      const FieldMeta *field_meta;
      // 对于count(*)这种情况，选择任意一个字段填入即可
      if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")){
        if(relation_attr.function_name==FunctionName::AGGREGATE_COUNT){
          const TableMeta &table_meta = default_table->table_meta();
          field_meta = table_meta.field(table_meta.sys_field_num());
        }else{
          rc=RC::INVALID_ARGUMENT;
          free(expr_attr);
          return std::make_unique<ValueExpr>(Value(0));
        }
      }else{
        field_meta = default_table->table_meta().field(relation_attr.attribute_name.c_str());
      }
      if (nullptr == field_meta) {
        LOG_WARN("no such field, in expr resolving field=%s.%s", default_table->name(), relation_attr.attribute_name.c_str());
        rc=RC::SCHEMA_FIELD_MISSING;
        free(expr_attr);
        return std::make_unique<ValueExpr>(Value(0));
      }
      fieldExpr=std::make_unique<FieldExpr>(
        Field(default_table,field_meta),relation_attr.function_name,relation_attr.param,aggr);
    }
    // 查询不存在的表名默认返回一个空Value TODO:返回NULL最合适
    else if(table_map.find(relation_attr.relation_name)==table_map.end()){
      LOG_WARN("no such table. table_name=%s", relation_attr.relation_name.c_str());
      rc=RC::SCHEMA_FIELD_MISSING;
      free(expr_attr);
      return std::make_unique<ValueExpr>(Value(0));
    }
    // 查询存在的表名则正常查询
    else{
      const Table* table = table_map.at(relation_attr.relation_name);
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field, in expr resolving field=%s.%s", default_table->name(), relation_attr.attribute_name.c_str());
        rc=RC::SCHEMA_FIELD_MISSING;
        free(expr_attr);
        return std::make_unique<ValueExpr>(Value(0));
      }
      fieldExpr=std::make_unique<FieldExpr>(
        Field(table,field_meta),relation_attr.function_name,relation_attr.param);
    }
    free(expr_attr);
    return fieldExpr;
  }
  else if(expr_attr->type==EXPRTYPE::VAL){
    std::unique_ptr<ValueExpr> valExpr=std::make_unique<ValueExpr>(expr_attr->value);
    free(expr_attr);
    return valExpr;
  }
  else{
    // 永远不应该到达，程序流向此处说明前端解析错误
    LOG_ERROR("ExpressionSqlNode resolve error, program should not get here");
    return std::make_unique<ValueExpr>(Value((int)0));
  }
}