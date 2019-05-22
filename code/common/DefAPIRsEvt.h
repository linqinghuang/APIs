#ifndef __DefAPIRsEvt_H__
#define __DefAPIRsEvt_H__

#include "DefAPIType.h"
#include "DefCallDisconnectReason.h"
#include "DefNumberType.h"


namespace MRPS
{

	/*号码*/
	typedef struct CallNumber
	{
		std::string   strSystemId;
		std::string   strNumber;		      ///<号码
		std::string   strGateway;	      ///<网关 拨打外网需要
		NumberType    type;	                          ///<号码类型

		CallNumber()
		{
			type = MRPS_NUMBER_TYPE_INDIVIDUAL;
		}

		CallNumber(const CallNumber& other)
		{
			strSystemId = other.strSystemId;
			strNumber = other.strNumber;
			strGateway = other.strGateway;
			type = other.type;
		}

		CallNumber& operator=(const CallNumber& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strNumber = other.strNumber;
			strGateway = other.strGateway;
			type = other.type;
			return *this;
		}
	}CallNumber;




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
	struct Param_RS_OpenServiceAck_Evt : public Param_Base
	{
		std::string        strSystemId;
		OpenRSResult       result;
		time_t             timeStamp;

		Param_RS_OpenServiceAck_Evt()
		{
			type = ParamType_Param_RS_OpenServiceAck_Evt;
			result = OPEN_RS_SUCCESS;
			timeStamp = std::time(NULL);
		}

