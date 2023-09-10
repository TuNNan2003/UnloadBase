#include "callback.h"
#include "event/sql_event.h"
#include "event/session_event.h"

void CallBack::callback(SQLStageEvent *sql_event,SessionEvent *event){
    ParsedSqlNode *sql_node = sql_event->sql_node().get();
    if(sql_node->flag==SCF_SELECT){
        SelectSqlNode select_sql= sql_node->selection;
        event->initNames();
        for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
            const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
            event->addFuncName(relation_attr.function_name);
        }
    }
}