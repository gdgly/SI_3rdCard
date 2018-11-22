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
	DWORD EventID;//事件的ID, 不同的事件ID对应不同处理方法
	LPVOID pEventStruct;//不同事件的参数返回结构体指针

}EventData;
typedef int (WINAPI *APPCallBack)(EventData *event);
*/
typedef int (WINAPI *APPCallBack)(char *EventName,int* EventResult ,int  *EventParameterCount, char *EventParameterStr );///EventParameterStr:EventParameterName1 = EventParameterValue1 ||...||EventParameterNameN = EventParameterValueN(N = EventParameterCount)
	
//打开设备
int XFSDLL_API IC2_OpenDevice();

//关闭设备
int XFSDLL_API IC2_CloseDevice();

/*
功能：获取2、3磁道信息
参数：
输入参数：
trackid    2：2磁道 3：3磁道  23：2、3磁道
itimeout   超时时间
输出参数：
pchTrackData2    2磁道数据
pchTrackData3    3磁道数据
*/
int XFSDLL_API IC2_ReadCardTracks(IN int trackid, OUT char* pchTrackData2,OUT char* pchTrackData3, IN int itimeout);

/*
功能：上电
输出参数：
pchInitData    上电复位后返回的数据
*/
int XFSDLL_API IC2_ChipPowerOn(OUT char* pchInitData);

//下电
int XFSDLL_API IC2_ChipPowerOff();


/*
功能：从指定发卡箱发卡
输入：	ChipProtocols  与IC卡通信协议：0 WFS_IDC_CHIPT0，其他 WFS_IDC_CHIPT1
		szDataIn       写入数据
输出：	lpszDataOut    输出数据
*/
int XFSDLL_API IC2_ICCChipIo(short ChipProtocols, char* szDataIn, char* lpszDataOut);

/*获取设备状态
输出参数：
pDevstatus：
0：设备正常(在线)
1：设备忙
2：设备离线
3：设备故障
*/
int XFSDLL_API IC2_GetDeviceStatus(OUT int* pDevstatus);

int XFSDLL_API IC2_GetMediaStatus(OUT int* pMediastatus);

//复位设备
int XFSDLL_API IC2_ResetDevice();

//SP事件的应用回调
int XFSDLL_API IC2_EventInit(APPCallBack appcallback);

int XFSDLL_API IC2_GetErrorMessage(IN HRESULT lhResult, OUT int *APPRet,OUT char *ErrCodeDiscription,OUT char *ErrSolutuion);//SP错误码转换成应用所需错误码，及对应错误码的解析、解决方案建议
int XFSDLL_API IC2_GetExtraInfor(char *ExtraInforKey,char *ExtraInforValue);//获取扩展状态
int XFSDLL_API IC2_GetDetailInforByKey(char *DetailInforKey,char *DetailInforValue);//根据信息字段名称获取对应的其他模块相关状态
int XFSDLL_API IC2_GetExtraCap(char *ExtraCapKey,char *ExtraCapValue);//获取扩展能力
int XFSDLL_API IC2_GetDetailCapByKey(char *DetailCapKey,char *DetailCapValue);//根据信息字段名称获取对应的其他能力

int XFSDLL_API IC2_AsyncAcceptCard( IN int iTimeout);

int XFSDLL_API IC2_AcceptCardAndChip( IN int iTimeout);


#ifdef __cplusplus
}
#endif