// GWI_CardRead_Adapt.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "GWI_CardRead_Adapt.h"
#include "DCardRead.h"
#include "IcCardRead.h"
#include "lock.h"

#include "HCardRead_ICT3k9.h"
#include "HIC2_MT.h"
#include "log.h"
#include <string>
#include <process.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDCardRead* dr =NULL;
CIcCardRead* ir=NULL;
CHCardReadBase* hdr = NULL;
CHIc2Base* hir = NULL;

int iLogicType = 0;
int iMediaType = 0; //1.�Ӵ�  2.�ǽӴ�
bool bLogicEnd = false;
char csATR[MAX_PATH];

bool bIsOpen = false;
CriSection criSection;
// Ψһ��Ӧ�ó������

CWinApp theApp;


char strLog[1024];
char strL[1024];

using namespace std;

#define  CONFIG_PATH_DEFAULT "c:\\gwi_cardread_adapt_api_config.ini"
#define  CONFIG_PATH ".\\gwi_cardread_adapt_api_config.ini"
#define  APP "cardread"
#define  SECTION "init"
#define  SEC_DEVTYPR "devtype"
#define  SEC_IC2 "ic2"

#define ICT3k9 "ICT3k9"
#define MT  "MT"
int iInitIni = -1;

GWI_CARDREAD_ADAPT_API int __stdcall Init()
{
	setTraceLevel(0x1111);
	INFO("Enter.")
	//���ȼ�Ϊ1.CONFIG_PATH_DEFAULT  2.CONFIG_PATH  3.������ΪSP
	iInitIni = -1;
	char csDevtype[MAX_PATH] = {};
	char csIC2[MAX_PATH] = {};
	iInitIni = ::GetPrivateProfileIntA(APP,SECTION,0,CONFIG_PATH_DEFAULT);
	if (1!=iInitIni || 2!=iInitIni)
	{
		iInitIni = ::GetPrivateProfileIntA(APP,SECTION,0,CONFIG_PATH);
		::GetPrivateProfileStringA(APP,SEC_DEVTYPR,"",csDevtype,MAX_PATH,CONFIG_PATH);
		::GetPrivateProfileStringA(APP,SEC_IC2,"",csIC2,MAX_PATH,CONFIG_PATH);
	}
	else
	{
		::GetPrivateProfileStringA(APP,SEC_DEVTYPR,"",csDevtype,MAX_PATH,CONFIG_PATH_DEFAULT);
		::GetPrivateProfileStringA(APP,SEC_IC2,"",csIC2,MAX_PATH,CONFIG_PATH_DEFAULT);
	}
	iInitIni = 1==iInitIni?1:2;
	sprintf(strLog,"%d",iInitIni);
	DEBUG(strLog);
	if (2==iInitIni)
	{
		
		dr = new CDCardRead();
		ir = new CIcCardRead();
	}
	else //��Ӳ����̬�ⷽʽ
	{
		if (0 == strcmp(ICT3k9,csDevtype))
		{
			hdr = nullptr==hdr? new HCardRead_ICT3k9():hdr;
		}
		//----------------------//
		if (0 == strcmp(MT,csIC2))
		{
			hir = new CHIC2_MT();
		}
	}
	INFO("Exit:0");
	return 0;
}

GWI_CARDREAD_ADAPT_API int __stdcall Open_EX()
{
	INFO("Enter.");
	bIsOpen = true;
	
	if (1==iInitIni)
	{
		int iHDRret,iHIRret;
		if(hdr)iHDRret=hdr->OpenDevice();
		if(hir)iHIRret=hir->OpenDevice();

		int iRet = 0==iHDRret?1:0;
		iRet = 0==iHIRret?iRet+2:iRet;
		sprintf(strLog,"%d",iRet);
		INFO(strLog);
		return iRet;
	}
	
	int iDRret = dr->OpenDevice();
	int iIRret = ir->OpenDevice();

	int iRet = 0==iDRret?1:0;
	iRet = 0==iIRret?iRet+2:iRet;
	sprintf(strLog,"%d",iRet);
	INFO(strLog);
	return iRet;
}

