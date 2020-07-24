// -*- C++ -*-
//
// Package:     <TriggerInfoProd>
// Module:      TriggerInfoProd
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Apr  5 12:03:40 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TriggerInfoProd/TriggerInfoProd.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"

#include "TriggerInfoProd/TriggerInfoProxy.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "TriggerInfoProd.TriggerInfoProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: producer.cc,v 1.19 2000/12/04 19:11:13 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
TriggerInfoProd::TriggerInfoProd( void )               // anal1
   : Producer( "TriggerInfoProd" )
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
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< TriggerInfoProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   // or
   //    register non-default-ctor proxy 
   //       (don't forget to write "TriggerInfoProd::makeMyProxy()")
#if 0
   registerProxyFactory( 
      Stream::kEvent, 
      new ProxyFactoryFunction< TriggerInfoProd, MyProxy >( *this, 
						     &TriggerInfoProd::makeMyProxy ),
      UsageTag() );    // or UsageTag( "MyUsage" )
#endif
}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#include "DataHandler/Template/ProxyFactory.cc"
template class ProxyFactory< TriggerInfoProxy >;
#if 0
#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction< TriggerInfoProd, MyProxy >;
#endif

// non-trivial proxyfactory producer method used above
// (if you want to use it, don't forget to declare this method 
//  in "producer.h"!)
#if 0
ProxyBase*
TriggerInfoProd::makeMyProxy()
{ 
   return new MyProxy( "pass me something" );
}
#endif

// TriggerInfoProd::TriggerInfoProd( const TriggerInfoProd& iTriggerInfoProd )
// {
//    *this = iTriggerInfoProd;
// }

TriggerInfoProd::~TriggerInfoProd()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const TriggerInfoProd& TriggerInfoProd::operator=( const TriggerInfoProd& iTriggerInfoProd )
// {
//   if( this != &iTriggerInfoProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iTriggerInfoProd );
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
TriggerInfoProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TriggerInfoProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
TriggerInfoProd::hist_book( HIHistoManager& )
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
