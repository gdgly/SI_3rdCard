// GWI_CardRead_AdaptExCtrl.cpp : CGWI_CardRead_AdaptExCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "GWI_CardRead_AdaptEx.h"
#include "GWI_CardRead_AdaptExCtrl.h"
#include "GWI_CardRead_AdaptExPropPage.h"
#include "afxdialogex.h"

#include ".\\lib\\GWI_CardRead_Adapt.h"
#pragma  comment(lib, ".\\lib\\GWI_CardRead_Adapt.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGWI_CardRead_AdaptExCtrl, COleControl)



// 消息映射

BEGIN_MESSAGE_MAP(CGWI_CardRead_AdaptExCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CGWI_CardRead_AdaptExCtrl, COleControl)
	DISP_FUNCTION_ID(CGWI_CardRead_AdaptExCtrl, "ocx_Init", dispidocx_Init, ocx_Init, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CGWI_CardRead_AdaptExCtrl, "ocx_PowerOn_EX", dispidocx_PowerOn_EX, ocx_PowerOn_EX, VT_BSTR, VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CGWI_CardRead_AdaptExCtrl, "ocx_PowerOFF_EX", dispidocx_PowerOFF_EX, ocx_PowerOFF_EX, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CGWI_CardRead_AdaptExCtrl, "ocx_ChipIO_EX", dispidocx_ChipIO_EX, ocx_ChipIO_EX, VT_BSTR, VTS_BSTR VTS_I4)
	DISP_FUNCTION_ID(CGWI_CardRead_AdaptExCtrl, "ocx_Open_EX", dispidocx_Open_EX, ocx_Open_EX, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CGWI_CardRead_AdaptExCtrl, "ocx_Close_EX", dispidocx_Close_EX, ocx_Close_EX, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CGWI_CardRead_AdaptExCtrl, "ocx_ResetDevice", dispidocx_ResetDevice, ocx_ResetDevice, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CGWI_CardRead_AdaptExCtrl, "ocx_ReadCardTracks", dispidocx_ReadCardTracks, ocx_ReadCardTracks, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CGWI_CardRead_AdaptExCtrl, "ocx_GetDeviceStatus", dispidocx_GetDeviceStatus, ocx_GetDeviceStatus, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CGWI_CardRead_AdaptExCtrl, "ocx_GetMediaStatus", dispidocx_GetMediaStatus, ocx_GetMediaStatus, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CGWI_CardRead_AdaptExCtrl, "ocx_GetSN", dispidocx_GetSN, ocx_GetSN, VT_BSTR, VTS_NONE)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CGWI_CardRead_AdaptExCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CGWI_CardRead_AdaptExCtrl, 1)
	PROPPAGEID(CGWI_CardRead_AdaptExPropPage::guid)
END_PROPPAGEIDS(CGWI_CardRead_AdaptExCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CGWI_CardRead_AdaptExCtrl, "GWI_CARDREAD_ADA.GWI_CardRead_AdaCtrl.1",
	0x7f7313cb, 0x3817, 0x4afb, 0xa6, 0x6a, 0xe2, 0x63, 0x98, 0x30, 0x4c, 0xb2)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CGWI_CardRead_AdaptExCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID IID_DGWI_CardRead_AdaptEx = { 0xB028B27E, 0x8384, 0x4A53, { 0x97, 0xB9, 0xC4, 0xAC, 0xCE, 0xDD, 0x99, 0xBA } };
const IID IID_DGWI_CardRead_AdaptExEvents = { 0x366321C, 0xE7BC, 0x4143, { 0x88, 0xAE, 0x39, 0xA8, 0x1E, 0x4A, 0x36, 0xC3 } };


// 控件类型信息

static const DWORD _dwGWI_CardRead_AdaptExOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CGWI_CardRead_AdaptExCtrl, IDS_GWI_CARDREAD_ADAPTEX, _dwGWI_CardRead_AdaptExOleMisc)



// CGWI_CardRead_AdaptExCtrl::CGWI_CardRead_AdaptExCtrlFactory::UpdateRegistry -
// 添加或移除 CGWI_CardRead_AdaptExCtrl 的系统注册表项

BOOL CGWI_CardRead_AdaptExCtrl::CGWI_CardRead_AdaptExCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_GWI_CARDREAD_ADAPTEX,
			IDB_GWI_CARDREAD_ADAPTEX,
			afxRegApartmentThreading,
			_dwGWI_CardRead_AdaptExOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// CGWI_CardRead_AdaptExCtrl::CGWI_CardRead_AdaptExCtrl - 构造函数

