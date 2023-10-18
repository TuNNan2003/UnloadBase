#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"

class Trx;
class UpdateStmt;

/**
 * @brief 物理算子 更新
 * @ingroup PhysicalOperator
*/
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
    UpdatePhysicalOperator(Table *table, std::vector<SetVariableSqlNode> set_node) : table_(table), set_node_(set_node)
    {}

    virtual ~UpdatePhysicalOperator() = default;

    PhysicalOperatorType type() const override
    {
        return PhysicalOperatorType::UPDATE;
    }

    RC open(Trx *trx) override;
    RC next() override;
    RC close() override;
    RC convert(std::vector<Value>* value, std::vector<int>* index, RowTuple* row_tuple);
    RC update(Table *table, RowTuple *row_tuple, std::vector<Value> value, std::vector<int> index);

    Tuple *current_tuple() override
    {
        return nullptr;
    }

private:
    Table *table_ = nullptr;
    std::vector<SetVariableSqlNode> set_node_;
    Trx *trx_ = nullptr;
};