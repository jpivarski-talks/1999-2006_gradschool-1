// -*- C++ -*-
//
// Package:     CertainBhabhas
// Module:      CertainBhabhas
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim McCann
// Created:     Thu Jun  6 14:42:54 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "CertainBhabhas/CertainBhabhas.h"
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
#include "C3Mu/MuTrack.h"
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "Navigation/NavTkShMatch.h"
#include "BunchFinder/BunchDecision.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"

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
static const char* const kFacilityString = "Processor.CertainBhabhas" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.30 2002/04/02 22:04:09 ajm36 Exp $";
static const char* const kTagString = "$Name: v06_05_01 $";

//
// static data member definitions
//



//
// constructors and destructor
//
CertainBhabhas::CertainBhabhas( void )               // anal1
   : Processor( "CertainBhabhas" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &CertainBhabhas::event,    Stream::kEvent );
   //bind( &CertainBhabhas::beginRun, Stream::kBeginRun );
   //bind( &CertainBhabhas::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

CertainBhabhas::~CertainBhabhas()                    // anal5
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
CertainBhabhas::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
CertainBhabhas::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
CertainBhabhas::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_showers_energy = iHistoManager.histogram(
      100, "showers energy", 100, 0., 7. );
   m_showers_momentum = iHistoManager.histogram(
      200, "showers momentum", 100, 0., 1. );
   m_track_momentum = iHistoManager.histogram(
      400, "track momentum", 100, 0., 7. );
   m_weighted_d0 = iHistoManager.histogram(
      500, "weighted d0", 100, 0., 0.005 );
   m_weighted_z0 = iHistoManager.histogram(
      600, "weighted z0", 100, -0.05, 0.05 );
   m_bunchwt = iHistoManager.histogram(
      700, "bunchweight margin", 100, 0., 1. );

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
CertainBhabhas::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable< NavShower > navshowers;
   extract( iFrame.record( Stream::kEvent ), navshowers );

   int bhabha_showers( 0 );
   Hep3Vector showers_momentum( 0., 0., 0. );
   FATable< NavShower >::const_iterator shower_iter;
   for ( shower_iter = navshowers.begin();
	 shower_iter != navshowers.end();
	 shower_iter++ )
      if ( ( shower_iter->attributes().goodBarrel() ||
	     shower_iter->attributes().goodEndcap()    )  &&
	   ! shower_iter->attributes().hot()                  ) {
	 
	 m_showers_energy->fill( shower_iter->attributes().energy() );

	 // look out: minimum-ionizing particle, could be a muon!
	 if ( 0.150 < shower_iter->attributes().energy()          &&
	      shower_iter->attributes().energy() < 0.270      )
	    return ActionBase::kFailed;

	 if ( 0.270 < shower_iter->attributes().energy() ) {
	    bhabha_showers++;
	    showers_momentum += shower_iter->attributes().momentum();
	 }
      }

   if ( bhabha_showers != 2 ) return ActionBase::kFailed;
   if ( showers_momentum.mag() > 1. ) return ActionBase::kFailed;

   // now you have to do tracking...
   for ( shower_iter = navshowers.begin();
	 shower_iter != navshowers.end();
	 shower_iter++ )
      if ( ! shower_iter->attributes().hot() ) {
	 // medium-sized showers shouldn't be allowed
	 if ( 0.150 < shower_iter->attributes().energy()  &&
	      shower_iter->attributes().energy() < 4.6       ) {
	    return ActionBase::kFailed;
	 }
	 // huge showers shouldn't be allowed
	 else if ( 6. < shower_iter->attributes().energy() ) {
	    return ActionBase::kFailed;
	 }
	 // little showers can exist, so long as they have no associated tracks
	 else if ( shower_iter->attributes().energy() < 0.150 ) {
	    if ( shower_iter->trackMatches().size() != 0 ) return ActionBase::kFailed;
	 }
	 // beam-energy showers should be from the bhabhas
	 else if ( 4.6 < shower_iter->attributes().energy()  &&
		   shower_iter->attributes().energy() < 6. ) {
	    if ( shower_iter->trackMatches().size() != 1 ) return ActionBase::kFailed;
	 }
      }
      else { // hot shower!
      }

   FATable< NavTrack > navtracks;
   extract( iFrame.record( Stream::kEvent ), navtracks );

   if ( navtracks.size() != 2 ) return ActionBase::kFailed;
   
   FATable< NavTrack >::const_iterator track_iter;
   HepVector3D event_momentum( 0., 0., 0. );
   for ( track_iter = navtracks.begin();
	 track_iter != navtracks.end();
	 track_iter++ ) {
      // no tolerance for fit-aborts or z-escapes
      if ( track_iter->pionQuality()->fitAbort()  ||
	   track_iter->seedQuality()->originUsed()   )
	 return ActionBase::kFailed;

      // the momentum must be right
      m_track_momentum->fill( track_iter->pionFit()->momentum().mag() );
      if ( track_iter->pionFit()->momentum().mag() < 4.6  ||
           6. < track_iter->pionFit()->momentum().mag()     )
	 return ActionBase::kFailed;

      // only take a particular range in theta
      if ( abs( track_iter->pionHelix()->cotTheta() ) > 1.265 )
	 return ActionBase::kFailed;

      event_momentum += track_iter->pionFit()->momentum();
   }

   // I've already studied this cut
   double xdiff2 = sqr( event_momentum.x() + 0.0261 );
   double ydiff2 = sqr( event_momentum.y() + 0.0003 );
   if ( ( xdiff2 + ydiff2 ) > 0.300 ) return ActionBase::kFailed;

   FAItem< TRHelixFit > first_helix = navtracks.begin()->pionHelix();
   FAItem< TRHelixFit > second_helix = ( ++navtracks.begin() )->pionHelix();

   // this one is obvious
   if ( first_helix->curvature() * second_helix->curvature() > 0. )
      return ActionBase::kFailed;

   // I've already done most of this with event_momentum
