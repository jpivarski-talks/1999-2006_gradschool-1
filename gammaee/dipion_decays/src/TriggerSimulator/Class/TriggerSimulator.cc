// -*- C++ -*-
//
// Package:     TriggerSimulator
// Module:      TriggerSimulator
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Wed Apr 23 13:51:01 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TriggerSimulator/TriggerSimulator.h"
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

#include "BeamEnergy/BeamEnergy.h"
#include "C3cc/CcEventSummary.h"
#include "EventProperties/EventProperties.h"
#include "Level4Proc/Level4Decision.h"
#include "EventType/EventType.h"
#include "Navigation/NavTkShMatch.h"

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
static const char* const kFacilityString = "Processor.TriggerSimulator" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TriggerSimulator::TriggerSimulator( void )               // anal1
   : Processor( "TriggerSimulator" )
   , m_total(0)
   , m_passMe(0)
   , m_passOfficial(0)
   , m_disagreements(0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TriggerSimulator::event,    Stream::kEvent );
   //bind( &TriggerSimulator::beginRun, Stream::kBeginRun );
   //bind( &TriggerSimulator::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

TriggerSimulator::~TriggerSimulator()                    // anal5
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
TriggerSimulator::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TriggerSimulator::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
   printout(SYSTEM);
}


// ---------------- standard place to book histograms ---------------
void
TriggerSimulator::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TriggerSimulator::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator track_end = tracks.end();

   int goodTracksL4(0);

   int goodTracksET(0);
   double chargedEnergyET(0.);

   for ( FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	 track_iter != track_end;
	 ++track_iter ) {

      // This is for Level 4
      FAItem<TRSeedTrack> seedTrack = track_iter->seedTrack();
      FAItem<TRSeedTrackQuality> seedQuality = track_iter->seedQuality();
      if ( !seedQuality->originUsed()                              &&
	   seedQuality->numberHitsExpected() > 0                   &&
	   (double(seedQuality->numberHits()) /
	    double(seedQuality->numberHitsExpected())) > 0.4       &&
	   sqrt(1. - 1./(1 + sqr(seedTrack->cotTheta()))) <= 0.93  &&
	   (seedQuality->chiSquare() /
	    double(seedQuality->degreesOfFreedom())) < 20.         &&
	   fabs(seedTrack->d0()) < 0.025                           &&
	   fabs(seedTrack->z0()) < 0.15                               ) {
	 goodTracksL4++;
      } // end this is for level 4

      // This is for eventType selection
      FAItem<TDKinematicFit> pionFit(track_iter->pionFit());
      FAItem<TRHelixFit> pionHelix(track_iter->pionHelix());
      FAItem<TRTrackFitQuality> pionQuality(track_iter->pionQuality());

      report(DEBUG, kFacilityString) 
	 << "pionQuality->fit() " << pionQuality->fit() << endl
	 << "pionQuality->fitAbort() " << pionQuality->fitAbort() << endl
	 << "(pionQuality->degreesOfFreedom() > 0 ? pionQuality->chiSquare() / double(pionQuality->degreesOfFreedom()) : 0.) "
	 << (pionQuality->degreesOfFreedom() > 0 ?
	     pionQuality->chiSquare() / double(pionQuality->degreesOfFreedom()) : 0.) << endl
	 << "seedQuality->numberHitsExpected() " << seedQuality->numberHitsExpected() << endl
	 << "(double(seedQuality->numberLayers()) / double(seedQuality->numberHitsExpected())) "
	 << (double(seedQuality->numberLayers()) /
	     double(seedQuality->numberHitsExpected())) << endl
	 << "fabs(pionHelix->d0()) " << fabs(pionHelix->d0()) << endl
	 << "fabs(pionHelix->z0()) " << fabs(pionHelix->z0()) << endl
	 << "pionFit->momentum().mag() " << pionFit->momentum().mag() << endl
	 << "fabs(pionHelix->cotTheta()) " << fabs(pionHelix->cotTheta()) << endl
	 << "sqrt(fabs(pionHelix->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) "
	 << sqrt(fabs(pionHelix->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) << endl
	 << "sqrt(fabs(pionHelix->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) "
	 << sqrt(fabs(pionHelix->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) << endl;

      if ( pionQuality->fit()                                                                  &&
	   ! pionQuality->fitAbort()                                                           &&
	   (pionQuality->degreesOfFreedom() > 0 ?
	    pionQuality->chiSquare() / double(pionQuality->degreesOfFreedom()) : 0.) < 100.    &&
	   seedQuality->numberHitsExpected() > 0                                               &&
	   (double(seedQuality->numberLayers()) /
	    double(seedQuality->numberHitsExpected())) > 0.5                                   &&
	   (double(seedQuality->numberLayers()) /
	    double(seedQuality->numberHitsExpected())) < 1.2                                   &&
	   fabs(pionHelix->d0()) < 0.03                                                        &&
	   fabs(pionHelix->z0()) < 0.18                                                        &&
	   pionFit->momentum().mag() > 0.01 * eBeam->value()                                   &&
	   pionFit->momentum().mag() < 1.50 * eBeam->value()                                   &&
	   fabs(pionHelix->cotTheta()) < 3.0424                                                &&
	   sqrt(fabs(pionHelix->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) < 0.5  &&
	   sqrt(fabs(pionHelix->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) < 0.25                ) {
	 goodTracksET++;
	 chargedEnergyET += pionFit->energy();
      } // end this is for eventType selection

   } // end loop over tracks

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator shower_end = showers.end();

   double totalCCEnergyL3(0.);
   int significantShowersL3(0);
   double biggestShowerL3(0.);
   double zPosCCEnergyL3(0.);
   double zNegCCEnergyL3(0.);

   double totalCCEnergyET(0.);
   double biggestShowerET(0.);
   double neutralEnergyET(0.);

   for ( FATable<NavShower>::const_iterator shower_iter = showers.begin();
	 shower_iter != shower_end;
	 ++shower_iter ) {

      // This is for Level 3
      totalCCEnergyL3 += shower_iter->attributes().energy();
      if ( shower_iter->attributes().energy() > 0.100 ) {
	 significantShowersL3++;
      }
      if ( shower_iter->attributes().energy() > biggestShowerL3 ) {
	 biggestShowerL3 += shower_iter->attributes().energy();
      }
      if ( shower_iter->attributes().theta() < 95.*M_PI/180. ) {
	 zPosCCEnergyL3 += shower_iter->attributes().energy();
      }
      if ( shower_iter->attributes().theta() > 85.*M_PI/180. ) {
	 zNegCCEnergyL3 += shower_iter->attributes().energy();
      } // end this is for level 3

      // This is for eventType selection
      if ( shower_iter->attributes().energy() > 0.01 * eBeam->value()  &&
	   shower_iter->attributes().status()                            ) {
	 totalCCEnergyET += shower_iter->attributes().energy();
	 
	 if ( shower_iter->attributes().energy() > biggestShowerET ) {
	    biggestShowerET = shower_iter->attributes().energy();
	 }
	 
	 if ( shower_iter->noTrackMatch()                                              &&
	      shower_iter->noTrackMatchConReg()                                        &&
	      (! shower_iter->bremTrack().valid()                                  ||
	       ( shower_iter->bremTrack()->trackShowerMatch().valid()          &&
		 shower_iter->bremTrack()->trackShowerMatch()->eOverP() < 0.5    )   )   ) {
	    neutralEnergyET += shower_iter->attributes().energy();
	 }
      } // end this is for eventType selection

   } // end loop over showers

   DABoolean passL3(
      (totalCCEnergyL3 > 1.75  &&  (zPosCCEnergyL3 > 0.100  &&
				    zNegCCEnergyL3 > 0.100     ))  ||
      totalCCEnergyL3 > 2.25                                         );

   DABoolean passHadronLooseL3(
      significantShowersL3 >= 8                &&
      totalCCEnergyL3 > 0.3 * eBeam->value()   &&
      totalCCEnergyL3 < 1.8 * eBeam->value()   &&
      biggestShowerL3 < 0.8 * eBeam->value()   &&
      zPosCCEnergyL3 > 0.100 * eBeam->value()  &&
      zNegCCEnergyL3 > 0.100 * eBeam->value()     );

   DABoolean passL4( goodTracksL4 >= 2 );
      
   DABoolean passEventSelection(
      goodTracksET > 2                                               &&
      (chargedEnergyET + neutralEnergyET) > 0.2 * 2.*eBeam->value()  &&
      (goodTracksET > 4                                      ||
       (totalCCEnergyET > 0.15 * 2.*eBeam->value()       &&
	(totalCCEnergyET < 0.75 * 2.*eBeam->value()  ||
	 biggestShowerET < 0.75 * eBeam->value()       )   )   )       );

   FAItem<Level4Decision> l4decision;
   extract(iFrame.record(Stream::kEvent), l4decision);

   FAItem<EventType> eventType;
   extract(iFrame.record(Stream::kEvent), eventType);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   m_total++;
   if ( ((passL3  &&  passHadronLooseL3)  ||  passL4)  &&  passEventSelection ) {
      m_passMe++;
   }
   if ( (l4decision->decision() == Level4Decision::kKeepLevel3Garbage  ||
	 l4decision->decision() == Level4Decision::kLevel3AutoAccept   ||
	 l4decision->decision() == Level4Decision::kLevel4Keep           )  &&
	eventType->hadron()                                                    ) {
      m_passOfficial++;
   }
   if ( m_total % 100000 == 0 ) {
      printout(NOTICE);
   }
   else if ( m_total % 1000 == 0 ) {
      printout(INFO);
   }

   if ( (((passL3  &&  passHadronLooseL3)  ||  passL4)  &&  passEventSelection)  !=
	((l4decision->decision() == Level4Decision::kKeepLevel3Garbage  ||
	  l4decision->decision() == Level4Decision::kLevel3AutoAccept   ||
	  l4decision->decision() == Level4Decision::kLevel4Keep           )  &&
	 eventType->hadron()                                                    ) ) {
      m_disagreements++;

      report(SYSTEM, kFacilityString)

	 << "Disagreement!!!" << endl

	 << "I think it should have " << ((((passL3  &&  passHadronLooseL3)  ||  passL4)  &&  passEventSelection) ? "passed" : "failed")
	 << " and the official code thinks it should have " << (((l4decision->decision() == Level4Decision::kKeepLevel3Garbage  ||
								  l4decision->decision() == Level4Decision::kLevel3AutoAccept   ||
								  l4decision->decision() == Level4Decision::kLevel4Keep           )  &&
								 eventType->hadron()) ? "passed" : "failed")
	 << "." << endl

	 << "passL3 " << passL3 << " passHadronLooseL3 " << passHadronLooseL3
	 << " passL4 " << passL4 << " passEventSelection " << passEventSelection << endl

	 << "keepLevel3Garbage " << (l4decision->decision() == Level4Decision::kKeepLevel3Garbage)
	 << " level3AutoAccept " << (l4decision->decision() == Level4Decision::kLevel3AutoAccept)
	 << " level4Keep " << (l4decision->decision() == Level4Decision::kLevel4Keep)
	 << " eventType->hadron() " << eventType->hadron() << endl

	 << "significantShowersL3 (>= 8) " << significantShowersL3
	 << " totalCCEnergyL3 (0.3 - 1.8 eBeam) " << totalCCEnergyL3
	 << " biggestShowerL3 (< 0.8 eBeam) " << biggestShowerL3
	 << " zPosCCEnergyL3 (> 0.1 eBeam) " << zPosCCEnergyL3
	 << " zNegCCEnergyL3 (> 0.1 eBeam) " << zNegCCEnergyL3
	 << " eBeam " << eBeam->value() << endl

	 << "goodTracksL4 (>= 2) " << goodTracksL4 << endl

	 << "goodTracksET (> 2 or 4) " << goodTracksET
	 << " chargedEnergyET " << chargedEnergyET
	 << " neutralEnergyET (sums to 0.2*2*eBeam) " << neutralEnergyET
	 << " totalCCEnergyET ((> 0.15 or < 0.75)*2*eBeam) " << totalCCEnergyET
	 << " biggestShowerET (< 0.75*eBeam) " << biggestShowerET << endl

	 << "nbChargedTracks " << props->nbChargedTracks()
	 << " chargedEnergy " << props->chargedEnergy()
	 << " neutralEnergy " << props->neutralEnergy()
	 << " ccTotalEnergy " << props->ccTotalEnergy()
	 << " firstLargestEShower " << props->firstLargestEShower() << endl;
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
TriggerSimulator::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
TriggerSimulator::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

void
TriggerSimulator::printout(Severity severity)
{
   report(severity, kFacilityString)
      << "I pass " << m_passMe << " / " << m_total << " (" << (100. * double(m_passMe)/double(m_total))
      << "%), the official code passes " << m_passOfficial << " (" << (100. * double(m_passOfficial)/double(m_total))
      << "%).  There have been " << m_disagreements << " disagreements." << endl;
}

//
// const member functions
//

//
// static member functions
//
