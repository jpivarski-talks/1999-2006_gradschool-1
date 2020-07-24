// -*- C++ -*-
//
// Package:     CcenFailuresFilter
// Module:      CcenFailuresFilter
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Jul 26 17:01:24 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "CcenFailuresFilter/CcenFailuresFilter.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "TriggerL1Data/TriggerL1Data.h"

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
//RICH example 
//Dedx example
//Event Shape example


// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.CcenFailuresFilter" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.25 2002/01/25 20:42:06 ajm36 Exp $";
static const char* const kTagString = "$Name: v06_03_01 $";

//
// static data member definitions
//


//
// constructors and destructor
//
CcenFailuresFilter::CcenFailuresFilter( void )               // anal1
   : Processor( "CcenFailuresFilter" )
   , m_ebeam("ebeam", this, 0.)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &CcenFailuresFilter::event,    Stream::kEvent );
   //bind( &CcenFailuresFilter::beginRun, Stream::kBeginRun );
   //bind( &CcenFailuresFilter::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

CcenFailuresFilter::~CcenFailuresFilter()                    // anal5
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
CcenFailuresFilter::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
CcenFailuresFilter::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
CcenFailuresFilter::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
CcenFailuresFilter::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<TriggerL1Data> triggerDecision;
   extract(iFrame.record(Stream::kEvent), triggerDecision);
   if (!triggerDecision->isHadron()  &&
       !triggerDecision->isRadTau()  &&
       !triggerDecision->isElTrack()   ) return ActionBase::kFailed;

   FATable<CcShowerAttributes> ccatts;
   extract(iFrame.record(Stream::kEvent), ccatts);
   FATable<CcShowerAttributes>::const_iterator ccatts_end = ccatts.end();

   double total = 0;
   double e1 = 0;
   for (FATable<CcShowerAttributes>::const_iterator ccatts_iter = ccatts.begin();
	ccatts_iter != ccatts_end;
	ccatts_iter++) {
      double energy = ccatts_iter->energy();
      if (energy > 0.01*m_ebeam.value()  &&
	  ccatts_iter->status()) {
	 total += energy;
	 if (energy > e1) e1 = energy;
      }
   }

   if (e1 > 0.85*m_ebeam.value()) return ActionBase::kFailed;
   if (total < 0.85*2.*m_ebeam.value()) return ActionBase::kFailed;
   // Now you can extract everything

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
CcenFailuresFilter::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
CcenFailuresFilter::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

//
// const member functions
//

//
// static member functions
//
