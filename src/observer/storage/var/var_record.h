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
*   Created by wuhuua on 2023/9/25
*/

#pragma once

#include "common/rc.h"
#include <string>
#include <vector>
#include <limits>

#define VARFILESEP '_'
#define VARFILEEND ".data"
#define VARTYPELEN -1
#define VARMAXLEN 65535

/*
*   VarRecordFileHandler本质上是变长数据在内存中存储的代理
*   通过handler来和内存中的数据进行交互
*   VarRecordFileHandler应当对数据具有完全的管理权限
*   由于变长数据在内存中随机存储且只存储一份，外部不应考虑其析构问题
*/
class VarRecordFileHandler{
    private:
        // 存放文件全名
        std::string fullName;
        // 存放指向内存数据的指针
        char* data=nullptr;
        std::string getFileName(std::string attr_name,std::string table_name);
        std::string getFilePathWithName(std::string attr_name,std::string table_name,const char *base_dir);
        // 删除内存中加载的data，并且置data为nullptr
        void flush();
    public:
        RC initFile();
        RC removeFile();
        VarRecordFileHandler(std::string attr_name,std::string table_name,const char *base_dir);
        RC checkFile();
        ~VarRecordFileHandler();
        // 初次转换时懒加载文件内容到内存中
        RC transVarAddress(char* file_addr, char* &memory_addr);
        // 直接插入操作
        RC insert(unsigned long long &address,const char* insert_data,int length);
        //更新操作中更新的数据为src_data，根据新旧长度对比选择追加或修改
        RC update(unsigned long long &address,const char* tgt_data,int srcLen,int tgtLen);
        const char* getFullName(){
            return fullName.c_str();
        }
};



/*
*    定义变长数据在data中以定长为8字节的指针存放，包含长度数据和指针数据
*    |--|------------------|
*     P1        P2
*     P1存放2个字节大小的无符号整型数
*     P2存放6个字节长度的地址指针
*/
typedef unsigned long long varLenPointer;
#define VAR_LENGTH_BITNUM 16

/*
*   变长数据的方法类，提供varLenPointer的一系列转化方法
*/
class varLenAttr{
    public:
        // 从pointer中解析文件指针
        unsigned long long static parseAddr(varLenPointer pointer);
        // 从pointer中解析长度
        int static parseLen(varLenPointer pointer);
        // 获取机器指针比特字长
        int static getBitNumULL();
        // 获取机器指针字长
        int static getByteNumULL();
        // 根据长度和文件指针构造pointer
        varLenPointer static makeVarLenPointer(int length,unsigned long long address);
};