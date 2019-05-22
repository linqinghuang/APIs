#ifndef __IAPIObject_H__
#define __IAPIObject_H__


#include "IInLogInterface.h"
#include "DefAPIType.h"
#include "DefNumberType.h"
#include "DefCallType.h"
#include "DefAPISystemEvt.h"
#include "DefAPIMgrEvt.h"
#include "DefAPIRsEvt.h"
#include "DefMedia.h"

namespace MRPS
{
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/

	

	struct InitParamPer
	{
		std::string strModule;
		std::string strName;
		std::string strValue;

		InitParamPer(){}

		InitParamPer(const InitParamPer& other)
		{
			strModule = other.strModule;
			strName = other.strName;
			strValue = other.strValue;
		}

		InitParamPer& operator=(const InitParamPer& other)
		{
			if (&other == this)
			{
				return *this;
			}

			strModule = other.strModule;
			strName = other.strName;
			strValue = other.strValue;

			return *this;
		}
	};

	struct Init_PucInfo
	{
		std::string  strLocalSipIp;
		unsigned int usLocalSipPort;
		std::string  strPUCId;
		int           iSegment;
		std::vector<InitParamPer> vecPers;

		Init_PucInfo(){ iSegment = 0; usLocalSipPort = 0; }

		Init_PucInfo(const Init_PucInfo& other)
		{
			strLocalSipIp = other.strLocalSipIp;
			usLocalSipPort = other.usLocalSipPort;
			strPUCId = other.strPUCId;
			iSegment = other.iSegment;
			vecPers = other.vecPers;
		}

		Init_PucInfo& operator=(const Init_PucInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}

