#include "APICommonLog.h"

//#define WRITE_LOCAL_ERROR_LOG(strLog) \
//do \
//{ \
//	std::string tmp_strLogs; \
//	char tmp_szLogHead[MAX_LOG_HEADER] = { 0 }; \
//	std::string tmp_strFunName(__FUNCTION__); \
//	sprintf(tmp_szLogHead, "[%s:%d] ", tmp_strFunName.c_str(), __LINE__); \
//	tmp_strLogs.append(tmp_szLogHead); \
//	tmp_strLogs.append(strLog); \
//	CDvrsWriteLogFile::GetInstance()->Write(tmp_strLogs, (CDvrsWriteLogFile::ELogLevel)CCommonLog::LOG_ERROR); \
//}while (0);


/************************************************************************/
/*                                                                      */
/************************************************************************/
void CAPICommonLog::SetLogCallback(MRPS::MRPS_Log_Evt pLogCallback)
{
	m_pLogCallback = (unsigned long)pLogCallback;
}

void CAPICommonLog::Write(const std::string& strSystemId, const std::string& strModule, const std::string& strLog, ELogLevel eLevel /* = LOG_INFO */)
{
	if (m_pLogCallback != 0)
	{
		MRPS::Param_Log_Evt logEvt;
		logEvt.strSystemId = strSystemId;
		logEvt.strModule = strModule;
		logEvt.level = (MRPS::RsApi_LogLevel)eLevel;
		logEvt.strLogInfo = strLog;
		((MRPS::MRPS_Log_Evt)(unsigned long)(m_pLogCallback))(logEvt);
	}
}

CAPICommonLog* CAPICommonLog::GetInstance()
{
	static CAPICommonLog apiLog;
	return &apiLog;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CAPICommonLog::CAPICommonLog()
{	
	m_pLogCallback = 0;
}

CAPICommonLog::~CAPICommonLog()
{

}

