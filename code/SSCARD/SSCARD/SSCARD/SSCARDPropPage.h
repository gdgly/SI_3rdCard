#pragma once

// SSCARDPropPage.h : CSSCARDPropPage ����ҳ���������


// CSSCARDPropPage : �й�ʵ�ֵ���Ϣ������� SSCARDPropPage.cpp��

class CSSCARDPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSSCARDPropPage)
	DECLARE_OLECREATE_EX(CSSCARDPropPage)

// ���캯��
public:
	CSSCARDPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_SSCARD };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

