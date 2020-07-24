// -*- C++ -*-
//
// Package:     JustLookForPhi
// Module:      JustLookForPhi
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Oct 26 12:54:04 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "JustLookForPhi/JustLookForPhi.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"
#include "Navigation/NavElecId.h"
#include "Navigation/NavTkShMatch.h"

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
static const char* const kFacilityString = "Processor.JustLookForPhi" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
JustLookForPhi::JustLookForPhi( void )               // anal1
   : Processor( "JustLookForPhi" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &JustLookForPhi::event,    Stream::kEvent );
   //bind( &JustLookForPhi::beginRun, Stream::kBeginRun );
   //bind( &JustLookForPhi::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

JustLookForPhi::~JustLookForPhi()                    // anal5
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
JustLookForPhi::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
JustLookForPhi::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
JustLookForPhi::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   m_phi1 = iHistoManager.histogram("phi of first track", 100, 0., 2.*M_PI);
   m_phip = iHistoManager.histogram("phi of positive track", 100, 0., 2.*M_PI);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
JustLookForPhi::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   report(SYSTEM, kFacilityString) << "here" << endl;

   // Create a table of tracks and fill it.
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable );

   report(SYSTEM, kFacilityString) << "tracks: " << trackTable.size() << endl;

   if (trackTable.size() != 2) return ActionBase::kFailed;

   bool see_electron = false;
   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();
   FATable< NavTrack >::const_iterator pos = trackTableEnd;
   FATable< NavTrack >::const_iterator neg = trackTableEnd;
   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr ) {
      report(SYSTEM, kFacilityString) << "  track id: " << trackItr->identifier() << endl;
      report(SYSTEM, kFacilityString) << "  track p: " << trackItr->pionFit()->momentum().mag() << endl;
      report(SYSTEM, kFacilityString) << "  track eoverp: ";
      if (trackItr->trackShowerMatch().valid())
	 report(SYSTEM, kFacilityString) << trackItr->trackShowerMatch()->eOverP() << endl;
      else
	 report(SYSTEM, kFacilityString) << "invalid" << endl;
      report(SYSTEM, kFacilityString) << "  track curv: " << trackItr->pionHelix()->curvature() << endl;

//      if (trackItr->elecId().simpleElecId()) see_electron = true;
      if (trackItr->pionFit()->momentum().mag() > 4.  &&  trackItr->trackShowerMatch().valid()  &&
	  trackItr->trackShowerMatch()->eOverP() > 0.5) see_electron = true;
      if (trackItr->pionHelix()->curvature() > 0.)  pos = trackItr;
      else neg = trackItr;
   }

   report(SYSTEM, kFacilityString) << "sawelectron: " << see_electron << endl;

   if (! see_electron  ||  pos == trackTableEnd  ||  neg == trackTableEnd  ||  pos == neg) return ActionBase::kFailed;

   report(SYSTEM, kFacilityString) << "fill1: " << trackTableBegin->pionHelix()->phi0() << endl;
   report(SYSTEM, kFacilityString) << "fillp: " << pos->pionHelix()->phi0() << endl;

   m_phi1->fill(trackTableBegin->pionHelix()->phi0());
   m_phip->fill(pos->pionHelix()->phi0());

   report(SYSTEM, kFacilityString) << "yay!" << endl;

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
JustLookForPhi::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
JustLookForPhi::endRun( Frame& iFrame )         // anal4 equiv.
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
