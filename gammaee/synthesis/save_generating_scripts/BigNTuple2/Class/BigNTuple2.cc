// -*- C++ -*-
//
// Package:     BigNTuple2
// Module:      BigNTuple2
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim McCann
// Created:     Thu May 30 15:00:07 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "BigNTuple2/BigNTuple2.h"
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

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"
#include "C3Mu/MuTrack.h"
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "Navigation/NavConReg.h"
#include "KinematicTrajectory/KTKinematicData.h"
#include "KinematicTrajectory/KTHelix.h"
#include "TrackRoot/TRHelixFit.h"
#include "Navigation/NavTkShMatch.h"
#include "C3cc/CcAssignedEnergyHit.h"
#include "BunchFinder/BunchDecision.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"
#include "/home/mccann/hadron_filter/src/EventVertex/EventVertex/EventVertex.h"
#include "CleoDB/DBEventHeader.h"
#include "EventProperties/EventProperties.h"

#include <vector>

// #include <stdlib.h>
// #define random ( double( rand() ) / ( pow(2,15) - 1. ) )

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
static const char* const kFacilityString = "Processor.BigNTuple2" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.30 2002/04/02 22:04:09 ajm36 Exp $";
static const char* const kTagString = "$Name: v06_05_01 $";

//
// static data member definitions
//



//
// constructors and destructor
//
BigNTuple2::BigNTuple2( void )               // anal1
   : Processor( "BigNTuple2" )
   , m_lookForCosmics( "lookForCosmics", this, false )
   , m_getBunchData( "getBunchData", this, true )
   , m_showBad( "showBad", this, false )
   , m_rmsCut( "rmsCut", this, 0.000500 )
   , m_tailCut( "tailCut", this, 0.005 )
   , m_interestingOnly( "interestingOnly", this, false )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &BigNTuple2::event,    Stream::kEvent );
   //bind( &BigNTuple2::beginRun, Stream::kBeginRun );
   //bind( &BigNTuple2::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

//   srand( 452135 );

}

BigNTuple2::~BigNTuple2()                    // anal5
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
BigNTuple2::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
BigNTuple2::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

const double cosmic_energy_low = 0.210-0.060;
const double cosmic_energy_high = 0.210+0.060;

const double cosmic_phi0diff_low = 3.1415926-0.005;
const double cosmic_phi0diff_high = 3.1415926+0.005;

const double cosmic_d0sum_low = -0.0005;
const double cosmic_d0sum_high = 0.0005;
		    
const double cosmic_z0diff_low = -0.001;
const double cosmic_z0diff_high = 0.001;
		    
const double cosmic_cotThetadiff_low = -0.015;
const double cosmic_cotThetadiff_high = 0.015;

const char* ntuple_labels[BigNTuple2::kEntries] = {
   "evtnum",
   "w_z0",
   "w_d0",
   "charge",
   "ch_px",
   "ch_py",
   "ch_pz",
   "n_px",
   "n_py",
   "n_pz",
   "num_sh",
   "num_un",
   "num_tr",
   "tot_sh_e",
   "max_sh_e",
   "tot_un_e",
   "max_un_e",
   "tot_tr_p",
   "ttp_th",
   "ttp_phi",
   "max_tr_p",
   "tot_tr_e",
   "max_tr_e",
   "bw_best",
   "bw_next",
   "v_x",
   "v_y",
   "v_z",
   "v_chi2",
   "v_chi2pT",
   "x",
   "y",
   "sigx",
   "sigy",
   "xydist",
   "zsep",
   "eneu"
};

// ---------------- standard place to book histograms ---------------
void
BigNTuple2::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_cosmic = iHistoManager.ntuple(
      1, "cosmic", kEntries, 262144, ntuple_labels );

   m_other = iHistoManager.ntuple(
      2, "other", kEntries, 262144, ntuple_labels );

   m_cosmic_energy = iHistoManager.histogram(
      100, "cosmic energy", 100, cosmic_energy_low, cosmic_energy_high );
   m_cosmic_phi0diff = iHistoManager.histogram(
      200, "cosmic phi0diff", 100, cosmic_phi0diff_low, cosmic_phi0diff_high );
   m_cosmic_d0sum = iHistoManager.histogram(
      300, "cosmic d0sum", 100, cosmic_d0sum_low, cosmic_d0sum_high );
   m_cosmic_z0diff = iHistoManager.histogram(
      400, "cosmic z0diff", 100, cosmic_z0diff_low, cosmic_z0diff_high );
   m_cosmic_cotThetadiff = iHistoManager.histogram(
      500, "cosmic cotThetadiff", 100, cosmic_cotThetadiff_low, cosmic_cotThetadiff_high );
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
BigNTuple2::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   DABoolean isCosmic( false );

   FATable< NavShower > navshowers;
   extract( iFrame.record( Stream::kEvent ), navshowers );
   FATable< NavShower >::const_iterator showers_end = navshowers.end();

   FATable< NavTrack > navtracks;
   extract( iFrame.record( Stream::kEvent ), navtracks );
   FATable< NavTrack >::const_iterator tracks_end = navtracks.end();

   FAItem< TrackletBunchDecision > bunchDecision;
   if ( m_getBunchData.value() )
      extract( iFrame.record( Stream::kEvent ), bunchDecision );

   FAItem< DBEventHeader > header;
   extract( iFrame.record( Stream::kEvent ), header );

   FAItem< EventProperties > props;
   extract( iFrame.record( Stream::kEvent ), props );

//     FAItem< EventVertex > eventVertex;
//     if ( navtracks.size() > 2 )
//        extract( iFrame.record( Stream::kEvent ), eventVertex );

//     if ( m_lookForCosmics.value() )
//        if ( navtracks.size() == 2 ) {

//  	 FATable< MuTrack > mutracks;
//  	 extract( iFrame.record( Stream::kEvent ), mutracks );

//  	 if ( mutracks.size() == 2 ) {

//  	    FATable< MuTrack >::const_iterator secondMu = mutracks.begin();
//  	    FATable< MuTrack >::const_iterator firstMu = secondMu;
//  	    secondMu++;

//  	    if ( firstMu->dpthmu() > 3.  &&
//  		 secondMu->dpthmu() > 3.     ) {

//  	       FATable< NavTrack >::const_iterator secondNav = navtracks.begin();
//  	       FATable< NavTrack >::const_iterator firstNav = secondNav;
//  	       secondNav++;

//  	       if ( ! firstNav->pionQuality()->fitAbort()  &&
//  		    ! secondNav->pionQuality()->fitAbort()     ) {

//  		  if ( ! firstNav->seedQuality()->originUsed()  &&
//  		       ! secondNav->seedQuality()->originUsed()     ) {

//  		     int suspicious_showers( 0 );
//  		     double suspicious_energy[2];
//  		     for ( FATable< NavShower >::const_iterator shower_iter = navshowers.begin();
//  			   shower_iter != showers_end;
//  			   shower_iter++ ) {

//  			double energy( shower_iter->attributes().energy() );

//  			if ( cosmic_energy_low < energy && energy < cosmic_energy_high  &&
//  			     ! shower_iter->attributes().hot()                          &&
//  			     shower_iter->trackMatches().size() == 1                       ) {

//  			   if ( suspicious_showers < 2 )
//  			      suspicious_energy[ suspicious_showers ] = energy;
//  			   suspicious_showers++;

//  			}
//  		     } // end loop over showers

