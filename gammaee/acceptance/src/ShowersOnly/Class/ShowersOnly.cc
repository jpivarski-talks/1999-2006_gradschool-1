// -*- C++ -*-
//
// Package:     ShowersOnly
// Module:      ShowersOnly
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri May 21 10:28:56 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ShowersOnly/ShowersOnly.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "TriggerL1Data/TriggerL1Data.h"
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
static const char* const kFacilityString = "Processor.ShowersOnly" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
ShowersOnly::ShowersOnly( void )               // anal1
   : Processor( "ShowersOnly" )
   , m_eBeam("eBeam", this, 0.)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &ShowersOnly::event,    Stream::kEvent );
   //bind( &ShowersOnly::beginRun, Stream::kBeginRun );
   //bind( &ShowersOnly::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

ShowersOnly::~ShowersOnly()                    // anal5
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
ShowersOnly::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
ShowersOnly::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
ShowersOnly::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   const char* label[kNumEntries] = {
      "t1had", "t1rad", "t1el", "t1tt",
      "tracks", "visen", "ccen", "e1",
      "neue", "q",
      "ebeam"
   };

   m_ntuple = iHistoManager.ntuple(
      1, "ntuple", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
ShowersOnly::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   float v[kNumEntries];
   v[k_ebeam] = m_eBeam.value();

   FAItem<TriggerL1Data> triggerDecision;
   extract(iFrame.record(Stream::kEvent), triggerDecision);
   v[k_t1had] = triggerDecision->isHadron();
   v[k_t1rad] = triggerDecision->isRadTau();
   v[k_t1el] = triggerDecision->isElTrack();
   v[k_t1tt] = triggerDecision->isTwoTrack();

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);
   v[k_tracks] = props->nbChargedTracks();
   v[k_visen] = (props->chargedEnergy() + props->neutralEnergy()) / 2. / v[k_ebeam];
   v[k_ccen] = props->ccTotalEnergy() / 2. / v[k_ebeam];
   v[k_e1] = props->firstLargestEShower() / v[k_ebeam];
   v[k_neue] = props->neutralEnergy() / 2. / v[k_ebeam];
   v[k_q] = float(props->netCharge());

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
ShowersOnly::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
ShowersOnly::endRun( Frame& iFrame )         // anal4 equiv.
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
