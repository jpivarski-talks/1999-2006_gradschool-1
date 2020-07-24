// -*- C++ -*-
//
// Package:     BigNTuple
// Module:      BigNTuple
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
#include "BigNTuple/BigNTuple.h"
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
#include "Navigation/NavTkShMatch.h"
#include "C3cc/CcAssignedEnergyHit.h"
#include "BunchFinder/BunchDecision.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"
#include "/home/mccann/hadron_filter/src/EventVertex/EventVertex/EventVertex.h"

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
static const char* const kFacilityString = "Processor.BigNTuple" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.30 2002/04/02 22:04:09 ajm36 Exp $";
static const char* const kTagString = "$Name: v06_05_01 $";

//
// static data member definitions
//



//
// constructors and destructor
//
BigNTuple::BigNTuple( void )               // anal1
   : Processor( "BigNTuple" )
   , m_lookForCosmics( "lookForCosmics", this, false )
   , m_getBunchData( "getBunchData", this, true )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &BigNTuple::event,    Stream::kEvent );
   //bind( &BigNTuple::beginRun, Stream::kBeginRun );
   //bind( &BigNTuple::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

BigNTuple::~BigNTuple()                    // anal5
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
BigNTuple::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
BigNTuple::terminate( void )     // anal5 "Interactive"
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

const char* ntuple_labels[BigNTuple::kEntries] = {
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
};

