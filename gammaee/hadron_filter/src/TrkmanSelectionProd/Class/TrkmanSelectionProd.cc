// -*- C++ -*-
//
// Package:     <TrkmanSelectionProd>
// Module:      TrkmanSelectionProd
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Nadia Adam
// Created:     Mon Oct 28 12:14:24 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TrkmanSelectionProd/TrkmanSelectionProd.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"


// Selection Proxy
#include "Selection/Template/SelectionProxy.cc"
#include "Selection/SelectionProxy.h"
#include "Selection/SelectionPrefixProxy.h"
#include "DataHandler/ProxyFactoryArgument.h"
#include "Navigation/NavTrack.h"
#include "TrkmanSelectionProd/TrkmanApprover.h"
#include "TrkmanSelectionProd/TrkmanTkShMatchApprover.h"

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
static const char* const kFacilityString = "TrkmanSelectionProd.TrkmanSelectionProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: producer.cc,v 1.19 2000/12/04 19:11:13 cdj Exp $";
static const char* const kTagString = "$Name: v03_06_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
TrkmanSelectionProd::TrkmanSelectionProd( void )               // anal1
   : Producer( "TrkmanSelectionProd" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // Proxy that selects NavTrack objects to return to Frame
   //   as "TrkmanApproved" tracks
   typedef TrkmanApprover TrkmanApproverType;
   TrkmanApproverType NavTrack_Selector1;
   registerProxyFactory( Stream::kEvent,
			 new 
			 ProxyFactoryArgument< SelectionPrefixProxy< 
			 NavTrack,
			 TrkmanApproverType >,
			 TrkmanApproverType >(NavTrack_Selector1),
			 UsageTag("TrkmanApproved") );

   // Proxy that selects NavTrack objects to return to Frame
   //   as "TrkmanApproved" tracks for track-shower matching
   typedef TrkmanTkShMatchApprover TrkmanTkShMatchApproverType;
   TrkmanTkShMatchApproverType NavTrack_Selector2;
   registerProxyFactory( Stream::kEvent,
			 new 
			 ProxyFactoryArgument< SelectionPrefixProxy< 
			 NavTrack,
			 TrkmanTkShMatchApproverType >,
			 TrkmanTkShMatchApproverType >(NavTrack_Selector2),
			 UsageTag("TrkmanTkShMatch") );

}

// TrkmanSelectionProd::TrkmanSelectionProd( const TrkmanSelectionProd& iTrkmanSelectionProd )
// {
//    *this = iTrkmanSelectionProd;
// }

TrkmanSelectionProd::~TrkmanSelectionProd()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
TrkmanSelectionProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TrkmanSelectionProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
TrkmanSelectionProd::hist_book( HIHistoManager& )
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
