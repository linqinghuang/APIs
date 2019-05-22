/**
HYTERA_LTE_RS_API.h
LTE录音录像API接口
参考文档：《BWT-3800_需求规格-录音录像.doc》

1. Date: 2016/12/06
Author: xujinghua

Modification: Create
*/


#ifndef __MRPS_API_H__
#define __MRPS_API_H__

#include <string>
#include <vector>
#pragma pack(push, 1)

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#ifdef _MRPS_EXPORTS_
#define MRPS_API __declspec(dllexport)
#else
#define MRPS_API __declspec(dllimport)
#endif

#else
#define MRPS_API
#endif


#ifdef __cplusplus
extern "C"{
#endif

#define NumberLen 32
#define GatewayLen 32
#define DeviceNumberLen 64
#define NodeCodeLen 64
#define AliasLen 128
#define Len64 64
#define Len32 32
#define Len128 128
		
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
	typedef int(*MRPS_InitializeAck_Evt)(InitResult result, time_t time_stamp);



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
	typedef int(*MRPS_Heartbeat_Evt)(HeartbeatResult result, time_t  time_stamp);

	/*登录ACK事件结果枚举定义*/
	typedef enum LoginResult
	{
		LOGIN_SUCCESS = 0,							 ///< 成功
		LOGIN_ERROR_UNKNOWN = -1,					 ///< 未知错误
		LOGIN_ERROR_USER_ALREADY_LOGINED = -2,       ///< 用户已登录
		LOGIN_ERROR_INVALID_USER_OR_PASSWORD = -3,   ///< 用户名或者密码错误
		LOGIN_ERROR_INVALID_SSI = -4,			     ///< SSI号码不可用
		LOGIN_ERROR_INVALID_SERVICE = -5		     ///< 系统服务不可用
	}LoginResult;

	/** 登录回调确认事件	
	@param [in] name     录音服务器用户名
	@param [in] id       录音服务器的号码
	@param [in] result   结果 具体内容见  LoginResult
	@param [in] time_t   时间戳
	@return 
	*/
	typedef int(*MRPS_LoginAck_Evt)(const char* pszName, const char* pszNumber, LoginResult result, time_t time_stamp);


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
	typedef int(*MRPS_LogoutAck_Evt)(const char* pszName, const char* pszNumber, LogoutResult result, time_t time_stamp);

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
	}SystemEvent;

	/** 系统事件回调事件
	@param [in] event    系统事件	
	@param [in] time_t   时间戳
	@return 
	@see
	*/
	typedef int(*MRPS_System_Evt)(SystemEvent event, time_t time_stamp);

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
	typedef int(*MRPS_Log_Evt)(const char* pszLogInfo, const char* pszModule, RsApi_LogLevel level);

	//API系统服务回调事件原型
	typedef struct
	{
		MRPS_InitializeAck_Evt		rs_initialize_ack;     ///< 系统初始化确认事件
		MRPS_Heartbeat_Evt			rs_heartbeat_ack;      ///< 系统心跳事件
		MRPS_LoginAck_Evt			rs_login_ack;          ///< 登录回调确认事件
		MRPS_LogoutAck_Evt			rs_logout_ack;         ///< 登出回调确认事件
		MRPS_System_Evt			    rs_system_event;       ///< 系统回调事件
		MRPS_Log_Evt                rs_log_event;
	} SYS_EVENTS, *PSYS_EVENTS;

	/** 初始化API服务
	@param [in] pszServerIp          系统连接IP
	@param [in] usServerPort         系统连接端口
	@param [in] pszLocalIp           本地IP
	@param [in] usLocalPort          本地端口	
	@param [in] events               回调事件列表
	@return 
	@see
	*/
	int MRPS_API MRPS_Initialize(const char* pszServerIp, unsigned short usServerPort, const char* pszLocalIp, unsigned short usLocalPort, PSYS_EVENTS events);

	/** 关闭API服务
	@return 
	@see
	*/
	int MRPS_API MRPS_Uninitialize();

	/** 设置心跳
	@param [in] iInterval          表示心跳时间间隔，单位：毫秒。
	@return 
	@par 
	*/
	int MRPS_API MRPS_SetHeartbeatInterval(int iInterval);

	/** 登录	
	@param [in] pszName                登录系统用户名
	@param [in] pszPassword            登录系统密码
	@param [in] pszNumber              录音服务器号码	
	@return 
	@see
	*/
	int MRPS_API MRPS_Login(const char* pszName, const char* pszPassword, const char* pszNumber);

	/** 登出	
	@return 
	*/
	int MRPS_API MRPS_Logout();

	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++API网管服务事件+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
	/*开启网管服务ACK事件结果枚举定义*/
	typedef enum OpenMGRResult
	{
		OPEN_MGR_SUCCESS = 0,	                ///< 成功
		OPEN_MGR_ERROR_UNKNOWN = -1,			  ///< 未知错误
		OPEN_MGR_ERROR_INVALID_LICENSE = -2,///< LICENSE非法
		OPEN_MGR_ERROR_NETWORK_ERR = -3,	 ///< 网络错误
		OPEN_MGR_ERROR_NO_PERMISSION = -4,  ///< 无权限
	}OpenMGRResult;

	/** 打开系统管理服务确认事件
	@param [in] result	        打开GPS服务确认事件结果
	@param [in] timeStamp	    时间戳

	@return 返回值的意义见 Result 开始的宏
	*/
	typedef int(*MRPS_MGR_OpenServiceAck_Evt)(OpenMGRResult result, time_t timeStamp);
	
	/*获取全网个人用户ACK事件结果枚举定义*/
	typedef enum GetUserInfoResult
	{
		GET_USER_INFO_SUCCESS = 0,	              ///<成功
		GET_USER_INFO_ERROR_UNKNOWN = -1,			///<未知错误
	}GetUserInfoResult;

	//用户信息结构定义
	typedef struct
	{
		int		iType;		//若为终端 0:无线终端  1:系统调度台 2：用户调度台 3：录音服务器 4：GPS服务器
		char	szNumber[Len32];
		char    szAlias[Len128];
		char    szDeviceNumber[Len64];
		char    szNodeCode[Len64];
	}USER, *PUSER;

	/** 获取全网个人用户信息确认事件
	@param [in] result	        获取结果
	@param [in] bEnd			是否最后一个包（true为结束、false没有结束）
	@param [in] puser			用户信息
	@param [in] iUserSize			用户信息数组可用长度
	@param [in] timeStamp      时间戳

	@return 返回值的意义见 Result 开始的宏
	*/
	typedef int(*MRPS_MGR_GetUserInfoAck_Evt)(GetUserInfoResult result, bool bEnd, PUSER puser, int iUserSize, time_t timeStamp);

	/*获取全网组用户ACK事件结果枚举定义*/
	typedef enum GetGroupInfoResult
	{
		GET_GROUP_INFO_SUCCESS = 0,	              ///<成功
		GET_GROUP_INFO_ERROR_UNKNOWN = -1,			///<未知错误
	}GetGroupInfoResult;	

	/** 获取全网组用户信息确认事件
	@param [in] result	        获取结果
	@param [in] bEnd			是否最后一个包（true为结束、false没有结束）
	@param [in] puser			用户信息
	@param [in] iSize			用户信息数组可用长度
	@param [in] timeStamp      时间戳

	@return 返回值的意义见 Result 开始的宏
	*/
	typedef int(*MRPS_MGR_GetGroupInfoAck_Evt)(GetGroupInfoResult result, bool bEnd, PUSER pgroup, int iSize, time_t timeStamp);

	/*获取人员信息ACK事件结果枚举定义*/
	typedef enum GetStaffInfoResult
	{
		GET_STAFF_INFO_SUCCESS = 0,	              ///< 成功
		GET_STAFF_INFO_ERROR_UNKNOWN = -1,			///< 未知错误
	}GetStaffInfoResult;

	/*人员信息*/
	typedef struct
	{
		int	            iNO;
		char		    szName[Len64];           //员工姓名
		char		    szPlateNum[Len32];       //车牌号
		char		    szStaffNum[Len32];       //警员编号
		char            szPost[Len64];           //职务
		char		    szWorkType[Len64];       //警种
		char   		    szUnitName[Len128];      //单位名称
		char		    szUnitCode[Len32];       //单位代码
		char      		szTelNum[Len32];         //手机号 
		char		    szNumber[Len32];         //个呼号
		char		    szUsetype[Len64];        //用途类型
		int		        iNumberType;             //终端类型 0：是手台 1：车台
		char		    szNodeCode[Len64];		 //组织编号
	}STAFF, *PSTAFF;

	/*查询权限内人员信息确认事件
	@param [in] result：	   结果码，详见GetStaffInfoResult定义
	@param [in] bEnd：	   是否最后一个包（true为结束、false没有结束）
	@param [in] pstaff：    人员信息
	@param [in] iSize：    人员信息数组可用长度
	@param [in] timeStamp：时间戳
	@return 返回值的意义见 Result 开始的宏
	*/
	typedef int(*MRPS_MGR_GetStaffInfoAck_Evt)(GetStaffInfoResult result, bool bEnd, PSTAFF pstaff, int iSize, time_t timeStamp);

	/*获取调度员权限内组织信息ACK事件结果枚举定义*/
	typedef enum GetLdsUserOrgInfoResult
	{
		GET_LDSUSER_ORG_INFO_SUCCESS = 0,	              ///< 成功
		GET_LDSUSER_ORG_INFO_LDS_NOT_EXIT = 1,			///< 调度台用户未找到
		GET_LDSUSER_ORG_INFO_TIMEOUT = 2,			///< 查询超时
	};

	/*组织信息结构定义*/
	typedef struct
	{
		char	szNodeName[Len64];   //名称
		char	szOrgCode[Len64];    //组织机构代码 
		char	szNodeCode[Len64];   //组织编号
	}ORG, *PORG;


	/*查询调度员所拥有权限的组织结构信息确认事件
	@param [in] result：	   结果码，详见GetLdsUserOrgInfoResult定义
	@param [in] pldsorg：    组织信息
	@param [in] length：    组织信息数组可用长度
	@param [in] time_stamp：时间戳
	@return 返回值的意义见 Result 开始的宏
	*/
	typedef int(*MRPS_MGR_GetOrgInfoAck_Evt)(GetLdsUserOrgInfoResult result, PORG porg, int iSize, time_t timeStamp);

	//系统管理事件原型
	typedef struct
	{
		MRPS_MGR_OpenServiceAck_Evt            mgr_open_service_ack;
		MRPS_MGR_GetUserInfoAck_Evt			mgr_get_user_info_ack;
		MRPS_MGR_GetGroupInfoAck_Evt			mgr_get_group_info_ack;
		MRPS_MGR_GetOrgInfoAck_Evt             mgr_get_org_info_ack;
		MRPS_MGR_GetStaffInfoAck_Evt           mgr_get_staff_info_ack;
		
	} MGR_EVENTS, *PMGR_EVENTS;


	/** 打开系统管理服务
	@param [in] mgr_events	        打开系统管理服务	

	@return 
	*/
	int MRPS_API MRPS_Mgr_OpenService(PMGR_EVENTS mgr_events);

	/** 关闭系统管理服务
	@return 
	*/
	int MRPS_API MRPS_Mgr_CloseService();

	/*号码类型*/
	enum NumberType
	{
		NUMBER_TYPE_INDIVIDUAL = 1,                   ///<个号
		NUMBER_TYPE_GROUP = 2,                        ///<组号
		NUMBER_TYPE_EXTERNAL = 3,                     ///<外线
		NUMBER_TYPE_BROADCAST = 4,	                  ///<全网
		NUMBER_TYPE_WORKSTATION = 5,                  ///<工作站号码
		NUMBER_TYPE_FLEET = 6,	                      ///<fleet号码
		NUMBER_TYPE_DGNAGROUP = 7,	                  ///DGNA动态组
		NUMBER_TYPE_OTAPGROUP = 8,	                  ///OTAP动态组
		NUMBER_TYPE_GPSSERVER = 9,                    //GPS服务器
		NUMBER_TYPE_RECORDSERVER = 10,                //录音服务器
		NUMBER_TYPE_MPTGATEWAY = 11,                  //MPT网关
	};

	/*号码*/
	typedef struct CallNumber
	{
		char       szNumber[Len32];		      ///<号码
		char       szGateway[Len32];	      ///<网关 拨打外网需要
		NumberType type;	                          ///<号码类型
	}CallNumber;

	/** 查看全网个人用户信息
	@return 
	*/
	int MRPS_API MRPS_Mgr_GetUserInfo(CallNumber src);

	/** 查看全网组用户信息
	@return 
	*/
	int MRPS_API MRPS_Mgr_GetGroupInfo(CallNumber src);

	/*发送查询本用户可查询的组织信息的请求，用户为最后一次注册的用户，如最后一次注册失败则查询不到结果。
	@return 
	*/
	int MRPS_API MRPS_Mgr_GetOrgInfo(CallNumber src);

	/*发送查询本用户可查询的人员信息的请求，用户为最后一次注册的用户，如最后一次注册失败则查询不到结果。
	@return 
	*/
	int MRPS_API MRPS_Mgr_GetStaffInfo(CallNumber src);

	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++API全网录音服务事件+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	//全网录音服务事件 
	
	/*打开全网录音服务ACK事件结果枚举定义*/
	typedef enum OpenRSResult
	{
		OPEN_RS_SUCCESS = 0,	            ///< 成功
		OPEN_RS_ERROR_UNKNOWN = -1,			///< 未知错误
		OPEN_RS_ERROR_INVALID_LICENSE = -2, ///< LICENSE非法
		OPEN_RS_ERROR_NETWORK_ERR = -3,		///< 网络错误
		OPEN_RS_ERROR_NO_PERMISSION = -4,   ///< 无权限
		OPEN_RS_ERROR_NO_RES = -5,   ///< 全网录音服务超限（目前PDT集群系统最多支持两个全网录音服务器）
	}OpenRSResult;
	/** 打开全网录音服务确认事件
	@param [in]   result				结果
	@param [in]   time_stamp;			时间戳

	@return 返回值的意义见 Result 开始的宏
	*/
	typedef Result(*MRPS_RS_OpenServiceAck_Evt)(OpenRSResult result,
		time_t       timeStamp);
	

	/*定制录音ACK事件结果枚举定义*/
	typedef enum StartRecordResult
	{
		StartRecord_Success = 0,                      ///<成功
		StartRecord_Fail = 1,                         ///<部分失败
		StartRecord_ALLFail = 2,                      ///<全部失败
	}StartRecordResult;

	/** 开始订阅录音确认事件
	@param [in]   result		    结果
	@param [in]   pArrNumber	    开始订阅录音的对象数组（成功对象数组）
	@param [in]   iSize;	        数组组员数（成功对象的个数）

	@return 
	*/
	typedef int(*MRPS_RS_StartRecordAck_Evt)(StartRecordResult result, const CallNumber* pArrNumber, int iSize);

	/*取消定制录音ACK事件结果枚举定义*/
	typedef enum StopRecordResult
	{
		StopRecord_Success = 0,                      ///<成功
		StopRecord_Fail = 1,                         ///<部分失败
		StopRecord_ALLFail = 2,                      ///<全部失败
	}StopRecordResult;

	/** 停止订阅录音确认事件
	@param [in]   result		    结果
	@param [in]   pArrNumber	    停止订阅录音的对象数组（成功对象数组）
	@param [in]   iSize;	        数组组员数（成功对象的个数）

	@return 
	*/
	typedef int(*MRPS_RS_StopRecordAck_Evt)(StopRecordResult result, const CallNumber* pArrNumber, int iSize);

	typedef unsigned long	  CALL_ID;                                    ///<呼叫ID类型 

	typedef enum CallType
	{
		CALL_TYPE_GROUP_CALL = 0,                     ///<组呼
		CALL_TYPE_INDIVIDUAL_CALL = 1,                ///<单呼
		CALL_TYPE_BROADCAST_CALL = 2,                 ///<广播呼
		CALL_TYPE_SYSTEM_CALL = 3,                    ///<系统全呼
		CALL_TYPE_EXTERNAL_CALL = 4,                  ///<外部呼叫:PSAN/PABX,MSISDN	
		CALL_TYPE_STATION_CALL = 5,                   // 基站全呼
		CALL_TYPE_LOCAL_CALL = 6,                     // 本地全呼
		CALL_TYPE_EMERGENCY_STATION_CALL = 7,         // 紧急基站全呼
		CALL_TYPE_EMERGENCY_LOCAL_CALL = 8,           // 紧急本地全呼
		CALL_TYPE_EMERGENCY_WHOLENET_CALL = 9,        // 紧急全网全呼
	}CallType;

	/** 呼叫优先级: 0默认等级 1-10 普通级 11-14优先级 15 紧急呼叫*/
	typedef int CallPriority;

	/*加密类型枚举定义*/
	typedef enum EncryptType
	{
		CALL_ENCRYPT_NONE = 0,                        ///不加密呼叫
		CALL_ENCRYPT_SOFT = 1,                        ///软加密呼叫
		CALL_ENCRYPT_HARD = 2,                        ///硬加密呼叫
		CALL_ENCRYPT_MAX
	}EncryptType;

	/*呼叫发起ACK事件结果枚举定义*/
	typedef enum SetupCallResult
	{
		SETUP_CALL_SUCCESS = 0,	                      ///< 成功
		SETUP_CALL_ERROR_UNKNOWN = -1,			      ///< 未知错误
		SETUP_CALL_ERROR_CC_SERVICE_DONT_OPEN = -2,   ///< 呼叫控制服务未开启
		SETUP_CALL_ERROR_HAVE_NOT_LOGIN = -3,	      ///<  未登录
		SETUP_CALL_ERROR_FAIL_TO_SETUP_CALL = -4,     ///< 呼叫失败
	}SetupCallResult;

	/** 呼叫发起事件
	@param [in]   callId			呼叫建立后的呼叫id
	@param [in]   caller			主叫号码
	@param [in]   called			被叫号码
	@param [in]   calltype			呼叫类型	
	@param [in]   priority			呼叫优先级 ,数字大的级别高
	@param [in]   duplexmode		双工模式.  true为全双工;false为半双工
	@param [in]   encryption        加密呼叫的类型
	@param [in]   result			结果
	@param [in]   slotsCode			基站时隙编码
	@param [in]   timeStamp  		时间戳

	@return 
	*/
	typedef int(*MRPS_RS_SetupCallAck_Evt)(CALL_ID          callId,
											const CallNumber& caller,
											const CallNumber& called,
											CallType          calltype,
											CallPriority      priority,											
											bool              bDuplexmode,
											EncryptType       encryptionmode,
											SetupCallResult   result,											
											time_t            timeStamp);


	/** 呼叫连接事件
	@param [in]   callId			呼叫建立后的呼叫id
	@param [in]   time_stamp;		时间戳

	@return 
	@note
	
	*/
	typedef int(*MRPS_RS_Connected_Evt)(CALL_ID callId, time_t timeStamp);



	/*挂断呼叫ACK事件结果枚举定义*/
	typedef enum CallDisconnectReason
	{
		UNKNOWN = 100,                          ///< 未知原因
		HANG_UP,                                ///< 用户请求挂断
		CC_SERVICE_DONT_OPEN,                   ///< 呼叫控制服务未开启
		HAVE_NOT_LOGIN,                         ///< 未登录
		FAIL_TO_SETUP_CALL,                     ///< 呼叫失败
		NO_PERMISSION,                          ///< 无权限
		INVALID_SSI,                            ///< 该号码不存在
		OTHER_PARTY_BUSY,                       ///< 对方忙
		OTHER_PARTY_REFUSE,                     ///< 对方拒绝
		OTHER_PARTY_DONT_SUPPORT_ENCRYPTION,    ///< 对方不支持加密
		SYSTEM_CC_BUSY,                         ///< 系统呼叫模块忙
		CALL_TIMEOUT,                           ///< 呼叫超时
	}CallDisconnectReason;

	/** 呼叫挂断事件
	@param [in]   call_id			    呼叫建立后的呼叫id
	@param [in]   reason				呼叫断开原因
	@param [in]   timeStamp			    时间戳

	@return 
	*/
	typedef int(*MRPS_RS_Disconnected_Evt)(CALL_ID callId, CallDisconnectReason reason, time_t timeStamp);


	/** 话权变更事件
	@param [in]   callId		    呼叫id
	@param [in]   speaker		    获取通话权的号码
	@param [in]   timeStamp 	    时间戳

	@return 
	*/
	typedef int(*MRPS_RS_TxGranted_Evt)(CALL_ID callId, const CallNumber& speaker, time_t timeStamp);

	/** 话权释放事件
	@param [in]   callId		    呼叫id
	@param [in]   timeStamp	        时间戳
	@return 
	*/
	typedef int(*MRPS_RS_TxCease_Evt)(CALL_ID callId, time_t timeStamp);

	/// 呼叫的语音RTP资源参数
	typedef struct  Voice_Resources_Rtp
	{
		char szIp[32];		    ///<rtp的ip地址
		unsigned short usPort;	///<rtp的端口号		
	}Voice_Resources_Rtp;

	/** 语音资源事件
	@param [in]   callId		    呼叫id
	@param [in]   pRtpResource		    语音来源方（全双工时语音两路，建议主叫语音按左声道写录音文件，被叫语音按右声道写录音文件。）
	@param [in]   iRtpCount			RTP源个数
	@param [in]   timeStamp	        时间戳
	@return 
	*/
	typedef int(*MRPS_RS_RtpResource_Evt)(CALL_ID callId, const Voice_Resources_Rtp* pRtpResource, int iRtpCount, time_t timeStamp);


	enum Rs_SdsType
	{

	};

	/** 接收文本短信事件
	@param [in] strSdsId			短消息的唯一标志号，用于区分短消息用 (Tetra系统由系统产生，PDT可以采取用不断递增)	
	@param [in] sender				发送者
	@param [in] receiver			接收者
	@param [in] msgType			    消息类型
	@param [in] msgMode				短数据发送模式
	@param [in] strMsgData			内容	
	@param [in] timeStamp		    呼叫保持产生的时间 (从1970-1-1 0:0:0 开始流逝的秒数)

	@return 返回值

	@see SDS_SendText
	*/
	typedef int(*MRPS_RS_Sds_Evt)(const std::string& strSdsId,
		                           const CallNumber&  sender,
		                           const CallNumber&  receiver,
								   Rs_SdsType         msgType,
								   EncryptType        encrypt,
								   int                msgMode,
								   const std::string& strMsgData,
								   const std::string& stdCode,
								   const std::string& strUrl,
								   time_t             timeStamp);


	/** 登记，去登记事件
	@param [in]   target	            监控的对象
	@param [in]   iRegistType		    注册类型
	@param [in]   iUpdatePeriod				注册周期
	@param [in]   iUpdatePeriod				集群能力
	@param [in]   iUpdatePeriod				音频编解码能力
	@param [in]   iUpdatePeriod				视频编解码能力
	@param [in]   iStunStatus				遥晕状态
	@param [in]   time_stamp;			时间戳

	@return 返回值的意义见 Result 开始的宏

	*/
	typedef int(*MRPS_RS_Register_Evt)(const CallNumber& target, int  iRegistType, int iUpdatePeriod, int iStunStatus, time_t timeStamp);

	//全网录音服务回调函数原型
	//录音模块初始函数原型，上层需要在初始化Api服务成功之后调用
	typedef struct
	{		
		MRPS_RS_OpenServiceAck_Evt          rs_openservice_ack;
		MRPS_RS_StartRecordAck_Evt			rs_startrecord_ack;
		MRPS_RS_StopRecordAck_Evt			rs_stoprecord_ack;
		MRPS_RS_SetupCallAck_Evt			rs_setupcall;
		MRPS_RS_Connected_Evt				rs_connected;
		MRPS_RS_Disconnected_Evt			rs_disconnected;
		MRPS_RS_TxGranted_Evt				rs_txgranted;
		MRPS_RS_TxCease_Evt			        rs_txcease;
		MRPS_RS_RtpResource_Evt			    rs_voiceresource;
		MRPS_RS_Sds_Evt                     rs_sds_evt;
		MRPS_RS_Register_Evt                rs_register_evt;
	} RS_EVENTS, *PRS_EVENTS;


	/** 打开全网录音服务
	@param [in] cc_events 全网录音服务回调函数原型
	@return 
	*/
	int MRPS_API MRPS_RS_OpenService(PRS_EVENTS rs_events);

	/** 关闭全网录音服务
	@return 
	*/
	int MRPS_API MRPS_RS_CloseService();

	/** 开始录音订阅
	@param [in] pArrNumber      开始录音订阅对象数组
	@param [in] iSize           数组组成员个数
	@return 
	@note
	成员个数单次最大为32个
	*/
	int MRPS_API MRPS_RS_StartRecord(const CallNumber* pArrNumber, int iSize);

	/** 结束录音订阅
	@param [in] pArrNumber      结束录音订阅对象数组
	@param [in] iSize           数组组成员个数

	@return 
	@note
	成员个数单次最大为32个
	*/
	int MRPS_API MRPS_RS_StopRecord(const CallNumber* pArrNumber, int iSize);

	
	/** 结束录音订阅
	@param [in] callId         呼叫唯一标识
	@param [in] pRtpResource   接收RTP数组
	@param [in] iRtpCount      接收RTP个数

	@return
	@note	
	*/
	int MRPS_API  MRPS_RS_SetRtpResources(CALL_ID callId, const Voice_Resources_Rtp* pRtpResource, int iRtpCount);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif