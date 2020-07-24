#if !defined(GEANT3MATERIALSMEDIAPROD_G3ITRACKINGMEDIUMPROXY_H)
#define GEANT3MATERIALSMEDIAPROD_G3ITRACKINGMEDIUMPROXY_H
// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      G3iTrackingMediumProxy
//
/**\class G3iTrackingMediumProxy G3iTrackingMediumProxy.h Geant3MaterialsMediaProd/G3iTrackingMediumProxy.h
 
 Description: Proxy to "handle" G3iTrackingMedium

 Usage:
    <usage>

*/
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec 14 11:06:34 EST 1999
// $Id: G3iTrackingMediumProxy.h,v 1.1.1.1 1999/12/15 18:35:49 bkh Exp $
//
// Revision history
//
// $Log: G3iTrackingMediumProxy.h,v $
// Revision 1.1.1.1  1999/12/15 18:35:49  bkh
// imported Geant3MaterialsMediaProd sources
//
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "Geant3Interface/G3iTrackingMedium.h"

// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */


class G3iTrackingMediumProxy : public ProxyBindableTemplate< FAPtrTable< G3iTrackingMedium > >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef FAPtrTable< G3iTrackingMedium > value_type ;

      // Constructors and destructor
      G3iTrackingMediumProxy();
      virtual ~G3iTrackingMediumProxy();

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
      G3iTrackingMediumProxy( const G3iTrackingMediumProxy& );
      // assignment operator(s)
      const G3iTrackingMediumProxy& operator=( const G3iTrackingMediumProxy& );
      // private member functions
      //this function has already been written for you
      void bind(
		void (G3iTrackingMediumProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );
      // private const member functions

      // data members
      value_type* m_ptrTable ;

      // static data members
};

// inline function definitions

#endif /* GEANT3MATERIALSMEDIAPROD_G3ITRACKINGMEDIUMPROXY_H */
