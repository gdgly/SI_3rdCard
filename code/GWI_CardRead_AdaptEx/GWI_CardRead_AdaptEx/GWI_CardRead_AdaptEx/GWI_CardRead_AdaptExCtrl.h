#pragma once

// GWI_CardRead_AdaptExCtrl.h : CGWI_CardRead_AdaptExCtrl ActiveX �ؼ����������


// CGWI_CardRead_AdaptExCtrl : �й�ʵ�ֵ���Ϣ������� GWI_CardRead_AdaptExCtrl.cpp��

class CGWI_CardRead_AdaptExCtrl : public COleControl
{
	DECLARE_DYNCREATE(CGWI_CardRead_AdaptExCtrl)

// ���캯��
public:
	CGWI_CardRead_AdaptExCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CGWI_CardRead_AdaptExCtrl();

	DECLARE_OLECREATE_EX(CGWI_CardRead_AdaptExCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CGWI_CardRead_AdaptExCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CGWI_CardRead_AdaptExCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CGWI_CardRead_AdaptExCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		dispidocx_GetSN = 11L,
		dispidocx_GetMediaStatus = 10L,
		dispidocx_GetDeviceStatus = 9L,
		dispidocx_ReadCardTracks = 8L,
		dispidocx_ResetDevice = 7L,
		dispidocx_Close_EX = 6L,
		dispidocx_Open_EX = 5L,
		dispidocx_ChipIO_EX = 4L,
		dispidocx_PowerOFF_EX = 3L,
		dispidocx_PowerOn_EX = 2L,
		dispidocx_Init = 1L
	};
protected:
	/*
	Ŀ�ģ���ʼ��ͨ���������ļ���ʵ��SP���û���Ӳ����̬�����
	��������ocx_Init
	���룺
	
	�����
	
	���أ�
	0�� �ɹ�
	���� ʧ��
	*/
	LONG ocx_Init(void);
	/*
	Ŀ�ģ���DLLʵ���ϵ����
	��������ocx_PowerOn_EX
	���룺
	LONG iType���ϵ����� 1-�Ӵ�ʽ��������2-�ǽӴ�ʽ��������3-�Զ�Ѱ�����Ӵ�ʽ���������ȣ�4-�Զ�Ѱ�����ǽӴ�ʽ����������
	LONG lTimeout����ʱʱ�� ��λ����)
	�����

	���أ�
	BSTR���ϵ縴λ��Ϣ
	*/
	BSTR ocx_PowerOn_EX(LONG iType, LONG lTimeout);
	/*
	Ŀ�ģ��ڲ��Զ��µ磬�綯ʽ��������Ҫ���˽ӿ��¿����ߵ���λ�¿�
	��������ocx_PowerOFF_EX
	���룺
	
	�����

	���أ�
	0�� �ɹ�
	���� ʧ��
	*/
	LONG ocx_PowerOFF_EX(void);
	/*
	Ŀ�ģ��ڲ��Զ�ʵ��оƬ�������֮���ָ���
	��������ocx_ChipIO_EX
	���룺
	LPCTSTR szDataIn������ָ��
	LONG iLenIn������ָ���
	�����
	���أ�
	BSTR��iLenOut^lpszDataOut ָ���^����ָ��
	*/
	BSTR ocx_ChipIO_EX(LPCTSTR szDataIn, LONG iLenIn);
	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ִ��豸
	��������ocx_Open_EX
	���룺
	
	�����
	
	���أ�
	0�� �ɹ�
	���� ʧ��
	*/
	LONG ocx_Open_EX(void);
	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ֹر��豸���᲻���Զ��¿��̿�ȡ����Ӳ����SP�رսӿڣ��ϲ�͸������
	��������ocx_Close_EX
	���룺
	
	�����

	���أ�
	0�� �ɹ�
	���� ʧ��
	*/
	LONG ocx_Close_EX(void);
	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ָ�λ�������綯���������¿�
	��������ocx_ResetDevice
	���룺
	
	�����
	
	���أ�
	0�� �ɹ�
	���� ʧ��
	*/
	LONG ocx_ResetDevice(void);
	/*
	Ŀ�ģ��ڲ��Զ����ŵ�����
	��������ocx_ReadCardTracks
	���룺
	LONG itimeout����ʱʱ�� ��λ���룩
	�����
	
	���أ�
	BSTR��pchTrackData2^pchTrackData3^ ���ŵ�^���ŵ�^
	*/
	BSTR ocx_ReadCardTracks(LONG itimeout);
	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ֻ�ȡ�豸״̬
	��������ocx_GetDeviceStatus
	���룺
	
	�����
	���أ�
	0���豸����(����)
	1���豸æ
	2���豸����
	3���豸����
	-1�����ó���
	*/
	BSTR ocx_GetDeviceStatus(void);
	/*
	Ŀ�ģ��ڲ��Զ�ʵ�ֻ�ȡ��Ƭ״̬
	��������ocx_GetMediaStatus
	���룺
	
	�����
	
	���أ�
	0���豸����(����)
	1���豸æ
	2���豸����
	3���豸����
	-1�����ó���
	*/
	BSTR ocx_GetMediaStatus(void);
	BSTR ocx_GetSN(void);
};

