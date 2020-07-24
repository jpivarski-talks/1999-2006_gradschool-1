// -*- C++ -*-
//
// Package:     CheckTrackEff
// Module:      CheckTrackEff
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri May 14 15:26:54 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "CheckTrackEff/CheckTrackEff.h"
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

#include "CleoDB/DBEventHeader.h"
#include "EventProperties/EventProperties.h"
#include "BeamEnergy/BeamEnergy.h"

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
static const char* const kFacilityString = "Processor.CheckTrackEff" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
CheckTrackEff::CheckTrackEff( void )               // anal1
   : Processor( "CheckTrackEff" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &CheckTrackEff::event,    Stream::kEvent );
   //bind( &CheckTrackEff::beginRun, Stream::kBeginRun );
   //bind( &CheckTrackEff::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

   m_run = 0;
   initialize();

}

CheckTrackEff::~CheckTrackEff()                    // anal5
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
CheckTrackEff::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

   m_run = 0;
   initialize();
}

// -------------------- terminate method ----------------------------
void
CheckTrackEff::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
   summarize();
}


// ---------------- standard place to book histograms ---------------
void
CheckTrackEff::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
CheckTrackEff::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);
   if (head->run() != m_run) {
      if (m_run != 0) summarize();
      m_run = head->run();
   }

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   // Extract tracks
   FATable< NavTrack > tracks   ;
   extract(iFrame.record(Stream::kEvent),  tracks ) ;

   // Loop over tracks in event
   for( FATable< NavTrack >::const_iterator trackItr ( tracks.begin() ) ; 
	trackItr != tracks.end() ; ++trackItr ) 
   {
      // Track identifier
      const UInt32 trackID ( trackItr->identifier() ) ;

      // Seed Track Quality
      FAItem< TRSeedTrackQuality > seedTrackQuality( trackItr->seedQuality() );

      const double nLayers   ( seedTrackQuality->numberLayers() ) ;
      const double nExpected ( seedTrackQuality->numberHitsExpected() ) ;

      const double hitFraction ( nExpected > 0 ? nLayers/nExpected : 0 ) ;

      // Fit Quality
      FAItem< TRTrackFitQuality > pionQuality( trackItr->pionQuality() );

      const DABoolean trackFitOK ( pionQuality->fit()       &&
				   !pionQuality->fitAbort()     );

      const double dof         ( pionQuality->degreesOfFreedom() ) ;
      const double reducedChi2 ( dof > 0 ? pionQuality->chiSquare()/dof : 0 ) ;

      // Particle kinematic parameters
      FAItem< TDKinematicFit > pion ( trackItr->pionFit() ) ;

      GeV          pTk ( pion->momentum().mag() ) ; // track momentum
      const int    qTk ( pion->charge()<0 ? ceil( pion->charge() - 0.5 ) :
			 floor( pion->charge() + 0.5 ) ) ; // electric charge

//       // Energy of matched shower
//       const GeV eTk ( trackItr->trackShowerMatch().valid() ?
// 		      trackItr->trackShowerMatch()->matchedEnergy() : 0 ) ;

      // Helix parameters
      FAItem< TRHelixFit > helix ( trackItr->pionHelix() ) ;

      const double adacd       ( fabs( helix->d0() ) ) ;
      const double az0         ( fabs( helix->position().z() ) ) ;
      const double phi0        ( helix->phi0() ) ;
      const double aCotTheta   ( fabs( helix->cotTheta() ) ) ;
      const double errCotTheta ( sqrt( fabs(
	 helix->errorMatrix()( KTHelix::kCotTheta, KTHelix::kCotTheta ) ) ) ) ;
      const double errz0       ( sqrt( fabs(
	 helix->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) ) ) ) ;
      
      // Apply (loose) track selection criteria
      const DABoolean thisTrackIsGood ( trackFitOK
					&& reducedChi2 < 100.0
					&& hitFraction > 0.5
					&& hitFraction < 1.2
					&& adacd       < 0.03
					&& az0         < 0.18
					&& pTk         > 0.01*eBeam->value()
					&& pTk         < 1.500*eBeam->value()
					&& aCotTheta   < 3.0424 // |cosTh|<0.95
					&& errCotTheta < 0.5
					&& errz0       < 0.25 ) ;               

      m_tracks++;
      if (trackFitOK) m_trackFitOK++;
      if (reducedChi2 < 100.0) m_reducedChi2++;
      if (hitFraction > 0.5) m_hitFraction_low++;
      if (hitFraction < 1.2) m_hitFraction_high++;
      if (adacd       < 0.03) m_adacd++;
      if (az0         < 0.18) m_az0++;
      if (pTk         > 0.01*eBeam->value()) m_pTk_low++;
      if (pTk         < 1.500*eBeam->value()) m_pTk_high++;
      if (aCotTheta   < 3.0424) m_aCotTheta++;
      if (errCotTheta < 0.5) m_errCotTheta++;
      if (errz0       < 0.25) m_errz0++;

      if (props->nbChargedTracks() == 1) {
	 m1_tracks++;
	 if (trackFitOK) m1_trackFitOK++;
	 if (reducedChi2 < 100.0) m1_reducedChi2++;
	 if (hitFraction > 0.5) m1_hitFraction_low++;
	 if (hitFraction < 1.2) m1_hitFraction_high++;
	 if (adacd       < 0.03) m1_adacd++;
	 if (az0         < 0.18) m1_az0++;
	 if (pTk         > 0.01*eBeam->value()) m1_pTk_low++;
	 if (pTk         < 1.500*eBeam->value()) m1_pTk_high++;
	 if (aCotTheta   < 3.0424) m1_aCotTheta++;
	 if (errCotTheta < 0.5) m1_errCotTheta++;
	 if (errz0       < 0.25) m1_errz0++;
      }
      else if (props->nbChargedTracks() == 2) {
	 m2_tracks++;
	 if (trackFitOK) m2_trackFitOK++;
	 if (reducedChi2 < 100.0) m2_reducedChi2++;
	 if (hitFraction > 0.5) m2_hitFraction_low++;
	 if (hitFraction < 1.2) m2_hitFraction_high++;
	 if (adacd       < 0.03) m2_adacd++;
	 if (az0         < 0.18) m2_az0++;
	 if (pTk         > 0.01*eBeam->value()) m2_pTk_low++;
	 if (pTk         < 1.500*eBeam->value()) m2_pTk_high++;
	 if (aCotTheta   < 3.0424) m2_aCotTheta++;
	 if (errCotTheta < 0.5) m2_errCotTheta++;
	 if (errz0       < 0.25) m2_errz0++;
      }
      else if (props->nbChargedTracks() == 3) {
	 m3_tracks++;
	 if (trackFitOK) m3_trackFitOK++;
	 if (reducedChi2 < 100.0) m3_reducedChi2++;
	 if (hitFraction > 0.5) m3_hitFraction_low++;
	 if (hitFraction < 1.2) m3_hitFraction_high++;
	 if (adacd       < 0.03) m3_adacd++;
	 if (az0         < 0.18) m3_az0++;
	 if (pTk         > 0.01*eBeam->value()) m3_pTk_low++;
	 if (pTk         < 1.500*eBeam->value()) m3_pTk_high++;
	 if (aCotTheta   < 3.0424) m3_aCotTheta++;
	 if (errCotTheta < 0.5) m3_errCotTheta++;
	 if (errz0       < 0.25) m3_errz0++;
      }
      else if (props->nbChargedTracks() == 4) {
	 m4_tracks++;
	 if (trackFitOK) m4_trackFitOK++;
	 if (reducedChi2 < 100.0) m4_reducedChi2++;
	 if (hitFraction > 0.5) m4_hitFraction_low++;
	 if (hitFraction < 1.2) m4_hitFraction_high++;
	 if (adacd       < 0.03) m4_adacd++;
	 if (az0         < 0.18) m4_az0++;
	 if (pTk         > 0.01*eBeam->value()) m4_pTk_low++;
	 if (pTk         < 1.500*eBeam->value()) m4_pTk_high++;
	 if (aCotTheta   < 3.0424) m4_aCotTheta++;
	 if (errCotTheta < 0.5) m4_errCotTheta++;
	 if (errz0       < 0.25) m4_errz0++;
      }
      else if (props->nbChargedTracks() == 5) {
	 m5_tracks++;
	 if (trackFitOK) m5_trackFitOK++;
	 if (reducedChi2 < 100.0) m5_reducedChi2++;
	 if (hitFraction > 0.5) m5_hitFraction_low++;
	 if (hitFraction < 1.2) m5_hitFraction_high++;
	 if (adacd       < 0.03) m5_adacd++;
	 if (az0         < 0.18) m5_az0++;
	 if (pTk         > 0.01*eBeam->value()) m5_pTk_low++;
	 if (pTk         < 1.500*eBeam->value()) m5_pTk_high++;
	 if (aCotTheta   < 3.0424) m5_aCotTheta++;
	 if (errCotTheta < 0.5) m5_errCotTheta++;
	 if (errz0       < 0.25) m5_errz0++;
      }

   }

   return ActionBase::kPassed;
}