GWI_CARDREAD_ADAPT_API int __stdcall Close_EX()
{
	INFO("Enter.");
	IS_OPEN
	int iDRret,iIRret;

	if (1==iInitIni)
	{
		if(hdr)iDRret = hdr->CloseDevice();
		if(hir)iIRret=hir->CloseDevice();
	}
	else
	{
		if(dr)iDRret = dr->CloseDevice();
		if (ir)iIRret = ir->CloseDevice();
	}
	
	if (dr)
	{
		delete dr;
		dr = nullptr;
	}
	if (ir)
	{
		delete ir;
		ir = nullptr;
	}
	if (hdr)
	{
		delete hdr;
		hdr = nullptr;
	}
	if (hir)
	{
		delete hir;
		hir = nullptr;
	}
	iLogicType = 0;
	iMediaType = 0; //1.�Ӵ�  2.�ǽӴ�
	bLogicEnd = false;
	iInitIni = -1;
	int iRet = 0==iDRret?1:0;
	iRet = 0==iIRret?iRet+2:iRet;
	bIsOpen = false;
	sprintf(strLog,"%d",iRet);
	INFO(strLog);
	return iRet;
}

unsigned int __stdcall IDC_InhaleGetStaus(void *param)
{
	
	//���������λΪ��
	//1.���� 2.��ȡ������״̬ 3.����bLogicEnd=true 4.����iLogicType=1
	int iret = 1;
	int imedia[4] = {0};
	int count = 0;
	DWORD* dwTimeout = (DWORD*)param;
	LONG lTimeout = *dwTimeout*1000*0.8;

	sprintf(strLog,"Enter.param[%d]",lTimeout);
	DEBUG(strLog);

	//�Ȼ�ȡ����״̬Ϊ1 ��ͨ����ֱ�Ӷ���
	if (1==iInitIni)
	{
		if(nullptr == hdr) 
		{
			DEBUG("(DLL-���ϵ�ӿڲ���ʽ������-��hdrΪNULL)")
			return 3;
		}
		int iMediaStatus = -1;
		iret = hdr->GetMediaStatus(&iMediaStatus);
		if (1 == iMediaStatus)
		{
			criSection.Lock();
			bLogicEnd =true;
			iLogicType=1;
			criSection.Unlock();
			sprintf(strLog,"Exit:0.bLogicEnd[%d],iLogicType[%d]",bLogicEnd,iLogicType);
			DEBUG(strLog);
			DEBUG("DLL-���ϵ�ӿڲ���ʽ������-��Exit:0 ���ڶ�������Ӧλ��");
			return 0;
		}
		//��Ϊ1 ���ȵ����˿���ֹ�п���λ�ò�������Ĳ�����
		hdr->EjectICard();
	}
	else
	{
		if(nullptr == dr) 
		{
			DEBUG("(SP-���ϵ�ӿڲ���ʽ������-��drΪNULL)")
			return 3;
		}
		int iMediaStatus = -1;
		iret = dr->GetMediaStatus(&iMediaStatus);

		sprintf(strLog,"DLL-���ϵ�ӿڲ���ʽ������-��iMediaStatus[%d]",iMediaStatus);
		DEBUG(strLog);
		if (1 == iMediaStatus || 7 == iMediaStatus)
		{
			criSection.Lock();
			bLogicEnd =true;
			iLogicType=1;
			criSection.Unlock();
			sprintf(strLog,"Exit:0.bLogicEnd[%d],iLogicType[%d]",bLogicEnd,iLogicType);
			DEBUG(strLog);
			DEBUG("SP-���ϵ�ӿڲ���ʽ������-��Exit:0 ���ڶ�������Ӧλ��");
			return 0;
		}
		//��Ϊ1 ���ȵ����˿���ֹ�п���λ�ò�������Ĳ�����
		//dr->EjectICard();
	}
	DEBUG("(DLL-���ϵ�ӿڲ���ʽ������-��EjectICard)")
	DWORD dwTick0 = GetTickCount();
	DWORD dwTick1 = GetTickCount();

	while(dwTick1-dwTick0 < lTimeout && !bLogicEnd)
	{
		sprintf(strLog,"IDC_InhaleGetStaus -> count[%d]",++count);
		DEBUG(strLog);
		if (1==iInitIni)
		{
			if(hdr) iret = hdr->InhaleCard(*dwTimeout);
		}
		else
		{
			iret = dr->InhaleCard(*dwTimeout);
		}
		sprintf(strLog,"IDC_InhaleGetStaus -> InhaleCard ret[%d]",iret);
		DEBUG(strLog);
		if(0==iret) break;
		Sleep(400);
		dwTick1 = GetTickCount();
	}
	
	if (0==iret)
	{
		DEBUG("(�ϵ�ӿڲ���ʽ������-�������ɹ�)");
		criSection.Lock();
		bLogicEnd =true;
		iLogicType=1;
		criSection.Unlock();
		sprintf(strLog,"Exit:0.bLogicEnd[%d],iLogicType[%d]",bLogicEnd,iLogicType);
		DEBUG(strLog);
		DEBUG("Exit:0 �綯�������߳̽���");
		return 0;
	}
	
	sprintf(strLog,"Exit:1.bLogicEnd[%d],iLogicType[%d]",bLogicEnd,iLogicType);
	DEBUG(strLog);
	DEBUG("Exit:1 �綯�������߳̽���")
	return 1;
	
}

