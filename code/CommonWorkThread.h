/**
 @Copyright Copyright (C), 2014, Hytera
 @file		CommonWorkThread.h
 @created	2014/06/27
 @brief		

 @author	xujinghua
*/

#ifndef __CommonWorkThread_H__
#define __CommonWorkThread_H__

#include "CommonThreadCore.h"
#include "Poco/Thread.h"
#include "Poco/Mutex.h"
#include "Poco/Event.h"
#include "Poco/RWLock.h"
#include <vector>
#include <atomic>


struct CommonThread_Object
{
	CommonThread_data		thread_data;				///< 相关的线程数据
	CCommonThreadCore	   *threadcore;				///< 使用的类型
};

typedef std::vector<CommonThread_Object>	CommonThread_Object_vector;	   ///< 线程要执行的消息队列

typedef void(*PFunc_LogOutput)(const std::string& strLog);

class CCommonWorkThread : public Poco::Runnable
{
public:
	CCommonWorkThread(void);
	virtual ~CCommonWorkThread(void);

public:	
	void         SetDeleteData(bool bDel = false);
	void         SetThreadName(const std::string& strThreadName);//只调用一次
	std::string  GetThreadName();
	int          GetCWorkThreadListCount();	
	void         HSAddMessage(CCommonThreadCore *pThreadCore = NULL, __culong_ uMsgId = 0, __culong_ ulParam = 0, __culong_ uwParam = 0, __clong_ lData = 0, std::string strmsg = "");
	bool         Start();
	void         Stop(long lMilliseconds);
	void         SetLogOutput(PFunc_LogOutput pFuncLogOutput);

private:
	bool         _AddMsgToVector(CommonThread_Object  msgData);
	bool         _IsAddMsgVectorEmpty();
	bool         _IsExecMsgVectorEmpty();

private:
	Poco::FastMutex					m_mutexAddMsgVector;
	Poco::FastMutex					m_mutexExecMsgVector;
	CommonThread_Object_vector		m_vectorExecMsg;
	CommonThread_Object_vector		m_vectorAddMsg;
	Poco::Thread					m_threadExecMsg;
	Poco::Event						m_eventExecWait;
	
	std::atomic_bool			    m_bStopRunning;
	std::atomic_bool                m_bDeleteData;
	std::atomic_bool                m_bExitExec;

	PFunc_LogOutput                 m_pFuncLogOutput;

	std::string                     m_strThreadName;

private:
	void run();
};


#endif

