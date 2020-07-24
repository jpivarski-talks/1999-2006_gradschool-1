// -*- C++ -*-
//
// Package:     SimpleZ0Cut
// Module:      SimpleZ0Cut
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim McCann
// Created:     Mon Mar 25 09:42:10 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "SimpleZ0Cut/SimpleZ0Cut.h"
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
static const char* const kFacilityString = "Processor.SimpleZ0Cut" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.27 2002/03/12 16:22:13 ajm36 Exp $";
static const char* const kTagString = "$Name: v06_03_03 $";

//
// static data member definitions
//


//
// constructors and destructor
//
SimpleZ0Cut::SimpleZ0Cut( void )               // anal1
   : Processor( "SimpleZ0Cut" )
   , m_bhabhas( 0 )
   , m_gamgams( 0 )
   , m_hadrons( 0 )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &SimpleZ0Cut::event,    Stream::kEvent );
   //bind( &SimpleZ0Cut::beginRun, Stream::kBeginRun );
   //bind( &SimpleZ0Cut::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

SimpleZ0Cut::~SimpleZ0Cut()                    // anal5
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
SimpleZ0Cut::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
SimpleZ0Cut::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
SimpleZ0Cut::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_z0 = iHistoManager.histogram(
      100, "z0", 200, -1.*k_m, 1.*k_m );

   m_event_z0 = iHistoManager.histogram(
      200, "event z0 (weighted)", 200, -1.*k_m, 1.*k_m );

   m_norm_event_z0 = iHistoManager.histogram(
      300, "norm event z0 (weighted)", 200, -20., 20. );

   m_type = iHistoManager.histogram(
      400, "1 = bhabha, 2 = gamgam, 3 = hadronic, 4 = other",
      4, 0.5, 4.5 );

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
SimpleZ0Cut::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   int unmatched_showers( 0 );
   int matched_showers( 0 );
   int tracks( 0 );

   int event_charge( 0 );
   double shower1( 0. );
   double shower2( 0. );
   double mom1( 0. );
   double mom2( 0. );
   
   double cc_energy( 0. );
   double biggest_shower( 0. );

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
      const CcShowerAttributes& atts( showerItr->attributes() );

      if ( atts.goodBarrel()  ||  atts.goodEndcap() )
	 cc_energy += atts.energy();

      if ( !( atts.goodBarrel()  ||  atts.goodEndcap() )  ||
	   atts.energy() < 100*k_MeV                      ||
	   false )
	 continue;  // (bad shower)

      if ( atts.energy() > biggest_shower )
	 biggest_shower = atts.energy();

      if ( shower1 == 0. ) shower1 = atts.energy();
      else if ( shower2 == 0. ) shower2 = atts.energy();

      if ( showerItr->noTrackMatch() ) {
	 unmatched_showers++;
      } else {
	 matched_showers++;
      }
   } // end loop over showers

   // Create a table of tracks and fill it.
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ), trackTable );

   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();
   // Loop over tracks.
   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd;
         ++trackItr ) {
      // Ask for the pion fit and quality information.
      FAItem< TDKinematicFit > pionFit = trackItr->pionFit();
      FAItem< TRHelixFit > pionHelix = trackItr->pionHelix();
      FAItem< TRTrackFitQuality > pionQuality = trackItr->pionQuality();
      FAItem< TRSeedTrackQuality > seedQuality = trackItr->seedQuality();

      if ( seedQuality->numberHitsExpected() == 0     ||
	   seedQuality->originUsed()                  ||
	   pionQuality->fitAbort()                    ||
	   // this is temporary
//	   pionFit->momentum().mag() < 500.*k_MeV     ||
	   false )
	 continue;  // (bad track)

      tracks++;

      event_charge += ( pionHelix->curvature() > 0. ? 1 : -1 );
      if ( mom1 == 0. ) mom1 = pionFit->momentum().mag();
      else if ( mom2 == 0. ) mom2 = pionFit->momentum().mag();

      double z0( pionHelix->z0() );
      double z0_weight( 1./ abs(
	 pionHelix->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 )
	 ) );

      m_z0->fill( z0 );

      sum_z0 += z0 * z0_weight;
      sum_z0_weights += z0_weight;

   } // end loop over tracks

   if ( tracks == 0 ) return ActionBase::kFailed;

   double weighted_ave_z0( sum_z0 / sum_z0_weights );
   double weighted_ave_z0_err( sqrt( 1. / sum_z0_weights ) );

   m_event_z0->fill( weighted_ave_z0 );
   if ( weighted_ave_z0_err > 0. )
      m_norm_event_z0->fill( weighted_ave_z0 / weighted_ave_z0_err );

   if ( abs( weighted_ave_z0 ) > 5.*k_cm ) return ActionBase::kFailed;

   DABoolean change( false );

   if ( unmatched_showers == 0   &&
	matched_showers == 2     &&
	tracks == 2              &&
	event_charge == 0        &&
	shower1 > 2.*k_GeV       &&
	shower2 > 2.*k_GeV       &&
	mom1 > 4.*k_GeV          &&
	mom2 > 4.*k_GeV          &&
	true )
   { m_bhabhas++;  m_type->fill( 1. );  change = true; }

   else if ( unmatched_showers == 2   &&
	     matched_showers == 0     &&
	     tracks == 0              &&
	     shower1 > 2.*k_GeV       &&
	     shower2 > 2.*k_GeV       &&
	     true )
   { m_gamgams++;  m_type->fill( 2. );  change = true; }

   else if ( tracks > 2               &&
	     cc_energy > 2.*k_GeV     &&
	     ( tracks > 4               ||
	       ( cc_energy > 1.5*k_GeV      &&
		 ( cc_energy < 7.5*k_GeV       ||
		   biggest_shower < 7.5*k_GeV     )
		  )
		)                     &&
	     true )
   { m_hadrons++;  m_type->fill( 3. );  change = true; }

   else m_type->fill( 4. );

   if ( change ) { // save some temp disk space

      report( NOTICE, kFacilityString )
	 << "bhabhas = " << m_bhabhas << " gamgams = " << m_gamgams
	 << " hadrons = " << m_hadrons << endl;
      
      if ( m_hadrons != 0  &&  m_bhabhas != 0 )
	 report( NOTICE, kFacilityString )
	    << "hadrons / bhabhas = "
	    << double( m_hadrons ) / double( m_bhabhas )
	    << " +/- " << ( double( m_hadrons ) / double( m_bhabhas )
			    * sqrt( 1. / m_hadrons + 1. / m_bhabhas ) )
	    << endl;
      
      if ( m_hadrons != 0  &&  m_gamgams != 0 )
	 report( NOTICE, kFacilityString )
	    << "hadrons / gamgams = "
	    << double( m_hadrons ) / double( m_gamgams )
	    << " +/- " << ( double( m_hadrons ) / double( m_gamgams )
			    * sqrt( 1. / m_hadrons + 1. / m_gamgams ) )
	    << endl;
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
SimpleZ0Cut::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
SimpleZ0Cut::endRun( Frame& iFrame )         // anal4 equiv.
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
