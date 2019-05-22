#include "APICommonDef.h"

namespace MRPS
{
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	void gfunc_WstringToUtf8String(const std::wstring& wstrTmp, std::string& strTmp)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> wc2tuf8;
		strTmp = wc2tuf8.to_bytes(wstrTmp);
	}

	void gfunc_Utf8StringToWstring(const std::string& strTmp, std::wstring& wstrTmp)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> wc2tuf8;
		wstrTmp = wc2tuf8.from_bytes(strTmp);
	}

	void gfunc_WstringToMbString(const std::wstring& wstrTmp, std::string& strTmp)
	{
		const char *pLocal = "";
		using wcmb = std::codecvt_byname<wchar_t, char, std::mbstate_t>;
		std::wstring_convert<wcmb> mb2wc(new wcmb(pLocal));
		strTmp = mb2wc.to_bytes(wstrTmp);
	}

	void gfunc_MbStringToWstring(const std::string& strTmp, std::wstring& wstrTmp)
	{
		const char *pLocal = "";
		using wcmb = std::codecvt_byname<wchar_t, char, std::mbstate_t>;
		std::wstring_convert<wcmb> mb2wc(new wcmb(pLocal));
		wstrTmp = mb2wc.from_bytes(strTmp);
	}

	void gfunc_MbStringToUtf8String(const std::string& strMb, std::string& strUtf8)
	{
		std::wstring wstrTmp;
		gfunc_MbStringToWstring(strMb, wstrTmp);
		gfunc_WstringToUtf8String(wstrTmp, strUtf8);
	}

	void gfunc_Utf8StringToMbString(const std::string& strUtf8, std::string& strMb)
	{
		std::wstring wstrTmp;
		gfunc_Utf8StringToWstring(strUtf8, wstrTmp);
		gfunc_WstringToMbString(wstrTmp, strMb);
	}

	std::string gfunc_Wstring2MbString(const std::wstring& wstrTmp)
	{
		std::string strTmp;
		gfunc_WstringToMbString(wstrTmp, strTmp);
		return strTmp;
	}

	std::wstring gfunc_MbString2Wstring(const std::string& strTmp)
	{
		std::wstring wstrTmp;
		gfunc_MbStringToWstring(strTmp, wstrTmp);
		return wstrTmp;
	}

	std::string gfunc_Wstring2Utf8String(const std::wstring& wstrTmp)
	{
		std::string strUtf8;
		gfunc_WstringToUtf8String(wstrTmp, strUtf8);
		return strUtf8;
	}

	std::wstring gfunc_Utf8String2Wstring(const std::string& strTmp)
	{
		std::wstring wstrTmp;
		gfunc_Utf8StringToWstring(strTmp, wstrTmp);
		return wstrTmp;
	}
}

std::string g_strSystemId = "";
