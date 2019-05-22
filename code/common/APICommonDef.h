#ifndef __APICommonDef_H__
#define __APICommonDef_H__

#include <string>
#include <atomic>
#include <locale>
#include <map>
#include <vector>
#include <codecvt>
#include "IAPIObject.h"
#include "APICommonLog.h"

extern std::string g_strSystemId;
extern std::string g_strApiModuleName;

namespace MRPS
{
	

	extern void gfunc_WstringToUtf8String(const std::wstring& wstrTmp, std::string& strTmp);
	extern void gfunc_Utf8StringToWstring(const std::string& strTmp, std::wstring& wstrTmp);
	extern void gfunc_WstringToMbString(const std::wstring& wstrTmp, std::string& strTmp);
	extern void gfunc_MbStringToWstring(const std::string& strTmp, std::wstring& wstrTmp);
	extern void gfunc_Utf8StringToMbString(const std::string& strUtf8, std::string& strMb);
	extern void gfunc_MbStringToUtf8String(const std::string& strMb, std::string& strUtf8);

	extern std::wstring gfunc_MbString2Wstring(const std::string& strTmp);
	extern std::string  gfunc_Wstring2MbString(const std::wstring& wstrTmp);
	extern std::string  gfunc_Wstring2Utf8String(const std::wstring& wstrTmp);
	extern std::wstring gfunc_Utf8String2Wstring(const std::string& strTmp);

#define LOG_BUFFER_SIZE 2048


#define WRITE_FATAL_LOG(strLog) API_WRITE_FATAL_LOG(g_strSystemId, g_strApiModuleName, strLog)
#define WRITE_ERROR_LOG(strLog) API_WRITE_ERROR_LOG(g_strSystemId, g_strApiModuleName, strLog)
#define WRITE_WARN_LOG(strLog)  API_WRITE_WARN_LOG(g_strSystemId, g_strApiModuleName, strLog)
#define WRITE_INFO_LOG(strLog)  API_WRITE_INFO_LOG(g_strSystemId, g_strApiModuleName, strLog)
#define WRITE_DEBUG_LOG(strLog) API_WRITE_DEBUG_LOG(g_strSystemId, g_strApiModuleName, strLog)



}

#endif