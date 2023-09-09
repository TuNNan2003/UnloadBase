#pragma once

#include "sql/parser/value.h"

#define DATE_FORMAT_YEAR   'Y'
#define DATE_FORMAT_MONTH  'M'
#define DATE_FORMAT_DAY    'D'
#define DATE_FORMAT_ERROR  "DATEFORMATERROR"


class Function{
    public:
        static int length(const char* str);
        static float round(float num,int mark);
        static const char* date_format(Value date,const char* fmt);
    private:
        static const char* date_format(int year,int day,int month,const char* fmt);
        static char toBiggerCase(char ch);
};