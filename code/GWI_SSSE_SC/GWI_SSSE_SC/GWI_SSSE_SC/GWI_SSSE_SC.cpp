// GWI_SSSE_SC.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "GWI_SSSE_SC.h"
#include "log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

#define  LEN_1024 1024
char strL[LEN_1024];

_ResponseError respError[] = {
	{0x90,0x00,"ִ�гɹ�"},
	{0x63,0xC0,"����ʧ�ܣ� ����������ԵĴ���"},
	{0x65,0x81,"�ڴ����"},
	{0x67,0x00,"P1�� P2 �� Lc ��һ��"},
	{0x69,0x81,"�������ļ��ṹ������"},
	{0x69,0x82,"�����㰲ȫ״̬"},
	{0x69,0x83,"��֤��������"},
	{0x69,0x84,"����������Ч"},
	{0x69,0x85,"������ʹ������"},
	{0x69,0x86,"�������ʹ�ã��޵�ǰ�����ļ���"},
	{0x69,0x88,"��ȫ�����������ȷ"},
	{0x6A,0x80,"�������������ȷ"},
	{0x6A,0x81,"���ܲ���֧��"},
	{0x6A,0x82,"δ�ҵ��ļ�"},
	{0x6A,0x83,"δ�ҵ���¼"},
	{0x6A,0x86,"���� P1�� P2 ����ȷ"},
	{0x6A,0x88,"��Կδ�ҵ�"},
	{0x6C,0x00,"���ȴ��� Le ����"},
	{0x6E,0x00,"CLA ��"},
	{0x93,0x03,"Ӧ�ñ���������"},
	{0x00,0x00,"��ȡSW1��SW2ʧ��"}
};

static int respError_len = sizeof(respError) /sizeof(respError[0]);


static void getRespSw1Sw2(char* csData,char& sw1,char& sw2)
{
	if (nullptr == csData || strlen(csData) < 2)
	{
		sw1 = 0x00;
		sw2 = 0x00;
		return;
	}
	int iLen = strlen(csData);
	unsigned char sw1sw2[3] = {};
	DSP_2_HEX((unsigned char*)(csData+iLen-4),sw1sw2,2);
	sw1=sw1sw2[0];
	sw2=sw1sw2[1];
}

static void getRespError(char sw1,char sw2,char* errorMsg)
{
	if (nullptr == errorMsg) return;

	if (0x6E ==  sw1 || 0x6e == sw1)
	{
		sprintf(errorMsg,"���ȴ��� Le ���󣩳���Ϊ��%d",(int)sw2);
		return;
	}
	if (0x63 ==  sw1)
	{
		sprintf(errorMsg,"����ʧ�ܣ� ����������ԵĴ���%d",(int)(sw2&0x0F));
		return;
	}
	for (int i=0; i<respError_len;i++)
	{
		if (sw1 == respError[i].sw1 && sw2 == respError[i].sw2)
		{
			sprintf(errorMsg,"%s",respError[i].msg);
			return;
		}
	}
	sprintf(errorMsg,"%s","δ֪����");
}

static void getRespErrorCodeMsg(char* csData,char* csCode, char* csMsg)
{
	char sw1,sw2;
	getRespSw1Sw2(csData,sw1,sw2);
	sprintf(csCode,"%c%c",sw1,sw2);
	getRespError(sw1,sw2,csMsg);
}

int doApdu(const char* in, char* out)
{
	LOG_DEBUG(in);
	/* ׮����
	out[0]='0';
	out[1]='F';
	out[2]='9';
	out[3]='0';
	out[4]='0';
	out[5]='0';
	*/
	DWORD iLenin = strlen(in);
	DWORD iLenout = 0;
	int iret = -1;
	iret = ChipIO_EX(in,iLenin,out,iLenout);
	LOG_DEBUG(out);
	return iret;
}
//----------------------------------------------------------------------//


int doExchange(unsigned char* inData,int inDataLen,char* outData,int& outDataLen)
{
	int iret = -1;
	unsigned char ucIndata[LEN_1024] = {};
	HEX_2_DSP((unsigned char*)inData,ucIndata,inDataLen);
	iret = doApdu((char*)ucIndata,outData);
	outDataLen = strlen((outData));
	return iret;
}

