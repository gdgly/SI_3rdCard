// GWI_CardRead_AdaptExPropPage.cpp : CGWI_CardRead_AdaptExPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "GWI_CardRead_AdaptEx.h"
#include "GWI_CardRead_AdaptExPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGWI_CardRead_AdaptExPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CGWI_CardRead_AdaptExPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CGWI_CardRead_AdaptExPropPage, "GWI_CARDREAD_A.GWI_CardRead_APropPage.1",
	0xe80d1a23, 0x8b2a, 0x4096, 0xb6, 0x91, 0x8d, 0x8f, 0x1d, 0xf6, 0x2e, 0xaa)



// CGWI_CardRead_AdaptExPropPage::CGWI_CardRead_AdaptExPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CGWI_CardRead_AdaptExPropPage ��ϵͳע�����

BOOL CGWI_CardRead_AdaptExPropPage::CGWI_CardRead_AdaptExPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GWI_CARDREAD_ADAPTEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGWI_CardRead_AdaptExPropPage::CGWI_CardRead_AdaptExPropPage - ���캯��

CGWI_CardRead_AdaptExPropPage::CGWI_CardRead_AdaptExPropPage() :
	COlePropertyPage(IDD, IDS_GWI_CARDREAD_ADAPTEX_PPG_CAPTION)
{
}



// CGWI_CardRead_AdaptExPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CGWI_CardRead_AdaptExPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CGWI_CardRead_AdaptExPropPage ��Ϣ�������
