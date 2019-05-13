#include "CommonLog.h"
#include "LogWriter.h"

const unsigned long  ThreadId_WriteLog = 33333;
const unsigned long  ThreadId_WriteCallbackLog = 33334;
const unsigned long  ThreadId_WriteMasterStandbyLog = 33335;

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
void CCommonLog::Write(std::string strLog, ELogLevel eLevel /* = LOG_INFO */)
{
	//m_threadProcLog.HSAddMessage(this, ThreadId_WriteLog, eLevel, 0, 0, strLog);
	DoWrite(strLog, eLevel);
}

void CCommonLog::LibApiWrite(std::string strLog, ELogLevel eLevel)
{
	//m_threadProcLog.HSAddMessage(this, ThreadId_WriteCallbackLog, eLevel, 0, 0, strLog);
	LibApiDoWrite(strLog, eLevel);
}

void CCommonLog::MasterStandbyWrite(std::string strLog, ELogLevel eLevel)
{
	//m_threadProcLog.HSAddMessage(this, ThreadId_WriteMasterStandbyLog, eLevel, 0, 0, strLog);
	MasterStandbyDoWrite(strLog, eLevel);
}

void CCommonLog::DoWrite(std::string strLog, ELogLevel eLevel /*= LOG_INFO*/)
{
	switch (eLevel)
	{
	case LOG_DEBUG:
		LW_Debug(m_strPluginName.c_str(), strLog.c_str());
		break;
	case LOG_INFO:
		LW_Info(m_strPluginName.c_str(), strLog.c_str());
		break;
	case LOG_WARN:
		LW_Warn(m_strPluginName.c_str(), strLog.c_str());
		break;
	case LOG_ERROR:
		LW_Error(m_strPluginName.c_str(), strLog.c_str());
		break;
	case LOG_FATAL:
		LW_System(m_strPluginName.c_str(), strLog.c_str());
		break;
	default:
		break;
	}
}

void CCommonLog::LibApiDoWrite(std::string strLog, ELogLevel eLevel /*= LOG_INFO*/)
{
	switch (eLevel)
	{
	case LOG_DEBUG:
		LW_Debug(m_strLibApiPluginName.c_str(), strLog.c_str());
		break;
	case LOG_INFO:
		LW_Info(m_strLibApiPluginName.c_str(), strLog.c_str());
		break;
	case LOG_WARN:
		LW_Warn(m_strLibApiPluginName.c_str(), strLog.c_str());
		break;
	case LOG_ERROR:
		LW_Error(m_strLibApiPluginName.c_str(), strLog.c_str());
		break;
	case LOG_FATAL:
		LW_System(m_strLibApiPluginName.c_str(), strLog.c_str());
		break;
	default:
		break;
	}
}

void CCommonLog::MasterStandbyDoWrite(std::string strLog, ELogLevel eLevel)
{
	switch (eLevel)
	{
	case LOG_DEBUG:
		LW_Debug(m_strMasterStandbyLibName.c_str(), strLog.c_str());
		break;
	case LOG_INFO:
		LW_Info(m_strMasterStandbyLibName.c_str(), strLog.c_str());
		break;
	case LOG_WARN:
		LW_Warn(m_strMasterStandbyLibName.c_str(), strLog.c_str());
		break;
	case LOG_ERROR:
		LW_Error(m_strMasterStandbyLibName.c_str(), strLog.c_str());
		break;
	case LOG_FATAL:
		LW_System(m_strMasterStandbyLibName.c_str(), strLog.c_str());
		break;
	default:
		break;
	}
}

void CCommonLog::HSGetMessage(CommonThread_data msg_data)
{
	switch (msg_data.msg_id)
	{
		case ThreadId_WriteLog:
		{
			try
			{
				DoWrite(msg_data.str_msg, (ELogLevel)msg_data.lParam);
			}
			catch (...)
			{
			}
		}
			break;
		case ThreadId_WriteCallbackLog:
		{
			try
			{
				LibApiDoWrite(msg_data.str_msg, (ELogLevel)msg_data.lParam);
			}
			catch (...)
			{
			}
		}
			break;
		case ThreadId_WriteMasterStandbyLog:
		{
			try
			{
				MasterStandbyDoWrite(msg_data.str_msg, (ELogLevel)msg_data.lParam);
			}
			catch (...)
			{
			}
		}
			break;
		default:
			break;
	}	
}

CCommonLog* CCommonLog::GetInstance()
{
	static CCommonLog apiLog;
	return &apiLog;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CCommonLog::CCommonLog()
{	
	m_strPluginName = "GatheringPlugin";
	m_strLibApiPluginName = "LIB_API";
	m_strMasterStandbyLibName = "MasterStandby";
}

CCommonLog::~CCommonLog()
{

}