GWI_SSSE_SC_API int SELECT_SSSE_YH(char* outData,int& outDataLen,char* errorCode, char* errorMsg)
{
	char rapdu[LEN_1024] = {};
	unsigned char capdu[LEN_1024] = {};
	capdu[0] = 0x00;
	capdu[1] = 0xA4;
	capdu[2] = 0x04;
	capdu[3] = 0x00;
	capdu[4] = 0x0F;
	memcpy(capdu+5,"\x73\x78\x31\x2E\x73\x68\x2E\xC9\xE7\xBB\xE1\xB1\xA3\xD5\xCF", 15);
	//ִ��apdu
	int inDataLen = 20;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"���ó���");
		return iret;
	}
	getRespErrorCodeMsg(rapdu,errorCode,errorMsg);
	strcpy(outData,rapdu);
	return 0;
}

GWI_SSSE_SC_API int SELECT_FILE_SSSE_YH(unsigned char P1, unsigned char Lc, unsigned char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg)
{
	char rapdu[LEN_1024] = {};
	unsigned char capdu[LEN_1024] = {};
	capdu[0] = 0x00;
	capdu[1] = 0xA4;
	capdu[2] = P1;
	capdu[3] = 0x00;
	capdu[4] = Lc;

	unsigned char ucLc[3] = {};
	HEX_2_DSP(&Lc,ucLc,1);

	int inDataLen = (ucLc[0]-0x30)*16+(ucLc[1]-0x30);
	memcpy(capdu+5,inData, inDataLen);
	//ִ��apdu
	inDataLen+=5;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"���ó���");
		return iret;
	}
	getRespErrorCodeMsg(rapdu,errorCode,errorMsg);
	strcpy(outData,rapdu);
	return 0;
}
GWI_SSSE_SC_API int GET_CHALLENGE_SSSE_YH(unsigned char Le,char* outData,int& outDataLen,char* errorCode, char* errorMsg)
{

	char rapdu[128] = {};
	unsigned char capdu[128] = {};
	capdu[0] = 0x00;
	capdu[1] = 0x84;
	capdu[2] = 0x00;
	capdu[3] = 0x00;
	capdu[4] = Le; 
	
	//ִ��apdu
	int inDataLen = 5;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"���ó���");
		return iret;
	}
	getRespErrorCodeMsg(rapdu,errorCode,errorMsg);
	strcpy(outData,rapdu);
	return 0;
}

GWI_SSSE_SC_API int INTERNAL_AUTHENTICATION_SSSE_YH(unsigned char Lc, char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg)
{
	char rapdu[128] = {};
	unsigned char capdu[128] = {};
	capdu[0] = 0x00;
	capdu[1] = 0x88;
	capdu[2] = 0x00;
	capdu[3] = 0x00;
	capdu[4] = Lc; 

	//ִ��apdu
	int inDataLen = strlen(inData);
	DSP_2_HEX((unsigned char*)inData,(unsigned char*)(capdu+5),inDataLen);
	inDataLen = inDataLen/2 + 5;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"���ó���");
		return iret;
	}
	getRespErrorCodeMsg(rapdu,errorCode,errorMsg);
	strcpy(outData,rapdu);
	return 0;
}

GWI_SSSE_SC_API int READ_RECORD_SSSE_YH(unsigned char P1, unsigned char P2, unsigned char Le, char* outData,int& outDataLen,char* errorCode, char* errorMsg)
{
	char rapdu[128] = {};
	unsigned char capdu[128] = {};
	capdu[0] = 0x00;
	capdu[1] = 0xB2;
	capdu[2] = P1;
	capdu[3] = P2;
	capdu[4] = Le;
	//ִ��apdu
	int inDataLen = 5;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"���ó���");
		return iret;
	}
	getRespErrorCodeMsg(rapdu,errorCode,errorMsg);
	strcpy(outData,rapdu);
	return 0;
}

GWI_SSSE_SC_API int EXTERNAL_AUTHENTICATION_SSSE_YH(unsigned char P2,unsigned char Lc, char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg)
{
	char rapdu[128] = {};
	unsigned char capdu[128] = {};
	capdu[0] = 0x00;
	capdu[1] = 0x82;
	capdu[2] = 0x00;
	capdu[3] = P2;
	capdu[4] = Lc;
	//ִ��apdu
	int inDataLen = strlen(inData);
	DSP_2_HEX((unsigned char*)inData,(unsigned char*)(capdu+5),inDataLen);
	inDataLen = inDataLen/2 + 5;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"���ó���");
		return iret;
	}
	getRespErrorCodeMsg(rapdu,errorCode,errorMsg);
	strcpy(outData,rapdu);
	return 0;
}

