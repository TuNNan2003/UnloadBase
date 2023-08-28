/* 
 * Copyright (c) 2023 UnloadBase and/or its affiliates. All rights reserved.
 */

#pragma once

#define SEPERATOR '-'

#define DEFAULT_NULL "NULLDATA"

#include <string>

class Date{
    private:
        char year[5];
        char month[3];
        char day[3];
        bool nullFlag=false;
        bool parseDate(char* ptr, char* segment,int len,const char* errorInfo);
    public:
        Date();
        Date(const char* date_);
        void setNullData();
        std::string toString();
        
};