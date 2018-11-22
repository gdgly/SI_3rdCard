// SSCARDPropPage.cpp : CSSCARDPropPage 属性页类的实现。

#include "stdafx.h"
#include "SSCARD.h"
#include "SSCARDPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CSSCARDPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CSSCARDPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CSSCARDPropPage, "SSCARD.SSCARDPropPage.1",
	0xf18c019e, 0x45c, 0x4bb6, 0xbb, 0x92, 0xc3, 0x3, 0x3d, 0x67, 0x95, 0x10)



// CSSCARDPropPage::CSSCARDPropPageFactory::UpdateRegistry -
// 添加或移除 CSSCARDPropPage 的系统注册表项

BOOL CSSCARDPropPage::CSSCARDPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SSCARD_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CSSCARDPropPage::CSSCARDPropPage - 构造函数

CSSCARDPropPage::CSSCARDPropPage() :
	COlePropertyPage(IDD, IDS_SSCARD_PPG_CAPTION)
{
}



// CSSCARDPropPage::DoDataExchange - 在页和属性间移动数据

void CSSCARDPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CSSCARDPropPage 消息处理程序
