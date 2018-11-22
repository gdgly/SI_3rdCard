// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
#include <afx.h>
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
#endif


#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>
// Windows ͷ�ļ�:
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


// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
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