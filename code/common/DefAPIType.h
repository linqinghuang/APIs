#ifndef __DefAPIType_H__
#define __DefAPIType_H__

#include <vector>
#include <string>
#include <ctime>
#include <map>

namespace MRPS
{
	enum APIType
	{
		APIType_Unknown = 0,
		APIType_LTE,
		APIType_PDT,
		APIType_ICC,
		APIType_PUC,		
		APIType_3GPP,
		APIType_Tetra,		
	};

	enum ParamType
	{
		ParamType_Unknown = 0,
		ParamType_Param_InitializeAck_Evt,
		ParamType_Param_Heartbeat_Evt,
		ParamType_Param_LoginAck_Evt,
		ParamType_Param_LogoutAck_Evt,
		ParamType_Param_System_Evt,
		ParamType_Param_Log_Evt,
		ParamType_Param_Alarm_Evt,
		ParamType_Param_MGR_OpenServiceAck_Evt,
		ParamType_Param_MGR_CloseServiceAck_Evt,
		ParamType_Param_MGR_RequestDataVersion_Evt,
		ParamType_Param_MGR_GetPucInfoAck_Evt,
		ParamType_Param_MGR_GetPucSystemInfoAck_Evt,
		ParamType_Param_MGR_GetAccountInfoAck_Evt,
		ParamType_Param_MGR_GetUserInfoAck_Evt,
		ParamType_Param_MGR_GetGroupInfoAck_Evt,
		ParamType_Param_MGR_GetStaffInfoAck_Evt,
		ParamType_Param_MGR_GetOrgInfoAck_Evt,
		ParamType_Param_MGR_GetSapInfoAck_Evt,
		ParamType_Param_RS_OpenServiceAck_Evt,
		ParamType_Param_RS_CloseServiceAck_Evt,
		ParamType_Param_RS_StartRecordAck_Evt,
		ParamType_Param_RS_StopRecordAck_Evt,
		ParamType_Param_RS_SetupCallAck_Evt,
		ParamType_Param_RS_Connected_Evt,
		ParamType_Param_RS_Disconnected_Evt,
		ParamType_Param_RS_TxGranted_Evt,
		ParamType_Param_RS_TxCease_Evt,
		ParamType_Param_RS_MemberConnected_Evt,
		ParamType_Param_RS_MemberDisonnected_Evt,
		ParamType_Param_RS_RtpResource_Evt,
		ParamType_Param_RS_AppendSpeaker,
		ParamType_Param_RS_Sds_Evt,
		ParamType_Param_RS_Register_Evt,
		ParamType_Param_RS_AppendInfo,

		ParamType_Param_MGR_GetCrosspatchInfoAck_Evt,
		ParamType_Param_MGR_GetConferenceInfoAck_Evt,
		ParamType_Param_MGR_GetDgnaInfoAck_Evt,
		ParamType_Param_MGR_GetPreDgnaInfoAck_Evt,
		ParamType_Param_MGR_GetSimulselectInfoAck_Evt,

		ParamType_Param_MON_MoninterAck_Evt,
	};

	struct Param_Base
	{
		ParamType type;
		Param_Base(){ type = ParamType_Unknown; }
		virtual ~Param_Base(){}
	};

}

#endif