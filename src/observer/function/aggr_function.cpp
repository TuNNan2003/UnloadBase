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

#include "aggr_function.h"

AggregateFunction AggregateFunctionFactory::CreateAggregateFunction(FunctionName func){
    switch (func){
        case FunctionName::AGGREGATE_AVG : {
            return AvgAggregateFunction();
        }break;
        case FunctionName::AGGREGATE_COUNT : {
            return CountAggregateFunction();
        }break;
        case FunctionName::AGGREGATE_MAX : {
            return MaxAggregateFunction();
        }break;
        case FunctionName::AGGREGATE_MIN : {
            return MinAggregateFunction();
        }break;
        case FunctionName::AGGREGATE_SUM : {
            return SumAggregateFunction();
        }break;
        default : {
            return CountAggregateFunction();
        }break;
    }
}

void MaxAggregateFunction::calc(Value value, Value& res){
    if(begin_flag){
        std::swap(res, value);
        begin_flag = false;
    }else{
        if(res.compare(value) <= 0){
            std::swap(res, value);
        }
    }
}

void MinAggregateFunction::calc(Value value, Value& res){
    if(begin_flag){
        std::swap(res, value);
        begin_flag = false;
    }else{
        if(res.compare(value) >= 0){
            std::swap(res, value);
        }
    }
}

void SumAggregateFunction::calc(Value value, Value& res){
    if(begin_flag){
        std::swap(value, res);
        begin_flag = false;
    }else{
        res.add(value);
    }
}

void AvgAggregateFunction::calc(Value value, Value& res){
    if(begin_flag){
        std::swap(res, value);
        count = 1;
        begin_flag = false;
    }else{
        res.add(value);
        count++;
    }
}

void AvgAggregateFunction::set(Value& res){
    if(count != 0){
        res.set_float(res.get_float() / count);
    }
}

void CountAggregateFunction::calc(Value value, Value& res){
    if(begin_flag){
        res.set_int(1);
        begin_flag = false;
    }else{
        res.set_int(res.get_int() + 1);
    }
}