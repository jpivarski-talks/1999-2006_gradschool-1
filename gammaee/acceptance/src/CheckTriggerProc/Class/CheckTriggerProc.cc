// -*- C++ -*-
//
// Package:     CheckTriggerProc
// Module:      CheckTriggerProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Apr  5 13:04:19 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "CheckTriggerProc/CheckTriggerProc.h"
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
static const char* const kFacilityString = "Processor.CheckTriggerProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
CheckTriggerProc::CheckTriggerProc( void )               // anal1
   : Processor( "CheckTriggerProc" )
   , m_total(0)
   , m_invalidTriggerInfo(0)
   , m_invalidTriggerL1Data(0)
   , m_badbucket(0)
   , m_hadrons(0)
   , m_wronghadrons(0)
   , m_nonhadrons(0)
   , m_wrongnonhadrons(0)
   , m_radtaus(0)
   , m_wrongradtaus(0)
   , m_nonradtaus(0)
   , m_wrongnonradtaus(0)
   , m_eltracks(0)
   , m_wrongeltracks(0)
   , m_noneltracks(0)
   , m_wrongnoneltracks(0)
   , m_twotracks(0)
   , m_wrongtwotracks(0)
   , m_nontwotracks(0)
   , m_wrongnontwotracks(0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &CheckTriggerProc::event,    Stream::kEvent );
   //bind( &CheckTriggerProc::beginRun, Stream::kBeginRun );
   //bind( &CheckTriggerProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

CheckTriggerProc::~CheckTriggerProc()                    // anal5
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
CheckTriggerProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
CheckTriggerProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)

   report(SYSTEM, kFacilityString)
      << "Invalid TriggerInfo = " << m_invalidTriggerInfo << " / " << m_total << endl;
   report(SYSTEM, kFacilityString)
      << "Invalid TriggerL1Data = " << m_invalidTriggerL1Data << " / " << m_total << endl;
   report(SYSTEM, kFacilityString)
      << "Bad Bucket = " << m_badbucket << " / " << m_total << endl;

   report(SYSTEM, kFacilityString)
      << "Wrongly called Hadron = " << m_wronghadrons << " / " << m_hadrons << endl;
   report(SYSTEM, kFacilityString)
      << "Wrongly called NonHadron = " << m_wrongnonhadrons << " / " << m_nonhadrons << endl;

   report(SYSTEM, kFacilityString)
      << "Wrongly called Radtau = " << m_wrongradtaus << " / " << m_radtaus << endl;
   report(SYSTEM, kFacilityString)
      << "Wrongly called NonRadtau = " << m_wrongnonradtaus << " / " << m_nonradtaus << endl;

   report(SYSTEM, kFacilityString)
      << "Wrongly called Eltrack = " << m_wrongeltracks << " / " << m_eltracks << endl;
   report(SYSTEM, kFacilityString)
      << "Wrongly called NonEltrack = " << m_wrongnoneltracks << " / " << m_noneltracks << endl;

   report(SYSTEM, kFacilityString)
      << "Wrongly called Twotrack = " << m_wrongtwotracks << " / " << m_twotracks << endl;
   report(SYSTEM, kFacilityString)
      << "Wrongly called NonTwotrack = " << m_wrongnontwotracks << " / " << m_nontwotracks << endl;
}


// ---------------- standard place to book histograms ---------------
void
CheckTriggerProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "axial", "stereo", "cblo", "cbmd",
      "hadron", "radtau", "eltrack", "twotrack"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
CheckTriggerProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   m_total++;

   FAItem<TriggerInfo> triggerInfo;
   extract(iFrame.record(Stream::kEvent), triggerInfo);
   if (!triggerInfo.valid()) {
      m_invalidTriggerInfo++;

      report(SYSTEM, kFacilityString)
	 << "TriggerInfo not valid (" << m_invalidTriggerInfo
	 << "/" << m_total << ")." << endl;
      return ActionBase::kPassed;
   }

   FAItem<TriggerL1Data> triggerDecision;
   extract(iFrame.record(Stream::kEvent), triggerDecision);
   if (!triggerDecision.valid()) {
      m_invalidTriggerL1Data++;

      report(SYSTEM, kFacilityString)
	 << "TriggerL1Data not valid (" << m_invalidTriggerL1Data
	 << "/" << m_total << ")." << endl;
      return ActionBase::kPassed;
   }

   if (triggerInfo->axial() == -1) {
      m_badbucket++;

      report(SYSTEM, kFacilityString)
	 << "No known bucket (" << m_badbucket << "/" << m_total << ")." << endl;
      return ActionBase::kPassed;
   }

   float v[kNumEntries];
   v[k_axial] = triggerInfo->axial();
   v[k_stereo] = triggerInfo->stereo();
   v[k_cblo] = triggerInfo->cblo();
   v[k_cbmd] = triggerInfo->cbmd();
   v[k_hadron] = triggerDecision->isHadron();
   v[k_radtau] = triggerDecision->isRadTau();
   v[k_eltrack] = triggerDecision->isElTrack();
   v[k_twotrack] = triggerDecision->isTwoTrack();
   m_ntuple->fill(v);

   bool myhadron(triggerInfo->axial() > 2  &&
		 triggerInfo->cblo() > 0     );

   bool myradtau(triggerInfo->stereo() > 1    &&
		 (triggerInfo->cblo() > 1  ||
		  triggerInfo->cbmd() > 0       ));

   bool myeltrack(triggerInfo->axial() > 0  &&
		  triggerInfo->cbmd() > 0     );

   bool mytwotrack(triggerInfo->axial() > 1);

   if (triggerDecision->isHadron()) {
      m_hadrons++;

      if (!myhadron) {
	 m_wronghadrons++;

	 report(SYSTEM, kFacilityString)
	    << "Hadron with " << triggerInfo->axial() << " axial tracks and "
	    << triggerInfo->cblo() << " CBLOs (" << m_wronghadrons
	    << "/" << m_hadrons << ")." << endl;
      }
   }
   else {
      m_nonhadrons++;

      if (myhadron) {
	 m_wrongnonhadrons++;

	 report(SYSTEM, kFacilityString)
	    << "NonHadron with " << triggerInfo->axial() << " axial tracks and "
	    << triggerInfo->cblo() << " CBLOs (" << m_wrongnonhadrons
	    << "/" << m_nonhadrons << ")." << endl;
      }
   }

   if (triggerDecision->isRadTau()) {
      m_radtaus++;

      if (!myradtau) {
	 m_wrongradtaus++;

	 report(SYSTEM, kFacilityString)
	    << "Radtau with " << triggerInfo->stereo() << " stereo tracks and "
	    << triggerInfo->cblo() << " CBLOs and " << triggerInfo->cbmd()
	    << " CBMDs (" << m_wrongradtaus << "/" << m_radtaus << ")." << endl;
      }
   }
   else {
      m_nonradtaus++;

      if (myradtau) {
	 m_wrongnonradtaus++;

	 report(SYSTEM, kFacilityString)
	    << "NonRadtau with " << triggerInfo->stereo() << " stereo tracks and "
	    << triggerInfo->cblo() << " CBLOs and " << triggerInfo->cbmd()
	    << " CBMDs (" << m_wrongnonradtaus << "/" << m_nonradtaus << ")." << endl;
      }
   }

   if (triggerDecision->isElTrack()) {
      m_eltracks++;

      if (!myeltrack) {
	 m_wrongeltracks++;

	 report(SYSTEM, kFacilityString)
	    << "Eltrack with " << triggerInfo->axial() << " axial tracks and "
	    << triggerInfo->cbmd() << " CBMDs (" << m_wrongeltracks
	    << "/" << m_eltracks << ")." << endl;
      }
   }
   else {
      m_noneltracks++;

      if (myeltrack) {
	 m_wrongnoneltracks++;

	 report(SYSTEM, kFacilityString)
	    << "NonEltrack with " << triggerInfo->axial() << " axial tracks and "
	    << triggerInfo->cbmd() << " CBMDs (" << m_wrongnoneltracks
	    << "/" << m_noneltracks << ")." << endl;
      }
   }

   if (triggerDecision->isTwoTrack()) {
      m_twotracks++;

      if (!mytwotrack) {
	 m_wrongtwotracks++;

	 report(SYSTEM, kFacilityString)
	    << "Twotrack with " << triggerInfo->axial() << " axial tracks ("
	    << m_wrongtwotracks << "/" << m_twotracks << ")." << endl;
      }
   }
   else {
      m_nontwotracks++;

      if (mytwotrack) {
	 m_wrongnontwotracks++;

	 if (m_wrongnontwotracks % 1000 == 0) {
	    report(SYSTEM, kFacilityString)
	       << "NonTwotrack with " << triggerInfo->axial() << " axial tracks ("
	       << m_wrongnontwotracks << "/" << m_nontwotracks << ")." << endl;
	 }
      }
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
CheckTriggerProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
CheckTriggerProc::endRun( Frame& iFrame )         // anal4 equiv.
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
