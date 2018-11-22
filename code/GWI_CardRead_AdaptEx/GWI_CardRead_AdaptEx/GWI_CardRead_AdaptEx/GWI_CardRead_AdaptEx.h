#pragma once

// GWI_CardRead_AdaptEx.h : GWI_CardRead_AdaptEx.DLL 的主头文件

#if !defined( __AFXCTL_H__ )
#error "在包括此文件之前包括“afxctl.h”"
#endif

#include "resource.h"       // 主符号


// CGWI_CardRead_AdaptExApp : 有关实现的信息，请参阅 GWI_CardRead_AdaptEx.cpp。

class CGWI_CardRead_AdaptExApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

