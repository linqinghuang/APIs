
#include "CommonTimer.h"
#include "Poco/Timestamp.h"
#include "Poco/Clock.h"
#include <thread>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void CCommonTimer::AddTimer(CCommonTimerCore *pTimerCore, unsigned long uMsgId, unsigned long uInterval)
{
	CommonTimerData data;
	data.pCoreTimer = pTimerCore;
	//Poco::Timestamp stamp;
	Poco::Clock stamp;
	data.u64FirstTime = stamp.microseconds();//stamp.epochMicroseconds();
	data.uInterval = uInterval;

	_AddTimer(uMsgId, data);

	if (m_threadExec.isRunning())
	{
		m_envetNotifyExec.set();
		return ;
	}

	_StartThread();
}

void CCommonTimer::RemoveTimer(unsigned long uMsgId)
{
	_RemoveTimer(uMsgId);
}

void CCommonTimer::SetTimerMode(TimerMode mode)
{
	m_timerMode = mode;
}

void CCommonTimer::SetTimerName(const std::string& strTimerName)
{
	m_strTimerName = strTimerName;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CCommonTimer::CCommonTimer()
{
	m_bStopThread = false;
	m_timerMode = TimerMode_Absolute;
}

CCommonTimer::~CCommonTimer()
{
	_StopThread();
}

bool CCommonTimer::_StartThread()
{
	m_bStopThread = false;
	try
	{	
		if (!m_threadExec.isRunning())
		{
			Poco::ScopedLock<Poco::FastMutex> lock(m_mutexStartThread);
			if (!m_threadExec.isRunning())
			{
				m_threadExec.start(*this);
			}			
		}		
	}	
	catch(Poco::Exception &ex)
	{
		//std::cout<<"_StartThread: "<<ex.displayText()<<std::endl;
		int k = 0;
		return false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void CCommonTimer::_StopThread()
{
	try
	{
		m_bStopThread = true;
		m_envetNotifyExec.set();
		m_threadExec.join(20);
	}	
	catch(Poco::Exception &ex)
	{
		//std::cout<<"_StopThread: "<<ex.displayText()<<std::endl;
		int k = 0;
	}
	catch (...)
	{
		int k = 0;
	}
}


void CCommonTimer::_AddTimer(unsigned long uMsgId, CommonTimerData data)
{
	Poco::ScopedLock<Poco::FastMutex> lock(m_mutexTimerInfo);
	m_mapTimerInfo.insert(std::make_pair(uMsgId, data));
}

void CCommonTimer::_RemoveTimer(unsigned long uMsgId)
{
	Poco::ScopedLock<Poco::FastMutex> lock(m_mutexTimerInfo);
	std::map<unsigned long, CommonTimerData>::iterator itr;
	itr = m_mapTimerInfo.find(uMsgId);
	if (itr != m_mapTimerInfo.end())
	{
		m_mapTimerInfo.erase(itr);
	}
}

void CCommonTimer::_ModifyFirstTime(unsigned uMsgId, unsigned long long uTime)
{
	Poco::ScopedLock<Poco::FastMutex> lock(m_mutexTimerInfo);
	std::map<unsigned long, CommonTimerData>::iterator itr;
	itr = m_mapTimerInfo.find(uMsgId);
	if (itr != m_mapTimerInfo.end())
	{
		itr->second.u64FirstTime = uTime;
	}
}

bool CCommonTimer::_IsTimerMapEmpty()
{
	Poco::ScopedLock<Poco::FastMutex> lock(m_mutexTimerInfo);
	return m_mapTimerInfo.empty();
}

void CCommonTimer::run()
{
	while(!m_bStopThread)
	{
		if (_IsTimerMapEmpty())
		{
			m_envetNotifyExec.wait();
		}
		else
		{
			std::map<unsigned long, CommonTimerData> mapTmps;
			{
				Poco::ScopedLock<Poco::FastMutex> lock(m_mutexTimerInfo);
				mapTmps = m_mapTimerInfo;
			}		

			std::map<unsigned long, CommonTimerData>::const_iterator itr;
			for (itr = mapTmps.begin(); itr != mapTmps.end(); ++itr)
			{
				//Poco::Timestamp stamp;
				Poco::Clock stamp;
				unsigned long long u64Time = stamp.microseconds();//stamp.epochMicroseconds();
				long long n64Interval = (long long)(u64Time - itr->second.u64FirstTime);
				if (n64Interval < 0)
				{
					_ModifyFirstTime(itr->first, u64Time);
					continue;
				}

				unsigned long long n64Tmp = itr->second.uInterval;
				n64Tmp *= (1000);					
				
				if ((unsigned long long)n64Interval > n64Tmp)
				{
					if (n64Interval > (n64Tmp * 2))
					{
						_ModifyFirstTime(itr->first, u64Time);
					}
					else
					{
						if (m_timerMode == TimerMode_Absolute)
						{
							_ModifyFirstTime(itr->first, itr->second.u64FirstTime + n64Tmp);
						}
						else
						{
							_ModifyFirstTime(itr->first, u64Time);
						}						
					}
					
					if (m_bStopThread)
					{
						break;
					}

					try
					{
						itr->second.pCoreTimer->OnTimer(itr->first);
					}					
					catch (...)
					{
					}
									
				}
			}
			//Poco::Thread::sleep(1);	
			//m_envetWait.tryWait(1);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}		
	}
}