// -*- C++ -*-
//
// Package:     HadronFilterProc
// Module:      HadronFilterProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim McCann
// Created:     Mon Aug  5 13:54:13 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "HadronFilterProc/HadronFilterProc.h"
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
#include "BunchFinder/BunchDecision.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"
#include "Navigation/NavShower.h"
#include "Navigation/NavTkShMatch.h"
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
static const char* const kFacilityString = "Processor.HadronFilterProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
HadronFilterProc::HadronFilterProc( void )               // anal1
   : Processor( "HadronFilterProc" )
   , m_fillBuffer( "fillBuffer", this, true )
   , m_noBeamSpot( "noBeamSpot", this, false )
   , m_noBunchWeight( "noBunchWeight", this, false )
   , m_ntupleSize( "ntupleSize", this, 1000 )
   , m_closestIntersectionCut( "closestIntersectionCut", this, 0.003 )
   , m_tailCut( "tailCut", this, 0.005 )
   , m_weightedZ0Cut( "weightedZ0Cut", this, 0.10 )
   , m_bunchWeightMarginCut( "bunchWeightMarginCut", this, 0.4 )
   , m_beamSpotX( "beamSpotX", this, 0. )
   , m_beamSpotY( "beamSpotY", this, 0. )
   , m_applyNeutralEnergyCut( "applyNeutralEnergyCut", this, false )
   , m_chargeConstraint( "chargeConstraint", this, 0. )
   , m_beamSpotVars( NULL )
   , m_centeredBeamSpot( NULL )
   , m_numTracks_passed( NULL )
   , m_numTracks_failed( NULL )
   , m_closestIntersection_passed( NULL )
   , m_closestIntersection_failed( NULL )
   , m_weightedZ0_passed( NULL )
   , m_weightedZ0_failed( NULL )
   , m_bunchWeightMargin_passed( NULL )
   , m_bunchWeightMargin_failed( NULL )
   , m_num_buffer_events( 0 )
   , m_buffer_pointer( 0 )
   , m_buf_x()
   , m_buf_sigx()
   , m_buf_y()
   , m_buf_sigy()
   , m_entriesInNtuple( 0 )
   , m_passed( 0 )
   , m_gt2tracks( 0 )
   , m_allevents( 0 )
   , m_run( 0 )
   , m_event( 0 )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &HadronFilterProc::event,    Stream::kEvent );
   //bind( &HadronFilterProc::beginRun, Stream::kBeginRun );
   //bind( &HadronFilterProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

HadronFilterProc::~HadronFilterProc()                    // anal5
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
HadronFilterProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
HadronFilterProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
   if ( m_gt2tracks > 0 ) {
      report( SYSTEM, kFacilityString )
	 << "                         Events which have passed / all 3+ track events = " << m_passed << " / " << m_gt2tracks
	 << " = " << double(m_passed) / double(m_gt2tracks) << endl;
      report( SYSTEM, kFacilityString )
	 << "Events which have passed / all events = " << m_passed << " / " << m_allevents
	 << " = " << double(m_passed) / double(m_allevents) << endl;
   }

   report( SYSTEM, kFacilityString )
      << "HEYLOOKATME!!! Leaving run " << m_run << " after event number " << m_event << endl
      << "HEYLOOKATME!!! (last one)" << endl;
}


