#ifndef __DefAPISystemEvt_H__
#define __DefAPISystemEvt_H__

#include "DefAPIType.h"

namespace MRPS
{
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++APIϵͳ����ص�����+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

	/*����API����ACK�¼����ö�ٶ���*/
	typedef enum InitResult
	{
		INIT_SUCCESS = 0,					///< �ɹ�
		INIT_ERROR_UNKNOWN = -1,			///< δ֪����
		INIT_ERROR_INVALID_LICENSE = -2,    ///< LICENSE�Ƿ�
		INIT_ERROR_NETWORK_ERR = -3,		///< �������
	}InitResult;

	/** ���Ʒ���ȷ���¼�
	@param [in] result   ��� �������ݼ� InitResult
	@param [in] time_t   ʱ���
	@return
	*/
	struct Param_InitializeAck_Evt : public Param_Base
	{
		std::string strSystemId;
		InitResult  result;
		time_t      timeStamp;

		Param_InitializeAck_Evt()
		{
			type = ParamType_Param_InitializeAck_Evt;
			result = INIT_SUCCESS;
			timeStamp = std::time(NULL);
		}

		Param_InitializeAck_Evt(const Param_InitializeAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_InitializeAck_Evt& operator=(const Param_InitializeAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_InitializeAck_Evt)(const Param_InitializeAck_Evt& param);



	/*����ACK�¼����ö�ٶ���*/
	typedef enum HeartbeatResult
	{
		HEARTBEAT_SUCCESS = 0,	                ///< �ɹ�
		HEARTBEAT_ERROR_UNKNOWN = -1,			///< δ֪����
		HEARTBEAT_ERROR_TIMEOUT = -2,			///< ������ʱ
		HEARTBEAT_ERROR_NETWORK_ERR = -3,		///< �������
	}HeartbeatResult;

	/** ϵͳ�����¼�
	@param [in] result   ��� �������ݼ�  HeartbeatResult
	@param [in] time_t   ʱ���
	@return
	*/
	struct Param_Heartbeat_Evt : public Param_Base
	{
		std::string     strSystemId;
		HeartbeatResult result;
		time_t          timeStamp;

		Param_Heartbeat_Evt()
		{
			type = ParamType_Param_Heartbeat_Evt;
			result = HEARTBEAT_SUCCESS;
			timeStamp = std::time(NULL);
		}

		Param_Heartbeat_Evt(const Param_Heartbeat_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_Heartbeat_Evt& operator=(const Param_Heartbeat_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			return *this;

		}
	};
	typedef int(*MRPS_Heartbeat_Evt)(const Param_Heartbeat_Evt& param);

	/*��¼ACK�¼����ö�ٶ���*/
	typedef enum LoginResult
	{
		LOGIN_SUCCESS = 0,							 ///< �ɹ�
		LOGIN_ERROR_UNKNOWN = -1,					 ///< δ֪����
		LOGIN_ERROR_USER_ALREADY_LOGINED = -2,       ///< �û��ѵ�¼
		LOGIN_ERROR_INVALID_USER_OR_PASSWORD = -3,   ///< �û��������������
		LOGIN_ERROR_INVALID_SSI = -4,			     ///< SSI���벻����
		LOGIN_ERROR_INVALID_SERVICE = -5,		     ///< ϵͳ���񲻿���
		LOGIN_ERROR_LICENSEERROR = -6,
		LOGIN_ERROR_LICENSE_LIMIT_NUM = -7,
		LOGIN_ERROR_SERVER_UNINIT = -8,
		LOGIN_ERROR_SERVER_UNLOADDATA = -9,

		//SIP ERROR
		LOGIN_ERROR_Unauthorized = -30,
		LOGIN_ERROR_Forbidden = -31,
		LOGIN_ERROR_NotFound = -32,
		LOGIN_ERROR_RequestTimeout = -33,

		LOGIN_ERROR_NETWORKERROR = -99,
	}LoginResult;

	/** ��¼�ص�ȷ���¼�
	@param [in] name     ¼���������û���
	@param [in] id       ¼���������ĺ���
	@param [in] result   ��� �������ݼ�  LoginResult
	@param [in] time_t   ʱ���
	@return
	*/
	struct Param_LoginAck_Evt : public Param_Base
	{
		std::string     strSystemId;
		std::string     strUser;
		std::string     strNumber;
		LoginResult     result;
		time_t          timeStamp;

		Param_LoginAck_Evt()
		{
			type = ParamType_Param_LoginAck_Evt;
			result = LOGIN_SUCCESS;
			timeStamp = std::time(NULL);
		}

		Param_LoginAck_Evt(const Param_LoginAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			strUser = other.strUser;
			strNumber = other.strNumber;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_LoginAck_Evt& operator=(const Param_LoginAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strUser = other.strUser;
			strNumber = other.strNumber;
			result = other.result;
			timeStamp = other.timeStamp;
			return *this;

		}
	};
	typedef int(*MRPS_LoginAck_Evt)(const Param_LoginAck_Evt& param);


	/*�ǳ�ACK�¼����ö�ٶ���*/
	typedef enum LogoutResult
	{
		LOGOUT_SUCCESS = 0,						///< �ɹ�
		LOGOUT_ERROR_UNKNOWN = -1,				///< δ֪����
		LOGOUT_ERROR_NETWORK_ERR = -2,		    ///< �������
	}LogoutResult;

	/** �ǳ��ص�ȷ���¼�
	@param [in] name     �û���
	@param [in] id       ¼���������ĺ���
	@param [in] result   �ǳ���� ��LogoutResult
	@param [in] time_t   ʱ���
	@return
	@see
	*/
	struct Param_LogoutAck_Evt : public Param_Base
	{
		std::string     strSystemId;
		std::string     strUser;
		std::string     strNumber;
		LogoutResult     result;
		time_t          timeStamp;

		Param_LogoutAck_Evt()
		{
			type = ParamType_Param_LogoutAck_Evt;
			result = LOGOUT_SUCCESS;
			timeStamp = std::time(NULL);
		}

		Param_LogoutAck_Evt(const Param_LogoutAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			strUser = other.strUser;
			strNumber = other.strNumber;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_LogoutAck_Evt& operator=(const Param_LogoutAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strUser = other.strUser;
			strNumber = other.strNumber;
			result = other.result;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_LogoutAck_Evt)(const Param_LogoutAck_Evt& param);

	/*ϵͳACK�¼����ö�ٶ���*/
	typedef enum SystemEvent
	{
		SYSTEM_EVENT_NETWORK_CONNECTED = 1,         ///< �������ӳɹ�
		SYSTEM_EVENT_NETWORK_DISCONNECT,            ///< ���������Ͽ�
		SYSTEM_EVENT_NETWORK_ERROR,	                ///< �����쳣
		SYSTEM_EVENT_USER_LOGUT_ABNORMAL,	        ///< �û��쳣�˳�
		SYSTEM_EVENT_HEARTBEAT_TIMEOU,	            ///< ������ʱ
		SYSTEM_EVENT_SYSTEM_ABNORMAL,		        ///< ϵͳ�쳣
		SYSTEM_EVENT_SERVICE_CC_ABNORMAL,	        ///< ���п��Ʒ����쳣
		SYSTEM_EVENT_SERVICE_REC_ABNORMAL,	        ///< ¼�������쳣
		SYSTEM_EVENT_SERVICE_NMS_ABNORMAL,	        ///< ���ܷ����쳣
		SYSTEM_EVENT_SERVICE_NMS_NORMAL,            ///< ���ܷ�������
		SYSTEM_EVENT_SERVICE_SDS_ABNORMAL,	        ///< ����Ϣ�����쳣
		SYSTEM_EVENT_SERVICE_GPS_ABNORMAL,	        ///< GPS�����쳣
		SYSTEM_EVENT_SERVICE_STATUS_UN_NORMAL,      ///<δ֪�쳣
		SYSTEM_EVENT_SERVICE_STATUS_NORMAL,         ///<����
		SYSTEM_EVENT_SERVICE_STATUS_SERVER_RESTART, ///<����������
		SYSTEM_EVENT_SERVICE_STATUS_SERVER_SHUTDOWN,///<�������ر�

		SYSTEM_EVENT_USER_KICKOUT = 200,

	}SystemEvent;

	/** ϵͳ�¼��ص��¼�
	@param [in] event    ϵͳ�¼�
	@param [in] time_t   ʱ���
	@return
	@see
	*/
	struct Param_System_Evt : public Param_Base
	{
		std::string     strSystemId;
		SystemEvent     result;
		time_t          timeStamp;

		Param_System_Evt()
		{
			type = ParamType_Param_System_Evt;
			result = SYSTEM_EVENT_NETWORK_ERROR;
			timeStamp = std::time(NULL);
		}

		Param_System_Evt(const Param_System_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_System_Evt& operator=(const Param_System_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_System_Evt)(const Param_System_Evt& param);

	enum RsApi_LogLevel
	{
		APILOG_FATAL = 0,	/**< �������� */
		APILOG_ERROR,	    /**< ���� */
		APILOG_WARN,	    /**< ���� */
		APILOG_INFO,	    /**< ��ͨ�����Ϣ */
		APILOG_DEBUG,	    /**< ������Ϣ */
	};

	/** ��־�¼��ص��¼�
	@param [in] pszLogInfo ��־��Ϣ
	@param [in] pszModule  ��־ģ��
	@param [in] level      ��־����
	@return
	@see
	*/
	struct Param_Log_Evt : public Param_Base
	{
		std::string     strSystemId;
		std::string     strLogInfo;
		std::string     strModule;
		RsApi_LogLevel  level;

		Param_Log_Evt()
		{
			type = ParamType_Param_Log_Evt;
			level = APILOG_DEBUG;
		}

		Param_Log_Evt(const Param_Log_Evt& other)
		{
			strSystemId = other.strSystemId;
			strLogInfo = other.strLogInfo;
			strModule = other.strModule;
			level = other.level;
		}

		Param_Log_Evt& operator=(const Param_Log_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strLogInfo = other.strLogInfo;
			strModule = other.strModule;
			level = other.level;
			return *this;
		}
	};
	typedef int(*MRPS_Log_Evt)(const Param_Log_Evt& param);

	enum AlarmFlag
	{
		AlarmFlag_Unknown = 0,
		AlarmFlag_Alarm,
		AlarmFlag_CancelAlarm,
	};

	/** �澯�¼��ص��¼�
	@param [in] pszLogInfo ��־��Ϣ
	@param [in] pszModule  ��־ģ��
	@param [in] level      ��־����
	@return
	@see
	*/
	struct Param_Alarm_Evt : public Param_Base
	{
		std::string     strSystemId;
		std::string     strAlarmCode;
		std::string     strAlarmInfo;
		std::string     strModule;
		int             iAlarmFlag;
		time_t          timeStamp;

		Param_Alarm_Evt()
		{
			type = ParamType_Param_Alarm_Evt;	
			iAlarmFlag = AlarmFlag_Unknown;
			timeStamp = std::time(NULL);
		}

		Param_Alarm_Evt(const Param_Alarm_Evt& other)
		{
			strSystemId = other.strSystemId;
			strAlarmCode = other.strAlarmCode;
			strModule = other.strModule;
			strAlarmInfo = other.strAlarmInfo;
			timeStamp = other.timeStamp;
			iAlarmFlag = other.iAlarmFlag;
		}

		Param_Alarm_Evt& operator=(const Param_Alarm_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strAlarmCode = other.strAlarmCode;
			strModule = other.strModule;
			strAlarmInfo = other.strAlarmInfo;
			timeStamp = other.timeStamp;
			iAlarmFlag = other.iAlarmFlag;
			return *this;
		}
	};
	typedef int(*MRPS_Alarm_Evt)(const Param_Alarm_Evt& param);

	//APIϵͳ����ص��¼�ԭ��
	typedef struct SYS_EVENTS
	{
		MRPS_InitializeAck_Evt		rs_initialize_ack;     ///< ϵͳ��ʼ��ȷ���¼�
		MRPS_Heartbeat_Evt			rs_heartbeat_ack;      ///< ϵͳ�����¼�
		MRPS_LoginAck_Evt			rs_login_ack;          ///< ��¼�ص�ȷ���¼�
		MRPS_LogoutAck_Evt			rs_logout_ack;         ///< �ǳ��ص�ȷ���¼�
		MRPS_System_Evt			    rs_system_event;       ///< ϵͳ�ص��¼�
		MRPS_Log_Evt                rs_log_event;
		MRPS_Alarm_Evt              rs_alarm_event;

		SYS_EVENTS()
		{
			rs_initialize_ack = NULL;
			rs_heartbeat_ack = NULL;
			rs_login_ack = NULL;
			rs_logout_ack = NULL;
			rs_system_event = NULL;
			rs_log_event = NULL;
			rs_alarm_event = NULL;
		}

		SYS_EVENTS(const SYS_EVENTS& other)
		{
			rs_initialize_ack = other.rs_initialize_ack;
			rs_heartbeat_ack = other.rs_heartbeat_ack;
			rs_login_ack = other.rs_login_ack;
			rs_logout_ack = other.rs_logout_ack;
			rs_system_event = other.rs_system_event;
			rs_log_event = other.rs_log_event;
			rs_alarm_event = other.rs_alarm_event;
		}

		SYS_EVENTS& operator=(const SYS_EVENTS& other)
		{
			if (&other == this)
			{
				return *this;
			}

			rs_initialize_ack = other.rs_initialize_ack;
			rs_heartbeat_ack = other.rs_heartbeat_ack;
			rs_login_ack = other.rs_login_ack;
			rs_logout_ack = other.rs_logout_ack;
			rs_system_event = other.rs_system_event;
			rs_log_event = other.rs_log_event;
			rs_alarm_event = other.rs_alarm_event;

			return *this;
		}

	}*PSYS_EVENTS;
}

#endif