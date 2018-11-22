#pragma  once
// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 GWI_CARDREAD_ADAPT_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// GWI_CARDREAD_ADAPT_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef GWI_CARDREAD_ADAPT_EXPORTS
#define GWI_CARDREAD_ADAPT_API __declspec(dllexport)
#else
#define GWI_CARDREAD_ADAPT_API __declspec(dllimport)
#endif

extern "C"
{

	/*
	目的：内部自动实现读取配置文件实现是直接掉硬件DLL 还是SP得中间件DLL
	函数名：Init
	输入：
	
	输出：

	返回：
	0 成功
	其它 失败
	*/

	GWI_CARDREAD_ADAPT_API int __stdcall Init();
	/*
	目的：内部自动实现卡片上电 集成内部业务逻辑如进卡，判断是IDC还是IC2
	函数名：PowerOn_EX
	输入：
	int iType 卡片上电类型 1-接触式操作卡；2-非接触式操作卡；3-自动寻卡，接触式操作卡优先；4-自动寻卡，非接触式操作卡优先
	long lTimeout 超时时间 单位：秒
	输出：
	char* csAtr  上电信息
	返回：
	0 成功
	其它 失败
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall PowerOn_EX(IN INT iType, IN LONG lTimeout, OUT LPSTR csAtr);

	/*
	目的：内部自动实现卡片下电 与PowerOn_EX对应执行
	函数名：PowerOFF_EX
	输入：
	输出：
	返回：
	0 成功
	其它 失败
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall PowerOFF_EX();

	/*
	目的：内部自动实现卡片数据交互 与PowerOn_EX对应执行
	函数名：ChipIO_EX
	输入：
	LPCSTR szDataIn：指令输入数据
	DWORD iLenIn：指令长度
	输出：
	LPSTR  lpszDataOut：指令回应数据
	DWORD &iLenOut：回应数据长度
	返回：
	0 成功
	其它 失败
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall ChipIO_EX(IN LPCSTR szDataIn, IN DWORD iLenIn, OUT  LPSTR  lpszDataOut,OUT DWORD &iLenOut);

	/*
	目的：内部自动实现打开硬件 包括打开 复位 和 状态监测
	函数名：Open_EX
	输入：
	输出：
	返回：
	1： IDC打开成功  2：IC2打开成功 3：IDC和IC2打开成功
	其它 失败
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall Open_EX();

	/*
	目的：内部自动实现硬件关闭 自动实现关闭退卡 停止前端进卡等
	函数名：Close_EX
	输入：
	输出：
	返回：
	1： IDC关闭成功  2：IC2关闭成功 3：IDC和IC2关闭成功
	其它 失败
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall Close_EX();

	/*
	目的：内部自动复位
	函数名：ResetDevice
	输入：
	输出：
	返回：
	0： 成功
	其它 失败
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall ResetDevice();
	/*
	目的：内部自动实现读2磁和3磁
	函数名：ReadCardTracks
	输入：
	int  itimeout：超时时间
	输出：
	char* pchTrackData2：2磁道数据
	char* pchTrackData3：3磁道数据
	返回：
	0： 成功
	其它 失败
	*/
	GWI_CARDREAD_ADAPT_API  int __stdcall ReadCardTracks (char* pchTrackData2, char* pchTrackData3, int  itimeout);

	/*
	目的：内部自动实现获取设备状态
	函数名：GetDeviceStatus
	输入：
	
	输出：
	int* pDevstatus：状态
	返回：
	0： 成功
	其它 失败
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall GetDeviceStatus( int* pDevstatus);

	/*
	目的：内部自动实现获取卡片状态
	函数名：GetMediaStatus
	输入：
	
	输出：
	int*  pMediastatus：状态
	返回：
	0： 成功
	其它 失败
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall GetMediaStatus(int*  pMediastatus);
};