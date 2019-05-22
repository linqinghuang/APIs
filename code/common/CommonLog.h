/**
@Copyright Copyright (C), 2015-2016, Hytera
@file		CommonLog.h
@created	2015/12/23
@brief

@author	xujinghua
*/

#ifndef __TetraApiLog_H__
#define __TetraApiLog_H__


#include "CommonWorkThread.h"
#include "CommonTimer.h"

const unsigned long MAX_LOG_HEADER = 1024;

#define WRITE_COMMON_LOG(level, strLog) \
do \
{ \
	std::string tmp_strLogs; \
	char tmp_szLogHead[MAX_LOG_HEADER] = { 0 }; \
	std::string tmp_strFunName(__FUNCTION__); \
	sprintf(tmp_szLogHead, "[%s:%d] ", tmp_strFunName.c_str(), __LINE__); \
	tmp_strLogs.append(tmp_szLogHead); \
	tmp_strLogs.append(strLog); \
	CCommonLog::GetInstance()->Write(tmp_strLogs, level); \
}while (0);

#define LIBAPI_WRITE_COMMON_LOG(level, strLog) \
do \
{ \
	std::string tmp_strLogs; \
	char tmp_szLogHead[MAX_LOG_HEADER] = { 0 }; \
	std::string tmp_strFunName(__FUNCTION__); \
	sprintf(tmp_szLogHead, "[%s:%d] ", tmp_strFunName.c_str(), __LINE__); \
	tmp_strLogs.append(tmp_szLogHead); \
	tmp_strLogs.append(strLog); \
	CCommonLog::GetInstance()->LibApiWrite(tmp_strLogs, level); \
}while (0);

#define MASTERSTANDBY_WRITE_COMMON_LOG(level, strLog) \
do \
{ \
	std::string tmp_strLogs; \
	char tmp_szLogHead[MAX_LOG_HEADER] = { 0 }; \
	std::string tmp_strFunName(__FUNCTION__); \
	sprintf(tmp_szLogHead, "[%s:%d] ", tmp_strFunName.c_str(), __LINE__); \
	tmp_strLogs.append(tmp_szLogHead); \
	tmp_strLogs.append(strLog); \
	CCommonLog::GetInstance()->MasterStandbyWrite(tmp_strLogs, level); \
}while (0);

#define WRITE_FATAL_LOG(strLog) WRITE_COMMON_LOG(CCommonLog::LOG_FATAL, strLog)
#define WRITE_ERROR_LOG(strLog) WRITE_COMMON_LOG(CCommonLog::LOG_ERROR, strLog)
#define WRITE_WARN_LOG(strLog) WRITE_COMMON_LOG(CCommonLog::LOG_WARN, strLog)
#define WRITE_INFO_LOG(strLog) WRITE_COMMON_LOG(CCommonLog::LOG_INFO, strLog)
#define WRITE_DEBUG_LOG(strLog) WRITE_COMMON_LOG(CCommonLog::LOG_DEBUG, strLog)

#define LIBAPI_WRITE_FATAL_LOG(strLog) LIBAPI_WRITE_COMMON_LOG(CCommonLog::LOG_FATAL, strLog)
#define LIBAPI_WRITE_ERROR_LOG(strLog) LIBAPI_WRITE_COMMON_LOG(CCommonLog::LOG_ERROR, strLog)
#define LIBAPI_WRITE_WARN_LOG(strLog)  LIBAPI_WRITE_COMMON_LOG(CCommonLog::LOG_WARN, strLog)
#define LIBAPI_WRITE_INFO_LOG(strLog)  LIBAPI_WRITE_COMMON_LOG(CCommonLog::LOG_INFO, strLog)
#define LIBAPI_WRITE_DEBUG_LOG(strLog) LIBAPI_WRITE_COMMON_LOG(CCommonLog::LOG_DEBUG, strLog)

#define MASTERSTANDBY_WRITE_FATAL_LOG(strLog) MASTERSTANDBY_WRITE_COMMON_LOG(CCommonLog::LOG_FATAL, strLog)
#define MASTERSTANDBY_WRITE_ERROR_LOG(strLog) MASTERSTANDBY_WRITE_COMMON_LOG(CCommonLog::LOG_ERROR, strLog)
#define MASTERSTANDBY_WRITE_WARN_LOG(strLog)  MASTERSTANDBY_WRITE_COMMON_LOG(CCommonLog::LOG_WARN, strLog)
#define MASTERSTANDBY_WRITE_INFO_LOG(strLog)  MASTERSTANDBY_WRITE_COMMON_LOG(CCommonLog::LOG_INFO, strLog)
#define MASTERSTANDBY_WRITE_DEBUG_LOG(strLog) MASTERSTANDBY_WRITE_COMMON_LOG(CCommonLog::LOG_DEBUG, strLog)

class CCommonLog : CCommonThreadCore
{
public:
	enum ELogLevel
	{
		LOG_FATAL = 0,	/**< 致命错误 */
		LOG_ERROR,	    /**< 错误 */
		LOG_WARN,	    /**< 警告 */
		LOG_INFO,	    /**< 普通输出信息 */
		LOG_DEBUG,	    /**< 调试信息 */
	};

public:		
	void Write(std::string strLog, ELogLevel eLevel = LOG_INFO);
	void LibApiWrite(std::string strLog, ELogLevel eLevel = LOG_INFO);
	void MasterStandbyWrite(std::string strLog, ELogLevel eLevel = LOG_INFO);

private:
	void DoWrite(std::string strLog, ELogLevel eLevel = LOG_INFO);
	void LibApiDoWrite(std::string strLog, ELogLevel eLevel = LOG_INFO);
	void MasterStandbyDoWrite(std::string strLog, ELogLevel eLevel = LOG_INFO);

public:
	static CCommonLog*     GetInstance();
	virtual ~CCommonLog();

protected:
	CCommonLog();
	virtual void        HSGetMessage(CommonThread_data msg_data);

private:
	CCommonWorkThread     m_threadProcLog;
	std::string m_strPluginName;
	std::string m_strLibApiPluginName;
	std::string m_strMasterStandbyLibName;
};

#endif