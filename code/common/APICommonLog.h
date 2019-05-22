/**
@Copyright Copyright (C), 2015-2016, Hytera
@file		CommonLog.h
@created	2015/12/23
@brief

@author	xujinghua
*/

#ifndef __TetraApiLog_H__
#define __TetraApiLog_H__


#include "IAPIObject.h"
#include <atomic>

const unsigned long MAX_LOG_HEADER = 1024;

#define WRITE_COMMON_LOG(level, strSystemId, strModule, strLog) \
do \
{ \
	std::string tmp_strLogs; \
	char tmp_szLogHead[MAX_LOG_HEADER] = { 0 }; \
	std::string tmp_strFunName(__FUNCTION__); \
	sprintf(tmp_szLogHead, "[%s:%d] ", tmp_strFunName.c_str(), __LINE__); \
	tmp_strLogs.append(tmp_szLogHead); \
	tmp_strLogs.append(strLog); \
	CAPICommonLog::GetInstance()->Write(strSystemId, strModule, tmp_strLogs, level); \
}while (0);

#define API_WRITE_FATAL_LOG(strSystemId, strModule, strLog) WRITE_COMMON_LOG(CAPICommonLog::LOG_FATAL, strSystemId, strModule, strLog)
#define API_WRITE_ERROR_LOG(strSystemId, strModule, strLog) WRITE_COMMON_LOG(CAPICommonLog::LOG_ERROR, strSystemId, strModule, strLog)
#define API_WRITE_WARN_LOG(strSystemId, strModule, strLog) WRITE_COMMON_LOG(CAPICommonLog::LOG_WARN, strSystemId, strModule, strLog)
#define API_WRITE_INFO_LOG(strSystemId, strModule, strLog) WRITE_COMMON_LOG(CAPICommonLog::LOG_INFO, strSystemId, strModule, strLog)
#define API_WRITE_DEBUG_LOG(strSystemId, strModule, strLog) WRITE_COMMON_LOG(CAPICommonLog::LOG_DEBUG, strSystemId, strModule, strLog)


class CAPICommonLog
{
public:
	enum ELogLevel
	{
		LOG_FATAL = 0,	/**< �������� */
		LOG_ERROR,	    /**< ���� */
		LOG_WARN,	    /**< ���� */
		LOG_INFO,	    /**< ��ͨ�����Ϣ */
		LOG_DEBUG,	    /**< ������Ϣ */
	};

public:		
	void SetLogCallback(MRPS::MRPS_Log_Evt pLogCallback);
	void Write(const std::string& strSystemId, const std::string& strModule, const std::string& strLog, ELogLevel eLevel = LOG_INFO);

public:
	static CAPICommonLog*     GetInstance();
	virtual ~CAPICommonLog();

protected:
	CAPICommonLog();

private:
	std::atomic_ulong m_pLogCallback;
};

#endif