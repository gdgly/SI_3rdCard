#pragma once

#ifdef DCardReader_EXPORTS
#define XFSDLL_API __declspec(dllexport)WINAPI
#else
#define XFSDLL_API __declspec(dllimport)WINAPI
#endif

typedef struct tagEventData
{
	DWORD EventID;//事件的ID, 不同的事件ID对应不同处理方法
	LPVOID pEventStruct;//不同事件的参数返回结构体指针

}EventData;
typedef int (WINAPI *APPCallBack_DCR)(EventData *event);


#ifdef __cplusplus
extern "C"{
#endif 

int XFSDLL_API CDB_EventInit(APPCallBack_DCR appcallback); //SP事件的应用回调

int XFSDLL_API CDB_GetErrorMessage(IN HRESULT lhResult, OUT int *APPRet,OUT char *ErrCodeDiscription,OUT char *ErrSolutuion); //SP错误码转换成应用所需错误码，及对应错误码的解析、解决方案建议

//打开设备
int XFSDLL_API CDB_OpenDevice();

//关闭设备
int XFSDLL_API CDB_CloseDevice();

/*
功能：允许进卡
参数：
iTimeout 等待进卡超时时间
CardType  1纯磁条卡，2纯IC卡，3所有类型卡
*/
int XFSDLL_API CDB_InhaleCard(IN int CardType, IN int iTimeout);

int XFSDLL_API CDB_AsyncInhaleCard(IN int CardType, IN int iTimeout);

//退卡
int XFSDLL_API CDB_EjectICard();

//停止进卡
int XFSDLL_API CDB_StopInhaleCard();

//吞卡
int XFSDLL_API CDB_RetainCard();

/*
功能：获取通道状态
参数：
OUT pMediastatus：
0 :通道无卡
1 :卡在通道口
2 :卡在通道中（不在上电位）
3：卡在通道中，且已在上电位
4 :夹卡 
5 :通道状态未知
*/
int XFSDLL_API CDB_GetMediaStatus(OUT int* pMediastatus);

/*
功能：获取指定发卡箱状态
参数：
输入参数：
iBoxNo   卡箱编号
输出参数：
pMediastatus：
0:卡箱无卡
1:卡箱有卡
*/
int XFSDLL_API CDB_GetBoxStatus(IN int iBoxNo, OUT int* pMediastatus);

/*
功能：获取回收箱状态
参数：
pMediastatus：
0:回收箱已满
1:回收箱未满
pulCount:
0:回收箱中无卡
1:回收箱中有卡
2:状态未知
*/
int XFSDLL_API CDB_GetRecBoxStatus(OUT int* pMediastatus, OUT int* pulCount );

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
int XFSDLL_API CDB_ReadCardTracks(IN int trackid, OUT char* pchTrackData2,OUT char* pchTrackData3, IN int itimeout);

/*
功能：写单磁道数据
参数：
输入参数：
trackid			1：1磁道 2：2磁道 3：3磁道
pchTrackData	写入的数据
WriteMethod		写入方式：1 低抗磁（WFS_IDC_LOCO）， 2 高抗磁（WFS_IDC_HICO），3 由SP决定(WFS_IDC_AUTO)
itimeout		超时时间
输出参数：
无
返回值：
0：写磁成功
其他：写磁失败
*/
int XFSDLL_API CDB_WriteCardTrack(IN int trackid, IN char* pchTrackData,IN int WriteMethod, IN int itimeout);


/*
功能：上电
输出参数：
pchInitData    上电复位后返回的数据
*/
int XFSDLL_API CDB_ChipPowerOn(OUT char* pchInitData);

//下电
int XFSDLL_API CDB_ChipPowerOff();

//非接触式卡上电
int XFSDLL_API CDB_RFChipPowerOn (OUT char* pchInitData);

//非接触式卡下电
int XFSDLL_API CDB_RFChipPowerOff();

//非接触式卡读磁道信息
int XFSDLL_API CDB_RFReadCardTracks(IN int trackid, OUT char* pchTrackData2,OUT char* pchTrackData3, IN int itimeout);

/*非接触式卡ChipIo
功能：  与IC卡数据交互
输入：	ChipProtocols  与IC卡通信协议：0 WFS_IDC_CHIPT0，其他 WFS_IDC_CHIPT1
		szDataIn       写入数据
输出：	lpszDataOut    输出数据
*/
int XFSDLL_API CDB_RFChipIo( short ChipProtocols, char* szDataIn, char* lpszDataOut);
/*
功能：从指定发卡箱发卡
输入参数：
iBoxNumer    发卡箱编号
*/
int XFSDLL_API CDB_Dispense(IN int iBoxNumer);

/*
功能：  与IC卡数据交互
输入：	ChipProtocols  与IC卡通信协议：0 WFS_IDC_CHIPT0，其他 WFS_IDC_CHIPT1
		szDataIn       写入数据
输出：	lpszDataOut    输出数据
*/
int XFSDLL_API CDB_CDBChipIo(short ChipProtocols, char* szDataIn, char* lpszDataOut);

/*获取设备状态
输出参数：
pDevstatus：
0：设备正常(在线)
1：设备忙
2：设备离线
3：设备故障
*/
int XFSDLL_API CDB_GetDeviceStatus(OUT int* pDevstatus);

/*复位设备
输入参数：
Action 复位设备卡的动作方式：1无动作，2退卡，3吞卡
输出参数：
无
*/
int XFSDLL_API CDB_ResetDevice(IN int Action);

/*获取扩展状态*/
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