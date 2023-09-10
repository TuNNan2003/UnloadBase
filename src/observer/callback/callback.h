#include "sql/parser/parse.h"
#include "common/rc.h"
#include "session/session.h"

class SQLStageEvent;
class ParsedSqlNode;

class CallBack
{
public:
  void static callback(SQLStageEvent *sql_event,SessionEvent *event);
};