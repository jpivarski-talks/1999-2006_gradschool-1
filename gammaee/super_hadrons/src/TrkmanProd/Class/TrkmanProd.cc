// -*- C++ -*-
//
// File:    TrkmanProd.cc
// Package: TrkmanProd
// Module:  TrkmanProd
// 
// Description: Wrapped-up CLEO II Trkman common blocks
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Thomas Meyer
// Created:     Mon Jan 14 11:28:13 EST 2002
// $Id: TrkmanProd.cc,v 1.2 2002/11/04 18:38:49 nea9 Exp $
//
// Revision history
//
// $Log: TrkmanProd.cc,v $
// Revision 1.2  2002/11/04 18:38:49  nea9
// New CleoIII Trkman
//
// Revision 1.1.1.1  2002/01/28 13:57:18  tom
// Imported TrkmanProd sources
//
/* ******************************************************************** */

#include "Experiment/Experiment.h"

// SYSTEM INCLUDE FILES

// STL
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// USER INCLUDE FILES
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"

#include "TrkmanProd/TrkmanProd.h"
#include "TrkmanProd/TrkmanInfoProxy.h"
#include "TrkmanProd/TMClassificationProxy.h"
#include "TrkmanProd/TrkmanLatticeProxy.h"

// Selection Proxy
#include "Selection/Template/SelectionProxy.cc"
#include "Selection/SelectionProxy.h"
#include "Selection/SelectionPrefixProxy.h"
#include "DataHandler/ProxyFactoryArgument.h"
#include "Navigation/NavTrack.h"
// #include "TrkmanProd/TrkmanApprover.h"
// #include "TrkmanProd/TrkmanTkShMatchApprover.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCDecayTree/MCVertex.h"

// STL (again)
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// DEFINITIONS/MACROS
// Dumb shorthand for report
#define dout report(DEBUG, kFacilityString)
#define iout report(INFO, kFacilityString)
#define wout report(WARNING, kFacilityString)
#define eout report(EMERGENCY, kFacilityString)

//
// CONSTANTS, ENUMS AND TYPEDEFS
//
static const char* const kFacilityString = "TrkmanProd.TrkmanProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const 
kIdString  = "$Id: TrkmanProd.cc,v 1.2 2002/11/04 18:38:49 nea9 Exp $";

static const char* const
kTagString = "$Name:  $";

//
// STATIC DATA MEMBER DEFINITIONS
//

//
// CONSTRUCTORS AND DESTRUCTOR
//

/* ======================================================================== */
TrkmanProd::TrkmanProd( void )
   : Producer( "TrkmanProd" )
{
  report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

  // Proxy that provides TrkmanInfo objects to Frame
  registerProxyFactory( Stream::kEvent,
                        new
                        ProxyFactory< TMClassificationProxy >,
                        UsageTag() ); 

  registerProxyFactory( Stream::kEvent,
                        new
                        ProxyFactory< TrkmanInfoProxy >,
                        UsageTag() ); 

  registerProxyFactory( Stream::kEvent,
                        new
                        ProxyFactory< TrkmanLatticeProxy >,
                        UsageTag() ); 


  // Proxy that selects NavTrack objects to return to Frame
  //   as "TrkmanApproved" tracks
//   typedef TrkmanApprover TrkmanApproverType;
//   TrkmanApproverType NavTrack_Selector1;
//   registerProxyFactory( Stream::kEvent,
//                         new 
//                         ProxyFactoryArgument< SelectionPrefixProxy< 
//                         NavTrack,
//                         TrkmanApproverType >,
//                         TrkmanApproverType >(NavTrack_Selector1),
//                         UsageTag("TrkmanApproved") );

  // Proxy that selects NavTrack objects to return to Frame
  //   as "TrkmanApproved" tracks for track-shower matching
//   typedef TrkmanTkShMatchApprover TrkmanTkShMatchApproverType;
//   TrkmanTkShMatchApproverType NavTrack_Selector2;
//   registerProxyFactory( Stream::kEvent,
//                         new 
//                         ProxyFactoryArgument< SelectionPrefixProxy< 
//                         NavTrack,
//                         TrkmanTkShMatchApproverType >,
//                         TrkmanTkShMatchApproverType >(NavTrack_Selector2),
//                         UsageTag("TrkmanTkShMatch") );
}
/* ======================================================================== */

#include "DataHandler/Template/ProxyFactory.cc"
template class ProxyFactory< TrkmanInfoProxy >;
template class ProxyFactory< TrkmanLatticeProxy >;
template class ProxyFactory< TMClassificationProxy >;

#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction< TrkmanProd, TrkmanInfoProxy >;
template class ProxyFactoryFunction< TrkmanProd, TrkmanLatticeProxy >;
template class ProxyFactoryFunction< TrkmanProd, TMClassificationProxy >;

/* ======================================================================== */
// TrkmanProd::TrkmanProd( const TrkmanProd& iTrkmanProd )
// {
//    *this = iTrkmanProd;
// }
/* ======================================================================== */

/* ======================================================================== */
TrkmanProd::~TrkmanProd()
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}
/* ======================================================================== */

//
// ASSIGNMENT OPERATORS
//

/* ======================================================================== */
// const TrkmanProd& TrkmanProd::operator=( const TrkmanProd& iTrkmanProd )
// {
//   if( this != &iTrkmanProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iTrkmanProd );
//   }
//
//   return *this;
// }
/* ======================================================================== */

//
// MEMBER FUNCTIONS
//
// ProxyBase* TrkManProd::makeTrkmanInfoProxy()
// {
//    return new TrkmanInfoProxy( this );
// }

// TMClassification* TrkmanProd::trkmanClassifications()
// {
//    return m_trkmanClassifications;
// }

// TMData* TrkmanProd::trkmanData()
// {
//    return m_data;
// }

/* ======================================================================== */
void
TrkmanProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}
/* ======================================================================== */

/* ======================================================================== */
void
TrkmanProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}
/* ======================================================================== */

/* ======================================================================== */
void
TrkmanProd::hist_book( HIHistoManager& )
{
  report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

  // book your histograms here

}
/* ======================================================================== */



//
// CONST MEMBER FUNCTIONS
//

//
// STATIC MEMBER FUNCTIONS
//
