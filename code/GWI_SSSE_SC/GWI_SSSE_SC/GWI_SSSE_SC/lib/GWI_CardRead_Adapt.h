#pragma  once
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� GWI_CARDREAD_ADAPT_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// GWI_CARDREAD_ADAPT_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef GWI_CARDREAD_ADAPT_EXPORTS
#define GWI_CARDREAD_ADAPT_API __declspec(dllexport)
#else
#define GWI_CARDREAD_ADAPT_API __declspec(dllimport)
#endif

extern "C"
{

	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ֶ�ȡ�����ļ�ʵ����ֱ�ӵ�Ӳ��DLL ����SP���м��DLL
	��������Init
	���룺
	
	�����

	���أ�
	0 �ɹ�
	���� ʧ��
	*/

	GWI_CARDREAD_ADAPT_API int __stdcall Init();
	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ֿ�Ƭ�ϵ� �����ڲ�ҵ���߼���������ж���IDC����IC2
	��������PowerOn_EX
	���룺
	int iType ��Ƭ�ϵ����� 1-�Ӵ�ʽ��������2-�ǽӴ�ʽ��������3-�Զ�Ѱ�����Ӵ�ʽ���������ȣ�4-�Զ�Ѱ�����ǽӴ�ʽ����������
	long lTimeout ��ʱʱ�� ��λ����
	�����
	char* csAtr  �ϵ���Ϣ
	���أ�
	0 �ɹ�
	���� ʧ��
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall PowerOn_EX(IN INT iType, IN LONG lTimeout, OUT LPSTR csAtr);

	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ֿ�Ƭ�µ� ��PowerOn_EX��Ӧִ��
	��������PowerOFF_EX
	���룺
	�����
	���أ�
	0 �ɹ�
	���� ʧ��
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall PowerOFF_EX();

	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ֿ�Ƭ���ݽ��� ��PowerOn_EX��Ӧִ��
	��������ChipIO_EX
	���룺
	LPCSTR szDataIn��ָ����������
	DWORD iLenIn��ָ���
	�����
	LPSTR  lpszDataOut��ָ���Ӧ����
	DWORD &iLenOut����Ӧ���ݳ���
	���أ�
	0 �ɹ�
	���� ʧ��
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall ChipIO_EX(IN LPCSTR szDataIn, IN DWORD iLenIn, OUT  LPSTR  lpszDataOut,OUT DWORD &iLenOut);

	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ִ�Ӳ�� ������ ��λ �� ״̬���
	��������Open_EX
	���룺
	�����
	���أ�
	1�� IDC�򿪳ɹ�  2��IC2�򿪳ɹ� 3��IDC��IC2�򿪳ɹ�
	���� ʧ��
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall Open_EX();

	/*
	Ŀ�ģ��ڲ��Զ�ʵ��Ӳ���ر� �Զ�ʵ�ֹر��˿� ֹͣǰ�˽�����
	��������Close_EX
	���룺
	�����
	���أ�
	1�� IDC�رճɹ�  2��IC2�رճɹ� 3��IDC��IC2�رճɹ�
	���� ʧ��
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall Close_EX();

	/*
	Ŀ�ģ��ڲ��Զ���λ
	��������ResetDevice
	���룺
	�����
	���أ�
	0�� �ɹ�
	���� ʧ��
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall ResetDevice();
	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ֶ�2�ź�3��
	��������ReadCardTracks
	���룺
	int  itimeout����ʱʱ��
	�����
	char* pchTrackData2��2�ŵ�����
	char* pchTrackData3��3�ŵ�����
	���أ�
	0�� �ɹ�
	���� ʧ��
	*/
	GWI_CARDREAD_ADAPT_API  int __stdcall ReadCardTracks (char* pchTrackData2, char* pchTrackData3, int  itimeout);

	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ֻ�ȡ�豸״̬
	��������GetDeviceStatus
	���룺
	
	�����
	int* pDevstatus��״̬
	���أ�
	0�� �ɹ�
	���� ʧ��
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall GetDeviceStatus( int* pDevstatus);

	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ֻ�ȡ��Ƭ״̬
	��������GetMediaStatus
	���룺
	
	�����
	int*  pMediastatus��״̬
	���أ�
	0�� �ɹ�
	���� ʧ��
	*/
	GWI_CARDREAD_ADAPT_API int __stdcall GetMediaStatus(int*  pMediastatus);
};