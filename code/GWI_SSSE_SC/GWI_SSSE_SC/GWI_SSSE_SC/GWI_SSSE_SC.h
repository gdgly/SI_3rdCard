// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 GWI_SSSE_SC_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// GWI_SSSE_SC_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef GWI_SSSE_SC_EXPORTS
#define GWI_SSSE_SC_API __declspec(dllexport)
#else
#define GWI_SSSE_SC_API __declspec(dllimport)
#endif

#include "lib/GWI_CardRead_Adapt.h"
#pragma  comment(lib, "lib/GWI_CardRead_Adapt.lib")
// 此类是从 GWI_SSSE_SC.dll 导出的
class GWI_SSSE_SC_API CGWI_SSSE_SC {
public:
	CGWI_SSSE_SC(void);
	// TODO: 在此添加您的方法。
};
 

typedef struct _ResponseError
{
	char sw1;
	char sw2;
	char* msg;
}m_ResponseError,*p_ResponseError;



int doApdu(const char* in, char* out);

int doExchange(char* inData,int inDataLen,char* outData,int& outDataLen);
/*
目的：实现社保卡的SELECT指令，文件选择
输入：
char* inData：输入指令
int inDataLen：输入指令长度
输出：
char* outData：输出指令
int& outDataLen：输出指令长度
返回：
0：成功
其它：失败
*/
int doExchange(char* inData,int inDataLen,char* outData,int& outDataLen);


/*
目的：实现社保卡的SELECT指令，文件选择
输入：

输出：
char* outData：输出指令
int& outDataLen：输出指令长度
char* errorCode：指令后2字节数据
char* errorMsg：指令后2字节数据对应的解析
返回：
0：成功
其它：失败
*/
GWI_SSSE_SC_API int SELECT_SSSE_YH(char* outData,int& outDataLen,char* errorCode, char* errorMsg);

GWI_SSSE_SC_API int SELECT_FILE_SSSE_YH(unsigned char P1, unsigned char Lc, unsigned char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg);

GWI_SSSE_SC_API int GET_CHALLENGE_SSSE_YH(unsigned char Le,char* outData,int& outDataLen,char* errorCode, char* errorMsg);

GWI_SSSE_SC_API int INTERNAL_AUTHENTICATION_SSSE_YH(unsigned char Lc, char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg);

GWI_SSSE_SC_API int READ_RECORD_SSSE_YH(unsigned char P1, unsigned char P2, unsigned char Le, char* outData,int& outDataLen,char* errorCode, char* errorMsg);

GWI_SSSE_SC_API int EXTERNAL_AUTHENTICATION_SSSE_YH(unsigned char P2,unsigned char Lc, char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg);

GWI_SSSE_SC_API int VERIFY_SSSE_YH(unsigned char Lc, char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg);

GWI_SSSE_SC_API int UNBLOCK_SSSE_YH(unsigned char p2,unsigned char Lc,char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg);

GWI_SSSE_SC_API int CHANGE_PIN_SSSE_YH(unsigned char Lc, char* inData, char* outData,int& outDataLen,char* errorCode, char* errorMsg);