GWI_SSSE_SC_API int VERIFY_SSSE_YH(unsigned char Lc, char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg)
{
	char rapdu[128] = {};
	unsigned char capdu[128] = {};
	capdu[0] = 0x00;
	capdu[1] = 0x20;
	capdu[2] = 0x00;
	capdu[3] = 0x00;
	capdu[4] = Lc;
	//ִ��apdu
	int inDataLen = strlen(inData);
	DSP_2_HEX((unsigned char*)inData,(unsigned char*)(capdu+5),inDataLen);
	inDataLen = inDataLen/2 + 5;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"���ó���");
		return iret;
	}
	getRespErrorCodeMsg(rapdu,errorCode,errorMsg);
	strcpy(outData,rapdu);
	return 0;
}

//�����������롣�����ó��Լ��������������ĸ�������
GWI_SSSE_SC_API int UNBLOCK_SSSE_YH(unsigned char p2,unsigned char Lc,char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg)
{
	char rapdu[128] = {};
	unsigned char capdu[128] = {};
	capdu[0] = 0x84;
	capdu[1] = 0x24;
	capdu[2] = 0x00;
	capdu[3] = p2;
	capdu[4] = Lc;
	//ִ��apdu
	int inDataLen = strlen(inData);
	DSP_2_HEX((unsigned char*)inData,(unsigned char*)(capdu+5),inDataLen);
	inDataLen = inDataLen/2 + 5;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"���ó���");
		return iret;
	}
	getRespErrorCodeMsg(rapdu,errorCode,errorMsg);
	strcpy(outData,rapdu);
	return 0;
}

//��ǰ���������޸�Ϊ�µ�����
GWI_SSSE_SC_API int CHANGE_PIN_SSSE_YH(unsigned char Lc, char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg)
{
	char rapdu[128] = {};
	char cInApdu[128] = {};
	unsigned char capdu[128] = {};
	unsigned char ucIndata[128] = {};
	capdu[0] = 0x80;
	capdu[1] = 0x5E;
	capdu[2] = 0x01;
	capdu[3] = 0x00;
	capdu[4] = Lc;
	//ִ��apdu
	HEX_2_DSP((unsigned char*)capdu,(unsigned char*)cInApdu,5);
	int inDataLen = strlen(inData);
	//DSP_2_HEX((unsigned char*)inData,(unsigned char*)(cInApdu+10),inDataLen);
	strcpy(cInApdu+10,inData);
	inDataLen = inDataLen + 10;

	int iret = doApdu(cInApdu,rapdu);
	outDataLen = strlen(rapdu);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"���ó���");
		return iret;
	}
	getRespErrorCodeMsg(rapdu,errorCode,errorMsg);
	strcpy(outData,rapdu);
	return 0;
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
			char outData[LEN_1024] = {};int outDataLen = 0;char errorCode[3] = {}; char errorMsg[LEN_1024] = {};
			int iret;

			iret = SELECT_SSSE_YH(outData,outDataLen,errorCode,errorMsg);

			unsigned char FILE_SSSE_YH[] = "\xEF\x05";
			iret = SELECT_FILE_SSSE_YH(0x02,0x02,FILE_SSSE_YH,outData,outDataLen,errorCode,errorMsg);

			GET_CHALLENGE_SSSE_YH(0x08,outData,outDataLen,errorCode,errorMsg);

			INTERNAL_AUTHENTICATION_SSSE_YH(0x10,"1234567890ABCDEF1234567890ABCDEF",outData,outDataLen,errorCode,errorMsg);

			READ_RECORD_SSSE_YH(0x01,0x05,0x40,outData,outDataLen,errorCode,errorMsg);

			EXTERNAL_AUTHENTICATION_SSSE_YH(0x0A,0x10,"1234567890ABCDEF1234567890ABCDEF",outData,outDataLen,errorCode,errorMsg);

			getchar();
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