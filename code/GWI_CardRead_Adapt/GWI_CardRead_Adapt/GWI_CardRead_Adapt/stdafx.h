// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#include <afx.h>
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            //  从 Windows 头文件中排除极少使用的信息
#endif

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>
// Windows 头文件:


// TODO: 在此处引用程序需要的其他头文件
#define  INFO(d)  \
sprintf(strL,"__THREAD__[%d];__FILE__[%s];__LINE__[%d];__FUN__[%s];Data[%s]",GetCurrentThreadId(),__FILE__,__LINE__,__FUNCTION__,(d));\
log_infor(__FUNCTION__,"","%s",strL);

#define  ERROR(d)\
sprintf(strL,"__THREAD__[%d];__FILE__[%s];__LINE__[%d];__FUN__[%s];Data[%s]",GetCurrentThreadId(),__FILE__,__LINE__,__FUNCTION__,(d));\
log_error(__FUNCTION__,"","%s",strL);

#define  TRACE(d)\
sprintf(strL,"__THREAD__[%d];__FILE__[%s];__LINE__[%d];__FUN__[%s];Data[%s]",GetCurrentThreadId(),__FILE__,__LINE__,__FUNCTION__,(d));\
log_trace(__FUNCTION__,"","%s",strL);

#define  DEBUG(d) \
sprintf(strL,"__THREAD__[%d];__FILE__[%s];__LINE__[%d];__FUN__[%s];Data[%s]",GetCurrentThreadId(),__FILE__,__LINE__,__FUNCTION__,(d));\
log_debug(__FUNCTION__,"","%s",strL);


#define IS_OPEN if (!bIsOpen){INFO("Exit:1【bIsOpen = false】");return 1;}