#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子 用于执行update语句
 * @ingroup LogicalOperator
*/
class UpdateLogicalOperator : public LogicalOperator
{
public:
    UpdateLogicalOperator(Table* table, std::vector<SetVariableSqlNode> set_node);
    virtual ~UpdateLogicalOperator() = default;

    LogicalOperatorType type() const override
    {
        return LogicalOperatorType::UPDATE;
    }

    std::vector<SetVariableSqlNode> SetNode() const{return set_node_; }
    Table* GetTable() const {return table_;}
private:
    Table *table_ = nullptr;
    std::vector<SetVariableSqlNode> set_node_;
};