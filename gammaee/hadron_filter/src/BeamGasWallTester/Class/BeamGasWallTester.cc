// -*- C++ -*-
//
// Package:     BeamGasWallTester
// Module:      BeamGasWallTester
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim McCann
// Created:     Fri Feb  8 10:50:41 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "BeamGasWallTester/BeamGasWallTester.h"
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
#include "Navigation/NavConReg.h"
#include "KinematicTrajectory/KTKinematicData.h"
#include "Navigation/NavTkShMatch.h"
#include "C3cc/CcAssignedEnergyHit.h"

#include "CLHEP/Vector/ThreeVector.h"

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
static const char* const kFacilityString = "Processor.BeamGasWallTester" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.25 2002/01/25 20:42:06 ajm36 Exp $";
static const char* const kTagString = "$Name: v06_03_01 $";

//
// static data member definitions
//


//
// constructors and destructor
//
BeamGasWallTester::BeamGasWallTester( void )               // anal1
   : Processor( "BeamGasWallTester" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &BeamGasWallTester::event,    Stream::kEvent );
   //bind( &BeamGasWallTester::beginRun, Stream::kBeginRun );
   //bind( &BeamGasWallTester::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

BeamGasWallTester::~BeamGasWallTester()                    // anal5
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
BeamGasWallTester::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
BeamGasWallTester::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
BeamGasWallTester::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_z0 = iHistoManager.histogram(
      100, "z0", 1000, -1.*k_m, 1.*k_m );
   m_cotTheta = iHistoManager.histogram(
      150, "cotTheta", 100, -2.5, 2.5 );
   m_event_z0 = iHistoManager.histogram(
      200, "event z0", 200, -1.*k_m, 1.*k_m );
   m_event_z0_restrict = iHistoManager.histogram(
      201, "event z0 (restricted)", 200, -1.*k_m, 1.*k_m );
   m_ave_z0 = iHistoManager.histogram(
      250, "weighted ave z0", 200, -1.*k_m, 1.*k_m );
   m_ave_z0_restrict = iHistoManager.histogram(
      251, "weighted ave z0 (restricted)", 200, -1.*k_m, 1.*k_m );
   m_average_charge = iHistoManager.histogram(
      300, "average charge", 100, -2., 2. );
   m_average_charge_v_event_z0 = iHistoManager.profile(
      400, "average charge VS event z0", 20, -1.*k_m, 1.*k_m,
      -100., 100., HIHistProf::kErrorOnMean );
   m_average_charge_v_ave_z0 = iHistoManager.profile(
      450, "average charge VS weighted ave z0", 20, -1.*k_m, 1.*k_m,
      -100., 100., HIHistProf::kErrorOnMean );
   m_average_charge_v_ave_z0_2d = iHistoManager.histogram(
      451, "average charge VS weighted ave z0", 100, -1.*k_m, 1.*k_m,
                                     100, -2., 2. );
   m_cc_energy = iHistoManager.histogram(
      500, "cc energy", 100, 0., 12.*k_GeV );
   m_average_charge_v_cc_energy = iHistoManager.profile(
      510, "average charge VS cc energy", 20, 0., 12.*k_GeV,
      -100., 100., HIHistProf::kErrorOnMean );
   m_ave_z0_v_cc_energy = iHistoManager.profile(
      520, "abs( weighted ave z0 ) VS cc energy", 20, 0., 12.*k_GeV,
      -1.*k_m, 1.*k_m, HIHistProf::kErrorOnMean );
   m_ave_z0_v_cc_energy_2d = iHistoManager.histogram(
      521, "weighted ave z0 VS cc energy", 100, 0., 12.*k_GeV,
                                  100, -1.*k_m, 1.*k_m );
   m_total_energy = iHistoManager.histogram(
      600, "total energy", 100, 0., 12.*k_GeV );
   m_average_charge_v_total_energy = iHistoManager.profile(
      610, "average charge VS total energy", 20, 0., 12.*k_GeV,
      -100., 100., HIHistProf::kErrorOnMean );
   m_ave_z0_v_total_energy = iHistoManager.profile(
      620, "abs( weighted ave z0 ) VS total energy", 20, 0., 12.*k_GeV,
      -1.*k_m, 1.*k_m, HIHistProf::kErrorOnMean );
   m_ave_z0_v_total_energy_2d = iHistoManager.histogram(
      621, "weighted ave z0 VS total energy", 100, 0., 12.*k_GeV,
                                  100, -1.*k_m, 1.*k_m );
   m_event_z_momentum = iHistoManager.histogram(
      700, "event z momentum", 100, -7.*k_GeV, 7.*k_GeV );
   m_average_charge_v_event_z_momentum = iHistoManager.profile(
      710, "average charge VS event z momentum", 20, -7.*k_GeV, 7.*k_GeV,
      -100., 100., HIHistProf::kErrorOnMean );
   m_ave_z0_v_event_z_momentum = iHistoManager.profile(
      720, "abs( weighted ave z0 ) VS event z momentum", 20, -7.*k_GeV, 7.*k_GeV,
      -1.*k_m, 1.*k_m, HIHistProf::kErrorOnMean );
   m_ave_z0_v_event_z_momentum_2d = iHistoManager.histogram(
      721, "weighted ave z0 VS event z momentum", 100, -7.*k_GeV, 7.*k_GeV,
                                         100, -1.*k_m, 1.*k_m );
   m_event_mag_momentum = iHistoManager.histogram(
      800, "event momentum", 100, 0., 7.*k_GeV );
   m_average_charge_v_event_mag_momentum = iHistoManager.profile(
      810, "average charge VS event momentum", 20, 0., 7.*k_GeV,
      -100., 100., HIHistProf::kErrorOnMean );
   m_ave_z0_v_event_mag_momentum = iHistoManager.profile(
      820, "abs( weighted ave z0 ) VS event momentum", 20, 0., 7.*k_GeV,
      -1.*k_m, 1.*k_m, HIHistProf::kErrorOnMean );
   m_ave_z0_v_event_mag_momentum_2d = iHistoManager.histogram(
      821, "weighted ave z0 VS event momentum", 100, 0., 7.*k_GeV,
                                       100, -1.*k_m, 1.*k_m );
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
BeamGasWallTester::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   int bad_showers( 0 );
   int unmatched_showers( 0 );
   int matched_showers( 0 );
   int good_tracks( 0 );
   int bad_tracks( 0 );

   double cc_energy( 0. );
   double total_energy( 0. );
   Hep3Vector total_momentum( 0., 0., 0. );
   double event_charge( 0. );
   double sum_z0( 0. );
   double sum_z0_weights( 0. );

   // Create a table of showers and fill it.
   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ), showerTable );
   FATable< NavShower >::const_iterator showerTableBegin
      = showerTable.begin();
   FATable< NavShower >::const_iterator showerTableEnd
      = showerTable.end();

   for ( FATable< NavShower >::const_iterator showerItr = showerTableBegin;
	 showerItr != showerTableEnd;
	 showerItr++ ) {
      report( INFO, kFacilityString ) << "Shower " << showerItr->identifier();

      const CcShowerAttributes& atts( showerItr->attributes() );
      if ( !( atts.goodBarrel()  ||  atts.goodEndcap() )  ||
	   atts.energy() < 100*k_MeV                      ||
	   false ) {
	 report( INFO, kFacilityString ) << " (bad shower)" << endl;
	 bad_showers++;
	 continue;
      } else {
	 report( INFO, kFacilityString ) << endl;
      }

      if ( showerItr->noTrackMatch() ) {
	 unmatched_showers++;
	 total_energy += atts.energy();
	 total_momentum += atts.momentum();
	 report( INFO, kFacilityString ) << "    unmatched" << endl;
      } else {
	 matched_showers++;
	 report( INFO, kFacilityString ) << "    matched!" << endl;
      }

      report( INFO, kFacilityString ) << "    energy = " << cc_energy << endl;
      cc_energy += atts.energy();

   } // end loop over showers

   // Create a table of tracks and fill it.
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable );

   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();
   // Loop over tracks.
   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr ) {
      // Ask for the pion fit and quality information.
      FAItem< TDKinematicFit > pionFit = (*trackItr).pionFit();
      FAItem< TRHelixFit > pionHelix = (*trackItr).pionHelix();
      FAItem< TRTrackFitQuality > pionQuality = (*trackItr).pionQuality();
      FAItem< TRSeedTrackQuality > seedQuality = (*trackItr).seedQuality();

      report( INFO, kFacilityString ) << "Track " << trackItr->identifier();
      if ( seedQuality->numberHitsExpected() == 0     ||
	   seedQuality->originUsed()                  ||
	   pionQuality->fitAbort()                    ||
	   // this is temporary
//	   pionFit->momentum().mag() < 500.*k_MeV     ||
	   false ) {
	 report( INFO, kFacilityString ) << " (bad track)" << endl;
	 bad_tracks++;
	 continue;
      } else {
	 report( INFO, kFacilityString ) << endl;
	 good_tracks++;
      }

      double z0( pionHelix->z0() );
      double z0_weight( 1./ abs(
	 pionHelix->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 )
	 ) );

      m_z0->fill( z0 );
      m_cotTheta->fill( pionHelix->cotTheta() );

      report( INFO, kFacilityString )
	 << "    z0 = " << z0 << endl
	 << "    z0err = " << 1. / sqrt( z0_weight ) << endl
	 << "    cotTheta = " << pionHelix->cotTheta() << endl
	 << "    momentum = " << pionFit->momentum() << endl
	 ;

      sum_z0 += z0 * z0_weight;
      sum_z0_weights += z0_weight;

      total_energy += pionFit->energy();
      total_momentum += pionFit->momentum();
      event_charge += ( pionHelix->curvature() > 0. ? 1. : -1. );
      
   } // end loop over tracks

   double weighted_ave_z0( sum_z0 / sum_z0_weights );
   double weighted_ave_z0_err( sqrt( 1. / sum_z0_weights ) );

   double event_z_momentum( total_momentum.z() );
   double event_mag_momentum( total_momentum.mag() );
   double average_charge( good_tracks > 0 ?
			  event_charge / double( good_tracks ) : 100. );

   m_ave_z0->fill( weighted_ave_z0 );
   if ( abs( weighted_ave_z0 ) > 25*k_mm ) {
      m_ave_z0_restrict->fill( weighted_ave_z0 );
   }
   m_average_charge->fill( average_charge );
   m_average_charge_v_ave_z0->fill( weighted_ave_z0, average_charge );
   m_average_charge_v_ave_z0_2d->fill( weighted_ave_z0, average_charge );
   m_cc_energy->fill( cc_energy );
   m_average_charge_v_cc_energy->fill( cc_energy, average_charge );
   m_ave_z0_v_cc_energy->fill( cc_energy, abs( weighted_ave_z0 ) );
   m_ave_z0_v_cc_energy_2d->fill( cc_energy, weighted_ave_z0 );
   m_total_energy->fill( total_energy );
   m_average_charge_v_total_energy->fill( total_energy, average_charge );
   m_ave_z0_v_total_energy->fill( total_energy, abs( weighted_ave_z0 ) );
   m_ave_z0_v_total_energy_2d->fill( total_energy, weighted_ave_z0 );
   m_event_z_momentum->fill( event_z_momentum );
   m_average_charge_v_event_z_momentum->fill( event_z_momentum,
					      average_charge );
   m_ave_z0_v_event_z_momentum->fill( event_z_momentum,
				      abs( weighted_ave_z0 ) );
   m_ave_z0_v_event_z_momentum_2d->fill( event_z_momentum, weighted_ave_z0 );
   m_event_mag_momentum->fill( event_mag_momentum );
   m_average_charge_v_event_mag_momentum->fill( event_mag_momentum,
						average_charge );
   m_ave_z0_v_event_mag_momentum->fill( event_mag_momentum,
					abs( weighted_ave_z0 ) );
   m_ave_z0_v_event_mag_momentum_2d->fill( event_mag_momentum,
					   weighted_ave_z0 );

   report( INFO, kFacilityString )
      << "bad showers = " << bad_showers << endl
      << "unmatched showers = " << unmatched_showers << endl
      << "matched showers = " << matched_showers << endl
      << "bad tracks = " << bad_tracks << endl
      << "good tracks = " << good_tracks << endl
      << "cc energy = " << cc_energy << " GeV" << endl
      << "total energy = " << total_energy << " GeV" << endl
      << "total momentum = " << total_momentum << " GeV/c" << endl
      << "weighted ave z0 = " << weighted_ave_z0 << " m" << endl
      << "event charge = " << event_charge << " e" << endl
      << "average charge = " << average_charge << " e" << endl
      ;

   report( NOTICE, kFacilityString )
      << "JIMMY_NTUPLE " << weighted_ave_z0 << " "
      << cc_energy << " " << event_charge << " " << average_charge << endl;

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
BeamGasWallTester::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
BeamGasWallTester::endRun( Frame& iFrame )         // anal4 equiv.
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
