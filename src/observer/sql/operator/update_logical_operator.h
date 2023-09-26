#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子 用于执行update语句
 * @ingroup LogicalOperator
*/
class UpdateLogicalOperator : public LogicalOperator
{
public:
    UpdateLogicalOperator(Table* table, Value value, std::string attribute);
    virtual ~UpdateLogicalOperator() = default;

    LogicalOperatorType type() const override
    {
        return LogicalOperatorType::UPDATE;
    }

    Table *table() const {return table_;}
    Value value() const {return value_;}
    std::string attribute() const {return attribute_;}

private:
    Table *table_ = nullptr;
    std::string attribute_;
    Value value_;
};