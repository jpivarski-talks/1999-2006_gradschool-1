// -*- C++ -*-
//
// Package:     HitEfficiency
// Module:      HitEfficiency
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Sep 20 12:49:11 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "HitEfficiency/HitEfficiency.h"
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
#include "Navigation/NavTkShMatch.h"
#include "BeamEnergy/BeamEnergy.h"
#include "CleoDB/DBEventHeader.h"
#include "TriggerData/TriggerData.h"
#include "CalibratedData/CalibratedDRHit.h"
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
static const char* const kFacilityString = "Processor.HitEfficiency" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
HitEfficiency::HitEfficiency( void )               // anal1
   : Processor( "HitEfficiency" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &HitEfficiency::event,    Stream::kEvent );
   //bind( &HitEfficiency::beginRun, Stream::kBeginRun );
   //bind( &HitEfficiency::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

   for (int i = 0;  i <= 30;  i++)
      for (int j = 0;  j <= 30;  j++) {
	 m_axial[i][j] = 0;
	 m_stereo[i][j] = 0;
      }
}

HitEfficiency::~HitEfficiency()                    // anal5
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
HitEfficiency::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

   for (int i = 0;  i <= 30;  i++)
      for (int j = 0;  j <= 30;  j++) {
	 m_axial[i][j] = 0;
	 m_stereo[i][j] = 0;
      }
}

// -------------------- terminate method ----------------------------
void
HitEfficiency::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
HitEfficiency::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

//    m_lit = iHistoManager.profile("axMap lit versus quality tracks", 19, -0.5, 18.5, -1., 113., HIHistProf::kErrorOnMean);
//    m_blobs = iHistoManager.profile("axMap blobs versus quality tracks", 19, -0.5, 18.5, -1., 113., HIHistProf::kErrorOnMean);
//    m_axial = iHistoManager.profile("AXIAL tracks versus quality tracks", 19, -0.5, 18.5, -1., 113., HIHistProf::kErrorOnMean);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
HitEfficiency::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<TriggerData> trigdat;
   extract(iFrame.record(Stream::kEvent), trigdat);

//    UInt32 axMap[TriggerData::kNumberOfAxialKeyWires];
//    trigdat->getAxialTrackMap(axMap);
//    int prevt = -2;
//    int lit = 0;
//    int blobs = 0;
//    for (int t = 0;  t < 112;  t++) {
//       if (axMap[t] != 0) lit++;
//       if (axMap[t] != 0  &&  t - prevt > 1) {
// 	 blobs++;
// 	 prevt = t;
//       }
//    }

   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);
   int axial = 0;
   int stereo = 0;
   if (head->monteCarlo()) {
      for (int b = 0;  b < 4;  b++) {
	 if (trigdat->getAxTrackCount(b) > axial)
	    axial = trigdat->getAxTrackCount(b);
	 if (trigdat->getLoTrackCount(b) + trigdat->getHiTrackCount(b) > stereo)
	    stereo = trigdat->getLoTrackCount(b) + trigdat->getHiTrackCount(b);
      }
   }
   else {
      axial = trigdat->getAxTrackCount(trigdat->getLumiL1AcceptBucket());
      stereo = trigdat->getLoTrackCount(trigdat->getLumiL1AcceptBucket()) +
	 trigdat->getHiTrackCount(trigdat->getLumiL1AcceptBucket());
   }

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);
   int tracks = props->nbChargedTracks();

   if (tracks <= 30  &&  axial <= 30)
      m_axial[tracks][axial]++;
   if (tracks <= 30  &&  stereo <= 30)
      m_stereo[axial][stereo]++;

   if (head->number() < 10  ||  head->number() % 100 == 0) {
      cout << endl;
      cout << "(* Rows are quality tracks, columns are AXIAL (both start with zero): *)" << endl;
      for (int i = 0;  i <= 30;  i++) {
	 if (i == 0) cout << "{"; else cout << " ";
	 cout << "{";
	 for (int j = 0;  j <= 30;  j++) {
	    cout << m_axial[i][j];
	    if (j != 30) cout << ", ";
	 }
	 cout << "}";
	 if (i == 30) cout << "}"; else cout << ",";
	 cout << endl;
      }

      cout << endl;
      cout << "(* Rows are AXIAL, columns are STEREO (both start with zero): *)" << endl;
      for (int i = 0;  i <= 30;  i++) {
	 if (i == 0) cout << "{"; else cout << " ";
	 cout << "{";
	 for (int j = 0;  j <= 30;  j++) {
	    cout << m_stereo[i][j];
	    if (j != 30) cout << ", ";
	 }
	 cout << "}";
	 if (i == 30) cout << "}"; else cout << ",";
	 cout << endl;
      }

      cout << endl;
   }

//    m_lit->fill(tracks, lit);
//    m_blobs->fill(tracks, blobs);
//    m_axial->fill(tracks, axial);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator track_iter = tracks.begin();
   FATable<NavTrack>::const_iterator track_end = tracks.end();

   for (; track_iter != track_end;  ++track_iter) {
      if (!(!track_iter->pionQuality()->fitAbort()  &&
	    !track_iter->seedQuality()->originUsed()  &&
	    track_iter->pionFit()->momentum().perp() > 1./6.  &&
	    track_iter->pionQuality()->numberHitsExpected() > 0  &&
	    track_iter->pionQuality()->ratioNumberHitsToExpected() > 0.4  &&
	    abs(track_iter->pionHelix()->cotTheta()/sqrt(1. + sqr(track_iter->pionHelix()->cotTheta()))) < 0.93  &&
	    track_iter->pionQuality()->degreesOfFreedom() > 0 &&
	    track_iter->pionQuality()->chiSquare() / double(track_iter->pionQuality()->degreesOfFreedom()) < 3.5  &&
	    abs(track_iter->pionHelix()->d0()))) continue;

      cout << "hitlist:";
      const NavTrack::DRHitTable* myHitTable = track_iter->seedDRHits();
      for (int i = 0;  i < myHitTable->size();  i++) {
	 if ((*myHitTable)[i] == NULL  ||  (*myHitTable)[i]->layer() > 16) continue;

	 cout << " " << (*myHitTable)[i]->layer();
	 if (track_iter->pionQuality()->isLayerHit(TRSubdetectorLists::kDR3Axial, (*myHitTable)[i]->layer()))
	    cout << "*";
      }
      cout << endl;
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
HitEfficiency::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
HitEfficiency::endRun( Frame& iFrame )         // anal4 equiv.
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
