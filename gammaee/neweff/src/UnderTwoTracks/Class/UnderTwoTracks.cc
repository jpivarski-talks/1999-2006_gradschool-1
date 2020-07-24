// -*- C++ -*-
//
// Package:     UnderTwoTracks
// Module:      UnderTwoTracks
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Mar 29 14:15:47 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "UnderTwoTracks/UnderTwoTracks.h"
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

#include "EventProperties/EventProperties.h"
#include "BeamEnergy/BeamEnergy.h"

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
static const char* const kFacilityString = "Processor.UnderTwoTracks" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
UnderTwoTracks::UnderTwoTracks( void )               // anal1
   : Processor( "UnderTwoTracks" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &UnderTwoTracks::event,    Stream::kEvent );
   //bind( &UnderTwoTracks::beginRun, Stream::kBeginRun );
   //bind( &UnderTwoTracks::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

UnderTwoTracks::~UnderTwoTracks()                    // anal5
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
UnderTwoTracks::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
UnderTwoTracks::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
UnderTwoTracks::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
UnderTwoTracks::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

//    static bool first = true;
//    if (first) {
//       first = false;
//       FAItem<BeamEnergy> eBeam;
//       extract(iFrame.record(Stream::kStartRun), eBeam);
//       cout << "EBEAM " << eBeam->value() << endl;
//    }

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

//    if (props->nbChargedTracks() == 2) {
//       FATable<NavTrack> tracks;
//       extract(iFrame.record(Stream::kEvent), tracks);

//       HepVector3D p1 = tracks.find(props->firstTrackIdentifier())->pionFit()->momentum();
//       HepVector3D p2 = tracks.find(props->secondTrackIdentifier())->pionFit()->momentum();

//       cout << "GO_BOOTS " << p1.x() + p2.x() << endl;
//    }

   if (props->nbChargedTracks() < 3) return ActionBase::kPassed;
   else return ActionBase::kFailed;

}

/*
ActionBase::ActionResult
UnderTwoTracks::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
UnderTwoTracks::endRun( Frame& iFrame )         // anal4 equiv.
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
