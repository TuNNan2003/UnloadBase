/*
Copyright (c) 2023 UnloadHome and/or its affiliates. All rights reserved.
UnloadBase is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
 */

/*
*   Created by wuhuua on 2023/9/24
*/
#include "sql/parser/value.h"
#include "function.h"

/*
*   聚合函数采用函数式编程的方式，在迭代器中以不保存原始数据的方式计算
*   需要注意的是：
*   1.参数必须一致，第一个参数代表入参，第二个参数是维护的结果，第三个参数是状态
*   2.状态：state=0代表传递第一个参数、state=1代表之后的计算、state=2代表
*   参数传递完毕，需要进行后续回算
*   3.函数需要定义的中间变量可以设置为static，在state=0或state=1的时候清空
*   4.调用getAggrFunc可以获取对应函数名的指针
*/
class AggrFunc{
    public:
        void static (*getAggrFunc(FunctionName name))(Value,Value&,int);
    private:
        void static max(Value value,Value& res,int state);
        void static min(Value value,Value& res,int state);
        void static avg(Value value,Value& res,int state);
        void static sum(Value value,Value& res,int state);
        void static count(Value value,Value& res,int state);
        void static nothing2do(Value value,Value& res,int state);
};