void CheckTrackEff::summarize()
{
   if (m_tracks > 0) {
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m_trackFitOK = " << (1.0 - double(m_trackFitOK)/double(m_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m_reducedChi2 = " << (1.0 - double(m_reducedChi2)/double(m_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m_hitFraction_low = " << (1.0 - double(m_hitFraction_low)/double(m_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m_hitFraction_high = " << (1.0 - double(m_hitFraction_high)/double(m_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m_adacd = " << (1.0 - double(m_adacd)/double(m_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m_az0 = " << (1.0 - double(m_az0)/double(m_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m_pTk_low = " << (1.0 - double(m_pTk_low)/double(m_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m_pTk_high = " << (1.0 - double(m_pTk_high)/double(m_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m_aCotTheta = " << (1.0 - double(m_aCotTheta)/double(m_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m_errCotTheta = " << (1.0 - double(m_errCotTheta)/double(m_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m_errz0 = " << (1.0 - double(m_errz0)/double(m_tracks)) << endl;
   }

   if (m1_tracks > 0) {
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m1_trackFitOK = " << (1.0 - double(m1_trackFitOK)/double(m1_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m1_reducedChi2 = " << (1.0 - double(m1_reducedChi2)/double(m1_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m1_hitFraction_low = " << (1.0 - double(m1_hitFraction_low)/double(m1_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m1_hitFraction_high = " << (1.0 - double(m1_hitFraction_high)/double(m1_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m1_adacd = " << (1.0 - double(m1_adacd)/double(m1_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m1_az0 = " << (1.0 - double(m1_az0)/double(m1_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m1_pTk_low = " << (1.0 - double(m1_pTk_low)/double(m1_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m1_pTk_high = " << (1.0 - double(m1_pTk_high)/double(m1_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m1_aCotTheta = " << (1.0 - double(m1_aCotTheta)/double(m1_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m1_errCotTheta = " << (1.0 - double(m1_errCotTheta)/double(m1_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m1_errz0 = " << (1.0 - double(m1_errz0)/double(m1_tracks)) << endl;
   }

   if (m2_tracks > 0) {
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m2_trackFitOK = " << (1.0 - double(m2_trackFitOK)/double(m2_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m2_reducedChi2 = " << (1.0 - double(m2_reducedChi2)/double(m2_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m2_hitFraction_low = " << (1.0 - double(m2_hitFraction_low)/double(m2_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m2_hitFraction_high = " << (1.0 - double(m2_hitFraction_high)/double(m2_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m2_adacd = " << (1.0 - double(m2_adacd)/double(m2_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m2_az0 = " << (1.0 - double(m2_az0)/double(m2_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m2_pTk_low = " << (1.0 - double(m2_pTk_low)/double(m2_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m2_pTk_high = " << (1.0 - double(m2_pTk_high)/double(m2_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m2_aCotTheta = " << (1.0 - double(m2_aCotTheta)/double(m2_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m2_errCotTheta = " << (1.0 - double(m2_errCotTheta)/double(m2_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m2_errz0 = " << (1.0 - double(m2_errz0)/double(m2_tracks)) << endl;
   }

   if (m3_tracks > 0) {
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m3_trackFitOK = " << (1.0 - double(m3_trackFitOK)/double(m3_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m3_reducedChi2 = " << (1.0 - double(m3_reducedChi2)/double(m3_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m3_hitFraction_low = " << (1.0 - double(m3_hitFraction_low)/double(m3_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m3_hitFraction_high = " << (1.0 - double(m3_hitFraction_high)/double(m3_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m3_adacd = " << (1.0 - double(m3_adacd)/double(m3_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m3_az0 = " << (1.0 - double(m3_az0)/double(m3_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m3_pTk_low = " << (1.0 - double(m3_pTk_low)/double(m3_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m3_pTk_high = " << (1.0 - double(m3_pTk_high)/double(m3_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m3_aCotTheta = " << (1.0 - double(m3_aCotTheta)/double(m3_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m3_errCotTheta = " << (1.0 - double(m3_errCotTheta)/double(m3_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m3_errz0 = " << (1.0 - double(m3_errz0)/double(m3_tracks)) << endl;
   }

   if (m4_tracks > 0) {
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m4_trackFitOK = " << (1.0 - double(m4_trackFitOK)/double(m4_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m4_reducedChi2 = " << (1.0 - double(m4_reducedChi2)/double(m4_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m4_hitFraction_low = " << (1.0 - double(m4_hitFraction_low)/double(m4_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m4_hitFraction_high = " << (1.0 - double(m4_hitFraction_high)/double(m4_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m4_adacd = " << (1.0 - double(m4_adacd)/double(m4_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m4_az0 = " << (1.0 - double(m4_az0)/double(m4_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m4_pTk_low = " << (1.0 - double(m4_pTk_low)/double(m4_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m4_pTk_high = " << (1.0 - double(m4_pTk_high)/double(m4_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m4_aCotTheta = " << (1.0 - double(m4_aCotTheta)/double(m4_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m4_errCotTheta = " << (1.0 - double(m4_errCotTheta)/double(m4_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m4_errz0 = " << (1.0 - double(m4_errz0)/double(m4_tracks)) << endl;
   }

   if (m5_tracks > 0) {
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m5_trackFitOK = " << (1.0 - double(m5_trackFitOK)/double(m5_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m5_reducedChi2 = " << (1.0 - double(m5_reducedChi2)/double(m5_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m5_hitFraction_low = " << (1.0 - double(m5_hitFraction_low)/double(m5_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m5_hitFraction_high = " << (1.0 - double(m5_hitFraction_high)/double(m5_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m5_adacd = " << (1.0 - double(m5_adacd)/double(m5_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m5_az0 = " << (1.0 - double(m5_az0)/double(m5_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m5_pTk_low = " << (1.0 - double(m5_pTk_low)/double(m5_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m5_pTk_high = " << (1.0 - double(m5_pTk_high)/double(m5_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m5_aCotTheta = " << (1.0 - double(m5_aCotTheta)/double(m5_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m5_errCotTheta = " << (1.0 - double(m5_errCotTheta)/double(m5_tracks)) << endl;
      report(SYSTEM, kFacilityString) << "RUN " << m_run << " m5_errz0 = " << (1.0 - double(m5_errz0)/double(m5_tracks)) << endl;
   }

   initialize();
}

void CheckTrackEff::initialize()
{
   m_tracks = 0;
   m_trackFitOK = 0;
   m_reducedChi2 = 0;
   m_hitFraction_low = 0;
   m_hitFraction_high = 0;
   m_adacd = 0;
   m_az0 = 0;
   m_pTk_low = 0;
   m_pTk_high = 0;
   m_aCotTheta = 0;
   m_errCotTheta = 0;
   m_errz0 = 0;

   m1_tracks = 0;
   m1_trackFitOK = 0;
   m1_reducedChi2 = 0;
   m1_hitFraction_low = 0;
   m1_hitFraction_high = 0;
   m1_adacd = 0;
   m1_az0 = 0;
   m1_pTk_low = 0;
   m1_pTk_high = 0;
   m1_aCotTheta = 0;
   m1_errCotTheta = 0;
   m1_errz0 = 0;

   m2_tracks = 0;
   m2_trackFitOK = 0;
   m2_reducedChi2 = 0;
   m2_hitFraction_low = 0;
   m2_hitFraction_high = 0;
   m2_adacd = 0;
   m2_az0 = 0;
   m2_pTk_low = 0;
   m2_pTk_high = 0;
   m2_aCotTheta = 0;
   m2_errCotTheta = 0;
   m2_errz0 = 0;

   m3_tracks = 0;
   m3_trackFitOK = 0;
   m3_reducedChi2 = 0;
   m3_hitFraction_low = 0;
   m3_hitFraction_high = 0;
   m3_adacd = 0;
   m3_az0 = 0;
   m3_pTk_low = 0;
   m3_pTk_high = 0;
   m3_aCotTheta = 0;
   m3_errCotTheta = 0;
   m3_errz0 = 0;

   m4_tracks = 0;
   m4_trackFitOK = 0;
   m4_reducedChi2 = 0;
   m4_hitFraction_low = 0;
   m4_hitFraction_high = 0;
   m4_adacd = 0;
   m4_az0 = 0;
   m4_pTk_low = 0;
   m4_pTk_high = 0;
   m4_aCotTheta = 0;
   m4_errCotTheta = 0;
   m4_errz0 = 0;

   m5_tracks = 0;
   m5_trackFitOK = 0;
   m5_reducedChi2 = 0;
   m5_hitFraction_low = 0;
   m5_hitFraction_high = 0;
   m5_adacd = 0;
   m5_az0 = 0;
   m5_pTk_low = 0;
   m5_pTk_high = 0;
   m5_aCotTheta = 0;
   m5_errCotTheta = 0;
   m5_errz0 = 0;
}


/*
ActionBase::ActionResult
CheckTrackEff::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
CheckTrackEff::endRun( Frame& iFrame )         // anal4 equiv.
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