//  		     if ( suspicious_showers == 2 ) {

//  			FAItem< TRHelixFit > firstHelix = firstNav->pionHelix();
//  			FAItem< TRHelixFit > secondHelix = secondNav->pionHelix();

//  			double phi0diff( firstHelix->phi0() - secondHelix->phi0() );
//  			if ( phi0diff < 0. ) phi0diff *= -1.;
//  			double d0sum( firstHelix->d0() + secondHelix->d0() );
//  			double z0diff( firstHelix->z0() - secondHelix->z0() );
//  			double cotThetadiff( firstHelix->cotTheta() + secondHelix->cotTheta() );

//  			report( DEBUG, kFacilityString ) << "energy1 = " << suspicious_energy[0] << endl;
//  			report( DEBUG, kFacilityString ) << "energy2 = " << suspicious_energy[1] << endl;
//  			report( DEBUG, kFacilityString ) << "phi0diff = " << phi0diff << endl;
//  			report( DEBUG, kFacilityString ) << "d0sum = " << d0sum << endl;
//  			report( DEBUG, kFacilityString ) << "z0diff = " << z0diff << endl;
//  			report( DEBUG, kFacilityString ) << "cotThetadiff = " << cotThetadiff << endl;

//  			if ( cosmic_phi0diff_low < phi0diff         &&  phi0diff < cosmic_phi0diff_high         &&
//  			     cosmic_d0sum_low < d0sum               &&  d0sum < cosmic_d0sum_high               &&
//  			     cosmic_z0diff_low < z0diff             &&  z0diff < cosmic_z0diff_high             &&
//  			     cosmic_cotThetadiff_low < cotThetadiff && cotThetadiff < cosmic_cotThetadiff_high     ) {

//  			   isCosmic = true;

//  			   m_cosmic_energy->fill( suspicious_energy[0] );
//  			   m_cosmic_energy->fill( suspicious_energy[1] );
//  			   m_cosmic_phi0diff->fill( phi0diff );
//  			   m_cosmic_d0sum->fill( d0sum );
//  			   m_cosmic_z0diff->fill( z0diff );
//  			   m_cosmic_cotThetadiff->fill( cotThetadiff );

//  			} } } } } } } // end tests for isCosmic

   float v[kEntries];
   for ( int i = 0;  i < kEntries;  i++ ) v[i] = 0.;
   
   v[kEventNum] = header->number();

   double w_z0_denom( 0. );
   double w_d0_denom( 0. );

   vector< KTHelix* > helix;
   
   Hep3Vector totalTrackP(0.,0.,0.);
   // track loop
   for ( FATable< NavTrack >::const_iterator track_iter = navtracks.begin();
	 track_iter != tracks_end;
	 track_iter++ ) {
      
      if ( ! track_iter->seedQuality()->originUsed()             &&  // I want real z information!

	   ! track_iter->pionQuality()->fitAbort()               &&  // Don't let the fit fail

	   1./abs(track_iter->pionHelix()->curvature()) > 0.42   &&  // Diameter must be greater than 42 cm
                                                                     // to guarantee that it pokes through
                                                                     // the first stereo superlayer
	   true )
	 helix.push_back( (KTHelix*)( &*track_iter->pionHelix() ) );

      if ( ! track_iter->pionQuality()->fitAbort()  &&
	   ! track_iter->seedQuality()->originUsed()   ) {

	 v[kNumTracks] += 1.;

	 v[kChargedMomX] += track_iter->pionFit()->momentum().x();
	 v[kChargedMomY] += track_iter->pionFit()->momentum().y();
	 v[kChargedMomZ] += track_iter->pionFit()->momentum().z();

	 if ( track_iter->pionHelix()->curvature() > 0. )
	    v[kCharge] += 1.;
	 else
	    v[kCharge] -= 1.;

	 report( DEBUG, kFacilityString )
	    << "hasNullErrorMatrix() = " << track_iter->pionHelix()->hasNullErrorMatrix()
	    << ", errorMatrix()[ kZ0 ][ kZ0 ] = "
	    << track_iter->pionHelix()->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 )
	    << ", z0 = " << track_iter->pionHelix()->z0() << endl;

	 float z0err2( 1. );
	 if ( ! track_iter->pionHelix()->hasNullErrorMatrix()  &&
	      track_iter->pionHelix()->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) > 0. )
	    z0err2 = track_iter->pionHelix()->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 );

	 v[kWeightedZ0] += track_iter->pionHelix()->z0() / z0err2;
	 w_z0_denom += 1. / z0err2;

	 float d0err2( 1. );
	 if ( ! track_iter->pionHelix()->hasNullErrorMatrix()  &&
	      track_iter->pionHelix()->errorMatrix()( KTHelix::kD0, KTHelix::kD0 ) > 0. )
	    d0err2 = track_iter->pionHelix()->errorMatrix()( KTHelix::kD0, KTHelix::kD0 );

	 v[kWeightedD0] += abs( track_iter->pionHelix()->d0() ) / d0err2;
	 w_d0_denom += 1. / d0err2;

	 totalTrackP += track_iter->pionFit()->momentum();
	 if ( track_iter->pionFit()->momentum().mag() > v[kMaxTrackMomentum] )
	    v[kMaxTrackMomentum] = track_iter->pionFit()->momentum().mag();

	 v[kTotalTrackEnergy] += track_iter->pionFit()->energy();
	 if ( track_iter->pionFit()->energy() > v[kMaxTrackEnergy] )
	    v[kMaxTrackEnergy] = track_iter->pionFit()->energy();
      } // end if not fitabort and not z-escape
   } // end loop over tracks

   v[kTotalTrackMomentum] = totalTrackP.mag();
   v[kTotalTrackMomentumTheta] = totalTrackP.theta();
   v[kTotalTrackMomentumPhi] = totalTrackP.phi();

   if ( w_z0_denom != 0. )
      v[kWeightedZ0] /= w_z0_denom;
   
   if ( w_d0_denom != 0. )
      v[kWeightedD0] /= w_d0_denom;
   
   // shower loop
   for ( FATable< NavShower >::const_iterator shower_iter = navshowers.begin();
	 shower_iter != showers_end;
	 shower_iter++ )
      if ( ( shower_iter->attributes().goodBarrel()  ||
	     shower_iter->attributes().goodEndcap()     )  &&
	   ! shower_iter->attributes().hot()                   ) {
	 const double energy = shower_iter->attributes().energy();

	 v[kNumShowers] += 1.;
	 v[kTotalShowerEnergy] += energy;

	 if ( energy > v[kMaxShowerEnergy] ) v[kMaxShowerEnergy] = energy;

	 if ( shower_iter->noTrackMatch() ) {

	    v[kNumUnmatched] += 1.;
	    v[kTotalUnmatchedEnergy] += energy;

	    if ( energy > v[kMaxUnmatchedEnergy] ) v[kMaxUnmatchedEnergy] = energy;

	    v[kNeutralMomX] += shower_iter->attributes().momentum().x();
	    v[kNeutralMomY] += shower_iter->attributes().momentum().y();
	    v[kNeutralMomZ] += shower_iter->attributes().momentum().z();

	 } // end if no track match
      }

   if ( m_getBunchData.value() )
      if ( bunchDecision->numberOfTestedBunches() > 0 ) {
	 v[kBunchWeightBest] = bunchDecision->bestBunchInfo().bweight();
	 v[kBunchWeightNext] = bunchDecision->bunchInfo( 1 ).bweight();
      }

//     if ( navtracks.size() > 2  &&
//  	eventVertex->vertexType() == EventVertex::kGoodEvent ) {
//        v[kVertexX] = eventVertex->vertexPosition().x();
//        v[kVertexY] = eventVertex->vertexPosition().y();
//        v[kVertexZ] = eventVertex->vertexPosition().z();
//        v[kVertexChi2] = eventVertex->vertexChiSquare();
//        v[kVertexChi2perTrack] = ( eventVertex->vertexChiSquare() / 
//  				 eventVertex->numTrackFinalVertex() );
//     }

//     FAItem< MCDecayTree > decayTree;
//     extract( iFrame.record( Stream::kEvent ), decayTree, "Generator" );

   double x(0.), y(0.), sig2x(0.), sig2y(0.);
   if ( helix.size() > 2 ) {
      DABoolean success;
      success = event_vertex( x, y, sig2x, sig2y, helix, report( DEBUG, kFacilityString ) );

//        if ( success  &&
//  	   !( ( x > 0.001  &&  abs(x-0.001)/sqrt(sig2x) > 1. )    ||
//  	      ( x < -0.001  &&  abs(x+0.001)/sqrt(sig2x) > 1. )   ||
//  	      ( y > 0.001  &&  abs(y-0.001)/sqrt(sig2y) > 1. )    ||
//  	      ( y < -0.001  &&  abs(y+0.001)/sqrt(sig2y) > 1. )     ) ) {
//  	 cout << "(* Inside of cut, x = " << x << " +/- " << sqrt(sig2x)
//  	      << " y = " << y << " +/- " << sqrt(sig2y) << " *)" << endl;
//  	 event_vertex( x, y, sig2x, sig2y, helix, cout );  // , &( *decayTree ) );
//        }

//  //        if ( success ) cout << "NTUPLE " << x << " " << sqrt(sig2x) << " " << y << " " << sqrt(sig2y) << endl;

//        if ( ! success ) {
//  //  	 cout << "(* Failed *)" << endl;
//  //  	 event_vertex( x, y, sig2x, sig2y, helix, cout );
//        }
//     }
   }

   v[k2DVertexX] = x;
   v[k2DVertexY] = y;
   v[k2DVertexSigX] = sqrt(sig2x);
   v[k2DVertexSigY] = sqrt(sig2y);

   double xydistance(1000.), zseparation(1000.);
   if ( helix.size() > 2 )
      closest_intersection( xydistance, zseparation, -0.0002, 0.0007, helix );

   v[kXYDistance] = xydistance;
   v[kZSeparation] = zseparation;

   // Only if you make your own copies of the helixes!!!
//     for ( int k = 0;  k < helix.size();  k++ )
//        delete helix[k];

//     if ( m_interestingOnly.value() &&
//  	( abs(v[kWeightedZ0]) < 0.20 || v[kXYDistance] < 0.01 || v[kXYDistance] > 0.03 ) )
//     if ( m_interestingOnly.value() &&
//  	( abs(v[kWeightedZ0]) > 0.10 || v[kXYDistance] > 0.003 ) )
//     if ( m_interestingOnly.value()  &&
//  	props->neutralEnergy() < 0.01 )
//        return ActionBase::kFailed;
//     if ( m_interestingOnly.value()  &&
//  	xydistance > 0.12 )
//        return ActionBase::kFailed;
   if ( m_interestingOnly.value()  &&
 	navtracks.size() == 0 )
      return ActionBase::kFailed;

   v[kEnergyNeutral] = props->neutralEnergy();

   for ( int j = 0;  j < kEntries;  j++ )
      report( INFO, kFacilityString )
	 << ntuple_labels[j] << " = " << v[j] << endl;

   // put the variables into the ntuple
   if ( m_lookForCosmics.value()  &&  isCosmic )
      m_cosmic->fill( v );
   else
      m_other->fill( v );

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
BigNTuple2::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
BigNTuple2::endRun( Frame& iFrame )         // anal4 equiv.
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

const int kRa = 0;
const int kXa = 1;
const int kYa = 2;
const int kRb = 3;
const int kXb = 4;
const int kYb = 5;
const int kNumCirc = 6;

const int kCurva = 0;
const int kD0a = 1;
const int kPhi0a = 2;
const int kCurvb = 3;
const int kD0b = 4;
const int kPhi0b = 5;
const int kNumTrack = 6;

void BigNTuple2::closest_intersection(
   double& xydistance, double& zseparation, double x0, double y0, vector< KTHelix* >& helix )
{
   double tailcut( m_tailCut.value() );

   vector< double > xydist;
   vector< double > zsep;

   // This is a loop over the upper triangle of the helix-helix
   // matrix.
   int hi, hj;
   int nhelix( helix.size() );
   for ( hi = 0;  hi < nhelix;  hi++ ) {
      // loop over remaining, unvisited helixes
      for ( hj = hi + 1;  hj < nhelix;  hj++ ) {
	 double tx(0.), ty(0.), dummysig2x(0.), dummysig2y(0.), dummysig2xy(0.);
	 
	 // We don't want to deal with intersections that failed.
	 if ( calc_intersection( tx, ty, dummysig2x, dummysig2y, dummysig2xy,
				 *helix[hi], *helix[hj], true ) ) {

	    // This calculation of arclength comes from KTHelix.h
	    // (and agrees with my tests, except where I get
	    // confused by looping around the circle the wrong
	    // way).
	    double sinphi01( sin(helix[hi]->phi0()) );
	    double cosphi01( cos(helix[hi]->phi0()) );
	    double sinphi1( 2.*helix[hi]->curvature()*(tx*cosphi01 + ty*sinphi01) );
	    double cosphi1( 2.*helix[hi]->curvature()*(tx*sinphi01 - ty*cosphi01
						       + helix[hi]->d0()) + 1. );
	    double arclength1( atan2(sinphi1, cosphi1) / 2. / helix[hi]->curvature() );

	    double sinphi02( sin(helix[hj]->phi0()) );
	    double cosphi02( cos(helix[hj]->phi0()) );
	    double sinphi2( 2.*helix[hj]->curvature()*(tx*cosphi02 + ty*sinphi02) );
	    double cosphi2( 2.*helix[hj]->curvature()*(tx*sinphi02 - ty*cosphi02
						       + helix[hj]->d0()) + 1. );
	    double arclength2( atan2(sinphi2, cosphi2) / 2. / helix[hj]->curvature() );

	    // We don't even want to deal with intersections that
	    // use the wrong end of a circle (accept arclengths in
	    // the range from -tailcut to to halfway around the
	    // circle).
	    if ( arclength1 > -tailcut  &&  arclength1 < M_PI/2./abs(helix[hi]->curvature())  &&
		 arclength2 > -tailcut  &&  arclength2 < M_PI/2./abs(helix[hj]->curvature())     ) {

	       double z1( helix[hi]->cotTheta() * arclength1 + helix[hi]->z0() );
	       double z2( helix[hj]->cotTheta() * arclength2 + helix[hj]->z0() );

	       xydist.push_back( sqrt(sqr(tx) + sqr(ty)) );
	       zsep.push_back( z2 - z1 );
	    } // end if this intersection is on the right side of the helix
	 } // end if intersection was properly calculated
      } // end loop over tracks j
   } // end loop over tracks i
   
   double bestxy(1000.);
   double bestz(1000.);
   int i;
   int nint( xydist.size() );
   for ( i = 0;  i < nint;  i++ )
      if ( xydist[i] < bestxy ) {
	 bestxy = xydist[i];
	 bestz = zsep[i];
      }
   xydistance = bestxy;
   zseparation = bestz;
}

