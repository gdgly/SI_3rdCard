// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� GWI_SAM_ADAPT_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// GWI_SAM_ADAPT_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef GWI_SAM_ADAPT_EXPORTS
#define GWI_SAM_ADAPT_API __declspec(dllexport)
#else
#define GWI_SAM_ADAPT_API __declspec(dllimport)
#endif

// �����Ǵ� GWI_SAM_Adapt.dll ������
class GWI_SAM_ADAPT_API CGWI_SAM_Adapt {
public:
	CGWI_SAM_Adapt(void);
	// TODO: �ڴ�������ķ�����
};

/*
Ŀ�ģ��ڲ��Զ�ʵ�ֻ�ȡPSAM��������ʼ���������������ļ�ʵ��SP���û���Ӳ��DLL����
��������psamInit
���룺

�����
���أ�
0�� �ɹ�
���� ʧ��
*/
GWI_SAM_ADAPT_API int __stdcall psamInit();
/*
Ŀ�ģ��ڲ��Զ�ʵ�ֻ�ȡPSAM���ϵ����
��������psamPowerOn
���룺
int iSlotNum��������
�����
char *pchData���ϵ縴λ��Ϣ
int* iDataLen�����ݳ���
char* pchErrCode��������
char* pchError���������Ӧ�Ĵ�����Ϣ
���أ�
0�� �ɹ�
���� ʧ��
*/
GWI_SAM_ADAPT_API int __stdcall psamPowerOn(int iSlotNum, char *pchData, int* iDataLen, char* pchErrCode, char* pchError);

/*
Ŀ�ģ��ڲ��Զ�ʵ�ֻ�ȡPSAM���µ����
��������psamPowerOn
���룺
int iSlotNum��������
�����
char* pchErrCode��������
char* pchError���������Ӧ�Ĵ�����Ϣ
���أ�
0�� �ɹ�
���� ʧ��
*/
GWI_SAM_ADAPT_API int __stdcall psamPowerOff(int iSlotNum, char* pchErrCode, char* pchError);
/*
Ŀ�ģ��ڲ��Զ�ʵ�ֻ�ȡPSAM�����ݽ�������
��������psamPowerOn
���룺
int iSlotNum��������
char* pchInData������ָ��
int iInDataLen������ָ���
�����
char *pchOutData�����ָ��
int* iOutDataLen�����ָ���
char* pchErrCode��������
char* pchError���������Ӧ�Ĵ�����Ϣ
���أ�
0�� �ɹ�
���� ʧ��
*/
GWI_SAM_ADAPT_API int __stdcall psamExecCmd(int iSlot, char* pchInData, int iInDataLen, char *pchOutData, int* iOutDataLen, char *pchErrCode, char *pchError);