unsigned int __stdcall IC2_GetStaus(void *param)
{
	//���������λΪ��
	//1.��ȡ������״̬ 2.����bLogicEnd=true 3.����iLogicType=1
	DWORD dwTick0 = GetTickCount();
	DWORD dwTick1 = GetTickCount();
	DWORD* dwTimeout = (DWORD*)param;
	LONG lTimeout = *dwTimeout*1000;
	int imedia[4] = {};
	sprintf(strLog,"Enter.param[%d]",lTimeout);
	DEBUG(strLog);
	int count = 0;
	while(dwTick1-dwTick0 < lTimeout && !bLogicEnd)
	{
		sprintf(strLog,"IC2_GetStaus -> count[%d]",++count);
		DEBUG(strLog);
		if (1==iInitIni)
		{
			if(hir && 0 == hir->GetMediaStatus(imedia))
			{
				sprintf(strLog,"IC2_GetStaus -> GetMediaStatus [%d]",imedia);
				DEBUG(strLog);
				if (1==imedia[0])
				{
					criSection.Lock();
					bLogicEnd =true;
					iLogicType=2;
					criSection.Unlock();
					DEBUG("Exit:0(DLL-���ϵ�ӿڷǽӴ�������-����ȡ״̬Ϊ1�����¶�����״̬)")
					return 0;
				}
			}
		}
		else
		{
			if(0 == ir->GetMediaStatus(imedia))
			{
				sprintf(strLog,"IC2_GetStaus -> GetMediaStatus [%d]",imedia);
				DEBUG(strLog);
				if (1==imedia[0])
				{
					criSection.Lock();
					bLogicEnd =true;
					iLogicType=2;
					criSection.Unlock();
					DEBUG("Exit:0(SP-���ϵ�ӿڷǽӴ�������-����ȡ״̬Ϊ1�����¶�����״̬)")
					return 0;
				}
			}
		}
		
		Sleep(400);
		dwTick1 = GetTickCount();
	}
	DEBUG("Exit:1(DLL�ϵ�ӿڷǽӴ�������-����ȡ״̬ʧ�� ���߲�Ϊ1)")
	return 1;
}

