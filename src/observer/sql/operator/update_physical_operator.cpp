#include "common/log/log.h"
#include "sql/operator/update_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/update_stmt.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
    if (children_.empty())
    {
        return RC::SUCCESS;
    }

    std::unique_ptr<PhysicalOperator> &child = children_[0];
    RC rc = child->open(trx);
    if (rc != RC::SUCCESS)
    {
        LOG_WARN("failed to open child operator: %s", strrc(rc));
        return rc;
    }

    trx_ = trx;

    return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
    RC rc = RC::SUCCESS;
    if (children_.empty())
    {
        return RC::RECORD_EOF;
    }

    PhysicalOperator *child = children_[0].get();
    bool index_find = false;
    std::vector<int> index;
    std::vector<Value> value;
    while (RC::SUCCESS == (rc = child->next()))
    {
        Tuple *tuple = child->current_tuple();
        if (nullptr == tuple)
        {
            LOG_WARN("failed to get current recode %s", strrc(rc));
            return rc;
        }

        RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
        if (!index_find)
        {
            rc = convert(&value, &index, row_tuple);
            if (rc != RC::SUCCESS)
            {
                return rc;
            }
            index_find = true;
        }
        rc = update(table_, row_tuple, value, index);
        if (rc != RC::SUCCESS)
        {
            LOG_WARN("failed to update record: %s", strrc(rc));
            return rc;
        }
    }

    return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
    if (!children_.empty())
    {
        children_[0]->close();
    }
    return RC::SUCCESS;
}

RC UpdatePhysicalOperator::convert(std::vector<Value> *value, std::vector<int> *index, RowTuple *row_tuple)
{
    for (int i = 0; i < set_node_.size(); i++)
    {
        value->emplace_back(set_node_[i].value);
        int index_i = row_tuple->locate_index(set_node_[i].name);
        if (index_i == -1)
        {
            LOG_ERROR("Error attribute name %s", set_node_[i].name);
            return RC::NOTFOUND;
        }
        index->emplace_back(index_i);
    }
    return RC::SUCCESS;
}

RC UpdatePhysicalOperator::update(Table *table, RowTuple *row_tuple, std::vector<Value> value, std::vector<int> index)
{
    assert(value.size() == index.size());
    for (int i = 0; i < value.size(); i++)
    {
        RC rc = trx_->update_record(table, row_tuple, value[i], index[i]);
        if (rc != RC::SUCCESS)
        {
            LOG_WARN("failed to update record: %s", strrc(rc));
            return rc;
        }
    }
    return RC::SUCCESS; 
}