// -*- C++ -*-
//
// Package:     LumiRunCheck
// Module:      LumiRunCheck
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri Nov 12 16:40:44 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "LumiRunCheck/LumiRunCheck.h"
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
#include "BeamSpot/BeamSpot.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "EventProperties/EventProperties.h"


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
static const char* const kFacilityString = "Processor.LumiRunCheck" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
LumiRunCheck::LumiRunCheck( void )               // anal1
   : Processor( "LumiRunCheck" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &LumiRunCheck::event,    Stream::kEvent );
   //bind( &LumiRunCheck::beginRun, Stream::kBeginRun );
   //bind( &LumiRunCheck::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

   m_run = 0;
}

LumiRunCheck::~LumiRunCheck()                    // anal5
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
LumiRunCheck::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

   cout << "GREPME runs = {};" << endl;
   m_run = 0;
}

// -------------------- terminate method ----------------------------
void
LumiRunCheck::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)

   spill();
}


// ---------------- standard place to book histograms ---------------
void
LumiRunCheck::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_run = 0;
}

void
LumiRunCheck::spill()
{
   cout << "GREPME runs = Append[runs, " << m_run << "];" << endl;
   cout << "GREPME numer[" << m_run << "] = {" << m_numer[0];
   for (int i = 1;  i < 200;  i++) cout << ", " << m_numer[i];
   cout << "};" << endl;
   cout << "GREPME denom[" << m_run << "] = {" << m_denom[0];
   for (int i = 1;  i < 200;  i++) cout << ", " << m_denom[i];
   cout << "};" << endl;
   cout << "GREPME thetaphi[" << m_run << "] = {" << endl;
   for (int i = 0;  i < 10;  i++) {
      cout << "GREPME     {" << m_thetaphi[i][0];
      for (int j = 1;  j < 10;  j++) cout << ", " << m_thetaphi[i][j];
      if (i == 9) cout << "}" << endl;
      else cout << "}," << endl;
   }
   cout << "GREPME };" << endl;
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
LumiRunCheck::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);
   if (head->run() != m_run) {
      if (m_run != 0) spill();
      m_run = head->run();

      for (int i = 0;  i < 200;  i++) m_numer[i] = 0;
      for (int i = 0;  i < 200;  i++) m_denom[i] = 0;
      for (int i = 0;  i < 10;  i++)
	 for (int j = 0;  j < 10;  j++) m_thetaphi[i][j] = 0;
   }

   FAItem<TriggerL1Data> l1trig;
   extract(iFrame.record(Stream::kEvent), l1trig);
   if (!l1trig.valid()) return ActionBase::kFailed;

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator showers_end = showers.end();

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();
   FATable<NavTrack>::const_iterator track1 = tracks_end;
   FATable<NavTrack>::const_iterator track2 = tracks_end;

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   if (l1trig->isTwoTrack()           &&
       props->nbChargedTracks() == 2  &&
       props->netCharge() == 0          ) {

      double p1 = props->firstLargestPTrack() / eBeam->value();
      double p2 = props->secondLargestPTrack() / eBeam->value();

      double pmiss = -1.;
      if (props->firstTrackIdentifier() != 0) {
	 FATable<NavTrack>::const_iterator track_iter = tracks.find(props->firstTrackIdentifier());
	 if (track_iter != tracks_end) track1 = track_iter;
      }
      if (props->secondTrackIdentifier() != 0) {
	 FATable<NavTrack>::const_iterator track_iter = tracks.find(props->secondTrackIdentifier());
	 if (track_iter != tracks_end) track2 = track_iter;
      }
      if (track1 != tracks_end  &&  track2 != tracks_end) {
	 pmiss = (track1->pionFit()->momentum() + track2->pionFit()->momentum()).mag() / eBeam->value();
      }

      if (pmiss < 0.2  &&  abs(2 - p1 - p2 - pmiss) < 0.2) {
	 double s1costh = -1.5;
	 double s2costh = -1.5;
	 FATable<NavShower>::const_iterator showers_end = showers.end();
	 if (props->firstShowerIdentifier() != 0.) {
	    FATable<NavShower>::const_iterator shower_iter = showers.find(props->firstShowerIdentifier());
	    if (shower_iter != showers_end) {
	       s1costh = cos(shower_iter->attributes().theta());
	    }
	 }
	 if (props->secondShowerIdentifier() != 0.) {
	    FATable<NavShower>::const_iterator shower_iter = showers.find(props->secondShowerIdentifier());
	    if (shower_iter != showers_end) {
	       s2costh = cos(shower_iter->attributes().theta());
	    }
	 }

	 if (abs(s1costh) < 0.8  &&  abs(s2costh) < 0.8) {
	    double thetadiff = abs(s1costh - s2costh) / 2.;

	    int thetadiff_bin = int(thetadiff * 200./0.8);
	    if (thetadiff_bin < 200) {
	       m_denom[thetadiff_bin]++;
	       if (l1trig->isBarrelBhabha()) m_numer[thetadiff_bin]++;
	    }
	 } // shower angles within range
      } // pmiss and energy constraint okay
   } // TwoTrack, number of quality tracks == 2, q == 0


   if (tracks.size() == 0) {
      if (props->firstShowerIdentifier() != 0.) {
	 FATable<NavShower>::const_iterator shower_iter = showers.find(props->firstShowerIdentifier());
	 if (shower_iter != showers_end) {
	    double costheta = cos(shower_iter->attributes().theta());
	    double phi = shower_iter->attributes().phi();
	    if (costheta >= 0.) {
	       int theta_bin = int(costheta * 10./1.);
	       int phi_bin = int(phi * 10./2./M_PI);
	       if (theta_bin < 10 && phi_bin < 10)
		  m_thetaphi[theta_bin][phi_bin]++;
	    } // costheta is positive
	 } // iterator is good
      } // there was a biggest shower
   } // no tracks--- gamgam

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
LumiRunCheck::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
LumiRunCheck::endRun( Frame& iFrame )         // anal4 equiv.
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
