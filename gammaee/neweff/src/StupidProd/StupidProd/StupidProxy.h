// -*- C++ -*-
#if !defined(STUPIDPROD_STUPIDPROXY_H)
#define STUPIDPROD_STUPIDPROXY_H
//
// Package:     <StupidProd>
// Module:      StupidProxy
//
/**\class StupidProxy StupidProxy.h StupidProd/StupidProxy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Mar 22 01:38:42 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "StupidProd/Stupid.h"

// forward declarations

class StupidProxy : public ProxyBindableTemplate< Stupid >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef Stupid value_type;

      // Constructors and destructor
      StupidProxy();
      virtual ~StupidProxy();

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
      StupidProxy( const StupidProxy& );

      // assignment operator(s)
      const StupidProxy& operator=( const StupidProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (StupidProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_Stupid ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "StupidProd/Template/StupidProxy.cc"
//#endif

#endif /* STUPIDPROD_STUPIDPROXY_H */
