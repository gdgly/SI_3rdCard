// GWI_SAM_Adapt.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "GWI_SAM_Adapt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;


GWI_SAM_ADAPT_API int __stdcall psamInit()
{
	return 1;
}


GWI_SAM_ADAPT_API int __stdcall psamPowerOn(int iSlotNum, char *pchData, int* iDataLen, char* pchErrCode, char* pchError)
{
	int iRet = psamInit();
	if (0!=iRet)
	{
		strcpy(pchData,"");
		return iRet;
	}
	return 0;
}

GWI_SAM_ADAPT_API int __stdcall psamPowerOff(int iSlotNum, char* pchErrCode, char* pchError)
{
	return 1;
}

GWI_SAM_ADAPT_API int __stdcall psamExecCmd(int iSlot, char* pchInData, int iInDataLen, char *pchOutData, int* iOutDataLen, char *pchErrCode, char *pchError)
{
	return 1;
}
/*
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
*/