// A return value of true means that you have a good vertex. If false,
// don't trust x, y, sig2x or sig2y!
DABoolean BigNTuple2::event_vertex(
   double& x, double& y, double& sig2x, double& sig2y, vector< KTHelix* >& original,
   ostream& os, MCDecayTree* decayTree )
{
   const int nhelixescut = 3;
   double rmscut( m_rmsCut.value() );
   double tailcut( m_tailCut.value() );

   vector< KTHelix* > helix;
   int hindex;
   for ( hindex = 0;  hindex < original.size();  hindex++ )
      helix.push_back( original[hindex] );

   os << endl << "Show[ Graphics[{}]" << endl;
   for ( hindex = 0;  hindex < helix.size();  hindex++ ) {
      double r0( 1./2./helix[hindex]->curvature() );
      // The center of the circle
      double x0( -(helix[hindex]->d0() + r0) * sin(helix[hindex]->phi0()) );
      double y0( (helix[hindex]->d0() + r0) * cos(helix[hindex]->phi0()) );
      // The point on the circle which is closest to the origin
      double xs( helix[hindex]->d0()/(r0+helix[hindex]->d0()) * x0 );
      double ys( helix[hindex]->d0()/(r0+helix[hindex]->d0()) * y0 );

      double phis( atan2((ys - y0), (xs - x0)) );

      // This is a direction factor--- it will be +1 if the particle
      // travels in the direction of positive radians, -1 if the
      // particle goes the other way.
      double dir( -sin( phis - helix[hindex]->phi0() ) );
      
      os
	 << "    , ParametricPlot[ {" << x0 << " + " << abs(r0) << "*Cos[t], "
	 << y0 << " + " << abs(r0) << "*Sin[t]}" << endl
	 << "		    , {t," << phis - dir*tailcut/abs(r0) << "," << phis + dir*M_PI << "}" << endl
	 << "               , PlotPoints -> 10000" << endl
	 << "               , DisplayFunction -> Identity" << endl
	 << "             ]" << endl;
   }

   // This loop will throw away at most one helix. I want don't want
   // to throw any away if I am left with only three helixes--- this
   // is the minimum for a good vertex.
   //
   // If we enter this point with only two helixes (because the event
   // had only two tracks), we skip this loop entirely. It's the best
   // we can do.
   //
   // const int nhelixescut = 3;
   while ( helix.size() >= nhelixescut ) {
      // trial x and y intersections
      vector< double > trialx;
      vector< double > trialy;
      vector< int > hindex1;
      vector< int > hindex2;

      // This is a loop over the upper triangle of the helix-helix
      // matrix.
      int hi, hj;
      int nhelix( helix.size() );
      for ( hi = 0;  hi < nhelix;  hi++ ) {
	 // loop over remaining, unvisited helixes
	 for ( hj = hi + 1;  hj < nhelix;  hj++ ) {
	    double tx(0.), ty(0.), dummysig2x(0.), dummysig2y(0.), dummysig2xy(0.);

	    // We don't want to deal with intersections that failed.
	    if ( calc_intersection( tx, ty, dummysig2x, dummysig2y, dummysig2xy,
				    *helix[hi], *helix[hj], true ) ) {

	       // This calculation of arclength comes from KTHelix.h
	       // (and agrees with my tests, except where I get
	       // confused by looping around the circle the wrong
	       // way).
	       double sinphi01( sin(helix[hi]->phi0()) );
	       double cosphi01( cos(helix[hi]->phi0()) );
	       double sinphi1( 2.*helix[hi]->curvature()*(tx*cosphi01 + ty*sinphi01) );
	       double cosphi1( 2.*helix[hi]->curvature()*(tx*sinphi01 - ty*cosphi01
							  + helix[hi]->d0()) + 1. );
	       double arclength1( atan2(sinphi1, cosphi1) / 2. / helix[hi]->curvature() );

	       double sinphi02( sin(helix[hj]->phi0()) );
	       double cosphi02( cos(helix[hj]->phi0()) );
	       double sinphi2( 2.*helix[hj]->curvature()*(tx*cosphi02 + ty*sinphi02) );
	       double cosphi2( 2.*helix[hj]->curvature()*(tx*sinphi02 - ty*cosphi02
							 + helix[hj]->d0()) + 1. );
	       double arclength2( atan2(sinphi2, cosphi2) / 2. / helix[hj]->curvature() );



//  	       if ( helix.size() == original.size() ) {

//  		  double r01( 1./2./helix[hi]->curvature() );
//  		  // The center of the circle
//  		  double x01( -(helix[hi]->d0() + r01) * sin(helix[hi]->phi0()) );
//  		  double y01( (helix[hi]->d0() + r01) * cos(helix[hi]->phi0()) );
//  		  // The point on the circle which is closest to the origin
//  		  double xs1( helix[hi]->d0()/(r01+helix[hi]->d0()) * x01 );
//  		  double ys1( helix[hi]->d0()/(r01+helix[hi]->d0()) * y01 );
//  		  double phis1( atan2((ys1 - y01), (xs1 - x01)) );

//  		  double r02( 1./2./helix[hj]->curvature() );
//  		  // The center of the circle
//  		  double x02( -(helix[hj]->d0() + r02) * sin(helix[hj]->phi0()) );
//  		  double y02( (helix[hj]->d0() + r02) * cos(helix[hj]->phi0()) );
//  		  // The point on the circle whjch is closest to the origin
//  		  double xs2( helix[hj]->d0()/(r02+helix[hj]->d0()) * x02 );
//  		  double ys2( helix[hj]->d0()/(r02+helix[hj]->d0()) * y02 );
//  		  double phis2( atan2((ys2 - y02), (xs2 - x02)) );

//  		  double halfaround1( (M_PI + phis1)*abs(r01) );
//  		  double halfaround2( (M_PI + phis2)*abs(r02) );

//  		  double z1_h( helix[hi]->cotTheta() * halfaround1 + helix[hi]->z0() );
//  		  double z2_h( helix[hj]->cotTheta() * halfaround2 + helix[hj]->z0() );

//  		  double z1err2_h( helix[hi]->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 )
//  				   + sqr(halfaround1) * helix[hi]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kCotTheta )
//  				   + 2. * halfaround1 * helix[hi]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kZ0 ) );
//  		  double z2err2_h( helix[hj]->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 )
//  				   + sqr(halfaround2) * helix[hj]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kCotTheta )
//  				   + 2. * halfaround2 * helix[hj]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kZ0 ) );

//  		  cout << "NTUPLE " << (z1_h - z2_h) << " "
//  		       << helix[hi]->cotTheta() << " " << helix[hj]->cotTheta() << " "
//  		       << r01 << " " << r02 << " " << (x01 - x02) << " " << (y01 - y02) << endl;
//  //  		  cout << "NTUPLE " << (z1_h - z2_h)/sqrt(z1err2_h + z2err2_h) << " "
//  //  		       << helix[hi]->cotTheta() << " " << helix[hj]->cotTheta() << " "
//  //  		       << r01 << " " << r02 << " " << (x01 - x02) << " " << (y01 - y02) << endl;

//  	       }




	       // We don't even want to deal with intersections that
	       // use the wrong end of a circle (accept arclengths in
	       // the range from -tailcut to to halfway around the
	       // circle).
	       if ( arclength1 > -tailcut  &&  arclength1 < M_PI/2./abs(helix[hi]->curvature())  &&
		    arclength2 > -tailcut  &&  arclength2 < M_PI/2./abs(helix[hj]->curvature())     ) {

		  double z1( helix[hi]->cotTheta() * arclength1 + helix[hi]->z0() );
		  double z2( helix[hj]->cotTheta() * arclength2 + helix[hj]->z0() );

		  double z1err2( helix[hi]->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 )
				 + sqr(arclength1) * helix[hi]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kCotTheta )
				 + 2. * arclength1 * helix[hi]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kZ0 ) );
		  double z2err2( helix[hj]->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 )
				 + sqr(arclength2) * helix[hj]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kCotTheta )
				 + 2. * arclength2 * helix[hj]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kZ0 ) );

		  // We don't even want to deal with intersections that
		  // disagree in z by more than 3 sigma.
		  if ( abs(z1 - z2) / sqrt(z1err2 + z2err2) < 3. ) {

		     trialx.push_back( tx );
		     trialy.push_back( ty );
		     hindex1.push_back( hi );
		     hindex2.push_back( hj );

		     if ( helix.size() == original.size() )
			os << "    , Graphics[{Point[{" << tx << "," << ty << "}]}]" << endl;
		  } // end if good z separation
	       } // end if on the right (forward-going) part of the track
	    } // end if able to find an intersection

	 } // end loop over helix index j
      } // end loop over helix index i

      // number of intersections
      int nint( trialx.size() );
      if ( nint == 0 ) {
	 os << "    , AspectRatio -> 1" << endl
	    << "    , PlotRange -> {{-0.01, 0.01}, {-0.01, 0.01}} * 10" << endl
	    << "    , DisplayFunction -> $DisplayFunction" << endl
	    << "    ];" << endl << endl;
	 return false;
      }
      int i;

      // calculate the average (x, y) of the intersections
      double averagex(0.), averagey(0.);
      for ( i = 0;  i < nint;  i++ ) {
	 averagex += trialx[i];
	 averagey += trialy[i];
      }
      averagex /= double(nint);
      averagey /= double(nint);

      // calculate the rms distance from this average (x, y)
      double rms(0.);
      for ( i = 0;  i < nint;  i++ )
	 rms += sqr(trialx[i] - averagex) + sqr(trialy[i] - averagey);
      rms /= double(nint);
      rms = sqrt( rms );

      // If the rms is already below 1 mm, let's keep this set. It's
      // more valuable to have a lot of tracks to find a good vertex.
      //
      // const double rmscut = 0.001;
      if ( rms < rmscut ) break;

      // Now that we know the average and rms for all these trial
      // intersections, find the average and rms with one helix
      // missing, for each helix. The helix which, when missing,
      // reduces the rms the most is the first helix to remove.
      int besttoremove(-1);
      double bestsemirms(rms);
      DABoolean anyzero(false);
      for ( hi = 0;  hi < nhelix;  hi++ ) {
	 double semiavx(0.), semiavy(0.);
	 int n(0);
	 for ( i = 0;  i < nint;  i++ )
	    if ( hindex1[i] != hi  &&  hindex2[i] != hi ) {
	       semiavx = trialx[i];
	       semiavy = trialy[i];
	       n++;
	    }
	 // If removing a helix leaves us with no intersections, this
	 // helix must not be dropped!
	 if ( n == 0 ) {
	    // There is no way this can be chosen `besttoremove'.
	    continue;
	 }
	 semiavx /= double(n);
	 semiavy /= double(n);

	 double semirms(0.);
	 for ( i = 0;  i < nint;  i++ )
	    if ( hindex1[i] != hi  &&  hindex2[i] != hi )
	       semirms += sqr(trialx[i] - semiavx) + sqr(trialy[i] - semiavy);
	 semirms /= double(n);
	 semirms = sqrt( semirms );

	 if ( semirms == 0. ) anyzero = true;

	 if ( semirms < bestsemirms ) {
	    bestsemirms = semirms;
	    besttoremove = hi;
	 }
      } // end loop over helix indexes

      // If removing any helix just increases the rms, this is the
      // ideal set of helixes.
      if ( besttoremove == -1 ) break;

      // I don't want to remove so many helices that I am left with
      // only one intersection.
      if ( anyzero ) break;
      
      // Otherwise, do the whole thing again with one fewer helixes.
      vector< KTHelix* > tmp_copy;
      for ( hi = 0;  hi < nhelix;  hi++ )
	 tmp_copy.push_back( helix[hi] );
      helix.erase();
      for ( hi = 0;  hi < tmp_copy.size();  hi++ )
	 if ( hi != besttoremove )
	    helix.push_back( tmp_copy[hi] );

   } // end while you're still removing helixes

   os << "    , Graphics[{Line[0.001*{{1,1},{-1,1},{-1,-1},{1,-1},{1,1}}]}]" << endl;

   for ( hindex = 0;  hindex < helix.size();  hindex++ ) {
      double r0( 1./2./helix[hindex]->curvature() );
      // The center of the circle
      double x0( -(helix[hindex]->d0() + r0) * sin(helix[hindex]->phi0()) );
      double y0( (helix[hindex]->d0() + r0) * cos(helix[hindex]->phi0()) );
      // The point on the circle which is closest to the origin
      double xs( helix[hindex]->d0()/(r0+helix[hindex]->d0()) * x0 );
      double ys( helix[hindex]->d0()/(r0+helix[hindex]->d0()) * y0 );

      double phis( atan2((ys - y0), (xs - x0)) );

      // This is a direction factor--- it will be +1 if the particle
      // travels in the direction of positive radians, -1 if the
      // particle goes the other way.
      double dir( -sin( phis - helix[hindex]->phi0() ) );
  
      os
	 << "    , ParametricPlot[ {" << x0 << " + " << abs(r0) << "*Cos[t], "
	 << y0 << " + " << abs(r0) << "*Sin[t]}" << endl
	 << "		    , {t," << phis - dir*tailcut/abs(r0) << "," << phis + dir*M_PI << "}" << endl
	 << "               , PlotStyle -> {RGBColor[0,0,1]}" << endl
	 << "               , PlotPoints -> 10000" << endl
	 << "               , DisplayFunction -> Identity" << endl
	 << "             ]" << endl;
   }

   // Now we have an ideal set of helixes. Let's recalculate the
   // intersections, but this time with uncertainties.
   //
   // From this, I calculate a weighted mean x and a weighted mean y.
   double numerx(0.), denomx(0.), numery(0.), denomy(0.);

   int hi, hj;
   int nhelix( helix.size() );
   for ( hi = 0;  hi < nhelix;  hi++ ) {
      // loop over remaining, unvisited helixes
      for ( hj = hi + 1;  hj < nhelix;  hj++ ) {
	 double tx(0.), ty(0.), tsig2x(0.), tsig2y(0.), tsig2xy(0.);

	    // We don't want to deal with intersections that failed.
	    if ( calc_intersection( tx, ty, tsig2x, tsig2y, tsig2xy,
				    *helix[hi], *helix[hj], false ) ) {

	       // This calculation of arclength comes from KTHelix.h
	       // (and agrees with my tests, except where I get
	       // confused by looping around the circle the wrong
	       // way).
	       double sinphi01( sin(helix[hi]->phi0()) );
	       double cosphi01( cos(helix[hi]->phi0()) );
	       double sinphi1( 2.*helix[hi]->curvature()*(tx*cosphi01 + ty*sinphi01) );
	       double cosphi1( 2.*helix[hi]->curvature()*(tx*sinphi01 - ty*cosphi01
							 + helix[hi]->d0()) + 1. );
	       double arclength1( atan2(sinphi1, cosphi1) / 2. / helix[hi]->curvature() );

	       double sinphi02( sin(helix[hj]->phi0()) );
	       double cosphi02( cos(helix[hj]->phi0()) );
	       double sinphi2( 2.*helix[hj]->curvature()*(tx*cosphi02 + ty*sinphi02) );
	       double cosphi2( 2.*helix[hj]->curvature()*(tx*sinphi02 - ty*cosphi02
							 + helix[hj]->d0()) + 1. );
	       double arclength2( atan2(sinphi2, cosphi2) / 2. / helix[hj]->curvature() );

	       // We don't even want to deal with intersections that
	       // use the wrong end of a circle (accept arclengths in
	       // the range from -tailcut to to halfway around the
	       // circle).
	       if ( arclength1 > -tailcut  &&  arclength1 < M_PI/2./abs(helix[hi]->curvature())  &&
		    arclength2 > -tailcut  &&  arclength2 < M_PI/2./abs(helix[hj]->curvature())     ) {

		  double z1( helix[hi]->cotTheta() * arclength1 + helix[hi]->z0() );
		  double z2( helix[hj]->cotTheta() * arclength2 + helix[hj]->z0() );

		  double z1err2( helix[hi]->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 )
				 + sqr(arclength1) * helix[hi]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kCotTheta )
				 + 2. * arclength1 * helix[hi]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kZ0 ) );
		  double z2err2( helix[hj]->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 )
				 + sqr(arclength2) * helix[hj]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kCotTheta )
				 + 2. * arclength2 * helix[hj]->errorMatrix()( KTHelix::kCotTheta, KTHelix::kZ0 ) );

		  // We don't even want to deal with intersections that
		  // disagree in z by more than 3 sigma.
		  if ( abs(z1 - z2) / sqrt(z1err2 + z2err2) < 3. ) {

		     numerx += tx / tsig2x;
		     denomx += 1. / tsig2x;

		     numery += ty / tsig2y;
		     denomy += 1. / tsig2y;

		     os << "    , Graphics[{RGBColor[0,0,1],Point[{" << tx << "," << ty << "}]}]" << endl;
		  } // end if good z separation
	       } // end if on the right (forward-going) part of the track
	    } // end if able to find an intersection

      } // end loop over helix index j
   } // end loop over helix index i

   // It is possible that requiring the uncertainty calculations to
   // not fail leaves us with no more intersections. This is a wierd
   // case, so I'm going to protect the job but not worry about
   // handling it correctly.
   if ( denomx == 0.  ||  denomy == 0. ) {
      os << "    , AspectRatio -> 1" << endl
	 << "    , PlotRange -> {{-0.01, 0.01}, {-0.01, 0.01}} * 10" << endl
	 << "    , DisplayFunction -> $DisplayFunction" << endl
	 << "    ];" << endl << endl;
      return false;
   }

   x = numerx / denomx;
   sig2x = 1. / denomx;
   y = numery / denomy;
   sig2y = 1. / denomy;

   os << "    , Graphics[{RGBColor[1,0,0], Point[{" << x << ", " << y << "}]" << endl
      << "		, Line[{{" << x-sqrt(sig2x) << ", " << y << "}, {"
      << x+sqrt(sig2x) << ", " << y << "}}]" << endl
      << "            , Line[{{" << x << ", " << y-sqrt(sig2y) << "}, {"
      << x << ", " << y+sqrt(sig2y) << "}}]}]" << endl;