			strLocalSipIp = other.strLocalSipIp;
			usLocalSipPort = other.usLocalSipPort;
			strPUCId = other.strPUCId;
			iSegment = other.iSegment;
			vecPers = other.vecPers;
			return *this;
		}
	};

	struct Init_PdtInfo
	{
		int		iAudioCodec;

		Init_PdtInfo()	{ iAudioCodec = 0; }

		Init_PdtInfo(const Init_PdtInfo& other)
		{
			iAudioCodec = other.iAudioCodec;
		}

		Init_PdtInfo& operator=(const Init_PdtInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}

			iAudioCodec = other.iAudioCodec;
			return *this;
		}
	};

	struct Init_LteInfo
	{
		bool bIsRequestUrlUseDomain;
		bool bIsToUseDomain;
		std::string strRemoteDomain;
		bool bIsFromUseDomain;
		std::string strLocalDomain;
		unsigned char ucAudioCodec;
		unsigned short usAMRPara;
		unsigned char ucVideoCodec;
		unsigned int uiH264Para;
		int          iExpires;

		std::string  strProxyIp;
		unsigned short uProxyPort;
		std::string  strRouteIp;
		unsigned short uRoutePort;

		std::string strServerUser;


		Init_LteInfo()
		{			
			bIsRequestUrlUseDomain = false;
			bIsToUseDomain = false;
			bIsFromUseDomain = false;
			ucAudioCodec = 0;
			ucVideoCodec = 0;
			uiH264Para = 0;
			usAMRPara = 0;			
			iExpires = 3600;

			uProxyPort = 0;
			uRoutePort = 0;
		}

		Init_LteInfo(const Init_LteInfo& other)
		{
			bIsRequestUrlUseDomain = other.bIsRequestUrlUseDomain;
			strRemoteDomain = other.strRemoteDomain;
			bIsToUseDomain = other.bIsToUseDomain;
			bIsFromUseDomain = other.bIsFromUseDomain;
			strLocalDomain = other.strLocalDomain;
			ucAudioCodec = other.ucAudioCodec;
			usAMRPara = other.usAMRPara;
			ucVideoCodec = other.ucVideoCodec;
			uiH264Para = other.uiH264Para;
			iExpires = other.iExpires;

			strProxyIp = other.strProxyIp;
			uProxyPort = other.uProxyPort;
			strRouteIp = other.strRouteIp;
			uRoutePort = other.uRoutePort;

			strServerUser = other.strServerUser;
		}

		Init_LteInfo& operator=(const Init_LteInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}
			bIsRequestUrlUseDomain = other.bIsRequestUrlUseDomain;
			strRemoteDomain = other.strRemoteDomain;
			bIsToUseDomain = other.bIsToUseDomain;
			bIsFromUseDomain = other.bIsFromUseDomain;
			strLocalDomain = other.strLocalDomain;
			ucAudioCodec = other.ucAudioCodec;
			usAMRPara = other.usAMRPara;
			ucVideoCodec = other.ucVideoCodec;
			uiH264Para = other.uiH264Para;
			iExpires = other.iExpires;

			strProxyIp = other.strProxyIp;
			uProxyPort = other.uProxyPort;
			strRouteIp = other.strRouteIp;
			uRoutePort = other.uRoutePort;

			strServerUser = other.strServerUser;

			return *this;
		}
	};

	struct Param_Initialize
	{
		std::string    strSystemId;

		std::string    strServerIp;
		unsigned int   usServerPort;

		std::string    strServerIpEx;
		unsigned int   uiServerPortEx;

		std::string    strLocalIp;
		unsigned int   usLocalPort;

		SYS_EVENTS     events;	

		Init_PucInfo   ext_pucInfo;
		Init_LteInfo   ext_lteInfo;
		Init_PdtInfo   ext_PdtInfo;

		std::map<std::string, std::string> mapExtInfo;
		std::string strExtXml;

		Param_Initialize()
		{
			usServerPort = 0;
			uiServerPortEx = 0;
			usLocalPort = 0;
		}

		Param_Initialize(const Param_Initialize& other)
		{
			strSystemId = other.strSystemId;
			strServerIp = other.strServerIp;
			usServerPort = other.usServerPort;
			strServerIpEx = other.strServerIpEx;
			uiServerPortEx = other.uiServerPortEx;
			strLocalIp = other.strLocalIp;
			usLocalPort = other.usLocalPort;
			events = other.events;	
			ext_pucInfo = other.ext_pucInfo;
			ext_lteInfo = other.ext_lteInfo;
			ext_PdtInfo = other.ext_PdtInfo;
			mapExtInfo = other.mapExtInfo;
			strExtXml = other.strExtXml;
		}

		Param_Initialize& operator=(const Param_Initialize& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strServerIp = other.strServerIp;
			usServerPort = other.usServerPort;
			strServerIpEx = other.strServerIpEx;
			uiServerPortEx = other.uiServerPortEx;
			strLocalIp = other.strLocalIp;
			usLocalPort = other.usLocalPort;
			events = other.events;
			ext_pucInfo = other.ext_pucInfo;
			ext_lteInfo = other.ext_lteInfo;
			ext_PdtInfo = other.ext_PdtInfo;
			mapExtInfo = other.mapExtInfo;
			strExtXml = other.strExtXml;
			return *this;
		}
	};

	struct Param_Login
	{
		std::string strUser;
		std::string strPassword;
		std::string strNumber;

		std::string strServerName;

		std::map<std::string, std::string> mapExtInfo;
		std::string strExtXml;
		Param_Login()
		{

		}

		Param_Login(const Param_Login& other)
		{
			strUser = other.strUser;
			strPassword = other.strPassword;
			strNumber = other.strNumber;
			strServerName = other.strServerName;
			mapExtInfo = other.mapExtInfo;
			strExtXml = other.strExtXml;
		}

		Param_Login& operator=(const Param_Login& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strUser = other.strUser;
			strPassword = other.strPassword;
			strNumber = other.strNumber;
			strServerName = other.strServerName;
			mapExtInfo = other.mapExtInfo;
			strExtXml = other.strExtXml;
			return *this;
		}
	};

	struct Param_GetInfo
	{
		std::string strNumber;
		std::string strGateWay;
		int         iNumberType;
		std::string strPucId;
		std::string strVersion;

		std::map<std::string, std::string> mapExtInfo;
		std::string strExtXml;

		Param_GetInfo(){ iNumberType = -1; }
		Param_GetInfo(const Param_GetInfo& other)
		{
			strNumber = other.strNumber;
			strGateWay = other.strGateWay;
			iNumberType = other.iNumberType;
			strPucId = other.strPucId;
			strVersion = other.strVersion;
			mapExtInfo = other.mapExtInfo;
			strExtXml = other.strExtXml;
		}

		Param_GetInfo& operator=(const Param_GetInfo& other)
		{
			if (&other == this)
			{
				return *this;
			}

			strNumber = other.strNumber;
			strGateWay = other.strGateWay;
			iNumberType = other.iNumberType;
			strPucId = other.strPucId;
			strVersion = other.strVersion;
			mapExtInfo = other.mapExtInfo;
			strExtXml = other.strExtXml;
			return *this;
		}
	};

	struct Param_Monitor
	{
		std::string strNumber;
		std::string strGateway;
		int         iNumberType;
		std::string strPucId;
		std::string strPucSystemId;
		std::string strSapGuid;
		std::string strSapeType;
		int iLevel;

		std::map<std::string, std::string> mapExtInfo;
		std::string strExtXml;

		Param_Monitor(){ iNumberType = -1; iLevel = -1; }
		Param_Monitor(const Param_Monitor& other)
		{
			strNumber = other.strNumber;
			strGateway = other.strGateway;
			iNumberType = other.iNumberType;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strSapGuid = other.strSapGuid;
			strSapeType = other.strSapeType;
			iLevel = other.iLevel;
			mapExtInfo = other.mapExtInfo;
			strExtXml = other.strExtXml;
		}
		Param_Monitor& operator=(const Param_Monitor& other)
		{
			if (&other == this)
			{
				return *this;
			}
			strNumber = other.strNumber;
			strGateway = other.strGateway;
			iNumberType = other.iNumberType;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strSapGuid = other.strSapGuid;
			strSapeType = other.strSapeType;
			iLevel = other.iLevel;
			mapExtInfo = other.mapExtInfo;
			strExtXml = other.strExtXml;
			return *this;
		}
	};	

	struct Log_Param
	{
		std::string strPath;
		int         iLevel;
		int         iFileMaxSize;
		int         iSaveDays;

		Log_Param()
		{
			iLevel = 1;
			iFileMaxSize = 10;
			iSaveDays = 60;
		}

		Log_Param(const Log_Param& other)
		{
			strPath = other.strPath;
			iLevel = other.iLevel;
			iFileMaxSize = other.iFileMaxSize;
			iSaveDays = other.iSaveDays;			
		}
		Log_Param& operator=(const Log_Param& other)
		{
			if (&other == this)
			{
				return *this;
			}
			strPath = other.strPath;
			iLevel = other.iLevel;
			iFileMaxSize = other.iFileMaxSize;
			iSaveDays = other.iSaveDays;
			return *this;
		}

	};

	class IAPIObject
	{
	public:
		virtual int  MRPS_SetThirdLogParam(const Log_Param& param){ return 0; };

		virtual void MRPS_SetSystemId(const std::string& strSystemId) = 0;
		virtual int  MRPS_Initialize(const Param_Initialize& param) = 0;
		virtual int  MRPS_Uninitialize() = 0;
		virtual int  MRPS_SetHeartbeatInterval(int iInterval) = 0;
		virtual int  MRPS_Login(const Param_Login& param) = 0;
		virtual int  MRPS_Logout(const Param_Login& param) = 0;

		virtual int  MRPS_Mgr_OpenService(PMGR_EVENTS mgr_events) { return 0; };
		virtual int  MRPS_Mgr_CloseService() { return 0; };
		virtual int  MRPS_Mgr_RequestDataVersion() { return 0; };
		virtual int  MRPS_Mgr_GetPUCInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetPUCSystemInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetAccountInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetUserInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetCrosspatchInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetConferenceInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetGroupInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetOrgInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetStaffInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetSapInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetDgnaInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetPredefinedDgnaInfo(const Param_GetInfo& param) { return 0; };
		virtual int  MRPS_Mgr_GetSimulSelectInfo(const Param_GetInfo& param){ return 0; };

		virtual int  MRPS_RS_OpenService(PRS_EVENTS rs_events) = 0;
		virtual int  MRPS_RS_CloseService() = 0;
		virtual int  MRPS_RS_StartRecord(const Param_Monitor& param) = 0;
		virtual int  MRPS_RS_StopRecord(const Param_Monitor& param) = 0;
		virtual int  MRPS_RS_MonMonitor(const Param_Monitor& param)
		{
			return 0;
		};
		virtual int  MRPS_RS_SetRtpResources(const Param_RTPInfo& param) = 0;
		

		virtual int  GetAPIType() = 0;		

		

	public:
		IAPIObject(){}
		virtual ~IAPIObject(){}
	};


	enum API_ERRCODE
	{
		APICODE_SUCCESS = 0,
		APICODE_BASE = -1000,
		APICODE_StartFailed,
		APICODE_InitException,
		APICODE_StopFailed,
		APICODE_UnInitException,
	};
}



#endif