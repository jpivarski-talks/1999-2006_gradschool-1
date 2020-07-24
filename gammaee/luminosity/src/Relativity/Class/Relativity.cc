// -*- C++ -*-
//
// Package:     Relativity
// Module:      Relativity
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Mar 22 14:51:54 EST 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Relativity/Relativity.h"
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
#include "TrackDelivery/TDKinematicFit.h"
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "EventProperties/EventProperties.h"
#include "Level4Proc/Level4Decision.h"
#include "BeamEnergy/BeamEnergy.h"
#include "CleoDB/DBEventHeader.h"

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
static const char* const kFacilityString = "Processor.Relativity" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Relativity::Relativity( void )               // anal1
   : Processor( "Relativity" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Relativity::event,    Stream::kEvent );
   //bind( &Relativity::beginRun, Stream::kBeginRun );
   //bind( &Relativity::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

   m_run = 0;
   m_event = 0;
   m_gamgams = 0;
   m_bhabhas = 0;
   for (int i = 0;  i < 64;  i++) {
      m_phi1[i] = 0;
      m_phi2[i] = 0;
      m_phi3[i] = 0;
      m_phi4[i] = 0;
      m_phi5[i] = 0;
   }
   for (int i = 0;  i < 100;  i++)
      for (int j = 0;  j < 64;  j++) {
	 m_numer[i][j] = 0;
	 m_denom[i][j] = 0;
      }
   m_numer_region = 0;
   m_denom_region = 0;
}

Relativity::~Relativity()                    // anal5
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
Relativity::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Relativity::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)

   print();
}


// ---------------- standard place to book histograms ---------------
void
Relativity::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Relativity::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<TriggerL1Data> l1trig;
   extract(iFrame.record(Stream::kEvent), l1trig);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FAItem<Level4Decision> l4dec;
   extract(iFrame.record(Stream::kEvent), l4dec);

   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);

   if (m_run == 0) m_run = head->run();
   if (head->run() != m_run) {
      print();

      m_run = head->run();
      m_event = 0;
      m_gamgams = 0;
      m_bhabhas = 0;
      for (int i = 0;  i < 64;  i++) {
	 m_phi1[i] = 0;
	 m_phi2[i] = 0;
	 m_phi3[i] = 0;
	 m_phi4[i] = 0;
	 m_phi5[i] = 0;
      }
      for (int i = 0;  i < 100;  i++) {
	 for (int j = 0;  j < 64;  j++) {
	    m_numer[i][j] = 0;
	    m_denom[i][j] = 0;
	 }
      }
      m_numer_region = 0;
      m_denom_region = 0;
   }

   m_event++;

   FATable<NavShower>::const_iterator one = showers.find(props->firstShowerIdentifier());
   FATable<NavShower>::const_iterator two = showers.find(props->secondShowerIdentifier());
   if (l1trig->isBarrelBhabha()                              &&
       l4dec->decision() > 0                                 &&
       props->nbChargedTracks() < 2                          &&
       props->secondLargestEShower() / eBeam->value() > 0.4  &&
       one != showers.end()  &&  two != showers.end()) {
      double sh1phi = one->attributes().phi();
      double sh2phi = two->attributes().phi();
      double sh1cos = cos(one->attributes().theta());
      double sh2cos = cos(two->attributes().theta());
      if (abs(sin(sh1phi-sh2phi)) < 0.05     &&
	  abs(sh1cos+sh2cos) < 0.025         &&
	  0.45 < abs(sh1cos-sh2cos)/2.       &&
                 abs(sh1cos-sh2cos)/2. < 0.7   ) {
	 // it's a gamgam!
	 m_gamgams++;

	 int index = floor(64./2./M_PI*(atan2(cos(sh1phi+sh2phi),sin(sh1phi+sh2phi))+M_PI));

	 if (index < 64) {
	    if (abs(sh1cos-sh2cos)/2. < 0.50) {
	       m_phi1[index]++;
	    }
	    else if (abs(sh1cos-sh2cos)/2. < 0.55) {
	       m_phi2[index]++;
	    }
	    else if (abs(sh1cos-sh2cos)/2. < 0.60) {
	       m_phi3[index]++;
	    }
	    else if (abs(sh1cos-sh2cos)/2. < 0.65) {
	       m_phi4[index]++;
	    }
	    else {
	       m_phi5[index]++;
	    }
	 }
      }
   }

   FATable<NavTrack>::const_iterator ONE = tracks.find(props->firstTrackIdentifier());
   FATable<NavTrack>::const_iterator TWO = tracks.find(props->secondTrackIdentifier());
   if (l1trig->isElTrack()                                   &&
       l4dec->decision() > 0                                 &&
       props->nbChargedTracks() > 1                          &&
       props->secondLargestEShower() / eBeam->value() > 0.4  &&
       props->secondLargestPTrack() / eBeam->value() > 0.75  &&
       ONE != tracks.end()  &&  TWO != tracks.end()             ) {
      double tr1phi = ONE->pionHelix()->phi0();
      double tr2phi = TWO->pionHelix()->phi0();
      double tr1cos = ONE->pionHelix()->cotTheta() / sqrt(1. + sqr(ONE->pionHelix()->cotTheta()));
      double tr2cos = TWO->pionHelix()->cotTheta() / sqrt(1. + sqr(TWO->pionHelix()->cotTheta()));
      if (abs(tr1cos+tr2cos) < 0.025    &&
	  abs(sin(tr1phi-tr2phi)) < 0.3   ) {
	 // it's a bhabha!
	 if (abs(tr1cos-tr2cos)/2. < 0.7) m_bhabhas++;

	 int index = floor(100.*abs(tr1cos-tr2cos)/2.);
	 int index_phi = floor(64./2./M_PI*(atan2(cos(tr1phi+tr2phi),sin(tr1phi+tr2phi))+M_PI));

	 if (index < 100) {
	    m_denom[index][index_phi]++;
	    if (l1trig->isBarrelBhabha()) m_numer[index][index_phi]++;
	 }
	 
	 if (0.45 < abs(tr1cos-tr2cos)/2.       &&
                    abs(tr1cos-tr2cos)/2. < 0.7   ) {
	    m_denom_region++;
	    if (l1trig->isBarrelBhabha()) m_numer_region++;
	 }
      }
   }

   return ActionBase::kPassed;
}

