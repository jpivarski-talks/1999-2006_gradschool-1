// -*- C++ -*-
#if !defined(PACKAGE_TRKMANLATTICEPROXY_H)
#define PACKAGE_TRKMANLATTICEPROXY_H
//
// Package:     <package>
// Module:      TrkmanLatticeProxy
//
/**\class TrkmanLatticeProxy TrkmanLatticeProxy.h package/TrkmanLatticeProxy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Nadia Adam
// Created:     Mon Oct 21 14:36:19 EDT 2002
// $Id: TrkmanLatticeProxy.h,v 1.1 2002/11/04 18:38:27 nea9 Exp $
//
// Revision history
//
// $Log: TrkmanLatticeProxy.h,v $
// Revision 1.1  2002/11/04 18:38:27  nea9
// New CleoIII Trkman
//
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "Trkman/TrkmanLattice.h"
#include "Trkman/TMCurlers.h"

// forward declarations

class TrkmanLatticeProxy : public ProxyBindableTemplate< TrkmanLattice >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef TrkmanLattice value_type;
      typedef TMCurlers::CurlerGroup TrackVector;
      typedef TMCurlers::CurlerGroupVector CurlerGroupVector;
      typedef TMCurlers::CurlerGroupVector VeeGroupVector;

      // Constructors and destructor
      TrkmanLatticeProxy();
      virtual ~TrkmanLatticeProxy();

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
      TrkmanLatticeProxy( const TrkmanLatticeProxy& );

      // assignment operator(s)
      const TrkmanLatticeProxy& operator=( const TrkmanLatticeProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (TrkmanLatticeProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_TrkmanLattice ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "package/Template/TrkmanLatticeProxy.cc"
//#endif

#endif /* PACKAGE_TRKMANLATTICEPROXY_H */
