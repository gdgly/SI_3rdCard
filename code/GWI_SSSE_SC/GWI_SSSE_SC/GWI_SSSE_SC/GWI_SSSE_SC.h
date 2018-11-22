// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� GWI_SSSE_SC_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// GWI_SSSE_SC_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef GWI_SSSE_SC_EXPORTS
#define GWI_SSSE_SC_API __declspec(dllexport)
#else
#define GWI_SSSE_SC_API __declspec(dllimport)
#endif

#include "lib/GWI_CardRead_Adapt.h"
#pragma  comment(lib, "lib/GWI_CardRead_Adapt.lib")
// �����Ǵ� GWI_SSSE_SC.dll ������
class GWI_SSSE_SC_API CGWI_SSSE_SC {
public:
	CGWI_SSSE_SC(void);
	// TODO: �ڴ�������ķ�����
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
Ŀ�ģ�ʵ���籣����SELECTָ��ļ�ѡ��
���룺
char* inData������ָ��
int inDataLen������ָ���
�����
char* outData�����ָ��
int& outDataLen�����ָ���
���أ�
0���ɹ�
������ʧ��
*/
int doExchange(char* inData,int inDataLen,char* outData,int& outDataLen);


/*
Ŀ�ģ�ʵ���籣����SELECTָ��ļ�ѡ��
���룺

�����
char* outData�����ָ��
int& outDataLen�����ָ���
char* errorCode��ָ���2�ֽ�����
char* errorMsg��ָ���2�ֽ����ݶ�Ӧ�Ľ���
���أ�
0���ɹ�
������ʧ��
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