// ---------------- standard place to book histograms ---------------
void
BigNTuple::hist_book( HIHistoManager& iHistoManager )
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

   m_cosmic_un_cosTh = iHistoManager.histogram(
      600, "cosmic unmatched shower cos(theta)", 100, -1., 1. );
   m_other_un_cosTh = iHistoManager.histogram(
      650, "other unmatched shower cos(theta)", 100, -1., 1. );
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
BigNTuple::event( Frame& iFrame )          // anal3 equiv.
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

   FAItem< EventVertex > eventVertex;
   if ( navtracks.size() > 2 )
      extract( iFrame.record( Stream::kEvent ), eventVertex );

   if ( m_lookForCosmics.value() )
      if ( navtracks.size() == 2 ) {

	 FATable< MuTrack > mutracks;
	 extract( iFrame.record( Stream::kEvent ), mutracks );

	 if ( mutracks.size() == 2 ) {

	    FATable< MuTrack >::const_iterator secondMu = mutracks.begin();
	    FATable< MuTrack >::const_iterator firstMu = secondMu;
	    secondMu++;

	    if ( firstMu->dpthmu() > 3.  &&
		 secondMu->dpthmu() > 3.     ) {

	       FATable< NavTrack >::const_iterator secondNav = navtracks.begin();
	       FATable< NavTrack >::const_iterator firstNav = secondNav;
	       secondNav++;

	       if ( ! firstNav->pionQuality()->fitAbort()  &&
		    ! secondNav->pionQuality()->fitAbort()     ) {

		  if ( ! firstNav->seedQuality()->originUsed()  &&
		       ! secondNav->seedQuality()->originUsed()     ) {

		     int suspicious_showers( 0 );
		     double suspicious_energy[2];
		     for ( FATable< NavShower >::const_iterator shower_iter = navshowers.begin();
			   shower_iter != showers_end;
			   shower_iter++ ) {

			double energy( shower_iter->attributes().energy() );

			if ( cosmic_energy_low < energy && energy < cosmic_energy_high  &&
			     ! shower_iter->attributes().hot()                          &&
			     shower_iter->trackMatches().size() == 1                       ) {

			   if ( suspicious_showers < 2 )
			      suspicious_energy[ suspicious_showers ] = energy;
			   suspicious_showers++;

			}
		     } // end loop over showers

		     if ( suspicious_showers == 2 ) {

			FAItem< TRHelixFit > firstHelix = firstNav->pionHelix();
			FAItem< TRHelixFit > secondHelix = secondNav->pionHelix();

			double phi0diff( firstHelix->phi0() - secondHelix->phi0() );
			if ( phi0diff < 0. ) phi0diff *= -1.;
			double d0sum( firstHelix->d0() + secondHelix->d0() );
			double z0diff( firstHelix->z0() - secondHelix->z0() );
			double cotThetadiff( firstHelix->cotTheta() + secondHelix->cotTheta() );

			report( DEBUG, kFacilityString ) << "energy1 = " << suspicious_energy[0] << endl;
			report( DEBUG, kFacilityString ) << "energy2 = " << suspicious_energy[1] << endl;
			report( DEBUG, kFacilityString ) << "phi0diff = " << phi0diff << endl;
			report( DEBUG, kFacilityString ) << "d0sum = " << d0sum << endl;
			report( DEBUG, kFacilityString ) << "z0diff = " << z0diff << endl;
			report( DEBUG, kFacilityString ) << "cotThetadiff = " << cotThetadiff << endl;

			if ( cosmic_phi0diff_low < phi0diff         &&  phi0diff < cosmic_phi0diff_high         &&
			     cosmic_d0sum_low < d0sum               &&  d0sum < cosmic_d0sum_high               &&
			     cosmic_z0diff_low < z0diff             &&  z0diff < cosmic_z0diff_high             &&
			     cosmic_cotThetadiff_low < cotThetadiff && cotThetadiff < cosmic_cotThetadiff_high     ) {

			   isCosmic = true;

			   m_cosmic_energy->fill( suspicious_energy[0] );
			   m_cosmic_energy->fill( suspicious_energy[1] );
			   m_cosmic_phi0diff->fill( phi0diff );
			   m_cosmic_d0sum->fill( d0sum );
			   m_cosmic_z0diff->fill( z0diff );
			   m_cosmic_cotThetadiff->fill( cotThetadiff );

			} } } } } } } // end tests for isCosmic

   float v[kEntries];
   for ( int i = 0;  i < kEntries;  i++ ) v[i] = 0.;
   
   double w_z0_denom( 0. );
   double w_d0_denom( 0. );

   // track loop
   for ( FATable< NavTrack >::const_iterator track_iter = navtracks.begin();
	 track_iter != tracks_end;
	 track_iter++ )
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

	 v[kTotalTrackMomentum] += track_iter->pionFit()->momentum().mag();
	 if ( track_iter->pionFit()->momentum().mag() > v[kMaxTrackMomentum] )
	    v[kMaxTrackMomentum] = track_iter->pionFit()->momentum().mag();

	 v[kTotalTrackEnergy] += track_iter->pionFit()->energy();
	 if ( track_iter->pionFit()->energy() > v[kMaxTrackEnergy] )
	    v[kMaxTrackEnergy] = track_iter->pionFit()->energy();
      } // end loop over tracks

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

	    if ( m_lookForCosmics.value()  &&  isCosmic )
	       m_cosmic_un_cosTh->fill( shower_iter->attributes().theta() );
	    else
	       m_other_un_cosTh->fill( shower_iter->attributes().theta() );

	 } // end if no track match
      }

   if ( m_getBunchData.value() )
      if ( bunchDecision->numberOfTestedBunches() > 0 ) {
	 v[kBunchWeightBest] = bunchDecision->bestBunchInfo().bweight();
	 v[kBunchWeightNext] = bunchDecision->bunchInfo( 1 ).bweight();
      }

   if ( navtracks.size() > 2  &&
	eventVertex->vertexType() == EventVertex::kGoodEvent ) {
      v[kVertexX] = eventVertex->vertexPosition().x();
      v[kVertexY] = eventVertex->vertexPosition().y();
      v[kVertexZ] = eventVertex->vertexPosition().z();
      v[kVertexChi2] = eventVertex->vertexChiSquare();
      v[kVertexChi2perTrack] = ( eventVertex->vertexChiSquare() / 
				 eventVertex->numTrackFinalVertex() );
   }

   for ( int j = 0;  j < kEntries;  j++ )
      report( DEBUG, kFacilityString )
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
BigNTuple::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
BigNTuple::endRun( Frame& iFrame )         // anal4 equiv.
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

