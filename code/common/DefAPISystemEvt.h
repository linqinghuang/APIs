#ifndef __DefAPISystemEvt_H__
#define __DefAPISystemEvt_H__

#include "DefAPIType.h"

namespace MRPS
{
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++API系统服务回调函数+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

	/*定制API服务ACK事件结果枚举定义*/
	typedef enum InitResult
	{
		INIT_SUCCESS = 0,					///< 成功
		INIT_ERROR_UNKNOWN = -1,			///< 未知错误
		INIT_ERROR_INVALID_LICENSE = -2,    ///< LICENSE非法
		INIT_ERROR_NETWORK_ERR = -3,		///< 网络错误
	}InitResult;

	/** 定制服务确认事件
	@param [in] result   结果 具体内容见 InitResult
	@param [in] time_t   时间戳
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



	/*心跳ACK事件结果枚举定义*/
	typedef enum HeartbeatResult
	{
		HEARTBEAT_SUCCESS = 0,	                ///< 成功
		HEARTBEAT_ERROR_UNKNOWN = -1,			///< 未知错误
		HEARTBEAT_ERROR_TIMEOUT = -2,			///< 心跳超时
		HEARTBEAT_ERROR_NETWORK_ERR = -3,		///< 网络错误
	}HeartbeatResult;

	/** 系统心跳事件
	@param [in] result   结果 具体内容见  HeartbeatResult
	@param [in] time_t   时间戳
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

	/*登录ACK事件结果枚举定义*/
	typedef enum LoginResult
	{
		LOGIN_SUCCESS = 0,							 ///< 成功
		LOGIN_ERROR_UNKNOWN = -1,					 ///< 未知错误
		LOGIN_ERROR_USER_ALREADY_LOGINED = -2,       ///< 用户已登录
		LOGIN_ERROR_INVALID_USER_OR_PASSWORD = -3,   ///< 用户名或者密码错误
		LOGIN_ERROR_INVALID_SSI = -4,			     ///< SSI号码不可用
		LOGIN_ERROR_INVALID_SERVICE = -5,		     ///< 系统服务不可用
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

	/** 登录回调确认事件
	@param [in] name     录音服务器用户名
	@param [in] id       录音服务器的号码
	@param [in] result   结果 具体内容见  LoginResult
	@param [in] time_t   时间戳
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


	/*登出ACK事件结果枚举定义*/
	typedef enum LogoutResult
	{
		LOGOUT_SUCCESS = 0,						///< 成功
		LOGOUT_ERROR_UNKNOWN = -1,				///< 未知错误
		LOGOUT_ERROR_NETWORK_ERR = -2,		    ///< 网络错误
	}LogoutResult;

	/** 登出回调确认事件
	@param [in] name     用户名
	@param [in] id       录音服务器的号码
	@param [in] result   登出结果 见LogoutResult
	@param [in] time_t   时间戳
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

	/*系统ACK事件结果枚举定义*/
	typedef enum SystemEvent
	{
		SYSTEM_EVENT_NETWORK_CONNECTED = 1,         ///< 网络链接成功
		SYSTEM_EVENT_NETWORK_DISCONNECT,            ///< 网络正常断开
		SYSTEM_EVENT_NETWORK_ERROR,	                ///< 网络异常
		SYSTEM_EVENT_USER_LOGUT_ABNORMAL,	        ///< 用户异常退出
		SYSTEM_EVENT_HEARTBEAT_TIMEOU,	            ///< 心跳超时
		SYSTEM_EVENT_SYSTEM_ABNORMAL,		        ///< 系统异常
		SYSTEM_EVENT_SERVICE_CC_ABNORMAL,	        ///< 呼叫控制服务异常
		SYSTEM_EVENT_SERVICE_REC_ABNORMAL,	        ///< 录音服务异常
		SYSTEM_EVENT_SERVICE_NMS_ABNORMAL,	        ///< 网管服务异常
		SYSTEM_EVENT_SERVICE_NMS_NORMAL,            ///< 网管服务正常
		SYSTEM_EVENT_SERVICE_SDS_ABNORMAL,	        ///< 短消息服务异常
		SYSTEM_EVENT_SERVICE_GPS_ABNORMAL,	        ///< GPS服务异常
		SYSTEM_EVENT_SERVICE_STATUS_UN_NORMAL,      ///<未知异常
		SYSTEM_EVENT_SERVICE_STATUS_NORMAL,         ///<正常
		SYSTEM_EVENT_SERVICE_STATUS_SERVER_RESTART, ///<服务器重启
		SYSTEM_EVENT_SERVICE_STATUS_SERVER_SHUTDOWN,///<服务器关闭

		SYSTEM_EVENT_USER_KICKOUT = 200,

	}SystemEvent;

	/** 系统事件回调事件
	@param [in] event    系统事件
	@param [in] time_t   时间戳
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
		APILOG_FATAL = 0,	/**< 致命错误 */
		APILOG_ERROR,	    /**< 错误 */
		APILOG_WARN,	    /**< 警告 */
		APILOG_INFO,	    /**< 普通输出信息 */
		APILOG_DEBUG,	    /**< 调试信息 */
	};

	/** 日志事件回调事件
	@param [in] pszLogInfo 日志信息
	@param [in] pszModule  日志模块
	@param [in] level      日志级别
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

	/** 告警事件回调事件
	@param [in] pszLogInfo 日志信息
	@param [in] pszModule  日志模块
	@param [in] level      日志级别
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

	//API系统服务回调事件原型
	typedef struct SYS_EVENTS
	{
		MRPS_InitializeAck_Evt		rs_initialize_ack;     ///< 系统初始化确认事件
		MRPS_Heartbeat_Evt			rs_heartbeat_ack;      ///< 系统心跳事件
		MRPS_LoginAck_Evt			rs_login_ack;          ///< 登录回调确认事件
		MRPS_LogoutAck_Evt			rs_logout_ack;         ///< 登出回调确认事件
		MRPS_System_Evt			    rs_system_event;       ///< 系统回调事件
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