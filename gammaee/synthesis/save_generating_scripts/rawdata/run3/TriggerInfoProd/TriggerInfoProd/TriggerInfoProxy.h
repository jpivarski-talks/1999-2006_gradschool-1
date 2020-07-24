// -*- C++ -*-
#if !defined(TRIGGERINFOPROD_TRIGGERINFOPROXY_H)
#define TRIGGERINFOPROD_TRIGGERINFOPROXY_H
//
// Package:     <TriggerInfoProd>
// Module:      TriggerInfoProxy
//
/**\class TriggerInfoProxy TriggerInfoProxy.h TriggerInfoProd/TriggerInfoProxy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Apr  5 12:24:26 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "TriggerInfoProd/TriggerInfo.h"

// forward declarations

class TriggerInfoProxy : public ProxyBindableTemplate< TriggerInfo >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef TriggerInfo value_type;

      // Constructors and destructor
      TriggerInfoProxy();
      virtual ~TriggerInfoProxy();

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
      TriggerInfoProxy( const TriggerInfoProxy& );

      // assignment operator(s)
      const TriggerInfoProxy& operator=( const TriggerInfoProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (TriggerInfoProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_TriggerInfo ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "TriggerInfoProd/Template/TriggerInfoProxy.cc"
//#endif

#endif /* TRIGGERINFOPROD_TRIGGERINFOPROXY_H */
