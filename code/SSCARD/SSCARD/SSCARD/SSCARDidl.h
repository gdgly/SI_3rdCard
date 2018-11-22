

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __SSCARDidl_h__
#define __SSCARDidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DSSCARD_FWD_DEFINED__
#define ___DSSCARD_FWD_DEFINED__
typedef interface _DSSCARD _DSSCARD;
#endif 	/* ___DSSCARD_FWD_DEFINED__ */


#ifndef ___DSSCARDEvents_FWD_DEFINED__
#define ___DSSCARDEvents_FWD_DEFINED__
typedef interface _DSSCARDEvents _DSSCARDEvents;
#endif 	/* ___DSSCARDEvents_FWD_DEFINED__ */


#ifndef __SSCARD_FWD_DEFINED__
#define __SSCARD_FWD_DEFINED__

#ifdef __cplusplus
typedef class SSCARD SSCARD;
#else
typedef struct SSCARD SSCARD;
#endif /* __cplusplus */

#endif 	/* __SSCARD_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __SSCARDLib_LIBRARY_DEFINED__
#define __SSCARDLib_LIBRARY_DEFINED__

/* library SSCARDLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_SSCARDLib;

#ifndef ___DSSCARD_DISPINTERFACE_DEFINED__
#define ___DSSCARD_DISPINTERFACE_DEFINED__

/* dispinterface _DSSCARD */
/* [uuid] */ 


EXTERN_C const IID DIID__DSSCARD;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7E4FB4C8-0B4B-4D7F-A417-7B7DEBDCF391")
    _DSSCARD : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSSCARDVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSSCARD * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSSCARD * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSSCARD * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSSCARD * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSSCARD * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSSCARD * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSSCARD * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DSSCARDVtbl;

    interface _DSSCARD
    {
        CONST_VTBL struct _DSSCARDVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSSCARD_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSSCARD_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSSCARD_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSSCARD_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSSCARD_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSSCARD_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSSCARD_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSSCARD_DISPINTERFACE_DEFINED__ */


#ifndef ___DSSCARDEvents_DISPINTERFACE_DEFINED__
#define ___DSSCARDEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DSSCARDEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DSSCARDEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("9F6CBFA1-1839-4733-8900-11640ACC21DD")
    _DSSCARDEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSSCARDEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSSCARDEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSSCARDEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSSCARDEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSSCARDEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSSCARDEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSSCARDEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSSCARDEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DSSCARDEventsVtbl;

    interface _DSSCARDEvents
    {
        CONST_VTBL struct _DSSCARDEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSSCARDEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSSCARDEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSSCARDEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSSCARDEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSSCARDEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSSCARDEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSSCARDEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSSCARDEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SSCARD;

#ifdef __cplusplus

class DECLSPEC_UUID("B2167F16-E8B0-4D84-802E-3C7F34AA2873")
SSCARD;
#endif
#endif /* __SSCARDLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


