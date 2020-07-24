// -*- C++ -*-
//
// Package:     Y3sHadronFilter
// Module:      Y3sHadronFilter
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim McCann
// Created:     Tue Jan 15 12:48:50 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Y3sHadronFilter/Y3sHadronFilter.h"
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
#include "Navigation/NavTkShMatch.h"

#include "C3Mu/MuTrack.h"

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
static const char* const kFacilityString = "Processor.Y3sHadronFilter" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.24 2001/11/14 15:22:17 ajm36 Exp $";
static const char* const kTagString = "$Name: v06_02_01 $";

//
// static data member definitions
//


//
// constructors and destructor
//
Y3sHadronFilter::Y3sHadronFilter( void )               // anal1
   : Processor( "Y3sHadronFilter" )
   , m_beamspot_x( "beamspot_x", this, 0.35 )
   , m_beamspot_y( "beamspot_y", this, 0.87 )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Y3sHadronFilter::event,    Stream::kEvent );
   //bind( &Y3sHadronFilter::beginRun, Stream::kBeginRun );
   //bind( &Y3sHadronFilter::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

Y3sHadronFilter::~Y3sHadronFilter()                    // anal5
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
Y3sHadronFilter::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Y3sHadronFilter::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
Y3sHadronFilter::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_hist_showers = iHistoManager.histogram(
      50, "number of (good) showers", 41, -0.5, 40.5 );
   m_hist_unmatched_showers = iHistoManager.histogram(
      100, "unmatched showers", 21, -0.5, 20.5 );
   m_hist_tracks = iHistoManager.histogram(
      200, "number of (good) tracks", 21, -0.5, 20.5 );
   m_hist_showers_and_tracks = iHistoManager.histogram(
      300, "showers + tracks", 41, -0.5, 40.5 );
   m_hist_unmatched_showers_and_tracks = iHistoManager.histogram(
      350, "unmatched showers + tracks", 41, -0.5, 40.5 );
   m_hist_shower_mass = iHistoManager.histogram(
      355, "shower mass", 1000, 0., 300.*k_MeV );
   m_hist_shower_energy = iHistoManager.histogram(
      375, "shower energy", 1000, 0., 3.*k_GeV );
   m_hist_charge = iHistoManager.histogram(
      400, "event charge", 21, -10.5, 10.5 );
   m_hist_charge_vs_tracks = iHistoManager.histogram(
      500, "charge vs tracks", 21, -0.5, 20.5, 21, -10.5, 10.5 );
   m_hist_momentum_xy = iHistoManager.histogram(
      600, "momentum Y vs X", 100, -3.*k_GeV, 3.*k_GeV,
                              100, -3.*k_GeV, 3.*k_GeV );
   m_hist_twotrack_momentum_xy = iHistoManager.histogram(
      601, "two-track momentum Y vs X", 100, -3.*k_GeV, 3.*k_GeV,
                                        100, -3.*k_GeV, 3.*k_GeV );
   m_hist_momentum_z = iHistoManager.histogram(
      700, "momentum Z", 100, -4.*k_GeV, 4.*k_GeV );
   m_hist_twotrack_momentum_z = iHistoManager.histogram(
      701, "two-track momentum Z", 100, -4.*k_GeV, 4.*k_GeV );
   m_hist_energy = iHistoManager.histogram(
      725, "event energy", 1000, 0.*k_GeV, 12.*k_GeV );
   m_hist_track_momentum = iHistoManager.histogram(
      750, "track momentum", 100, 0., 6.*k_GeV );
   m_hist_track_d0 = iHistoManager.histogram(
      800, "track d0", 200, -3.*k_mm, 3.*k_mm );
   m_hist_track_d0_vs_phi0 = iHistoManager.histogram(
      850, "track d0 vs phi0", 314, 0., 2.*M_PI,
                               200, -3.*k_mm, 3.*k_mm );
   m_hist_track_z0 = iHistoManager.histogram(
      900, "track z0", 200, -5.*k_cm, 5.*k_cm );
   m_hist_twotrack_Ep = iHistoManager.histogram(
      1000, "two-track E/p positive VS negative", 142, 0., 1.42,
                                                  142, 0., 1.42 );
   m_hist_twotrack_dpthmu = iHistoManager.histogram(
      1100, "two-track dpthmu positive VS negative", 150, 0., 15.,
                                                     150, 0., 15. );

   const char* eventvars_labels[ 9 ] =
   { "showers", "nomatch", "goodtr", "badtr", "charge", "px", "py", "pz",
     "energy" };

   m_eventvars = iHistoManager.ntuple(
      1, "event", 9, 262144, eventvars_labels );

   const char* twotrack_eventvars_labels[ 6 ] =
   { "epos", "eneg", "ppos", "pneg", "mupos", "muneg" };

   m_twotrack_eventvars = iHistoManager.ntuple(
      2, "twotrack", 6, 262144, twotrack_eventvars_labels );

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Y3sHadronFilter::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   int num_showers( 0 );
   int num_unmatched_showers( 0 );
   int num_tracks( 0 );
   int num_bad_tracks( 0 );
   int total_charge( 0 );
   Hep3Vector total_momentum( 2.61*k_cm, 0., 0. );
   double total_energy( 0. );
   UInt16 pos_id( 0 );
   UInt16 neg_id( 0 );
   double pos_momentum( 0. );
   double neg_momentum( 0. );

   // Create a table of showers and fill it.
   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ), showerTable );
   FATable< NavShower >::const_iterator showerTableBegin
      = showerTable.begin();
   FATable< NavShower >::const_iterator showerTableEnd
      = showerTable.end();

   for ( FATable< NavShower >::const_iterator showerItr = showerTableBegin;
	 showerItr != showerTableEnd;
	 showerItr++ )
   {
      const CcShowerAttributes& atts( showerItr->attributes() );
      if ( ( atts.goodBarrel()  ||  atts.goodEndcap() )  &&
	   atts.energy() > 100*k_MeV  &&
	   true )
      {
	 num_showers++;
	 total_energy += atts.energy();

	 m_hist_shower_energy->fill( atts.energy() );
	 m_hist_shower_mass->fill( atts.mass() );
      }
   
      if ( ( atts.goodBarrel()  ||  atts.goodEndcap() )  &&
	   atts.energy() > 100*k_MeV  &&
	   showerItr->noTrackMatch()  &&
	   true )
      {
	 num_unmatched_showers++;
	 total_momentum += atts.momentum();
      } // end passes shower cuts
   } // end loop over showers

   // Create a table of tracks and fill it.
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ), trackTable );
   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();

   // Loop over tracks.
   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
      // Ask for the pion fit and quality information.
      FAItem< TDKinematicFit > pionFit = trackItr->pionFit();
      FAItem< TRHelixFit > pionHelix = trackItr->pionHelix();
      FAItem< TRTrackFitQuality > pionQuality = trackItr->pionQuality();
      FAItem< TRSeedTrackQuality > seedQuality = trackItr->seedQuality();

      TRHelixFit local_helix = (* pionHelix );
      Meters move_length;
      KTHelix::MoveStatus move_status =
	 local_helix.moveToReferencePoint(
	    HepPoint3D( m_beamspot_x.value()*k_mm,
			m_beamspot_y.value()*k_mm, 0. ), move_length );
      Meters d0 = local_helix.d0();
      double phi0 = local_helix.phi0();
      Meters z0 = local_helix.z0();

