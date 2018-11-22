#pragma once

// SSCARDPropPage.h : CSSCARDPropPage 属性页类的声明。


// CSSCARDPropPage : 有关实现的信息，请参阅 SSCARDPropPage.cpp。

class CSSCARDPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSSCARDPropPage)
	DECLARE_OLECREATE_EX(CSSCARDPropPage)

// 构造函数
public:
	CSSCARDPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_SSCARD };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

