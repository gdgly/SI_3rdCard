// SSCARD.cpp : CSSCARDApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "SSCARD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSSCARDApp theApp;

const GUID CDECL _tlid = { 0x6CA09989, 0xD8DC, 0x4679, { 0xBE, 0x5B, 0xFA, 0x31, 0x0, 0x8A, 0x30, 0xAE } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CSSCARDApp::InitInstance - DLL ��ʼ��

BOOL CSSCARDApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CSSCARDApp::ExitInstance - DLL ��ֹ

int CSSCARDApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣
	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
