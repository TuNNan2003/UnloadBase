#pragma once
#include "common/rc.h"
#include "event/sql_event.h"

/**
 * @brief 删除表的执行器
 * @ingroup Executor
*/
class DropTableExecutor
{
public: 
    DropTableExecutor() = default;
    virtual ~DropTableExecutor() = default;

    RC execute(SQLStageEvent* sql_event);
};