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
// Created:     Wed Dec 11 11:19:45 EST 2002
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

#include "BeamSpot/BeamSpot.h"
#include "CleoDB/DBEventHeader.h"
#include "EventProperties/EventProperties.h"
#include "Navigation/NavTrack.h"
#include "Navigation/NavShower.h"
#include "Navigation/NavTkShMatch.h"
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
static const char* const kFacilityString = "Processor.BeamGasCounterProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
BeamGasCounterProc::BeamGasCounterProc( void )               // anal1
   : Processor( "BeamGasCounterProc" )
   , m_total(0)
   , m_Rpos_fore(0)
   , m_Rpos_back(0)
   , m_Rneg_fore(0)
   , m_Rneg_back(0)
   , m_Rpos_neut(0)
   , m_Rneg_neut(0)
   , m_Lpos_fore(0)
   , m_Lpos_back(0)
   , m_Lneg_fore(0)
   , m_Lneg_back(0)
   , m_Lpos_neut(0)
   , m_Lneg_neut(0)
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
 
   calc_beamgas_events(SYSTEM);
}

// ---------------- standard place to book histograms ---------------
void
BeamGasCounterProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_vertex_zqual_neg = iHistoManager.histogram(
      10, "vertex zqual (neg)", 100, 0., 1.*k_cm );
   m_vertex_zqual_pos = iHistoManager.histogram(
      15, "vertex zqual (pos)", 100, 0., 1.*k_cm );
   m_vertex_perp_neg = iHistoManager.histogram(
      20, "vertex perp (neg)", 100, 0., 3.*k_cm );
   m_vertex_perp_pos = iHistoManager.histogram(
      25, "vertex perp (pos)", 100, 0., 3.*k_cm );
   m_perp_from_vertex_neg = iHistoManager.histogram(
      30, "perp from vertex (neg)", 100, 0., 10.*k_mm );
   m_perp_from_vertex_pos = iHistoManager.histogram(
      35, "perp from vertex (pos)", 100, 0., 10.*k_mm );

   m_event_charge = iHistoManager.histogram(
      100, "event charge", 21, -10.5, 10.5 );
   m_event_charge_trkman = iHistoManager.histogram(
      200, "event charge with Trkman", 21, -10.5, 10.5 );
   m_event_charge_trkman_vertex = iHistoManager.histogram(
      300, "event charge with Trkman and primary vertex only (intersection within 3mm)", 21, -10.5, 10.5 );

   m_event_pz_Rpos = iHistoManager.histogram(
      1100, "event momentum z for POSITIVE events (Trkman Q.ge.2)", 100, -6., 6. );
   m_event_pz_Rneg = iHistoManager.histogram(
      1200, "event momentum z for NEGATIVE events (Trkman Q.le.-2)", 100, -6., 6. );

   m_event_neutral_energy_Rpos = iHistoManager.histogram(
      2100, "neutral energy for POSITIVE events (Trkman Q.ge.2)", 100, 0., 12. );
   m_event_neutral_energy_Rneg = iHistoManager.histogram(
      2200, "neutral energy for NEGATIVE events (Trkman Q.le.-2)", 100, 0., 12. );

   m_event_pz_Lpos = iHistoManager.histogram(
      1101, "event momentum z for POSITIVE events (Trkman Q.ge.2)", 100, -6., 6. );
   m_event_pz_Lneg = iHistoManager.histogram(
      1201, "event momentum z for NEGATIVE events (Trkman Q.le.-2)", 100, -6., 6. );

   m_event_neutral_energy_Lpos = iHistoManager.histogram(
      2101, "neutral energy for POSITIVE events (Trkman+vertex Q.ge.2)", 100, 0., 12. );
   m_event_neutral_energy_Lneg = iHistoManager.histogram(
      2201, "neutral energy for NEGATIVE events (Trkman+vertex Q.le.-2)", 100, 0., 12. );

   m_num_tracks_Rpos = iHistoManager.histogram(
      11010, "number of tracks Rpos", 30, -0.5, 29.5 );
   m_weighted_z0_Rpos = iHistoManager.histogram(
      11030, "weighted z0 Rpos", 100/4, -0.10, 0.10 );
   m_visible_energy_Rpos = iHistoManager.histogram(
      11040, "visible energy Rpos", 100/4, 0., 12. );
   m_cc_energy_Rpos = iHistoManager.histogram(
      11050, "calorimeter energy Rpos", 100/4, 0., 12. );
   m_neutral_energy_Rpos = iHistoManager.histogram(
      11055, "neutral energy Rpos", 100/4, 0., 12. );
   m_biggest_shower_Rpos = iHistoManager.histogram(
      11060, "biggest shower energy Rpos", 100/2, 0., 6. );
   m_biggest_match_Rpos = iHistoManager.histogram(
      11090, "biggest matched shower energy Rpos", 100/2, 0., 3. );
   m_biggest_track_Rpos = iHistoManager.histogram(
      11110, "biggest track momentum Rpos", 100/2, 0., 6. );
   m_sphericity_Rpos = iHistoManager.histogram(
      11140, "sphericity Rpos", 100/4, 0., 1. );
   m_acoplanarity_Rpos = iHistoManager.histogram(
      11150, "acoplanarity Rpos", 100/4, 0., M_PI );
   m_num_showers_Rpos = iHistoManager.histogram(
      11160, "number of showers Rpos", 50, -0.5, 49.5 );
   m_totalMomentum_mag_Rpos = iHistoManager.histogram(
      11170, "event momentum mag Rpos", 100/4, 0., 6. );
   m_totalMomentum_perp_Rpos = iHistoManager.histogram(
      11180, "event momentum perp Rpos", 100/4, 0., 3. );
   m_totalMomentum_z_Rpos = iHistoManager.histogram(
      11190, "event momentum z Rpos", 100/4, -5., 5. );
   m_track_z0_Rpos = iHistoManager.histogram(
      11250, "indiv track z0 Rpos", 100, -0.2, 0.2 );
   m_shifted_track_z0_Rpos = iHistoManager.histogram(
      11260, "indiv track z0 - event weighted z0 Rpos", 100, -0.1, 0.1 );
   m_track_momentum_mag_Rpos = iHistoManager.histogram(
      11270, "indiv track momentum mag Rpos", 100, 0., 3. );
   m_track_momentum_perp_Rpos = iHistoManager.histogram(
      11280, "indiv track momentum perp Rpos", 100, 0., 3. );
   m_track_momentum_z_Rpos = iHistoManager.histogram(
      11290, "indiv track momentum z Rpos", 100, -2., 2. );
   m_shower_energy_Rpos = iHistoManager.histogram(
      11300, "indiv shower energy Rpos", 100, 0., 2. );

   m_num_tracks_Rneg = iHistoManager.histogram(
      21010, "number of tracks Rneg", 30, -0.5, 29.5 );
   m_weighted_z0_Rneg = iHistoManager.histogram(
      21030, "weighted z0 Rneg", 100/4, -0.10, 0.10 );
   m_visible_energy_Rneg = iHistoManager.histogram(
      21040, "visible energy Rneg", 100/4, 0., 12. );
   m_cc_energy_Rneg = iHistoManager.histogram(
      21050, "calorimeter energy Rneg", 100/4, 0., 12. );
   m_neutral_energy_Rneg = iHistoManager.histogram(
      21055, "neutral energy Rneg", 100/4, 0., 12. );
   m_biggest_shower_Rneg = iHistoManager.histogram(
      21060, "biggest shower energy Rneg", 100/2, 0., 6. );
   m_biggest_match_Rneg = iHistoManager.histogram(
      21090, "biggest matched shower energy Rneg", 100/2, 0., 3. );
   m_biggest_track_Rneg = iHistoManager.histogram(
      21110, "biggest track momentum Rneg", 100/2, 0., 6. );
   m_sphericity_Rneg = iHistoManager.histogram(
      21140, "sphericity Rneg", 100/4, 0., 1. );
   m_acoplanarity_Rneg = iHistoManager.histogram(
      21150, "acoplanarity Rneg", 100/4, 0., M_PI );
   m_num_showers_Rneg = iHistoManager.histogram(
      21160, "number of showers Rneg", 50, -0.5, 49.5 );
   m_totalMomentum_mag_Rneg = iHistoManager.histogram(
      21170, "event momentum mag Rneg", 100/4, 0., 6. );
   m_totalMomentum_perp_Rneg = iHistoManager.histogram(
      21180, "event momentum perp Rneg", 100/4, 0., 3. );
   m_totalMomentum_z_Rneg = iHistoManager.histogram(
      21190, "event momentum z Rneg", 100/4, -5., 5. );
   m_track_z0_Rneg = iHistoManager.histogram(
      21250, "indiv track z0 Rneg", 100, -0.2, 0.2 );
   m_shifted_track_z0_Rneg = iHistoManager.histogram(
      21260, "indiv track z0 - event weighted z0 Rneg", 100, -0.1, 0.1 );
   m_track_momentum_mag_Rneg = iHistoManager.histogram(
      21270, "indiv track momentum mag Rneg", 100, 0., 3. );
   m_track_momentum_perp_Rneg = iHistoManager.histogram(
      21280, "indiv track momentum perp Rneg", 100, 0., 3. );
   m_track_momentum_z_Rneg = iHistoManager.histogram(
      21290, "indiv track momentum z Rneg", 100, -2., 2. );
   m_shower_energy_Rneg = iHistoManager.histogram(
      21300, "indiv shower energy Rneg", 100, 0., 2. );

   m_num_tracks_Lpos = iHistoManager.histogram(
      31010, "number of tracks Lpos", 30, -0.5, 29.5 );
   m_weighted_z0_Lpos = iHistoManager.histogram(
      31030, "weighted z0 Lpos", 100/4, -0.10, 0.10 );
   m_visible_energy_Lpos = iHistoManager.histogram(
      31040, "visible energy Lpos", 100/4, 0., 12. );
   m_cc_energy_Lpos = iHistoManager.histogram(
      31050, "calorimeter energy Lpos", 100/4, 0., 12. );
   m_neutral_energy_Lpos = iHistoManager.histogram(
      31055, "neutral energy Lpos", 100/4, 0., 12. );
   m_biggest_shower_Lpos = iHistoManager.histogram(
      31060, "biggest shower energy Lpos", 100/2, 0., 6. );
   m_biggest_match_Lpos = iHistoManager.histogram(
      31090, "biggest matched shower energy Lpos", 100/2, 0., 3. );
   m_biggest_track_Lpos = iHistoManager.histogram(
      31110, "biggest track momentum Lpos", 100/2, 0., 6. );
   m_sphericity_Lpos = iHistoManager.histogram(
      31140, "sphericity Lpos", 100/4, 0., 1. );
   m_acoplanarity_Lpos = iHistoManager.histogram(
      31150, "acoplanarity Lpos", 100/4, 0., M_PI );
   m_num_showers_Lpos = iHistoManager.histogram(
      31160, "number of showers Lpos", 50, -0.5, 49.5 );
   m_totalMomentum_mag_Lpos = iHistoManager.histogram(
      31170, "event momentum mag Lpos", 100/4, 0., 6. );
   m_totalMomentum_perp_Lpos = iHistoManager.histogram(
      31180, "event momentum perp Lpos", 100/4, 0., 3. );
   m_totalMomentum_z_Lpos = iHistoManager.histogram(
      31190, "event momentum z Lpos", 100/4, -5., 5. );
   m_track_z0_Lpos = iHistoManager.histogram(
      31250, "indiv track z0 Lpos", 100, -0.2, 0.2 );
   m_shifted_track_z0_Lpos = iHistoManager.histogram(
      31260, "indiv track z0 - event weighted z0 Lpos", 100, -0.1, 0.1 );
   m_track_momentum_mag_Lpos = iHistoManager.histogram(
      31270, "indiv track momentum mag Lpos", 100, 0., 3. );
   m_track_momentum_perp_Lpos = iHistoManager.histogram(
      31280, "indiv track momentum perp Lpos", 100, 0., 3. );
   m_track_momentum_z_Lpos = iHistoManager.histogram(
      31290, "indiv track momentum z Lpos", 100, -2., 2. );
   m_shower_energy_Lpos = iHistoManager.histogram(
      31300, "indiv shower energy Lpos", 100, 0., 2. );

   m_num_tracks_Lneg = iHistoManager.histogram(
      41010, "number of tracks Lneg", 30, -0.5, 29.5 );
   m_weighted_z0_Lneg = iHistoManager.histogram(
      41030, "weighted z0 Lneg", 100/4, -0.10, 0.10 );
   m_visible_energy_Lneg = iHistoManager.histogram(
      41040, "visible energy Lneg", 100/4, 0., 12. );
   m_cc_energy_Lneg = iHistoManager.histogram(
      41050, "calorimeter energy Lneg", 100/4, 0., 12. );
   m_neutral_energy_Lneg = iHistoManager.histogram(
      41055, "neutral energy Lneg", 100/4, 0., 12. );
   m_biggest_shower_Lneg = iHistoManager.histogram(
      41060, "biggest shower energy Lneg", 100/2, 0., 6. );
   m_biggest_match_Lneg = iHistoManager.histogram(
      41090, "biggest matched shower energy Lneg", 100/2, 0., 3. );
   m_biggest_track_Lneg = iHistoManager.histogram(
      41110, "biggest track momentum Lneg", 100/2, 0., 6. );
   m_sphericity_Lneg = iHistoManager.histogram(
      41140, "sphericity Lneg", 100/4, 0., 1. );
   m_acoplanarity_Lneg = iHistoManager.histogram(
      41150, "acoplanarity Lneg", 100/4, 0., M_PI );
   m_num_showers_Lneg = iHistoManager.histogram(
      41160, "number of showers Lneg", 50, -0.5, 49.5 );
   m_totalMomentum_mag_Lneg = iHistoManager.histogram(
      41170, "event momentum mag Lneg", 100/4, 0., 6. );
   m_totalMomentum_perp_Lneg = iHistoManager.histogram(
      41180, "event momentum perp Lneg", 100/4, 0., 3. );
   m_totalMomentum_z_Lneg = iHistoManager.histogram(
      41190, "event momentum z Lneg", 100/4, -5., 5. );
   m_track_z0_Lneg = iHistoManager.histogram(
      41250, "indiv track z0 Lneg", 100, -0.2, 0.2 );
   m_shifted_track_z0_Lneg = iHistoManager.histogram(
      41260, "indiv track z0 - event weighted z0 Lneg", 100, -0.1, 0.1 );
   m_track_momentum_mag_Lneg = iHistoManager.histogram(
      41270, "indiv track momentum mag Lneg", 100, 0., 3. );
   m_track_momentum_perp_Lneg = iHistoManager.histogram(
      41280, "indiv track momentum perp Lneg", 100, 0., 3. );
   m_track_momentum_z_Lneg = iHistoManager.histogram(
      41290, "indiv track momentum z Lneg", 100, -2., 2. );
   m_shower_energy_Lneg = iHistoManager.histogram(
      41300, "indiv shower energy Lneg", 100, 0., 2. );

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
BeamGasCounterProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem< BeamSpot > spot;
   extract( iFrame.record( Stream::kBeginRun ), spot );
   double beam_x( spot->center().x() );
   double beam_y( spot->center().y() );
   double beam_z( spot->center().z() );

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);
   double event_momentum_z(props->totalMomentumVect().z());
   double neutral_energy(props->neutralEnergy());

   FATable< NavTrack >::const_iterator track_iter;
   FATable< NavTrack >::const_iterator other_iter;
   FATable< NavShower >::const_iterator shower_iter;

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();

   FATable<NavTrack> tracks_trkman;
   extract(iFrame.record(Stream::kEvent), tracks_trkman, "TrkmanApproved");
   FATable<NavTrack>::const_iterator tracks_trkman_end = tracks_trkman.end();

   FATable< NavShower > navshowers;
   extract( iFrame.record( Stream::kEvent ), navshowers );
   FATable< NavShower >::const_iterator showers_end = navshowers.end();

   double event_charge(0.);
   double event_charge_trkman(0.);
   double event_charge_trkman_vertex(0.);

   int fitted_tracks(0);
   double znumer(0.);
   double zdenom(0.);
   double weighted_z0(1000.);
   int num_showers(0);

   for ( track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter ) {
      event_charge += (track_iter->pionHelix()->curvature() > 0. ? 1. : -1.);
      if ( ! track_iter->pionQuality()->fitAbort() ) fitted_tracks++;

      if ( ! track_iter->seedQuality()->originUsed()            &&  // - I want real z information!
	   ! track_iter->pionQuality()->fitAbort()              &&  // - Don't let the fit fail
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&  // - Diameter must be greater than 42 cm
                                                                    //   to guarantee that it pokes through
                                                                    //   the first stereo superlayer
	   ! track_iter->pionHelix()->hasNullErrorMatrix()          // - I want an error matrix for
                                                                    //   weighted means
	 ) {
	 double z0err2( track_iter->pionHelix()->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) );

	 znumer += track_iter->pionHelix()->z0() / z0err2;
	 zdenom += 1. / z0err2;
      } // end passes weighted z0 track cuts

   }
   if ( zdenom != 0. )
      weighted_z0 = znumer / zdenom;

   for ( shower_iter = navshowers.begin();  shower_iter != showers_end;  shower_iter++ ) {
      if ( ! shower_iter->attributes().hot()  &&
	   shower_iter->attributes().energy() > 0.030 ) {
	 num_showers++;
      } // end if not hot
   } // end loop over showers

   double best_perp(1000.);
   double vertex_x(1000.);
   double vertex_y(1000.);
   for ( track_iter = tracks_trkman.begin();  track_iter != tracks_trkman_end;  ++track_iter ) {
      double charge(track_iter->pionHelix()->curvature() > 0. ? 1. : -1.);

      if ( ! track_iter->seedQuality()->originUsed()            &&
	   ! track_iter->pionQuality()->fitAbort()              &&
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&
	   ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {
	 // Secondary track loop to calculate pairwise intersections
	 for ( other_iter = track_iter;  other_iter != tracks_trkman_end;  other_iter++ ) {
	    if ( other_iter != track_iter  &&
		 ! other_iter->seedQuality()->originUsed()            &&
		 ! other_iter->pionQuality()->fitAbort()              &&
		 1./abs(other_iter->pionHelix()->curvature()) > 0.42  &&
		 ! other_iter->pionHelix()->hasNullErrorMatrix()        
	       ) { 
	       double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);

	       KTHelix track( *track_iter->pionHelix() );
	       KTHelix other( *other_iter->pionHelix() );

	       if ( calc_intersection( tx, ty, tz, tsig2z, tzsep, track, other ) ) {

		  double zqual(sqrt(tsig2z + sqr(tzsep)));
		  double perp(sqrt(sqr(tx - beam_x) + sqr(ty - beam_y)));

		  if ( charge > 0. ) {
		     m_vertex_zqual_pos->fill(zqual);
		     m_vertex_perp_pos->fill(perp);
		  } else {
		     m_vertex_zqual_neg->fill(zqual);
		     m_vertex_perp_neg->fill(perp);
		  }

		  if ( perp < best_perp ) {
		     best_perp = perp;
		     vertex_x = tx;
		     vertex_y = ty;
		  }

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over primary track

   for ( track_iter = tracks_trkman.begin();  track_iter != tracks_trkman_end;  ++track_iter ) {
      double charge(track_iter->pionHelix()->curvature() > 0. ? 1. : -1.);

      event_charge_trkman += charge;

      double best_perp_from_vertex(1000.);
      if ( ! track_iter->seedQuality()->originUsed()            &&
	   ! track_iter->pionQuality()->fitAbort()              &&
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&
	   ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {
	 // Secondary track loop to calculate pairwise intersections
	 for ( other_iter = track_iter;  other_iter != tracks_trkman_end;  other_iter++ ) {
	    if ( other_iter != track_iter  &&
		 ! other_iter->seedQuality()->originUsed()            &&
		 ! other_iter->pionQuality()->fitAbort()              &&
		 1./abs(other_iter->pionHelix()->curvature()) > 0.42  &&
		 ! other_iter->pionHelix()->hasNullErrorMatrix()        
	       ) { 
	       double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);

	       KTHelix track( *track_iter->pionHelix() );
	       KTHelix other( *other_iter->pionHelix() );

	       if ( calc_intersection( tx, ty, tz, tsig2z, tzsep, track, other ) ) {

		  double perp_from_vertex(sqrt(sqr(tx - vertex_x) + sqr(ty - vertex_y)));
		  if ( perp_from_vertex < best_perp_from_vertex )
		     best_perp_from_vertex = perp_from_vertex;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts

      if ( charge > 0. ) {
	 m_perp_from_vertex_pos->fill(best_perp_from_vertex);
      } else {
	 m_perp_from_vertex_neg->fill(best_perp_from_vertex);
      }

      if ( best_perp_from_vertex < 3.*k_mm )
	 event_charge_trkman_vertex += charge;
   } // end loop over tracks

   m_event_charge->fill(event_charge);
   m_event_charge_trkman->fill(event_charge_trkman);
   m_event_charge_trkman_vertex->fill(event_charge_trkman_vertex);

   m_total++;

   if ( event_charge_trkman > 1.5 ) {
      m_event_pz_Rpos->fill(event_momentum_z);
      m_event_neutral_energy_Rpos->fill(neutral_energy);

      if ( event_momentum_z > 0. )
	 m_Rpos_fore++;
      else
	 m_Rpos_back++;
      
      if ( neutral_energy > 4.*k_GeV )
	 m_Rpos_neut++;

      m_num_tracks_Rpos->fill( fitted_tracks );
      m_weighted_z0_Rpos->fill( weighted_z0 );
      m_visible_energy_Rpos->fill( props->eVis() );
      m_cc_energy_Rpos->fill( props->ccTotalEnergy() );
      m_neutral_energy_Rpos->fill( props->neutralEnergy() );
      m_biggest_shower_Rpos->fill( props->firstLargestEShower() );
      m_biggest_match_Rpos->fill( props->firstMatchedEnergy() );
      m_biggest_track_Rpos->fill( props->firstLargestPTrack() );
      m_sphericity_Rpos->fill( props->sphericity() );
      m_acoplanarity_Rpos->fill( props->acoplanarity() );
      m_num_showers_Rpos->fill( num_showers );
      m_totalMomentum_mag_Rpos->fill( props->totalMomentumVect().mag() );
      m_totalMomentum_perp_Rpos->fill( props->totalMomentumVect().perp() );
      m_totalMomentum_z_Rpos->fill( props->totalMomentumVect().z() );

      for ( track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter ) {
	 if ( ! track_iter->pionQuality()->fitAbort() ) {
	    m_track_z0_Rpos->fill( track_iter->pionHelix()->z0() );
	    m_shifted_track_z0_Rpos->fill( track_iter->pionHelix()->z0() - weighted_z0 );
	    m_track_momentum_mag_Rpos->fill( track_iter->pionFit()->momentum().mag() );
	    m_track_momentum_perp_Rpos->fill( track_iter->pionFit()->momentum().perp() );
	    m_track_momentum_z_Rpos->fill( track_iter->pionFit()->momentum().z() );
	 }
      }
      for ( shower_iter = navshowers.begin();  shower_iter != showers_end;  shower_iter++ ) {
	 if ( ! shower_iter->attributes().hot()  &&
	      shower_iter->attributes().energy() > 0.030 ) {
	    m_shower_energy_Rpos->fill( shower_iter->attributes().energy() );
	 } // end if not hot
      } // end loop over showers

   } // end if Rpositive
   else if ( event_charge_trkman < -1.5 ) {
      m_event_pz_Rneg->fill(event_momentum_z);
      m_event_neutral_energy_Rneg->fill(neutral_energy);

      if ( event_momentum_z > 0. )
	 m_Rneg_fore++;
      else
	 m_Rneg_back++;

      if ( neutral_energy > 4.*k_GeV )
	 m_Rneg_neut++;

      m_num_tracks_Rneg->fill( fitted_tracks );
      m_weighted_z0_Rneg->fill( weighted_z0 );
      m_visible_energy_Rneg->fill( props->eVis() );
      m_cc_energy_Rneg->fill( props->ccTotalEnergy() );
      m_neutral_energy_Rneg->fill( props->neutralEnergy() );
      m_biggest_shower_Rneg->fill( props->firstLargestEShower() );
      m_biggest_match_Rneg->fill( props->firstMatchedEnergy() );
      m_biggest_track_Rneg->fill( props->firstLargestPTrack() );
      m_sphericity_Rneg->fill( props->sphericity() );
      m_acoplanarity_Rneg->fill( props->acoplanarity() );
      m_num_showers_Rneg->fill( num_showers );
      m_totalMomentum_mag_Rneg->fill( props->totalMomentumVect().mag() );
      m_totalMomentum_perp_Rneg->fill( props->totalMomentumVect().perp() );
      m_totalMomentum_z_Rneg->fill( props->totalMomentumVect().z() );

      for ( track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter ) {
	 if ( ! track_iter->pionQuality()->fitAbort() ) {
	    m_track_z0_Rneg->fill( track_iter->pionHelix()->z0() );
	    m_shifted_track_z0_Rneg->fill( track_iter->pionHelix()->z0() - weighted_z0 );
	    m_track_momentum_mag_Rneg->fill( track_iter->pionFit()->momentum().mag() );
	    m_track_momentum_perp_Rneg->fill( track_iter->pionFit()->momentum().perp() );
	    m_track_momentum_z_Rneg->fill( track_iter->pionFit()->momentum().z() );
	 }
      }
      for ( shower_iter = navshowers.begin();  shower_iter != showers_end;  shower_iter++ ) {
	 if ( ! shower_iter->attributes().hot()  &&
	      shower_iter->attributes().energy() > 0.030 ) {
	    m_shower_energy_Rneg->fill( shower_iter->attributes().energy() );
	 } // end if not hot
      } // end loop over showers

   } // end else Rnegative

   if ( event_charge_trkman_vertex > 1.5 ) {
      m_event_pz_Lpos->fill(event_momentum_z);
      m_event_neutral_energy_Lpos->fill(neutral_energy);

      if ( event_momentum_z > 0. )
	 m_Lpos_fore++;
      else
	 m_Lpos_back++;
      
      if ( neutral_energy > 4.*k_GeV )
	 m_Lpos_neut++;

      m_num_tracks_Lpos->fill( fitted_tracks );
      m_weighted_z0_Lpos->fill( weighted_z0 );
      m_visible_energy_Lpos->fill( props->eVis() );
      m_cc_energy_Lpos->fill( props->ccTotalEnergy() );
      m_neutral_energy_Lpos->fill( props->neutralEnergy() );
      m_biggest_shower_Lpos->fill( props->firstLargestEShower() );
      m_biggest_match_Lpos->fill( props->firstMatchedEnergy() );
      m_biggest_track_Lpos->fill( props->firstLargestPTrack() );
      m_sphericity_Lpos->fill( props->sphericity() );
      m_acoplanarity_Lpos->fill( props->acoplanarity() );
      m_num_showers_Lpos->fill( num_showers );
      m_totalMomentum_mag_Lpos->fill( props->totalMomentumVect().mag() );
      m_totalMomentum_perp_Lpos->fill( props->totalMomentumVect().perp() );
      m_totalMomentum_z_Lpos->fill( props->totalMomentumVect().z() );

      for ( track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter ) {
	 if ( ! track_iter->pionQuality()->fitAbort() ) {
	    m_track_z0_Lpos->fill( track_iter->pionHelix()->z0() );
	    m_shifted_track_z0_Lpos->fill( track_iter->pionHelix()->z0() - weighted_z0 );
	    m_track_momentum_mag_Lpos->fill( track_iter->pionFit()->momentum().mag() );
	    m_track_momentum_perp_Lpos->fill( track_iter->pionFit()->momentum().perp() );
	    m_track_momentum_z_Lpos->fill( track_iter->pionFit()->momentum().z() );
	 }
      }
      for ( shower_iter = navshowers.begin();  shower_iter != showers_end;  shower_iter++ ) {
	 if ( ! shower_iter->attributes().hot()  &&
	      shower_iter->attributes().energy() > 0.030 ) {
	    m_shower_energy_Lpos->fill( shower_iter->attributes().energy() );
	 } // end if not hot
      } // end loop over showers

   } // end if Lpositive
   else if ( event_charge_trkman_vertex < -1.5 ) {
      m_event_pz_Lneg->fill(event_momentum_z);
      m_event_neutral_energy_Lneg->fill(neutral_energy);

      if ( event_momentum_z > 0. )
	 m_Lneg_fore++;
      else
	 m_Lneg_back++;

      if ( neutral_energy > 4.*k_GeV )
	 m_Lneg_neut++;

      m_num_tracks_Lneg->fill( fitted_tracks );
      m_weighted_z0_Lneg->fill( weighted_z0 );
      m_visible_energy_Lneg->fill( props->eVis() );
      m_cc_energy_Lneg->fill( props->ccTotalEnergy() );
      m_neutral_energy_Lneg->fill( props->neutralEnergy() );
      m_biggest_shower_Lneg->fill( props->firstLargestEShower() );
      m_biggest_match_Lneg->fill( props->firstMatchedEnergy() );
      m_biggest_track_Lneg->fill( props->firstLargestPTrack() );
      m_sphericity_Lneg->fill( props->sphericity() );
      m_acoplanarity_Lneg->fill( props->acoplanarity() );
      m_num_showers_Lneg->fill( num_showers );
      m_totalMomentum_mag_Lneg->fill( props->totalMomentumVect().mag() );
      m_totalMomentum_perp_Lneg->fill( props->totalMomentumVect().perp() );
      m_totalMomentum_z_Lneg->fill( props->totalMomentumVect().z() );

      for ( track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter ) {
	 if ( ! track_iter->pionQuality()->fitAbort() ) {
	    m_track_z0_Lneg->fill( track_iter->pionHelix()->z0() );
	    m_shifted_track_z0_Lneg->fill( track_iter->pionHelix()->z0() - weighted_z0 );
	    m_track_momentum_mag_Lneg->fill( track_iter->pionFit()->momentum().mag() );
	    m_track_momentum_perp_Lneg->fill( track_iter->pionFit()->momentum().perp() );
	    m_track_momentum_z_Lneg->fill( track_iter->pionFit()->momentum().z() );
	 }
      }
      for ( shower_iter = navshowers.begin();  shower_iter != showers_end;  shower_iter++ ) {
	 if ( ! shower_iter->attributes().hot()  &&
	      shower_iter->attributes().energy() > 0.030 ) {
	    m_shower_energy_Lneg->fill( shower_iter->attributes().energy() );
	 } // end if not hot
      } // end loop over showers

   } // end else Lnegative

   if ( m_total % 100 == 0 ) calc_beamgas_events(INFO);

   return ActionBase::kPassed;
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

void
BeamGasCounterProc::calc_beamgas_events(Severity severity)
{
   double R_positive_positrons, R_positive_posit_err, R_positive_electrons, R_positive_elect_err;
   double R_positrons, R_posit_err, R_electrons, R_elect_err;

   // a net positive imbalance indicates beamgas
   // foreward direction indicates positrons
   R_positive_positrons = double(m_Rpos_fore) - double(m_Rneg_fore);
   R_positive_posit_err = sqrt(1./double(m_Rpos_fore) + 1./double(m_Rneg_fore));

   // some beamgas events have negative charge, correct for this
   // all positron beamgas / positive positron beamgas is
   //                302/134 = 2.25 +/- 0.23
   R_positrons = R_positive_positrons * 2.25;
   R_posit_err = R_positrons * sqrt(sqr(R_positive_posit_err)/sqr(R_positive_positrons) +
				    sqr(0.23)/sqr(2.25));

   // a net positive imbalance indicates beamgas
   // backward direction indicates electrons
   R_positive_electrons = double(m_Rpos_back) - double(m_Rneg_back);
   R_positive_elect_err = sqrt(1./double(m_Rpos_back) + 1./double(m_Rneg_back));

   // some beamgas events have negative charge, correct for this
   // all electron beamgas / positive electron beamgas is
   //                135/59 = 2.29 +/- 0.36
   R_electrons = R_positive_electrons * 2.29;
   R_elect_err = R_electrons * sqrt(sqr(R_positive_elect_err)/sqr(R_positive_electrons) +
				    sqr(0.36)/sqr(2.29));

   report(severity, kFacilityString)
      << "Conservative estimations (track set defined by Trkman):" << endl
      << "m_Rpos_fore = " << m_Rpos_fore << " m_Rpos_back = " << m_Rpos_back
      << " m_Rneg_fore = " << m_Rneg_fore << " m_Rneg_back = " << m_Rneg_back
      << " m_Rpos_neut = " << m_Rpos_neut << " m_Rneg_neut = " << m_Rneg_neut << endl
      << endl
      << "Positron beamgas events (Trkman): " << R_positrons << " +/- " << R_posit_err << endl
      << "Electron beamgas events (Trkman): " << R_electrons << " +/- " << R_elect_err << endl
      << "Total events: " << m_total << endl;

   double L_positive_positrons, L_positive_posit_err, L_positive_electrons, L_positive_elect_err;
   double L_positrons, L_posit_err, L_electrons, L_elect_err;

   // a net positive imbalance indicates beamgas
   // foreward direction indicates positrons
   L_positive_positrons = double(m_Lpos_fore) - double(m_Lneg_fore);
   L_positive_posit_err = sqrt(1./double(m_Lpos_fore) + 1./double(m_Lneg_fore));

   // some beamgas events have negative charge, correct for this
   // all positron beamgas / positive positron beamgas is
   //                302/134 = 2.25 +/- 0.23
   L_positrons = L_positive_positrons * 2.25;
   L_posit_err = L_positrons * sqrt(sqr(L_positive_posit_err)/sqr(L_positive_positrons) +
				    sqr(0.23)/sqr(2.25));

   // a net positive imbalance indicates beamgas
   // backward direction indicates electrons
   L_positive_electrons = double(m_Lpos_back) - double(m_Lneg_back);
   L_positive_elect_err = sqrt(1./double(m_Lpos_back) + 1./double(m_Lneg_back));

   // some beamgas events have negative charge, correct for this
   // all electron beamgas / positive electron beamgas is
   //                135/59 = 2.29 +/- 0.36
   L_electrons = L_positive_electrons * 2.29;
   L_elect_err = L_electrons * sqrt(sqr(L_positive_elect_err)/sqr(L_positive_electrons) +
				    sqr(0.36)/sqr(2.29));

   report(severity, kFacilityString)
      << "Contraversial estimations (track set defined by Trkman and vertex in 3mm):" << endl
      << "m_Lpos_fore = " << m_Lpos_fore << " m_Lpos_back = " << m_Lpos_back
      << " m_Lneg_fore = " << m_Lneg_fore << " m_Lneg_back = " << m_Lneg_back
      << " m_Lpos_neut = " << m_Lpos_neut << " m_Lneg_neut = " << m_Lneg_neut << endl
      << endl
      << "Positron beamgas events (Trkman+vertex): " << L_positrons << " +/- " << L_posit_err << endl
      << "Electron beamgas events (Trkman+vertex): " << L_electrons << " +/- " << L_elect_err << endl
      << "Total events: " << m_total << endl;
}

DABoolean BeamGasCounterProc::calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
					       KTHelix& a, KTHelix& b )
{
   x = y = z = sig2z = zsep = 1000.;  // To more easily find unchecked failures

   // Express the two helices in terms of (x - xa)^2 + (y - ya)^2 == ra^2
   double ra( 1./2./a.curvature() );
   double xa( -(a.d0() + ra) * sin(a.phi0()) );
   double ya( (a.d0() + ra) * cos(a.phi0()) );

   double rb( 1./2./b.curvature() );
   double xb( -(b.d0() + rb) * sin(b.phi0()) );
   double yb( (b.d0() + rb) * cos(b.phi0()) );

   // Zero or infinitely many solutions
   // I don't want to deal with either case
   if ( xa == xb  &&  ya == yb ) return false;

   double disc( (pow(4.*sqr(ra)*(xa - xb) - 
		     4.*(sqr(rb)*(xa - xb) + 
			(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))
		     ,2.) - 16.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))*
		 (pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
		  2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
		  2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
		  pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
		  4.*sqr(rb)*sqr(ya - yb)))/
		(64.*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );
   // no real solutions
   if ( disc < 0 ) return false;

   double pre( (sqr(rb)*(xa - xb) + sqr(ra)*(-xa + xb) + 
		(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))/
	       (2.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))) );

   // The two x solutions
   double xsol1( pre + sqrt( disc ) );
   double xsol2( pre - sqrt( disc ) );

   // Two possibilities for the y solution to each x solution
   double ysol1a( yb + sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1b( yb - sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1;
   if ( abs( sqr(xsol1 - xa) + sqr(ysol1a - ya) - sqr(ra) ) <
	abs( sqr(xsol1 - xa) + sqr(ysol1b - ya) - sqr(ra) )   )
      ysol1 = ysol1a;
   else
      ysol1 = ysol1b;

   double ysol2a( yb + sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2b( yb - sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2;
   if ( abs( sqr(xsol2 - xa) + sqr(ysol2a - ya) - sqr(ra) ) <
	abs( sqr(xsol2 - xa) + sqr(ysol2b - ya) - sqr(ra) )   )
      ysol2 = ysol2a;
   else
      ysol2 = ysol2b;

   // Calculate the arclength of each solution along the two tracks.
   // Throw out a solution if the particle needs to travel (too far)
   // backward to get to it. If both solutions are okay, take the one
   // closest to the origin.
   DABoolean arclength1_ok( arclength_test( xsol1, ysol1, a, b ) );
   DABoolean arclength2_ok( arclength_test( xsol2, ysol2, a, b ) );
   
   if ( !arclength1_ok  &&  !arclength2_ok ) return false;

   else if ( arclength1_ok  &&  !arclength2_ok ) {
      x = xsol1;  y = ysol1;
   }

   else if ( !arclength1_ok  &&  arclength2_ok ) {
      x = xsol2;  y = ysol2;
   }

   else if ( sqr(xsol1) + sqr(ysol1) < sqr(xsol2) + sqr(ysol2) ) {
      x = xsol1;  y = ysol1;
   }

   else {
      x = xsol2;  y = ysol2;
   }      

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   double az( a.cotTheta() * aarclength + a.z0() );
   double bz( b.cotTheta() * barclength + b.z0() );
   double sig2_az( a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(aarclength)
		   + a.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * aarclength * a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );
   double sig2_bz( b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(barclength)
		   + b.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * barclength * b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );

   z = (az/sig2_az + bz/sig2_bz) / (1./sig2_az + 1./sig2_bz);
   sig2z = 1. / (1./sig2_az + 1./sig2_bz);
   zsep = az - bz;

   // Because it is not useful for the `closest_intersection'
   // algorithm, I had to throw out a great deal of lovely code that
   // calculates uncertanties in x and y.  If you want this, ask me
   // about it.
   return true;
}

DABoolean BeamGasCounterProc::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
{
   const double tailCut = 0.005;

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   return ( aarclength > -tailCut  &&  aarclength < M_PI/2./abs(a.curvature()) )  &&
      ( barclength > -tailCut  &&  barclength < M_PI/2./abs(b.curvature()) );
}

//
// const member functions
//

//
// static member functions
//
