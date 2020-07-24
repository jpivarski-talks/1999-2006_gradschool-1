// -*- C++ -*-
//
// Package:     TmpFilterProc
// Module:      TmpFilterProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Oct  8 12:34:47 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TmpFilterProc/TmpFilterProc.h"
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
static const char* const kFacilityString = "Processor.TmpFilterProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TmpFilterProc::TmpFilterProc( void )               // anal1
   : Processor( "TmpFilterProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TmpFilterProc::event,    Stream::kEvent );
   //bind( &TmpFilterProc::beginRun, Stream::kBeginRun );
   //bind( &TmpFilterProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

TmpFilterProc::~TmpFilterProc()                    // anal5
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
TmpFilterProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TmpFilterProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
TmpFilterProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TmpFilterProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   
   int ntracks( tracks.size() );
   int charge(0);
   for ( FATable< NavTrack >::const_iterator track_iter = tracks.begin();
	 track_iter != tracks.end();
	 track_iter++ )
      charge += ( track_iter->pionHelix()->curvature() > 0. ? 1 : -1 );

   report( NOTICE, kFacilityString )
      << "ntracks = " << ntracks << " charge = " << charge << endl;

   if ( ntracks > 20  &&  abs(charge) > 1 )
      return ActionBase::kPassed;
   else
      return ActionBase::kFailed;

//     // Create a table of tracks and fill it.
//     FATable< NavTrack > trackTable;
//     extract( iFrame.record( Stream::kEvent ) , trackTable );

//     double charge(0.);

//     FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
//     FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();
//     // Loop over tracks.
//     for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
//           trackItr != trackTableEnd ;
//           ++trackItr )
//     {
//        if ( ! trackItr->pionQuality()->fitAbort() )
//  	 charge += ( trackItr->pionHelix()->curvature() > 0. ? 1. : -1. );
//        else
//  	 charge += ( trackItr->seedTrack()->curvature() > 0. ? 1. : -1. );
//     }

//     if ( charge > 3.5 ) return ActionBase::kPassed;
//     else return ActionBase::kFailed;

//     FAItem< BunchDecision > decision;
//     extract( iFrame.record( Stream::kEvent ), decision );
//     cout << "bunchnumber, bunchtime, ntested " << decision->bestBunchNumber()
//  	<< " " << decision->bestBunchTime()
//  	<< " " << decision->numberOfTestedBunches() << endl;

//     FAItem< TrackletBunchDecision > decision;
//     extract( iFrame.record( Stream::kEvent ), decision );
//     cout << "BOINK " << decision->bestBunchInfo().bweight() << " "
//  	<< decision->bunchInfo(1).bweight() << endl;

//     double best( decision->bestBunchInfo().bweight() );
//     double next( decision->bunchInfo(1).bweight() );
//     double margin( (best - next) / best );

//     if ( margin > 0.25 ) return ActionBase::kPassed;
//     else return ActionBase::kFailed;
   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
TmpFilterProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
TmpFilterProc::endRun( Frame& iFrame )         // anal4 equiv.
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
