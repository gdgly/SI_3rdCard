

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Nov 22 10:27:32 2018
 */
/* Compiler settings for SSCARD.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_SSCARDLib,0x6CA09989,0xD8DC,0x4679,0xBE,0x5B,0xFA,0x31,0x00,0x8A,0x30,0xAE);


MIDL_DEFINE_GUID(IID, DIID__DSSCARD,0x7E4FB4C8,0x0B4B,0x4D7F,0xA4,0x17,0x7B,0x7D,0xEB,0xDC,0xF3,0x91);


MIDL_DEFINE_GUID(IID, DIID__DSSCARDEvents,0x9F6CBFA1,0x1839,0x4733,0x89,0x00,0x11,0x64,0x0A,0xCC,0x21,0xDD);


MIDL_DEFINE_GUID(CLSID, CLSID_SSCARD,0xB2167F16,0xE8B0,0x4D84,0x80,0x2E,0x3C,0x7F,0x34,0xAA,0x28,0x73);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