//        // Now apply some of the standard rare-B analysis cuts.
//        if ( seedQuality->numberHitsExpected() == 0 )
//        {
//           report( WARNING, kFacilityString )
//              <<"Number of Hits expected is zero, skipping this track!" 
//  	    << endl;   
//           continue;
//        }

      float hit_fraction = pionQuality->ratioNumberHitsToExpected();
      double cos_theta = pionFit->momentum().cosTheta();

      if ( !pionQuality->fitAbort()  &&      // not an aborted fit
           !seedQuality->originUsed()  &&    // not a "z-escape"
           ( pionFit->pmag() <= 6.*k_GeV )  &&
           ( pionFit->pmag() > 100.*k_MeV )  &&
           ( hit_fraction >= 0.3 )  &&
           ( abs( cos_theta ) <= 0.9 )  &&
  	   abs( d0 ) < 3.*k_mm  &&           // 2D beamspot cut
  	   abs( z0 ) < 5.*k_cm  &&           // z beamspot cut
	   true )
      {
	 num_tracks++;
	 int charge = ( pionHelix->curvature() > 0. ? 1 : -1 );
	 total_charge += charge;
	 total_momentum += pionFit->momentum();

	 if ( charge ==  1 ) {
	    pos_id = trackItr->identifier();
	    pos_momentum = pionFit->momentum().mag();
	 }
	 if ( charge == -1 ) {
	    neg_id = trackItr->identifier();
	    neg_momentum = pionFit->momentum().mag();
	 }

	 m_hist_track_momentum->fill( pionFit->momentum().mag() );
	 m_hist_track_d0->fill( d0 );
	 m_hist_track_d0_vs_phi0->fill( phi0, d0 );
	 m_hist_track_z0->fill( z0 );

      } // end passes track quality cuts
      else { num_bad_tracks++; }
   } // end loop over tracks

   m_hist_showers->fill( float( num_showers ) );
   m_hist_unmatched_showers->fill( float( num_unmatched_showers ) );
   m_hist_tracks->fill( float( num_tracks ) );
   m_hist_showers_and_tracks->fill(
      float( num_showers + num_tracks ) );
   m_hist_unmatched_showers_and_tracks->fill(
      float( num_unmatched_showers + num_tracks ) );
   m_hist_charge->fill( float( total_charge ) );
   m_hist_charge_vs_tracks->fill( num_tracks, total_charge );
   m_hist_momentum_xy->fill( total_momentum.x(), total_momentum.y() );
   m_hist_momentum_z->fill( total_momentum.z() );
   m_hist_energy->fill( total_energy );

   float eventvars[ 9 ] = { float( num_showers ),
			    float( num_unmatched_showers ),
			    float( num_tracks ),
			    float( num_bad_tracks ),
			    float( total_charge ),
			    total_momentum.x(), total_momentum.y(),
			    total_momentum.z(),
			    total_energy };
   m_eventvars->fill( eventvars );

   if ( num_tracks == 2  &&  total_charge == 0 )
   {
      m_hist_twotrack_momentum_xy->fill(
	 total_momentum.x(), total_momentum.y() );
      m_hist_twotrack_momentum_z->fill( total_momentum.z() );

      FATable< MuTrack > muTrackTable;
      report( DEBUG, kFacilityString )
	 << "asking for FATable< MuTrack >" << endl;
      extract( iFrame.record( Stream::kEvent ), muTrackTable );
      report( DEBUG, kFacilityString ) << "success!" << endl;

      double pos_dpthmu( 0. );
      double neg_dpthmu( 0. );

      for ( FATable< MuTrack >::const_iterator muTrackItr
	       = muTrackTable.begin();
	    muTrackItr != muTrackTable.end();
	    muTrackItr++ )
      {
	 if ( muTrackItr->identifier() == pos_id )
	    pos_dpthmu = muTrackItr->dpthmu();
	 if ( muTrackItr->identifier() == neg_id )
	    neg_dpthmu = muTrackItr->dpthmu();
      } // end loop over mu tracks

      m_hist_twotrack_dpthmu->fill( neg_dpthmu, pos_dpthmu );

      double pos_energy( 0. );
      double neg_energy( 0. );
      DABoolean pos_energy_exists( false );
      DABoolean neg_energy_exists( false );

      for ( FATable< NavShower >::const_iterator showerItr
	       = showerTableBegin;
	    showerItr != showerTableEnd;
	    showerItr++ )
      {
	 const CcShowerAttributes& atts( showerItr->attributes() );
	 if ( ( atts.goodBarrel()  ||  atts.goodEndcap() )  &&
	      atts.energy() > 100*k_MeV  &&
	      ! showerItr->noTrackMatch()  &&
	      true )
	 {
	    FATable< NavTkShMatch > trackMatchTable
	       = showerItr->trackMatches();

	    if ( trackMatchTable.size() == 1 )
	    {
	       FATable< NavTkShMatch >::const_iterator trackMatchItr
		  = trackMatchTable.begin();

	       if ( trackMatchItr->identifier() == pos_id ) {
		  pos_energy = trackMatchItr->matchedEnergy();
		  pos_energy_exists = true; }

	       if ( trackMatchItr->identifier() == neg_id ) {
		  neg_energy = trackMatchItr->matchedEnergy();
		  neg_energy_exists = true; }
	    } // end if shower matches only one track
	 } // end if the shower is a good one with a track match
      } // end loop over all showers
	 
      if ( pos_energy_exists && neg_energy_exists  &&
	   pos_momentum != 0.  &&  neg_momentum != 0. )
	 m_hist_twotrack_Ep->fill( neg_energy / neg_momentum,
				   pos_energy / pos_momentum );

      float twotrack_eventvars[ 6 ] = { pos_energy,
					neg_energy,
					pos_momentum,
					neg_momentum,
					pos_dpthmu,
					neg_dpthmu };
      m_twotrack_eventvars->fill( twotrack_eventvars );

   } // end if there are only two tracks
   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
Y3sHadronFilter::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Y3sHadronFilter::endRun( Frame& iFrame )         // anal4 equiv.
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
