// SSCARDPropPage.cpp : CSSCARDPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "SSCARD.h"
#include "SSCARDPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CSSCARDPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CSSCARDPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CSSCARDPropPage, "SSCARD.SSCARDPropPage.1",
	0xf18c019e, 0x45c, 0x4bb6, 0xbb, 0x92, 0xc3, 0x3, 0x3d, 0x67, 0x95, 0x10)



// CSSCARDPropPage::CSSCARDPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CSSCARDPropPage ��ϵͳע�����

BOOL CSSCARDPropPage::CSSCARDPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SSCARD_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CSSCARDPropPage::CSSCARDPropPage - ���캯��

CSSCARDPropPage::CSSCARDPropPage() :
	COlePropertyPage(IDD, IDS_SSCARD_PPG_CAPTION)
{
}



// CSSCARDPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CSSCARDPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CSSCARDPropPage ��Ϣ�������
