// -*- C++ -*-
//
// Package:     TestBeamGas
// Module:      TestBeamGas
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Feb  4 16:45:09 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TestBeamGas/TestBeamGas.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"

#include "Navigation/NavShower.h"
#include "Navigation/NavTkShMatch.h"
#include "C3cc/CcShowerAttributes.h"

#include "CleoDB/DBEventHeader.h"
#include "EventProperties/EventProperties.h"
#include "BeamSpot/BeamSpot.h"
#include "BeamEnergy/BeamEnergy.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"

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
static const char* const kFacilityString = "Processor.TestBeamGas" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_01 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TestBeamGas::TestBeamGas( void )               // anal1
   : Processor( "TestBeamGas" )
   , m_closestIntersectionCut( "closestIntersectionCut", this, 0.005 )
   , m_weightedZCut( "weightedZCut", this, 0.05 )
   , m_weightedZCleverness( "weightedZCleverness", this, 0. )
   , m_explicitBeamSpot( "explicitBeamSpot", this, false )
   , m_beamX( "beamX", this, 0. )
   , m_beamY( "beamY", this, 0. )
   , m_beamZ( "beamZ", this, 0. )
   , m_beam_x(0.)
   , m_beam_y(0.)
   , m_beam_z(0.)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TestBeamGas::event,    Stream::kEvent );
   bind( &TestBeamGas::beginRun, Stream::kBeginRun );
   //bind( &TestBeamGas::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

TestBeamGas::~TestBeamGas()                    // anal5
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
TestBeamGas::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TestBeamGas::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
TestBeamGas::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_charge = iHistoManager.histogram(
      100, "charge (bkh)", 31, -15.5, 15.5);

   m_z = iHistoManager.histogram(
      200, "z", 60, -0.30, 0.30);
   m_z_p1 = iHistoManager.histogram(
      201, "z Q.ge.1", 60, -0.30, 0.30);
   m_z_m1 = iHistoManager.histogram(
      202, "z Q.le.-1", 60, -0.30, 0.30);
   m_z_p2 = iHistoManager.histogram(
      203, "z Q.ge.2", 60, -0.30, 0.30);
   m_z_m2 = iHistoManager.histogram(
      204, "z Q.le.-2", 60, -0.30, 0.30);

   m_track_z0 = iHistoManager.histogram(
      300, "track z0", 200, -0.5, 0.5);
   m_track_z0_p1 = iHistoManager.histogram(
      301, "track z0 Q.ge.1", 200, -0.5, 0.5);
   m_track_z0_m1 = iHistoManager.histogram(
      302, "track z0 Q.le.-1", 200, -0.5, 0.5);
   m_track_z0_p2 = iHistoManager.histogram(
      303, "track z0 Q.ge.2", 200, -0.5, 0.5);
   m_track_z0_m2 = iHistoManager.histogram(
      304, "track z0 Q.le.-2", 200, -0.5, 0.5);

   m_track_z0_z = iHistoManager.histogram(
      400, "track z0 - event z", 200, -0.5, 0.5);
   m_track_z0_p1_z = iHistoManager.histogram(
      401, "track z0 - event z Q.ge.1", 200, -0.5, 0.5);
   m_track_z0_m1_z = iHistoManager.histogram(
      402, "track z0 - event z Q.le.-1", 200, -0.5, 0.5);
   m_track_z0_p2_z = iHistoManager.histogram(
      403, "track z0 - event z Q.ge.2", 200, -0.5, 0.5);
   m_track_z0_m2_z = iHistoManager.histogram(
      404, "track z0 - event z Q.le.-2", 200, -0.5, 0.5);

   m_track_pmag = iHistoManager.histogram(
      500, "track pmag", 100, 0., 3.);
   m_track_pmag_p1 = iHistoManager.histogram(
      501, "track pmag Q.ge.1", 100, 0., 3.);
   m_track_pmag_m1 = iHistoManager.histogram(
      502, "track pmag Q.le.-1", 100, 0., 3.);
   m_track_pmag_p2 = iHistoManager.histogram(
      503, "track pmag Q.ge.2", 100, 0., 3.);
   m_track_pmag_m2 = iHistoManager.histogram(
      504, "track pmag Q.le.-2", 100, 0., 3.);

   m_track_pperp = iHistoManager.histogram(
      600, "track pperp", 100, 0., 3.);
   m_track_pperp_p1 = iHistoManager.histogram(
      601, "track pperp Q.ge.1", 100, 0., 3.);
   m_track_pperp_m1 = iHistoManager.histogram(
      602, "track pperp Q.le.-1", 100, 0., 3.);
   m_track_pperp_p2 = iHistoManager.histogram(
      603, "track pperp Q.ge.2", 100, 0., 3.);
   m_track_pperp_m2 = iHistoManager.histogram(
      604, "track pperp Q.le.-2", 100, 0., 3.);

   m_track_pz = iHistoManager.histogram(
      700, "track pz", 100, -3., 3.);
   m_track_pz_p1 = iHistoManager.histogram(
      701, "track pz Q.ge.1", 100, -3., 3.);
   m_track_pz_m1 = iHistoManager.histogram(
      702, "track pz Q.le.-1", 100, -3., 3.);
   m_track_pz_p2 = iHistoManager.histogram(
      703, "track pz Q.ge.2", 100, -3., 3.);
   m_track_pz_m2 = iHistoManager.histogram(
      704, "track pz Q.le.-2", 100, -3., 3.);

   m_shower_e = iHistoManager.histogram(
      800, "shower e", 100, 0., 2.);
   m_shower_e_p1 = iHistoManager.histogram(
      801, "shower e Q.ge.1", 100, 0., 2.);
   m_shower_e_m1 = iHistoManager.histogram(
      802, "shower e Q.le.-1", 100, 0., 2.);
   m_shower_e_p2 = iHistoManager.histogram(
      803, "shower e Q.ge.2", 100, 0., 2.);
   m_shower_e_m2 = iHistoManager.histogram(
      804, "shower e Q.le.-2", 100, 0., 2.);

   const char* label[kNumEntries] = {
      "q",
      "z", "neue", "vise", "mat1", "mat2", "nsh", "cce", 
      "sh1", "sh2", "sh3", "sh4", "sh5",
      "ntr", "bkh_cce", "bkh_sh1", "tr1", "tr2", "ebeam", "ci",
      "pmag", "pperp", "pz" };
   m_ntuple = iHistoManager.ntuple(
      1, "event", kNumEntries, 262144, label );

   const char* shower_label[kSHOWERNumEntries] = {
      "hot", "en", "stat", "nomat", "nomatcr", "brval", "brmatval", "breop" };
   m_shower_ntuple = iHistoManager.ntuple(
      2, "shower", kSHOWERNumEntries, 262144, shower_label );

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TestBeamGas::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   double z(calc_z(iFrame));
   double ci(calc_ci(iFrame));

   FAItem<EventProperties> prop;
   extract(iFrame.record(Stream::kEvent), prop);
   
   int num_tracks(prop->nbChargedTracks());
   int charge(prop->netCharge());
   double neutralEnergy(prop->neutralEnergy());
   double visibleEnergy(prop->eVis());
   double bkh_shower_energy(prop->ccTotalEnergy());
   double bkh_shower1(prop->firstLargestEShower());
   double matched1(prop->firstMatchedEnergy());
   double matched2(prop->secondMatchedEnergy());
   double track1(prop->firstLargestPTrack());
   double track2(prop->secondLargestPTrack());
   double eventp_mag(prop->totalMomentumVect().mag());
   double eventp_perp(prop->totalMomentumVect().perp());
   double eventp_z(prop->totalMomentumVect().z());

   FATable<NavTrack> track;
   extract(iFrame.record(Stream::kEvent), track);
   FATable<NavTrack>::const_iterator track_end = track.end();

//   if ( abs(z) > 0.05 )
   if ( true )
      for ( FATable<NavTrack>::const_iterator track_iter = track.begin();
	    track_iter != track_end;
	    ++track_iter ) {
	 m_track_z0->fill(track_iter->pionHelix()->z0());
	 if ( charge >= 1 ) m_track_z0_p1->fill(track_iter->pionHelix()->z0());
	 if ( charge <= -1 ) m_track_z0_m1->fill(track_iter->pionHelix()->z0());
	 if ( charge >= 2 ) m_track_z0_p2->fill(track_iter->pionHelix()->z0());
	 if ( charge <= -2 ) m_track_z0_m2->fill(track_iter->pionHelix()->z0());

	 m_track_z0_z->fill(track_iter->pionHelix()->z0() - z);
	 if ( charge >= 1 ) m_track_z0_p1_z->fill(track_iter->pionHelix()->z0() - z);
	 if ( charge <= -1 ) m_track_z0_m1_z->fill(track_iter->pionHelix()->z0() - z);
	 if ( charge >= 2 ) m_track_z0_p2_z->fill(track_iter->pionHelix()->z0() - z);
	 if ( charge <= -2 ) m_track_z0_m2_z->fill(track_iter->pionHelix()->z0() - z);

	 m_track_pmag->fill(track_iter->pionFit()->momentum().mag());
	 if ( charge >= 1 ) m_track_pmag_p1->fill(track_iter->pionFit()->momentum().mag());
	 if ( charge <= -1 ) m_track_pmag_m1->fill(track_iter->pionFit()->momentum().mag());
	 if ( charge >= 2 ) m_track_pmag_p2->fill(track_iter->pionFit()->momentum().mag());
	 if ( charge <= -2 ) m_track_pmag_m2->fill(track_iter->pionFit()->momentum().mag());

	 m_track_pperp->fill(track_iter->pionFit()->momentum().perp());
	 if ( charge >= 1 ) m_track_pperp_p1->fill(track_iter->pionFit()->momentum().perp());
	 if ( charge <= -1 ) m_track_pperp_m1->fill(track_iter->pionFit()->momentum().perp());
	 if ( charge >= 2 ) m_track_pperp_p2->fill(track_iter->pionFit()->momentum().perp());
	 if ( charge <= -2 ) m_track_pperp_m2->fill(track_iter->pionFit()->momentum().perp());

	 m_track_pz->fill(track_iter->pionFit()->momentum().z());
	 if ( charge >= 1 ) m_track_pz_p1->fill(track_iter->pionFit()->momentum().z());
	 if ( charge <= -1 ) m_track_pz_m1->fill(track_iter->pionFit()->momentum().z());
	 if ( charge >= 2 ) m_track_pz_p2->fill(track_iter->pionFit()->momentum().z());
	 if ( charge <= -2 ) m_track_pz_m2->fill(track_iter->pionFit()->momentum().z());
      }

   FATable<NavShower> shower;
   extract(iFrame.record(Stream::kEvent), shower);
   FATable<NavShower>::const_iterator shower_end = shower.end();

   FAItem<BeamEnergy> beam;
   extract(iFrame.record(Stream::kStartRun), beam);

   int num_showers(0);
   double shower_energy(0.);
   double shower1(0.);
   double shower2(0.);
   double shower3(0.);
   double shower4(0.);
   double shower5(0.);

   for ( FATable<NavShower>::const_iterator shower_iter = shower.begin();
	 shower_iter != shower_end;
	 ++shower_iter ) {
      float v[kSHOWERNumEntries];
      for ( int i = 0;  i < kSHOWERNumEntries;  i++ ) v[i] = 0.;
      v[kSHOWERHot] = shower_iter->attributes().hot();
      v[kSHOWEREnergy] = shower_iter->attributes().energy();
      v[kSHOWERStatus] = shower_iter->attributes().status();
      v[kSHOWERnoTrackMatch] = shower_iter->noTrackMatch();
      v[kSHOWERnoTrackMatchConReg] = shower_iter->noTrackMatchConReg();
      v[kSHOWERbremTrackValid] = shower_iter->bremTrack().valid();
      if ( shower_iter->bremTrack().valid() ) {
	 v[kSHOWERbremTrackShowerMatchValid] = shower_iter->bremTrack()->trackShowerMatch().valid();
	 if ( shower_iter->bremTrack()->trackShowerMatch().valid() ) {
	    v[kSHOWERbremTrackShowerMatchEoverP] = shower_iter->bremTrack()->trackShowerMatch()->eOverP();
	 } // end if trackShowerMatch is valid
      } // end if bremTrack is valid
//      if ( abs(z) > 0.05 ) m_shower_ntuple->fill(v);
      m_shower_ntuple->fill(v);

      if ( !shower_iter->attributes().hot()                        &&
	   shower_iter->attributes().status()                      &&
	   shower_iter->attributes().energy() > 0.01*beam->value()    ) {
	 num_showers++;
	 shower_energy += shower_iter->attributes().energy();

	 double energy(shower_iter->attributes().energy());
	 if ( energy > shower1 ) {
	    shower5 = shower4;
	    shower4 = shower3;
	    shower3 = shower2;
	    shower2 = shower1;
	    shower1 = energy;
	 }
	 else if ( energy > shower2 ) {
	    shower5 = shower4;
	    shower4 = shower3;
	    shower3 = shower2;
	    shower2 = energy;
	 }
	 else if ( energy > shower3 ) {
	    shower5 = shower4;
	    shower4 = shower3;
	    shower3 = energy;
	 }
	 else if ( energy > shower4 ) {
	    shower5 = shower4;
	    shower4 = energy;
	 }
	 else if ( energy > shower5 ) {
	    shower5 = energy;
	 }

//	 if ( abs(z) > 0.05 ) {
	 if ( true ) {
	    m_shower_e->fill(energy);
	    if ( charge >= 1 ) m_shower_e_p1->fill(energy);
	    if ( charge <= -1 ) m_shower_e_m1->fill(energy);
	    if ( charge >= 2 ) m_shower_e_p2->fill(energy);
	    if ( charge <= -2 ) m_shower_e_m2->fill(energy);
	 }

      } // end if shower good
   } // loop over showers

   m_charge->fill(charge);

   m_z->fill(z);
   if ( charge >= 1 ) m_z_p1->fill(z);
   if ( charge <= -1 ) m_z_m1->fill(z);
   if ( charge >= 2 ) m_z_p2->fill(z);
   if ( charge <= -2 ) m_z_m2->fill(z);

   float v[kNumEntries];
   v[kCharge] = charge;
   v[kZ] = z;
   v[kNeutralenergy] = neutralEnergy;
   v[kVisibleenergy] = visibleEnergy;
   v[kMatched1] = matched1;
   v[kMatched2] = matched2;
   v[kNumShowers] = num_showers;
   v[kShowerEnergy] = shower_energy;
   v[kShower1] = shower1;
   v[kShower2] = shower2;
   v[kShower3] = shower3;
   v[kShower4] = shower4;
   v[kShower5] = shower5;
   v[kNumTracks] = num_tracks;
   v[kBKHShowerEnergy] = bkh_shower_energy;
   v[kBKHShower1] = bkh_shower1;
   v[kTrack1] = track1;
   v[kTrack2] = track2;
   v[kEBeam] = beam->value();
   v[kClosestIntersection] = ci;
   v[kEventPMag] = eventp_mag;
   v[kEventPPerp] = eventp_perp;
   v[kEventPZ] = eventp_z;

