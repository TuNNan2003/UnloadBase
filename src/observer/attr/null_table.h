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

#pragma once
/*
*   Null表是分组倒存的结构，每8个字段为一组，索引靠前的靠字节右
*/
class NullTable{
    public:
        // 复制record中的数据，传入attrNum为可见字段个数
        NullTable(const char* tableData,int attrNum);
        // 初始化NullTable
        NullTable(int attrNum);
        ~NullTable();
        const char* toBytes();
        int tableSize();
        // 传入可见字段在表中索引(不包含系统表)，设置为空
        void setNull(int index);
        // 传入可见字段在表中索引(不包含系统表)，获取为空
        bool isNull(int index);
        // 根据字段个数计算null表大小
        static int calcTableSize(int attrNum);
    private:
        int tableSize_;
        char* tableData_=nullptr;
};