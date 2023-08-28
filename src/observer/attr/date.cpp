/*
 * Copyright (c) 2023 UnloadBase and/or its affiliates. All rights reserved.
 */

#include "attr/date.h"
#include "common/log/log.h"

Date::Date(){
    this->setNullData();
}

Date::Date(const char *date_)
{
    char *ptr = (char *)date_;
    if (!parseDate(ptr, this->year, 4, "year format error"))
    {
        this->setNullData();
        return;
    }
    if (!parseDate(ptr, this->month, 2, "month format error"))
    {
        this->setNullData();
        return;
    }
    if (!parseDate(ptr, this->day, 2, "day format error"))
    {
        this->setNullData();
        return;
    }
}

bool Date::parseDate(char *ptr, char *segment, int len, const char *errorInfo)
{
    int i = 0;
    while (*ptr == '-')
    {
        ptr++;
    }
    for (i = 0; i < len; i++)
    {
        if (*ptr == '\0' || *ptr == '-')
        {
            segment[i] = '\0';
            break;
        }
        else
        {
            segment[i] = *ptr;
        }
        ptr++;
    }
    if (i == 0)
    {
        LOG_ERROR("Date Parser error: %s", errorInfo);
        return false;
    }
    return true;
}

void Date::setNullData()
{
    this->nullFlag = true;
}

std::string Date::toString()
{
    if (this->nullFlag)
    {
        return DEFAULT_NULL;
    }
    std::string res = std::string();
    char *ptr = &year[0];
    while (*ptr != '\0')
    {
        res.push_back(*ptr);
        ptr++;
    }
    ptr = &month[0];
    while (*ptr != '\0')
    {
        res.push_back(*ptr);
        ptr++;
    }
    ptr = &day[0];
    while (*ptr != '\0')
    {
        res.push_back(*ptr);
        ptr++;
    }
    return res;
}