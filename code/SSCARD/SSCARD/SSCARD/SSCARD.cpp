// SSCARD.cpp : CSSCARDApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "SSCARD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSSCARDApp theApp;

const GUID CDECL _tlid = { 0x6CA09989, 0xD8DC, 0x4679, { 0xBE, 0x5B, 0xFA, 0x31, 0x0, 0x8A, 0x30, 0xAE } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CSSCARDApp::InitInstance - DLL 初始化

BOOL CSSCARDApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CSSCARDApp::ExitInstance - DLL 终止

int CSSCARDApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。
	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
