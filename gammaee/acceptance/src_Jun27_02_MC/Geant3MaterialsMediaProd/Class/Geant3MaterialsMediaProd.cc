// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      Geant3MaterialsMediaProd
// 
// Description: 
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec 14 10:58:53 EST 1999
// $Id: Geant3MaterialsMediaProd.cc,v 1.4 2001/03/15 21:51:22 bkh Exp $
//
// Revision history
//
// $Log: Geant3MaterialsMediaProd.cc,v $
// Revision 1.4  2001/03/15 21:51:22  bkh
// Get Magnetic Field from Start Run
//
// Revision 1.3  2001/01/16 20:06:23  bkh
// Remove internal command to setup GEANT3
//
// Revision 1.2  1999/12/29 16:26:25  bkh
// Vacuum atomic properties must be non-zero in a mix
//
// Revision 1.1.1.1  1999/12/15 18:35:50  bkh
// imported Geant3MaterialsMediaProd sources
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Geant3MaterialsMediaProd/Geant3MaterialsMediaProd.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
//#include "DataHandler/ProxyFactoryFunction.h"

#include "Geant3MaterialsMediaProd/DGConstMaterialPtrProxy.h"
#include "Geant3MaterialsMediaProd/G3iTrackingMediumProxy.h"

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
static const char* const kReport = "Geant3MaterialsMediaProd.Geant3MaterialsMediaProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: Geant3MaterialsMediaProd.cc,v 1.4 2001/03/15 21:51:22 bkh Exp $";
static const char* const kTagString = "$Name: v01_01_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
Geant3MaterialsMediaProd::Geant3MaterialsMediaProd()
   : Producer  ( "Geant3MaterialsMediaProd" )
{
   report( DEBUG, kReport ) << "here in ctor()" << endl;

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
   registerProxyFactory( Stream::kBaseGeometry, 
			 new ProxyFactory< DGConstMaterialPtrProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kStartRun, 
			 new ProxyFactory< G3iTrackingMediumProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#include "DataHandler/Template/ProxyFactory.cc"
template class ProxyFactory< DGConstMaterialPtrProxy >;
template class ProxyFactory< G3iTrackingMediumProxy  >;

// Geant3MaterialsMediaProd::Geant3MaterialsMediaProd( const Geant3MaterialsMediaProd& iGeant3MaterialsMediaProd )
// {
//    *this = iGeant3MaterialsMediaProd;
// }

Geant3MaterialsMediaProd::~Geant3MaterialsMediaProd()
{
   report( DEBUG, kReport ) << "here in dtor()" << endl;
}

//
// assignment operators
//
// const Geant3MaterialsMediaProd& Geant3MaterialsMediaProd::operator=( const Geant3MaterialsMediaProd& iGeant3MaterialsMediaProd )
// {
//   if( this != &iGeant3MaterialsMediaProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iGeant3MaterialsMediaProd );
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
Geant3MaterialsMediaProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kReport ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Geant3MaterialsMediaProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kReport ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
Geant3MaterialsMediaProd::hist_book( HIHistoManager& )
{
   report( DEBUG, kReport ) << "here in hist_book()" << endl;

   // book your histograms here

}

//
// const member functions
//

//
// static member functions
//