GWI_CARDREAD_ADAPT_API int __stdcall PowerOn_EX(IN INT iType, IN LONG lTimeout, OUT LPSTR csAtr)
{
	sprintf(strLog,"Enter.iType[%d];lTimeout[%d]",iType,lTimeout);
	INFO(strLog);
	IS_OPEN
	//��ʼ������
	iLogicType = 0;
	bLogicEnd = false;
	iMediaType = 0;
	int iret = -1;
	memset(csATR,0x00,sizeof(csATR));
	sprintf(strLog,"iLogicType[%d]",iLogicType);
	DEBUG(strLog);
	if (1!=iLogicType && 2!=iLogicType) //wsh��20180620 �������ϵ� ������ظ�������Ч������ �� ҵ���߼�����
	{
		DWORD lTickBefore = GetTickCount();
		DWORD lTickNow=GetTickCount();

		HANDLE h1,h2;
		unsigned uth1,uth2;
		h1 = (HANDLE)_beginthreadex( NULL,         // security
			0,            // stack size
			IDC_InhaleGetStaus,
			&lTimeout,           // arg list
			0,  // so we can later call ResumeThread()
			&uth1);
		h2= (HANDLE)_beginthreadex( NULL,         // security
			0,            // stack size
			IC2_GetStaus,
			&lTimeout,           // arg list
			0,  // so we can later call ResumeThread()
			&uth2);
		Sleep(200);
		DWORD dwTimeOut = lTimeout*1.2*1000;
		HANDLE hArray[] = {h1,h2};
		WaitForMultipleObjects(2,hArray,TRUE,INFINITE);
		CloseHandle( h1 );
		CloseHandle( h2 );

		if (1==iInitIni)
		{
			if(hdr) hdr->StopInhaleCard();
		}
		else
		{
			dr->StopInhaleCard();//���ۺ��ֽ�������Ҫ����ǰ�˽���
		}
	}
	sprintf(strLog,"iLogicType[%d]",iLogicType);
	DEBUG(strLog);
	//����ͬ������ʽ�Ķ��ද��
	if (1==iLogicType)//IDC���� 
	{
		if (1==iType)//1-�Ӵ�ʽ������
		{
			iMediaType = 1;
			if (1==iInitIni)
			{
				if(hdr) iret = hdr->ChipPowerOn(csATR);
			}
			else
			{
				iret = dr->ChipPowerOn(csATR);
			}
		}
		if (2==iType)//2-�ǽӴ�ʽ��������
		{
			iMediaType = 2;
			if (1==iInitIni)
			{
				if (hdr)iret = hdr->RFChipPowerOn(csATR);
			}
			else
			{
				iret = dr->RFChipPowerOn(csATR);
			}
		}
		if (3==iType)//3-�Զ�Ѱ�����Ӵ�ʽ����������
		{
			if (1==iInitIni)
			{
				if(hdr)iret = hdr->ChipPowerOn(csATR);
				iMediaType = 1;
				if (0!=iret)
				{
					iMediaType = 2;
					if(hdr)iret = hdr->RFChipPowerOn(csATR);
				}
			}
			else
			{
				iret = dr->ChipPowerOn(csATR);
				iMediaType = 1;
				if (0!=iret)
				{
					iMediaType = 2;
					iret = dr->RFChipPowerOn(csATR);
				}
			}
		}
		if (4==iType)//4-�Զ�Ѱ�����ǽӴ�ʽ����������
		{
			if (1==iInitIni)
			{
				iMediaType = 2;
				if(hdr)iret = hdr->RFChipPowerOn(csATR);
				if (0!=iret)
				{
					iMediaType = 1;
					if(hdr)iret = hdr->ChipPowerOn(csATR);
				}
			}
			else
			{
				iMediaType = 2;
				iret = dr->RFChipPowerOn(csATR);
				if (0!=iret)
				{
					iMediaType = 1;
					iret = dr->ChipPowerOn(csATR);
				}
			}
		}
	}
	else if (2==iLogicType)
	{
		if (1==iInitIni)
		{
			iMediaType = 2;
			if(hir)iret =hir->ChipPowerOn(csATR);
		}
		else
		{
			iMediaType = 2;
			iret =ir->ChipPowerOn(csATR);
		}
	}
	sprintf(csAtr,"%s",csATR);

	sprintf(strLog,"iLogicType[%d];iMediaType[%d]",iLogicType,iMediaType);
	DEBUG(strLog);
	sprintf(strLog,"Exit:iret[%d];csAtr[%s]",iret,csAtr);
	INFO(strLog);
	return iret;
}

GWI_CARDREAD_ADAPT_API int __stdcall PowerOFF_EX()
{
	INFO("Enter.");
	IS_OPEN
	int iret = -1;
	sprintf(strLog,"iLogicType[%d];iInitIni[%d]",iLogicType,iInitIni);
	DEBUG(strLog);
	if (1==iLogicType)//IDC���� 
	{
		if (1==iMediaType)
		{
			if (1==iInitIni)
			{
				if(hdr) iret = dr->ChipPowerOff();
			}
			else
			{
				iret = dr->ChipPowerOff();
			}
		}
		else if(2==iMediaType)
		{

			if (1==iInitIni)
			{
				if(hdr)iret = hdr->RFChipPowerOff();
			}
			else
			{
				iret = dr->RFChipPowerOff();
			}
		}
	}
	else if (2==iLogicType)//IC2����
	{
		if (2==iMediaType )//IC2û���ϵ�� ���˳�
		{
			if (1==iInitIni)
			{
				if (hir)iret = hir->ChipPowerOff();
			}
			else
			{
				iret = ir->ChipPowerOff();
			}
		}
	}

	if (1==iInitIni)
	{
		if(hdr)iret = hdr->EjectICard();
	}
	else
	{
		iret = dr->EjectICard();
	}
	iLogicType = 0;
	iMediaType = 0; //1.�Ӵ�  2.�ǽӴ�
	bLogicEnd = false;
	sprintf(strLog,"Exit:iret[%d]",iret);
	INFO(strLog);
	return iret;
}

