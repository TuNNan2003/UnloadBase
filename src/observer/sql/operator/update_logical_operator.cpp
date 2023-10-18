#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table* table, std::vector<SetVariableSqlNode> set_node): table_(table), set_node_(set_node)
{}