//     if ( decayTree != NULL )
//        for ( MCDecayTree::const_vIterator vertex_iter = decayTree->vBegin();
//  	    vertex_iter != decayTree->vEnd();
//  	    vertex_iter++ )
//  	 os << "    , Graphics[{RGBColor[0,1,0], Point[{" << vertex_iter->position().x()
//  	    << ", " << vertex_iter->position().y() << "}]" << endl;

   os << "    , AspectRatio -> 1" << endl
      << "    , PlotRange -> {{-0.01, 0.01}, {-0.01, 0.01}} * 10" << endl
      << "    , DisplayFunction -> $DisplayFunction" << endl
      << "    ];" << endl << endl;
   
   return true;
}

DABoolean BigNTuple2::calc_intersection(
   double& x, double& y, double& sig2x, double& sig2y, double& sig2xy,
   KTHelix& a, KTHelix& b, DABoolean no_uncertainties )
{
   // see intersections4.m and my "Resonance Studies" notebook for a derivation

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

   // Take the x-y solution closest to the origin
   int which_num;
   char which_let;
   if ( sqr(xsol1) + sqr(ysol1) < sqr(xsol2) + sqr(ysol2) ) {
      x = xsol1;
      y = ysol1;
      which_num = 1;
      if ( abs( ysol1 - ysol1a ) < abs( ysol1 - ysol1b ) )
	 which_let = 'a';
      else
	 which_let = 'b';
   }
   else {
      x = xsol2;
      y = ysol2;
      which_num = 2;
      if ( abs( ysol2 - ysol2a ) < abs( ysol2 - ysol2b ) )
	 which_let = 'a';
      else
	 which_let = 'b';
   }

   if ( no_uncertainties ) return true;

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

   calc_errors( x, y, dx_dcirc, dy_dcirc, a, b, sig2x, sig2y, sig2xy );
   return true;
}