//     // tight back-to-back cuts that I used in cosmic determination
//     double phi0diff( first_helix->phi0() - second_helix->phi0() );
//     double d0sum( first_helix->d0() + second_helix->d0() );
   double z0diff( first_helix->z0() - second_helix->z0() );
//     double cotThetadiff( first_helix->cotTheta() - second_helix->cotTheta() );

//     if ( phi0diff < 3.1415926-0.005  ||  3.1415926+0.005 < phi0diff  ||
//  	abs( d0sum ) > 0.0005                                       ||
//  	abs( z0diff ) > 0.001                                       ||
//  	abs( cotThetadiff ) > 0.015                                    )
//     return ActionBase::kFailed;
   if ( abs( z0diff ) > 0.002 ) return ActionBase::kFailed;

   // additionally, we want this to come from the beamspot
   if ( first_helix->hasNullErrorMatrix()  ||  second_helix->hasNullErrorMatrix()  ||
	first_helix->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) == 0.             ||
	first_helix->errorMatrix()( KTHelix::kD0, KTHelix::kD0 ) == 0.             ||
	second_helix->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) == 0.            ||
	second_helix->errorMatrix()( KTHelix::kD0, KTHelix::kD0 ) == 0.               )
      return ActionBase::kFailed;
   HepSymMatrix first_matrix( first_helix->errorMatrix() );
   HepSymMatrix second_matrix( first_helix->errorMatrix() );
   double d0_numer( abs( first_helix->d0() ) / first_matrix( KTHelix::kZ0, KTHelix::kZ0 ) +
		    abs( second_helix->d0() ) / second_matrix( KTHelix::kZ0, KTHelix::kZ0 ) );
   double d0_denom( 1. / first_matrix( KTHelix::kZ0, KTHelix::kZ0 ) +
		    1. / second_matrix( KTHelix::kZ0, KTHelix::kZ0 )  );
   double z0_numer( first_helix->z0() / first_matrix( KTHelix::kD0, KTHelix::kD0 ) +
		    second_helix->z0() / second_matrix( KTHelix::kD0, KTHelix::kD0 ) );
   double z0_denom( 1. / first_matrix( KTHelix::kD0, KTHelix::kD0 ) +
		    1. / second_matrix( KTHelix::kD0, KTHelix::kD0 )  );
   if ( d0_denom == 0.  ||  z0_denom == 0. ) return ActionBase::kFailed;
   m_weighted_d0->fill( d0_numer / d0_denom );
   m_weighted_z0->fill( z0_numer / z0_denom );

   if ( abs( d0_numer / d0_denom ) > 0.003  ||
	abs( z0_numer / z0_denom ) > 0.03      )
      return ActionBase::kFailed;

   // one last check: make sure there are no muon clusters associated with either track
   FATable< MuTrack > mutracks;
   extract( iFrame.record( Stream::kEvent ), mutracks );
   if ( mutracks.size() != 0 ) return ActionBase::kFailed;

   // NOW I trust that this is a bhabha.
   m_showers_momentum->fill( showers_momentum.mag() );

   FAItem< TrackletBunchDecision > bunchDecision;
   extract( iFrame.record( Stream::kEvent ), bunchDecision );

   if ( bunchDecision->bestBunchInfo().bweight() != 0. )
      m_bunchwt->fill( ( bunchDecision->bestBunchInfo().bweight() -
			 bunchDecision->bunchInfo( 1 ).bweight()    )
		       / bunchDecision->bestBunchInfo().bweight()     );

   return ActionBase::kPassed;
}

/*
  ActionBase::ActionResult
  CertainBhabhas::beginRun( Frame& iFrame )       // anal2 equiv.
  {
  report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

  return ActionBase::kPassed;
  }
*/

/*
  ActionBase::ActionResult
  CertainBhabhas::endRun( Frame& iFrame )         // anal4 equiv.
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
