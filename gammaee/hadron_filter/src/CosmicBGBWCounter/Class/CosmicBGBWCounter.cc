// -*- C++ -*-
//
// Package:     CosmicBGBWCounter
// Module:      CosmicBGBWCounter
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Wed Sep  4 15:19:33 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "CosmicBGBWCounter/CosmicBGBWCounter.h"
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
static const char* const kFacilityString = "Processor.CosmicBGBWCounter" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
CosmicBGBWCounter::CosmicBGBWCounter( void )               // anal1
   : Processor( "CosmicBGBWCounter" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &CosmicBGBWCounter::event,    Stream::kEvent );
   //bind( &CosmicBGBWCounter::beginRun, Stream::kBeginRun );
   //bind( &CosmicBGBWCounter::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

CosmicBGBWCounter::~CosmicBGBWCounter()                    // anal5
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
CosmicBGBWCounter::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
CosmicBGBWCounter::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
CosmicBGBWCounter::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* labels[9] = {"d0", "phi0", "cotTheta", "z0",
			    "numtr", "d0miss", "sinmiss", "thmiss", "z0miss"};
   m_ntuple = iHistoManager.ntuple(1, "ntuple", 9, 262144, labels);

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
CosmicBGBWCounter::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   // Create a table of tracks and fill it.
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable );

   int numTracks(0);
   float d0miss(1.), sinmiss(1.), thmiss(1.), z0miss(1.);

   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();
   // Loop over tracks.
   for ( FATable< NavTrack >::const_iterator t1 = trackTableBegin;
         t1 != trackTableEnd ;
         t1++ )
   {
      FATable< NavTrack >::const_iterator t2 = t1;  t2++;

      for ( ; t2 != trackTableEnd;  t2++ )
      {
	 if ( ! t1->pionQuality()->fitAbort()    &&
	      ! t2->pionQuality()->fitAbort()    &&
	      ! t1->seedQuality()->originUsed()  &&
	      ! t2->seedQuality()->originUsed()      )
	 {
	    FAItem< TRHelixFit > h1 = t1->pionHelix();
	    FAItem< TRHelixFit > h2 = t2->pionHelix();

	    float trial_d0miss(h1->d0() + h2->d0());
	    float trial_sinmiss(sin(h1->phi0() - h2->phi0()));
	    float trial_thmiss(h1->cotTheta() - h2->cotTheta());
	    float trial_z0miss(h1->z0() - h2->z0());
	    
	    if ( abs(trial_d0miss) < abs(d0miss) ) d0miss = trial_d0miss;
	    if ( trial_sinmiss < sinmiss ) sinmiss = trial_sinmiss;
	    if ( abs(trial_thmiss) < abs(thmiss) ) thmiss = trial_thmiss;
	    if ( abs(trial_z0miss) < abs(z0miss) ) z0miss = trial_z0miss;
	 } // end if both pass cuts
      } // end loop over t2

      if ( ! t1->pionQuality()->fitAbort()  &&
	   ! t1->seedQuality()->originUsed()   )
	 numTracks++;

   } // end loop over t1

   for ( FATable< NavTrack >::const_iterator track = trackTableBegin;
         track != trackTableEnd ;
         track++ )
   {
      if ( ! track->pionQuality()->fitAbort()  &&
	   ! track->seedQuality()->originUsed()   )
      {
	 FAItem< TRHelixFit > helix = track->pionHelix();

	 float v[9] = {helix->d0(), helix->phi0(), helix->cotTheta(), helix->z0(),
		       float(numTracks), d0miss, sinmiss, thmiss, z0miss};
	 m_ntuple->fill(v);

      } // end if passes cuts
   } // end loop over tracks

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
CosmicBGBWCounter::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
CosmicBGBWCounter::endRun( Frame& iFrame )         // anal4 equiv.
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
