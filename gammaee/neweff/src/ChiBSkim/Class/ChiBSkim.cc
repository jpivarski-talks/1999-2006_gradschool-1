// -*- C++ -*-
//
// Package:     ChiBSkim
// Module:      ChiBSkim
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Feb 16 18:51:23 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ChiBSkim/ChiBSkim.h"
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
#include "Navigation/NavTkShMatch.h"
#include "C3cc/CcShowerAttributes.h"
#include "BeamEnergy/BeamEnergy.h"
#include "BeamSpot/BeamSpot.h"
#include "EventProperties/EventProperties.h"
#include "EventType/EventType.h"

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
static const char* const kFacilityString = "Processor.ChiBSkim" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
ChiBSkim::ChiBSkim( void )               // anal1
   : Processor( "ChiBSkim" )
   , m_cut("cut", this, true)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &ChiBSkim::event,    Stream::kEvent );
   //bind( &ChiBSkim::beginRun, Stream::kBeginRun );
   //bind( &ChiBSkim::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

ChiBSkim::~ChiBSkim()                    // anal5
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
ChiBSkim::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
ChiBSkim::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
ChiBSkim::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "ntk", "epntk",
      "tr1", "tr2", "eop1", "eop2",
      "mass1s",
      "d1", "d2", "z1", "z2",
      "costh1", "costh2", "phi1", "phi2",
      "ph1", "ph2",
      "masschib",
      "costh3", "costh4", "phi3", "phi4",
      "allp", "allpt", "alle",
      "type"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
