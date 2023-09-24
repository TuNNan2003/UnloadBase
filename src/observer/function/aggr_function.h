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




class AggregateFunction{
public:
    AggregateFunction() : begin_flag(true) {}
    virtual ~AggregateFunction() { }
    virtual void calc(Value value, Value& res) {return; }
protected:
    bool begin_flag;
};

class MaxAggregateFunction : public AggregateFunction{
public:
    MaxAggregateFunction() : AggregateFunction() {}
    void calc(Value value, Value& res); 
};

class MinAggregateFunction : public AggregateFunction{
public:
    MinAggregateFunction() : AggregateFunction() {}
    void calc(Value value, Value& res);
};

class AvgAggregateFunction : public AggregateFunction{
public:
    AvgAggregateFunction() : AggregateFunction() {}
    void calc(Value value, Value& res);
    void average(Value& res);
private:
    int count;
};

class SumAggregateFunction : public AggregateFunction{
public:
    SumAggregateFunction() : AggregateFunction() {}
    void calc(Value value, Value& res);
};

class CountAggregateFunction : public AggregateFunction{
public:
    CountAggregateFunction() : AggregateFunction() {}
    void calc(Value value, Value& res);
};

class AggregateFunctionFactory{
public: 
    AggregateFunctionFactory() {}
    AggregateFunction* CreateAggregateFunction(FunctionName func);
};