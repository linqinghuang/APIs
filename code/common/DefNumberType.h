#ifndef __DefNumberType_H__
#define __DefNumberType_H__

namespace MRPS
{
	/*号码类型*/
	enum NumberType
	{
		MRPS_NUMBER_TYPE_UNKNOWN = -1,

		MRPS_NUMBER_TYPE_INDIVIDUAL = 0,                    //个号
		MRPS_NUMBER_TYPE_GROUP = 1,                         //组号
		MRPS_NUMBER_TYPE_EXTERNAL = 2,                      //外线
		MRPS_NUMBER_TYPE_BROADCAST = 3,	                    //全网
		MRPS_NUMBER_TYPE_DGNAGROUP = 4,	                    //DGNA动态组
		MRPS_NUMBER_TYPE_WORKSTATION = 5,                   //工作站号码
		MRPS_NUMBER_TYPE_FLEET = 6,	                        //fleet号码
		MRPS_NUMBER_TYPE_DISPATCHERCOUNT = 7,	            //调度台用户
		MRPS_NUMBER_TYPE_CROSSPATCH = 8,                    //跨系统派接
		MRPS_NUMBER_TYPE_SIMULSELECT = 9,                   //多选呼叫
		MRPS_NUMBER_TYPE_RECORDREPLAY = 10,                 //录音回放
		MRPS_NUMBER_TYPE_TMP_CONFERENCE = 11,

		MRPS_NUMBER_TYPE_SIMULCASTDIGITALGROUP = 100,       //同播数字组
		MRPS_NUMBER_TYPE_SIMULCASTGROUPCTCSS = 101,         //同播模拟组(亚音频)
		MRPS_NUMBER_TYPE_SIMULCASTGROUPCDCSS = 102,         //同播模拟组(亚音数码)
		MRPS_NUMBER_TYPE_SIMULCASTGROUPCDCSS_INVERT = 103,  //同播模拟组(反转亚音数码)

		MRPS_NUMBER_TYPE_OTAPGROUP = 200,	                //OTAP动态组
		MRPS_NUMBER_TYPE_GPSSERVER = 201,                   //GPS服务器
		MRPS_NUMBER_TYPE_RECORDSERVER = 202,                //录音服务器
		MRPS_NUMBER_TYPE_MPTGATEWAY = 203,                  //MPT网关
		MPRS_NUMBER_TYPE_INDIVIDUAL_IDSC = 204,   			//IDSC的号码
		MPRS_NUMBER_TYPE_BACKGROUP = 205,   				//背景组号码
		MPRS_NUMBER_TYPE_RESPONSE_GROUP = 206,   			//响应组号码
		MPRS_NUMBER_TYPE_CUR_GROUP = 207,   				//当前组号码
		MPRS_NUMBER_TYPE_SCAN_GROUP = 208,    				//扫描组号码

		MRPS_NUMBER_TYPE_CAMERA = 301,                  //摄像头

		MRPS_NUMBER_TYPE_CONFERENCE = 501,
	};
}

#endif