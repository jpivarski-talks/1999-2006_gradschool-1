// -*- C++ -*-
//
// File:    TrkmanInfoProxy.h
// Package: TrkmanInfo
// Module:  TrkmanInfoProd
//
/**\class TrkmanInfoProxy TrkmanInfoProxy.h TrkmanProd/TrkmanInfoProxy.h
 
 Description: Proxy to provide (empty) TrkmanInfo to Frame

 Usage:
    <usage>

*/
//
// Author:      Thomas Meyer
// Created:     Tue Jan 15 14:06:46 EST 2002
// $Id: TrkmanInfoProxy.h,v 1.2 2002/11/04 18:38:27 nea9 Exp $
//
// Revision history
//
// $Log: TrkmanInfoProxy.h,v $
// Revision 1.2  2002/11/04 18:38:27  nea9
// New CleoIII Trkman
//
// Revision 1.1.1.1  2002/01/28 13:57:18  tom
// Imported TrkmanProd sources
//
/* ******************************************************************** */
#ifndef TRKMANPROD_TRKMANINFOPROXY_H
#define TRKMANPROD_TRKMANINFOPROXY_H

// SYSTEM INCLUDE FILES

// USER INCLUDE FILES
#include "ProxyBind/ProxyBindableTemplate.h"
#include "STLUtility/fwd_vector.h"

#include "Trkman/TrkmanInfo.h"
#include "Trkman/TMCurlers.h"
// DEFINITIONS

// FORWARD DECLARATIONS
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */


class TrkmanInfoProxy : 
  public ProxyBindableTemplate< FAPtrTable< TrkmanInfo > >
{
      // ---------- FRIEND CLASSES AND FUNCTIONS ---------------

public:
      // ---------- CONSTANTS, ENUMS AND TYPEDEFS --------------
      typedef FAPtrTable< TrkmanInfo > value_type ;
      typedef STL_VECTOR( TrkmanInfo* ) TrkmanInfoList;
      typedef TMCurlers::CurlerGroupVector CurlerGroupVector;
      typedef TMCurlers::CurlerGroupVector VeeGroupVector;


      // ---------- CONSTRUCTORS AND DESTRUCTOR ----------------
      TrkmanInfoProxy();
      
      virtual ~TrkmanInfoProxy();

      // ---------- MEMBER FUNCTIONS ---------------------------
      
      // Use this form of a function when calling 'bind'
      // void boundMethod( const Record& iRecord );
      
      // ---------- CONST MEMBER FUNCTIONS ---------------------
      
      // ---------- STATIC MEMBER FUNCTIONS --------------------

protected:
      // ---------- PROTECTED MEMBER FUNCTIONS -----------------
      virtual void invalidateCache() ;
      
      virtual const value_type* faultHandler( const Record& aRecord,
                                          const DataKey& aKey );

      // ---------- PROTECTED CONST MEMBER FUNCTIONS -----------

private:
      // ---------- CONSTRUCTORS AND DESTRUCTOR ----------------
      TrkmanInfoProxy( const TrkmanInfoProxy& );
      
      // ---------- ASSIGNMENT OPERATOR(S) ---------------------
      const TrkmanInfoProxy& operator=( const TrkmanInfoProxy& );
      
      // ---------- PRIVATE MEMBER FUNCTIONS -------------------
      // This function has already been written for you
      void bind( void (TrkmanInfoProxy::*iMethod)( const Record& ),
		 const Stream::Type& iStream );

      // ---------- PRIVATE CONST MEMBER FUNCTIONS -------------

      // ---------- DATA MEMBERS -------------------------------
      value_type* m_ptrTable ;
      TrkmanInfoList m_trkminfos;

      // ---------- STATIC DATA MEMBERS ------------------------

};

// INLINE FUNCTION DEFINITIONS

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "TrkmanProd/Template/TrkmanInfoProxy.cc"
//#endif

#endif /* TRKMANPROD_TRKMANINFOPROXY_H */
