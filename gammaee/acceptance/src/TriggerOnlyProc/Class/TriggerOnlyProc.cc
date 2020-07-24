// -*- C++ -*-
//
// Package:     TriggerOnlyProc
// Module:      TriggerOnlyProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Thu May 20 02:31:16 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TriggerOnlyProc/TriggerOnlyProc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "TriggerL1Data/TriggerL1Data.h"
#include "TriggerInfoProd/TriggerInfo.h"

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
static const char* const kFacilityString = "Processor.TriggerOnlyProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TriggerOnlyProc::TriggerOnlyProc( void )               // anal1
   : Processor( "TriggerOnlyProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TriggerOnlyProc::event,    Stream::kEvent );
   //bind( &TriggerOnlyProc::beginRun, Stream::kBeginRun );
   //bind( &TriggerOnlyProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

TriggerOnlyProc::~TriggerOnlyProc()                    // anal5
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
TriggerOnlyProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TriggerOnlyProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
TriggerOnlyProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here
   const char* label[kNumEntries] = {
      "t1had", "t1rad", "t1el", "t1tt",
      "axial", "stereo", "cblo", "cbmd"
   };

   m_ntuple = iHistoManager.ntuple(
      1, "ntuple", kNumEntries, 262144, label);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TriggerOnlyProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;
   float v[kNumEntries];

   FAItem<TriggerL1Data> triggerDecision;
   extract(iFrame.record(Stream::kEvent), triggerDecision);
   v[k_t1had] = triggerDecision->isHadron();
   v[k_t1rad] = triggerDecision->isRadTau();
   v[k_t1el] = triggerDecision->isElTrack();
   v[k_t1tt] = triggerDecision->isTwoTrack();

   FAItem<TriggerInfo> triggerInfo;
   extract(iFrame.record(Stream::kEvent), triggerInfo);
   v[k_axial] = triggerInfo->axial();
   v[k_stereo] = triggerInfo->stereo();
   v[k_cblo] = triggerInfo->cblo();
   v[k_cbmd] = triggerInfo->cbmd();

   m_ntuple->fill(v);
   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
TriggerOnlyProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
TriggerOnlyProc::endRun( Frame& iFrame )         // anal4 equiv.
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
