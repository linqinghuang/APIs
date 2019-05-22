
#include "CommonWorkThread.h"
#include <thread>


/************************************************************************/
/*                                                                      */
/************************************************************************/
void CCommonWorkThread::SetDeleteData(bool bDel /* = false */)
{	
	m_bDeleteData = bDel;
}

void CCommonWorkThread::SetThreadName(const std::string& strThreadName)
{
	m_strThreadName = strThreadName;
}

std::string CCommonWorkThread::GetThreadName()
{
	return m_strThreadName;
}

int CCommonWorkThread::GetCWorkThreadListCount()
{
	int nAddMsgVectorSize = 0;
	int nExecMsgVectorSize = 0;

	{
		Poco::ScopedLock<Poco::FastMutex> lock(m_mutexAddMsgVector);
		nAddMsgVectorSize = m_vectorAddMsg.size();
	}

	{
		Poco::ScopedLock<Poco::FastMutex> lock(m_mutexExecMsgVector);
		nExecMsgVectorSize = m_vectorExecMsg.size();
	}

	return nAddMsgVectorSize + nExecMsgVectorSize;
}

void CCommonWorkThread::HSAddMessage(CCommonThreadCore *pThreadCore /* = NULL */, __culong_ uMsgId /* = 0 */, __culong_ ulParam /* = 0 */, __culong_ uwParam /* = 0 */, __clong_ lData /* = 0 */, std::string strmsg /* = */)
{
	try
	{		
		if (NULL != pThreadCore)
		{
			if (m_bStopRunning)
			{
				if (m_bDeleteData && pThreadCore)
				{
					pThreadCore->DeleteData(ulParam, uwParam, lData);
				}
				return ;
			}

			CommonThread_Object  msg_data;				

			msg_data.threadcore				= pThreadCore;
			msg_data.thread_data.msg_id		= uMsgId;
			msg_data.thread_data.lParam		= ulParam;
			msg_data.thread_data.wParam		= uwParam;
			msg_data.thread_data.data		= lData;
			msg_data.thread_data.str_msg    = strmsg;

			_AddMsgToVector(msg_data);
			if (!_IsAddMsgVectorEmpty())
			{
				m_bStopRunning = false;
				if (m_threadExecMsg.isRunning())
				{
					m_eventExecWait.set();
					return ;
				}
			}

			if (!m_threadExecMsg.isRunning())
			{
				m_threadExecMsg.start(*this);
			}			
		}
	}
	catch (Poco::Exception& ex)
	{
		std::string strTmp = m_strThreadName + "--HSAddMessage Exception" + ex.what();
		if (m_pFuncLogOutput)
		{
			m_pFuncLogOutput(strTmp);
		}
		
	}
	catch (...)
	{
		std::string strTmp = m_strThreadName + "--Unknown HSAddMessage Exception";
		if (m_pFuncLogOutput)
		{
			m_pFuncLogOutput(strTmp);
		}
	}
}

void CCommonWorkThread::SetLogOutput(PFunc_LogOutput pFuncLogOutput)
{
	m_pFuncLogOutput = pFuncLogOutput;
}

bool CCommonWorkThread::Start()
{
	m_bStopRunning = false;

	try
	{
		if (m_threadExecMsg.isRunning())
		{			
			return true;
		}

		m_threadExecMsg.start(*this);
	}	
	catch (...)
	{
		std::string strTmp = m_strThreadName + "--Unknown Start Exception";
		m_pFuncLogOutput(strTmp);
		return false;
	}
	return true;	
}

