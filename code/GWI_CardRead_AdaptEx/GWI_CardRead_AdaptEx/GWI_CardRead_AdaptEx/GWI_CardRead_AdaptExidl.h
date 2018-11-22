

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __GWI_CardRead_AdaptExidl_h__
#define __GWI_CardRead_AdaptExidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DGWI_CardRead_AdaptEx_FWD_DEFINED__
#define ___DGWI_CardRead_AdaptEx_FWD_DEFINED__
typedef interface _DGWI_CardRead_AdaptEx _DGWI_CardRead_AdaptEx;
#endif 	/* ___DGWI_CardRead_AdaptEx_FWD_DEFINED__ */


#ifndef ___DGWI_CardRead_AdaptExEvents_FWD_DEFINED__
#define ___DGWI_CardRead_AdaptExEvents_FWD_DEFINED__
typedef interface _DGWI_CardRead_AdaptExEvents _DGWI_CardRead_AdaptExEvents;
#endif 	/* ___DGWI_CardRead_AdaptExEvents_FWD_DEFINED__ */


#ifndef __GWI_CardRead_AdaptEx_FWD_DEFINED__
#define __GWI_CardRead_AdaptEx_FWD_DEFINED__

#ifdef __cplusplus
typedef class GWI_CardRead_AdaptEx GWI_CardRead_AdaptEx;
#else
typedef struct GWI_CardRead_AdaptEx GWI_CardRead_AdaptEx;
#endif /* __cplusplus */

#endif 	/* __GWI_CardRead_AdaptEx_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __GWI_CardRead_AdaptExLib_LIBRARY_DEFINED__
#define __GWI_CardRead_AdaptExLib_LIBRARY_DEFINED__

/* library GWI_CardRead_AdaptExLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_GWI_CardRead_AdaptExLib;

#ifndef ___DGWI_CardRead_AdaptEx_DISPINTERFACE_DEFINED__
#define ___DGWI_CardRead_AdaptEx_DISPINTERFACE_DEFINED__

/* dispinterface _DGWI_CardRead_AdaptEx */
/* [uuid] */ 


EXTERN_C const IID DIID__DGWI_CardRead_AdaptEx;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B028B27E-8384-4A53-97B9-C4ACCEDD99BA")
    _DGWI_CardRead_AdaptEx : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DGWI_CardRead_AdaptExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGWI_CardRead_AdaptEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGWI_CardRead_AdaptEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGWI_CardRead_AdaptEx * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGWI_CardRead_AdaptEx * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGWI_CardRead_AdaptEx * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGWI_CardRead_AdaptEx * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGWI_CardRead_AdaptEx * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DGWI_CardRead_AdaptExVtbl;

    interface _DGWI_CardRead_AdaptEx
    {
        CONST_VTBL struct _DGWI_CardRead_AdaptExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGWI_CardRead_AdaptEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DGWI_CardRead_AdaptEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DGWI_CardRead_AdaptEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DGWI_CardRead_AdaptEx_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DGWI_CardRead_AdaptEx_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DGWI_CardRead_AdaptEx_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DGWI_CardRead_AdaptEx_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DGWI_CardRead_AdaptEx_DISPINTERFACE_DEFINED__ */


#ifndef ___DGWI_CardRead_AdaptExEvents_DISPINTERFACE_DEFINED__
#define ___DGWI_CardRead_AdaptExEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DGWI_CardRead_AdaptExEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DGWI_CardRead_AdaptExEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0366321C-E7BC-4143-88AE-39A81E4A36C3")
    _DGWI_CardRead_AdaptExEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DGWI_CardRead_AdaptExEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DGWI_CardRead_AdaptExEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DGWI_CardRead_AdaptExEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DGWI_CardRead_AdaptExEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DGWI_CardRead_AdaptExEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DGWI_CardRead_AdaptExEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DGWI_CardRead_AdaptExEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DGWI_CardRead_AdaptExEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DGWI_CardRead_AdaptExEventsVtbl;

    interface _DGWI_CardRead_AdaptExEvents
    {
        CONST_VTBL struct _DGWI_CardRead_AdaptExEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DGWI_CardRead_AdaptExEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DGWI_CardRead_AdaptExEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DGWI_CardRead_AdaptExEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DGWI_CardRead_AdaptExEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DGWI_CardRead_AdaptExEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DGWI_CardRead_AdaptExEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DGWI_CardRead_AdaptExEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DGWI_CardRead_AdaptExEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_GWI_CardRead_AdaptEx;

#ifdef __cplusplus

class DECLSPEC_UUID("7F7313CB-3817-4AFB-A66A-E26398304CB2")
GWI_CardRead_AdaptEx;
#endif
#endif /* __GWI_CardRead_AdaptExLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