//   if ( abs(z) > 0.05 ) m_ntuple->fill(v);
   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

ActionBase::ActionResult
TestBeamGas::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   m_beam_x = m_beamX.value();
   m_beam_y = m_beamY.value();
   m_beam_z = m_beamZ.value();

   if ( ! m_explicitBeamSpot.value() ) {
      FAItem< BeamSpot > spot;
      extract( iFrame.record( Stream::kBeginRun ), spot );
      m_beam_x = spot->center().x();
      m_beam_y = spot->center().y();
      m_beam_z = spot->center().z();
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
TestBeamGas::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

double
TestBeamGas::calc_z(Frame& iFrame)
{
   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   double weighted_z(1000.);
   double znumer(0.);
   double zdenom(0.);

   FATable< NavTrack >::const_iterator track_iter;
   FATable< NavTrack >::const_iterator other_iter;
   for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ ) {
      if ( ! track_iter->seedQuality()->originUsed()            &&
	   ! track_iter->pionQuality()->fitAbort()              &&
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&
	   ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {
	 // Secondary track loop to calculate pairwise intersections
	 for ( other_iter = track_iter;  other_iter != tracks_end;  other_iter++ ) {
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

		  double perp( sqrt(sqr(tx - m_beam_x) + sqr(ty - m_beam_y)) );

		  if ( abs(m_weightedZCleverness.value() - 0.) < .1 ) {
		     // uncertainty in the z intersection + mismatch in z + mismatch in perp
		     double z_uncert2( tsig2z + sqr(tzsep) + sqr(tx - m_beam_x) + sqr(ty - m_beam_y) );
		     znumer += tz / z_uncert2;
		     zdenom += 1. / z_uncert2;
		  }
		  else if ( abs(m_weightedZCleverness.value() - -1.) < .1 ) {
		     // uncertainty in the z intersection + mismatch in z, cut on perp
		     if ( perp > m_closestIntersectionCut.value() ) {
			double z_uncert2( tsig2z + sqr(tzsep) );
			znumer += tz / z_uncert2;
			zdenom += 1. / z_uncert2;
		     }
		  }
		  else {
		     report(EMERGENCY, kFacilityString)
			<< "unknown weightedZCleverness mode"
			<< m_weightedZCleverness.value() << endl;
		     assert(false);
		  }

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over tracks

   if ( zdenom != 0. ) weighted_z = znumer / zdenom;

   return weighted_z - m_beam_z;
}

double
TestBeamGas::calc_ci(Frame& iFrame)
{
   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   double ci(1000.);

   FATable< NavTrack >::const_iterator track_iter;
   FATable< NavTrack >::const_iterator other_iter;
   for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ ) {
      if ( ! track_iter->seedQuality()->originUsed()            &&
	   ! track_iter->pionQuality()->fitAbort()              &&
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&
	   ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {
	 // Secondary track loop to calculate pairwise intersections
	 for ( other_iter = track_iter;  other_iter != tracks_end;  other_iter++ ) {
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

		  double perp( sqrt(sqr(tx - m_beam_x) + sqr(ty - m_beam_y)) );
		  if ( perp < ci ) ci = perp;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over tracks

   return ci;
}

DABoolean TestBeamGas::calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean TestBeamGas::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
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
