#ifndef __DefCallDisconnectReason_H__
#define __DefCallDisconnectReason_H__

namespace MRPS
{
	/*挂断呼叫ACK事件结果枚举定义*/
	typedef enum CallDisconnectReason
	{
		MRPS_UNKNOWN = 100,                          ///< 未知原因
		MRPS_HANG_UP,                                ///< 用户请求挂断
		MRPS_CC_SERVICE_DONT_OPEN,                   ///< 呼叫控制服务未开启
		MRPS_HAVE_NOT_LOGIN,                         ///< 未登录
		MRPS_FAIL_TO_SETUP_CALL,                     ///< 呼叫失败
		MRPS_NO_PERMISSION,                          ///< 无权限
		MRPS_INVALID_SSI,                            ///< 该号码不存在
		MRPS_OTHER_PARTY_BUSY,                       ///< 对方忙
		MRPS_OTHER_PARTY_REFUSE,                     ///< 对方拒绝
		MRPS_OTHER_PARTY_DONT_SUPPORT_ENCRYPTION,    ///< 对方不支持加密
		MRPS_SYSTEM_CC_BUSY,                         ///< 系统呼叫模块忙
		MRPS_CALL_TIMEOUT,                           ///< 呼叫超时

		MRPS_LTE_CALL_HANG_UP = 300,//通用呼叫释放
		MRPS_LTE_CALL_CALLER_HANG_UP,//主叫发起的呼叫释放
		MRPS_LTE_CALL_CALLED_HANG_UP,//被叫发起的呼叫
		MRPS_LTE_CALL_SYSTEM_HANG_UP,//核心网强制呼叫释放
		MRPS_LTE_CALL_TIMEOUT,//超时释放

		MRPS_CALL_SYSTEM_DISCONNECT = 400,
		MRPS_CALL_CALLDISCONNECT_TIMEOUT,

		MRPS_PUC_701 = 701,//获取媒体资源并link失败
		MRPS_PUC_702,                    //呼叫冲突
		MRPS_PUC_703,//获取媒体通道失败
		MRPS_PUC_704,//SDP协商失败
		MRPS_PUC_705,//视频呼叫bindMonitor失败
		MRPS_PUC_706,//呼叫并入失败
		MRPS_PUC_707,//PTT空闲超时
		MRPS_PUC_708,//业务流程超时挂机
		MRPS_PUC_709,//呼叫发起者挂机
		MRPS_PUC_710,//呼叫接收者挂机
		MRPS_PUC_711,//分配SIP呼叫对象失败
		MRPS_PUC_712,//获取SIP网关地址失败
		MRPS_PUC_713,//获取服务器SIP地址失败
		MRPS_PUC_714,//获取SIP电话地址失败
		MRPS_PUC_715,//录音回放录音时间长度不对

		MRPS_PUC_751 = 751,//调度员全双工呼叫其他子系统分配SAP失败
		MRPS_PUC_752,//调度员呼叫子系统分配SAP失败
		MRPS_PUC_753,//分配SAP找不到合适的SAP
		MRPS_PUC_754,//有在线的SAP，调度员没有SAP权限
		MRPS_PUC_755,//有在线的SAP，SAP忙
		MRPS_PUC_756,//指定的SAP不在线

		MRPS_PUC_801 = 801,//终端全双工呼叫调度员创建呼叫失败！
		MRPS_PUC_802,//终端全双工呼叫调度员找不到用户！
		MRPS_PUC_803,//监听全双工raido呼叫创建失败
		MRPS_PUC_804,//监听全双工raido呼叫没有找到用户
		MRPS_PUC_805,//电话用户呼叫调度员失败(没有权限的在线调度台或者获取调度台SIP信息失败)
		MRPS_PUC_806,//调度台呼叫调度台失败(调度台不在线或者获取调度台SIP信息失败)
		MRPS_PUC_807,//调度台全双工呼叫电话失败
		MRPS_PUC_808,//调度台全双工呼叫其他子系统创建呼叫失败
		MRPS_PUC_809,//电话全双工呼叫其他子系统创建呼叫失败

		MRPS_PUC_821 = 821,//Raido半双工呼叫调度台找不到用户
		MRPS_PUC_822,//客户端去派接监听触发向客户端挂断呼叫
		MRPS_PUC_823,//客户端去号码监听挂断呼叫
		MRPS_PUC_824,//客户去成员监听触发向客户端挂断呼叫
		MRPS_PUC_825,//呼端呼叫结束向网关发挂机
		MRPS_PUC_826,//客户端发挂机或者客户端退出触发向客户端挂断呼叫
		MRPS_PUC_827,//客户端退出
		MRPS_PUC_828,//派接成员呼叫结束触发向客户端挂断呼叫
		MRPS_PUC_829,//派接激活者挂机
		MRPS_PUC_830,//客户端删除派接成员触发向子系统挂断呼叫
		MRPS_PUC_831,//客户端呼叫子系统被叫忙
		MRPS_PUC_832,//迪爱思号码错误
		MRPS_PUC_833,//客户端呼叫子系统创建子系统呼叫失败
		MRPS_PUC_834,//获取派接数据失败
		MRPS_PUC_835,//派接呼叫忙，当前派接正在呼叫中
		MRPS_PUC_836,//派接呼叫成员都失败
		MRPS_PUC_837,//用户呼叫客户端失败
		MRPS_PUC_838,//绑定电话的客户端全部挂机了
		MRPS_PUC_839,//客户端删除监听挂断
		MRPS_PUC_840,//获取号码对象失败挂断


		MRPS_PUC_DMR2_unknown = 1000,
		MRPS_PUC_DMR2_hang_up,
		MRPS_PUC_DMR2_call_timeout,

		MRPS_PUC_DMR3_unknown = 1200,
		MRPS_PUC_DMR3_hang_up,
		MRPS_PUC_DMR3_ccservice_not_open,
		MRPS_PUC_DMR3_have_not_login,
		MRPS_PUC_DMR3_fail_to_setup_call,
		MRPS_PUC_DMR3_no_permission,
		MRPS_PUC_DMR3_invalid_ssi,
		MRPS_PUC_DMR3_other_party_busy,
		MRPS_PUC_DMR3_other_party_refuse,
		MRPS_PUC_DMR3_other_party_not_support_encryption,
		MRPS_PUC_DMR3_system_cc_busy,
		MRPS_PUC_DMR3_call_timeout,

		MRPS_PUC_TETRA_unknown = 1300,
		MRPS_PUC_TETRA_User_request_disconnect,
		MRPS_PUC_TETRA_Called_party_busy,
		MRPS_PUC_TETRA_Called_party_not_reached,
		MRPS_PUC_TETRA_Called_party_not_support_encryption,
		MRPS_PUC_TETRA_Network_is_busy,
		MRPS_PUC_TETRA_The_traffic_not_allowed,
		MRPS_PUC_TETRA_The_traffic_incompatible,
		MRPS_PUC_TETRA_The_service_unavailable,
		MRPS_PUC_TETRA_Either_party_is_preempted,
		MRPS_PUC_TETRA_Invalid_call_identifier,
		MRPS_PUC_TETRA_Called_party_rejects_the_call,
		MRPS_PUC_TETRA_No_Idle_CC_entity,
		MRPS_PUC_TETRA_Timer_expiry,
		MRPS_PUC_TETRA_SwMI_disconnect,
		MRPS_PUC_TETRA_No_acknowledgement,
		MRPS_PUC_TETRA_Unknown_TETRA_identity,
		MRPS_PUC_TETRA_Supplementary_Service_dependent,
		MRPS_PUC_TETRA_Unknown_external_subscriber_number,
		MRPS_PUC_TETRA_Call_restoration_failure,
		MRPS_PUC_TETRA_Called_party_requires_encryption,
		MRPS_PUC_TETRA_Concurrent_set_up_not_supported,
		MRPS_PUC_TETRA_Called_party_is_under_the_same_DM_GATE_of_the_calling_party,

	}CallDisconnectReason;
}

#endif