void
Relativity::print()
{
// class RunRecord:
//   def __init__(self, events = 0, gamgams = 0, bhabhas = 0, phi1 = [], phi2 = [], phi3 = [], phi4 = [], phi5 = [], numer = [], denom = [], numer_region = 0, denom_region = 0):
//     self.events = events
//     self.gamgams = gamgams
//     self.bhabhas = bhabhas
//     self.phi1 = phi1
//     self.phi2 = phi2
//     self.phi3 = phi3
//     self.phi4 = phi4
//     self.phi5 = phi5
//     self.numer = numer
//     self.denom = denom
//     self.numer_region = numer_region
//     self.denom_region = denom_region
// run = {}

   cout << "PYTHON run[" << m_run << "] = RunRecord("
	<< "events = " << m_event << ", "
	<< "gamgams = " << m_gamgams << ", "
	<< "bhabhas = " << m_bhabhas << ", "
	<< "phi1 = [";
   for (int i = 0;  i < 64;  i++) cout << m_phi1[i] << ", ";
   cout << "], "
	<< "phi2 = [";
   for (int i = 0;  i < 64;  i++) cout << m_phi2[i] << ", ";
   cout << "], "
	<< "phi3 = [";
   for (int i = 0;  i < 64;  i++) cout << m_phi3[i] << ", ";
   cout << "], "
	<< "phi4 = [";
   for (int i = 0;  i < 64;  i++) cout << m_phi4[i] << ", ";
   cout << "], "
	<< "phi5 = [";
   for (int i = 0;  i < 64;  i++) cout << m_phi5[i] << ", ";
   cout << "], "
	<< "numer = [";
   for (int i = 0;  i < 100;  i++) {
      cout << "[";
      for (int j = 0;  j < 64;  j++)
	 cout << m_numer[i][j] << ", ";
      cout << "], ";
   }
   cout << "], "
	<< "denom = [";
   for (int i = 0;  i < 100;  i++) {
      cout << "[";
      for (int j = 0;  j < 64;  j++)
	 cout << m_denom[i][j] << ", ";
      cout << "], ";
   }
   cout << "], "
	<< "numer_region = " << m_numer_region << ", "
	<< "denom_region = " << m_denom_region << ")" << endl;
}

/*
ActionBase::ActionResult
Relativity::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Relativity::endRun( Frame& iFrame )         // anal4 equiv.
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