void CCommonWorkThread::Stop(long lMilliseconds)
{
    m_bStopRunning = true;
	m_eventExecWait.set();

	try
	{		
		if (lMilliseconds == 0)
		{
			m_threadExecMsg.join();
		}
		else
		{
			m_threadExecMsg.join(lMilliseconds);
		}
	}
	catch(Poco::Exception &ex)
	{
		if (m_pFuncLogOutput)
		{
			std::string strTmp = m_strThreadName + "--Stop Exception: ";
			strTmp += ex.displayText();
			m_pFuncLogOutput(strTmp);
		}		
	}
	catch (...)
	{
		std::string strTmp = m_strThreadName + "--Unknown Stop Exception";		
		if (m_pFuncLogOutput)
		{
			m_pFuncLogOutput(strTmp);
		}
	}

	{
		Poco::ScopedLock<Poco::FastMutex> lock(m_mutexAddMsgVector);
		CommonThread_Object_vector::iterator iter;
		for (iter = m_vectorAddMsg.begin(); iter != m_vectorAddMsg.end(); ++iter)
		{
			if (m_bDeleteData)
			{
				iter->threadcore->DeleteData(iter->thread_data.lParam, iter->thread_data.wParam, iter->thread_data.data);
			}
		}
		m_vectorAddMsg.clear();
	}

	{
		Poco::ScopedLock<Poco::FastMutex> lock(m_mutexExecMsgVector);
		CommonThread_Object_vector::iterator iter;
		for (iter = m_vectorExecMsg.begin(); iter != m_vectorExecMsg.end(); ++iter)
		{
			if (m_bDeleteData)
			{
				iter->threadcore->DeleteData(iter->thread_data.lParam, iter->thread_data.wParam, iter->thread_data.data);
			}
		}
		m_vectorExecMsg.clear();
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CCommonWorkThread::CCommonWorkThread(void)
{
	try
	{
		m_bExitExec = false;
		m_pFuncLogOutput = NULL;
        m_bDeleteData  = false;
		m_bStopRunning = false;
		m_threadExecMsg.start(*this);		
	}
	catch (...)
	{
		int k = 0;
	}
}

CCommonWorkThread::~CCommonWorkThread(void)
{
	m_pFuncLogOutput = NULL;
	Stop(0);	
}

void CCommonWorkThread::run()
{
	int iExeCount = 0;
	while(!m_bStopRunning)
	{
		try
		{	
			if (!_IsExecMsgVectorEmpty())
			{
				Poco::ScopedLock<Poco::FastMutex> lock(m_mutexExecMsgVector);
				CommonThread_Object_vector::iterator iter;
				iter = m_vectorExecMsg.begin();
				if (NULL != iter->threadcore)
				{
					try
					{
						iter->threadcore->HSGetMessage(iter->thread_data);
					}					
					catch (...)
					{
						if (m_pFuncLogOutput)
						{
							std::string strTmp = m_strThreadName + "--run Exception : ";
							m_pFuncLogOutput(strTmp);
						}
					}					
				}

                if (m_bDeleteData)
                {
					iter->threadcore->DeleteData(iter->thread_data.lParam, iter->thread_data.wParam, iter->thread_data.data);
                }

                m_vectorExecMsg.erase(iter);
				iExeCount++;
			}
			else
			{
				if (_IsAddMsgVectorEmpty())
				{
					CommonThread_Object_vector vecTmp;
					{
						Poco::ScopedLock<Poco::FastMutex> lock(m_mutexAddMsgVector);
						m_vectorAddMsg.swap(vecTmp);						
					}
					{
						Poco::ScopedLock<Poco::FastMutex> lock(m_mutexExecMsgVector);
						m_vectorExecMsg.swap(vecTmp);
					}
					m_eventExecWait.wait();
				}
				else
				{	
					CommonThread_Object_vector vecTmp;
					{
						Poco::ScopedLock<Poco::FastMutex> lock(m_mutexAddMsgVector);
						vecTmp = m_vectorAddMsg;
						m_vectorAddMsg.clear();
					}
					{
						Poco::ScopedLock<Poco::FastMutex> lock(m_mutexExecMsgVector);
						m_vectorExecMsg.clear();
						m_vectorExecMsg = vecTmp;	
					}								
					
                    //Poco::Thread::sleep(0);
					//std::this_thread::sleep_for(std::chrono::milliseconds(0));
				}
			}

			if (iExeCount >= 10)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				iExeCount = 0;
			}
						
		}
		catch (...)
		{
			int k = 0;
		}		
	}
}


bool CCommonWorkThread::_AddMsgToVector(CommonThread_Object msgData)
{
	Poco::ScopedLock<Poco::FastMutex> lock(m_mutexAddMsgVector);
	m_vectorAddMsg.push_back(msgData);
	return true;
}

bool CCommonWorkThread::_IsAddMsgVectorEmpty()
{
	Poco::ScopedLock<Poco::FastMutex> lock(m_mutexAddMsgVector);
	return m_vectorAddMsg.empty();
}

bool CCommonWorkThread::_IsExecMsgVectorEmpty()
{
	Poco::ScopedLock<Poco::FastMutex> lock(m_mutexExecMsgVector);
	return m_vectorExecMsg.empty();
}