// ---------------- standard place to book histograms ---------------
void
HadronFilterProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   const char* beamSpotVarsLabels[kNBeamSpotVars] = {
      "run", "event", "x", "sigx", "y", "sigy", "spread" };
   m_beamSpotVars = iHistoManager.ntuple(
      1, "beamSpotVars", kNBeamSpotVars, 262144, beamSpotVarsLabels );
   m_centeredBeamSpot = iHistoManager.histogram(
      2, "centered beamspot", 200, -0.01, 0.01, 200, -0.01, 0.01 );

   const char* ntupleLabels[kNNtupleVars] = {
      "numtr", "int1", "int2", "int3", "wz0", "charge", "visen", "neuen", "pperp", "pz",
      "sh1", "sh2", "sh3", "tr1", "tr2", "numsh", "chpperp", "chpz"
   };
   m_passNtuple = iHistoManager.ntuple(
      100, "passed", kNNtupleVars, 262144, ntupleLabels );

   m_numTracks_passed = iHistoManager.histogram(
      101, "num tracks PASSED", 50, -0.5, 49.5 );
   m_numTracks_failed = iHistoManager.histogram(
      201, "num tracks FAILED", 50, -0.5, 49.5 );

   m_closestIntersection_passed = iHistoManager.histogram(
      102, "closest intersection PASSED", 100, 0., 0.01 );
   m_closestIntersection_failed = iHistoManager.histogram(
      202, "closest intersection FAILED", 100, 0., 0.01 );

   m_weightedZ0_passed = iHistoManager.histogram(
      103, "weighted Z0 PASSED", 100, -0.5, 0.5 );
   m_weightedZ0_failed = iHistoManager.histogram(
      203, "weighted Z0 FAILED", 100, -0.5, 0.5 );

   m_bunchWeightMargin_passed = iHistoManager.histogram(
      104, "bunchweight margin PASSED", 100, 0., 1. );
   m_bunchWeightMargin_failed = iHistoManager.histogram(
      204, "bunchweight margin FAILED", 100, 0., 1. );

   m_num_tracks = iHistoManager.histogram(
      1010, "number of tracks", 30, -0.5, 29.5 );
   m_closest_intersection = iHistoManager.histogram(
      1020, "closest intersection", 100/4, 0., 0.003 );
   m_weighted_z0 = iHistoManager.histogram(
      1030, "weighted z0", 100/4, -0.10, 0.10 );
   m_weighted_z0_far = iHistoManager.histogram(
      1035, "weighted z0 (far)", 100, -1.5, 1.5 );
   m_visible_energy = iHistoManager.histogram(
      1040, "visible energy", 100/4, 0., 12. );
   m_cc_energy = iHistoManager.histogram(
      1050, "calorimeter energy", 100/4, 0., 12. );
   m_neutral_energy = iHistoManager.histogram(
      1055, "neutral energy", 100/4, 0., 12. );
   m_biggest_shower = iHistoManager.histogram(
      1060, "biggest shower energy", 100/2, 0., 6. );
   m_second_biggest_shower = iHistoManager.histogram(
      1070, "second biggest shower energy", 100/2, 0., 3. );
   m_third_biggest_shower = iHistoManager.histogram(
      1080, "third biggest shower energy", 100/2, 0., 3. );
   m_biggest_match = iHistoManager.histogram(
      1090, "biggest matched shower energy", 100/2, 0., 3. );
   m_second_biggest_match = iHistoManager.histogram(
      1100, "second biggest matched shower energy", 100/2, 0., 3. );
   m_biggest_track = iHistoManager.histogram(
      1110, "biggest track momentum", 100/2, 0., 6. );
   m_second_track = iHistoManager.histogram(
      1120, "second biggest track momentum", 100/2, 0., 6. );
   m_sphericity = iHistoManager.histogram(
      1140, "sphericity", 100/4, 0., 1. );
   m_acoplanarity = iHistoManager.histogram(
      1150, "acoplanarity", 100/4, 0., M_PI );
   m_num_showers = iHistoManager.histogram(
      1160, "number of showers", 50, -0.5, 49.5 );
   m_totalMomentum_mag = iHistoManager.histogram(
      1170, "event momentum mag", 100/4, 0., 6. );
   m_totalMomentum_perp = iHistoManager.histogram(
      1180, "event momentum perp", 100/4, 0., 3. );
   m_totalMomentum_z = iHistoManager.histogram(
      1190, "event momentum z", 100/4, -5., 5. );
   m_reconstructed_mass = iHistoManager.histogram(
      1200, "reconstructed upsilon mass", 100/2, 8., 11. );
   m_chargedMomentum_mag = iHistoManager.histogram(
      1210, "charged momentum mag", 100/4, 0., 6. );
   m_chargedMomentum_perp = iHistoManager.histogram(
      1220, "charged momentum perp", 100/4, 0., 6. );
   m_chargedMomentum_z = iHistoManager.histogram(
      1230, "charged momentum z", 100/4, -6., 6. );
   m_charge = iHistoManager.histogram(
      1240, "charge", 31, -15.5, 15.5 );
   m_track_z0 = iHistoManager.histogram(
      1250, "indiv track z0", 100, -0.2, 0.2 );
   m_shifted_track_z0 = iHistoManager.histogram(
      1260, "indiv track z0 - event weighted z0", 100, -0.1, 0.1 );
   m_shifted_track_z0_close = iHistoManager.histogram(
      1265, "indiv track z0 - event weighted z0", 100, -0.01, 0.01 );
   m_track_momentum_mag = iHistoManager.histogram(
      1270, "indiv track momentum mag", 100, 0., 3. );
   m_track_momentum_perp = iHistoManager.histogram(
      1280, "indiv track momentum perp", 100, 0., 3. );
   m_track_momentum_z = iHistoManager.histogram(
      1290, "indiv track momentum z", 100, -2., 2. );
   m_track_chi2 = iHistoManager.histogram(
      1295, "indiv track chi2", 100, 0., 300. );
   m_track_chi2dof = iHistoManager.histogram(
      1296, "indiv track chi2/dof", 100, 0., 3. );
   m_shower_energy = iHistoManager.histogram(
      1300, "indiv shower energy", 100, 0., 2. );
   m_second_closest_intersection = iHistoManager.histogram(
      1310, "second closest intersection", 100/4, 0., 0.004 );
   m_third_closest_intersection = iHistoManager.histogram(
      1320, "third closest intersection", 100/4, 0., 0.005 );
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
HadronFilterProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   FATable< NavShower > navshowers;
   extract( iFrame.record( Stream::kEvent ), navshowers );
   FATable< NavShower >::const_iterator showers_end = navshowers.end();

   FAItem< DBEventHeader > header;
   extract( iFrame.record( Stream::kEvent ), header );

   FAItem< EventProperties > props;
   extract( iFrame.record( Stream::kEvent ), props );

   double bunchweight_margin(1.);
   FAItem< TrackletBunchDecision > bunchDecision;

   if ( ! m_noBunchWeight.value() ) {
      extract( iFrame.record( Stream::kEvent ), bunchDecision );
      if ( bunchDecision->numberOfTestedBunches() > 0    &&
	   bunchDecision->bestBunchInfo().bweight() > 0.    )
	 bunchweight_margin = ( ( bunchDecision->bestBunchInfo().bweight()
				  - bunchDecision->bunchInfo( 1 ).bweight() )
				/ bunchDecision->bestBunchInfo().bweight() );
   } // end if measure bunchweight

   if ( m_run != header->run() ) {
      report( SYSTEM, kFacilityString )
	 << "HEYLOOKATME!!! Leaving run " << m_run << " after event number " << m_event << endl;
      m_run = header->run();
   }
   m_event = header->number();

   vector< KTHelix* > beamspot_helix;
   vector< KTHelix* > cut_helix;
   vector< int > cut_identifier;

   double charge(0.);
   Hep3Vector chargedMomentum(0.025, 0., 0.);  // counter-balance crossing angle momentum

   double weighted_z0(1000.);
   double znumer(0.);
   double zdenom(0.);

   FATable< NavTrack >::const_iterator track_iter;
   for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ )
   {
      // Quality cuts for beamspot-finding helices
      if ( ! track_iter->seedQuality()->originUsed()            &&  // - I want real z information!
	   ! track_iter->pionQuality()->fitAbort()              &&  // - Don't let the fit fail
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&  // - Diameter must be greater than 42 cm
                                                                    //   to guarantee that it pokes through
                                                                    //   the first stereo superlayer
	   ! track_iter->pionHelix()->hasNullErrorMatrix()          // - I want an error matrix for
                                                                    //   weighted means
	 )
	 beamspot_helix.push_back( (KTHelix*)( &*track_iter->pionHelix() ) );

      // Quality cuts for cut-determining helices
      if ( ! track_iter->pionQuality()->fitAbort()                  // - Just make sure it didn't abort
                                                                    //   (since that might force the track
                                                                    //   through the origin wrongly)
	 ) {
	 cut_helix.push_back( (KTHelix*)( &*track_iter->pionHelix() ) );
	 cut_identifier.push_back( track_iter->pionHelix()->identifier() );

	 charge += ( track_iter->pionHelix()->curvature() > 0. ? 1. : -1. );
	 chargedMomentum += track_iter->pionFit()->momentum();

      } // end passes cut cuts

      // Quality cuts for weighted z0 determination
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
   } // end loop over tracks

   if ( zdenom != 0. )
      weighted_z0 = znumer / zdenom;

   double beam_x(m_beamSpotX.value()), beam_sigx(0.);
   double beam_y(m_beamSpotY.value()), beam_sigy(0.), beam_spread(0.);
   if ( ! m_noBeamSpot.value() ) {
      double x(2000.), y(2000.), sigx(2000.), sigy(2000.);
      const int min_bs_tracks = 5;
      const double max_bs_from_origin = 0.01;

      if ( m_fillBuffer.value() ) {
	 if ( beamspot_helix.size() > min_bs_tracks               &&
	      event_vertex( x, y, sigx, sigy, beamspot_helix )    &&
	      sqrt(sqr(x) + sqr(y)) < max_bs_from_origin ) {
	    m_buf_x.push_back( x );
	    m_buf_y.push_back( y );
	    m_buf_sigx.push_back( sigx );
	    m_buf_sigy.push_back( sigy );
	    m_num_buffer_events++;
	 }
	 return ActionBase::kFailed;
      } // end if doing nothing but filling the beamspot buffers

      double beam_xnumer(0.), beam_xdenom(0.), beam_ynumer(0.), beam_ydenom(0.);
      int i;
      for ( i = 0;  i < m_num_buffer_events;  i++ ) {
	 beam_xnumer += m_buf_x[i] / sqr(m_buf_sigx[i]);
	 beam_xdenom += 1. / sqr(m_buf_sigx[i]);

	 beam_ynumer += m_buf_y[i] / sqr(m_buf_sigy[i]);
	 beam_ydenom += 1. / sqr(m_buf_sigy[i]);
      }
      assert( beam_xdenom > 0.  &&  beam_ydenom > 0. );
      beam_x = beam_xnumer / beam_xdenom;
      beam_sigx = sqrt( 1. / beam_xdenom );
      beam_y = beam_ynumer / beam_ydenom;
      beam_sigy = sqrt( 1. / beam_ydenom );

      for ( i = 0;  i < m_num_buffer_events;  i++ )
	 beam_spread += sqr(m_buf_x[i]) + sqr(m_buf_y[i]);
      assert( m_num_buffer_events > 0 );
      beam_spread /= double(m_num_buffer_events);
      beam_spread = sqrt(beam_spread);

      if ( beamspot_helix.size() > min_bs_tracks               &&
	   event_vertex( x, y, sigx, sigy, beamspot_helix )    &&
	   sqrt(sqr(x) + sqr(y)) < max_bs_from_origin ) {

	 m_buf_x[ m_buffer_pointer ] = x;
	 m_buf_y[ m_buffer_pointer ] = y;
	 m_buf_sigx[ m_buffer_pointer ] = sigx;
	 m_buf_sigy[ m_buffer_pointer ] = sigy;
	 m_buffer_pointer++;

	 m_centeredBeamSpot->fill( x - beam_x, y - beam_y );

	 if ( m_buffer_pointer == m_num_buffer_events ) {
	    m_buffer_pointer = 0;

	    float bs[kNBeamSpotVars];
	    bs[kRunNum] = header->run();
	    bs[kEventNum] = header->number();
	    bs[kX] = beam_x;
	    bs[kSigX] = beam_sigx;
	    bs[kY] = beam_y;
	    bs[kSigY] = beam_sigy;
	    bs[kSpread] = beam_spread;

	    m_beamSpotVars->fill( bs );
	 } // end if wrap-around
      } // end if this makes a good beamspot element

   } // end if calculating a beamspot

   m_allevents++;
   if ( cut_helix.size() < 3 ) return ActionBase::kFailed;
   m_gt2tracks++;

   double closest_inter( closest_intersection( cut_helix, beam_x, beam_y ) );
   double second_closest_inter( closest_intersection( cut_helix, beam_x, beam_y,
						      closest_inter+0.000000000001 ) );
   double third_closest_inter( closest_intersection( cut_helix, beam_x, beam_y,
						     second_closest_inter+0.000000000001 ) );

   if ( m_gt2tracks > 0  &&  m_gt2tracks % 100 == 0 ) {
      report( SYSTEM, kFacilityString )
	 << "                         Events which have passed / all 3+ track events = " << m_passed << " / " << m_gt2tracks
	 << " = " << double(m_passed) / double(m_gt2tracks) << endl;
      report( SYSTEM, kFacilityString )
	 << "Events which have passed / all events = " << m_passed << " / " << m_allevents
	 << " = " << double(m_passed) / double(m_allevents) << endl;
   }

   if ( closest_inter < m_closestIntersectionCut.value()       &&
	abs( weighted_z0 ) < m_weightedZ0Cut.value()           &&
  	bunchweight_margin > m_bunchWeightMarginCut.value()    &&
        ( ! m_applyNeutralEnergyCut.value()  ||  props->neutralEnergy() > 0.01 )  &&
	( m_chargeConstraint.value() == 0.   ||
	  ( m_chargeConstraint.value() > 0.  &&  charge >= m_chargeConstraint.value() )  ||
	  ( m_chargeConstraint.value() < 0.  &&  charge <= m_chargeConstraint.value() )     )
      ) {

      m_passed++;

      m_numTracks_passed->fill( cut_helix.size() );
      m_closestIntersection_passed->fill( closest_inter );
      m_weightedZ0_passed->fill( weighted_z0 );
      m_bunchWeightMargin_passed->fill( bunchweight_margin );

      /////////////////////////////////////////////////////////////////////
      m_num_tracks->fill( cut_helix.size() );
      m_closest_intersection->fill( closest_inter );
      m_weighted_z0->fill( weighted_z0 );
      m_weighted_z0_far->fill( weighted_z0 );
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
      m_chargedMomentum_mag->fill( chargedMomentum.mag() );
      m_chargedMomentum_perp->fill( chargedMomentum.perp() );
      m_chargedMomentum_z->fill( chargedMomentum.z() );
      m_charge->fill( charge );
      m_second_closest_intersection->fill( second_closest_inter );
      m_third_closest_intersection->fill( third_closest_inter );

      double massSquared( sqr(props->eVis())
			  - (props->totalMomentumVect() + Hep3Vector(0.025,0.,0.)).mag2() );
      if ( massSquared > 0. )
	 m_reconstructed_mass->fill( sqrt(massSquared) );

      for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ )
      {
	 // Quality cuts for cut-determining helices
	 if ( ! track_iter->pionQuality()->fitAbort()                  // - Just make sure it didn't abort
	      //   (since that might force the track
	      //   through the origin wrongly)
	    ) {
	    m_track_z0->fill( track_iter->pionHelix()->z0() );
	    m_shifted_track_z0->fill( track_iter->pionHelix()->z0() - weighted_z0 );
	    m_shifted_track_z0_close->fill( track_iter->pionHelix()->z0() - weighted_z0 );
	    m_track_momentum_mag->fill( track_iter->pionFit()->momentum().mag() );
	    m_track_momentum_perp->fill( track_iter->pionFit()->momentum().perp() );
	    m_track_momentum_z->fill( track_iter->pionFit()->momentum().z() );
	    m_track_chi2->fill( track_iter->pionQuality()->chiSquare() );
	    if ( track_iter->pionQuality()->degreesOfFreedom() > 0 )
	       m_track_chi2dof->fill( track_iter->pionQuality()->chiSquare() /
				      float( track_iter->pionQuality()->degreesOfFreedom() ) );
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
      /////////////////////////////////////////////////////////////////////

      float v[kNNtupleVars];
      v[kNumTracks] = cut_helix.size();
      v[kClosestIntersection] = closest_inter;
      v[kSecondClosestIntersection] = second_closest_inter;
      v[kThirdClosestIntersection] = third_closest_inter;
      v[kWeightedZ0] = weighted_z0;
      v[kCharge] = charge;
      v[kVisibleEnergy] = props->eVis();
      v[kNeutralEnergy] = props->neutralEnergy();
      v[kEventMomentumPerp] = props->totalMomentumVect().perp();
      v[kEventMomentumZ] = props->totalMomentumVect().z();

      v[kBiggestShowerEnergy] = props->firstLargestEShower();
      v[kSecondBiggestShowerEnergy] = props->secondLargestEShower();
      v[kThirdBiggestShowerEnergy] = props->thirdLargestEShower();
      v[kBiggestTrackMomentum] = props->firstLargestPTrack();
      v[kSecondBiggestTrackMomentum] = props->secondLargestPTrack();
      v[kNumberOfShowers] = num_showers;
      v[kChargedMomentumPerp] = chargedMomentum.perp();
      v[kChargedMomentumZ] = chargedMomentum.z();

      if ( m_ntupleSize.value() < 0.  ||  m_entriesInNtuple < m_ntupleSize.value() ) {
	 m_passNtuple->fill( v );
	 m_entriesInNtuple++;
      }
      return ActionBase::kPassed;
   }
   else {
      m_numTracks_failed->fill( cut_helix.size() );
      m_closestIntersection_failed->fill( closest_inter );
      m_weightedZ0_failed->fill( weighted_z0 );
      m_bunchWeightMargin_failed->fill( bunchweight_margin );

//        if ( m_ntupleSize.value() < 0.  ||  m_entriesInNtuple < m_ntupleSize.value() ) {
//  	 m_failNtuple->fill( v );
//  	 m_entriesInNtuple++;
//        }
      return ActionBase::kFailed;
   }
}

