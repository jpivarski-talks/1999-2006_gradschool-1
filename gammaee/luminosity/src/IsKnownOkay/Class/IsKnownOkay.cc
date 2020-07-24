// -*- C++ -*-
//
// Package:     IsKnownOkay
// Module:      IsKnownOkay
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Wed Apr 20 10:49:22 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "IsKnownOkay/IsKnownOkay.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "EventProperties/EventProperties.h"
#include "EventType/EventType.h"
#include "BeamEnergy/BeamEnergy.h"
#include "Level3TagWord/Level3TagWord.h"
#include "Level4Proc/Level4Decision.h"
#include "Level4Proc/Level4DecisionProxy.h"


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
static const char* const kFacilityString = "Processor.IsKnownOkay" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
IsKnownOkay::IsKnownOkay( void )               // anal1
   : Processor( "IsKnownOkay" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &IsKnownOkay::event,    Stream::kEvent );
   //bind( &IsKnownOkay::beginRun, Stream::kBeginRun );
   //bind( &IsKnownOkay::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

IsKnownOkay::~IsKnownOkay()                    // anal5
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
IsKnownOkay::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
IsKnownOkay::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
IsKnownOkay::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
IsKnownOkay::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<EventType> type;
   extract(iFrame.record(Stream::kEvent), type);

   FAItem<Level4Decision> l4dec;
   extract(iFrame.record(Stream::kEvent), l4dec);

   if ((props->chargedEnergy() + props->neutralEnergy()) / 2. /eBeam->value() > 0.4) {
      if (!type->known()) report(SYSTEM, kFacilityString)
	 << "Ack! visen = "
	 << (props->chargedEnergy() + props->neutralEnergy()) / 2. / eBeam->value()
	 << " and not known!" << endl;
   }

   if ((props->chargedEnergy() + props->neutralEnergy()) / 2. /eBeam->value() > 0.04  &&  props->nbChargedTracks() > 1) {
      if (!type->known()) report(SYSTEM, kFacilityString)
	 << "Ack! visen = "
	 << (props->chargedEnergy() + props->neutralEnergy()) / 2. / eBeam->value()
	 << " and tracks = " << props->nbChargedTracks()
	 << " and not known!" << endl;
   }

//    if (type->known() && l4dec->decision() == 0) {
//       report(SYSTEM, kFacilityString)
// 	 << "Yay!  known and l4dec == 0 happens SOMETIMES..." << endl;
//    }

//    if (l4dec->decision() == 0)
//       report(SYSTEM, kFacilityString) << "l4dec == 0" << endl;

//    if (!type->known())
//       report(SYSTEM, kFacilityString) << "!known" << endl;


   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
IsKnownOkay::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
IsKnownOkay::endRun( Frame& iFrame )         // anal4 equiv.
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
