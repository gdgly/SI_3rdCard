// GWI_SSSE_SC.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "GWI_SSSE_SC.h"
#include "log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

#define  LEN_1024 1024
char strL[LEN_1024];

_ResponseError respError[] = {
	{0x90,0x00,"执行成功"},
	{0x63,0xC0,"鉴别失败， 允许继续尝试的次数"},
	{0x65,0x81,"内存错误"},
	{0x67,0x00,"P1、 P2 与 Lc 不一致"},
	{0x69,0x81,"命令与文件结构不相容"},
	{0x69,0x82,"不满足安全状态"},
	{0x69,0x83,"验证方法锁定"},
	{0x69,0x84,"引用数据无效"},
	{0x69,0x85,"不满足使用条件"},
	{0x69,0x86,"命令不允许使用（无当前基本文件）"},
	{0x69,0x88,"安全报文数据项不正确"},
	{0x6A,0x80,"数据域参数不正确"},
	{0x6A,0x81,"功能不被支持"},
	{0x6A,0x82,"未找到文件"},
	{0x6A,0x83,"未找到记录"},
	{0x6A,0x86,"参数 P1、 P2 不正确"},
	{0x6A,0x88,"密钥未找到"},
	{0x6C,0x00,"长度错误（ Le 错误）"},
	{0x6E,0x00,"CLA 错"},
	{0x93,0x03,"应用被永久锁定"},
	{0x00,0x00,"获取SW1和SW2失败"}
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
		sprintf(errorMsg,"长度错误（ Le 错误）长度为：%d",(int)sw2);
		return;
	}
	if (0x63 ==  sw1)
	{
		sprintf(errorMsg,"鉴别失败， 允许继续尝试的次数%d",(int)(sw2&0x0F));
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
	sprintf(errorMsg,"%s","未知错误");
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
	/* 桩数据
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
	//执行apdu
	int inDataLen = 20;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"调用出错");
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
	//执行apdu
	inDataLen+=5;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"调用出错");
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
	
	//执行apdu
	int inDataLen = 5;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"调用出错");
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

	//执行apdu
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
		strcpy(errorMsg,"调用出错");
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
	//执行apdu
	int inDataLen = 5;
	outDataLen = 0;
	int iret = doExchange(capdu,inDataLen,rapdu,outDataLen);
	if (0!=iret)
	{
		strcpy(outData,"");
		outDataLen = 0;
		strcpy(errorCode,"");
		strcpy(errorMsg,"调用出错");
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
	//执行apdu
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
		strcpy(errorMsg,"调用出错");
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
	//执行apdu
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
		strcpy(errorMsg,"调用出错");
		return iret;
	}
	getRespErrorCodeMsg(rapdu,errorCode,errorMsg);
	strcpy(outData,rapdu);
	return 0;
}

//解锁个人密码。仅重置尝试计数器，并不更改个人密码
GWI_SSSE_SC_API int UNBLOCK_SSSE_YH(unsigned char p2,unsigned char Lc,char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg)
{
	char rapdu[128] = {};
	unsigned char capdu[128] = {};
	capdu[0] = 0x84;
	capdu[1] = 0x24;
	capdu[2] = 0x00;
	capdu[3] = p2;
	capdu[4] = Lc;
	//执行apdu
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
		strcpy(errorMsg,"调用出错");
		return iret;
	}
	getRespErrorCodeMsg(rapdu,errorCode,errorMsg);
	strcpy(outData,rapdu);
	return 0;
}

//当前个人密码修改为新的密码
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
	//执行apdu
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
		strcpy(errorMsg,"调用出错");
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
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。
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
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
*/