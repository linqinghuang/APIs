/**
HYTERA_LTE_RS_API.h
LTE¼��¼��API�ӿ�
�ο��ĵ�����BWT-3800_������-¼��¼��.doc��

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
	typedef int(*MRPS_InitializeAck_Evt)(InitResult result, time_t time_stamp);



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
	typedef int(*MRPS_Heartbeat_Evt)(HeartbeatResult result, time_t  time_stamp);

	/*��¼ACK�¼����ö�ٶ���*/
	typedef enum LoginResult
	{
		LOGIN_SUCCESS = 0,							 ///< �ɹ�
		LOGIN_ERROR_UNKNOWN = -1,					 ///< δ֪����
		LOGIN_ERROR_USER_ALREADY_LOGINED = -2,       ///< �û��ѵ�¼
		LOGIN_ERROR_INVALID_USER_OR_PASSWORD = -3,   ///< �û��������������
		LOGIN_ERROR_INVALID_SSI = -4,			     ///< SSI���벻����
		LOGIN_ERROR_INVALID_SERVICE = -5		     ///< ϵͳ���񲻿���
	}LoginResult;

	/** ��¼�ص�ȷ���¼�	
	@param [in] name     ¼���������û���
	@param [in] id       ¼���������ĺ���
	@param [in] result   ��� �������ݼ�  LoginResult
	@param [in] time_t   ʱ���
	@return 
	*/
	typedef int(*MRPS_LoginAck_Evt)(const char* pszName, const char* pszNumber, LoginResult result, time_t time_stamp);


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
	typedef int(*MRPS_LogoutAck_Evt)(const char* pszName, const char* pszNumber, LogoutResult result, time_t time_stamp);

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
	}SystemEvent;

	/** ϵͳ�¼��ص��¼�
	@param [in] event    ϵͳ�¼�	
	@param [in] time_t   ʱ���
	@return 
	@see
	*/
	typedef int(*MRPS_System_Evt)(SystemEvent event, time_t time_stamp);

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
	typedef int(*MRPS_Log_Evt)(const char* pszLogInfo, const char* pszModule, RsApi_LogLevel level);

	//APIϵͳ����ص��¼�ԭ��
	typedef struct
	{
		MRPS_InitializeAck_Evt		rs_initialize_ack;     ///< ϵͳ��ʼ��ȷ���¼�
		MRPS_Heartbeat_Evt			rs_heartbeat_ack;      ///< ϵͳ�����¼�
		MRPS_LoginAck_Evt			rs_login_ack;          ///< ��¼�ص�ȷ���¼�
		MRPS_LogoutAck_Evt			rs_logout_ack;         ///< �ǳ��ص�ȷ���¼�
		MRPS_System_Evt			    rs_system_event;       ///< ϵͳ�ص��¼�
		MRPS_Log_Evt                rs_log_event;
	} SYS_EVENTS, *PSYS_EVENTS;

	/** ��ʼ��API����
	@param [in] pszServerIp          ϵͳ����IP
	@param [in] usServerPort         ϵͳ���Ӷ˿�
	@param [in] pszLocalIp           ����IP
	@param [in] usLocalPort          ���ض˿�	
	@param [in] events               �ص��¼��б�
	@return 
	@see
	*/
	int MRPS_API MRPS_Initialize(const char* pszServerIp, unsigned short usServerPort, const char* pszLocalIp, unsigned short usLocalPort, PSYS_EVENTS events);

	/** �ر�API����
	@return 
	@see
	*/
	int MRPS_API MRPS_Uninitialize();

	/** ��������
	@param [in] iInterval          ��ʾ����ʱ��������λ�����롣
	@return 
	@par 
	*/
	int MRPS_API MRPS_SetHeartbeatInterval(int iInterval);

	/** ��¼	
	@param [in] pszName                ��¼ϵͳ�û���
	@param [in] pszPassword            ��¼ϵͳ����
	@param [in] pszNumber              ¼������������	
	@return 
	@see
	*/
	int MRPS_API MRPS_Login(const char* pszName, const char* pszPassword, const char* pszNumber);

	/** �ǳ�	
	@return 
	*/
	int MRPS_API MRPS_Logout();

	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++API���ܷ����¼�+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	
	/*�������ܷ���ACK�¼����ö�ٶ���*/
	typedef enum OpenMGRResult
	{
		OPEN_MGR_SUCCESS = 0,	                ///< �ɹ�
		OPEN_MGR_ERROR_UNKNOWN = -1,			  ///< δ֪����
		OPEN_MGR_ERROR_INVALID_LICENSE = -2,///< LICENSE�Ƿ�
		OPEN_MGR_ERROR_NETWORK_ERR = -3,	 ///< �������
		OPEN_MGR_ERROR_NO_PERMISSION = -4,  ///< ��Ȩ��
	}OpenMGRResult;

	/** ��ϵͳ�������ȷ���¼�
	@param [in] result	        ��GPS����ȷ���¼����
	@param [in] timeStamp	    ʱ���

	@return ����ֵ������� Result ��ʼ�ĺ�
	*/
	typedef int(*MRPS_MGR_OpenServiceAck_Evt)(OpenMGRResult result, time_t timeStamp);
	
	/*��ȡȫ�������û�ACK�¼����ö�ٶ���*/
	typedef enum GetUserInfoResult
	{
		GET_USER_INFO_SUCCESS = 0,	              ///<�ɹ�
		GET_USER_INFO_ERROR_UNKNOWN = -1,			///<δ֪����
	}GetUserInfoResult;

	//�û���Ϣ�ṹ����
	typedef struct
	{
		int		iType;		//��Ϊ�ն� 0:�����ն�  1:ϵͳ����̨ 2���û�����̨ 3��¼�������� 4��GPS������
		char	szNumber[Len32];
		char    szAlias[Len128];
		char    szDeviceNumber[Len64];
		char    szNodeCode[Len64];
	}USER, *PUSER;

	/** ��ȡȫ�������û���Ϣȷ���¼�
	@param [in] result	        ��ȡ���
	@param [in] bEnd			�Ƿ����һ������trueΪ������falseû�н�����
	@param [in] puser			�û���Ϣ
	@param [in] iUserSize			�û���Ϣ������ó���
	@param [in] timeStamp      ʱ���

	@return ����ֵ������� Result ��ʼ�ĺ�
	*/
	typedef int(*MRPS_MGR_GetUserInfoAck_Evt)(GetUserInfoResult result, bool bEnd, PUSER puser, int iUserSize, time_t timeStamp);

	/*��ȡȫ�����û�ACK�¼����ö�ٶ���*/
	typedef enum GetGroupInfoResult
	{
		GET_GROUP_INFO_SUCCESS = 0,	              ///<�ɹ�
		GET_GROUP_INFO_ERROR_UNKNOWN = -1,			///<δ֪����
	}GetGroupInfoResult;	

	/** ��ȡȫ�����û���Ϣȷ���¼�
	@param [in] result	        ��ȡ���
	@param [in] bEnd			�Ƿ����һ������trueΪ������falseû�н�����
	@param [in] puser			�û���Ϣ
	@param [in] iSize			�û���Ϣ������ó���
	@param [in] timeStamp      ʱ���

	@return ����ֵ������� Result ��ʼ�ĺ�
	*/
	typedef int(*MRPS_MGR_GetGroupInfoAck_Evt)(GetGroupInfoResult result, bool bEnd, PUSER pgroup, int iSize, time_t timeStamp);

	/*��ȡ��Ա��ϢACK�¼����ö�ٶ���*/
	typedef enum GetStaffInfoResult
	{
		GET_STAFF_INFO_SUCCESS = 0,	              ///< �ɹ�
		GET_STAFF_INFO_ERROR_UNKNOWN = -1,			///< δ֪����
	}GetStaffInfoResult;

	/*��Ա��Ϣ*/
	typedef struct
	{
		int	            iNO;
		char		    szName[Len64];           //Ա������
		char		    szPlateNum[Len32];       //���ƺ�
		char		    szStaffNum[Len32];       //��Ա���
		char            szPost[Len64];           //ְ��
		char		    szWorkType[Len64];       //����
		char   		    szUnitName[Len128];      //��λ����
		char		    szUnitCode[Len32];       //��λ����
		char      		szTelNum[Len32];         //�ֻ��� 
		char		    szNumber[Len32];         //������
		char		    szUsetype[Len64];        //��;����
		int		        iNumberType;             //�ն����� 0������̨ 1����̨
		char		    szNodeCode[Len64];		 //��֯���
	}STAFF, *PSTAFF;

	/*��ѯȨ������Ա��Ϣȷ���¼�
	@param [in] result��	   ����룬���GetStaffInfoResult����
	@param [in] bEnd��	   �Ƿ����һ������trueΪ������falseû�н�����
	@param [in] pstaff��    ��Ա��Ϣ
	@param [in] iSize��    ��Ա��Ϣ������ó���
	@param [in] timeStamp��ʱ���
	@return ����ֵ������� Result ��ʼ�ĺ�
	*/
	typedef int(*MRPS_MGR_GetStaffInfoAck_Evt)(GetStaffInfoResult result, bool bEnd, PSTAFF pstaff, int iSize, time_t timeStamp);

	/*��ȡ����ԱȨ������֯��ϢACK�¼����ö�ٶ���*/
	typedef enum GetLdsUserOrgInfoResult
	{
		GET_LDSUSER_ORG_INFO_SUCCESS = 0,	              ///< �ɹ�
		GET_LDSUSER_ORG_INFO_LDS_NOT_EXIT = 1,			///< ����̨�û�δ�ҵ�
		GET_LDSUSER_ORG_INFO_TIMEOUT = 2,			///< ��ѯ��ʱ
	};

	/*��֯��Ϣ�ṹ����*/
	typedef struct
	{
		char	szNodeName[Len64];   //����
		char	szOrgCode[Len64];    //��֯�������� 
		char	szNodeCode[Len64];   //��֯���
	}ORG, *PORG;


	/*��ѯ����Ա��ӵ��Ȩ�޵���֯�ṹ��Ϣȷ���¼�
	@param [in] result��	   ����룬���GetLdsUserOrgInfoResult����
	@param [in] pldsorg��    ��֯��Ϣ
	@param [in] length��    ��֯��Ϣ������ó���
	@param [in] time_stamp��ʱ���
	@return ����ֵ������� Result ��ʼ�ĺ�
	*/
	typedef int(*MRPS_MGR_GetOrgInfoAck_Evt)(GetLdsUserOrgInfoResult result, PORG porg, int iSize, time_t timeStamp);

	//ϵͳ�����¼�ԭ��
	typedef struct
	{
		MRPS_MGR_OpenServiceAck_Evt            mgr_open_service_ack;
		MRPS_MGR_GetUserInfoAck_Evt			mgr_get_user_info_ack;
		MRPS_MGR_GetGroupInfoAck_Evt			mgr_get_group_info_ack;
		MRPS_MGR_GetOrgInfoAck_Evt             mgr_get_org_info_ack;
		MRPS_MGR_GetStaffInfoAck_Evt           mgr_get_staff_info_ack;
		
	} MGR_EVENTS, *PMGR_EVENTS;


	/** ��ϵͳ�������
	@param [in] mgr_events	        ��ϵͳ�������	

	@return 
	*/
	int MRPS_API MRPS_Mgr_OpenService(PMGR_EVENTS mgr_events);

	/** �ر�ϵͳ�������
	@return 
	*/
	int MRPS_API MRPS_Mgr_CloseService();

	/*��������*/
	enum NumberType
	{
		NUMBER_TYPE_INDIVIDUAL = 1,                   ///<����
		NUMBER_TYPE_GROUP = 2,                        ///<���
		NUMBER_TYPE_EXTERNAL = 3,                     ///<����
		NUMBER_TYPE_BROADCAST = 4,	                  ///<ȫ��
		NUMBER_TYPE_WORKSTATION = 5,                  ///<����վ����
		NUMBER_TYPE_FLEET = 6,	                      ///<fleet����
		NUMBER_TYPE_DGNAGROUP = 7,	                  ///DGNA��̬��
		NUMBER_TYPE_OTAPGROUP = 8,	                  ///OTAP��̬��
		NUMBER_TYPE_GPSSERVER = 9,                    //GPS������
		NUMBER_TYPE_RECORDSERVER = 10,                //¼��������
		NUMBER_TYPE_MPTGATEWAY = 11,                  //MPT����
	};

	/*����*/
	typedef struct CallNumber
	{
		char       szNumber[Len32];		      ///<����
		char       szGateway[Len32];	      ///<���� ����������Ҫ
		NumberType type;	                          ///<��������
	}CallNumber;

	/** �鿴ȫ�������û���Ϣ
	@return 
	*/
	int MRPS_API MRPS_Mgr_GetUserInfo(CallNumber src);

	/** �鿴ȫ�����û���Ϣ
	@return 
	*/
	int MRPS_API MRPS_Mgr_GetGroupInfo(CallNumber src);

	/*���Ͳ�ѯ���û��ɲ�ѯ����֯��Ϣ�������û�Ϊ���һ��ע����û��������һ��ע��ʧ�����ѯ���������
	@return 
	*/
	int MRPS_API MRPS_Mgr_GetOrgInfo(CallNumber src);

	/*���Ͳ�ѯ���û��ɲ�ѯ����Ա��Ϣ�������û�Ϊ���һ��ע����û��������һ��ע��ʧ�����ѯ���������
	@return 
	*/
	int MRPS_API MRPS_Mgr_GetStaffInfo(CallNumber src);

	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++APIȫ��¼�������¼�+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	//ȫ��¼�������¼� 
	
	/*��ȫ��¼������ACK�¼����ö�ٶ���*/
	typedef enum OpenRSResult
	{
		OPEN_RS_SUCCESS = 0,	            ///< �ɹ�
		OPEN_RS_ERROR_UNKNOWN = -1,			///< δ֪����
		OPEN_RS_ERROR_INVALID_LICENSE = -2, ///< LICENSE�Ƿ�
		OPEN_RS_ERROR_NETWORK_ERR = -3,		///< �������
		OPEN_RS_ERROR_NO_PERMISSION = -4,   ///< ��Ȩ��
		OPEN_RS_ERROR_NO_RES = -5,   ///< ȫ��¼�������ޣ�ĿǰPDT��Ⱥϵͳ���֧������ȫ��¼����������
	}OpenRSResult;
	/** ��ȫ��¼������ȷ���¼�
	@param [in]   result				���
	@param [in]   time_stamp;			ʱ���

	@return ����ֵ������� Result ��ʼ�ĺ�
	*/
	typedef Result(*MRPS_RS_OpenServiceAck_Evt)(OpenRSResult result,
		time_t       timeStamp);
	

	/*����¼��ACK�¼����ö�ٶ���*/
	typedef enum StartRecordResult
	{
		StartRecord_Success = 0,                      ///<�ɹ�
		StartRecord_Fail = 1,                         ///<����ʧ��
		StartRecord_ALLFail = 2,                      ///<ȫ��ʧ��
	}StartRecordResult;

	/** ��ʼ����¼��ȷ���¼�
	@param [in]   result		    ���
	@param [in]   pArrNumber	    ��ʼ����¼���Ķ������飨�ɹ��������飩
	@param [in]   iSize;	        ������Ա�����ɹ�����ĸ�����

	@return 
	*/
	typedef int(*MRPS_RS_StartRecordAck_Evt)(StartRecordResult result, const CallNumber* pArrNumber, int iSize);

	/*ȡ������¼��ACK�¼����ö�ٶ���*/
	typedef enum StopRecordResult
	{
		StopRecord_Success = 0,                      ///<�ɹ�
		StopRecord_Fail = 1,                         ///<����ʧ��
		StopRecord_ALLFail = 2,                      ///<ȫ��ʧ��
	}StopRecordResult;

	/** ֹͣ����¼��ȷ���¼�
	@param [in]   result		    ���
	@param [in]   pArrNumber	    ֹͣ����¼���Ķ������飨�ɹ��������飩
	@param [in]   iSize;	        ������Ա�����ɹ�����ĸ�����

	@return 
	*/
	typedef int(*MRPS_RS_StopRecordAck_Evt)(StopRecordResult result, const CallNumber* pArrNumber, int iSize);

	typedef unsigned long	  CALL_ID;                                    ///<����ID���� 

	typedef enum CallType
	{
		CALL_TYPE_GROUP_CALL = 0,                     ///<���
		CALL_TYPE_INDIVIDUAL_CALL = 1,                ///<����
		CALL_TYPE_BROADCAST_CALL = 2,                 ///<�㲥��
		CALL_TYPE_SYSTEM_CALL = 3,                    ///<ϵͳȫ��
		CALL_TYPE_EXTERNAL_CALL = 4,                  ///<�ⲿ����:PSAN/PABX,MSISDN	
		CALL_TYPE_STATION_CALL = 5,                   // ��վȫ��
		CALL_TYPE_LOCAL_CALL = 6,                     // ����ȫ��
		CALL_TYPE_EMERGENCY_STATION_CALL = 7,         // ������վȫ��
		CALL_TYPE_EMERGENCY_LOCAL_CALL = 8,           // ��������ȫ��
		CALL_TYPE_EMERGENCY_WHOLENET_CALL = 9,        // ����ȫ��ȫ��
	}CallType;

	/** �������ȼ�: 0Ĭ�ϵȼ� 1-10 ��ͨ�� 11-14���ȼ� 15 ��������*/
	typedef int CallPriority;

	/*��������ö�ٶ���*/
	typedef enum EncryptType
	{
		CALL_ENCRYPT_NONE = 0,                        ///�����ܺ���
		CALL_ENCRYPT_SOFT = 1,                        ///����ܺ���
		CALL_ENCRYPT_HARD = 2,                        ///Ӳ���ܺ���
		CALL_ENCRYPT_MAX
	}EncryptType;

	/*���з���ACK�¼����ö�ٶ���*/
	typedef enum SetupCallResult
	{
		SETUP_CALL_SUCCESS = 0,	                      ///< �ɹ�
		SETUP_CALL_ERROR_UNKNOWN = -1,			      ///< δ֪����
		SETUP_CALL_ERROR_CC_SERVICE_DONT_OPEN = -2,   ///< ���п��Ʒ���δ����
		SETUP_CALL_ERROR_HAVE_NOT_LOGIN = -3,	      ///<  δ��¼
		SETUP_CALL_ERROR_FAIL_TO_SETUP_CALL = -4,     ///< ����ʧ��
	}SetupCallResult;

	/** ���з����¼�
	@param [in]   callId			���н�����ĺ���id
	@param [in]   caller			���к���
	@param [in]   called			���к���
	@param [in]   calltype			��������	
	@param [in]   priority			�������ȼ� ,���ִ�ļ����
	@param [in]   duplexmode		˫��ģʽ.  trueΪȫ˫��;falseΪ��˫��
	@param [in]   encryption        ���ܺ��е�����
	@param [in]   result			���
	@param [in]   slotsCode			��վʱ϶����
	@param [in]   timeStamp  		ʱ���

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


	/** ���������¼�
	@param [in]   callId			���н�����ĺ���id
	@param [in]   time_stamp;		ʱ���

	@return 
	@note
	
	*/
	typedef int(*MRPS_RS_Connected_Evt)(CALL_ID callId, time_t timeStamp);



	/*�ҶϺ���ACK�¼����ö�ٶ���*/
	typedef enum CallDisconnectReason
	{
		UNKNOWN = 100,                          ///< δ֪ԭ��
		HANG_UP,                                ///< �û�����Ҷ�
		CC_SERVICE_DONT_OPEN,                   ///< ���п��Ʒ���δ����
		HAVE_NOT_LOGIN,                         ///< δ��¼
		FAIL_TO_SETUP_CALL,                     ///< ����ʧ��
		NO_PERMISSION,                          ///< ��Ȩ��
		INVALID_SSI,                            ///< �ú��벻����
		OTHER_PARTY_BUSY,                       ///< �Է�æ
		OTHER_PARTY_REFUSE,                     ///< �Է��ܾ�
		OTHER_PARTY_DONT_SUPPORT_ENCRYPTION,    ///< �Է���֧�ּ���
		SYSTEM_CC_BUSY,                         ///< ϵͳ����ģ��æ
		CALL_TIMEOUT,                           ///< ���г�ʱ
	}CallDisconnectReason;

	/** ���йҶ��¼�
	@param [in]   call_id			    ���н�����ĺ���id
	@param [in]   reason				���жϿ�ԭ��
	@param [in]   timeStamp			    ʱ���

	@return 
	*/
	typedef int(*MRPS_RS_Disconnected_Evt)(CALL_ID callId, CallDisconnectReason reason, time_t timeStamp);


	/** ��Ȩ����¼�
	@param [in]   callId		    ����id
	@param [in]   speaker		    ��ȡͨ��Ȩ�ĺ���
	@param [in]   timeStamp 	    ʱ���

	@return 
	*/
	typedef int(*MRPS_RS_TxGranted_Evt)(CALL_ID callId, const CallNumber& speaker, time_t timeStamp);

	/** ��Ȩ�ͷ��¼�
	@param [in]   callId		    ����id
	@param [in]   timeStamp	        ʱ���
	@return 
	*/
	typedef int(*MRPS_RS_TxCease_Evt)(CALL_ID callId, time_t timeStamp);

	/// ���е�����RTP��Դ����
	typedef struct  Voice_Resources_Rtp
	{
		char szIp[32];		    ///<rtp��ip��ַ
		unsigned short usPort;	///<rtp�Ķ˿ں�		
	}Voice_Resources_Rtp;

	/** ������Դ�¼�
	@param [in]   callId		    ����id
	@param [in]   pRtpResource		    ������Դ����ȫ˫��ʱ������·����������������������д¼���ļ�������������������д¼���ļ�����
	@param [in]   iRtpCount			RTPԴ����
	@param [in]   timeStamp	        ʱ���
	@return 
	*/
	typedef int(*MRPS_RS_RtpResource_Evt)(CALL_ID callId, const Voice_Resources_Rtp* pRtpResource, int iRtpCount, time_t timeStamp);


	enum Rs_SdsType
	{

	};

	/** �����ı������¼�
	@param [in] strSdsId			����Ϣ��Ψһ��־�ţ��������ֶ���Ϣ�� (Tetraϵͳ��ϵͳ������PDT���Բ�ȡ�ò��ϵ���)	
	@param [in] sender				������
	@param [in] receiver			������
	@param [in] msgType			    ��Ϣ����
	@param [in] msgMode				�����ݷ���ģʽ
	@param [in] strMsgData			����	
	@param [in] timeStamp		    ���б��ֲ�����ʱ�� (��1970-1-1 0:0:0 ��ʼ���ŵ�����)

	@return ����ֵ

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


	/** �Ǽǣ�ȥ�Ǽ��¼�
	@param [in]   target	            ��صĶ���
	@param [in]   iRegistType		    ע������
	@param [in]   iUpdatePeriod				ע������
	@param [in]   iUpdatePeriod				��Ⱥ����
	@param [in]   iUpdatePeriod				��Ƶ���������
	@param [in]   iUpdatePeriod				��Ƶ���������
	@param [in]   iStunStatus				ң��״̬
	@param [in]   time_stamp;			ʱ���

	@return ����ֵ������� Result ��ʼ�ĺ�

	*/
	typedef int(*MRPS_RS_Register_Evt)(const CallNumber& target, int  iRegistType, int iUpdatePeriod, int iStunStatus, time_t timeStamp);

	//ȫ��¼������ص�����ԭ��
	//¼��ģ���ʼ����ԭ�ͣ��ϲ���Ҫ�ڳ�ʼ��Api����ɹ�֮�����
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


	/** ��ȫ��¼������
	@param [in] cc_events ȫ��¼������ص�����ԭ��
	@return 
	*/
	int MRPS_API MRPS_RS_OpenService(PRS_EVENTS rs_events);

	/** �ر�ȫ��¼������
	@return 
	*/
	int MRPS_API MRPS_RS_CloseService();

	/** ��ʼ¼������
	@param [in] pArrNumber      ��ʼ¼�����Ķ�������
	@param [in] iSize           �������Ա����
	@return 
	@note
	��Ա�����������Ϊ32��
	*/
	int MRPS_API MRPS_RS_StartRecord(const CallNumber* pArrNumber, int iSize);

	/** ����¼������
	@param [in] pArrNumber      ����¼�����Ķ�������
	@param [in] iSize           �������Ա����

	@return 
	@note
	��Ա�����������Ϊ32��
	*/
	int MRPS_API MRPS_RS_StopRecord(const CallNumber* pArrNumber, int iSize);

	
	/** ����¼������
	@param [in] callId         ����Ψһ��ʶ
	@param [in] pRtpResource   ����RTP����
	@param [in] iRtpCount      ����RTP����

	@return
	@note	
	*/
	int MRPS_API  MRPS_RS_SetRtpResources(CALL_ID callId, const Voice_Resources_Rtp* pRtpResource, int iRtpCount);

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif