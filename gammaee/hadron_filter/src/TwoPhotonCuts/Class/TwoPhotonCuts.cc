// -*- C++ -*-
//
// Package:     TwoPhotonCuts
// Module:      TwoPhotonCuts
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Sep 17 15:51:58 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TwoPhotonCuts/TwoPhotonCuts.h"
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
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
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
static const char* const kFacilityString = "Processor.TwoPhotonCuts" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TwoPhotonCuts::TwoPhotonCuts( void )               // anal1
   : Processor( "TwoPhotonCuts" )
   , m_passed( 0 )
   , m_allevents( 0 )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TwoPhotonCuts::event,    Stream::kEvent );
   //bind( &TwoPhotonCuts::beginRun, Stream::kBeginRun );
   //bind( &TwoPhotonCuts::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

TwoPhotonCuts::~TwoPhotonCuts()                    // anal5
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
TwoPhotonCuts::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TwoPhotonCuts::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
   if ( m_allevents > 0 ) {
      report( SYSTEM, kFacilityString )
	 << " ?????????????????????????????????????????????????????????????????????????" << endl
	 << " ?????? Der passen eventovitch = " << m_passed << " / " << m_allevents
	 << " = " << double(m_passed) / double(m_allevents) << " ???????" << endl
	 << " ?????????????????????????????????????????????????????????????????????????" << endl;
   }
}


