// -*- C++ -*-
//
// Package:     PlotTrigger
// Module:      PlotTrigger
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Apr  5 14:28:54 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "PlotTrigger/PlotTrigger.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "TriggerInfoProd/TriggerInfo.h"
#include "TriggerL1Data/TriggerL1Data.h"


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
static const char* const kFacilityString = "Processor.PlotTrigger" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
PlotTrigger::PlotTrigger( void )               // anal1
   : Processor( "PlotTrigger" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &PlotTrigger::event,    Stream::kEvent );
   //bind( &PlotTrigger::beginRun, Stream::kBeginRun );
   //bind( &PlotTrigger::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

PlotTrigger::~PlotTrigger()                    // anal5
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
PlotTrigger::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
PlotTrigger::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
PlotTrigger::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   m_axial = iHistoManager.histogram(
      "Axial Tracks", 16, -0.5, 15.5);
   m_stereo = iHistoManager.histogram(
      "Stereo Tracks", 16, -0.5, 15.5);
   m_cblo = iHistoManager.histogram(
      "CBLO", 8, -0.5, 7.5);
   m_cbmd = iHistoManager.histogram(
      "CBMD", 8, -0.5, 7.5);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
PlotTrigger::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<TriggerL1Data> triggerDecision;
   extract(iFrame.record(Stream::kEvent), triggerDecision);
   
   FAItem<TriggerInfo> triggerInfo;
   extract(iFrame.record(Stream::kEvent), triggerInfo);
   
   if (triggerDecision->isHadron()  ||
       triggerDecision->isRadTau()  ||
       triggerDecision->isElTrack()   ) {
      m_axial->fill(triggerInfo->axial());
      m_stereo->fill(triggerInfo->stereo());
      m_cblo->fill(triggerInfo->cblo());
      m_cbmd->fill(triggerInfo->cbmd());
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
PlotTrigger::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
PlotTrigger::endRun( Frame& iFrame )         // anal4 equiv.
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
