// -*- C++ -*-
//
// Package:     TestFactor
// Module:      TestFactor
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Wed Jan 29 14:23:43 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TestFactor/TestFactor.h"
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
#include "EventProperties/EventProperties.h"

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
static const char* const kFacilityString = "Processor.TestFactor" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_01 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TestFactor::TestFactor( void )               // anal1
   : Processor( "TestFactor" )
   , m_pos(0)
   , m_neg(0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TestFactor::event,    Stream::kEvent );
   //bind( &TestFactor::beginRun, Stream::kBeginRun );
   //bind( &TestFactor::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

TestFactor::~TestFactor()                    // anal5
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
TestFactor::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TestFactor::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)

   report(SYSTEM, kFacilityString)
      << "The scale factor is " << m_pos << " / " << m_neg << " = "
      << double(m_pos)/double(m_neg) << " +/- "
      << double(m_pos)/double(m_neg)*sqrt(1./double(m_pos) + 1./double(m_neg)) << endl;
}


// ---------------- standard place to book histograms ---------------
void
TestFactor::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_ne_pos = iHistoManager.histogram(
      100, "Positive-Event Neutral Energy", 100, 0., 10.);
   m_ne_neg = iHistoManager.histogram(
      200, "Negative-Event Neutral Energy", 100, 0., 10.);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TestFactor::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);
   if ( ! props.valid() ) return ActionBase::kFailed;

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   if ( ! tracks.valid() ) return ActionBase::kFailed;
   FATable<NavTrack>::const_iterator tracks_begin = tracks.begin();
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();

   int charge(0);
   for ( FATable<NavTrack>::const_iterator track_iter = tracks_begin;
	 track_iter != tracks_end;
	 ++track_iter ) {
      if ( track_iter->pionQuality().valid()                              &&
	   track_iter->pionHelix().valid()                                &&
	   track_iter->pionHelix()->curvature() != 0.                     &&
	   track_iter->pionQuality()->fit()                               &&
	   ! track_iter->pionQuality()->fitAbort()                        &&
	   track_iter->pionQuality()->numberHitsExpected() > 0            &&
	   track_iter->pionQuality()->ratioNumberHitsToExpected() >= 0.3     ) {
	 charge += ( track_iter->pionHelix()->curvature() > 0. ? 1 : -1 );
      } // end if track is okay
   } // end loop over tracks

   if ( charge >= 2 ) {
      if ( props->neutralEnergy() > 4. ) m_pos++;
      m_ne_pos->fill(props->neutralEnergy());
   }
   else if ( charge <= -2 ) {
      if ( props->neutralEnergy() > 4. ) m_neg++;
      m_ne_neg->fill(props->neutralEnergy());
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
TestFactor::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
TestFactor::endRun( Frame& iFrame )         // anal4 equiv.
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
