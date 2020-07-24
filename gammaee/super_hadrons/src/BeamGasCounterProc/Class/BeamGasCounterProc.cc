// -*- C++ -*-
//
// Package:     BeamGasCounterProc
// Module:      BeamGasCounterProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Wed Jan 29 16:23:19 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "BeamGasCounterProc/BeamGasCounterProc.h"
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
static const char* const kFacilityString = "Processor.BeamGasCounterProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_01 $";

//
// static data member definitions
//



//
// constructors and destructor
//
BeamGasCounterProc::BeamGasCounterProc( void )               // anal1
   : Processor( "BeamGasCounterProc" )
   , m_factor( "factor", this, 1.634 )
   , m_factorUncert( "factorUncert", this, 0.043 )
   , m_events(0)
   , m_pos(0)
   , m_neg(0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &BeamGasCounterProc::event,    Stream::kEvent );
   //bind( &BeamGasCounterProc::beginRun, Stream::kBeginRun );
   //bind( &BeamGasCounterProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

BeamGasCounterProc::~BeamGasCounterProc()                    // anal5
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
BeamGasCounterProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
BeamGasCounterProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
   howmany(SYSTEM);

}


// ---------------- standard place to book histograms ---------------
void
BeamGasCounterProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_ne = iHistoManager.histogram(
      100, "Neutral Energy of Positive Excess", 50, 0., 10.);
   m_ne_pos = iHistoManager.histogram(
      110, "Neutral Energy of Positive Events", 50, 0., 10.);
   m_ne_neg = iHistoManager.histogram(
      120, "Neutral Energy of Negative Events", 50, 0., 10.);
   m_pz = iHistoManager.histogram(
      200, "Z Momentum of Positive Excess", 50, -4., 4.);
   m_pz_pos = iHistoManager.histogram(
      210, "Z Momentum of Positive Events", 50, -4., 4.);
   m_pz_neg = iHistoManager.histogram(
      220, "Z Momentum of Negative Events", 50, -4., 4.);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
BeamGasCounterProc::event( Frame& iFrame )          // anal3 equiv.
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

   m_events++;
   if ( charge >= 2 ) {
      m_pos++;
      m_ne->fill(props->neutralEnergy());
      m_ne_pos->fill(props->neutralEnergy());
      m_pz->fill(props->totalMomentumVect().z());
      m_pz_pos->fill(props->totalMomentumVect().z());
   }
   else if ( charge <= -2 ) {
      m_neg++;
      m_ne->fill(props->neutralEnergy(), -m_factor.value());
      m_ne_neg->fill(props->neutralEnergy());
      m_pz->fill(props->totalMomentumVect().z(), -m_factor.value());
      m_pz_neg->fill(props->totalMomentumVect().z());
   }

   if ( m_events % 100 == 0 ) howmany(INFO);

   return ActionBase::kPassed;
}

void BeamGasCounterProc::howmany(Severity severity)
{
   Severity subseverity(severity == INFO ? DEBUG : NOTICE);

   // Some beamgas events have 0, 1, or negative charge.  Correct for
   // this by a factor of all beamgas / positive beamgas:
   //                437/193 = 2.26 +/- 0.20

   double pos(m_pos);
   double neg(m_neg);
   double factor(m_factor.value());
   double factorUncert(m_factorUncert.value());

   report(subseverity, kFacilityString)
      << "pos: " << pos << " neg: " << neg
      << " factor: " << factor << " +/- " << factorUncert << endl;

   report(severity, kFacilityString)
      << "Events: " << m_events
      << " Beamgas: " << 2.26 * (pos - factor*neg) << " +/- "
      << sqrt(sqr(0.20) * sqr(pos - factor*neg) +
	      sqr(factorUncert) * sqr(2.26) * sqr(neg) +
	      pos * sqr(2.26) +
	      neg * sqr(2.26) * sqr(factor))
      << endl;
}

/*
ActionBase::ActionResult
BeamGasCounterProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
BeamGasCounterProc::endRun( Frame& iFrame )         // anal4 equiv.
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
