// -*- C++ -*-
#if !defined(EVENTVERTEXPROD_EVENTVERTEXPRIVATEPROXY_H)
#define EVENTVERTEXPROD_EVENTVERTEXPRIVATEPROXY_H
//
// Package:     <EventVertexProd>
// Module:      EventVertexPrivateProxy
//
/**\class EventVertexPrivateProxy EventVertexPrivateProxy.h EventVertexProd/EventVertexPrivateProxy.h
 
 Description:   Proxy to make event vertex

 Usage:
    <usage>

*/
//
// Author:      Roy A. Briere, Michael Earl Watkins
// Created:     Mon Mar 18 23:06:31 EST 2002
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
#include "EventVertexProd/EventVertexProd.h"
#include "EventVertexProd/EventVertexHolder.h"
// forward declarations

class EventVertexPrivateProxy : public ProxyBindableTemplate< EventVertexPrivate >
{
  // friend classes and functions

 public:
  // constants, enums and typedefs
  typedef EventVertexPrivate value_type;

  // Constructors and destructor
  EventVertexPrivateProxy(EventVertexHolder* eventVertexHolder );
  virtual ~EventVertexPrivateProxy();

  // member functions

  // use this form of a function when calling 'bind'
  // void boundMethod( const Record& iRecord );

  // const member functions

  // static member functions

 protected:
  // protected member functions
      virtual void invalidateCache();
      virtual const value_type* faultHandler(const Record& aRecord,
                                             const DataKey& aKey);

  // protected const member functions

 private:
  // Constructors and destructor
  EventVertexPrivateProxy( const EventVertexPrivateProxy& );

  // assignment operator(s)
  const EventVertexPrivateProxy& operator=( const EventVertexPrivateProxy& );

  // private member functions

  //this function has already been written for you
  void bind(void (EventVertexPrivateProxy::*iMethod)( const Record& ),
	    const Stream::Type& iStream);

  // private const member functions

  // data members
  value_type* m_EventVertexPrivate;
  EventVertexHolder* m_eventVertexHolder;   
  // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "EventVertexProd/Template/EventVertexPrivateProxy.cc"
//#endif

#endif /* EVENTVERTEXPROD_EVENTVERTEXPRIVATEPROXY_H */
