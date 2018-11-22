

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Jul 24 10:08:14 2018
 */
/* Compiler settings for GWI_CardRead_AdaptEx.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_GWI_CardRead_AdaptExLib,0x277D0D05,0xA21F,0x4D09,0x8C,0x14,0xC7,0x07,0xAE,0xE5,0xD8,0x12);


MIDL_DEFINE_GUID(IID, DIID__DGWI_CardRead_AdaptEx,0xB028B27E,0x8384,0x4A53,0x97,0xB9,0xC4,0xAC,0xCE,0xDD,0x99,0xBA);


MIDL_DEFINE_GUID(IID, DIID__DGWI_CardRead_AdaptExEvents,0x0366321C,0xE7BC,0x4143,0x88,0xAE,0x39,0xA8,0x1E,0x4A,0x36,0xC3);


MIDL_DEFINE_GUID(CLSID, CLSID_GWI_CardRead_AdaptEx,0x7F7313CB,0x3817,0x4AFB,0xA6,0x6A,0xE2,0x63,0x98,0x30,0x4C,0xB2);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



