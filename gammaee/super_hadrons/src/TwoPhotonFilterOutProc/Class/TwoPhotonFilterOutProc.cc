// -*- C++ -*-
//
// Package:     TwoPhotonFilterOutProc
// Module:      TwoPhotonFilterOutProc
// 
// Description: Cuts OUT two-photon (non-annihilation hadronic) background, leaving over 99% of the collision events.
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Nov  5 12:06:53 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TwoPhotonFilterOutProc/TwoPhotonFilterOutProc.h"
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
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "Navigation/NavTkShMatch.h"

#include "CleoDB/DBEventHeader.h"
#include "EventProperties/EventProperties.h"
#include "BeamSpot/BeamSpot.h"
#include "CesrCleoComm/CesrBeamEnergy.h"

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
static const char* const kFacilityString = "Processor.TwoPhotonFilterOutProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TwoPhotonFilterOutProc::TwoPhotonFilterOutProc( void )               // anal1
   : Processor( "TwoPhotonFilterOutProc" )
   , m_passed(0)
   , m_total(0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TwoPhotonFilterOutProc::event,    Stream::kEvent );
   bind( &TwoPhotonFilterOutProc::beginRun, Stream::kBeginRun );
   //bind( &TwoPhotonFilterOutProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

TwoPhotonFilterOutProc::~TwoPhotonFilterOutProc()                    // anal5
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
TwoPhotonFilterOutProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TwoPhotonFilterOutProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
   report( SYSTEM, kFacilityString )
      << "Passed " << m_passed << " out of " << m_total
      << " which is " << double(m_passed)/double(m_total)*100 << "%." << endl;
}


