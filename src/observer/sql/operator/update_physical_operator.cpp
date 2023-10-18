#include "common/log/log.h"
#include "sql/operator/update_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/update_stmt.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
    if(children_.empty()){
        return RC::SUCCESS;
    }

    std::unique_ptr<PhysicalOperator> &child = children_[0];
    RC rc = child->open(trx);
    if(rc != RC::SUCCESS){
        LOG_WARN("failed to open child operator: %s", strrc(rc));
        return rc;
    }

    trx_ = trx;

    return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
    RC rc = RC::SUCCESS;
    if(children_.empty()){
        return RC::RECORD_EOF;
    }
    
    PhysicalOperator *child = children_[0].get();
    bool index_find = false;
    int index = -1;
    while(RC::SUCCESS == (rc = child->next())){
        Tuple *tuple = child->current_tuple();
        if(nullptr == tuple){
            LOG_WARN("failed to get current recode %s", strrc(rc));
            return rc;
        }

        RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
        if(!index_find){
            index = row_tuple->locate_index(attribute_);
            if(index == -1){
                LOG_DEBUG("Error attribute name %s", attribute_.c_str());
                return RC::NOTFOUND;
            }
            index_find = true;
        }
        rc = trx_->update_record(table_, row_tuple, value_, index);
        if(rc != RC::SUCCESS){
            LOG_WARN("failed to update record: %s", strrc(rc));
            return rc;
        }
    }

    return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close(){
    if(!children_.empty()){
        children_[0]->close();
    }
    return RC::SUCCESS;
}