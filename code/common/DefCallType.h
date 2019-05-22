#ifndef __DefCallType_H__
#define __DefCallType_H__

namespace MRPS
{
	typedef enum CallType
	{
		MRPS_CALL_TYPE_UNKNOWN = -1,
		MRPS_CALL_TYPE_INDIVIDUAL_CALL = 0,                ///<单呼
		MRPS_CALL_TYPE_GROUP_CALL = 1,                     ///<组呼	    
		MRPS_CALL_TYPE_SYSTEM_CALL = 2,                    ///<系统全呼
		MRPS_CALL_TYPE_BROADCAST_CALL = 3,                 ///<广播呼		                 
		MRPS_CALL_TYPE_EXTERNAL_CALL = 4,                  ///<外部呼叫:PSAN/PABX,MSISDN	
		MRPS_CALL_TYPE_REMOTE_MONITOR_CALL = 5,            //远程监听呼叫
		MRPS_CALL_TYPE_ANALOG_CALL = 6,                    //模拟呼叫
		MRPS_CALL_TYPE_EMERGENCY_CALL = 7,                 //紧急呼叫
		MRPS_CALL_TYPE_CROSSPATCH_CALL = 8,                //跨系统派接呼叫
		MRPS_CALL_TYPE_INTERCOM_CALL = 9,                  //调度台间呼叫
		MRPS_CALL_TYPE_RECORDPAY_CALL = 10,                //录音回放
		MRPS_CALL_TYPE_INDIVIDUAL_VIDEOANDVOICE_CALL = 11, //可视单呼，有语音
		MRPS_CALL_TYPE_INDIVIDUAL_ONLYVIDEO_CALL = 12,     //可视单呼，无语音
		MRPS_CALL_TYPE_GROUP_VIDEOANDVOICE_CALL = 13,      //可视组呼，有语音
		MRPS_CALL_TYPE_GROUP_ONLYVIDEO_CALL = 14,          //可视组呼，无语音
		MRPS_CALL_TYPE_GROUP_DIFFERENTSOURCE_CALL = 15,    //不同源可视组呼
		MRPS_CALL_TYPE_BROADCAST_VOICE_CALL = 16,          //语音组播
		MRPS_CALL_TYPE_BROADCAST_VIDEO_CALL = 17,          //视频组播
		MRPS_CALL_TYPE_BROADCAST_ONLYVIDEO_CALL = 18,      //仅视频组播
		MRPS_CALL_TYPE_PULLVIDEO_CALL = 19,                //视频上拉
		MRPS_CALL_TYPE_DOWNVIDEO_CALL = 20,                //视频下拉
		MRPS_CALL_TYPE_BACKVIDEO_CALL = 21,                //视频回传
		MRPS_CALL_TYPE_PUSHVIDEO_CALL = 22,                //视频推送
		MRPS_CALL_TYPE_PULLVIDEOWITHVOICE_CALL = 23,       //视频上拉,供eLTE使用和hytera使用
		MRPS_CALL_TYPE_VIDEOFEEDBACKWITHVOICE_CALL = 24,   //视频回传, 供eLTE使用
		MRPS_CALL_TYPE_INTERCOMWITHVIDEO_CALL = 25,        //调度台之间视频+语音
		MRPS_CALL_TYPE_INTERCOMONLYVIDEO_CALL = 26,        //调度台之间视频 + 无语音
		MRPS_CALL_TYPE_CONFERENCE_CALL_WITH_VOICE = 27,
		MRPS_CALL_TYPE_CONFERENCE_CALL_WITH_VIDEO_AND_VOICE = 28,
		MRPS_CALL_TYPE_INCLUDE_CALL = 29,

		MRPS_CALL_TYPE_STATION_CALL = 100,                   // 基站全呼
		MRPS_CALL_TYPE_LOCAL_CALL = 101,                     // 本地全呼
		MRPS_CALL_TYPE_EMERGENCY_STATION_CALL = 102,         // 紧急基站全呼
		MRPS_CALL_TYPE_EMERGENCY_LOCAL_CALL = 103,           // 紧急本地全呼
		MRPS_CALL_TYPE_EMERGENCY_WHOLENET_CALL = 104,        // 紧急全网全呼
		MRPS_CALL_TYPE_ALL_CALL = 105,						 //全网全呼/基站全呼/本地全呼（广播类型）
		MRPS_CALL_TYPE_NONBROAD_ALL_CALL = 106,    			 //非广播类型的全呼
		MRPS_CALL_TYPE_ENVIRONMENT_VIDEOMONITOR_CALL = 201,
	}CallType;
}

#endif