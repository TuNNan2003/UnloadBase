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
*   Created by wuhuua on 2023/10/4
*/

#include "algorithm.h"

#define ANYCHAR '_'
#define ANYSTR '%'
#define MATCHBYKMP

#ifdef MATCHBYKMP
int KMPSearch(const char* text, const char* pattern, int patternLength) {
    int* lps=new int[patternLength];
    lps[0]=0;
    int i = 0, j = 0, len=0;
    while (text[i]!='\0') {
        if (pattern[j] == text[i]||pattern[j]==ANYCHAR) {
            if(j>0){
                while(len>0&&text[i] != pattern[len]&& pattern[len]!=ANYCHAR){
                    len = lps[len - 1];
                }
                if(text[i] == pattern[len]|| pattern[len]==ANYCHAR){
                    len++;
                }
                lps[j] = len;
            }
            j++;
            i++;
        }

        if (j == patternLength) {
            delete[] lps;
            return i - j;
        }

        if (text[i]!='\0' && pattern[j] != text[i]&&pattern[j]!=ANYCHAR) {
            if (j != 0){
                j = lps[j - 1];
                len=j==0?0:lps[j-1];
            }
            else
                i++;
        }
    }
    delete[] lps;
    return -1;
}
bool matchByKMP(std::string s,std::string p){
    int pos=-1;
    int len=0;
    const char* str_ch=s.c_str();
    const char* format_ch=p.c_str();
    const char* ptr;

    while(*format_ch!='\0'&&*str_ch!='\0'&&*format_ch!=ANYSTR&&*str_ch!=ANYSTR){
        if(*format_ch==*str_ch||*format_ch==ANYCHAR){
            format_ch++;
            str_ch++;
        }
        else{
            return false;
        }
    }
    if(*format_ch=='\0'){
        return *str_ch=='\0';
    }

    while(*format_ch!='\0'){
        while(*format_ch!='\0'&&(*format_ch==ANYSTR||*format_ch==ANYCHAR)){
            if(*format_ch==ANYCHAR){
                if(*str_ch=='\0'){return false;}
                str_ch++;
            }
            format_ch++;
        }
        if(*format_ch!='\0'){
            ptr=format_ch;
            while(*ptr!='\0'&&*ptr!=ANYSTR){ptr++;}
            len=ptr-format_ch;
            if(*ptr!='\0'){
                pos=KMPSearch(str_ch,format_ch,len);
                if(pos==-1){return false;}
                str_ch+=len+pos;
                format_ch=ptr;
            }else{
                if(!s.empty()){
                    ptr=&s.back();
                }
                else{
                    return false;
                }
                if(ptr-str_ch<len-1){return false;}
                str_ch=ptr-len+1;
                return KMPSearch(str_ch,format_ch,len)==0;
            }
        }
        
    }
    return true;
}
#endif

#ifdef MATCHBYDP
bool matchByDP(std::string s,std::string p){
    int m = s.length();
    int n = p.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    dp[0][0] = 1;
    for(int i = 1; i <= n; ++i){
        if(p[i - 1] == ANYSTR){
        dp[0][i] = 1;
        }else{
        break;
        }
    }
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= n; ++j){
        if(p[j - 1] == ANYSTR) {
            dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
        }
        else if(p[j - 1] == ANYCHAR || s[i - 1] == p[j - 1]){
            dp[i][j] = dp[i - 1][j - 1];
        }
        }
    }
    return dp[m][n];
}
#endif

bool Algorithm::wildcardMatching(std::string s,std::string p){
    #ifdef MATCHBYKMP
        return matchByKMP(s,p);
    #endif
    #ifdef MATCHBYDP
        return matchByDP(s,p);
    #endif
}
