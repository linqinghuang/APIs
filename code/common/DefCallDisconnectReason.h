#ifndef __DefCallDisconnectReason_H__
#define __DefCallDisconnectReason_H__

namespace MRPS
{
	/*�ҶϺ���ACK�¼����ö�ٶ���*/
	typedef enum CallDisconnectReason
	{
		MRPS_UNKNOWN = 100,                          ///< δ֪ԭ��
		MRPS_HANG_UP,                                ///< �û�����Ҷ�
		MRPS_CC_SERVICE_DONT_OPEN,                   ///< ���п��Ʒ���δ����
		MRPS_HAVE_NOT_LOGIN,                         ///< δ��¼
		MRPS_FAIL_TO_SETUP_CALL,                     ///< ����ʧ��
		MRPS_NO_PERMISSION,                          ///< ��Ȩ��
		MRPS_INVALID_SSI,                            ///< �ú��벻����
		MRPS_OTHER_PARTY_BUSY,                       ///< �Է�æ
		MRPS_OTHER_PARTY_REFUSE,                     ///< �Է��ܾ�
		MRPS_OTHER_PARTY_DONT_SUPPORT_ENCRYPTION,    ///< �Է���֧�ּ���
		MRPS_SYSTEM_CC_BUSY,                         ///< ϵͳ����ģ��æ
		MRPS_CALL_TIMEOUT,                           ///< ���г�ʱ

		MRPS_LTE_CALL_HANG_UP = 300,//ͨ�ú����ͷ�
		MRPS_LTE_CALL_CALLER_HANG_UP,//���з���ĺ����ͷ�
		MRPS_LTE_CALL_CALLED_HANG_UP,//���з���ĺ���
		MRPS_LTE_CALL_SYSTEM_HANG_UP,//������ǿ�ƺ����ͷ�
		MRPS_LTE_CALL_TIMEOUT,//��ʱ�ͷ�

		MRPS_CALL_SYSTEM_DISCONNECT = 400,
		MRPS_CALL_CALLDISCONNECT_TIMEOUT,

		MRPS_PUC_701 = 701,//��ȡý����Դ��linkʧ��
		MRPS_PUC_702,                    //���г�ͻ
		MRPS_PUC_703,//��ȡý��ͨ��ʧ��
		MRPS_PUC_704,//SDPЭ��ʧ��
		MRPS_PUC_705,//��Ƶ����bindMonitorʧ��
		MRPS_PUC_706,//���в���ʧ��
		MRPS_PUC_707,//PTT���г�ʱ
		MRPS_PUC_708,//ҵ�����̳�ʱ�һ�
		MRPS_PUC_709,//���з����߹һ�
		MRPS_PUC_710,//���н����߹һ�
		MRPS_PUC_711,//����SIP���ж���ʧ��
		MRPS_PUC_712,//��ȡSIP���ص�ַʧ��
		MRPS_PUC_713,//��ȡ������SIP��ַʧ��
		MRPS_PUC_714,//��ȡSIP�绰��ַʧ��
		MRPS_PUC_715,//¼���ط�¼��ʱ�䳤�Ȳ���

		MRPS_PUC_751 = 751,//����Աȫ˫������������ϵͳ����SAPʧ��
		MRPS_PUC_752,//����Ա������ϵͳ����SAPʧ��
		MRPS_PUC_753,//����SAP�Ҳ������ʵ�SAP
		MRPS_PUC_754,//�����ߵ�SAP������Աû��SAPȨ��
		MRPS_PUC_755,//�����ߵ�SAP��SAPæ
		MRPS_PUC_756,//ָ����SAP������

		MRPS_PUC_801 = 801,//�ն�ȫ˫�����е���Ա��������ʧ�ܣ�
		MRPS_PUC_802,//�ն�ȫ˫�����е���Ա�Ҳ����û���
		MRPS_PUC_803,//����ȫ˫��raido���д���ʧ��
		MRPS_PUC_804,//����ȫ˫��raido����û���ҵ��û�
		MRPS_PUC_805,//�绰�û����е���Աʧ��(û��Ȩ�޵����ߵ���̨���߻�ȡ����̨SIP��Ϣʧ��)
		MRPS_PUC_806,//����̨���е���̨ʧ��(����̨�����߻��߻�ȡ����̨SIP��Ϣʧ��)
		MRPS_PUC_807,//����̨ȫ˫�����е绰ʧ��
		MRPS_PUC_808,//����̨ȫ˫������������ϵͳ��������ʧ��
		MRPS_PUC_809,//�绰ȫ˫������������ϵͳ��������ʧ��

		MRPS_PUC_821 = 821,//Raido��˫�����е���̨�Ҳ����û�
		MRPS_PUC_822,//�ͻ���ȥ�ɽӼ���������ͻ��˹ҶϺ���
		MRPS_PUC_823,//�ͻ���ȥ��������ҶϺ���
		MRPS_PUC_824,//�ͻ�ȥ��Ա����������ͻ��˹ҶϺ���
		MRPS_PUC_825,//���˺��н��������ط��һ�
		MRPS_PUC_826,//�ͻ��˷��һ����߿ͻ����˳�������ͻ��˹ҶϺ���
		MRPS_PUC_827,//�ͻ����˳�
		MRPS_PUC_828,//�ɽӳ�Ա���н���������ͻ��˹ҶϺ���
		MRPS_PUC_829,//�ɽӼ����߹һ�
		MRPS_PUC_830,//�ͻ���ɾ���ɽӳ�Ա��������ϵͳ�ҶϺ���
		MRPS_PUC_831,//�ͻ��˺�����ϵͳ����æ
		MRPS_PUC_832,//�ϰ�˼�������
		MRPS_PUC_833,//�ͻ��˺�����ϵͳ������ϵͳ����ʧ��
		MRPS_PUC_834,//��ȡ�ɽ�����ʧ��
		MRPS_PUC_835,//�ɽӺ���æ����ǰ�ɽ����ں�����
		MRPS_PUC_836,//�ɽӺ��г�Ա��ʧ��
		MRPS_PUC_837,//�û����пͻ���ʧ��
		MRPS_PUC_838,//�󶨵绰�Ŀͻ���ȫ���һ���
		MRPS_PUC_839,//�ͻ���ɾ�������Ҷ�
		MRPS_PUC_840,//��ȡ�������ʧ�ܹҶ�


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