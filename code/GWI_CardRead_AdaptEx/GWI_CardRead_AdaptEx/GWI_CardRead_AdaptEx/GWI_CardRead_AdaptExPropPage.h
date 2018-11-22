#pragma once

// GWI_CardRead_AdaptExPropPage.h : CGWI_CardRead_AdaptExPropPage 属性页类的声明。


// CGWI_CardRead_AdaptExPropPage : 有关实现的信息，请参阅 GWI_CardRead_AdaptExPropPage.cpp。

class CGWI_CardRead_AdaptExPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CGWI_CardRead_AdaptExPropPage)
	DECLARE_OLECREATE_EX(CGWI_CardRead_AdaptExPropPage)

// 构造函数
public:
	CGWI_CardRead_AdaptExPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_GWI_CARDREAD_ADAPTEX };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