ChiBSkim::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   const bool cut = m_cut.value();

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator track_iter = tracks.begin();
   FATable<NavTrack>::const_iterator track_end = tracks.end();
   if (cut && tracks.size() < 2) return ActionBase::kFailed;

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator shower_iter = showers.begin();
   FATable<NavShower>::const_iterator shower_end = showers.end();
   if (cut && showers.size() < 4) return ActionBase::kFailed;

   FAItem<BeamEnergy> beamEnergy;
   extract(iFrame.record(Stream::kStartRun), beamEnergy);

   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<EventType> type;
   extract(iFrame.record(Stream::kEvent), type);

   double tr1 = 0.;
   double tr2 = 0.;
   FATable<NavTrack>::const_iterator track_iter1 = track_end;
   FATable<NavTrack>::const_iterator track_iter2 = track_end;
   for (; track_iter != track_end;  ++track_iter) {
      double p = track_iter->pionFit()->momentum().mag();
      if (p > tr1) {
	 tr2 = tr1;
	 tr1 = p;

	 track_iter2 = track_iter1;
	 track_iter1 = track_iter;
      }
      else if (p > tr2) {
	 tr2 = p;

	 track_iter2 = track_iter;
      }
   } // end track loop
   if (track_iter1 != track_end) tr1 *= (track_iter1->pionHelix()->curvature() > 0. ? 1. : -1);
   if (track_iter2 != track_end) tr2 *= (track_iter2->pionHelix()->curvature() > 0. ? 1. : -1);

   if (cut && (tr1 * tr2 >= 0.)) return ActionBase::kFailed;

   if (cut && fabs(tr1) > 1.05 * beamEnergy->value()) return ActionBase::kFailed;
   if (cut && fabs(tr1) < 0.75 * beamEnergy->value()) return ActionBase::kFailed;
   if (cut && fabs(tr2) < 0.75 * beamEnergy->value()) return ActionBase::kFailed;

   double eOverP1 = -1.;
   double eOverP2 = -1.;
   NavTkShMatch::ShowerIdList track_showers;
   if (track_iter1 != track_end  &&  track_iter1->trackShowerMatch().valid()) {
      eOverP1 = track_iter1->trackShowerMatch()->eOverP();

      const NavTkShMatch::ShowerIdList sublist = track_iter1->trackShowerMatch()->showerIds();
      NavTkShMatch::ShowerIdList::const_iterator sublist_iter = sublist.begin();
      NavTkShMatch::ShowerIdList::const_iterator sublist_end = sublist.end();
      for (; sublist_iter != sublist_end;  ++sublist_iter) track_showers.push_back(*sublist_iter);
   }
   if (track_iter2 != track_end  &&  track_iter2->trackShowerMatch().valid()) {
      eOverP2 = track_iter2->trackShowerMatch()->eOverP();

      const NavTkShMatch::ShowerIdList sublist = track_iter2->trackShowerMatch()->showerIds();
      NavTkShMatch::ShowerIdList::const_iterator sublist_iter = sublist.begin();
      NavTkShMatch::ShowerIdList::const_iterator sublist_end = sublist.end();
      for (; sublist_iter != sublist_end;  ++sublist_iter) track_showers.push_back(*sublist_iter);
   }
   if (track_iter1 != track_end  &&  track_iter1->bremShowers().valid()) {
      FATable<NavShower>::const_iterator brem_iter = track_iter1->bremShowers().begin();
      FATable<NavShower>::const_iterator brem_end = track_iter1->bremShowers().end();
      for (; brem_iter != brem_end;  ++brem_iter) track_showers.push_back(brem_iter->identifier());
   }
   if (track_iter2 != track_end  &&  track_iter2->bremShowers().valid()) {
      FATable<NavShower>::const_iterator brem_iter = track_iter2->bremShowers().begin();
      FATable<NavShower>::const_iterator brem_end = track_iter2->bremShowers().end();
      for (; brem_iter != brem_end;  ++brem_iter) track_showers.push_back(brem_iter->identifier());
   }

   if (cut && (eOverP1 == -1. || eOverP1 > 0.3)) return ActionBase::kFailed;
   if (cut && (eOverP2 == -1. || eOverP2 > 0.3)) return ActionBase::kFailed;

   double mass1s = 0.;
   if (track_iter1 != track_end  &&  track_iter2 != track_end) {
      HepVector3D pv1 = track_iter1->pionFit()->momentum();
      HepVector3D pv2 = track_iter2->pionFit()->momentum();

      mass1s = sqr(pv1.mag() + pv2.mag()) - (pv1 + pv2).mag2();
      if (mass1s > 0.) mass1s = sqrt(mass1s);
   }

   if (cut && (mass1s < 9.200 || mass1s > 9.700)) return ActionBase::kFailed;

   double d1 = 1.;
   double d2 = 1.;
   double z1 = 1.;
   double z2 = 1.;
   if (track_iter1 != track_end) {
      KTHelix tr1(*track_iter1->pionHelix());
      double dist;
      tr1.moveToReferencePoint(spot->center(), dist, KTMoveControl::kDirectionEither);
      d1 = tr1.d0();
      z1 = tr1.z0();
   }
   if (track_iter2 != track_end) {
      KTHelix tr2(*track_iter2->pionHelix());
      double dist;
      tr2.moveToReferencePoint(spot->center(), dist, KTMoveControl::kDirectionEither);
      d2 = tr2.d0();
      z2 = tr2.z0();
   }
			       
   if (cut && fabs(d1) > 0.002) return ActionBase::kFailed;
   if (cut && fabs(d2) > 0.002) return ActionBase::kFailed;
   if (cut && fabs(z1) > 0.05) return ActionBase::kFailed;
   if (cut && fabs(z2) > 0.05) return ActionBase::kFailed;

   double costh1 = 2.;
   double costh2 = 2.;
   if (track_iter1 != track_end) costh1 = track_iter1->pionHelix()->cotTheta() /
				    (sqr(track_iter1->pionHelix()->cotTheta()) + 1.);
   if (track_iter2 != track_end) costh2 = track_iter2->pionHelix()->cotTheta() /
				    (sqr(track_iter2->pionHelix()->cotTheta()) + 1.);

   double phi1 = -2.*M_PI;
   double phi2 = -2.*M_PI;
   if (track_iter1 != track_end) phi1 = track_iter1->pionHelix()->phi0();
   if (track_iter2 != track_end) phi2 = track_iter2->pionHelix()->phi0();

   double ph1 = 0.;
   double ph2 = 0.;
   FATable<NavShower>::const_iterator photon_iter1 = shower_end;
   FATable<NavShower>::const_iterator photon_iter2 = shower_end;
   for (; shower_iter != shower_end;  ++shower_iter) {
      if (!shower_iter->attributes().hot()) {
	 bool in_list = false;
	 NavTkShMatch::ShowerIdList::const_iterator trackshowers_iter = track_showers.begin();
	 NavTkShMatch::ShowerIdList::const_iterator trackshowers_end = track_showers.end();
	 for (; trackshowers_iter != trackshowers_end  &&  !in_list;  ++trackshowers_iter) {
	    if (shower_iter->identifier() == *trackshowers_iter) in_list = true;
	 }
	 if (!in_list) {
	    double e = shower_iter->attributes().energy();
	    if (e > ph1) {
	       ph2 = ph1;
	       ph1 = e;

	       photon_iter2 = photon_iter1;
	       photon_iter1 = shower_iter;
	    }
	    else if (e > ph2) {
	       ph2 = e;

	       photon_iter2 = shower_iter;
	    }
	 } // end if not in track_showers list
      } // end if not hot
   } // end loop over all showers

   if (cut && (ph1 < 0.275  ||  ph1 > 0.500)) return ActionBase::kFailed;
   if (cut && (ph2 < 0.075  ||  ph2 > 0.225)) return ActionBase::kFailed;

   double masschib = 0.;
   if (track_iter1 != track_end  &&  track_iter2 != track_end  &&  photon_iter1 != shower_end) {
      HepVector3D pv1 = track_iter1->pionFit()->momentum();
      HepVector3D pv2 = track_iter2->pionFit()->momentum();
      HepVector3D pv3 = photon_iter1->attributes().momentum();

      masschib = sqr(pv1.mag() + pv2.mag() + pv3.mag()) - (pv1 + pv2 + pv3).mag2();
      if (masschib > 0.) masschib = sqrt(masschib);
   }

   if (cut && (masschib < 9.000 || masschib > 10.500)) return ActionBase::kFailed;

   double costh3 = 2.;
   double costh4 = 2.;
   if (photon_iter1 != shower_end) costh3 = cos(photon_iter1->attributes().theta());
   if (photon_iter2 != shower_end) costh4 = cos(photon_iter2->attributes().theta());

   double phi3 = -2.*M_PI;
   double phi4 = -2.*M_PI;
   if (photon_iter1 != shower_end) phi3 = photon_iter1->attributes().phi();
   if (photon_iter2 != shower_end) phi4 = photon_iter2->attributes().phi();

   double all_momentum = -1.;
   double all_transverse = -1.;
   double all_energy = -1.;
   if (track_iter1 != track_end  &&  track_iter2 != track_end  &&
       photon_iter1 != shower_end  &&  photon_iter2 != shower_end) {
      HepVector3D pv1 = track_iter1->pionFit()->momentum();
      HepVector3D pv2 = track_iter2->pionFit()->momentum();
      HepVector3D pv3 = photon_iter1->attributes().momentum();
      HepVector3D pv4 = photon_iter2->attributes().momentum();

      HepVector3D total = pv1 + pv2 + pv3 + pv4;
      all_momentum = total.mag();
      all_transverse = total.perp();
      all_energy = pv1.mag() + pv2.mag() + pv3.mag() + pv4.mag();
   }

   float v[kNumEntries];
   v[kntk] = tracks.size();
   v[kepntk] = props->nbChargedTracks();
   v[ktr1] = tr1;
   v[ktr2] = tr2;
   v[keop1] = eOverP1;
   v[keop2] = eOverP2;
   v[kmass1s] = mass1s;
   v[kd1] = d1;
   v[kd2] = d2;
   v[kz1] = z1;
   v[kz2] = z2;
   v[kcosth1] = costh1;
   v[kcosth2] = costh2;
   v[kphi1] = phi1;
   v[kphi2] = phi2;
   v[kph1] = ph1;
   v[kph2] = ph2;
   v[kmasschib] = masschib;
   v[kcosth3] = costh3;
   v[kcosth4] = costh4;
   v[kphi3] = phi3;
   v[kphi4] = phi4;
   v[kallp] = all_momentum;
   v[kallpt] = all_transverse;
   v[kalle] = all_energy;
   v[ktype] = ((type->radLepAll() ? 1. : 0.) +
	       (type->bhaGamAll() ? 2. : 0.));
   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
ChiBSkim::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
ChiBSkim::endRun( Frame& iFrame )         // anal4 equiv.
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