// ---------------- standard place to book histograms ---------------
void
TwoPhotonFilterOutProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   const char* label[kEntries] = {
      "pz", "abspz", "energy", "abspperp", "westen", "easten", "bigen", "littleen",
      "npos", "nneg", "nneut"
   };

   m_ntuple = iHistoManager.ntuple(
      1, "ntuple", kEntries, 262144, label );

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TwoPhotonFilterOutProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem< CesrBeamEnergy > eBeam;
   extract( iFrame.record( Stream::kStartRun ), eBeam );

   FAItem< DBEventHeader > header;
   extract( iFrame.record( Stream::kEvent ), header );

   FAItem< EventProperties > props;
   extract( iFrame.record( Stream::kEvent ), props );

   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   FATable< NavShower > showers;
   extract( iFrame.record( Stream::kEvent ), showers );
   FATable< NavShower >::const_iterator showers_end = showers.end();

   double signed_pz_sum(0.);
   double absval_pz_sum(0.);

   double energy_sum(0.);

   double absval_pperp_sum(0.);

   double west_energy_sum(0.);
   double east_energy_sum(0.);

   int npos(0);
   int nneg(0);
   int nneut(0);

   for ( FATable< NavTrack >::const_iterator track_iter = tracks.begin();
	 track_iter != tracks_end;
	 track_iter++ ) {
      if ( ! track_iter->pionQuality()->fitAbort()                             &&
	   track_iter->pionQuality()->degreesOfFreedom() > 0                   &&
	   ( track_iter->pionQuality()->chiSquare() /
	     double( track_iter->pionQuality()->degreesOfFreedom() ) ) < 100.  &&
	   track_iter->pionQuality()->ratioNumberHitsToExpected() > 0.5        &&
	   track_iter->pionQuality()->ratioNumberHitsToExpected() < 1.2        &&
	   abs( track_iter->pionHelix()->d0() ) < 3. * k_cm                    &&
	   abs( track_iter->pionHelix()->z0() ) < 18. * k_cm                   &&
	   track_iter->pionFit()->momentum().mag() > 0.01*eBeam->value()       &&
	   track_iter->pionFit()->momentum().mag() < 1.5*eBeam->value()        &&
	   abs( track_iter->pionHelix()->cotTheta() ) < 3.0424                 &&
	   sqrt( abs( track_iter->pionHelix()->errorMatrix()(
	      KTHelix::kCotTheta, KTHelix::kCotTheta ) ) ) < 50. * k_cm        &&
	   sqrt( abs( track_iter->pionHelix()->errorMatrix()(
	      KTHelix::kZ0, KTHelix::kZ0 ) ) ) < 25. * k_cm                    
	 ) {

	 signed_pz_sum += track_iter->pionFit()->momentum().z();
	 absval_pz_sum += abs( track_iter->pionFit()->momentum().z() );

	 energy_sum += track_iter->pionFit()->energy();

	 absval_pperp_sum += abs( track_iter->pionFit()->momentum().perp() );

	 if ( track_iter->pionFit()->momentum().z() > 0. )
	    west_energy_sum += track_iter->pionFit()->energy();
	 else
	    east_energy_sum += track_iter->pionFit()->energy();

	 if ( track_iter->pionHelix()->curvature() > 0. ) npos++;
	 else nneg++;

      } // end if this is an acceptable charged particle
   } // end loop over tracks

   for ( FATable< NavShower >::const_iterator shower_iter = showers.begin();
	 shower_iter != showers_end;
	 shower_iter++ ) {
      if ( shower_iter->attributes().status()          		       &&   
	   ! shower_iter->attributes().hot()           		       &&
	   shower_iter->attributes().energy() > 0.01*eBeam->value()    &&
	   shower_iter->noTrackMatch()                 		       &&
	   shower_iter->noTrackMatchConReg()           		       &&
	   ( ! shower_iter->bremTrack().valid()  ||
	     ( shower_iter->bremTrack()->trackShowerMatch().valid()  &&
	       shower_iter->bremTrack()->trackShowerMatch()->eOverP() < 0.5 ) )
	 ) {
	 
	 signed_pz_sum += shower_iter->attributes().momentum().z();
	 absval_pz_sum += abs( shower_iter->attributes().momentum().z() );

	 energy_sum += shower_iter->attributes().energy();

	 absval_pperp_sum += abs( shower_iter->attributes().momentum().perp() );

	 if ( shower_iter->attributes().momentum().z() > 0. )
	    west_energy_sum += shower_iter->attributes().energy();
	 else
	    east_energy_sum += shower_iter->attributes().energy();

	 nneut++;

      } // end if this is an acceptable neutral particle
   } // end loop over showers

   float v[kEntries];  for ( int i = 0;  i < kEntries;  i++ ) v[i] = 0.;

   v[kPz] = signed_pz_sum;
   v[kAbsPz] = absval_pz_sum;
   v[kEnergy] = energy_sum;
   v[kAbsPPerp] = absval_pperp_sum;
   v[kWestEnergy] = west_energy_sum;
   v[kEastEnergy] = east_energy_sum;
   double big_energy, little_energy;
   if ( west_energy_sum > east_energy_sum ) {
      big_energy = west_energy_sum;
      little_energy = east_energy_sum;
   }
   else {
      big_energy = east_energy_sum;
      little_energy = west_energy_sum;
   }
   v[kBigEnergy] = big_energy;
   v[kLittleEnergy] = little_energy;
   v[kNPos] = float( npos );
   v[kNNeg] = float( nneg );
   v[kNNeut] = float( nneut );

   m_ntuple->fill( v );

   m_total++;
   if ( m_total % 100 == 0 ) {
      report( INFO, kFacilityString )
	 << "Passed " << m_passed << " out of " << m_total
	 << " which is " << double(m_passed)/double(m_total)*100 << "%." << endl;
   }

   if ( abs( signed_pz_sum ) / absval_pz_sum < 0.999   &&
	energy_sum > 0.1 * 2. * eBeam->value()         &&
	absval_pperp_sum > 0.1 * 2. * eBeam->value()   &&
	little_energy > 0.01                               ) {
      m_passed++;
      return ActionBase::kPassed;
   }
   else
      return ActionBase::kFailed;
}

ActionBase::ActionResult
TwoPhotonFilterOutProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
TwoPhotonFilterOutProc::endRun( Frame& iFrame )         // anal4 equiv.
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
