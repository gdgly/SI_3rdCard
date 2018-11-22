// GWI_SSSE_SC_TEST.cpp: 主项目文件。

#include "stdafx.h"

using namespace System;
#include "../Debug/GWI_SSSE_SC.h"
#pragma  comment(lib, "../Debug/GWI_SSSE_SC.lib")
int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");
#define LEN_1024 1024
	char outData[LEN_1024] = {};int outDataLen = 0;char errorCode[3] = {}; char errorMsg[LEN_1024] = {};
	int iret;

	iret = SELECT_SSSE_YH(outData,outDataLen,errorCode,errorMsg);

	unsigned char FILE_SSSE_YH[] = "\xEF\x05";
	iret = SELECT_FILE_SSSE_YH(0x02,0x02,FILE_SSSE_YH,outData,outDataLen,errorCode,errorMsg);

	GET_CHALLENGE_SSSE_YH(0x08,outData,outDataLen,errorCode,errorMsg);

	INTERNAL_AUTHENTICATION_SSSE_YH(0x10,"1234567890ABCDEF1234567890ABCDEF",outData,outDataLen,errorCode,errorMsg);

	READ_RECORD_SSSE_YH(0x01,0x05,0x40,outData,outDataLen,errorCode,errorMsg);

	EXTERNAL_AUTHENTICATION_SSSE_YH(0x0A,0x10,"1234567890ABCDEF1234567890ABCDEF",outData,outDataLen,errorCode,errorMsg);

	//getchar();
    return 0;
}
