#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table* table, Value value, std::string attribute): table_(table), value_(value), attribute_(attribute)
{}