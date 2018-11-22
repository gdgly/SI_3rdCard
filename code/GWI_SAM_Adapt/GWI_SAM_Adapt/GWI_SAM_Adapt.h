// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 GWI_SAM_ADAPT_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// GWI_SAM_ADAPT_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef GWI_SAM_ADAPT_EXPORTS
#define GWI_SAM_ADAPT_API __declspec(dllexport)
#else
#define GWI_SAM_ADAPT_API __declspec(dllimport)
#endif

// 此类是从 GWI_SAM_Adapt.dll 导出的
class GWI_SAM_ADAPT_API CGWI_SAM_Adapt {
public:
	CGWI_SAM_Adapt(void);
	// TODO: 在此添加您的方法。
};

/*
目的：内部自动实现获取PSAM卡操作初始化，包括读配置文件实现SP调用还是硬件DLL调用
函数名：psamInit
输入：

输出：
返回：
0： 成功
其它 失败
*/
GWI_SAM_ADAPT_API int __stdcall psamInit();
/*
目的：内部自动实现获取PSAM卡上电操作
函数名：psamPowerOn
输入：
int iSlotNum：卡座号
输出：
char *pchData：上电复位信息
int* iDataLen：数据长度
char* pchErrCode：错误码
char* pchError：错误码对应的错误信息
返回：
0： 成功
其它 失败
*/
GWI_SAM_ADAPT_API int __stdcall psamPowerOn(int iSlotNum, char *pchData, int* iDataLen, char* pchErrCode, char* pchError);

/*
目的：内部自动实现获取PSAM卡下电操作
函数名：psamPowerOn
输入：
int iSlotNum：卡座号
输出：
char* pchErrCode：错误码
char* pchError：错误码对应的错误信息
返回：
0： 成功
其它 失败
*/
GWI_SAM_ADAPT_API int __stdcall psamPowerOff(int iSlotNum, char* pchErrCode, char* pchError);
/*
目的：内部自动实现获取PSAM卡数据交互操作
函数名：psamPowerOn
输入：
int iSlotNum：卡座号
char* pchInData：输入指令
int iInDataLen：输入指令长度
输出：
char *pchOutData：输出指令
int* iOutDataLen：输出指令长度
char* pchErrCode：错误码
char* pchError：错误码对应的错误信息
返回：
0： 成功
其它 失败
*/
GWI_SAM_ADAPT_API int __stdcall psamExecCmd(int iSlot, char* pchInData, int iInDataLen, char *pchOutData, int* iOutDataLen, char *pchErrCode, char *pchError);

