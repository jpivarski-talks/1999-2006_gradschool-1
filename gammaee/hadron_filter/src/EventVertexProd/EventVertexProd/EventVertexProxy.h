// -*- C++ -*-
#if !defined(EVENTVERTEXPROD_EVENTVERTEXPROXY_H)
#define EVENTVERTEXPROD_EVENTVERTEXPROXY_H
//
// Package:     <EventVertexProd>
// Module:      EventVertexProxy
//
/**\class EventVertexProxy EventVertexProxy.h EventVertexProd/EventVertexProxy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Michael Watkins
// Created:     Thu May 30 14:41:17 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "EventVertexProd/EventVertexPrivate.h"
#include "EventVertex/EventVertex.h"
#include "EventVertexProd/EventVertexProd.h"
#include "EventVertexProd/EventVertexHolder.h"
// forward declarations

class EventVertexProxy : public ProxyBindableTemplate< EventVertex >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef EventVertex value_type;

      // Constructors and destructor
      EventVertexProxy();
      virtual ~EventVertexProxy();

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
      EventVertexProxy( const EventVertexProxy& );

      // assignment operator(s)
      const EventVertexProxy& operator=( const EventVertexProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (EventVertexProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_EventVertex ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "EventVertexProd/Template/EventVertexProxy.cc"
//#endif

#endif /* EVENTVERTEXPROD_EVENTVERTEXPROXY_H */