// ---------------- standard place to book histograms ---------------
void
TwoPhotonCuts::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_num_tracks = iHistoManager.histogram(
      1010, "number of tracks", 30, -0.5, 29.5 );
   m_closest_intersection = iHistoManager.histogram(
      1020, "closest intersection", 100, 0., 0.003 );
   m_weighted_z0 = iHistoManager.histogram(
      1030, "weighted z0", 100, -0.10, 0.10 );
   m_visible_energy = iHistoManager.histogram(
      1040, "visible energy", 100, 0., 12. );
   m_cc_energy = iHistoManager.histogram(
      1050, "calorimeter energy", 100, 0., 12. );
   m_neutral_energy = iHistoManager.histogram(
      1055, "neutral energy", 100, 0., 12. );
   m_biggest_shower = iHistoManager.histogram(
      1060, "biggest shower energy", 100, 0., 6. );
   m_second_biggest_shower = iHistoManager.histogram(
      1070, "second biggest shower energy", 100, 0., 3. );
   m_third_biggest_shower = iHistoManager.histogram(
      1080, "third biggest shower energy", 100, 0., 3. );
   m_biggest_match = iHistoManager.histogram(
      1090, "biggest matched shower energy", 100, 0., 3. );
   m_second_biggest_match = iHistoManager.histogram(
      1100, "second biggest matched shower energy", 100, 0., 3. );
   m_biggest_track = iHistoManager.histogram(
      1110, "biggest track momentum", 100, 0., 6. );
   m_second_track = iHistoManager.histogram(
      1120, "second biggest track momentum", 100, 0., 6. );
   m_sphericity = iHistoManager.histogram(
      1140, "sphericity", 100, 0., 1. );
   m_acoplanarity = iHistoManager.histogram(
      1150, "acoplanarity", 100, 0., M_PI );
   m_num_showers = iHistoManager.histogram(
      1160, "number of showers", 50, -0.5, 49.5 );
   m_totalMomentum_mag = iHistoManager.histogram(
      1170, "event momentum mag", 100, 0., 6. );
   m_totalMomentum_perp = iHistoManager.histogram(
      1180, "event momentum perp", 100, 0., 3. );
   m_totalMomentum_z = iHistoManager.histogram(
      1190, "event momentum z", 100, -5., 5. );
   m_reconstructed_mass = iHistoManager.histogram(
      1200, "reconstructed upsilon mass", 100, 8., 11. );
   m_chargedMomentum_mag = iHistoManager.histogram(
      1210, "charged momentum mag", 100, 0., 6. );
   m_chargedMomentum_perp = iHistoManager.histogram(
      1220, "charged momentum perp", 100, 0., 6. );
   m_chargedMomentum_z = iHistoManager.histogram(
      1230, "charged momentum z", 100, -6., 6. );
   m_charge = iHistoManager.histogram(
      1240, "charge", 31, -15.5, 15.5 );
   m_track_z0 = iHistoManager.histogram(
      1250, "indiv track z0", 100, -0.2, 0.2 );
   m_shifted_track_z0 = iHistoManager.histogram(
      1260, "indiv track z0 - event weighted z0", 100, -0.1, 0.1 );
   m_track_momentum_mag = iHistoManager.histogram(
      1270, "indiv track momentum mag", 100, 0., 3. );
   m_track_momentum_perp = iHistoManager.histogram(
      1280, "indiv track momentum perp", 100, 0., 3. );
   m_track_momentum_z = iHistoManager.histogram(
      1290, "indiv track momentum z", 100, -2., 2. );
   m_shower_energy = iHistoManager.histogram(
      1300, "indiv shower energy", 100, 0., 2. );
   m_second_closest_intersection = iHistoManager.histogram(
      1310, "second closest intersection", 100, 0., 0.004 );
   m_third_closest_intersection = iHistoManager.histogram(
      1320, "third closest intersection", 100, 0., 0.005 );

   m_num_tracks_failed = iHistoManager.histogram(
      2010, "FAILED number of tracks", 30, -0.5, 29.5 );
   m_closest_intersection_failed = iHistoManager.histogram(
      2020, "FAILED closest intersection", 100, 0., 0.003 );
   m_weighted_z0_failed = iHistoManager.histogram(
      2030, "FAILED weighted z0", 100, -0.10, 0.10 );
   m_visible_energy_failed = iHistoManager.histogram(
      2040, "FAILED visible energy", 100, 0., 12. );
   m_cc_energy_failed = iHistoManager.histogram(
      2050, "FAILED calorimeter energy", 100, 0., 12. );
   m_neutral_energy_failed = iHistoManager.histogram(
      2055, "FAILED neutral energy", 100, 0., 12. );
   m_biggest_shower_failed = iHistoManager.histogram(
      2060, "FAILED biggest shower energy", 100, 0., 6. );
   m_second_biggest_shower_failed = iHistoManager.histogram(
      2070, "FAILED second biggest shower energy", 100, 0., 3. );
   m_third_biggest_shower_failed = iHistoManager.histogram(
      2080, "FAILED third biggest shower energy", 100, 0., 3. );
   m_biggest_match_failed = iHistoManager.histogram(
      2090, "FAILED biggest matched shower energy", 100, 0., 3. );
   m_second_biggest_match_failed = iHistoManager.histogram(
      2100, "FAILED second biggest matched shower energy", 100, 0., 3. );
   m_biggest_track_failed = iHistoManager.histogram(
      2110, "FAILED biggest track momentum", 100, 0., 6. );
   m_second_track_failed = iHistoManager.histogram(
      2120, "FAILED second biggest track momentum", 100, 0., 6. );
   m_sphericity_failed = iHistoManager.histogram(
      2140, "FAILED sphericity", 100, 0., 1. );
   m_acoplanarity_failed = iHistoManager.histogram(
      2150, "FAILED acoplanarity", 100, 0., M_PI );
   m_num_showers_failed = iHistoManager.histogram(
      2160, "FAILED number of showers", 50, -0.5, 49.5 );
   m_totalMomentum_mag_failed = iHistoManager.histogram(
      2170, "FAILED event momentum mag", 100, 0., 6. );
   m_totalMomentum_perp_failed = iHistoManager.histogram(
      2180, "FAILED event momentum perp", 100, 0., 3. );
   m_totalMomentum_z_failed = iHistoManager.histogram(
      2190, "FAILED event momentum z", 100, -5., 5. );
   m_reconstructed_mass_failed = iHistoManager.histogram(
      2200, "FAILED reconstructed upsilon mass", 100, 8., 11. );
   m_chargedMomentum_mag_failed = iHistoManager.histogram(
      2210, "FAILED charged momentum mag", 100, 0., 6. );
   m_chargedMomentum_perp_failed = iHistoManager.histogram(
      2220, "FAILED charged momentum perp", 100, 0., 6. );
   m_chargedMomentum_z_failed = iHistoManager.histogram(
      2230, "FAILED charged momentum z", 100, -6., 6. );
   m_charge_failed = iHistoManager.histogram(
      2240, "FAILED charge", 31, -15.5, 15.5 );
   m_track_z0_failed = iHistoManager.histogram(
      2250, "FAILED indiv track z0", 100, -0.2, 0.2 );
   m_shifted_track_z0_failed = iHistoManager.histogram(
      2260, "FAILED indiv track z0 - event weighted z0", 100, -0.1, 0.1 );
   m_track_momentum_mag_failed = iHistoManager.histogram(
      2270, "FAILED indiv track momentum mag", 100, 0., 3. );
   m_track_momentum_perp_failed = iHistoManager.histogram(
      2280, "FAILED indiv track momentum perp", 100, 0., 3. );
   m_track_momentum_z_failed = iHistoManager.histogram(
      2290, "FAILED indiv track momentum z", 100, -2., 2. );
   m_shower_energy_failed = iHistoManager.histogram(
      2300, "FAILED indiv shower energy", 100, 0., 2. );
   m_second_closest_intersection_failed = iHistoManager.histogram(
      2310, "FAILED second closest intersection", 100, 0., 0.004 );
   m_third_closest_intersection_failed = iHistoManager.histogram(
      2320, "FAILED third closest intersection", 100, 0., 0.005 );

   m_weighted_z0_mezzo = iHistoManager.histogram(
      3030, "MEZZO weighted z0", 100, -0.10, 0.10 );
   m_visible_energy_mezzo = iHistoManager.histogram(
      3040, "MEZZO visible energy", 100, 0., 12. );
   m_biggest_shower_mezzo = iHistoManager.histogram(
      3060, "MEZZO biggest shower energy", 100, 0., 6. );
   m_second_biggest_shower_mezzo = iHistoManager.histogram(
      3070, "MEZZO second biggest shower energy", 100, 0., 3. );
   m_biggest_track_mezzo = iHistoManager.histogram(
      3110, "MEZZO biggest track momentum", 100, 0., 6. );
   m_totalMomentum_perp_mezzo = iHistoManager.histogram(
      3180, "MEZZO event momentum perp", 100, 0., 3. );
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TwoPhotonCuts::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem< DBEventHeader > header;
   extract( iFrame.record( Stream::kEvent ), header );

   FAItem< EventProperties > props;
   extract( iFrame.record( Stream::kEvent ), props );

   double charge(0.);

   double weighted_z0(1000.);
   double znumer(0.);
   double zdenom(0.);

   Hep3Vector charged_momentum(0.,0.,0.);
   
   FATable< NavShower > navshowers;
   extract( iFrame.record( Stream::kEvent ), navshowers );
   FATable< NavShower >::const_iterator showers_end = navshowers.end();

   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable );

   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();
   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
      if ( ! trackItr->pionQuality()->fitAbort() )
	 charge += ( trackItr->pionHelix()->curvature() > 0. ? 1. : -1. );

      if ( ! trackItr->seedQuality()->originUsed()            &&  // - I want real z information!
	   ! trackItr->pionQuality()->fitAbort()              &&  // - Don't let the fit fail
	   1./abs(trackItr->pionHelix()->curvature()) > 0.42  &&  // - Diameter must be greater than 42 cm
                                                                  //   to guarantee that it pokes through
                                                                  //   the first stereo superlayer
	   ! trackItr->pionHelix()->hasNullErrorMatrix()          // - I want an error matrix for
                                                                  //   weighted means
	 ) {
	 double z0err2( trackItr->pionHelix()->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) );

	 znumer += trackItr->pionHelix()->z0() / z0err2;
	 zdenom += 1. / z0err2;

	 charged_momentum += trackItr->pionFit()->momentum();
      } // end passes weighted z0 track cuts
   } // end loop over tracks
	 
   if ( zdenom != 0. )
      weighted_z0 = znumer / zdenom;

   double visible_energy(props->eVis());
   double shower1(props->firstLargestEShower());
   double shower2(props->secondLargestEShower());
   double track1(props->firstLargestPTrack());
   double event_pperp(props->totalMomentumVect().perp());
   double charged_pz(charged_momentum.z());

   m_allevents++;
   if ( m_allevents > 0  &&  m_allevents % 100 == 0 ) {
      report( SYSTEM, kFacilityString )
	 << " ?????????????????????????????????????????????????????????????????????????" << endl
	 << " ?????? Der passen eventovitch = " << m_passed << " / " << m_allevents
	 << " = " << double(m_passed) / double(m_allevents) << " ???????" << endl
	 << " ?????????????????????????????????????????????????????????????????????????" << endl;
      report( INFO, kFacilityString )
	 << " ??? Bes-ye heurosite van das Monti Carlile yest bugge ??? " << endl;
   }

   if (
      visible_energy < 7.5     &&
      shower1 < 1.0            &&
      shower2 < 1.0            &&
      track1 < 2.0             &&
      event_pperp < 1.0        &&
      true )
      m_weighted_z0_mezzo->fill( weighted_z0 );
   if (
      abs(weighted_z0) < 0.05  &&
      shower1 < 1.0            &&
      shower2 < 1.0            &&
      track1 < 2.0             &&
      event_pperp < 1.0        &&
      true )
      m_visible_energy_mezzo->fill( props->eVis() );
   if (
      abs(weighted_z0) < 0.05  &&
      visible_energy < 7.5     &&
      shower2 < 1.0            &&
      track1 < 2.0             &&
      event_pperp < 1.0        &&
      true )
      m_biggest_shower_mezzo->fill( props->firstLargestEShower() );
   if (
      abs(weighted_z0) < 0.05  &&
      visible_energy < 7.5     &&
      shower1 < 1.0            &&
      track1 < 2.0             &&
      event_pperp < 1.0        &&
      true )
      m_second_biggest_shower_mezzo->fill( props->secondLargestEShower() );
   if (
      abs(weighted_z0) < 0.05  &&
      visible_energy < 7.5     &&
      shower1 < 1.0            &&
      shower2 < 1.0            &&
      event_pperp < 1.0        &&
      true )
      m_biggest_track_mezzo->fill( props->firstLargestPTrack() );
   if (
      abs(weighted_z0) < 0.05  &&
      visible_energy < 7.5     &&
      shower1 < 1.0            &&
      shower2 < 1.0            &&
      track1 < 2.0             &&
      true )
      m_totalMomentum_perp_mezzo->fill( props->totalMomentumVect().perp() );

