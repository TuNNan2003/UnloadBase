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

#include <iostream>

#include "var_record.h"
#include "common/lang/string.h"
#include "common/log/log.h"

std::string VarRecordFileHandler::getFileName(std::string attr_name,std::string table_name){
    return table_name+VARFILESEP+attr_name+VARFILEEND;
}


std::string VarRecordFileHandler::getFilePathWithName(std::string attr_name,std::string table_name,const char *base_dir){
    return std::string(base_dir)+'/'+getFileName(attr_name,table_name);
}


VarRecordFileHandler::VarRecordFileHandler(std::string attr_name,std::string table_name,const char *base_dir){
    this->fullName=getFilePathWithName(attr_name,table_name,base_dir);
}

VarRecordFileHandler::~VarRecordFileHandler(){
    if(this->data!=nullptr){
        delete[] this->data;
    }
}

RC VarRecordFileHandler::initFile(){
    if(this->fullName.empty()){
        return RC::EMPTY;
    }
    std::ofstream file(this->fullName);
    if (file.is_open()) {
        file.close();
        return RC::SUCCESS;
    } 
    return RC::FILE_NOT_EXIST;
}

RC VarRecordFileHandler::transVarAddress(char* file_addr, char* &memory_addr){
    if(this->data==nullptr){
        if(this->fullName.empty()){
            return RC::EMPTY;
        }
        std::ifstream file;
        file.open(this->fullName, std::ios_base::in | std::ios_base::binary);
        if (file.is_open()) {
            file.seekg(0, std::ios::end);
            std::streampos fileSize = file.tellg();
            file.seekg(0, std::ios::beg);
            this->data = new char[(unsigned long long)fileSize];
            file.read(this->data, fileSize);
            file.close();
        }
        else {
            return RC::FILE_NOT_OPENED;
        }
    }
    memory_addr=(char*)((unsigned long long)this->data+(unsigned long long)file_addr);
    return RC::SUCCESS;
}

RC VarRecordFileHandler::insert(unsigned long long &address,const char* insert_data,int length){
    if(length>VARMAXLEN){
        return RC::IOERR_TOO_LONG;
    }
    if(this->fullName.empty()){
        return RC::EMPTY;
    }
    std::ofstream file(this->fullName, std::ios::in | std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file.seekp(0, std::ios::end);
        std::streampos endPosition = file.tellp();
        address = static_cast<unsigned long long>(endPosition);
        file.write(insert_data, length);
        file.close();
        // 重置内存
        this->flush();
    } else {
        return RC::FILE_NOT_OPENED;
    }
    return RC::SUCCESS;
}

void VarRecordFileHandler::flush(){
    if(this->data!=nullptr){
        delete[] this->data;
    }
    this->data=nullptr;
}

RC VarRecordFileHandler::checkFile(){
    if(this->fullName.empty()){
        return RC::EMPTY;
    }
    std::ofstream file(this->fullName, std::ios::in | std::ios::binary);
    if(file.is_open()){
        return RC::FILE_EXIST;
    }
    return RC::FILE_NOT_EXIST;
}

RC VarRecordFileHandler::removeFile(){
    if(this->fullName.empty()){
        return RC::EMPTY;
    }
    if(unlink(this->fullName.c_str()) != 0){
        return RC::FILE_NOT_REMOVED;
    }
    return RC::SUCCESS;
}

RC VarRecordFileHandler::update(unsigned long long &address,const char* tgt_data,int srcLen,int tgtLen){
    if(this->fullName.empty()){
        return RC::EMPTY;
    }
    std::ofstream file(this->fullName, std::ios::in | std::ios::out | std::ios::binary);
    if (file.is_open()) {
        // 插入长度小于原本长度，在原本位置修改，同时更新懒加载
        if(srcLen>=tgtLen){
            file.seekp(address);
            if(this->data!=nullptr){
                memcpy(this->data+address,tgt_data,tgtLen);
            }
        }
        // 插入长度大于原本长度，在新的位置修改，重置内存
        else{
            file.seekp(0, std::ios::end);
            std::streampos endPosition = file.tellp();
            address = static_cast<unsigned long long>(endPosition);
            this->flush();
        }
        file.write(tgt_data,tgtLen);
        file.close();
    } else {
        return RC::FILE_NOT_OPENED;
    }
    return RC::SUCCESS;
}



unsigned long long varLenAttr::parseAddr(varLenPointer pointer){
    unsigned long long mask = std::numeric_limits<unsigned long long>::max() >> VAR_LENGTH_BITNUM;
    return pointer&mask;
}

int varLenAttr::parseLen(varLenPointer pointer){
    int addressBitNum=getBitNumULL()-VAR_LENGTH_BITNUM;
    return static_cast<int>((pointer>>addressBitNum)&0xFFFF);
}

varLenPointer varLenAttr::makeVarLenPointer(int length,unsigned long long address){
    varLenPointer pointer;
    pointer=parseAddr(address);
    unsigned long long length_=0ULL;
    length_+=length;
    pointer+=length_<<(getBitNumULL()-VAR_LENGTH_BITNUM);
    return pointer;
}

int varLenAttr::getBitNumULL(){
    return sizeof(varLenPointer)*8;
}

int varLenAttr::getByteNumULL(){
    return sizeof(varLenPointer);
}