		Param_RS_OpenServiceAck_Evt(const Param_RS_OpenServiceAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_RS_OpenServiceAck_Evt& operator=(const Param_RS_OpenServiceAck_Evt& other)
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
	typedef int(*MRPS_RS_OpenServiceAck_Evt)(const Param_RS_OpenServiceAck_Evt& param);


	typedef enum CloseRSResult
	{
		CLOSE_RS_SUCCESS = 0,	            ///< 成功		
	}CloseRSResult;

	struct Param_RS_CloseServiceAck_Evt : public Param_Base
	{
		std::string        strSystemId;
		CloseRSResult      result;
		time_t             timeStamp;

		Param_RS_CloseServiceAck_Evt()
		{
			type = ParamType_Param_RS_CloseServiceAck_Evt;
			result = CLOSE_RS_SUCCESS;
			timeStamp = std::time(NULL);
		}

		Param_RS_CloseServiceAck_Evt(const Param_RS_CloseServiceAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_RS_CloseServiceAck_Evt& operator=(const Param_RS_CloseServiceAck_Evt& other)
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
	typedef int(*MRPS_RS_CloseServiceAck_Evt)(const Param_RS_CloseServiceAck_Evt& param);


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
	struct Param_RS_StartRecordAck_Evt : public Param_Base
	{
		std::string        strSystemId;
		std::string        strPucId;
		std::string        strPucSystemId;
		StartRecordResult  result;
		CallNumber         number;
		int                iLevel;
		time_t             timeStamp;

		Param_RS_StartRecordAck_Evt()
		{
			type = ParamType_Param_RS_StartRecordAck_Evt;
			result = StartRecord_Success;
			iLevel = 0;
			timeStamp = std::time(NULL);
		}

		Param_RS_StartRecordAck_Evt(const Param_RS_StartRecordAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			number = other.number;
			iLevel = other.iLevel;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_RS_StartRecordAck_Evt& operator=(const Param_RS_StartRecordAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			number = other.number;
			iLevel = other.iLevel;
			result = other.result;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_RS_StartRecordAck_Evt)(const Param_RS_StartRecordAck_Evt& param);

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
	struct Param_RS_StopRecordAck_Evt : public Param_Base
	{
		std::string        strSystemId;
		std::string        strPucId;
		std::string        strPucSystemId;
		StopRecordResult   result;
		CallNumber         number;
		int                iLevel;
		time_t             timeStamp;

		Param_RS_StopRecordAck_Evt()
		{
			type = ParamType_Param_RS_StartRecordAck_Evt;
			result = StopRecord_Success;
			iLevel = 0;
			timeStamp = std::time(NULL);
		}

		Param_RS_StopRecordAck_Evt(const Param_RS_StopRecordAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			result = other.result;
			number = other.number;
			iLevel = other.iLevel;
			timeStamp = other.timeStamp;
		}

		Param_RS_StopRecordAck_Evt& operator=(const Param_RS_StopRecordAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			result = other.result;
			number = other.number;
			iLevel = other.iLevel;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_RS_StopRecordAck_Evt)(const Param_RS_StopRecordAck_Evt& param);


	/*定制录音ACK事件结果枚举定义*/
	typedef enum MON_MontierResult
	{
		MON_Montier_Success = 0,                      ///<成功
		MON_Montier_Fail = 1,                         ///<失败
	}MON_MontierResult;

	/** PDT短信、上下线监听事件
	@param [in]   result		    结果

	@return
	*/
	struct Param_MON_MoninterAck_Evt : public Param_Base
	{
		std::string        strSystemId;
		std::string        strPucId;
		std::string        strPucSystemId;
		MON_MontierResult  result;
		CallNumber         number;
		int                iLevel;
		time_t             timeStamp;

		Param_MON_MoninterAck_Evt()
		{
			type = ParamType_Param_MON_MoninterAck_Evt;
			result = MON_Montier_Success;
			iLevel = 0;
			timeStamp = std::time(NULL);
		}

		Param_MON_MoninterAck_Evt(const Param_MON_MoninterAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			number = other.number;
			iLevel = other.iLevel;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_MON_MoninterAck_Evt& operator=(const Param_MON_MoninterAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			number = other.number;
			iLevel = other.iLevel;
			result = other.result;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_MON_MoninterAck_Evt)(const Param_MON_MoninterAck_Evt& param);


	enum MediaType
	{
		MediaType_UNKNOWN = -1,
		MediaType_Audio = 1,
		MediaType_Video = 2,
	};

	/** 呼叫优先级: 0默认等级 1-10 普通级 11-14优先级 15 紧急呼叫*/
	typedef int CallPriority;

	/*加密类型枚举定义*/
	typedef enum EncryptAlgorithmType
	{
		CALL_ENCRYPT_NONE = 0,
		CALL_ENCRYPT_SOFT = 1,                        ///软加密呼叫
		CALL_ENCRYPT_HARD = 2,                        ///硬加密呼叫
		CALL_ENCRYPT_MAX
	}EncryptAlgorithmType;

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
	struct Param_RS_SetupCallAck_Evt : public Param_Base
	{
		std::string          strSystemId;
		std::string          strPucId;
		std::string          strCallId;
		std::string          strPucSystemId;
		CallNumber           caller;
		CallNumber           called;
		CallType             calltype;
		MediaType            mediaType;
		int                  iMediaCode;
		int                  iPrioAttribute;
		CallPriority         priority;
		bool                 bDuplexmode;
		bool                 bEncrytFlag;
		int                  iHookSignalingFlag;
		EncryptAlgorithmType algorithmType;
		std::string          strFrameRate;
		std::string          strFrameSize;
		SetupCallResult      result;
		time_t               timeStamp;

		Param_RS_SetupCallAck_Evt()
		{
			type = ParamType_Param_RS_SetupCallAck_Evt;
			mediaType = MediaType_Audio;
			calltype = MRPS_CALL_TYPE_UNKNOWN;
			mediaType = MediaType_UNKNOWN;
			iMediaCode = 0;
			iPrioAttribute = 0;
			bDuplexmode = false;
			priority = 0;
			bEncrytFlag = false;
			algorithmType = CALL_ENCRYPT_NONE;
			result = SETUP_CALL_SUCCESS;
			bEncrytFlag = false;
			iHookSignalingFlag = 0;
			timeStamp = std::time(NULL);
		}

		Param_RS_SetupCallAck_Evt(const Param_RS_SetupCallAck_Evt& other)
		{
			strSystemId = other.strSystemId;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strFrameRate = other.strFrameRate;
			strFrameSize = other.strFrameSize;
			strCallId = other.strCallId;
			caller = other.caller;
			called = other.called;
			calltype = other.calltype;
			mediaType = other.mediaType;
			iMediaCode = other.iMediaCode;
			iPrioAttribute = other.iPrioAttribute;
			iHookSignalingFlag = other.iHookSignalingFlag;
			priority = other.priority;
			bDuplexmode = other.bDuplexmode;
			bEncrytFlag = other.bEncrytFlag;
			algorithmType = other.algorithmType;
			result = other.result;
			timeStamp = other.timeStamp;
		}

		Param_RS_SetupCallAck_Evt& operator=(const Param_RS_SetupCallAck_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			strFrameRate = other.strFrameRate;
			strFrameSize = other.strFrameSize;
			strCallId = other.strCallId;
			caller = other.caller;
			called = other.called;
			calltype = other.calltype;
			mediaType = other.mediaType;
			iMediaCode = other.iMediaCode;
			iPrioAttribute = other.iPrioAttribute;
			iHookSignalingFlag = other.iHookSignalingFlag;
			priority = other.priority;
			bDuplexmode = other.bDuplexmode;
			bEncrytFlag = other.bEncrytFlag;
			algorithmType = other.algorithmType;
			result = other.result;
			timeStamp = other.timeStamp;
			return *this;
		}
	};

	typedef int(*MRPS_RS_SetupCallAck_Evt)(const Param_RS_SetupCallAck_Evt& param);


	/** 呼叫连接事件
	@param [in]   callId			呼叫建立后的呼叫id
	@param [in]   time_stamp;		时间戳

	@return
	@note

	*/
	struct Param_RS_Connected_Evt : public Param_Base
	{
		std::string        strSystemId;
		std::string        strCallId;
		time_t             timeStamp;

		Param_RS_Connected_Evt()
		{
			type = ParamType_Param_RS_Connected_Evt;
			timeStamp = std::time(NULL);
		}

		Param_RS_Connected_Evt(const Param_RS_Connected_Evt& other)
		{
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			timeStamp = other.timeStamp;
		}

		Param_RS_Connected_Evt& operator=(const Param_RS_Connected_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_RS_Connected_Evt)(const Param_RS_Connected_Evt& param);





	/** 呼叫挂断事件
	@param [in]   call_id			    呼叫建立后的呼叫id
	@param [in]   reason				呼叫断开原因
	@param [in]   timeStamp			    时间戳

	@return
	*/
	struct Param_RS_Disconnected_Evt : public Param_Base
	{
		std::string          strSystemId;
		std::string          strCallId;
		std::string          strConnectFlag;
		CallDisconnectReason reason;
		time_t               timeStamp;

		Param_RS_Disconnected_Evt()
		{
			type = ParamType_Param_RS_Disconnected_Evt;
			reason = MRPS_UNKNOWN;
			timeStamp = std::time(NULL);
		}

		Param_RS_Disconnected_Evt(const Param_RS_Disconnected_Evt& other)
		{
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			reason = other.reason;
			timeStamp = other.timeStamp;
			strConnectFlag = other.strConnectFlag;
		}

		Param_RS_Disconnected_Evt& operator=(const Param_RS_Disconnected_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			reason = other.reason;
			timeStamp = other.timeStamp;
			strConnectFlag = other.strConnectFlag;
			return *this;
		}
	};
	typedef int(*MRPS_RS_Disconnected_Evt)(const Param_RS_Disconnected_Evt& param);


	/** 话权变更事件
	@param [in]   callId		    呼叫id
	@param [in]   speaker		    获取通话权的号码
	@param [in]   timeStamp 	    时间戳

	@return
	*/
	struct Param_RS_TxGranted_Evt : public Param_Base
	{
		std::string          strSystemId;
		std::string          strCallId;
		CallNumber           speaker;
		time_t               timeStamp;

		Param_RS_TxGranted_Evt()
		{
			type = ParamType_Param_RS_TxGranted_Evt;
			timeStamp = std::time(NULL);
		}

		Param_RS_TxGranted_Evt(const Param_RS_TxGranted_Evt& other)
		{
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			speaker = other.speaker;
			timeStamp = other.timeStamp;
		}

		Param_RS_TxGranted_Evt& operator=(const Param_RS_TxGranted_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			speaker = other.speaker;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_RS_TxGranted_Evt)(const Param_RS_TxGranted_Evt& param);

	/** 话权释放事件
	@param [in]   callId		    呼叫id
	@param [in]   timeStamp	        时间戳
	@return
	*/
	struct Param_RS_TxCease_Evt : public Param_Base
	{
		std::string          strSystemId;
		std::string          strCallId;
		CallNumber           speaker;
		std::string          strResultCode;
		time_t               timeStamp;


		Param_RS_TxCease_Evt()
		{
			type = ParamType_Param_RS_TxCease_Evt;
			timeStamp = std::time(NULL);
		}

		Param_RS_TxCease_Evt(const Param_RS_TxCease_Evt& other)
		{
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			speaker = other.speaker;
			strResultCode = other.strResultCode;
			timeStamp = other.timeStamp;
		}

		Param_RS_TxCease_Evt& operator=(const Param_RS_TxCease_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			speaker = other.speaker;
			strResultCode = other.strResultCode;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_RS_TxCease_Evt)(const Param_RS_TxCease_Evt& param);


	struct Param_RS_VideoSourceInd_Evt : public Param_Base
	{
		std::string          strSystemId;
		std::string          strCallId;
		std::string          strVideoId;
		std::string          strVideoType;
		time_t               timeStamp;


		Param_RS_VideoSourceInd_Evt()
		{
			type = ParamType_Param_RS_TxCease_Evt;
			timeStamp = std::time(NULL);
		}

		Param_RS_VideoSourceInd_Evt(const Param_RS_VideoSourceInd_Evt& other)
		{
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			strVideoId = other.strVideoId;
			strVideoType = other.strVideoType;
			timeStamp = other.timeStamp;
		}

		Param_RS_VideoSourceInd_Evt& operator=(const Param_RS_VideoSourceInd_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			strVideoId = other.strVideoId;
			strVideoType = other.strVideoType;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_RS_VideoSourceInd_Evt)(const Param_RS_VideoSourceInd_Evt& param);


	/// 呼叫的语音RTP资源参数
	typedef struct  Voice_Resources_Rtp
	{
		std::string    strFromIp;   ///<rtp的ip地址
		std::string    strFromPort;	///<rtp的端口号		
		std::string    strToIp;		///<rtp的ip地址
		std::string    strToPort;	///<rtp的端口号	

		Voice_Resources_Rtp()
		{

		}

		Voice_Resources_Rtp(const Voice_Resources_Rtp& other)
		{
			strFromIp = other.strFromIp;
			strFromPort = other.strFromPort;
			strToIp = other.strToIp;
			strToPort = other.strToPort;
		}

		Voice_Resources_Rtp& operator=(const Voice_Resources_Rtp& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strFromIp = other.strFromIp;
			strFromPort = other.strFromPort;
			strToIp = other.strToIp;
			strToPort = other.strToPort;
			return *this;
		}
	}Voice_Resources_Rtp;


	struct ParamRtp_Audio
	{
		Voice_Resources_Rtp rtpAudioInfo;
		std::string strAudioCodec;
		std::string strAMRParameter;
		int         iAudioCodec;
		int         iBitrate;
		int         iPayloadType;
		int         iPayloadFormat;
		int         iSuportPDCP;
		int         iPTime;

		ParamRtp_Audio()
		{
			iAudioCodec = 0;
			iPayloadType = 0;
			iPayloadType = 0;
			iPayloadFormat = 0;
			iSuportPDCP = 0;
			iPTime = 0;
			iBitrate = 0;
		}

		ParamRtp_Audio(const ParamRtp_Audio& other)
		{
			rtpAudioInfo = other.rtpAudioInfo;
			strAudioCodec = other.strAudioCodec;
			strAMRParameter = other.strAMRParameter;
			iAudioCodec = other.iAudioCodec;
			iBitrate = other.iBitrate;
			iPayloadType = other.iPayloadType;
			iPayloadFormat = other.iPayloadFormat;
			iSuportPDCP = other.iSuportPDCP;
			iPTime = other.iPTime;
		}

		ParamRtp_Audio& operator=(const ParamRtp_Audio& other)
		{
			if (this == &other)
			{
				return *this;
			}
			rtpAudioInfo = other.rtpAudioInfo;
			strAudioCodec = other.strAudioCodec;
			strAMRParameter = other.strAMRParameter;
			iAudioCodec = other.iAudioCodec;
			iBitrate = other.iBitrate;
			iPayloadType = other.iPayloadType;
			iPayloadFormat = other.iPayloadFormat;
			iSuportPDCP = other.iSuportPDCP;
			iPTime = other.iPTime;
			return *this;
		}
	};

	struct ParamRtp_Video
	{
		Voice_Resources_Rtp rtpVideoInfo;
		std::string strVideoCodec;
		std::string strH264Parameter;
		std::string strVideoFrameRate;
		std::string strVideoFrameSize;
		int         iVideoCodec;
		int         iVideoFrameRate;
		int         iVideoFrameSize;
		int         iVideoPayloadType;

		ParamRtp_Video()
		{
			iVideoCodec = 0;
			iVideoFrameRate = 0;
			iVideoFrameSize = 0;
			iVideoPayloadType = 0;
		}

		ParamRtp_Video(const ParamRtp_Video& other)
		{
			rtpVideoInfo = other.rtpVideoInfo;
			strVideoCodec = other.strVideoCodec;
			strH264Parameter = other.strH264Parameter;
			strVideoFrameRate = other.strVideoFrameRate;
			strVideoFrameSize = other.strVideoFrameSize;
			iVideoCodec = other.iVideoCodec;
			iVideoFrameRate = other.iVideoFrameRate;
			iVideoFrameSize = other.iVideoFrameSize;
			iVideoPayloadType = other.iVideoPayloadType;
		}

		ParamRtp_Video& operator=(const ParamRtp_Video& other)
		{
			if (this == &other)
			{
				return *this;
			}
			rtpVideoInfo = other.rtpVideoInfo;
			strVideoCodec = other.strVideoCodec;
			strH264Parameter = other.strH264Parameter;
			strVideoFrameRate = other.strVideoFrameRate;
			strVideoFrameSize = other.strVideoFrameSize;
			iVideoCodec = other.iVideoCodec;
			iVideoFrameRate = other.iVideoFrameRate;
			iVideoFrameSize = other.iVideoFrameSize;
			iVideoPayloadType = other.iVideoPayloadType;
			return *this;
		}
	};

	struct ParamRtp_Channel
	{
		std::string strMemberGuid;
		std::string strId;
		std::string strNumber;
		bool bHaveAudio;
		bool bHaveVideo;
		ParamRtp_Audio audio;
		ParamRtp_Video video;

		ParamRtp_Channel()
		{
			bHaveAudio = false;
			bHaveVideo = false;
		}

		ParamRtp_Channel(const ParamRtp_Channel& other)
		{
			bHaveAudio = other.bHaveAudio;
			bHaveVideo = other.bHaveVideo;
			audio = other.audio;
			video = other.video;
			strMemberGuid = other.strMemberGuid;
			strNumber = other.strNumber;
			strId = other.strId;
		}

		ParamRtp_Channel& operator=(const ParamRtp_Channel& other)
		{
			if (&other == this)
			{
				return *this;
			}

			bHaveAudio = other.bHaveAudio;
			bHaveVideo = other.bHaveVideo;
			audio = other.audio;
			video = other.video;
			strMemberGuid = other.strMemberGuid;
			strNumber = other.strNumber;
			strId = other.strId;
			return *this;
		}
	};

	enum RTPRequestMode
	{
		RTPRequestMode_Unknown = 0,
		RTPRequestMode_Normal,
		RTPRequestMode_InsertSpeaker,
		RTPRequestMode_CallUpgrade,
		RTPRequestMode_CallDegrade,
	};

	struct Param_RTPInfo
	{
		std::string strCallId;
		int         iRequestMode;
		//std::string strMemberGuid;		
		//std::vector<ParamRtp_Audio> vecAudioInfos;
		//std::vector<ParamRtp_Video> vecVideoInfos;
		std::vector<ParamRtp_Channel> vecRtpChannels;

		Param_RTPInfo()
		{
			iRequestMode = RTPRequestMode_Unknown;
		}

		Param_RTPInfo(const Param_RTPInfo& other)
		{
			strCallId = other.strCallId;
			iRequestMode = other.iRequestMode;
			vecRtpChannels = other.vecRtpChannels;
		}

		Param_RTPInfo& operator=(const Param_RTPInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strCallId = other.strCallId;
			iRequestMode = other.iRequestMode;
			vecRtpChannels = other.vecRtpChannels;
			return *this;
		}
	};

	

	/** 语音资源事件
	@param [in]   callId		    呼叫id
	@param [in]   pRtpResource		    语音来源方（全双工时语音两路，建议主叫语音按左声道写录音文件，被叫语音按右声道写录音文件。）
	@param [in]   iNeedRequestRtp	    0：表示不需要发送接收rtp信息  1：表示需要发送接收的rtp信息
	@param [in]   bIsThawingScreen	    0：表示非融屏  1：表示融屏
	@param [in]   timeStamp	        时间戳
	@return
	*/
	struct Param_RS_RtpResource_Evt : public Param_Base
	{
		std::string          strSystemId;
		Param_RTPInfo        rtpInfo;
		int                  iNeedRequestRtp;		
		bool                 bIsThawingScreen;
		time_t               timeStamp;

		Param_RS_RtpResource_Evt()
		{
			type = ParamType_Param_RS_RtpResource_Evt;
			iNeedRequestRtp = 0;
			bIsThawingScreen = false;			
			timeStamp = std::time(NULL);
		}

		Param_RS_RtpResource_Evt(const Param_RS_RtpResource_Evt& other)
		{
			bIsThawingScreen = other.bIsThawingScreen;
			strSystemId = other.strSystemId;
			rtpInfo = other.rtpInfo;
			iNeedRequestRtp = other.iNeedRequestRtp;			
			timeStamp = other.timeStamp;
		}

		Param_RS_RtpResource_Evt& operator=(const Param_RS_RtpResource_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			bIsThawingScreen = other.bIsThawingScreen;
			strSystemId = other.strSystemId;
			rtpInfo = other.rtpInfo;
			iNeedRequestRtp = other.iNeedRequestRtp;			
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_RS_RtpSource_Evt)(const Param_RS_RtpResource_Evt& param);


	struct MemberInfo
	{
		std::string strId;
		std::string strNumber;
		std::string strNumberType;
		std::string strNumberSystemId;
		std::string strMemberGuid;
		bool        bHaveAudio;
		std::string strAudioCodec;
		bool        bHaveVideo;
		std::string strVideoCodec;
		std::string strFrameRate;
		std::string strFrameSize;

		MemberInfo()
		{
			bHaveAudio = false;
			bHaveVideo = false;
		}
		MemberInfo(const MemberInfo& other)
		{
			strNumberSystemId = other.strNumberSystemId;
			strNumber = other.strNumber;
			strNumberType = other.strNumberType;
			strMemberGuid = other.strMemberGuid;
			bHaveAudio = other.bHaveAudio;
			strAudioCodec = other.strAudioCodec;
			bHaveVideo = other.bHaveVideo;
			strVideoCodec = other.strVideoCodec;
			strFrameRate = other.strFrameRate;
			strFrameSize = other.strFrameSize;
			strId = other.strId;
		}

		MemberInfo& operator=(const MemberInfo& other)
		{
			if (&other == this)
			{
				return *this;
			}
			strNumberSystemId = other.strNumberSystemId;
			strNumber = other.strNumber;
			strNumberType = other.strNumberType;
			strMemberGuid = other.strMemberGuid;
			bHaveAudio = other.bHaveAudio;
			strAudioCodec = other.strAudioCodec;
			bHaveVideo = other.bHaveVideo;
			strVideoCodec = other.strVideoCodec;
			strFrameRate = other.strFrameRate;
			strFrameSize = other.strFrameSize;
			strId = other.strId;
			return *this;
		}
	};

	struct Param_RS_MemberConnected_Evt : public Param_Base
	{
		std::string             strSystemId;
		std::string             strCallId;
		bool                    bIsNeedRequestRtp;
		std::vector<MemberInfo> vecMemberInfos;
		time_t                  timeStamp;

		Param_RS_MemberConnected_Evt()
		{
			type = ParamType_Param_RS_MemberConnected_Evt;
			bIsNeedRequestRtp = false;
			timeStamp = std::time(NULL);
		}

		Param_RS_MemberConnected_Evt(const Param_RS_MemberConnected_Evt& other)
		{
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			vecMemberInfos = other.vecMemberInfos;
			bIsNeedRequestRtp = other.bIsNeedRequestRtp;;
			timeStamp = other.timeStamp;
		}

		Param_RS_MemberConnected_Evt& operator=(const Param_RS_MemberConnected_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			vecMemberInfos = other.vecMemberInfos;
			bIsNeedRequestRtp = other.bIsNeedRequestRtp;
			timeStamp = other.timeStamp;
			return *this;
		}
	};

	typedef int(*MRPS_RS_Member_Connect_Evt)(const Param_RS_MemberConnected_Evt& param);


	struct Param_RS_MemberDisonnected_Evt : public Param_Base
	{
		std::string strSystemId;
		std::string strCallId;
		std::string strNumber;
		std::string strNumberType;
		std::string strMemberGuid;
		std::string strAudioCodec;
		std::string strVideoCodec;
		time_t      timeStamp;

		Param_RS_MemberDisonnected_Evt()
		{
			type = ParamType_Param_RS_MemberDisonnected_Evt;
			timeStamp = std::time(NULL);
		}

		Param_RS_MemberDisonnected_Evt(const Param_RS_MemberDisonnected_Evt& other)
		{
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			strNumber = other.strNumber;
			strNumberType = other.strNumberType;
			strMemberGuid = other.strMemberGuid;
			strAudioCodec = other.strAudioCodec;
			strVideoCodec = other.strVideoCodec;
			timeStamp = other.timeStamp;
		}

		Param_RS_MemberDisonnected_Evt& operator=(const Param_RS_MemberDisonnected_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			strNumber = other.strNumber;
			strNumberType = other.strNumberType;
			strMemberGuid = other.strMemberGuid;
			strAudioCodec = other.strAudioCodec;
			strVideoCodec = other.strVideoCodec;
			timeStamp = other.timeStamp;
			return *this;
		}
	};

	typedef int(*MRPS_RS_Member_Disconnected_Evt)(const Param_RS_MemberDisonnected_Evt& param);

	enum AppendNumber_Type
	{
		AppendNumber_Type_Unknown = 0,
		AppendNumber_Type_Caller,
		AppendNumber_Type_Called,
		AppendNumber_Type_Append,
	};

	struct Param_RS_AppendSpeaker : public Param_Base
	{
		std::string strSystemId;
		std::string strCallId;
		CallNumber  number;
		AppendNumber_Type appendNumberType;
		time_t      timeStamp;

		Param_RS_AppendSpeaker()
		{
			type = ParamType_Param_RS_AppendSpeaker;
			timeStamp = std::time(NULL);
			appendNumberType = AppendNumber_Type_Unknown;
		}

		Param_RS_AppendSpeaker(const Param_RS_AppendSpeaker& other)
		{
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			number = other.number;
			timeStamp = other.timeStamp;
			appendNumberType = other.appendNumberType;
		}

		Param_RS_AppendSpeaker& operator=(const Param_RS_AppendSpeaker& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			number = other.number;
			timeStamp = other.timeStamp;
			appendNumberType = other.appendNumberType;
			return *this;
		}
	};

	typedef int(*MRPS_RS_AppendSpeaker_Evt)(const Param_RS_AppendSpeaker& param);

	struct Param_RS_VoiceReceive : public Param_Base
	{
		std::string		strSystemId;
		std::string		strCallId;
		const char*		pDataBuf;
		unsigned short	sDataLen;
		unsigned short	sBatchNo;
		CallNumber		Speaker;
		time_t			timeStamp;

		Param_RS_VoiceReceive()
		{
			type = ParamType_Param_RS_AppendSpeaker;
			timeStamp = std::time(NULL);
			pDataBuf = NULL;
			sDataLen = 0;
			sBatchNo = 0;
		}

		Param_RS_VoiceReceive(const Param_RS_VoiceReceive& other)
		{
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			pDataBuf = other.pDataBuf;
			sDataLen = other.sDataLen;
			sBatchNo = other.sBatchNo;
			Speaker = other.Speaker;
			timeStamp = other.timeStamp;
		}

		Param_RS_VoiceReceive& operator=(const Param_RS_VoiceReceive& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strCallId = other.strCallId;
			pDataBuf = other.pDataBuf;
			sDataLen = other.sDataLen;
			sBatchNo = other.sBatchNo;
			Speaker = other.Speaker;
			timeStamp = other.timeStamp;
			return *this;
		}
	};

	enum Rs_SdsType
	{
		Rs_SdsType_Unknown = -1,
		Rs_SdsType_Status = 1,
		Rs_SdsType_Text = 2,
		Rs_SdsType_Media = 3,
	};

	struct Sds_Media_Info
	{
		int iMediaType;//文件类型 1、图片 2、音频 3、视频
		std::string strOrgName;
		std::string strBrief;//概要
		int iFileSize;//文件大小
		std::string strThumbnail;//缩略图
		std::string strAuthgrant;//校验码
		std::string strUser;
		std::string strPassword;
		std::string strUrl;

		Sds_Media_Info(){ iMediaType = -1; iFileSize = 0; }
		Sds_Media_Info(const Sds_Media_Info& other)
		{
			iMediaType = other.iMediaType;
			strOrgName = other.strOrgName;
			strBrief = other.strBrief;
			iFileSize = other.iFileSize;
			strThumbnail = other.strThumbnail;
			strAuthgrant = other.strAuthgrant;
			strUser = other.strUser;
			strPassword = other.strPassword;
			strUrl = other.strUrl;
		}

		Sds_Media_Info& operator=(const Sds_Media_Info& other)
		{
			if (&other == this)
			{
				return *this;
			}

			iMediaType = other.iMediaType;
			strOrgName = other.strOrgName;
			strBrief = other.strBrief;
			iFileSize = other.iFileSize;
			strThumbnail = other.strThumbnail;
			strAuthgrant = other.strAuthgrant;
			strUser = other.strUser;
			strPassword = other.strPassword;
			strUrl = other.strUrl;
			return *this;
		}
	};

	struct Sds_Media_Content
	{
		std::vector<Sds_Media_Info> vecMedias;
		std::string strText;

		Sds_Media_Content(){}

		Sds_Media_Content(const Sds_Media_Content& other)
		{
			vecMedias = other.vecMedias;
			strText = other.strText;
		}

		Sds_Media_Content& operator=(const Sds_Media_Content& other)
		{
			if (&other == this)
			{
				return *this;
			}

			vecMedias = other.vecMedias;
			strText = other.strText;
			return *this;
		}
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
	struct Param_RS_Sds_Evt : public Param_Base
	{
		std::string          strSystemId;
		std::string          strSdsId;
		std::string          strPucId;
		std::string          strPucSystemId;
		CallNumber           sender;
		CallNumber           receiver;
		Rs_SdsType           msgType;
		EncryptAlgorithmType algorithmType;
		int                  iEncryptFlag;
		int                  iFlashFlag;
		int                  iEmergencyFlag;
		int                  iSdsSendMode;
		int                  iCodeType;
		std::string          strContent;;
		int                  iResult;
		time_t               timeStamp;

		Sds_Media_Content    mediaContent;

		Param_RS_Sds_Evt()
		{
			type = ParamType_Param_RS_Sds_Evt;
			msgType = Rs_SdsType_Unknown;
			algorithmType = CALL_ENCRYPT_NONE;
			iEncryptFlag = 0;
			iFlashFlag = 0;
			iEmergencyFlag = 0;
			iSdsSendMode = 0;
			iResult = 0;
			iCodeType = 0;
			timeStamp = std::time(NULL);
		}

		Param_RS_Sds_Evt(const Param_RS_Sds_Evt& other)
		{
			strSystemId = other.strSystemId;
			strSdsId = other.strSdsId;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			sender = other.sender;
			receiver = other.receiver;
			msgType = other.msgType;
			algorithmType = other.algorithmType;
			iEncryptFlag = other.iEncryptFlag;
			iFlashFlag = other.iFlashFlag;
			iEmergencyFlag = other.iEmergencyFlag;
			iSdsSendMode = other.iSdsSendMode;
			iCodeType = other.iCodeType;
			strContent = other.strContent;
			iResult = other.iResult;
			mediaContent = other.mediaContent;
			timeStamp = other.timeStamp;
		}

		Param_RS_Sds_Evt& operator=(const Param_RS_Sds_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strSdsId = other.strSdsId;
			strPucId = other.strPucId;
			strPucSystemId = other.strPucSystemId;
			sender = other.sender;
			receiver = other.receiver;
			msgType = other.msgType;
			algorithmType = other.algorithmType;
			iEncryptFlag = other.iEncryptFlag;
			iFlashFlag = other.iFlashFlag;
			iEmergencyFlag = other.iEmergencyFlag;
			iSdsSendMode = other.iSdsSendMode;
			iCodeType = other.iCodeType;
			strContent = other.strContent;
			iResult = other.iResult;
			timeStamp = other.timeStamp;
			mediaContent = other.mediaContent;
			return *this;
		}
	};
	typedef int(*MRPS_RS_Sds_Evt)(const Param_RS_Sds_Evt& param);


	typedef struct  Regist_Status
	{
		std::string          strPucId;
		std::string          strDeviceId;
		std::string          strSapGuid;
		std::string          strBasestationId;
		CallNumber           target;
		int                  iRegistStatus;
		int                  iRegistType;//0：初始注册；1：周期注册
		int                  iUpdatePeriod;
		int                  iStunStatus;
		bool                 bHaveDeviceId;

		time_t               regTime;

		std::string          strTrunkingCapability;
		std::string          strAudioCodecCapability;
		std::string          strVideoCodecCapability;

		Regist_Status()
		{
			iRegistStatus = 0;
			iRegistType = 0;
			iUpdatePeriod = 0;
			iStunStatus = 0;
			bHaveDeviceId = true;

			regTime = time(NULL);

		}

		Regist_Status(const Regist_Status& other)
		{
			strPucId = other.strPucId;
			strDeviceId = other.strDeviceId;
			strSapGuid = other.strSapGuid;
			strBasestationId = other.strBasestationId;
			target = other.target;
			iRegistStatus = other.iRegistStatus;
			iRegistType = other.iRegistType;
			iUpdatePeriod = other.iUpdatePeriod;
			iStunStatus = other.iStunStatus;
			regTime = other.regTime;
			bHaveDeviceId = other.bHaveDeviceId;

			strTrunkingCapability = other.strTrunkingCapability;
			strAudioCodecCapability = other.strAudioCodecCapability;
			strVideoCodecCapability = other.strVideoCodecCapability;
		}

		Regist_Status& operator=(const Regist_Status& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strPucId = other.strPucId;
			strDeviceId = other.strDeviceId;
			strSapGuid = other.strSapGuid;
			strBasestationId = other.strBasestationId;
			target = other.target;
			iRegistStatus = other.iRegistStatus;
			iRegistType = other.iRegistType;
			iUpdatePeriod = other.iUpdatePeriod;
			iStunStatus = other.iStunStatus;
			regTime = other.regTime;
			bHaveDeviceId = other.bHaveDeviceId;

			strTrunkingCapability = other.strTrunkingCapability;
			strAudioCodecCapability = other.strAudioCodecCapability;
			strVideoCodecCapability = other.strVideoCodecCapability;
			return *this;
		}
	}Regist_Status;

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
	struct Param_RS_Register_Evt : public Param_Base
	{
		std::string          strSystemId;
		std::string          strPucId;
		std::vector<Regist_Status> vecStatus;
		time_t               timeStamp;

		Param_RS_Register_Evt()
		{
			type = ParamType_Param_RS_Register_Evt;
			timeStamp = std::time(NULL);
		}

		Param_RS_Register_Evt(const Param_RS_Register_Evt& other)
		{
			strSystemId = other.strSystemId;
			strPucId = other.strPucId;
			vecStatus = other.vecStatus;
			timeStamp = other.timeStamp;
		}

		Param_RS_Register_Evt& operator=(const Param_RS_Register_Evt& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strPucId = other.strPucId;
			vecStatus = other.vecStatus;
			timeStamp = other.timeStamp;
			return *this;
		}
	};
	typedef int(*MRPS_RS_Register_Evt)(const Param_RS_Register_Evt& param);

	enum AppendSetupFlag
	{
		AppendSetupFlag_Unknown = 0,
		AppendSetupFlag_HaveSetup,
		AppendSetupFlag_NoSetup,
	};

	struct Param_RS_AppendInfo : public Param_Base
	{
		std::string strSystemId;
		std::string strAppendInfo;
		std::string strCallId;
		int         iAppendFlag;
		time_t      timeStamp;

		Param_RS_AppendInfo()
		{
			type = ParamType_Param_RS_AppendInfo;
			timeStamp = std::time(NULL);	
			iAppendFlag = AppendSetupFlag_Unknown;
		}

		Param_RS_AppendInfo(const Param_RS_AppendInfo& other)
		{
			strSystemId = other.strSystemId;
			strAppendInfo = other.strAppendInfo;			
			timeStamp = other.timeStamp;
			strCallId = other.strCallId;
			iAppendFlag = other.iAppendFlag;
		}

		Param_RS_AppendInfo& operator=(const Param_RS_AppendInfo& other)
		{
			if (this == &other)
			{
				return *this;
			}
			strSystemId = other.strSystemId;
			strAppendInfo = other.strAppendInfo;
			timeStamp = other.timeStamp;
			strCallId = other.strCallId;
			iAppendFlag = other.iAppendFlag;
			return *this;
		}
	};

	typedef int(*MRPS_RS_AppendInfo_Evt)(const Param_RS_AppendInfo& param);

	//全网录音服务回调函数原型
	//录音模块初始函数原型，上层需要在初始化Api服务成功之后调用
	typedef struct RS_EVENTS
	{
		MRPS_RS_OpenServiceAck_Evt          rs_openservice_ack;
		MRPS_RS_CloseServiceAck_Evt         rs_closeservice_ack;
		MRPS_RS_StartRecordAck_Evt			rs_startrecord_ack;
		MRPS_RS_StopRecordAck_Evt			rs_stoprecord_ack;
		MRPS_RS_SetupCallAck_Evt			rs_setupcall;
		MRPS_RS_Connected_Evt				rs_connected;
		MRPS_RS_Disconnected_Evt			rs_disconnected;
		MRPS_RS_TxGranted_Evt				rs_txgranted;
		MRPS_RS_TxCease_Evt			        rs_txcease;
		MRPS_RS_Member_Connect_Evt          rs_member_connect_ack;
		MRPS_RS_Member_Disconnected_Evt     rs_member_disconnect_evt;
		MRPS_RS_RtpSource_Evt			    rs_rtpsource;
		MRPS_RS_VideoSourceInd_Evt          rs_videosourceind;
		MRPS_RS_AppendSpeaker_Evt           rs_appendnumber;
		MRPS_RS_Sds_Evt                     rs_sds_evt;
		MRPS_RS_Register_Evt                rs_register_evt;
		MRPS_RS_AppendInfo_Evt              rs_appendinfo_evt;
		MRPS_MON_MoninterAck_Evt			mon_MoniterAck_evt;

		RS_EVENTS()
		{
			rs_openservice_ack = NULL;
			rs_closeservice_ack = NULL;
			rs_startrecord_ack = NULL;
			rs_stoprecord_ack = NULL;
			rs_setupcall = NULL;
			rs_connected = NULL;
			rs_disconnected = NULL;
			rs_txgranted = NULL;
			rs_txcease = NULL;
			rs_member_connect_ack = NULL;
			rs_member_disconnect_evt = NULL;
			rs_rtpsource = NULL;
			rs_videosourceind = NULL;
			rs_appendnumber = NULL;
			rs_sds_evt = NULL;
			rs_register_evt = NULL;
			rs_appendinfo_evt = NULL;
			mon_MoniterAck_evt = NULL;
		}

		RS_EVENTS(const RS_EVENTS& other)
		{
			rs_openservice_ack = other.rs_openservice_ack;
			rs_closeservice_ack = other.rs_closeservice_ack;
			rs_startrecord_ack = other.rs_startrecord_ack;
			rs_stoprecord_ack = other.rs_stoprecord_ack;
			rs_setupcall = other.rs_setupcall;
			rs_connected = other.rs_connected;
			rs_disconnected = other.rs_disconnected;
			rs_txgranted = other.rs_txgranted;
			rs_txcease = other.rs_txcease;
			rs_member_connect_ack = other.rs_member_connect_ack;
			rs_member_disconnect_evt = other.rs_member_disconnect_evt;
			rs_rtpsource = other.rs_rtpsource;
			rs_videosourceind = other.rs_videosourceind;
			rs_appendnumber = other.rs_appendnumber;
			rs_sds_evt = other.rs_sds_evt;
			rs_register_evt = other.rs_register_evt;
			rs_appendinfo_evt = other.rs_appendinfo_evt;
			mon_MoniterAck_evt = other.mon_MoniterAck_evt;
		}

		RS_EVENTS& operator=(const RS_EVENTS& other)
		{
			if (&other == this)
			{
				return *this;
			}

			rs_openservice_ack = other.rs_openservice_ack;
			rs_closeservice_ack = other.rs_closeservice_ack;
			rs_startrecord_ack = other.rs_startrecord_ack;
			rs_stoprecord_ack = other.rs_stoprecord_ack;
			rs_setupcall = other.rs_setupcall;
			rs_connected = other.rs_connected;
			rs_disconnected = other.rs_disconnected;
			rs_txgranted = other.rs_txgranted;
			rs_txcease = other.rs_txcease;
			rs_member_connect_ack = other.rs_member_connect_ack;
			rs_member_disconnect_evt = other.rs_member_disconnect_evt;
			rs_rtpsource = other.rs_rtpsource;
			rs_videosourceind = other.rs_videosourceind;
			rs_appendnumber = other.rs_appendnumber;
			rs_sds_evt = other.rs_sds_evt;
			rs_register_evt = other.rs_register_evt;
			rs_appendinfo_evt = other.rs_appendinfo_evt;
			mon_MoniterAck_evt = other.mon_MoniterAck_evt;
			return *this;
		}

	}*PRS_EVENTS;
}

#endif