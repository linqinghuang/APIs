/**
 @Copyright Copyright (C), 2014, Hytera
 @file		CommonTimer.h
 @created	2014/06/27
 @brief		

 @author	xujinghua
*/

#ifndef __CommonTimer_H__
#define __CommonTimer_H__

#include "CommonTimerCore.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"
#include "Poco/Thread.h"
#include <map>
#include <atomic>

struct CommonTimerData
{
	CCommonTimerCore	   *pCoreTimer;	       //�ص�ָ��
	unsigned long long u64FirstTime;	   //��ʼ���õ�ʱ��
	unsigned long	   uInterval;		   //��ʱ�����¼��¼���λ����
};

enum TimerMode
{
	TimerMode_Relative,
	TimerMode_Absolute,
};

class CCommonTimer : public Poco::Runnable
{
public:	
	void AddTimer(CCommonTimerCore *pTimerCore, unsigned long uMsgId, unsigned long uInterval);//uInterval,��λ����	  
	void RemoveTimer(unsigned long uMsgId);		
	void SetTimerMode(TimerMode mode);//ֻ����һ��
	void SetTimerName(const std::string& strTimerName);//ֻ����һ��

public:
	CCommonTimer();
	virtual ~CCommonTimer();

protected:
	virtual void run();
	bool         _StartThread();
	void         _StopThread();
	
	void         _AddTimer(unsigned long uMsgId, CommonTimerData data);
	void         _RemoveTimer(unsigned long uMsgId);
	void         _ModifyFirstTime(unsigned uMsgId, unsigned long long uTime);
	bool         _IsTimerMapEmpty();

protected:
	Poco::Thread                           m_threadExec;
	
	std::atomic_bool                       m_bStopThread;
	Poco::Event	                           m_envetNotifyExec;	
	Poco::FastMutex					       m_mutexTimerInfo;
	std::map<unsigned long, CommonTimerData> m_mapTimerInfo;

	Poco::Event	                           m_envetWait;
	Poco::FastMutex                        m_mutexStartThread;
	TimerMode                              m_timerMode;
	std::string                            m_strTimerName;
};

#endif