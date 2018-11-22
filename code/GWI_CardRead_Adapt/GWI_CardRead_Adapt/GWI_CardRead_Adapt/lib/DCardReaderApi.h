#pragma once

#ifdef DCardReader_EXPORTS
#define XFSDLL_API __declspec(dllexport)WINAPI
#else
#define XFSDLL_API __declspec(dllimport)WINAPI
#endif

typedef struct tagEventData
{
	DWORD EventID;//�¼���ID, ��ͬ���¼�ID��Ӧ��ͬ������
	LPVOID pEventStruct;//��ͬ�¼��Ĳ������ؽṹ��ָ��

}EventData;
typedef int (WINAPI *APPCallBack_DCR)(EventData *event);


#ifdef __cplusplus
extern "C"{
#endif 

int XFSDLL_API CDB_EventInit(APPCallBack_DCR appcallback); //SP�¼���Ӧ�ûص�

int XFSDLL_API CDB_GetErrorMessage(IN HRESULT lhResult, OUT int *APPRet,OUT char *ErrCodeDiscription,OUT char *ErrSolutuion); //SP������ת����Ӧ����������룬����Ӧ������Ľ����������������

//���豸
int XFSDLL_API CDB_OpenDevice();

//�ر��豸
int XFSDLL_API CDB_CloseDevice();

/*
���ܣ��������
������
iTimeout �ȴ�������ʱʱ��
CardType  1����������2��IC����3�������Ϳ�
*/
int XFSDLL_API CDB_InhaleCard(IN int CardType, IN int iTimeout);

int XFSDLL_API CDB_AsyncInhaleCard(IN int CardType, IN int iTimeout);

//�˿�
int XFSDLL_API CDB_EjectICard();

//ֹͣ����
int XFSDLL_API CDB_StopInhaleCard();

//�̿�
int XFSDLL_API CDB_RetainCard();

/*
���ܣ���ȡͨ��״̬
������
OUT pMediastatus��
0 :ͨ���޿�
1 :����ͨ����
2 :����ͨ���У������ϵ�λ��
3������ͨ���У��������ϵ�λ
4 :�п� 
5 :ͨ��״̬δ֪
*/
int XFSDLL_API CDB_GetMediaStatus(OUT int* pMediastatus);

/*
���ܣ���ȡָ��������״̬
������
���������
iBoxNo   ������
���������
pMediastatus��
0:�����޿�
1:�����п�
*/
int XFSDLL_API CDB_GetBoxStatus(IN int iBoxNo, OUT int* pMediastatus);

/*
���ܣ���ȡ������״̬
������
pMediastatus��
0:����������
1:������δ��
pulCount:
0:���������޿�
1:���������п�
2:״̬δ֪
*/
int XFSDLL_API CDB_GetRecBoxStatus(OUT int* pMediastatus, OUT int* pulCount );

/*
���ܣ���ȡ2��3�ŵ���Ϣ
������
���������
trackid    2��2�ŵ� 3��3�ŵ�  23��2��3�ŵ�
itimeout   ��ʱʱ��
���������
pchTrackData2    2�ŵ�����
pchTrackData3    3�ŵ�����
*/
int XFSDLL_API CDB_ReadCardTracks(IN int trackid, OUT char* pchTrackData2,OUT char* pchTrackData3, IN int itimeout);

/*
���ܣ�д���ŵ�����
������
���������
trackid			1��1�ŵ� 2��2�ŵ� 3��3�ŵ�
pchTrackData	д�������
WriteMethod		д�뷽ʽ��1 �Ϳ��ţ�WFS_IDC_LOCO���� 2 �߿��ţ�WFS_IDC_HICO����3 ��SP����(WFS_IDC_AUTO)
itimeout		��ʱʱ��
���������
��
����ֵ��
0��д�ųɹ�
������д��ʧ��
*/
int XFSDLL_API CDB_WriteCardTrack(IN int trackid, IN char* pchTrackData,IN int WriteMethod, IN int itimeout);


/*
���ܣ��ϵ�
���������
pchInitData    �ϵ縴λ�󷵻ص�����
*/
int XFSDLL_API CDB_ChipPowerOn(OUT char* pchInitData);

//�µ�
int XFSDLL_API CDB_ChipPowerOff();

//�ǽӴ�ʽ���ϵ�
int XFSDLL_API CDB_RFChipPowerOn (OUT char* pchInitData);

//�ǽӴ�ʽ���µ�
int XFSDLL_API CDB_RFChipPowerOff();

//�ǽӴ�ʽ�����ŵ���Ϣ
int XFSDLL_API CDB_RFReadCardTracks(IN int trackid, OUT char* pchTrackData2,OUT char* pchTrackData3, IN int itimeout);

/*�ǽӴ�ʽ��ChipIo
���ܣ�  ��IC�����ݽ���
���룺	ChipProtocols  ��IC��ͨ��Э�飺0 WFS_IDC_CHIPT0������ WFS_IDC_CHIPT1
		szDataIn       д������
�����	lpszDataOut    �������
*/
int XFSDLL_API CDB_RFChipIo( short ChipProtocols, char* szDataIn, char* lpszDataOut);
/*
���ܣ���ָ�������䷢��
���������
iBoxNumer    ��������
*/
int XFSDLL_API CDB_Dispense(IN int iBoxNumer);

/*
���ܣ�  ��IC�����ݽ���
���룺	ChipProtocols  ��IC��ͨ��Э�飺0 WFS_IDC_CHIPT0������ WFS_IDC_CHIPT1
		szDataIn       д������
�����	lpszDataOut    �������
*/
int XFSDLL_API CDB_CDBChipIo(short ChipProtocols, char* szDataIn, char* lpszDataOut);

/*��ȡ�豸״̬
���������
pDevstatus��
0���豸����(����)
1���豸æ
2���豸����
3���豸����
*/
int XFSDLL_API CDB_GetDeviceStatus(OUT int* pDevstatus);

/*��λ�豸
���������
Action ��λ�豸���Ķ�����ʽ��1�޶�����2�˿���3�̿�
���������
��
*/
int XFSDLL_API CDB_ResetDevice(IN int Action);

/*��ȡ��չ״̬*/
int XFSDLL_API CRD_GetExtraInfor(char *ExtraInforKey,char *ExtraInforValue);
int XFSDLL_API CRD_GetDetailInforByKey(char *DetailInforKey,char *DetailInforValue);
int XFSDLL_API CRD_GetExtraCap(char *ExtraCapKey,char *ExtraCapValue);
int XFSDLL_API CRD_GetDetailCapByKey(char *DetailCapKey,char *DetailCapValue);

int XFSDLL_API IDC_GetExtraInfor(char *ExtraInforKey,char *ExtraInforValue);
int XFSDLL_API IDC_GetDetailInforByKey(char *DetailInforKey,char *DetailInforValue);
int XFSDLL_API IDC_GetExtraCap(char *ExtraCapKey,char *ExtraCapValue);
int XFSDLL_API IDC_GetDetailCapByKey(char *DetailCapKey,char *DetailCapValue);

int XFSDLL_API CDB_SetCardUnitInfo(IN int usNumber,IN int ulCount);
#ifdef __cplusplus
}
#endif