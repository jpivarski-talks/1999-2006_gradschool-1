// -*- C++ -*-
//
// Package:     LookAtRawTrigger
// Module:      LookAtRawTrigger
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Feb 17 17:33:58 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "LookAtRawTrigger/LookAtRawTrigger.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "RawData/RawTrigger.h"
#include "TriggerL1Data/TriggerL1Data.h"

#include <iostream.h>

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
static const char* const kFacilityString = "Processor.LookAtRawTrigger" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
LookAtRawTrigger::LookAtRawTrigger( void )               // anal1
   : Processor( "LookAtRawTrigger" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &LookAtRawTrigger::event,    Stream::kEvent );
   //bind( &LookAtRawTrigger::beginRun, Stream::kBeginRun );
   //bind( &LookAtRawTrigger::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

LookAtRawTrigger::~LookAtRawTrigger()                    // anal5
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
LookAtRawTrigger::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
LookAtRawTrigger::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
LookAtRawTrigger::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
LookAtRawTrigger::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<RawTrigger> trig;
   extract(iFrame.record(Stream::kEvent), trig);

   if (!trig.valid()) report(SYSTEM, kFacilityString) << "RawTrigger invalid" << endl;
   else {
      RawTrigger::const_iterator iter = trig->begin();
      RawTrigger::const_iterator end = trig->end();
      report(SYSTEM, kFacilityString) << "Raw Trigger: ";
      for (; iter != end;  ++iter) {
	 report(SYSTEM, kFacilityString) << hex << *iter << " ";
      } // end of loop
      report(SYSTEM, kFacilityString) << dec << endl;
   } // end if valid

   FAItem<TriggerData> trigger;
   extract(iFrame.record(Stream::kEvent), trigger);

   report(SYSTEM, kFacilityString) << "Trigger L1AcceptBucket " << trigger->getL1AcceptBucket()
				   << " LumiL1AcceptBucket " << trigger->getLumiL1AcceptBucket()
				   << " CBTimeBucket " << trigger->getCBTimeBucket()
				   << " CETimeBucket " << trigger->getCETimeBucket()
				   << " TrackingTimeBucket " << trigger->getTrackingTimeBucket() << endl;
   for (int bucket = 0;  bucket < 4;  bucket++) {
      report(SYSTEM, kFacilityString) << "  bucket " << bucket
				      << " CBLoCount " << trigger->getCBLoCount(bucket)
				      << " CBMdCount " << trigger->getCBMdCount(bucket)
				      << " CBHiCount " << trigger->getCBHiCount(bucket)
				      << " CELoCount " << trigger->getCELoCount(bucket)
				      << " CEMdCount " << trigger->getCEMdCount(bucket)
				      << " CEHiCount " << trigger->getCEHiCount(bucket)
				      << " LoTrackCount " << trigger->getLoTrackCount(bucket)
				      << " HiTrackCount " << trigger->getHiTrackCount(bucket)
				      << " AxTrackCount " << trigger->getAxTrackCount(bucket)
				      << " LowposBits " << trigger->getLowposBits(bucket)
				      << " CBLoOld " << trigger->getCBLoOld(bucket)
				      << " CBMdOld " << trigger->getCBMdOld(bucket)
				      << " CBHiOld " << trigger->getCBHiOld(bucket)
				      << " CELoOld " << trigger->getCELoOld(bucket)
				      << " CEMdOld " << trigger->getCEMdOld(bucket)
				      << " CEHiOld " << trigger->getCEHiOld(bucket)
				      << " CBTimeBits " << trigger->getCBTimeBits(bucket)
				      << " CETimeBits " << trigger->getCETimeBits(bucket)
				      << " TrackingTimeBits " << trigger->getTrackingTimeBits(bucket) << endl;
   }

   FAItem<TriggerL1Data> t1;
   extract(iFrame.record(Stream::kEvent), t1);

   report(SYSTEM, kFacilityString) << "Formatted Trigger: "
				   << t1->isHadron() << " "
				   << t1->isMuPair() << " "
				   << t1->isCBSingleHi() << " "
				   << t1->isCESingleHi() << " "
				   << t1->isBarrelBhabha() << " "
				   << t1->isEndcapBhabha() << " "
				   << t1->isElTrack() << " "
				   << t1->isRadTau() << " "
				   << t1->isPulser() << " "
				   << t1->isRandom() << " "
				   << t1->isTwoTrack() << " "
				   << t1->isMinBias() << endl;

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
LookAtRawTrigger::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
LookAtRawTrigger::endRun( Frame& iFrame )         // anal4 equiv.
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
