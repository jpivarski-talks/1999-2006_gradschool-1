// -*- C++ -*-
//
// Package:     <EvtGenProd>
// Module:      EvtGenProd
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Anders Ryd
// Created:     Sat Sep 13 17:58:54 EDT 2003
// $Id: EvtGenProd.cc,v 1.3 2003/10/14 20:32:40 ryd Exp $
//
// Revision history
//
// $Log: EvtGenProd.cc,v $
// Revision 1.3  2003/10/14 20:32:40  ryd
// Switch to jetset; bug fixes for initial quarks
//
// Revision 1.2  2003/10/13 15:55:45  ryd
// Silence some debug messages
//
// Revision 1.1.1.1  2003/10/07 02:48:57  ryd
// imported EvtGenProd sources
//
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "EvtGenProd/EvtGenProd.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"
#include "EvtGenProd/EvtGenProxy.h"

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
static const char* const kFacilityString = "EvtGenProd.EvtGenProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: EvtGenProd.cc,v 1.3 2003/10/14 20:32:40 ryd Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
EvtGenProd::EvtGenProd( void )               // anal1
  : Producer( "EvtGenProd" ),
    m_decayfile( "decayFile", this, "" ),
    m_udecayfile( "udecayFile", this, "" ),
    m_evtpdl( "evtpdl", this, "" )

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

   //cout << "RYD inserting EvtGenProxy"<<endl;

   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactoryFunction< EvtGenProd, EvtGenProxy >
			 (*this, &EvtGenProd::makeEvtGenProxy), 
			 UsageTag("Generator") );    // or UsageTag( "MyUsage" )

}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction< EvtGenProd, EvtGenProxy >;



// EvtGenProd::EvtGenProd( const EvtGenProd& iEvtGenProd )
// {
//    *this = iEvtGenProd;
// }

EvtGenProd::~EvtGenProd()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const EvtGenProd& EvtGenProd::operator=( const EvtGenProd& iEvtGenProd )
// {
//   if( this != &iEvtGenProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iEvtGenProd );
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
EvtGenProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
EvtGenProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
EvtGenProd::hist_book( HIHistoManager& )
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





