#pragma once

// GWI_CardRead_AdaptExPropPage.h : CGWI_CardRead_AdaptExPropPage ����ҳ���������


// CGWI_CardRead_AdaptExPropPage : �й�ʵ�ֵ���Ϣ������� GWI_CardRead_AdaptExPropPage.cpp��

class CGWI_CardRead_AdaptExPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGWI_CardRead_AdaptExPropPage)
	DECLARE_OLECREATE_EX(CGWI_CardRead_AdaptExPropPage)

// ���캯��
public:
	CGWI_CardRead_AdaptExPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_GWI_CARDREAD_ADAPTEX };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

