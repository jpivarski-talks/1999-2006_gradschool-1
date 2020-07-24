// -*- C++ -*-
#if !defined(EVENTVERTEXPROD_EVENTVERTEXINFOPROXY_H)
#define EVENTVERTEXPROD_EVENTVERTEXINFOPROXY_H
//
// Package:     <EventVertexProd>
// Module:      EventVertexInfoProxy
//
/**\class EventVertexInfoProxy EventVertexInfoProxy.h EventVertexProd/EventVertexInfoProxy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Michael Watkins
// Created:     Thu May 30 14:41:31 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "EventVertex/EventVertexInfo.h"
#include "EventVertexProd/EventVertexPrivate.h"
#include "EventVertexProd/EventVertexProd.h"
#include "EventVertexProd/EventVertexHolder.h"
// forward declarations

class EventVertexInfoProxy : public ProxyBindableTemplate< EventVertexInfo >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef EventVertexInfo value_type;

      // Constructors and destructor
      EventVertexInfoProxy();
      virtual ~EventVertexInfoProxy();

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
      EventVertexInfoProxy( const EventVertexInfoProxy& );

      // assignment operator(s)
      const EventVertexInfoProxy& operator=( const EventVertexInfoProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (EventVertexInfoProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_EventVertexInfo ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "EventVertexProd/Template/EventVertexInfoProxy.cc"
//#endif

#endif /* EVENTVERTEXPROD_EVENTVERTEXINFOPROXY_H */