GWI_CARDREAD_ADAPT_API int __stdcall ChipIO_EX(IN LPCSTR szDataIn, IN DWORD iLenIn, OUT  LPSTR  lpszDataOut,OUT DWORD &iLenOut)
{
	sprintf(strLog,"szDataIn[%s];iLenIn[%d]",szDataIn,iLenIn);
	INFO("Enter.");
	IS_OPEN
	sprintf(strLog,"iLogicType[%d];iMediaType[%d],iInitIni[%d]",iLogicType,iMediaType,iInitIni);
	DEBUG(strLog);
	int iret = -1;
	if (1==iLogicType)//IDC���� 
	{
		if (1==iMediaType)
		{
			if (1==iInitIni)
			{
				if(hdr)iret = hdr->ICCChipIo((char*)szDataIn,iLenIn,lpszDataOut,iLenOut);
			}
			else
			{
				iret = dr->ICCChipIo((char*)szDataIn,iLenIn,lpszDataOut,iLenOut);
			}
		}
		else if(2==iMediaType)
		{
			if (1==iInitIni)
			{
				if(hdr)iret = dr->RFChipIo((char*)szDataIn,iLenIn,lpszDataOut,iLenOut);
			}
			else
			{
				iret = dr->RFChipIo((char*)szDataIn,iLenIn,lpszDataOut,iLenOut);
			}
		}
	}
	else if (2==iLogicType)//IC2����
	{
		if (1==iInitIni)
		{
			if(hir)iret = hir->ICCChipIo(0,(char*)szDataIn,lpszDataOut);
		}
		else
		{
			iret = ir->ICCChipIo(0,(char*)szDataIn,lpszDataOut);
		}
	}
	iLenOut = strlen(lpszDataOut);
	sprintf(strLog,"in[%s];out[%s]",szDataIn,lpszDataOut);
	DEBUG(strLog);
	sprintf(strLog,"Exit:iret[%d];lpszDataOut[%s],iLenOut[%d]",iret,lpszDataOut,iLenOut);
	INFO(strLog);
	return iret;
}

GWI_CARDREAD_ADAPT_API int __stdcall ResetDevice()
{
	INFO("Enter.");
	IS_OPEN
	sprintf(strLog,"iLogicType[%d];iMediaType[%d],iInitIni[%d]",iLogicType,iMediaType,iInitIni);
	DEBUG(strLog);
	int iret = -1;
	int idret = -1,iiret = -1;
	if (1==iInitIni)
	{
		if(hdr)idret = hdr->ResetDevice();
		if(hir)iiret = hir->ResetDevice();
	}
	else
	{
		idret = dr->ResetDevice();
		iiret = ir->ResetDevice();
	}
	iret = 0==idret?1:0;
	iret = 0==iiret?iret+2:iret;
	sprintf(strLog,"Exit:iret[%d]",iret);
	INFO(strLog);
	iLogicType = 0;
	iMediaType = 0; //1.�Ӵ�  2.�ǽӴ�
	bLogicEnd = false;
	return iret;
}

GWI_CARDREAD_ADAPT_API  int __stdcall ReadCardTracks (char* pchTrackData2, char* pchTrackData3, int  itimeout)
{
	sprintf(strLog,"Enter.itimeout[%d]",itimeout);
	INFO(strLog);
	IS_OPEN
	sprintf(strLog,"iLogicType[%d];iMediaType[%d],iInitIni[%d]",iLogicType,iMediaType,iInitIni);
	DEBUG(strLog);
	if (1!=iLogicType && 2!=iLogicType)
	{
		HANDLE h1;
		unsigned uth1;
		LONG lTimeout = itimeout;
		h1 = (HANDLE)_beginthreadex( NULL,         // security
			0,            // stack size
			IDC_InhaleGetStaus,
			&lTimeout,           // arg list
			0,  // so we can later call ResumeThread()
			&uth1);
		Sleep(200);
		WaitForSingleObject(h1,INFINITE);
	
		if (1==iInitIni)
		{
			if(hdr) hdr->StopInhaleCard();
		}
		else
		{
			dr->StopInhaleCard();//���ۺ��ֽ�������Ҫ����ǰ�˽���
		}
	}
	sprintf(strLog,"iLogicType[%d],iInitIni[%d]",iLogicType,iInitIni);
	DEBUG(strLog);
	int iret = -1;
	if (1==iLogicType)//IDC���� 
	{
		if (1==iInitIni)
		{
			if(hdr) hdr->ReadCardTracks(23,pchTrackData2,pchTrackData3,itimeout);
		}
		else
		{
			iret = dr->ReadCardTracks(23,pchTrackData2,pchTrackData3,itimeout);
		}
	}

	sprintf(strLog,"Exit:iret[%d];pchTrackData2[%s];pchTrackData3[%s]",iret,pchTrackData2,pchTrackData3);
	INFO(strLog);
	return iret;
}

