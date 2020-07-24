// -*- C++ -*-
//
// Package:     <EventVertexProd>
// Module:      EventVertexProd
// 
// Description: Producer to generate event vertex
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Roy A. Briere, Michael Earl Watkins
// Created:     Mon Mar 18 22:54:05 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"
#include "EventVertexProd/EventVertexProd.h"
#include "EventVertexProd/EventVertexPrivateProxy.h"
#include "EventVertexProd/EventVertexHolder.h"
#include "EventVertexProd/EventVertexProxy.h"
#include "EventVertexProd/EventVertexInfoProxy.h"

#include "Experiment/report.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "EventVertexProd.EventVertexProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: producer.cc,v 1.19 2000/12/04 19:11:13 cdj Exp $";
static const char* const kTagString = "$Name: v03_06_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
EventVertexProd::EventVertexProd( void )               // anal1
   : Producer  ( "EventVertexProd" ),
    m_eventVertexHolder  (this)

{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;
  
   // ----- register proxy factories ------------------
   // (Please see the "ProxyExample" library for examples!)
   //
   // Two steps: 1) use "registerProxyFactory" to register
   //            2) instantiate ProxyFactory/Function
   //               (if you're using the standard templated factories;
   //                you may of course roll your own!)

   // Proxy Registration Step 1:
   // either
   //    register default-ctor proxy
   // registerProxyFactory( Stream::kEvent, 
   //			 new ProxyFactory< MyProxy >, 
   //			 UsageTag() );    // or UsageTag( "MyUsage" )
   // or
   //    register non-default-ctor proxy 
   //       (don't forget to write "EventVertexProd::makeMyProxy()")
   registerProxyFactory(Stream::kEvent, new
			ProxyFactoryFunction<EventVertexProd, EventVertexPrivateProxy>
			(*this, &EventVertexProd::makeEventVertexPrivateProxy),
			UsageTag());    // or UsageTag( "MyUsage" )
   registerProxyFactory(Stream::kEvent, new
			ProxyFactoryFunction<EventVertexProd, EventVertexProxy>
			(*this, &EventVertexProd::makeEventVertexProxy),
			UsageTag());    // or UsageTag( "MyUsage" )
   registerProxyFactory(Stream::kEvent, new
			ProxyFactoryFunction<EventVertexProd, EventVertexInfoProxy>
			(*this, &EventVertexProd::makeEventVertexInfoProxy),
			UsageTag());    // or UsageTag( "MyUsage" )
}

// Proxy Registration Step 2:
// template instantiations for proxy factories
//#include "DataHandler/Template/ProxyFactory.cc"
//template class ProxyFactory< MyProxy >;
#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction<EventVertexProd, EventVertexPrivateProxy>;
template class ProxyFactoryFunction<EventVertexProd, EventVertexProxy>;
template class ProxyFactoryFunction<EventVertexProd, EventVertexInfoProxy>;
// non-trivial proxyfactory producer method used above
// (if you want to use it, don't forget to declare this method 
//  in "producer.h"!)
ProxyBase*
EventVertexProd::makeEventVertexPrivateProxy()
{ 
  return new EventVertexPrivateProxy(this->eventVertexHolder());
}
ProxyBase*
EventVertexProd::makeEventVertexProxy()
{ 
  return new EventVertexProxy();
}
ProxyBase*
EventVertexProd::makeEventVertexInfoProxy()
{ 
  return new EventVertexInfoProxy();
}
// EventVertexProd::EventVertexProd( const EventVertexProd& iEventVertexProd )
// {
//    *this = iEventVertexProd;
// }

EventVertexProd::~EventVertexProd()                    // anal5
{
  report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const EventVertexProd& EventVertexProd::operator=( const EventVertexProd& iEventVertexProd )
// {
//   if( this != &iEventVertexProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iEventVertexProd );
//   }
//
//   return *this;
// }

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
EventVertexProd::init( void )          // anal1 "Interactive"
{
  report( DEBUG, kFacilityString ) << "here in init()" << endl;

  // do any initialization here based on Parameter Input by User
  // (e.g. run expensive algorithms that are based on parameters
  //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
EventVertexProd::terminate( void )     // anal5 "Interactive"
{
  report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

  // do anything here BEFORE New Parameter Change
  // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
EventVertexProd::hist_book( HIHistoManager& iHistoManager)
{
  report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

  // book your histograms here

}

//
// const member functions
//

//
// static member functions
//
