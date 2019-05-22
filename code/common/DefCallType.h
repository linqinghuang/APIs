#ifndef __DefCallType_H__
#define __DefCallType_H__

namespace MRPS
{
	typedef enum CallType
	{
		MRPS_CALL_TYPE_UNKNOWN = -1,
		MRPS_CALL_TYPE_INDIVIDUAL_CALL = 0,                ///<����
		MRPS_CALL_TYPE_GROUP_CALL = 1,                     ///<���	    
		MRPS_CALL_TYPE_SYSTEM_CALL = 2,                    ///<ϵͳȫ��
		MRPS_CALL_TYPE_BROADCAST_CALL = 3,                 ///<�㲥��		                 
		MRPS_CALL_TYPE_EXTERNAL_CALL = 4,                  ///<�ⲿ����:PSAN/PABX,MSISDN	
		MRPS_CALL_TYPE_REMOTE_MONITOR_CALL = 5,            //Զ�̼�������
		MRPS_CALL_TYPE_ANALOG_CALL = 6,                    //ģ�����
		MRPS_CALL_TYPE_EMERGENCY_CALL = 7,                 //��������
		MRPS_CALL_TYPE_CROSSPATCH_CALL = 8,                //��ϵͳ�ɽӺ���
		MRPS_CALL_TYPE_INTERCOM_CALL = 9,                  //����̨�����
		MRPS_CALL_TYPE_RECORDPAY_CALL = 10,                //¼���ط�
		MRPS_CALL_TYPE_INDIVIDUAL_VIDEOANDVOICE_CALL = 11, //���ӵ�����������
		MRPS_CALL_TYPE_INDIVIDUAL_ONLYVIDEO_CALL = 12,     //���ӵ�����������
		MRPS_CALL_TYPE_GROUP_VIDEOANDVOICE_CALL = 13,      //���������������
		MRPS_CALL_TYPE_GROUP_ONLYVIDEO_CALL = 14,          //���������������
		MRPS_CALL_TYPE_GROUP_DIFFERENTSOURCE_CALL = 15,    //��ͬԴ�������
		MRPS_CALL_TYPE_BROADCAST_VOICE_CALL = 16,          //�����鲥
		MRPS_CALL_TYPE_BROADCAST_VIDEO_CALL = 17,          //��Ƶ�鲥
		MRPS_CALL_TYPE_BROADCAST_ONLYVIDEO_CALL = 18,      //����Ƶ�鲥
		MRPS_CALL_TYPE_PULLVIDEO_CALL = 19,                //��Ƶ����
		MRPS_CALL_TYPE_DOWNVIDEO_CALL = 20,                //��Ƶ����
		MRPS_CALL_TYPE_BACKVIDEO_CALL = 21,                //��Ƶ�ش�
		MRPS_CALL_TYPE_PUSHVIDEO_CALL = 22,                //��Ƶ����
		MRPS_CALL_TYPE_PULLVIDEOWITHVOICE_CALL = 23,       //��Ƶ����,��eLTEʹ�ú�hyteraʹ��
		MRPS_CALL_TYPE_VIDEOFEEDBACKWITHVOICE_CALL = 24,   //��Ƶ�ش�, ��eLTEʹ��
		MRPS_CALL_TYPE_INTERCOMWITHVIDEO_CALL = 25,        //����̨֮����Ƶ+����
		MRPS_CALL_TYPE_INTERCOMONLYVIDEO_CALL = 26,        //����̨֮����Ƶ + ������
		MRPS_CALL_TYPE_CONFERENCE_CALL_WITH_VOICE = 27,
		MRPS_CALL_TYPE_CONFERENCE_CALL_WITH_VIDEO_AND_VOICE = 28,
		MRPS_CALL_TYPE_INCLUDE_CALL = 29,

		MRPS_CALL_TYPE_STATION_CALL = 100,                   // ��վȫ��
		MRPS_CALL_TYPE_LOCAL_CALL = 101,                     // ����ȫ��
		MRPS_CALL_TYPE_EMERGENCY_STATION_CALL = 102,         // ������վȫ��
		MRPS_CALL_TYPE_EMERGENCY_LOCAL_CALL = 103,           // ��������ȫ��
		MRPS_CALL_TYPE_EMERGENCY_WHOLENET_CALL = 104,        // ����ȫ��ȫ��
		MRPS_CALL_TYPE_ALL_CALL = 105,						 //ȫ��ȫ��/��վȫ��/����ȫ�����㲥���ͣ�
		MRPS_CALL_TYPE_NONBROAD_ALL_CALL = 106,    			 //�ǹ㲥���͵�ȫ��
		MRPS_CALL_TYPE_ENVIRONMENT_VIDEOMONITOR_CALL = 201,
	}CallType;
}

#endif