/*
ActionBase::ActionResult
HadronFilterProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
HadronFilterProc::endRun( Frame& iFrame )         // anal4 equiv.
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

double HadronFilterProc::closest_intersection( vector< KTHelix* > helix,
					       double beam_x, double beam_y, double veto )
{
   double bestxy(1000.);

   // This is a loop over the upper triangle of the helix-helix
   // matrix.
   int i, j;
   int nhelix( helix.size() );
   for ( i = 0;  i < nhelix;  i++ )
      for ( j = i + 1;  j < nhelix;  j++ ) {
	 double tx(-1000.), ty(-1000.), dummysigx(-1000.), dummysigy(-1000.);
	 
	 // Don't bother with any failed intersections
	 if ( calc_intersection( tx, ty, dummysigx, dummysigy, *helix[i], *helix[j] ) ) {
	    double xy( sqrt(sqr(tx - beam_x) + sqr(ty - beam_y)) );
	    if ( xy > veto  &&  xy < bestxy ) bestxy = xy;
	 } // end if intersection succeeded

      } // end loop over pairs of helices
   
   return bestxy;
}

DABoolean HadronFilterProc::event_vertex( double& x, double& y, double& sigx, double& sigy,
					  vector< KTHelix* > helix )
{
   // These only affect beamspot determination, it's not sensitive
   // enough to need to be a parameter.
   const int minHelices = 3;
   const double rmscut = 0.0005;

   vector< KTHelix* > subset;
   int i, j;
   for ( i = 0;  i < helix.size();  i++ )
      subset.push_back( helix[i] );

   // Throw out helices until all the intersections form a tight
   // little bunch with RMS < rmscut.
   while ( subset.size() >= minHelices ) {
      // trial x and y intersections
      vector< double > trialx;
      vector< double > trialy;
      vector< int > hindex1;
      vector< int > hindex2;

      // This loop runs over the upper triangle of the helix-helix
      // matrix.
      int nsubset( subset.size() );
      for ( i = 0;  i < nsubset;  i++ )
	 for ( j = i + 1;  j < nsubset;  j++ ) {
	    double tx(-1000.), ty(-1000.), dummysigx(-1000.), dummysigy(-1000.);

	    // Don't bother with any failed intersections
	    if ( calc_intersection( tx, ty, dummysigx, dummysigy, *subset[i], *subset[j] )  &&
		 zsep_test( tx, ty, *subset[i], *subset[j] ) ) {
	       trialx.push_back( tx );
	       trialy.push_back( ty );
	       hindex1.push_back( i );
	       hindex2.push_back( j );
	    } // end if good intersection
	 } // end loop over all pairs of helices
      if( trialx.size() == 0 ) return false;

      // Calculate the RMS of the cloud of intersections
      double rms( calc_rms(trialx, trialy, hindex1, hindex2) );
      if ( rms < rmscut ) break;

      // Now that we know the average and rms for all these trial
      // intersections, find the average and rms with one helix
      // missing, for each helix. The helix which, when missing,
      // reduces the rms the most is the first helix to remove.
      int besttoremove(-1);
      double bestsemirms(rms);
      DABoolean anyzero(false);
      for ( i = 0;  i < nsubset;  i++ ) {
	 double semirms( calc_rms(trialx, trialy, hindex1, hindex2, i) );

	 // If removing a helix leaves us with no intersections, this
	 // helix must not be dropped!
	 if ( semirms == 0. ) {
	    anyzero = true;
	    continue;
	 }

	 if ( semirms < bestsemirms ) {
	    bestsemirms = semirms;
	    besttoremove = i;
	 }
      } // end loop over helix indexes

      // If removing any helix just increases the rms, this is the
      // ideal set of helices.
      if ( besttoremove == -1 ) break;

      // I don't want to remove so many helices that I am left with
      // only one intersection.
      if ( anyzero ) break;

      vector< KTHelix* > tmp_copy;
      for ( i = 0;  i < nsubset;  i++ )
	 tmp_copy.push_back( subset[i] );
      subset.erase();
      for ( i = 0;  i < tmp_copy.size();  i++ )
	 if ( i != besttoremove )
	    subset.push_back( tmp_copy[i] );
   } // end while removing helices from the subset

   // Now we have an ideal set of helices. Let's recalculate the
   // intersections for a weighted mean. (So this time we'll need
   // uncertainties.)
   double numerx(0.), denomx(0.), numery(0.), denomy(0.);
   int subset_size( subset.size() );
   for ( i = 0;  i < subset_size;  i++ )
      for ( j = i + 1;  j < subset_size;  j++ ) {
	 double tx(-1000.), ty(-1000.), tsigx(-1000.), tsigy(-1000.);

	 // Don't bother with any failed intersections
	 if ( calc_intersection( tx, ty, tsigx, tsigy, *subset[i], *subset[j], true )  &&
	      zsep_test( tx, ty, *subset[i], *subset[j] ) ) {
	    numerx += tx / sqr(tsigx);
	    denomx += 1. / sqr(tsigx);

	    numery += ty / sqr(tsigy);
	    denomy += 1. / sqr(tsigy);
	 } // end if good intersection
      } // end loop over all pairs of intersections left
   
   if ( denomx == 0.  ||  denomy == 0. ) return false;

   x = numerx / denomx;
   sigx = sqrt( 1. / denomx );
   y = numery / denomy;
   sigy = sqrt( 1. / denomy );

   return true;
}

DABoolean HadronFilterProc::zsep_test( double x, double y, KTHelix& a, KTHelix& b )
{
   // This only affects beamspot determination, it's not sensitive
   // enough to need to be a parameter.
   const double zsepCut = 0.001;

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

   return abs(az - bz) < zsepCut;
}

double HadronFilterProc::calc_rms( vector< double >& trialx, vector< double >& trialy,
				   vector< int >& hindex1, vector< int >& hindex2,
				   int skip )
{
   int ninter( trialx.size() ), nleft(0);

   // Find the center
   double averagex(0.), averagey(0.);
   int i;
   for ( i = 0;  i < ninter;  i++ )
      if ( skip == -1  ||  ( hindex1[i] != skip  &&  hindex2[i] != skip ) ) {
	 averagex += trialx[i];
	 averagey += trialy[i];
	 nleft++;
      }
   if ( nleft == 0 ) {
      return 0.;
   }
   averagex /= double(nleft);
   averagey /= double(nleft);

   // Find the spread away from that center
   double rms(0.);
   for ( i = 0;  i < ninter;  i++ )
      if ( skip == -1  ||  ( hindex1[i] != skip  &&  hindex2[i] != skip ) )
	 rms += sqr(trialx[i] - averagex) + sqr(trialy[i] - averagey);
   rms /= double(nleft);
   rms = sqrt( rms );

   return rms;
}

DABoolean HadronFilterProc::calc_intersection( double& x, double& y, double& sigx, double& sigy,
					       KTHelix& a, KTHelix& b, DABoolean calc_uncerts )
{
   x = y = sigx = sigy = 1000.;  // To more easily find unchecked failures

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
   int which_num;
   char which_let;
   
   if ( !arclength1_ok  &&  !arclength2_ok ) return false;

   else if ( arclength1_ok  &&  !arclength2_ok ) {
      x = xsol1;  y = ysol1;  which_num = 1;
      if ( abs(ysol1 - ysol1a) < abs(ysol1 - ysol1b) )
	 which_let = 'a';  else  which_let = 'b';
   }

   else if ( !arclength1_ok  &&  arclength2_ok ) {
      x = xsol2;  y = ysol2;  which_num = 2;
      if ( abs(ysol2 - ysol2a) < abs(ysol2 - ysol2b) )
	 which_let = 'a';  else  which_let = 'b';
   }      

   else if ( sqr(xsol1) + sqr(ysol1) < sqr(xsol2) + sqr(ysol2) ) {
      x = xsol1;  y = ysol1;  which_num = 1;
      if ( abs(ysol1 - ysol1a) < abs(ysol1 - ysol1b) )
	 which_let = 'a';  else  which_let = 'b';
   }

   else {
      x = xsol2;  y = ysol2;  which_num = 2;
      if ( abs(ysol2 - ysol2a) < abs(ysol2 - ysol2b) )
	 which_let = 'a';  else  which_let = 'b';
   }      

   if ( ! calc_uncerts ) return true;

   // now for the derivatives
   double dpre_dra( (ra*(-xa + xb))/(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) );
   double dpre_dxa( (sqr(ra)*(sqr(xa) - 2.*xa*xb + sqr(xb) - sqr(ya - yb)) + 
		     sqr(rb)*(-sqr(xa) + 2.*xa*xb - sqr(xb) + sqr(ya - yb)) + 
		     pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.))/
		    (2.*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );
   double dpre_dya( ((sqr(ra) - sqr(rb))*(xa - xb)*(ya - yb))/
		    pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.) );
   double dpre_drb( (rb*(xa - xb))/(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) );
   double dpre_dxb( (sqr(rb)*(sqr(xa) - 2.*xa*xb + sqr(xb) - sqr(ya - yb)) + 
		     sqr(ra)*(-sqr(xa) + 2.*xa*xb - sqr(xb) + sqr(ya - yb)) + 
		     pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.))/
		    (2.*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );
   double dpre_dyb( -(((sqr(ra) - sqr(rb))*(xa - xb)*(ya - yb))/
		      pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );

   double ddisc_dra( (ra*sqr(ya - yb)*(-sqr(ra) + sqr(rb) + sqr(xa) - 2.*xa*xb + 
					 sqr(xb) + sqr(ya) - 2.*ya*yb + sqr(yb)))/
		     pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.) );
   double ddisc_dxa( -(((xa - xb)*sqr(ya - yb)*
			(-pow(ra,4.) + sqr(rb)*
			 (-sqr(rb) + sqr(xa) - 2.*xa*xb + sqr(xb) + 
			  sqr(ya) - 2.*ya*yb + sqr(yb)) + 
			 sqr(ra)*(2.*sqr(rb) + sqr(xa) - 2.*xa*xb + sqr(xb) + 
				    sqr(ya) - 2.*ya*yb + sqr(yb))))/
		       pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),3.)) );
   double ddisc_dya( ((-pow(4.*sqr(ra)*(xa - xb) - 
			    4.*(sqr(rb)*(xa - xb) + 
			       (xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + 
					  sqr(ya - yb))),2.) + 
		       4.*(-((xa + xb)*(4.*sqr(ra)*(xa - xb) - 
				       4.*(sqr(rb)*(xa - xb) + 
					  (xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + 
						     sqr(ya - yb))))) - 
			  4.*(-sqr(ra) - sqr(rb) + sqr(xa) + sqr(xb) + 
			     sqr(ya - yb))*
			  (sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) - 
			  2.*(pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
			     2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
			     2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
			     pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
			     4.*sqr(rb)*sqr(ya - yb)))*
		       (sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) + 
		       16.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))*
		       (pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
			2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
			2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
			pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
			4.*sqr(rb)*sqr(ya - yb)))*(ya - yb))/
		     (1.6*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),3.)) );
   double ddisc_drb( (rb*sqr(ya - yb)*(sqr(ra) - sqr(rb) + sqr(xa) - 2.*xa*xb + 
					 sqr(xb) + sqr(ya) - 2.*ya*yb + sqr(yb)))/
		     pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.) );
   double ddisc_dxb( ((xa - xb)*sqr(ya - yb)*(-pow(ra,4.) + 
						sqr(rb)*(-sqr(rb) + sqr(xa)
							   - 2.*xa*xb + sqr(xb) + 
							   sqr(ya) - 2.*ya*yb + sqr(yb)) + 
						sqr(ra)*(2.*sqr(rb) + sqr(xa)
							   - 2.*xa*xb + sqr(xb) + 
							   sqr(ya) - 2.*ya*yb + sqr(yb))))/
		     pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),3.) );
   double ddisc_dyb( ((pow(4.*sqr(ra)*(xa - xb) - 
			   4.*(sqr(rb)*(xa - xb) + 
			      (xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + 
					 sqr(ya - yb))),2.) + 
		       4.*((xa + xb)*(4.*sqr(ra)*(xa - xb) - 
				     4.*(sqr(rb)*(xa - xb) + 
					(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + 
						   sqr(ya - yb)))) - 
			  4.*(sqr(ra) + sqr(rb) - sqr(xa) - sqr(xb) - 
			     sqr(ya - yb))*
			  (sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) + 
			  2.*(pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
			     2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
			     2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
			     pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
			     4.*sqr(rb)*sqr(ya - yb)))*
		       (sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)) - 
		       16.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))*
		       (pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
			2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
			2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
			pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
			4.*sqr(rb)*sqr(ya - yb)))*(ya - yb))/
		     (1.6*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),3.)) );

   double dx_dcirc[kNumCirc];
   double dy_dcirc[kNumCirc];

   if ( which_num == 1 ) {
      dx_dcirc[kRa] = dpre_dra + ddisc_dra / 2. / sqrt( disc );
      dx_dcirc[kXa] = dpre_dxa + ddisc_dxa / 2. / sqrt( disc );
      dx_dcirc[kYa] = dpre_dya + ddisc_dya / 2. / sqrt( disc );
      dx_dcirc[kRb] = dpre_drb + ddisc_drb / 2. / sqrt( disc );
      dx_dcirc[kXb] = dpre_dxb + ddisc_dxb / 2. / sqrt( disc );
      dx_dcirc[kYb] = dpre_dyb + ddisc_dyb / 2. / sqrt( disc );
   }
   else {
      dx_dcirc[kRa] = dpre_dra - ddisc_dra / 2. / sqrt( disc );
      dx_dcirc[kXa] = dpre_dxa - ddisc_dxa / 2. / sqrt( disc );
      dx_dcirc[kYa] = dpre_dya - ddisc_dya / 2. / sqrt( disc );
      dx_dcirc[kRb] = dpre_drb - ddisc_drb / 2. / sqrt( disc );
      dx_dcirc[kXb] = dpre_dxb - ddisc_dxb / 2. / sqrt( disc );
      dx_dcirc[kYb] = dpre_dyb - ddisc_dyb / 2. / sqrt( disc );
   }

   if ( which_let == 'a' ) {
      dy_dcirc[kRa] = -(x - xb) * dx_dcirc[kRa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kXa] = -(x - xb) * dx_dcirc[kXa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kYa] = -(x - xb) * dx_dcirc[kYa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kRb] = (rb - (x - xb)*dx_dcirc[kRb]) / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kXb] = -(x - xb) * (dx_dcirc[kXb] - 1.) / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kYb] = 1. - (x - xb)*dx_dcirc[kYb]/sqrt( sqr(rb) - sqr(x - xb) );
   }
   else {
      dy_dcirc[kRa] = (x - xb) * dx_dcirc[kRa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kXa] = (x - xb) * dx_dcirc[kXa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kYa] = (x - xb) * dx_dcirc[kYa] / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kRb] = (-rb + (x - xb)*dx_dcirc[kRb]) / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kXb] = (x - xb) * (dx_dcirc[kXb] - 1.) / sqrt( sqr(rb) - sqr(x - xb) );
      dy_dcirc[kYb] = 1. + (x - xb)*dx_dcirc[kYb]/sqrt( sqr(rb) - sqr(x - xb) );
   }

   // This is a Jacobian for transforming between circle variables and
   // tracking variables
   double dcirc_dtrack[kNumCirc][kNumTrack];
   int i, j;
   for ( i = 0;  i < kNumCirc;  i++ )
      for ( j = 0;  j < kNumTrack;  j++ )
	 dcirc_dtrack[i][j] = 0;
   
   dcirc_dtrack[kRa][kCurva] = -1. / 2. / sqr( a.curvature() );

   dcirc_dtrack[kXa][kCurva] = -dcirc_dtrack[kRa][kCurva] * sin( a.phi0() );
   dcirc_dtrack[kXa][kD0a]   = -sin( a.phi0() );
   dcirc_dtrack[kXa][kPhi0a] = -(ra + a.d0()) * cos( a.phi0() );

   dcirc_dtrack[kYa][kCurva] = dcirc_dtrack[kRa][kCurva] * cos( a.phi0() );
   dcirc_dtrack[kYa][kD0a]   = cos( a.phi0() );
   dcirc_dtrack[kYa][kPhi0a] = -(ra + a.d0()) * sin( a.phi0() );

   dcirc_dtrack[kRb][kCurvb] = -1. / 2. / sqr( b.curvature() );

   dcirc_dtrack[kXb][kCurvb] = -dcirc_dtrack[kRb][kCurvb] * sin( b.phi0() );
   dcirc_dtrack[kXb][kD0b]   = -sin( b.phi0() );
   dcirc_dtrack[kXb][kPhi0b] = -(rb + b.d0()) * cos( b.phi0() );

   dcirc_dtrack[kYb][kCurvb] = dcirc_dtrack[kRb][kCurvb] * cos( b.phi0() );
   dcirc_dtrack[kYb][kD0b]   = cos( b.phi0() );
   dcirc_dtrack[kYb][kPhi0b] = -(rb + b.d0()) * sin( b.phi0() );

   // Finally--- derivatives of x and y in terms of tracking variables!
   double dx_dtrack[kNumTrack];
   double dy_dtrack[kNumTrack];
   for ( j = 0;  j < kNumTrack;  j++ ) {
      dx_dtrack[j] = 0;
      dy_dtrack[j] = 0;
   }

   for ( i = 0;  i < kNumCirc;  i++ )
      for ( j = 0;  j < kNumTrack;  j++ ) {
	 dx_dtrack[j] += dx_dcirc[i] * dcirc_dtrack[i][j];
	 dy_dtrack[j] += dy_dcirc[i] * dcirc_dtrack[i][j];
      }

   // Propogating errors is a similarity transform. First we need a
   // transformation matrix.
   double sigma[kNumTrack][kNumTrack];
   for ( i = 0;  i < kNumTrack;  i++ )
      for ( j = 0;  j < kNumTrack;  j++ )
	 sigma[i][j] = 0;

   sigma[kCurva][kCurva] = a.errorMatrix()(KTHelix::kCurvature, KTHelix::kCurvature);
   sigma[kCurva][kD0a]   = a.errorMatrix()(KTHelix::kCurvature, KTHelix::kD0);
   sigma[kCurva][kPhi0a] = a.errorMatrix()(KTHelix::kCurvature, KTHelix::kPhi0);
   sigma[kD0a][kCurva]   = a.errorMatrix()(KTHelix::kD0, KTHelix::kCurvature);
   sigma[kD0a][kD0a]     = a.errorMatrix()(KTHelix::kD0, KTHelix::kD0);
   sigma[kD0a][kPhi0a]   = a.errorMatrix()(KTHelix::kD0, KTHelix::kPhi0);
   sigma[kPhi0a][kCurva] = a.errorMatrix()(KTHelix::kPhi0, KTHelix::kCurvature);
   sigma[kPhi0a][kD0a]   = a.errorMatrix()(KTHelix::kPhi0, KTHelix::kD0);
   sigma[kPhi0a][kPhi0a] = a.errorMatrix()(KTHelix::kPhi0, KTHelix::kPhi0);

   sigma[kCurvb][kCurvb] = b.errorMatrix()(KTHelix::kCurvature, KTHelix::kCurvature);
   sigma[kCurvb][kD0b]   = b.errorMatrix()(KTHelix::kCurvature, KTHelix::kD0);
   sigma[kCurvb][kPhi0b] = b.errorMatrix()(KTHelix::kCurvature, KTHelix::kPhi0);
   sigma[kD0b][kCurvb]   = b.errorMatrix()(KTHelix::kD0, KTHelix::kCurvature);
   sigma[kD0b][kD0b]     = b.errorMatrix()(KTHelix::kD0, KTHelix::kD0);
   sigma[kD0b][kPhi0b]   = b.errorMatrix()(KTHelix::kD0, KTHelix::kPhi0);
   sigma[kPhi0b][kCurvb] = b.errorMatrix()(KTHelix::kPhi0, KTHelix::kCurvature);
   sigma[kPhi0b][kD0b]   = b.errorMatrix()(KTHelix::kPhi0, KTHelix::kD0);
   sigma[kPhi0b][kPhi0b] = b.errorMatrix()(KTHelix::kPhi0, KTHelix::kPhi0);

   double x_std[kNumTrack];  // (sigma-transformed derivatives... errormatrix * dx_dtrack)
   double y_std[kNumTrack];  // (sigma-transformed derivatives... errormatrix * dy_dtrack)
   for ( j = 0;  j < kNumTrack;  j++ ) {
      x_std[j] = 0;  // (it's better than "vd"--- vector of derivatives...)
      y_std[j] = 0;
   }   

   for ( i = 0;  i < kNumTrack;  i++ )
      for ( j = 0;  j < kNumTrack;  j++ ) {
	 if ( dx_dtrack[i] != 0. )
	    x_std[j] += sigma[i][j] * dx_dtrack[i];
	 if ( dy_dtrack[i] != 0. )
	    y_std[j] += sigma[i][j] * dy_dtrack[i];
      }

   double sig2x(0.);
   double sig2y(0.);
//     double sig2xy(0.);

   for ( i = 0;  i < kNumTrack;  i++ ) {
      sig2x += dx_dtrack[i] * x_std[i];
      sig2y += dy_dtrack[i] * y_std[i];
//        sig2xy += dy_dtrack[i] * x_std[i];
   }

   sigx = sqrt(sig2x);
   sigy = sqrt(sig2y);
}

DABoolean HadronFilterProc::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
{
   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   return ( aarclength > -m_tailCut.value()  &&  aarclength < M_PI/2./abs(a.curvature()) )  &&
      ( barclength > -m_tailCut.value()  &&  barclength < M_PI/2./abs(b.curvature()) );
}

