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


// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
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


#define IS_OPEN if (!bIsOpen){INFO("Exit:1��bIsOpen = false��");return 1;}