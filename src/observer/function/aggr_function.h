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
#pragma once

#include "sql/parser/value.h"
#include "function.h"
#include "sql/parser/value.h"


/*
*   calc作为迭代器计算函数进行计算并保存中间变量
*   set利用中间变量计算最终的结果，适用于数理统计类型的变量
*/

class AggregateFunction{
public:
    AggregateFunction() : res(AttrType::NULLTYPE) {}
    virtual void calc(Value value) {return; }
    virtual void set(Value& _res){};
protected:
    Value res;
};

class MaxAggregateFunction : public AggregateFunction{
public:
    MaxAggregateFunction() : AggregateFunction() {}
    void calc(Value value); 
    void set(Value& _res){_res=res; return;}
};

class MinAggregateFunction : public AggregateFunction{
public:
    MinAggregateFunction() : AggregateFunction() {}
    void calc(Value value);
    void set(Value& _res){_res=res; return;}
};

class AvgAggregateFunction : public AggregateFunction{
public:
    AvgAggregateFunction() : AggregateFunction() {}
    void calc(Value value);
    void set(Value& res);
private:
    int count=0;
};

class SumAggregateFunction : public AggregateFunction{
public:
    SumAggregateFunction() : AggregateFunction() {}
    void calc(Value value);
    void set(Value& _res){_res=res; return;}
};

class CountAggregateFunction : public AggregateFunction{
public:
    CountAggregateFunction() : AggregateFunction() {}
    void calc(Value value);
    void set(Value& _res){_res.set_int(count); return;}
private:
    int count=0;
};

class AggregateFunctionFactory{
public: 
    AggregateFunctionFactory() {}
    static std::unique_ptr<AggregateFunction> CreateAggregateFunction(FunctionName func);
};