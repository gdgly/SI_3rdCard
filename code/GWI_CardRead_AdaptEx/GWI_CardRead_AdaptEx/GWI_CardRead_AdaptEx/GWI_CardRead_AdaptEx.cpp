// GWI_CardRead_AdaptEx.cpp : CGWI_CardRead_AdaptExApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "GWI_CardRead_AdaptEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGWI_CardRead_AdaptExApp theApp;

const GUID CDECL _tlid = { 0x277D0D05, 0xA21F, 0x4D09, { 0x8C, 0x14, 0xC7, 0x7, 0xAE, 0xE5, 0xD8, 0x12 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CGWI_CardRead_AdaptExApp::InitInstance - DLL ��ʼ��

BOOL CGWI_CardRead_AdaptExApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CGWI_CardRead_AdaptExApp::ExitInstance - DLL ��ֹ

int CGWI_CardRead_AdaptExApp::ExitInstance()
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
