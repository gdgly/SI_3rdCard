#pragma once

// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��
#define _ATL_NO_AUTOMATIC_NAMESPACE             // ���������Ƴ�ͻ

#include <afxctl.h>         // ActiveX �ؼ��� MFC ֧��
#include <afxext.h>         // MFC ��չ
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

// �����ϣ��ʹ�� MFC ���ݿ��࣬
//  ��ɾ����������������ļ�
#ifndef _WIN64

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#endif // _WIN64

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

#define VALIAD_SW1_SW2(errorCode) \
if (((errorCode)[0]&0xFF)!= 0x90 || ((errorCode)[1]&0xFF)!= 0x00)\
{\
	iret = getRetMsgBySw1Sw2(((errorCode)[0]&0xFF),((errorCode)[1]&0xFF),msg);\
	m_pOutInfo = msg;\
	sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",((errorCode)[0]&0xFF),((errorCode)[1]&0xFF),msg);\
	LOG_DEBUG(log_msg);\
	sprintf(log_msg,"iret[%d]",iret);\
	LOG_INFO(log_msg);\
	bIsRunCardReadOpen = false;\
	PowerOFF_EX();\
	return iret;\
}

#define VALIAD_SW1_SW2_NO_OFF(errorCode) \
	if (((errorCode)[0]&0xFF)!= 0x90 || ((errorCode)[1]&0xFF)!= 0x00)\
{\
	iret = getRetMsgBySw1Sw2(((errorCode)[0]&0xFF),((errorCode)[1]&0xFF),msg);\
	m_pOutInfo = msg;\
	sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",((errorCode)[0]&0xFF),((errorCode)[1]&0xFF),msg);\
	LOG_DEBUG(log_msg);\
	sprintf(log_msg,"iret[%d]",iret);\
	LOG_INFO(log_msg);\
	bIsRunCardReadOpen = false;\
	PowerOFF_EX();\
	return iret;\
}

#define VALIAD_RET(iret)\
	if (0!=(iret))\
	{\
		(iret) = getRetMsgBySw1Sw2(0xFF,0x21,msg);\
		m_pOutInfo = msg;\
		sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x21,msg);\
		LOG_DEBUG(log_msg);\
		sprintf(log_msg,"iret[%d]",iret);\
		LOG_INFO(log_msg);\
		bIsRunCardReadOpen = false;\
		PowerOFF_EX();\
		return (iret);\
	}

#define VALIAD_RET_NO_OFF(iret)\
	if (0!=(iret))\
{\
	(iret) = getRetMsgBySw1Sw2(0xFF,0x21,msg);\
	m_pOutInfo = msg;\
	sprintf(log_msg,"sw1[%X];sw2[%X];msg[%s]",0xFF,0x21,msg);\
	LOG_DEBUG(log_msg);\
	sprintf(log_msg,"iret[%d]",iret);\
	LOG_INFO(log_msg);\
	bIsRunCardReadOpen = false;\
	PowerOFF_EX();\
	return (iret);\
}
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