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
*   Created by wuhuua on 2023/10/21
*/

#include "null_table.h"

#include <string.h>

int NullTable::calcTableSize(int attrNum){
    return attrNum%8==0?attrNum/8:attrNum/8+1;
}

NullTable::NullTable(const char* tableData,int attrNum){
    tableSize_=calcTableSize(attrNum);
    tableData_=new char[tableSize_];
    memcpy(tableData_,tableData,tableSize_);
}

NullTable::NullTable(int attrNum){
    tableSize_=calcTableSize(attrNum);
    tableData_=new char[tableSize_];
    memset(tableData_,0,tableSize_);
}

NullTable::~NullTable(){
    if(this->tableData_!=nullptr){
        delete[] tableData_;
    }
}

const char* NullTable::toBytes(){
    return tableData_;
}

int NullTable::tableSize(){
    return tableSize_;
}

void NullTable::setNull(int index){
    tableData_[index/8]|=1<<(index%8);
}

bool NullTable::isNull(int index){
    return tableData_[index/8]&(1<<(index%8));
}