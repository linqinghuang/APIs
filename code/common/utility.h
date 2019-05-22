#ifndef MAILSERV_UTILITY_H
#define MAILSERV_UTILITY_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <list>
#include <vector>
#pragma warning(disable:4996)

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#define strncasecmp strnicmp
#undef _tcsnicmp
#define _tcsnicmp  strnicmp
#define strcasecmp stricmp
#define DIR_DELIM '\\'
#else
#include <limits.h>
#define MAX_PATH PATH_MAX
#define DIR_DELIM '/'
#define _tcsnicmp  strncmp
#endif

void TrimLeft(std::string& str, const char* chars2remove = " \t");
void TrimRight(std::string& str, const char* chars2remove = " \t");
void Trim(std::string& str, const char* chars2remove = " \t");
char* strdupnew(const char* src);
char* safe_strcpy(char* dest, const char* src, size_t bufsize);

std::string int2str(int data);
std::string long2str(long data);
int str2int(std::string str);
long str2long(std::string str);
std::string ToLower(std::string str);
std::string ToUpper(std::string str);
std::string& Replace(std::string& str,std::string sSrcSubStr,std::string sTagSubStr);
void strprintf(std::string& sOutStr,const char * format,...);


void TrimLeft( std::wstring& str, const wchar_t* chars2remove );   // = " \t"
void TrimRight( std::wstring& str, const wchar_t* chars2remove );  // = " \t"
void Trim( std::wstring& str, const wchar_t* chars2remove );       // = " \t"

/** 将有分隔符的字符串变成列表 
* 例如有一用 "|" 作为分隔符的字符串  "abc|def|12|rt", 该函数将把该字符串抓换为
* abc \n
* def \n
* 12  \n
* rt  \n
* 的列表
*
* @param [in] str 要分割的字符串
* @param [in] sep 分隔符
* @param [out] 分割后的数组
*
* @return 
*
* @see 
*/
bool str2list(std::string str,std::string sep,std::vector<std::string >& strList);

#endif