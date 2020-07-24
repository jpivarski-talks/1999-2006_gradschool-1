// -*- C++ -*-
//
// Package:     TrackShowerEfficiency
// Module:      TrackShowerEfficiency
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Apr 28 15:28:42 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TrackShowerEfficiency/TrackShowerEfficiency.h"
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
#include "CleoDB/DBEventHeader.h"
#include "BeamEnergy/BeamEnergy.h"
#include "EventType/EventType.h"
#include "Navigation/NavTkShMatch.h"

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
static const char* const kFacilityString = "Processor.TrackShowerEfficiency" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TrackShowerEfficiency::TrackShowerEfficiency( void )               // anal1
   : Processor( "TrackShowerEfficiency" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TrackShowerEfficiency::event,    Stream::kEvent );
   //bind( &TrackShowerEfficiency::beginRun, Stream::kBeginRun );
   //bind( &TrackShowerEfficiency::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

TrackShowerEfficiency::~TrackShowerEfficiency()                    // anal5
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
TrackShowerEfficiency::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TrackShowerEfficiency::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
TrackShowerEfficiency::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TrackShowerEfficiency::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<BeamEnergy> beamEnergy;
   extract(iFrame.record(Stream::kStartRun), beamEnergy);
 
   FAItem<DBEventHeader> header;
   extract(iFrame.record(Stream::kEvent), header);

   FAItem<EventType> eventType;
   extract(iFrame.record(Stream::kEvent), eventType);

   int numShowers(0);
   int noTrackMatch(0);
   int noTrackMatchConReg(0);
   int noBrem(0);
   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator shower_end = showers.end();
   for ( FATable<NavShower>::const_iterator shower_iter = showers.begin();
	 shower_iter != shower_end;
	 ++shower_iter ) {
      if ( shower_iter->attributes().energy() > 0.01 * beamEnergy->value()  &&
	   shower_iter->attributes().status() ) {
	 numShowers++;
	 if ( shower_iter->noTrackMatch() ) noTrackMatch++;
	 if ( shower_iter->noTrackMatchConReg() ) noTrackMatchConReg++;
	 if ( !shower_iter->bremTrack().valid()  ||
	      ( shower_iter->bremTrack()->trackShowerMatch().valid()         &&
		shower_iter->bremTrack()->trackShowerMatch()->eOverP() < 0.5    ) ) noBrem++;
      } // end if relevant shower
   } // end loop over showers

   cout << "NTUPLE " << header->run() << " " << header->number()
	<< " " << numShowers << " " << noTrackMatch << " " << noTrackMatchConReg << " " << noBrem
	<< " " << eventType->hadron() << endl;

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
TrackShowerEfficiency::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
TrackShowerEfficiency::endRun( Frame& iFrame )         // anal4 equiv.
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
