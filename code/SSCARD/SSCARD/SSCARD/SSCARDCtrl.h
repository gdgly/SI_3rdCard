#pragma once

// SSCARDCtrl.h : CSSCARDCtrl ActiveX �ؼ����������

#define  LEN_1024 1024
#define  MEMSET_APDU \
	memset(outData,0x00,sizeof(outData));\
	memset(errorCode,0x00,sizeof(errorCode));\
	memset(errorMsg,0x00,sizeof(errorMsg));

// CSSCARDCtrl : �й�ʵ�ֵ���Ϣ������� SSCARDCtrl.cpp��

class CSSCARDCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSSCARDCtrl)

// ���캯��
public:
	CSSCARDCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CSSCARDCtrl();

	DECLARE_OLECREATE_EX(CSSCARDCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CSSCARDCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSSCARDCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CSSCARDCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		dispidiReloadPIN_HSM_Step3 = 14L,
		dispidiReloadPIN_HSM_Step2 = 13L,
		dispidiReloadPIN_HSM_Step1 = 12L,
		dispidiReloadPIN = 11L,
		dispidiChangePIN = 10L,
		dispidiVerifyPIN = 9L,
		dispidocxOpenDevice = 8L,
		dispidocxCloseDevice = 7L,
		dispidocxEjectCard = 6L,
		dispidocxReadTrack = 5L,
		dispidReadCardTracks = 5L,
		dispidiReadCardBas_HSM_Step2 = 4L,
		dispidiReadCardBas_HSM_Step1 = 3L,
		dispidpOutInfo = 2,
		dispidiReadCardBas = 1L
	};
protected:
	LONG iReadCardBas(LONG iType);
	void OnpOutInfoChanged(void);
	CString m_pOutInfo;
	LONG iReadCardBas_HSM_Step1(LONG iType);
	LONG iReadCardBas_HSM_Step2(LPCTSTR pKey);
	BSTR ocxReadTrack(LONG lTimeout);
	LONG ocxEjectCard(void);
	ULONG ocxCloseDevice(void);
	LONG ocxOpenDevice(void);
	LONG iVerifyPIN(LONG iType, LPCTSTR pin);
	LONG iChangePIN(LONG iType, LPCTSTR oldPin, LPCTSTR newPin);
	LONG iReloadPIN(LONG iType, LPCTSTR pCardInfo);
	LONG iReloadPIN_HSM_Step1(LONG iType, LPCTSTR pCardInfo);
	LONG iReloadPIN_HSM_Step2(LPCTSTR pKey, LPCTSTR newPin);
	LONG iReloadPIN_HSM_Step3(LPCTSTR pKey);
};


typedef struct _ReturnMap
{
	int ret;
	char* msg;
	char sw1;
	char sw2;
}m_ReturnMap,*p_ReturnMap;

typedef struct _KLV
{
	char k[32];
	int l;
	char v[MAX_PATH];
}m_KLV,*p_KLV;