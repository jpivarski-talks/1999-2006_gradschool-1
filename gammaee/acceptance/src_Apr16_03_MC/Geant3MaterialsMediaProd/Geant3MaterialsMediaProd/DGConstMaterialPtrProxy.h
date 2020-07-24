#if !defined(GEANT3MATERIALSMEDIAPROD_DGCONSTMATERIALPTRPROXY_H)
#define GEANT3MATERIALSMEDIAPROD_DGCONSTMATERIALPTRPROXY_H
// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      DGConstMaterialPtrProxy
//
/**\class DGConstMaterialPtrProxy DGConstMaterialPtrProxy.h Geant3MaterialsMediaProd/DGConstMaterialPtrProxy.h
 
 Description: Proxy to "handle" DGConstMaterialPtr

 Usage:
    Triggered by extract of table of material pointers

*/
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec 14 11:04:59 EST 1999
// $Id: DGConstMaterialPtrProxy.h,v 1.1.1.1 1999/12/15 18:35:49 bkh Exp $
//
// Revision history
//
// $Log: DGConstMaterialPtrProxy.h,v $
// Revision 1.1.1.1  1999/12/15 18:35:49  bkh
// imported Geant3MaterialsMediaProd sources
//
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "DetectorGeometry/DGConstMaterialPtr.h"

// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */


class DGConstMaterialPtrProxy : public ProxyBindableTemplate< FAPtrTable< DGConstMaterialPtr > >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef FAPtrTable< DGConstMaterialPtr > value_type ;

      // Constructors and destructor
      DGConstMaterialPtrProxy();
      virtual ~DGConstMaterialPtrProxy();

      // member functions
      // use this form of a function when calling 'bind'
      // void boundMethod( const Record& iRecord );
      // const member functions
      // static member functions

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );

      // protected const member functions

   private:
      // Constructors and destructor
      DGConstMaterialPtrProxy( const DGConstMaterialPtrProxy& );
      // assignment operator(s)
      const DGConstMaterialPtrProxy& operator=( const DGConstMaterialPtrProxy& );
      // private member functions

      //this function has already been written for you
      void bind(
		void (DGConstMaterialPtrProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );
      // private const member functions

      // data members
      value_type* m_ptrTable ;

      // static data members
};

// inline function definitions
#endif /* GEANT3MATERIALSMEDIAPROD_DGCONSTMATERIALPTRPROXY_H */