GWI_CARDREAD_ADAPT_API int __stdcall GetDeviceStatus( int* pDevstatus)
{
	INFO("Enter.");
	IS_OPEN
	sprintf(strLog,"iLogicType[%d];iMediaType[%d],iInitIni[%d]",iLogicType,iMediaType,iInitIni);
	DEBUG(strLog);
	int iret = -1;
	int idret = -1,iiret = -1;
	int ddev,idev;
	if (1==iInitIni)
	{
		if(hdr)idret = dr->GetDeviceStatus(&ddev);
		if(hir)iiret = ir->GetDeviceStatus(&idev);
	}
	else
	{
		idret = dr->GetDeviceStatus(&ddev);
		iiret = ir->GetDeviceStatus(&idev);
	}

	int ipDevstatus=(ddev&0x0000FFFF)<<16+idev&0x0000FFFF;
	*pDevstatus = ipDevstatus;
	iret = 0==idret?1:0;
	iret = 0==iiret?iret+2:iret;
	sprintf(strLog,"Exit:iret[%d];dstatus[%d];istatus[%d];pDevstatus[%d]",iret,ddev,idev,ipDevstatus);
	INFO(strLog);
	return iret;
}

GWI_CARDREAD_ADAPT_API int __stdcall GetMediaStatus(int*  pMediastatus)
{
	INFO("Enter.");
	IS_OPEN
	sprintf(strLog,"iLogicType[%d];iMediaType[%d],iInitIni[%d]",iLogicType,iMediaType,iInitIni);
	DEBUG(strLog);
	int iret = -1;
	int idret = -1,iiret = -1;
	int ddev,idev;
	if (1==iInitIni)
	{
		if(hdr)idret = hdr->GetMediaStatus(&ddev);
		if(hir)iiret = hir->GetMediaStatus(&idev);
	}
	else
	{
		idret = dr->GetMediaStatus(&ddev);
		iiret = ir->GetMediaStatus(&idev);
	}
	int ipMediastatus=(ddev&0x0000FFFF)<<16+idev&0x0000FFFF;
	*pMediastatus = ipMediastatus;
	iret = 0==idret?1:0;
	iret = 0==iiret?iret+2:iret;
	sprintf(strLog,"Exit:iret[%d];dstatus[%d];istatus[%d];pMediastatus[%d]",iret,ddev,idev,ipMediastatus);
	INFO(strLog);
	return iret;
}

GWI_CARDREAD_ADAPT_API int __stdcall GetSN(char* sn)
{
	LONG result,istatus=0;
	int iret = 1;
	HKEY hMachine = HKEY_LOCAL_MACHINE;
	HKEY hKey;
	DWORD dwBufLen;
	char tempdata[256];
	result = RegOpenKeyExA(hMachine, "SOFTWARE\\WOW6432Node\\XFSDLL\\SPLogicName",0, KEY_ALL_ACCESS, &hKey);

	if(result == ERROR_SUCCESS)
	{
		dwBufLen = sizeof( tempdata );
		if (1==iLogicType)//IDC���� 
		{
			result = RegQueryValueExA( hKey, "IDCTerminalSN", NULL, NULL,(LPBYTE)tempdata, &dwBufLen );
			if(result == ERROR_SUCCESS)
			{
				sprintf(sn,"%s",tempdata);
				iret = 0;
			}
		}
		else if (2==iLogicType)
		{
			result = RegQueryValueExA( hKey, "IC2TerminalSN", NULL, NULL,(LPBYTE)tempdata, &dwBufLen );
			if(result == ERROR_SUCCESS)
			{
				sprintf(sn,"%s",tempdata);
				iret = 0;
			}
		}
		else
		{
			sprintf(sn,"%s","");
			iret = 1;
		}
	  
		RegCloseKey(hKey);
		return iret;
	}
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