#pragma once

// GWI_CardRead_AdaptExCtrl.h : CGWI_CardRead_AdaptExCtrl ActiveX 控件类的声明。


// CGWI_CardRead_AdaptExCtrl : 有关实现的信息，请参阅 GWI_CardRead_AdaptExCtrl.cpp。

class CGWI_CardRead_AdaptExCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGWI_CardRead_AdaptExCtrl)

// 构造函数
public:
	CGWI_CardRead_AdaptExCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CGWI_CardRead_AdaptExCtrl();

	DECLARE_OLECREATE_EX(CGWI_CardRead_AdaptExCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CGWI_CardRead_AdaptExCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGWI_CardRead_AdaptExCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CGWI_CardRead_AdaptExCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidocx_GetSN = 11L,
		dispidocx_GetMediaStatus = 10L,
		dispidocx_GetDeviceStatus = 9L,
		dispidocx_ReadCardTracks = 8L,
		dispidocx_ResetDevice = 7L,
		dispidocx_Close_EX = 6L,
		dispidocx_Open_EX = 5L,
		dispidocx_ChipIO_EX = 4L,
		dispidocx_PowerOFF_EX = 3L,
		dispidocx_PowerOn_EX = 2L,
		dispidocx_Init = 1L
	};
protected:
	/*
	目的：初始化通过读配置文件来实现SP调用还是硬件动态库调用
	函数名：ocx_Init
	输入：
	
	输出：
	
	返回：
	0： 成功
	其它 失败
	*/
	LONG ocx_Init(void);
	/*
	目的：掉DLL实现上电操作
	函数名：ocx_PowerOn_EX
	输入：
	LONG iType：上电类型 1-接触式操作卡；2-非接触式操作卡；3-自动寻卡，接触式操作卡优先；4-自动寻卡，非接触式操作卡优先
	LONG lTimeout：超时时间 单位（秒)
	输出：

	返回：
	BSTR：上电复位信息
	*/
	BSTR ocx_PowerOn_EX(LONG iType, LONG lTimeout);
	/*
	目的：内部自动下电，电动式读卡器需要掉此接口吐卡或者掉复位吐卡
	函数名：ocx_PowerOFF_EX
	输入：
	
	输出：

	返回：
	0： 成功
	其它 失败
	*/
	LONG ocx_PowerOFF_EX(void);
	/*
	目的：内部自动实现芯片与读卡器之间的指令交互
	函数名：ocx_ChipIO_EX
	输入：
	LPCTSTR szDataIn：输入指令
	LONG iLenIn：输入指令长度
	输出：
	返回：
	BSTR：iLenOut^lpszDataOut 指令长度^返回指令
	*/
	BSTR ocx_ChipIO_EX(LPCTSTR szDataIn, LONG iLenIn);
	/*
	目的：内部自动实现打开设备
	函数名：ocx_Open_EX
	输入：
	
	输出：
	
	返回：
	0： 成功
	其它 失败
	*/
	LONG ocx_Open_EX(void);
	/*
	目的：内部自动实现关闭设备，会不会自动吐卡吞卡取决于硬件或SP关闭接口，上层透传调用
	函数名：ocx_Close_EX
	输入：
	
	输出：

	返回：
	0： 成功
	其它 失败
	*/
	LONG ocx_Close_EX(void);
	/*
	目的：内部自动实现复位操作，电动读卡器会吐卡
	函数名：ocx_ResetDevice
	输入：
	
	输出：
	
	返回：
	0： 成功
	其它 失败
	*/
	LONG ocx_ResetDevice(void);
	/*
	目的：内部自动读磁道数据
	函数名：ocx_ReadCardTracks
	输入：
	LONG itimeout：超时时间 单位（秒）
	输出：
	
	返回：
	BSTR：pchTrackData2^pchTrackData3^ 二磁道^三磁道^
	*/
	BSTR ocx_ReadCardTracks(LONG itimeout);
	/*
	目的：内部自动实现获取设备状态
	函数名：ocx_GetDeviceStatus
	输入：
	
	输出：
	返回：
	0：设备正常(在线)
	1：设备忙
	2：设备离线
	3：设备故障
	-1：调用出错
	*/
	BSTR ocx_GetDeviceStatus(void);
	/*
	目的：内部自动实现获取卡片状态
	函数名：ocx_GetMediaStatus
	输入：
	
	输出：
	
	返回：
	0：设备正常(在线)
	1：设备忙
	2：设备离线
	3：设备故障
	-1：调用出错
	*/
	BSTR ocx_GetMediaStatus(void);
	BSTR ocx_GetSN(void);
};

