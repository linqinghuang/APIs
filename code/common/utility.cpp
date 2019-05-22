#include "utility.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>


#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#define vsnprintf _vsnprintf
#define snprintf _snprintf
#else
#define _vsnprintf vsnprintf
#endif

void TrimLeft(std::string& str, const char* chars2remove)
{
	if (!str.empty())
	{
		std::string::size_type pos = str.find_first_not_of(chars2remove);
		
		if (pos != std::string::npos)
		{
			str.erase(0,pos);
		}
		else
		{
			str.erase( str.begin() , str.end() ); // make empty
		}
	}
}

void TrimRight(std::string& str, const char* chars2remove)
{
	if (!str.empty())
	{
		std::string::size_type pos = str.find_last_not_of(chars2remove);
		
		if (pos != std::string::npos)
		{
            str.erase(pos+1);
		}
		else
        {
			str.erase( str.begin() , str.end() ); // make empty
        }
	}
}

void Trim(std::string& str, const char* chars2remove)
{
    TrimLeft( str, chars2remove );
    TrimRight( str, chars2remove );
}

char* strdupnew(const char* src)
{
	return strcpy(new char[strlen(src) + 1], src);
}

char* safe_strcpy(char* dest, const char* src, size_t bufsize)
{
	strncpy(dest, src, bufsize);
	dest[bufsize - 1] = 0;
	return dest;
}


std::string int2str(int data)
{
	std::string str;
	char sData[16] = {0};
	sprintf(sData,"%d",data);
    str = sData;
	return str;
}

std::string long2str(long data)
{
	std::string str;
	char sData[16] = {0};
	sprintf(sData,"%ld",data);
    str = sData;
	return str;
}

std::string float2str(float data)
{
	std::string str;
	char sData[32] = {0};
	sprintf(sData,"%10.5f",data);
	str = sData;
	return str;
}

int str2int(std::string str)
{
	
	return atoi(str.c_str());
}

long str2long(std::string str)
{
	return atol(str.c_str());
}

float str2float(std::string str)
{

	return atof(str.c_str());
}

std::string ToLower(std::string str)
{
	int i;
	int iLen = str.length();
	for(i= 0; i< iLen;i++)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}
std::string ToUpper(std::string str)
{
	int i;
	int iLen = str.length();
	for(i= 0; i< iLen;i++)
	{
		str[i] = toupper(str[i]);
	}
	return str;
}

std::string& Replace(std::string& str,std::string sSrcSubStr,std::string sTagSubStr)
{
	
	int iPos;
	int iSrcLen = sSrcSubStr.length();
	int iTagLen = sTagSubStr.length();
	
	iPos = str.find(sSrcSubStr,0);
	while(iPos >=0)
	{
		str.replace(iPos,iSrcLen,sTagSubStr);
		iPos = str.find(sSrcSubStr,iPos + iTagLen);
	}
    return str;	
}

void strprintf(std::string& sOutStr,const char * format,...)
{
    va_list ap;	
 	int iCount = 256;
	char * str;
	str  = (char *)malloc(iCount + 1);
	memset(str,0,iCount + 1);
	
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
    va_start(ap,format);
    int iRet = _vsnprintf(str, iCount, format, ap);
	while(iRet < 0)
	{
		
		iCount *= 2;
                str = (char *)realloc(str,iCount + 1);
		str[iCount] = 0;
		iRet = _vsnprintf(str, iCount, format, ap);
		
	}
	va_end(ap);

#else 
        
	va_start(ap,format);
	int iRet = _vsnprintf(str, iCount + 1, format, ap); 
	va_end(ap);
	if(iRet >= iCount + 1) //空间少了 /*glibc 2.1*/
	{
		
	    iCount = iRet + 1;
            str = (char *)realloc(str,iCount + 1);
            str[iCount] = 0;
            
 	    va_start(ap,format);
	    iRet = _vsnprintf(str, iCount, format, ap);
	    va_end(ap);	

	}
	else if(iRet < 0) //空间少了 /*glibc 2.0*/
	{
	     while(iRet < 0)
	     {
		iCount *= 2;
                str = (char *)realloc(str,iCount + 1);
		str[iCount] = 0;
 	        va_start(ap,format);
	        iRet = _vsnprintf(str, iCount, format, ap);
	        va_end(ap);		     	  
	     }
	     
	     	
	 	
	}
#endif
    sOutStr = str;
    free(str);

    
}

void TrimLeft( std::wstring& str, const wchar_t* chars2remove )
{
	if( !str.empty() )
	{
		std::wstring::size_type pos = str.find_first_not_of( chars2remove );
		if( pos == std::wstring::npos )
			str.erase( str.begin() , str.end() ); // make empty
		else
			str.erase( 0, pos );
	}
}

void TrimRight( std::wstring& str, const wchar_t* chars2remove )
{
	if( !str.empty() )
	{
		std::wstring::size_type pos = str.find_last_not_of( chars2remove );
		if( pos == std::wstring::npos )
			str.erase( str.begin() , str.end() ); // make empty
		else
		{
            str.erase( pos+1 );
		}
	}
}

void Trim( std::wstring& str, const wchar_t* chars2remove )
{
    TrimLeft( str, chars2remove );
    TrimRight( str, chars2remove );
}

bool str2list(std::string str,std::string sep,std::vector<std::string >& strList)
{

	int pos;
	std::string subStr;
	int iSepLen = sep.length();
	if(str.length() == 0)
	{
		return false;

	}
	if(iSepLen == 0)
	{
		return false;
	}

	pos = str.find(sep);
	while (pos >=0)
	{
		if(pos == 0)
		{

			subStr = "";
			strList.push_back(subStr);


		}
		else
		{
			subStr = str.substr(0,pos);
			strList.push_back(subStr);

		}
		str = str.substr(pos + iSepLen,str.length() - pos + iSepLen -1);
		pos = str.find(sep);
	}
	if(str.length() > 0)
		strList.push_back(str);
	return true;

}

