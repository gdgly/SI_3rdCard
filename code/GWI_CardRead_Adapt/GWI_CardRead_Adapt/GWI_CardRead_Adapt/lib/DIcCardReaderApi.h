#pragma once

#ifdef DIcCardReader_EXPORTS
#define XFSDLL_API __declspec(dllexport)WINAPI
#else
#define XFSDLL_API __declspec(dllimport)WINAPI
#endif

#ifdef __cplusplus
extern "C"{
#endif 
/*
typedef struct tagEventData
{
	DWORD EventID;//�¼���ID, ��ͬ���¼�ID��Ӧ��ͬ������
	LPVOID pEventStruct;//��ͬ�¼��Ĳ������ؽṹ��ָ��

}EventData;
typedef int (WINAPI *APPCallBack)(EventData *event);
*/
typedef int (WINAPI *APPCallBack)(char *EventName,int* EventResult ,int  *EventParameterCount, char *EventParameterStr );///EventParameterStr:EventParameterName1 = EventParameterValue1 ||...||EventParameterNameN = EventParameterValueN(N = EventParameterCount)
	
//���豸
int XFSDLL_API IC2_OpenDevice();

//�ر��豸
int XFSDLL_API IC2_CloseDevice();

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
int XFSDLL_API IC2_ReadCardTracks(IN int trackid, OUT char* pchTrackData2,OUT char* pchTrackData3, IN int itimeout);

/*
���ܣ��ϵ�
���������
pchInitData    �ϵ縴λ�󷵻ص�����
*/
int XFSDLL_API IC2_ChipPowerOn(OUT char* pchInitData);

//�µ�
int XFSDLL_API IC2_ChipPowerOff();


/*
���ܣ���ָ�������䷢��
���룺	ChipProtocols  ��IC��ͨ��Э�飺0 WFS_IDC_CHIPT0������ WFS_IDC_CHIPT1
		szDataIn       д������
�����	lpszDataOut    �������
*/
int XFSDLL_API IC2_ICCChipIo(short ChipProtocols, char* szDataIn, char* lpszDataOut);

/*��ȡ�豸״̬
���������
pDevstatus��
0���豸����(����)
1���豸æ
2���豸����
3���豸����
*/
int XFSDLL_API IC2_GetDeviceStatus(OUT int* pDevstatus);

int XFSDLL_API IC2_GetMediaStatus(OUT int* pMediastatus);

//��λ�豸
int XFSDLL_API IC2_ResetDevice();

//SP�¼���Ӧ�ûص�
int XFSDLL_API IC2_EventInit(APPCallBack appcallback);

int XFSDLL_API IC2_GetErrorMessage(IN HRESULT lhResult, OUT int *APPRet,OUT char *ErrCodeDiscription,OUT char *ErrSolutuion);//SP������ת����Ӧ����������룬����Ӧ������Ľ����������������
int XFSDLL_API IC2_GetExtraInfor(char *ExtraInforKey,char *ExtraInforValue);//��ȡ��չ״̬
int XFSDLL_API IC2_GetDetailInforByKey(char *DetailInforKey,char *DetailInforValue);//������Ϣ�ֶ����ƻ�ȡ��Ӧ������ģ�����״̬
int XFSDLL_API IC2_GetExtraCap(char *ExtraCapKey,char *ExtraCapValue);//��ȡ��չ����
int XFSDLL_API IC2_GetDetailCapByKey(char *DetailCapKey,char *DetailCapValue);//������Ϣ�ֶ����ƻ�ȡ��Ӧ����������

int XFSDLL_API IC2_AsyncAcceptCard( IN int iTimeout);

int XFSDLL_API IC2_AcceptCardAndChip( IN int iTimeout);


#ifdef __cplusplus
}
#endif