#ifndef __DefAPIMgrEvt_H__
#define __DefAPIMgrEvt_H__

#include "DefAPIType.h"

namespace MRPS
{
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
	struct Param_MGR_OpenServiceAck_Evt : public Param_Base
	{
		std::string     strSystemId;
		OpenMGRResult   result;
		time_t          timeStamp;

		Param_MGR_OpenServiceAck_Evt()
		{
			type = ParamType_Param_MGR_OpenServiceAck_Evt;
			result = OPEN_MGR_SUCCESS;
			timeStamp = std::time(NULL);
		}

		Param_MGR_OpenServiceAck_Evt(const Param_MGR_OpenServiceAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_MGR_OpenServiceAck_Evt& operator=(const Param_MGR_OpenServiceAck_Evt& other)
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
	typedef int(*MRPS_MGR_OpenServiceAck_Evt)(const Param_MGR_OpenServiceAck_Evt& param);

	typedef enum CloseMGRResult
	{
		CLOSE_MGR_SUCCESS = 0,	                ///< 成功		
	}CloseMGRResult;


	struct Param_MGR_CloseServiceAck_Evt : public Param_Base
	{
		std::string     strSystemId;
		CloseMGRResult  result;
		time_t          timeStamp;

		Param_MGR_CloseServiceAck_Evt()
		{
			type = ParamType_Param_MGR_CloseServiceAck_Evt;
			result = CLOSE_MGR_SUCCESS;
			timeStamp = std::time(NULL);
		}

		Param_MGR_CloseServiceAck_Evt(const Param_MGR_CloseServiceAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_MGR_CloseServiceAck_Evt& operator=(const Param_MGR_CloseServiceAck_Evt& other)
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
	typedef int(*MRPS_MGR_CloseServiceAck_Evt)(const Param_MGR_CloseServiceAck_Evt& param);


	typedef enum MGR_RequestDataVersionResult
	{
		MGR_RequestDataVersion_SUCCESS = 0,	                ///< 成功		
		MGR_RequestDataVersion_UNKNOWN = -1,
	}MGR_RequestDataVersionResult;

	typedef struct Mgr_DataVersionInfo
	{
		std::string strPucId;
		std::string strVerison;

		Mgr_DataVersionInfo()
		{

		}

		Mgr_DataVersionInfo(const Mgr_DataVersionInfo& other)
		{
			strPucId = other.strPucId;
			strVerison = other.strVerison;
		}

		Mgr_DataVersionInfo& operator=(const Mgr_DataVersionInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strPucId = other.strPucId;
			strVerison = other.strVerison;
			return *this;
		}
	}Mgr_DataVersionInfo;

	struct Param_MGR_RequestDataVersion_Evt : public Param_Base
	{
		std::string strSystemId;
		MGR_RequestDataVersionResult result;
		std::vector<Mgr_DataVersionInfo> vecVersionInfos;
		std::string strLocalPucId;
		time_t          timeStamp;

		Param_MGR_RequestDataVersion_Evt()
		{
			type = ParamType_Param_MGR_RequestDataVersion_Evt;
			result = MGR_RequestDataVersion_UNKNOWN;
			timeStamp = std::time(NULL);
		}

		Param_MGR_RequestDataVersion_Evt(const Param_MGR_RequestDataVersion_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			vecVersionInfos = other.vecVersionInfos;
			strLocalPucId = other.strLocalPucId;
			timeStamp = other.timeStamp;
		}

		Param_MGR_RequestDataVersion_Evt& operator=(const Param_MGR_RequestDataVersion_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			result = other.result;
			vecVersionInfos = other.vecVersionInfos;
			strLocalPucId = other.strLocalPucId;
			timeStamp = other.timeStamp;
			return *this;
		}
	};

	typedef int(*MRPS_MGR_RequestDataVersionAck_Evt)(const Param_MGR_RequestDataVersion_Evt& param);

	/*获取全网PUCACK事件结果枚举定义*/
	typedef enum GetPUCInfoResult
	{
		GET_PUC_INFO_SUCCESS = 0,	              ///<成功
		GET_PUC_INFO_ERROR_UNKNOWN = -1,			///<未知错误
	}GetPUCInfoResult;

	typedef struct PucInfo
	{
		std::string strPucId;
		std::string strPucName;
		std::string strPucSystemId;
		std::string strPucParentId;


		PucInfo()
		{

		}

		PucInfo(const PucInfo& other)
		{
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strPucName = other.strPucName;
			strPucParentId = other.strPucParentId;
		}

		PucInfo& operator=(const PucInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strPucName = other.strPucName;
			strPucParentId = other.strPucParentId;
			return *this;
		}
	}PucInfo, *PPucInfo;

	struct Param_MGR_GetPucInfoAck_Evt : public Param_Base
	{
		std::string       strSystemId;
		std::string       strLocalPucId;
		GetPUCInfoResult result;
		bool              bEnd;
		std::vector<PucInfo> puser;
		int               iSize;
		int               iCurPiece;
		time_t            timeStamp;

		Param_MGR_GetPucInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetPucInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			result = GET_PUC_INFO_SUCCESS;
			iCurPiece = 0;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetPucInfoAck_Evt(const Param_MGR_GetPucInfoAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			strLocalPucId = other.strLocalPucId;
			result = other.result;
			bEnd = other.bEnd;
			puser = other.puser;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
			timeStamp = other.timeStamp;
		}

		Param_MGR_GetPucInfoAck_Evt& operator=(const Param_MGR_GetPucInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strLocalPucId = other.strLocalPucId;
			result = other.result;
			bEnd = other.bEnd;
			puser = other.puser;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_MGR_GetPucInfoAck_Evt)(const Param_MGR_GetPucInfoAck_Evt& param);

	/*获取全网PUCACK事件结果枚举定义*/
	typedef enum GetPUCSystemInfoResult
	{
		GET_PUCSYSTEM_INFO_SUCCESS = 0,	              ///<成功
		GET_PUCSYSTEM_INFO_ERROR_UNKNOWN = -1,			///<未知错误
	}GetPUCSystemInfoResult;

	typedef struct PucSystemInfo
	{
		std::string strGuid;
		std::string strPucId;
		std::string strSystemId;
		std::string strSystemAlias;
		std::string strSystemType;
		std::string strEnableFlag;

		PucSystemInfo()
		{

		}

		PucSystemInfo(const PucSystemInfo& other)
		{
			strGuid = other.strGuid;
			strPucId = other.strPucId;
			strSystemId = other.strSystemId;
			strSystemAlias = other.strSystemAlias;
			strSystemType = other.strSystemType;
			strEnableFlag = other.strEnableFlag;
		}

		PucSystemInfo& operator=(const PucSystemInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strGuid = other.strGuid;
			strPucId = other.strPucId;
			strSystemId = other.strSystemId;
			strSystemAlias = other.strSystemAlias;
			strSystemType = other.strSystemType;
			strEnableFlag = other.strEnableFlag;
			return *this;
		}
	}PucSystemInfo, *PPucSystemInfo;

	struct Param_MGR_GetPucSystemInfoAck_Evt : public Param_Base
	{
		std::string            strSystemId;
		GetPUCSystemInfoResult result;
		bool              bEnd;
		std::vector<PucSystemInfo> puser;
		int               iSize;
		int               iCurPiece;
		time_t            timeStamp;

		Param_MGR_GetPucSystemInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetPucSystemInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			result = GET_PUCSYSTEM_INFO_SUCCESS;
			iCurPiece = 0;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetPucSystemInfoAck_Evt(const Param_MGR_GetPucSystemInfoAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			bEnd = other.bEnd;
			puser = other.puser;
			iSize = other.iSize;
			timeStamp = other.timeStamp;
			iCurPiece = other.iCurPiece;
		}

		Param_MGR_GetPucSystemInfoAck_Evt& operator=(const Param_MGR_GetPucSystemInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			result = other.result;
			bEnd = other.bEnd;
			puser = other.puser;
			iSize = other.iSize;
			timeStamp = other.timeStamp;
			iCurPiece = other.iCurPiece;
			return *this;
		}
	};
	typedef int(*MRPS_MGR_GetPucSystemInfoAck_Evt)(const Param_MGR_GetPucSystemInfoAck_Evt& param);

	/*获取全网个人用户ACK事件结果枚举定义*/
	typedef enum GetUserInfoResult
	{
		GET_USER_INFO_SUCCESS = 0,	              ///<成功
		GET_USER_INFO_ERROR_UNKNOWN = -1,			///<未知错误
	}GetUserInfoResult;

	//用户信息结构定义
	typedef struct USER
	{
		std::string strPucId;
		std::string strPucSystemId;
		std::string strDeviceGuid;
		std::string strDeviceId;
		int		    iNumberType;		//若为终端 0:无线终端  1:系统调度台 2：用户调度台 3：录音服务器 4：GPS服务器
		std::string strNumber;
		std::string strAlias;
		std::string strDeviceNumber;
		int         iDeviceType;
		std::string strGateWay;
		std::string strNodeCode;
		std::string strOrgIdentifier;
		std::string strSapGuuid;
		std::string strStatus;
		std::string strBasestationId;

		USER()
		{
			iNumberType = 0;
			iDeviceType = 0;
		}

		USER(const USER& other)
		{
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strDeviceGuid = other.strDeviceGuid;
			strDeviceId = other.strDeviceId;
			iNumberType = other.iNumberType;
			strNumber = other.strNumber;
			strAlias = other.strAlias;
			strDeviceNumber = other.strDeviceNumber;
			iDeviceType = other.iDeviceType;
			strNodeCode = other.strNodeCode;
			strOrgIdentifier = other.strOrgIdentifier;
			strSapGuuid = other.strSapGuuid;
			strStatus = other.strStatus;
			strBasestationId = other.strBasestationId;
			strGateWay = other.strGateWay;
		}

		USER& operator=(const USER& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strDeviceGuid = other.strDeviceGuid;
			strDeviceId = other.strDeviceId;
			iNumberType = other.iNumberType;
			strNumber = other.strNumber;
			strAlias = other.strAlias;
			strDeviceNumber = other.strDeviceNumber;
			iDeviceType = other.iDeviceType;
			strNodeCode = other.strNodeCode;
			strOrgIdentifier = other.strOrgIdentifier;
			strSapGuuid = other.strSapGuuid;
			strStatus = other.strStatus;
			strBasestationId = other.strBasestationId;
			strGateWay = other.strGateWay;
			return *this;
		}
	}USER, *PUSER;




	/** 获取全网个人用户信息确认事件
	@param [in] result	        获取结果
	@param [in] bEnd			是否最后一个包（true为结束、false没有结束）
	@param [in] puser			用户信息
	@param [in] iUserSize			用户信息数组可用长度
	@param [in] timeStamp      时间戳

	@return 返回值的意义见 Result 开始的宏
	*/
	struct Param_MGR_GetUserInfoAck_Evt : public Param_Base
	{
		std::string       strSystemId;
		GetUserInfoResult result;
		bool              bEnd;
		std::vector<USER> puser;
		int               iSize;
		int               iCurPiece;
		time_t            timeStamp;

		Param_MGR_GetUserInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetUserInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			result = GET_USER_INFO_SUCCESS;
			iCurPiece = 0;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetUserInfoAck_Evt(const Param_MGR_GetUserInfoAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			bEnd = other.bEnd;
			puser = other.puser;
			iSize = other.iSize;
			timeStamp = other.timeStamp;
			iCurPiece = other.iCurPiece;
		}

		Param_MGR_GetUserInfoAck_Evt& operator=(const Param_MGR_GetUserInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			result = other.result;
			bEnd = other.bEnd;
			puser = other.puser;
			iSize = other.iSize;
			timeStamp = other.timeStamp;
			iCurPiece = other.iCurPiece;
			return *this;
		}
	};
	typedef int(*MRPS_MGR_GetUserInfoAck_Evt)(const Param_MGR_GetUserInfoAck_Evt& param);

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
	struct Param_MGR_GetGroupInfoAck_Evt : public Param_Base
	{
		std::string        strSystemId;
		GetGroupInfoResult result;
		bool               bEnd;
		std::vector<USER>  pgroup;
		int                iSize;
		time_t             timeStamp;

		Param_MGR_GetGroupInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetGroupInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			result = GET_GROUP_INFO_ERROR_UNKNOWN;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetGroupInfoAck_Evt(const Param_MGR_GetGroupInfoAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			bEnd = other.bEnd;
			pgroup = other.pgroup;
			iSize = other.iSize;
			timeStamp = other.timeStamp;
		}

		Param_MGR_GetGroupInfoAck_Evt& operator=(const Param_MGR_GetGroupInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			result = other.result;
			bEnd = other.bEnd;
			pgroup = other.pgroup;
			iSize = other.iSize;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_MGR_GetGroupInfoAck_Evt)(const Param_MGR_GetGroupInfoAck_Evt& param);


	/** 获取全网个人用户信息确认事件
	@param [in] result	        获取结果
	@param [in] bEnd			是否最后一个包（true为结束、false没有结束）
	@param [in] puser			用户信息
	@param [in] iUserSize			用户信息数组可用长度
	@param [in] timeStamp      时间戳

	@return 返回值的意义见 Result 开始的宏
	*/
	struct Param_MGR_GetAccountInfoAck_Evt : public Param_Base
	{
		std::string       strSystemId;
		GetUserInfoResult result;
		bool              bEnd;
		std::vector<USER> puser;
		int               iSize;
		int               iCurPiece;
		time_t            timeStamp;

		Param_MGR_GetAccountInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetAccountInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			result = GET_USER_INFO_SUCCESS;
			iCurPiece = 0;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetAccountInfoAck_Evt(const Param_MGR_GetAccountInfoAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			bEnd = other.bEnd;
			puser = other.puser;
			iSize = other.iSize;
			timeStamp = other.timeStamp;
			iCurPiece = other.iCurPiece;
		}

		Param_MGR_GetAccountInfoAck_Evt& operator=(const Param_MGR_GetAccountInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			result = other.result;
			bEnd = other.bEnd;
			puser = other.puser;
			iSize = other.iSize;
			timeStamp = other.timeStamp;
			iCurPiece = other.iCurPiece;
			return *this;
		}
	};
	typedef int(*MRPS_MGR_GetAccountInfoAck_Evt)(const Param_MGR_GetAccountInfoAck_Evt& param);


	/*获取人员信息ACK事件结果枚举定义*/
	typedef enum GetStaffInfoResult
	{
		GET_STAFF_INFO_SUCCESS = 0,	              ///< 成功
		GET_STAFF_INFO_ERROR_UNKNOWN = -1,			///< 未知错误
	}GetStaffInfoResult;

	/*人员信息*/
	typedef struct STAFF
	{
		std::string     strGuid;
		std::string     strPucId;
		std::string     strPucSystemId;
		std::string     strOrgIdentifier;
		std::string     strNO;             //证件号码
		std::string		strName;           //员工姓名
		std::string     strStaffCode;      //人员编号
		std::string		strPlateNum;       //车牌号
		std::string     strStaffNum;       //警员编号
		std::string     strPost;           //职务
		std::string		strWorkType;       //警种
		std::string     strUnitName;       //单位名称
		std::string     strUnitCode;       //单位代码
		std::string     strTelNum;         //固定电话号 
		std::string		strNumber;         //个呼号
		std::string		strUsetype;        //用途类型
		int		        iNumberType;       //终端类型 0：是手台 1：车台
		std::string		strNodeCode;	   //组织编号
		std::string     strMobile;
		std::string     strAddress;
		std::string     strEmail;

		STAFF()
		{
			iNumberType = 0;
		}

		STAFF(const STAFF& other)
		{
			strGuid = other.strGuid;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strOrgIdentifier = other.strOrgIdentifier;
			strNO = other.strNO;
			strName = other.strName;
			strStaffCode = other.strStaffCode;
			strPlateNum = other.strPlateNum;
			strStaffNum = other.strStaffNum;
			strPost = other.strPost;
			strWorkType = other.strWorkType;
			strUnitName = other.strUnitName;
			strUnitCode = other.strUnitCode;
			strTelNum = other.strTelNum;
			strNumber = other.strNumber;
			strUsetype = other.strUsetype;
			iNumberType = other.iNumberType;
			strNodeCode = other.strNodeCode;
			strMobile = other.strMobile;
			strAddress = other.strAddress;
			strEmail = other.strEmail;
		}

		STAFF& operator=(const STAFF& other)
		{
			if (this == &other)
			{
				return *this;
			}

			strGuid = other.strGuid;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strOrgIdentifier = other.strOrgIdentifier;
			strNO = other.strNO;
			strName = other.strName;
			strStaffCode = other.strStaffCode;
			strPlateNum = other.strPlateNum;
			strStaffNum = other.strStaffNum;
			strPost = other.strPost;
			strWorkType = other.strWorkType;
			strUnitName = other.strUnitName;
			strUnitCode = other.strUnitCode;
			strTelNum = other.strTelNum;
			strNumber = other.strNumber;
			strUsetype = other.strUsetype;
			iNumberType = other.iNumberType;
			strNodeCode = other.strNodeCode;
			strMobile = other.strMobile;
			strAddress = other.strAddress;
			strEmail = other.strEmail;

			return *this;
		}

	}STAFF, *PSTAFF;

	/*查询权限内人员信息确认事件
	@param [in] result：	   结果码，详见GetStaffInfoResult定义
	@param [in] bEnd：	   是否最后一个包（true为结束、false没有结束）
	@param [in] pstaff：    人员信息
	@param [in] iSize：    人员信息数组可用长度
	@param [in] timeStamp：时间戳
	@return 返回值的意义见 Result 开始的宏
	*/
	struct Param_MGR_GetStaffInfoAck_Evt : public Param_Base
	{
		std::string        strSystemId;
		GetStaffInfoResult result;
		bool               bEnd;
		std::vector<STAFF> pstaff;
		int                iSize;
		int                iCurPiece;
		time_t             timeStamp;

		Param_MGR_GetStaffInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetStaffInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			result = GET_STAFF_INFO_ERROR_UNKNOWN;
			iCurPiece = 0;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetStaffInfoAck_Evt(const Param_MGR_GetStaffInfoAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			bEnd = other.bEnd;
			pstaff = other.pstaff;
			iSize = other.iSize;
			timeStamp = other.timeStamp;
			iCurPiece = other.iCurPiece;
		}

		Param_MGR_GetStaffInfoAck_Evt& operator=(const Param_MGR_GetStaffInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			result = other.result;
			bEnd = other.bEnd;
			pstaff = other.pstaff;
			iSize = other.iSize;
			timeStamp = other.timeStamp;
			iCurPiece = other.iCurPiece;
			return *this;
		}
	};
	typedef int(*MRPS_MGR_GetStaffInfoAck_Evt)(const Param_MGR_GetStaffInfoAck_Evt& param);

	/*获取调度员权限内组织信息ACK事件结果枚举定义*/
	typedef enum GetUserOrgInfoResult
	{
		GET_ORG_INFO_SUCCESS = 0,	              ///< 成功
		GET_ORG_INFO_UNKNOWNERROR = -1,
	};

	/*组织信息结构定义*/
	typedef struct ORG
	{
		std::string strGuid;
		std::string strPucId;
		std::string strPucSystemId;
		std::string strIdentifier;
		std::string	strNodeName;   //名称
		std::string	strOrgCode;    //组织机构代码 
		std::string strAlias;
		std::string	strNodeCode;   //组织编号

		ORG()
		{

		}

		ORG(const ORG& other)
		{
			strGuid = other.strGuid;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strIdentifier = other.strIdentifier;
			strNodeName = other.strNodeName;
			strOrgCode = other.strOrgCode;
			strAlias = other.strAlias;
			strNodeCode = other.strNodeCode;
		}

		ORG& operator=(const ORG& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strGuid = other.strGuid;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strIdentifier = other.strIdentifier;
			strNodeName = other.strNodeName;
			strOrgCode = other.strOrgCode;
			strAlias = other.strAlias;
			strNodeCode = other.strNodeCode;
			return *this;
		}
	}ORG, *PORG;


	/*查询调度员所拥有权限的组织结构信息确认事件
	@param [in] result：	   结果码，详见GetLdsUserOrgInfoResult定义
	@param [in] pldsorg：    组织信息
	@param [in] length：    组织信息数组可用长度
	@param [in] time_stamp：时间戳
	@return 返回值的意义见 Result 开始的宏
	*/
	struct Param_MGR_GetOrgInfoAck_Evt : public Param_Base
	{
		std::string        strSystemId;
		GetUserOrgInfoResult result;
		bool               bEnd;
		std::vector<ORG>  porg;
		int                iSize;
		int                iCurPiece;
		time_t             timeStamp;

		Param_MGR_GetOrgInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetOrgInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			iCurPiece = 0;
			result = GET_ORG_INFO_UNKNOWNERROR;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetOrgInfoAck_Evt(const Param_MGR_GetOrgInfoAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			porg = other.porg;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
		}

		Param_MGR_GetOrgInfoAck_Evt& operator=(const Param_MGR_GetOrgInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			porg = other.porg;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
			return *this;
		}
	};
	typedef int(*MRPS_MGR_GetOrgInfoAck_Evt)(const Param_MGR_GetOrgInfoAck_Evt& param);


	typedef enum GetSapInfoResult
	{
		GET_SAP_INFO_SUCCESS = 0,	              ///< 成功
		GET_SAP_INFO_UNKNOWNERROR = -1,
	};

	typedef struct SAP
	{
		std::string strGuid;
		std::string strPucId;
		std::string strPucSystemId;
		std::string strAlias;
		std::string	strType;
		std::string strStatus;

		SAP()
		{

		}

		SAP(const SAP& other)
		{
			strGuid = other.strGuid;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strAlias = other.strAlias;
			strType = other.strType;
			strStatus = other.strStatus;
		}

		SAP& operator=(const SAP& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strGuid = other.strGuid;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strAlias = other.strAlias;
			strType = other.strType;
			strStatus = other.strStatus;
			return *this;
		}
	}SAP, *PSAP;

	struct Param_MGR_GetSapInfoAck_Evt : public Param_Base
	{
		std::string        strSystemId;
		GetSapInfoResult   result;
		bool               bEnd;
		std::vector<SAP>   vecSaps;
		int                iSize;
		int                iCurPiece;
		time_t             timeStamp;

		Param_MGR_GetSapInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetSapInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			iCurPiece = 0;
			result = GET_SAP_INFO_UNKNOWNERROR;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetSapInfoAck_Evt(const Param_MGR_GetSapInfoAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecSaps = other.vecSaps;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
		}

		Param_MGR_GetSapInfoAck_Evt& operator=(const Param_MGR_GetSapInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecSaps = other.vecSaps;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
			return *this;
		}
	};
	typedef int(*MRPS_MGR_GetSapInfoAck_Evt)(const Param_MGR_GetSapInfoAck_Evt& param);



	typedef enum GetCrosspatchResult
	{
		GET_CROSSPATCH_SUCCESS = 0,	              ///< 成功
		GET_CROSSPATCH_UNKNOWNERROR = -1,
	};

	typedef struct Crosspatch_Member
	{
		std::string strMemberGuid;
		std::string strPucId;
		std::string strDeviceGuid;
		std::string strNumber;
		NumberType  numberType;
		std::string strPucSystemId;
		std::string strSapGuid;
		int         iCallPriority;

		Crosspatch_Member()
		{
			numberType = MRPS_NUMBER_TYPE_UNKNOWN;
			int iCallPriority = 0;
		}

		Crosspatch_Member(const Crosspatch_Member& other)
		{
			strMemberGuid = other.strMemberGuid;
			strPucId = other.strPucId;
			strDeviceGuid = other.strDeviceGuid;
			strNumber = other.strNumber;
			numberType = other.numberType;
			strPucSystemId = other.strPucSystemId;
			strSapGuid = other.strSapGuid;
			iCallPriority = other.iCallPriority;
		}

		Crosspatch_Member& operator=(const Crosspatch_Member& other)
		{
			if (&other == this)
			{
				return *this;
			}

			strMemberGuid = other.strMemberGuid;
			strPucId = other.strPucId;
			strDeviceGuid = other.strDeviceGuid;
			strNumber = other.strNumber;
			numberType = other.numberType;
			strPucSystemId = other.strPucSystemId;
			strSapGuid = other.strSapGuid;
			iCallPriority = other.iCallPriority;

			return *this;
		}
	}Crosspatch_Member;

	typedef struct CrosspatchInfo
	{
		std::string strCrosspatchGuid;
		std::string strPucId;
		std::string strCrosspatchIndex;
		std::string strCrosspatchAlias;
		std::string strDispatcher;
		std::string strVoiceDelay;
		std::string strActiveFlag;
		std::string strEnableFlag;
		std::string strCreateTime;
		std::string strUpdateTime;
		std::string strRemark;

		std::vector<Crosspatch_Member> vecMemebers;

		CrosspatchInfo()
		{

		}

		CrosspatchInfo(const CrosspatchInfo& other)
		{
			strCrosspatchGuid = other.strCrosspatchGuid;
			strPucId = other.strPucId;
			strCrosspatchIndex = other.strCrosspatchIndex;
			strCrosspatchAlias = other.strCrosspatchAlias;
			strDispatcher = other.strDispatcher;
			strVoiceDelay = other.strVoiceDelay;
			strActiveFlag = other.strActiveFlag;
			strEnableFlag = other.strEnableFlag;
			strCreateTime = other.strCreateTime;
			strUpdateTime = other.strUpdateTime;
			strRemark = other.strRemark;

			vecMemebers = other.vecMemebers;
		}

		CrosspatchInfo& operator=(const CrosspatchInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strCrosspatchGuid = other.strCrosspatchGuid;
			strPucId = other.strPucId;
			strCrosspatchIndex = other.strCrosspatchIndex;
			strCrosspatchAlias = other.strCrosspatchAlias;
			strDispatcher = other.strDispatcher;
			strVoiceDelay = other.strVoiceDelay;
			strActiveFlag = other.strActiveFlag;
			strEnableFlag = other.strEnableFlag;
			strCreateTime = other.strCreateTime;
			strUpdateTime = other.strUpdateTime;
			strRemark = other.strRemark;

			vecMemebers = other.vecMemebers;

			return *this;
		}
	}CrosspatchInfo, *PCrosspatchInfo;

	struct Param_MGR_GetCrosspatchInfoAck_Evt : public Param_Base
	{
		std::string         strMrpsSystemId;
		std::string         strPucSystemType;
		GetCrosspatchResult result;
		bool                bEnd;
		std::vector<CrosspatchInfo>    vecCrosspatchs;
		int                 iSize;
		int                 iCurPiece;
		time_t              timeStamp;

		Param_MGR_GetCrosspatchInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetCrosspatchInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			iCurPiece = 0;
			result = GET_CROSSPATCH_UNKNOWNERROR;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetCrosspatchInfoAck_Evt(const Param_MGR_GetCrosspatchInfoAck_Evt& other)
		{
			strMrpsSystemId = other.strMrpsSystemId;
			strPucSystemType = other.strPucSystemType;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecCrosspatchs = other.vecCrosspatchs;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
		}

		Param_MGR_GetCrosspatchInfoAck_Evt& operator=(const Param_MGR_GetCrosspatchInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strMrpsSystemId = other.strMrpsSystemId;
			strPucSystemType = other.strPucSystemType;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecCrosspatchs = other.vecCrosspatchs;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
			return *this;
		}

	};

	typedef int(*MRPS_MGR_GetCrosspatchInfoAck_Evt)(const Param_MGR_GetGroupInfoAck_Evt& param);

	typedef enum GetConferenceResult
	{
		GET_CONFERENCE_SUCCESS = 0,	              ///< 成功
		GET_CONFERENCE_UNKNOWNERROR = -1,
	};

	struct Conference_Member
	{
		std::string strMemberGuid;
		std::string strDeviceGuid;
		std::string strNumber;
		NumberType  numberType;
		std::string strPucSystemId;
		std::string strSapGuid;
		int         iCallPriority;
		std::string strVideoMixModel;

		Conference_Member()
		{
			numberType = MRPS_NUMBER_TYPE_UNKNOWN;
			iCallPriority = 0;
		}

		Conference_Member(const Conference_Member& other)
		{
			strMemberGuid = other.strMemberGuid;
			strDeviceGuid = other.strDeviceGuid;
			strNumber = other.strNumber;
			numberType = other.numberType;
			strPucSystemId = other.strPucSystemId;
			strSapGuid = other.strSapGuid;
			iCallPriority = other.iCallPriority;
			strVideoMixModel = other.strVideoMixModel;
		}

		Conference_Member& operator=(const Conference_Member& other)
		{
			if (&other == this)
			{
				return *this;
			}

			strMemberGuid = other.strMemberGuid;
			strDeviceGuid = other.strDeviceGuid;
			strNumber = other.strNumber;
			numberType = other.numberType;
			strPucSystemId = other.strPucSystemId;
			strSapGuid = other.strSapGuid;
			iCallPriority = other.iCallPriority;
			strVideoMixModel = other.strVideoMixModel;

			return *this;
		}
	};

	typedef struct ConferenceInfo
	{
		std::string strConferenceGuid;
		std::string strPucId;
		std::string strConferenceIndex;
		std::string strConferenceAlias;
		std::string strDispatcher;
		std::string strConferenceNumber;
		std::string strCallAfterInterval;
		std::string strVideoMixModel;
		std::string strCreateTime;
		std::string strRemark;

		std::vector<Conference_Member> vecMemebers;

		ConferenceInfo()
		{

		}

		ConferenceInfo(const ConferenceInfo& other)
		{
			strConferenceGuid = other.strConferenceGuid;
			strPucId = other.strPucId;
			strConferenceIndex = other.strConferenceIndex;
			strConferenceAlias = other.strConferenceAlias;
			strDispatcher = other.strDispatcher;
			strConferenceNumber = other.strConferenceNumber;
			strCallAfterInterval = other.strCallAfterInterval;
			strVideoMixModel = other.strVideoMixModel;
			strCreateTime = other.strCreateTime;
			strRemark = other.strRemark;

			vecMemebers = other.vecMemebers;
		}

		ConferenceInfo& operator=(const ConferenceInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}

			strConferenceGuid = other.strConferenceGuid;
			strPucId = other.strPucId;
			strConferenceIndex = other.strConferenceIndex;
			strConferenceAlias = other.strConferenceAlias;
			strDispatcher = other.strDispatcher;
			strConferenceNumber = other.strConferenceNumber;
			strCallAfterInterval = other.strCallAfterInterval;
			strVideoMixModel = other.strVideoMixModel;
			strCreateTime = other.strCreateTime;
			strRemark = other.strRemark;

			vecMemebers = other.vecMemebers;

			return *this;
		}
	}ConferenceInfo, *PConferenceInfo;

	struct Param_MGR_GetConferenceInfoAck_Evt : public Param_Base
	{
		std::string         strMrpsSystemId;
		GetConferenceResult result;
		bool                bEnd;
		std::vector<ConferenceInfo>    vecConrefences;
		int                 iSize;
		int                 iCurPiece;
		time_t              timeStamp;

		Param_MGR_GetConferenceInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetConferenceInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			iCurPiece = 0;
			result = GET_CONFERENCE_UNKNOWNERROR;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetConferenceInfoAck_Evt(const Param_MGR_GetConferenceInfoAck_Evt& other)
		{
			strMrpsSystemId = other.strMrpsSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecConrefences = other.vecConrefences;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
		}

		Param_MGR_GetConferenceInfoAck_Evt& operator=(const Param_MGR_GetConferenceInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strMrpsSystemId = other.strMrpsSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecConrefences = other.vecConrefences;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
			return *this;
		}
	};

	typedef int(*MRPS_MGR_GetConferenceInfoAck_Evt)(const Param_MGR_GetGroupInfoAck_Evt& param);


	struct Dgna_MemberInfo
	{
		std::string strMemberGuid;
		std::string strDeviceGuid;
		std::string strSubSystemId;
		std::string strNumber;
		NumberType  numberType;
		std::string strSapGuid;

		Dgna_MemberInfo()
		{
			numberType = MRPS_NUMBER_TYPE_UNKNOWN;
		}

		Dgna_MemberInfo(const Dgna_MemberInfo& other)
		{
			strMemberGuid = other.strMemberGuid;
			strDeviceGuid = other.strDeviceGuid;
			strSubSystemId = other.strSubSystemId;
			strNumber = other.strNumber;
			numberType = other.numberType;
			strSapGuid = other.strSapGuid;
		}

		Dgna_MemberInfo& operator=(const Dgna_MemberInfo& other)
		{
			if (&other == this)
			{
				return *this;
			}

			strMemberGuid = other.strMemberGuid;
			strDeviceGuid = other.strDeviceGuid;
			strSubSystemId = other.strSubSystemId;
			strNumber = other.strNumber;
			numberType = other.numberType;
			strSapGuid = other.strSapGuid;

			return *this;
		}
	};

	typedef struct DgnaInfo
	{
		std::string strDgnaGuid;
		std::string strPucId;
		std::string strSubSystemId;
		std::string strDgnaAlias;
		std::string strDispatcher;
		std::string strDgnaNumber;
		std::string strCreateTime;


		std::vector<Dgna_MemberInfo> vecMemebers;

		DgnaInfo()
		{

		}

		DgnaInfo(const DgnaInfo& other)
		{
			strDgnaGuid = other.strDgnaGuid;
			strPucId = other.strPucId;
			strSubSystemId = other.strSubSystemId;
			strDgnaAlias = other.strDgnaAlias;
			strDispatcher = other.strDispatcher;
			strDgnaNumber = other.strDgnaNumber;
			strCreateTime = other.strCreateTime;
			vecMemebers = other.vecMemebers;
		}

		DgnaInfo& operator=(const DgnaInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}

			strDgnaGuid = other.strDgnaGuid;
			strPucId = other.strPucId;
			strSubSystemId = other.strSubSystemId;
			strDgnaAlias = other.strDgnaAlias;
			strDispatcher = other.strDispatcher;
			strDgnaNumber = other.strDgnaNumber;
			strCreateTime = other.strCreateTime;
			vecMemebers = other.vecMemebers;

			return *this;
		}
	}DgnaInfo, *PDgnaInfo;

	typedef enum GetDgnaResult
	{
		GET_DGNA_SUCCESS = 0,	              ///< 成功
		GET_DGNA_UNKNOWNERROR = -1,
	};

	struct Param_MGR_GetDgnaInfoAck_Evt : public Param_Base
	{
		std::string         strMrpsSystemId;
		GetDgnaResult       result;
		bool                bEnd;
		std::vector<DgnaInfo>    vecDgnaInfos;
		int                 iSize;
		int                 iCurPiece;
		time_t              timeStamp;

		Param_MGR_GetDgnaInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetDgnaInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			iCurPiece = 0;
			result = GET_DGNA_UNKNOWNERROR;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetDgnaInfoAck_Evt(const Param_MGR_GetDgnaInfoAck_Evt& other)
		{
			strMrpsSystemId = other.strMrpsSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecDgnaInfos = other.vecDgnaInfos;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
		}

		Param_MGR_GetDgnaInfoAck_Evt& operator=(const Param_MGR_GetDgnaInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strMrpsSystemId = other.strMrpsSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecDgnaInfos = other.vecDgnaInfos;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
			return *this;
		}
	};


	typedef int(*MRPS_MGR_GetDgnaInfoAck_Evt)(const Param_MGR_GetGroupInfoAck_Evt& param);

	typedef struct PredefinedDgnaInfo
	{
		std::string strDgnaGuid;
		std::string strPucId;
		std::string strSubSystemId;
		std::string strDgnaNumber;
		std::string strSapGuid;
		std::string strBindFlag;


		PredefinedDgnaInfo()
		{

		}

		PredefinedDgnaInfo(const PredefinedDgnaInfo& other)
		{
			strDgnaGuid = other.strDgnaGuid;
			strPucId = other.strPucId;
			strSubSystemId = other.strSubSystemId;
			strDgnaNumber = other.strDgnaNumber;
			strSapGuid = other.strSapGuid;
			strBindFlag = other.strBindFlag;
		}

		PredefinedDgnaInfo& operator=(const PredefinedDgnaInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}

			strDgnaGuid = other.strDgnaGuid;
			strPucId = other.strPucId;
			strSubSystemId = other.strSubSystemId;
			strDgnaNumber = other.strDgnaNumber;
			strSapGuid = other.strSapGuid;
			strBindFlag = other.strBindFlag;

			return *this;
		}
	}PredefinedDgnaInfo, *PPredefinedDgnaInfo;

	typedef enum GetPredefinedDgnaResult
	{
		GET_PEDEFINEDDGNA_SUCCESS = 0,	              ///< 成功
		GET_PEDEFINEDDGNA_UNKNOWNERROR = -1,
	};

	struct Param_MGR_GetPredefinedDgnaInfoAck_Evt : public Param_Base
	{
		std::string         strMrpsSystemId;
		GetPredefinedDgnaResult       result;
		bool                bEnd;
		std::vector<PredefinedDgnaInfo>    vecPredefinedDgnaInfos;
		int                 iSize;
		int                 iCurPiece;
		time_t              timeStamp;

		Param_MGR_GetPredefinedDgnaInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetPreDgnaInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			iCurPiece = 0;
			result = GET_PEDEFINEDDGNA_UNKNOWNERROR;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetPredefinedDgnaInfoAck_Evt(const Param_MGR_GetPredefinedDgnaInfoAck_Evt& other)
		{
			strMrpsSystemId = other.strMrpsSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecPredefinedDgnaInfos = other.vecPredefinedDgnaInfos;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
		}

		Param_MGR_GetPredefinedDgnaInfoAck_Evt& operator=(const Param_MGR_GetPredefinedDgnaInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strMrpsSystemId = other.strMrpsSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecPredefinedDgnaInfos = other.vecPredefinedDgnaInfos;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
			return *this;
		}
	};

	typedef int(*MRPS_MGR_GetPredefinedDgnaInfoAck_Evt)(const Param_MGR_GetGroupInfoAck_Evt& param);

	struct Simulselect_MemberInfo
	{
		std::string strDeviceGuid;
		std::string strSubSystemId;
		std::string strPucId;
		std::string strNumber;
		NumberType  numberType;
		std::string strSapGuid;

		Simulselect_MemberInfo()
		{
			numberType = MRPS_NUMBER_TYPE_UNKNOWN;
		}

		Simulselect_MemberInfo(const Simulselect_MemberInfo& other)
		{
			strDeviceGuid = other.strDeviceGuid;
			strSubSystemId = other.strSubSystemId;
			strPucId = other.strPucId;
			strNumber = other.strNumber;
			numberType = other.numberType;
			strSapGuid = other.strSapGuid;
		}

		Simulselect_MemberInfo& operator=(const Simulselect_MemberInfo& other)
		{
			if (&other == this)
			{
				return *this;
			}

			strPucId = other.strPucId;
			strDeviceGuid = other.strDeviceGuid;
			strSubSystemId = other.strSubSystemId;
			strNumber = other.strNumber;
			numberType = other.numberType;
			strSapGuid = other.strSapGuid;

			return *this;
		}
	};

	typedef struct SimulselectInfo
	{
		std::string strSimulselectGuid;
		std::string strPucId;
		std::string strSubSystemId;
		std::string strSimulselectAlias;
		std::string strDispatcher;
		std::string strCreateTime;


		std::vector<Simulselect_MemberInfo> vecMemebers;

		SimulselectInfo()
		{

		}

		SimulselectInfo(const SimulselectInfo& other)
		{
			strSimulselectGuid = other.strSimulselectGuid;
			strPucId = other.strPucId;
			strSubSystemId = other.strSubSystemId;
			strSimulselectAlias = other.strSimulselectAlias;
			strDispatcher = other.strDispatcher;
			strCreateTime = other.strCreateTime;
			vecMemebers = other.vecMemebers;
		}

		SimulselectInfo& operator=(const SimulselectInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}

			strSimulselectGuid = other.strSimulselectGuid;
			strPucId = other.strPucId;
			strSubSystemId = other.strSubSystemId;
			strSimulselectAlias = other.strSimulselectAlias;
			strDispatcher = other.strDispatcher;
			strCreateTime = other.strCreateTime;
			vecMemebers = other.vecMemebers;

			return *this;
		}
	}SimulselectInfo, *PSimulselectInfo;

	enum GetSimulselectResult
	{
		GET_SIMULSELECT_SUCCESS = 0,	              ///< 成功
		GET_SIMULSELECT_UNKNOWNERROR = -1,
	};

	struct Param_MGR_GetSimulselectInfoAck_Evt : public Param_Base
	{
		std::string         strMrpsSystemId;
		GetSimulselectResult       result;
		bool                bEnd;
		std::vector<SimulselectInfo>    vecSimulselectInfos;
		int                 iSize;
		int                 iCurPiece;
		time_t              timeStamp;

		Param_MGR_GetSimulselectInfoAck_Evt()
		{
			type = ParamType_Param_MGR_GetSimulselectInfoAck_Evt;
			bEnd = false;
			iSize = 0;
			iCurPiece = 0;
			result = GET_SIMULSELECT_UNKNOWNERROR;
			timeStamp = std::time(NULL);
		}

		Param_MGR_GetSimulselectInfoAck_Evt(const Param_MGR_GetSimulselectInfoAck_Evt& other)
		{
			strMrpsSystemId = other.strMrpsSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecSimulselectInfos = other.vecSimulselectInfos;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
		}

		Param_MGR_GetSimulselectInfoAck_Evt& operator=(const Param_MGR_GetSimulselectInfoAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strMrpsSystemId = other.strMrpsSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
			bEnd = other.bEnd;
			vecSimulselectInfos = other.vecSimulselectInfos;
			iSize = other.iSize;
			iCurPiece = other.iCurPiece;
			return *this;
		}
	};

	typedef int(*MRPS_MGR_GetSimulselectInfoAck_Evt)(const Param_MGR_GetGroupInfoAck_Evt& param);


	//系统管理事件原型
	typedef struct MGR_EVENTS
	{
		MRPS_MGR_OpenServiceAck_Evt            mgr_open_service_ack;
		MRPS_MGR_CloseServiceAck_Evt           mgr_close_service_ack;
		MRPS_MGR_RequestDataVersionAck_Evt     mgr_requestdataversion_ack;
		MRPS_MGR_GetPucInfoAck_Evt             mgr_get_puc_info_ack;
		MRPS_MGR_GetPucSystemInfoAck_Evt       mgr_get_pucsystem_info_ack;
		MRPS_MGR_GetAccountInfoAck_Evt         mgr_get_pucaccount_info_ack;
		MRPS_MGR_GetUserInfoAck_Evt			   mgr_get_user_info_ack;
		MRPS_MGR_GetGroupInfoAck_Evt		   mgr_get_group_info_ack;
		MRPS_MGR_GetOrgInfoAck_Evt             mgr_get_org_info_ack;
		MRPS_MGR_GetStaffInfoAck_Evt           mgr_get_staff_info_ack;
		MRPS_MGR_GetSapInfoAck_Evt             mgr_get_sap_into_ack;
		MRPS_MGR_GetCrosspatchInfoAck_Evt      mgr_get_crosspatch_info_ack;
		MRPS_MGR_GetConferenceInfoAck_Evt      mgr_get_conference_info_ack;
		MRPS_MGR_GetDgnaInfoAck_Evt            mgr_get_dgna_info_ack;
		MRPS_MGR_GetPredefinedDgnaInfoAck_Evt  mgr_get_predefined_dgna_info_ack;
		MRPS_MGR_GetSimulselectInfoAck_Evt     mgr_get_simulselect_info_ack;


		MGR_EVENTS()
		{
			mgr_open_service_ack = NULL;
			mgr_close_service_ack = NULL;
			mgr_requestdataversion_ack = NULL;
			mgr_get_puc_info_ack = NULL;
			mgr_get_pucsystem_info_ack = NULL;
			mgr_get_pucaccount_info_ack = NULL;
			mgr_get_user_info_ack = NULL;
			mgr_get_group_info_ack = NULL;
			mgr_get_org_info_ack = NULL;
			mgr_get_staff_info_ack = NULL;
			mgr_get_sap_into_ack = NULL;
			mgr_get_crosspatch_info_ack = NULL;
			mgr_get_conference_info_ack = NULL;
			mgr_get_dgna_info_ack = NULL;
			mgr_get_predefined_dgna_info_ack = NULL;
			mgr_get_simulselect_info_ack = NULL;
		}

		MGR_EVENTS(const MGR_EVENTS& other)
		{
			mgr_open_service_ack = other.mgr_open_service_ack;
			mgr_close_service_ack = other.mgr_close_service_ack;
			mgr_requestdataversion_ack = other.mgr_requestdataversion_ack;
			mgr_get_puc_info_ack = other.mgr_get_puc_info_ack;
			mgr_get_pucsystem_info_ack = other.mgr_get_pucsystem_info_ack;
			mgr_get_pucaccount_info_ack = other.mgr_get_pucaccount_info_ack;
			mgr_get_user_info_ack = other.mgr_get_user_info_ack;
			mgr_get_group_info_ack = other.mgr_get_group_info_ack;
			mgr_get_org_info_ack = other.mgr_get_org_info_ack;
			mgr_get_staff_info_ack = other.mgr_get_staff_info_ack;
			mgr_get_sap_into_ack = other.mgr_get_sap_into_ack;
			mgr_get_crosspatch_info_ack = other.mgr_get_crosspatch_info_ack;
			mgr_get_conference_info_ack = other.mgr_get_conference_info_ack;
			mgr_get_dgna_info_ack = other.mgr_get_dgna_info_ack;
			mgr_get_predefined_dgna_info_ack = other.mgr_get_predefined_dgna_info_ack;
			mgr_get_simulselect_info_ack = other.mgr_get_simulselect_info_ack;
		}

		MGR_EVENTS& operator=(const MGR_EVENTS& other)
		{
			if (&other == this)
			{
				return *this;
			}

			mgr_open_service_ack = other.mgr_open_service_ack;
			mgr_close_service_ack = other.mgr_close_service_ack;
			mgr_requestdataversion_ack = other.mgr_requestdataversion_ack;
			mgr_get_puc_info_ack = other.mgr_get_puc_info_ack;
			mgr_get_pucsystem_info_ack = other.mgr_get_pucsystem_info_ack;
			mgr_get_pucaccount_info_ack = other.mgr_get_pucaccount_info_ack;
			mgr_get_user_info_ack = other.mgr_get_user_info_ack;
			mgr_get_group_info_ack = other.mgr_get_group_info_ack;
			mgr_get_org_info_ack = other.mgr_get_org_info_ack;
			mgr_get_staff_info_ack = other.mgr_get_staff_info_ack;
			mgr_get_sap_into_ack = other.mgr_get_sap_into_ack;
			mgr_get_crosspatch_info_ack = other.mgr_get_crosspatch_info_ack;
			mgr_get_conference_info_ack = other.mgr_get_conference_info_ack;
			mgr_get_dgna_info_ack = other.mgr_get_dgna_info_ack;
			mgr_get_predefined_dgna_info_ack = other.mgr_get_predefined_dgna_info_ack;
			mgr_get_simulselect_info_ack = other.mgr_get_simulselect_info_ack;

			return *this;
		}

	}*PMGR_EVENTS;
}

#endif