DABoolean BigNTuple2::calc_closest(
   double& x, double& y, double& sig2x, double& sig2y, double& sig2xy,
   KTHelix& a, KTHelix& b, DABoolean no_uncertainties )
{
   double ra( 1./2./a.curvature() );
   double xa( -(a.d0() + ra) * sin(a.phi0()) );
   double ya( (a.d0() + ra) * cos(a.phi0()) );

   double rb( 1./2./b.curvature() );
   double xb( -(b.d0() + rb) * sin(b.phi0()) );
   double yb( (b.d0() + rb) * cos(b.phi0()) );

   if ( xa == xb  &&  ya == yb ) return false;

   // The point on circle a and on circle b closest to the other circle
   double ax(0.), ay(0.);
   double bx(0.), by(0.);

   double dax_dcirc[kNumCirc];
   double day_dcirc[kNumCirc];
   double dbx_dcirc[kNumCirc];
   double dby_dcirc[kNumCirc];

   int i;
   for ( i = 0;  i < kNumCirc;  i++ ) {
      dax_dcirc[i] = 0.;
      day_dcirc[i] = 0.;
      dbx_dcirc[i] = 0.;
      dby_dcirc[i] = 0.;
   }

   // Special case for two circles directly above one another.
   if ( xa == xb ) {
      ax = bx = xa;

      double ay1( ya + ra );
      double ay2( ya - ra );
      int awhich(0);
      if ( sqr(ax - xb) + sqr(ay1 - yb) < sqr(ax - xb) + sqr(ay2 - yb) ) {
	 ay = ay1;
	 awhich = 1;
      }
      else {
	 ay = ay2;
	 awhich = 2;
      }

      double by1( yb + rb );
      double by2( yb - rb );
      int bwhich(0);
      if ( sqr(bx - xa) + sqr(by1 - ya) < sqr(bx - xa) + sqr(by2 - ya) ) {
	 by = by1;
	 bwhich = 1;
      }
      else {
	 by = by2;
	 bwhich = 2;
      }

      if ( no_uncertainties ) return true;

      dax_dcirc[kXa] = 1.;
      dax_dcirc[kXb] = 1.;
      dbx_dcirc[kXa] = 1.;
      dbx_dcirc[kXb] = 1.;

      day_dcirc[kRa] = ( awhich == 1 ? 1. : -1. );
      day_dcirc[kYa] = 1.;
      dby_dcirc[kRb] = ( bwhich == 1 ? 1. : -1. );
      dby_dcirc[kYb] = 1.;
   }
   // Typical case of two general circles.
   else {
      double denomdisc( 1 + sqr( (yb - ya)/(xb - xa) ) );
      
      double ax1( xa + ra / sqrt(denomdisc) );
      double ax2( xa - ra / sqrt(denomdisc) );
      double bx1( xb + rb / sqrt(denomdisc) );
      double bx2( xb - rb / sqrt(denomdisc) );

      double ay1( ya + (yb - ya)/(xb - xa) * (ax1 - xa) );
      double ay2( ya + (yb - ya)/(xb - xa) * (ax2 - xa) );
      double by1( yb + (yb - ya)/(xb - xa) * (bx1 - xb) );
      double by2( yb + (yb - ya)/(xb - xa) * (bx2 - xb) );

      int awhich(0);
      if ( abs( sqr(ax1 - xb) + sqr(ay1 - yb) - sqr(rb) ) <
	   abs( sqr(ax2 - xb) + sqr(ay2 - yb) - sqr(rb) ) ) {
	 ax = ax1;
	 ay = ay1;
	 awhich = 1;
      }
      else {
	 ax = ax2;
	 ay = ay2;
	 awhich = 2;
      }

      int bwhich(0);
      if ( abs( sqr(bx1 - xa) + sqr(by1 - ya) - sqr(ra) ) <
	   abs( sqr(bx2 - xa) + sqr(by2 - ya) - sqr(ra) ) ) {
	 bx = bx1;
	 by = by1;
	 bwhich = 1;
      }
      else {
	 bx = bx2;
	 by = by2;
	 bwhich = 2;
      }

      if ( no_uncertainties ) return true;

      double ddd_dxa( 2. * sqr(yb - ya) / pow(xb - xa, 3) );
      double ddd_dxb( -2. * sqr(yb - ya) / pow(xb - xa, 3) );
      double ddd_dya( -2. * (yb - ya) / sqr(xb - xa) );
      double ddd_dyb( 2. * (yb - ya) / sqr(xb - xa) );

      double asign( awhich == 1 ? 1. : -1. );
      dax_dcirc[kRa] = asign / sqrt(denomdisc);
      dax_dcirc[kXa] = 1. - asign * ra / 2. / pow(denomdisc, 3./2.) * ddd_dxa;
      dax_dcirc[kYa] = -asign * ra / 2. / pow(denomdisc, 3./2.) * ddd_dya;
      dax_dcirc[kRb] = 0.;
      dax_dcirc[kXb] = -asign * ra / 2. / pow(denomdisc, 3./2.) * ddd_dxb;
      dax_dcirc[kYb] = -asign * ra / 2. / pow(denomdisc, 3./2.) * ddd_dyb;

      double bsign( bwhich == 1 ? 1. : -1. );
      dbx_dcirc[kRa] = 0.;
      dbx_dcirc[kXa] = -bsign * rb / 2. / pow(denomdisc, 3./2.) * ddd_dxa;
      dbx_dcirc[kYa] = -bsign * rb / 2. / pow(denomdisc, 3./2.) * ddd_dya;
      dbx_dcirc[kRb] = bsign / sqrt(denomdisc);
      dbx_dcirc[kXb] = 1. - bsign * rb / 2. / pow(denomdisc, 3./2.) * ddd_dxb;
      dbx_dcirc[kYb] = -bsign * rb / 2. / pow(denomdisc, 3./2.) * ddd_dyb;

      double slope( (yb - ya)/(xb - xa) );
      double dslope_dxa( (yb - ya)/sqr(xb - xa) );
      double dslope_dya( -1./(xb - xa) );
      double dslope_dxb( -(yb - ya)/sqr(xb - xa) );
      double dslope_dyb( 1./(xb - xa) );

      day_dcirc[kRa] = slope * dax_dcirc[kRa];
      day_dcirc[kXa] = slope * (dax_dcirc[kXa] - 1.) + dslope_dxa * (ax - xa);
      day_dcirc[kYa] = 1. + slope * dax_dcirc[kYa] + dslope_dya * (ax - xa);
      day_dcirc[kRb] = slope * dax_dcirc[kRb];
      day_dcirc[kXb] = slope * dax_dcirc[kXb] + dslope_dxb * (ax - xa);
      day_dcirc[kYb] = slope * dax_dcirc[kYb] + dslope_dyb * (ax - xa);

      dby_dcirc[kRa] = slope * dbx_dcirc[kRa];
      dby_dcirc[kXa] = slope * dbx_dcirc[kXa] + dslope_dxa * (bx - xb);
      dby_dcirc[kYa] = slope * dbx_dcirc[kYa] + dslope_dya * (bx - xb);
      dby_dcirc[kRb] = slope * dbx_dcirc[kRb];
      dby_dcirc[kXb] = slope * (dbx_dcirc[kXb] - 1.) + dslope_dxb * (bx - xb);
      dby_dcirc[kYb] = 1. + slope * dbx_dcirc[kYb] + dslope_dyb * (bx - xb);
   } // end if xa =?= xb

   double sig2ax(0.), sig2ay(0.), sig2axay(0.), sig2bx(0.), sig2by(0.), sig2bxby(0.);
   calc_errors( ax, ay, dax_dcirc, day_dcirc, a, b, sig2ax, sig2ay, sig2axay );
   calc_errors( bx, by, dbx_dcirc, dby_dcirc, a, b, sig2bx, sig2by, sig2bxby );

   double chi2sep(0.);
   if ( ax == bx  &&  ay == by ) {
      // if they are in the same spot, chi2sep == 0
      x = ax;
      y = ay;
   }
   else {
      double axprime( ( ax*(bx - ax) + ay*(by - ay) )
		      / sqrt( sqr(bx - ax) + sqr(by - ay) ) );
      double bxprime( ( bx*(bx - ax) + by*(by - ay) )
		      / sqrt( sqr(bx - ax) + sqr(by - ay) ) );

      double daxprime_dax( ((ax - bx)*(sqr(ax) - ax*bx + ay*(ay - by)) + 
			    (-2*ax + bx)*(sqr(ax - bx) + sqr(ay - by)))/
			   pow(sqr(ax - bx) + sqr(ay - by),1.5) );
      double daxprime_day( ((sqr(ax) - ax*bx + ay*(ay - by))*(ay - by) + 
			    (sqr(ax - bx) + sqr(ay - by))*(-2*ay + by))/
			   pow(sqr(ax - bx) + sqr(ay - by),1.5) );
      double dbxprime_dbx( (-pow(ax,3) + 3*sqr(ax)*bx - 
			    ax*(sqr(ay) + 3*sqr(bx) - ay*by) + 
			    bx*(2*sqr(ay) + sqr(bx) - 3*ay*by + sqr(by)))/
			   pow(sqr(ax - bx) + sqr(ay - by),1.5) );
      double dbxprime_dby( (-pow(ay,3) + ax*bx*(ay - 3*by) - sqr(ax)*(ay - 2*by) + 
			    3*sqr(ay)*by + sqr(bx)*by - 3*ay*sqr(by) + pow(by,3))/
			   pow(sqr(ax - bx) + sqr(ay - by),1.5) );

      double sig2axprime( sig2ax*sqr(daxprime_dax) + sig2ay*sqr(daxprime_day)
			  + 2*sig2axay*daxprime_dax*daxprime_day );
      double sig2bxprime( sig2bx*sqr(dbxprime_dbx) + sig2by*sqr(dbxprime_dby)
			  + 2*sig2bxby*dbxprime_dbx*dbxprime_dby );

      if ( sig2axprime == 0.  &&  sig2bxprime == 0. ) {
	 chi2sep = HUGE_VAL;
	 x = (bx + ax) / 2.;
	 y = (by + ay) / 2.;
      }
      else { 
	 chi2sep = sqr(bxprime - axprime) / ( sig2axprime + sig2bxprime );
	 double sig2xprime( 1./(1./sig2axprime + 1./sig2bxprime) );
	 double xprime( (axprime/sig2axprime + bxprime/sig2bxprime) * sig2xprime );

	 x = xprime * (bx - ax) / sqrt(sqr(bx - ax) + sqr(by - ay));
	 y = xprime * (by - ay) / sqrt(sqr(bx - ax) + sqr(by - ay));
      } // end if errors are zero

   } // end if same place

   if ( sig2ax == 0.  &&  sig2ay == 0. ) {
      sig2x = 0.;
      sig2y = 0.;
      sig2xy = 0.;
   }
   else {
      double axay_cor( sig2axay / sqrt(sig2ax) / sqrt(sig2ay) );
      double bxby_cor( sig2bxby / sqrt(sig2bx) / sqrt(sig2by) );
      if ( chi2sep > 20. ) {
	 sig2x = 0.;
	 sig2y = 0.;
	 sig2xy = 0.;
      }
      else {
	 sig2x = 1. / sqr(erfc(abs(chi2sep)*M_SQRT1_2)) / (1./sig2ax + 1./sig2bx);
	 sig2y = 1. / sqr(erfc(abs(chi2sep)*M_SQRT1_2)) / (1./sig2ay + 1./sig2by);
	 sig2xy = (axay_cor + bxby_cor) / 2. * sqrt(sig2x) * sqrt(sig2y);
      } // end if very separated
   }

   return true;
}

