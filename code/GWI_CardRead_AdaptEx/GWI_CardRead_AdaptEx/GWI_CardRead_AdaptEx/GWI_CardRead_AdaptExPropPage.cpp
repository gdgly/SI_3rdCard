// GWI_CardRead_AdaptExPropPage.cpp : CGWI_CardRead_AdaptExPropPage 属性页类的实现。

#include "stdafx.h"
#include "GWI_CardRead_AdaptEx.h"
#include "GWI_CardRead_AdaptExPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CGWI_CardRead_AdaptExPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CGWI_CardRead_AdaptExPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CGWI_CardRead_AdaptExPropPage, "GWI_CARDREAD_A.GWI_CardRead_APropPage.1",
	0xe80d1a23, 0x8b2a, 0x4096, 0xb6, 0x91, 0x8d, 0x8f, 0x1d, 0xf6, 0x2e, 0xaa)



// CGWI_CardRead_AdaptExPropPage::CGWI_CardRead_AdaptExPropPageFactory::UpdateRegistry -
// 添加或移除 CGWI_CardRead_AdaptExPropPage 的系统注册表项

BOOL CGWI_CardRead_AdaptExPropPage::CGWI_CardRead_AdaptExPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_GWI_CARDREAD_ADAPTEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CGWI_CardRead_AdaptExPropPage::CGWI_CardRead_AdaptExPropPage - 构造函数

CGWI_CardRead_AdaptExPropPage::CGWI_CardRead_AdaptExPropPage() :
	COlePropertyPage(IDD, IDS_GWI_CARDREAD_ADAPTEX_PPG_CAPTION)
{
}



// CGWI_CardRead_AdaptExPropPage::DoDataExchange - 在页和属性间移动数据

void CGWI_CardRead_AdaptExPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CGWI_CardRead_AdaptExPropPage 消息处理程序