CGWI_CardRead_AdaptExCtrl::CGWI_CardRead_AdaptExCtrl()
{
	InitializeIIDs(&IID_DGWI_CardRead_AdaptEx, &IID_DGWI_CardRead_AdaptExEvents);
	// TODO: 在此初始化控件的实例数据。
}



// CGWI_CardRead_AdaptExCtrl::~CGWI_CardRead_AdaptExCtrl - 析构函数

CGWI_CardRead_AdaptExCtrl::~CGWI_CardRead_AdaptExCtrl()
{
	// TODO: 在此清理控件的实例数据。
}



// CGWI_CardRead_AdaptExCtrl::OnDraw - 绘图函数

void CGWI_CardRead_AdaptExCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}



// CGWI_CardRead_AdaptExCtrl::DoPropExchange - 持久性支持

void CGWI_CardRead_AdaptExCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}



// CGWI_CardRead_AdaptExCtrl::OnResetState - 将控件重置为默认状态

void CGWI_CardRead_AdaptExCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}



// CGWI_CardRead_AdaptExCtrl 消息处理程序


LONG CGWI_CardRead_AdaptExCtrl::ocx_Init(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	return Init();
}


BSTR CGWI_CardRead_AdaptExCtrl::ocx_PowerOn_EX(LONG iType, LONG lTimeout)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	char ATR[MAX_PATH] = {};
	PowerOn_EX(iType,lTimeout,ATR);

	CString strResult(ATR);

	// TODO: 在此添加调度处理程序代码

	return strResult.AllocSysString();
}


LONG CGWI_CardRead_AdaptExCtrl::ocx_PowerOFF_EX(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	
	return PowerOFF_EX();
}


BSTR CGWI_CardRead_AdaptExCtrl::ocx_ChipIO_EX(LPCTSTR szDataIn, LONG iLenIn)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	

	// TODO: 在此添加调度处理程序代码
	char lpszDataOut[1024] = {};
	DWORD lDataOutLen = 0;
	ChipIO_EX(szDataIn,iLenIn,lpszDataOut,lDataOutLen);
	char csInfo[1024+32] = {};
	sprintf_s(csInfo,1024+32,"%d^%s^",lDataOutLen,lpszDataOut);
	CString strResult(csInfo);
	return strResult.AllocSysString();
}


LONG CGWI_CardRead_AdaptExCtrl::ocx_Open_EX(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return Open_EX();
}


LONG CGWI_CardRead_AdaptExCtrl::ocx_Close_EX(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return Close_EX();
}


LONG CGWI_CardRead_AdaptExCtrl::ocx_ResetDevice(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return ResetDevice();
}


BSTR CGWI_CardRead_AdaptExCtrl::ocx_ReadCardTracks(LONG itimeout)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	char csTrack2[MAX_PATH] = {};
	char csTrack3[MAX_PATH] = {};
	ReadCardTracks(csTrack2,csTrack3,itimeout);
	char csInfo[512] = {};
	sprintf_s(csInfo,"%s^%s^",csTrack2,csTrack3);
	CString strResult(csInfo);
	// TODO: 在此添加调度处理程序代码
	return strResult.AllocSysString();
}


BSTR CGWI_CardRead_AdaptExCtrl::ocx_GetDeviceStatus(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	int iStatus = -1;
	GetDeviceStatus(&iStatus);
	int high = iStatus>>16;
	int low  = iStatus&0x0000FFFF;
	char csstatus[MAX_PATH] = {};
	sprintf_s(csstatus,MAX_PATH,"%d^%d^",high,low);
	CString strResult(csstatus);
	// TODO: 在此添加调度处理程序代码

	return strResult.AllocSysString();

}


BSTR CGWI_CardRead_AdaptExCtrl::ocx_GetMediaStatus(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	int iStatus = -1;
	GetDeviceStatus(&iStatus);
	int high = iStatus>>16;
	int low  = iStatus&0x0000FFFF;
	char csMediastatus[MAX_PATH] = {};
	sprintf_s(csMediastatus,MAX_PATH,"%d^%d^",high,low);
	CString strResult(csMediastatus);
	// TODO: 在此添加调度处理程序代码
	return strResult.AllocSysString();
}


BSTR CGWI_CardRead_AdaptExCtrl::ocx_GetSN(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	char cSN[MAX_PATH] = {};
	GetSN(cSN);
	CString strResult(cSN);

	// TODO: 在此添加调度处理程序代码
	
	return strResult.AllocSysString();
}