//     if ( abs(weighted_z0) < 0.02  &&
//  	visible_energy < 5.0     &&
//  	shower1 < 1.0            &&
//  	shower2 < 0.5            &&
//  	track1 < 1.0             &&
//  	event_pperp < 0.6        &&
//  	abs(charged_pz) > 0.5       )
   if ( abs(weighted_z0) < 0.05  &&
	visible_energy < 7.5     &&
	shower1 < 1.0            &&
	shower2 < 1.0            &&
	track1 < 2.0             &&
	event_pperp < 1.0           )
   {
      m_weighted_z0_failed->fill( weighted_z0 );
      m_visible_energy_failed->fill( props->eVis() );
      m_cc_energy_failed->fill( props->ccTotalEnergy() );
      m_neutral_energy_failed->fill( props->neutralEnergy() );
      m_biggest_shower_failed->fill( props->firstLargestEShower() );
      m_second_biggest_shower_failed->fill( props->secondLargestEShower() );
      m_third_biggest_shower_failed->fill( props->thirdLargestEShower() );
      m_biggest_match_failed->fill( props->firstMatchedEnergy() );
      m_second_biggest_match_failed->fill( props->secondMatchedEnergy() );
      m_biggest_track_failed->fill( props->firstLargestPTrack() );
      m_second_track_failed->fill( props->secondLargestPTrack() );
      m_sphericity_failed->fill( props->sphericity() );
      m_acoplanarity_failed->fill( props->acoplanarity() );
      m_totalMomentum_mag_failed->fill( props->totalMomentumVect().mag() );
      m_totalMomentum_perp_failed->fill( props->totalMomentumVect().perp() );
      m_totalMomentum_z_failed->fill( props->totalMomentumVect().z() );
      m_chargedMomentum_mag_failed->fill( charged_momentum.mag() );
      m_chargedMomentum_perp_failed->fill( charged_momentum.perp() );
      m_chargedMomentum_z_failed->fill( charged_momentum.z() );
      m_charge_failed->fill( charge );

      double massSquared( sqr(props->eVis())
			  - (props->totalMomentumVect() + Hep3Vector(0.025,0.,0.)).mag2() );
      if ( massSquared > 0. )
	 m_reconstructed_mass_failed->fill( sqrt(massSquared) );

      for ( FATable< NavTrack >::const_iterator track_iter = trackTable.begin();
	    track_iter != trackTableEnd;
	    track_iter++ )
      {
	 // Quality cuts for cut-determining helices
	 if ( ! track_iter->pionQuality()->fitAbort()                  // - Just make sure it didn't abort
	      //   (since that might force the track
	      //   through the origin wrongly)
	    ) {
	    m_track_z0_failed->fill( track_iter->pionHelix()->z0() );
	    m_shifted_track_z0_failed->fill( track_iter->pionHelix()->z0() - weighted_z0 );
	    m_track_momentum_mag_failed->fill( track_iter->pionFit()->momentum().mag() );
	    m_track_momentum_perp_failed->fill( track_iter->pionFit()->momentum().perp() );
	    m_track_momentum_z_failed->fill( track_iter->pionFit()->momentum().z() );
	 } // end if passes cut
      } // end loop over tracks

      int num_showers(0);
      for ( FATable< NavShower >::const_iterator shower_iter = navshowers.begin();
	    shower_iter != showers_end;
	    shower_iter++ ) {
	 if ( ! shower_iter->attributes().hot()  &&
	      shower_iter->attributes().energy() > 0.030 ) {
	    m_shower_energy_failed->fill( shower_iter->attributes().energy() );
	    num_showers++;
	 } // end if not hot
      } // end loop over showers
      m_num_showers_failed->fill( num_showers );

      return ActionBase::kFailed;
   }
   else {
      m_passed++;

      m_weighted_z0->fill( weighted_z0 );
      m_visible_energy->fill( props->eVis() );
      m_cc_energy->fill( props->ccTotalEnergy() );
      m_neutral_energy->fill( props->neutralEnergy() );
      m_biggest_shower->fill( props->firstLargestEShower() );
      m_second_biggest_shower->fill( props->secondLargestEShower() );
      m_third_biggest_shower->fill( props->thirdLargestEShower() );
      m_biggest_match->fill( props->firstMatchedEnergy() );
      m_second_biggest_match->fill( props->secondMatchedEnergy() );
      m_biggest_track->fill( props->firstLargestPTrack() );
      m_second_track->fill( props->secondLargestPTrack() );
      m_sphericity->fill( props->sphericity() );
      m_acoplanarity->fill( props->acoplanarity() );
      m_totalMomentum_mag->fill( props->totalMomentumVect().mag() );
      m_totalMomentum_perp->fill( props->totalMomentumVect().perp() );
      m_totalMomentum_z->fill( props->totalMomentumVect().z() );
      m_chargedMomentum_mag->fill( charged_momentum.mag() );
      m_chargedMomentum_perp->fill( charged_momentum.perp() );
      m_chargedMomentum_z->fill( charged_momentum.z() );
      m_charge->fill( charge );

      double massSquared( sqr(props->eVis())
			  - (props->totalMomentumVect() + Hep3Vector(0.025,0.,0.)).mag2() );
      if ( massSquared > 0. )
	 m_reconstructed_mass->fill( sqrt(massSquared) );

      for ( FATable< NavTrack >::const_iterator track_iter = trackTable.begin();
	    track_iter != trackTableEnd;
	    track_iter++ )
      {
	 // Quality cuts for cut-determining helices
	 if ( ! track_iter->pionQuality()->fitAbort()                  // - Just make sure it didn't abort
	      //   (since that might force the track
	      //   through the origin wrongly)
	    ) {
	    m_track_z0->fill( track_iter->pionHelix()->z0() );
	    m_shifted_track_z0->fill( track_iter->pionHelix()->z0() - weighted_z0 );
	    m_track_momentum_mag->fill( track_iter->pionFit()->momentum().mag() );
	    m_track_momentum_perp->fill( track_iter->pionFit()->momentum().perp() );
	    m_track_momentum_z->fill( track_iter->pionFit()->momentum().z() );
	 } // end if passes cut
      } // end loop over tracks

      int num_showers(0);
      for ( FATable< NavShower >::const_iterator shower_iter = navshowers.begin();
	    shower_iter != showers_end;
	    shower_iter++ ) {
	 if ( ! shower_iter->attributes().hot()  &&
	      shower_iter->attributes().energy() > 0.030 ) {
	    m_shower_energy->fill( shower_iter->attributes().energy() );
	    num_showers++;
	 } // end if not hot
      } // end loop over showers
      m_num_showers->fill( num_showers );

      return ActionBase::kPassed;
   }
}

/*
ActionBase::ActionResult
TwoPhotonCuts::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
TwoPhotonCuts::endRun( Frame& iFrame )         // anal4 equiv.
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
