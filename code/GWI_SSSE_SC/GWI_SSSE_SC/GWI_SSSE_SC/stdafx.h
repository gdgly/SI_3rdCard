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
#include <windows.h>

#define  LOG_INFO(d)  \
	sprintf(strL,"__FILE__[%s];__LINE__[%d];__FUN__[%s];Data[%s]",__FILE__,__LINE__,__FUNCTION__,(d));\
	log_infor(__FUNCTION__,"","%s",strL);

#define  LOG_ERROR(d)\
	sprintf(strL,"__FILE__[%s];__LINE__[%d];__FUN__[%s];Data[%s]",__FILE__,__LINE__,__FUNCTION__,(d));\
	log_error(__FUNCTION__,"","%s",strL);

#define  LOG_TRACE(d)\
	sprintf(strL,"__FILE__[%s];__LINE__[%d];__FUN__[%s];Data[%s]",__FILE__,__LINE__,__FUNCTION__,(d));\
	log_trace(__FUNCTION__,"","%s",strL);

#define  LOG_DEBUG(d) \
	sprintf(strL,"__FILE__[%s];__LINE__[%d];__FUN__[%s];Data[%s]",__FILE__,__LINE__,__FUNCTION__,(d));\
	log_debug(__FUNCTION__,"","%s",strL);


// TODO: 在此处引用程序需要的其他头文件
inline void HEX_2_DSP(unsigned char *hex,unsigned char *dsp,int count)
{
	unsigned  buf[3];
	int i;
	for(i=0;i<count;i++){
		sprintf_s((char *)buf,3,"%02X",(char *)hex[i]);
		memcpy(&dsp[i*2],buf,2);
	}
	dsp[count*2]=0x0;

}

inline void DSP_2_HEX(unsigned char *dsp,unsigned char *hex,int count)
{	
	int i;
	unsigned char ch1, ch2;
	for (i = 0; i < count; i++){
		ch1 = dsp[i*2], ch2 = dsp[i*2+1];
		hex[i]=(unsigned char)((((ch1<=0x39)?ch1-0x30:(ch1&0xdf)-0x41+10)<<4)\
			|((ch2<=0x39)?ch2-0x30:(ch2&0xdf)-0x41+10));
	}
}