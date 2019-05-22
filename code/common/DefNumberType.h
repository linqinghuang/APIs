#ifndef __DefNumberType_H__
#define __DefNumberType_H__

namespace MRPS
{
	/*��������*/
	enum NumberType
	{
		MRPS_NUMBER_TYPE_UNKNOWN = -1,

		MRPS_NUMBER_TYPE_INDIVIDUAL = 0,                    //����
		MRPS_NUMBER_TYPE_GROUP = 1,                         //���
		MRPS_NUMBER_TYPE_EXTERNAL = 2,                      //����
		MRPS_NUMBER_TYPE_BROADCAST = 3,	                    //ȫ��
		MRPS_NUMBER_TYPE_DGNAGROUP = 4,	                    //DGNA��̬��
		MRPS_NUMBER_TYPE_WORKSTATION = 5,                   //����վ����
		MRPS_NUMBER_TYPE_FLEET = 6,	                        //fleet����
		MRPS_NUMBER_TYPE_DISPATCHERCOUNT = 7,	            //����̨�û�
		MRPS_NUMBER_TYPE_CROSSPATCH = 8,                    //��ϵͳ�ɽ�
		MRPS_NUMBER_TYPE_SIMULSELECT = 9,                   //��ѡ����
		MRPS_NUMBER_TYPE_RECORDREPLAY = 10,                 //¼���ط�
		MRPS_NUMBER_TYPE_TMP_CONFERENCE = 11,

		MRPS_NUMBER_TYPE_SIMULCASTDIGITALGROUP = 100,       //ͬ��������
		MRPS_NUMBER_TYPE_SIMULCASTGROUPCTCSS = 101,         //ͬ��ģ����(����Ƶ)
		MRPS_NUMBER_TYPE_SIMULCASTGROUPCDCSS = 102,         //ͬ��ģ����(��������)
		MRPS_NUMBER_TYPE_SIMULCASTGROUPCDCSS_INVERT = 103,  //ͬ��ģ����(��ת��������)

		MRPS_NUMBER_TYPE_OTAPGROUP = 200,	                //OTAP��̬��
		MRPS_NUMBER_TYPE_GPSSERVER = 201,                   //GPS������
		MRPS_NUMBER_TYPE_RECORDSERVER = 202,                //¼��������
		MRPS_NUMBER_TYPE_MPTGATEWAY = 203,                  //MPT����
		MPRS_NUMBER_TYPE_INDIVIDUAL_IDSC = 204,   			//IDSC�ĺ���
		MPRS_NUMBER_TYPE_BACKGROUP = 205,   				//���������
		MPRS_NUMBER_TYPE_RESPONSE_GROUP = 206,   			//��Ӧ�����
		MPRS_NUMBER_TYPE_CUR_GROUP = 207,   				//��ǰ�����
		MPRS_NUMBER_TYPE_SCAN_GROUP = 208,    				//ɨ�������

		MRPS_NUMBER_TYPE_CAMERA = 301,                  //����ͷ

		MRPS_NUMBER_TYPE_CONFERENCE = 501,
	};
}

#endif