void BigNTuple2::calc_errors(
   double x, double y, double* dx_dcirc, double* dy_dcirc,
   KTHelix& a, KTHelix& b, double& sig2x, double& sig2y, double& sig2xy )
{
   double ra( 1./2./a.curvature() );
   double xa( -(a.d0() + ra) * sin(a.phi0()) );
   double ya( (a.d0() + ra) * cos(a.phi0()) );

   double rb( 1./2./b.curvature() );
   double xb( -(b.d0() + rb) * sin(b.phi0()) );
   double yb( (b.d0() + rb) * cos(b.phi0()) );

   // This is a Jacobian for transforming between circle variables and
   // tracking variables
   double dcirc_dtrack[kNumCirc][kNumTrack];
   int i, j;
   for ( i = 0;  i < kNumCirc;  i++ )
      for ( j = 0;  j < kNumTrack;  j++ )
	 dcirc_dtrack[i][j] = 0;
   
   dcirc_dtrack[kRa][kCurva] = -1. / 2. / sqr( a.curvature() );

   dcirc_dtrack[kXa][kCurva] = -dcirc_dtrack[kRa][kCurva] * sin( a.phi0() );
   dcirc_dtrack[kXa][kD0a] = -sin( a.phi0() );
   dcirc_dtrack[kXa][kPhi0a] = -(ra + a.d0()) * cos( a.phi0() );

   dcirc_dtrack[kYa][kCurva] = dcirc_dtrack[kRa][kCurva] * cos( a.phi0() );
   dcirc_dtrack[kYa][kD0a] = cos( a.phi0() );
   dcirc_dtrack[kYa][kPhi0a] = -(ra + a.d0()) * sin( a.phi0() );

   dcirc_dtrack[kRb][kCurvb] = -1. / 2. / sqr( b.curvature() );

   dcirc_dtrack[kXb][kCurvb] = -dcirc_dtrack[kRb][kCurvb] * sin( b.phi0() );
   dcirc_dtrack[kXb][kD0b] = -sin( b.phi0() );
   dcirc_dtrack[kXb][kPhi0b] = -(rb + b.d0()) * cos( b.phi0() );

   dcirc_dtrack[kYb][kCurvb] = dcirc_dtrack[kRb][kCurvb] * cos( b.phi0() );
   dcirc_dtrack[kYb][kD0b] = cos( b.phi0() );
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
   sigma[kCurva][kD0a] = a.errorMatrix()(KTHelix::kCurvature, KTHelix::kD0);
   sigma[kCurva][kPhi0a] = a.errorMatrix()(KTHelix::kCurvature, KTHelix::kPhi0);
   sigma[kD0a][kCurva] = a.errorMatrix()(KTHelix::kD0, KTHelix::kCurvature);
   sigma[kD0a][kD0a] = a.errorMatrix()(KTHelix::kD0, KTHelix::kD0);
   sigma[kD0a][kPhi0a] = a.errorMatrix()(KTHelix::kD0, KTHelix::kPhi0);
   sigma[kPhi0a][kCurva] = a.errorMatrix()(KTHelix::kPhi0, KTHelix::kCurvature);
   sigma[kPhi0a][kD0a] = a.errorMatrix()(KTHelix::kPhi0, KTHelix::kD0);
   sigma[kPhi0a][kPhi0a] = a.errorMatrix()(KTHelix::kPhi0, KTHelix::kPhi0);

   sigma[kCurvb][kCurvb] = b.errorMatrix()(KTHelix::kCurvature, KTHelix::kCurvature);
   sigma[kCurvb][kD0b] = b.errorMatrix()(KTHelix::kCurvature, KTHelix::kD0);
   sigma[kCurvb][kPhi0b] = b.errorMatrix()(KTHelix::kCurvature, KTHelix::kPhi0);
   sigma[kD0b][kCurvb] = b.errorMatrix()(KTHelix::kD0, KTHelix::kCurvature);
   sigma[kD0b][kD0b] = b.errorMatrix()(KTHelix::kD0, KTHelix::kD0);
   sigma[kD0b][kPhi0b] = b.errorMatrix()(KTHelix::kD0, KTHelix::kPhi0);
   sigma[kPhi0b][kCurvb] = b.errorMatrix()(KTHelix::kPhi0, KTHelix::kCurvature);
   sigma[kPhi0b][kD0b] = b.errorMatrix()(KTHelix::kPhi0, KTHelix::kD0);
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

   sig2x = 0.;
   sig2y = 0.;
   sig2xy = 0.;

   for ( i = 0;  i < kNumTrack;  i++ ) {
      sig2x += dx_dtrack[i] * x_std[i];
      sig2y += dy_dtrack[i] * y_std[i];
      sig2xy += dy_dtrack[i] * x_std[i];
   }
}
