// -*- C++ -*-
//
// Package:     SuperCuts
// Module:      SuperCuts
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri Jan 30 13:33:33 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "SuperCuts/SuperCuts.h"
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

#include "EventProperties/EventProperties.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"



#include "CleoDB/DBEventHeader.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "Level3TagWord/Level3TagWord.h"
#include "CleoDB/DBEventHeader.h"
#include "BeamEnergy/BeamEnergy.h"
#include "MagField/MagneticField.h"
#include "CleoDB/DBTrackerValues.h"
#include "TrackRoot/TRTrack.h"
#include "TrackDelivery/TDKinematicPionFit.h"
#include "TrackRoot/TRHelixPionFit.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"
#include "C3cc/CcShowerAttributes.h"
#include "C3cc/CcEnergyHit.h"
#include "C3cc/CcConRegShowerLattice.h"
#include "C3cc/CcHitShowerLattice.h"
#include "C3cc/CcConRegAttributes.h"






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
static const char* const kFacilityString = "Processor.SuperCuts" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
SuperCuts::SuperCuts( void )               // anal1
   : Processor( "SuperCuts" )
   , m_mcrare("mcrare", this, false)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &SuperCuts::event,    Stream::kEvent );
   //bind( &SuperCuts::beginRun, Stream::kBeginRun );
   //bind( &SuperCuts::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

SuperCuts::~SuperCuts()                    // anal5
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
SuperCuts::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
SuperCuts::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
SuperCuts::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "mc",
      "rawtk", "eptk", "tmtk",
      "ccen", "visen", "acop", "ect30", "ect25", "ect20", "ect15",
      "p1", "p2", "p3", "p4",
      "d1", "d2", "d3", "d4",
      "z1", "z2", "z3", "z4",
      "t1", "t2", "t3", "t4",
      "f1", "f2", "f3", "f4",
      "me1", "me2", "me3", "me4",
      "md1", "md2", "md3", "md4",
      "e1", "e2", "e3", "e4",
      "st1", "st2", "st3", "st4",
      "p2x", "p2y", "p2z",
      "p4x", "p4y", "p4z",
      "pallx", "pally", "pallz",
      "pepx", "pepy", "pepz"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
SuperCuts::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<MCDecayTree> tree;
   extract(iFrame.record(Stream::kEvent), tree, "Generator");
   MCDecayTree::const_vIterator viter;
   MCDecayTree::const_vIterator tree_vend = tree->vEnd();

   const MCParticlePropertyStore& mcppstore =
     tree->topParticle().properties().store();
   const int ups1 = mcppstore.nameToQQId("UPS1");
   const int ups2 = mcppstore.nameToQQId("UPS2");
   const int ups3 = mcppstore.nameToQQId("UPS3");
   const int eplus = mcppstore.nameToQQId("E+");
   const int eminus = mcppstore.nameToQQId("E-");
   const int muplus = mcppstore.nameToQQId("MU+");
   const int muminus = mcppstore.nameToQQId("MU-");

   bool ll_from_1s = false;
   bool ll_from_2s = false;
   bool ll_from_3s = false;
   for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
      if (viter->parent().properties().QQId() == ups1  ||
	  viter->parent().properties().QQId() == ups2  ||
	  viter->parent().properties().QQId() == ups3    ) {

	 MCVertex::const_pIterator chiter;
	 MCVertex::const_pIterator viter_pend = viter->pEnd();
	 
	 int children = 0;
	 bool eplus_, eminus_, muplus_, muminus_;
	 eplus_ = eminus_ = muplus_ = muminus_ = false;
	 for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	    children++;
	    if (chiter->properties().QQId() == eplus) eplus_ = true;
	    if (chiter->properties().QQId() == eminus) eminus_ = true;
	    if (chiter->properties().QQId() == muplus) muplus_ = true;
	    if (chiter->properties().QQId() == muminus) muminus_ = true;
	 } // end loop over children
	 if (((eplus_ && eminus_) || (muplus_ && muminus_))  &&
	     children == 2) {
	    if (viter->parent().properties().QQId() == ups1) ll_from_1s = true;
	    else if (viter->parent().properties().QQId() == ups2) ll_from_2s = true;
	    else if (viter->parent().properties().QQId() == ups3) ll_from_3s = true;
	 } // end if we're looking at a light lepton vertex

      } // end switch parent QQId
   } // end loop over vertices
   int mc_class = 0;
   if (ll_from_1s) mc_class = 1;
   if (ll_from_2s) mc_class = 2;
   if (ll_from_3s) mc_class = 3;

   if (m_mcrare.value()) {
      if (mc_class == 0) return ActionBase::kFailed;
   }
   else {
      if (mc_class != 0) return ActionBase::kFailed;
   }

//    FAItem<DBEventHeader> test1;
//    FAItem<TriggerL1Data> test2;
//    FAItem<Level3TagWord> test3;
//    FAItem<DBEventHeader> test4;
//    FAItem<BeamEnergy> test5;
//    FAItem<MagneticField> test6;
//    FAItem<DBTrackerValues> test7;
//    FATable<TRTrack> test8;
//    FATable<TDKinematicPionFit> test9;
//    FATable<TRHelixPionFit> test10;
//    FAItem<TrackletBunchDecision> test12;
//    FATable<CcShowerAttributes> test13;
//    FATable<CcEnergyHit> test14;
//    FAItem<CcConRegShowerLattice> test15;
//    FAItem<CcHitShowerLattice> test16;
//    FATable<CcConRegAttributes> test17;
//    FAItem<EventProperties> test18;

//    extract(iFrame.record(Stream::kEvent), test1);
//    extract(iFrame.record(Stream::kEvent), test2);
//    extract(iFrame.record(Stream::kEvent), test3);
//    extract(iFrame.record(Stream::kEvent), test4);
//    extract(iFrame.record(Stream::kStartRun), test5);
//    extract(iFrame.record(Stream::kStartRun), test6);
//    extract(iFrame.record(Stream::kEvent), test7);
//    extract(iFrame.record(Stream::kEvent), test8);
//    extract(iFrame.record(Stream::kEvent), test9);
//    extract(iFrame.record(Stream::kEvent), test10);
//    extract(iFrame.record(Stream::kEvent), test12);
//    extract(iFrame.record(Stream::kEvent), test13);
//    extract(iFrame.record(Stream::kEvent), test14);
//    extract(iFrame.record(Stream::kEvent), test15);
//    extract(iFrame.record(Stream::kEvent), test16);
//    extract(iFrame.record(Stream::kEvent), test17);
//    extract(iFrame.record(Stream::kEvent), test18);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);
   
   FAItem<BeamEnergy> beamEnergy;
   extract(iFrame.record(Stream::kStartRun), beamEnergy);

   FAItem<MagneticField> magField;
   extract(iFrame.record(Stream::kStartRun), magField);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator track_iter = tracks.begin();
   FATable<NavTrack>::const_iterator track_end = tracks.end();
   
   FATable<NavTrack> trkman_tracks;
   extract(iFrame.record(Stream::kEvent), trkman_tracks, "TrkmanApproved");

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator shower_iter = showers.begin();
   FATable<NavShower>::const_iterator shower_end = showers.end();
   
   HepVector3D pall = HepVector3D(0., 0., 0.);
   FATable<NavTrack>::const_iterator track1 = track_end;
   FATable<NavTrack>::const_iterator track2 = track_end;
   FATable<NavTrack>::const_iterator track3 = track_end;
   FATable<NavTrack>::const_iterator track4 = track_end;
   double p1, p2, p3, p4;  p1 = p2 = p3 = p4 = 0.;
   for (; track_iter != track_end;  ++track_iter) {
      pall += track_iter->pionFit()->momentum();

      double pthis = track_iter->pionFit()->momentum().mag();
      if (pthis > p1) {
	 track4 = track3;        p4 = p3;
	 track3 = track2;        p3 = p2;
	 track2 = track1;        p2 = p1;
	 track1 = track_iter;    p1 = pthis;
      }
      else if (pthis > p2) {
	 track4 = track3;        p4 = p3;
	 track3 = track2;        p3 = p2;
	 track2 = track_iter;    p2 = pthis;
      }	 
      else if (pthis > p3) {
	 track4 = track3;        p4 = p3;
	 track3 = track_iter;    p3 = pthis;
      }
      else if (pthis > p4) {
	 track4 = track_iter;    p4 = pthis;
      }
   }
   HepVector3D ptwo = (track1 != track_end  &&  track2 != track_end ?
		       track1->pionFit()->momentum() + track2->pionFit()->momentum() :
		       HepVector3D(1000., 1000., 1000.));
   HepVector3D pfour = (track1 != track_end  &&  track2 != track_end  &&
			track3 != track_end  &&  track4 != track_end     ?
			track1->pionFit()->momentum() + track2->pionFit()->momentum() +
			track3->pionFit()->momentum() + track4->pionFit()->momentum()   :
			HepVector3D(1000., 1000., 1000.));

   FATable<NavShower>::const_iterator shower1 = shower_end;
   FATable<NavShower>::const_iterator shower2 = shower_end;
   FATable<NavShower>::const_iterator shower3 = shower_end;
   FATable<NavShower>::const_iterator shower4 = shower_end;
   double e1, e2, e3, e4;  e1 = e2 = e3 = e4 = 0.;
   double energy_outside30, energy_outside25, energy_outside20, energy_outside15;
   energy_outside30 = energy_outside25 = energy_outside20 = energy_outside15 = 0.;
   for (; shower_iter != shower_end;  ++shower_iter) {
      if (!shower_iter->attributes().hot()) {
	 double ethis = shower_iter->attributes().energy();
	 if (ethis > e1) {
	    shower4 = shower3;        e4 = e3;
	    shower3 = shower2;        e3 = e2;
	    shower2 = shower1;        e2 = e1;
	    shower1 = shower_iter;    e1 = ethis;
	 }
	 else if (ethis > e2) {
	    shower4 = shower3;        e4 = e3;
	    shower3 = shower2;        e3 = e2;
	    shower2 = shower_iter;    e2 = ethis;
	 }	 
	 else if (ethis > e3) {
	    shower4 = shower3;        e4 = e3;
	    shower3 = shower_iter;    e3 = ethis;
	 }
	 else if (ethis > e4) {
	    shower4 = shower_iter;    e4 = ethis;
	 }

	 double cotthis = 1./tan(shower_iter->attributes().theta());
	 if (fabs(cotthis) > 3.0) {
	    energy_outside30 += ethis;
	 }
	 else if (fabs(cotthis) > 2.5) {
	    energy_outside25 += ethis;
	 }
	 else if (fabs(cotthis) > 2.0) {
	    energy_outside20 += ethis;
	 }
	 else if (fabs(cotthis) > 1.5) {
	    energy_outside15 += ethis;
	 }
      } // end if hot shower
   }

   float v[kNumEntries];
   v[kMC] = mc_class;
   v[kRawTk] = tracks.size();
   v[kEPTk] = props->nbChargedTracks();
   v[kTMTk] = trkman_tracks.size();
   v[kCCEn] = props->ccTotalEnergy();
   v[kVisEn] = props->chargedEnergy() + props->neutralEnergy();
   v[kACop] = props->acoplanarity() / ((M_PI/180.) * (5.29/beamEnergy->value()) * fabs(magField->BField().mag()/15.));
   v[kECt30] = energy_outside30;
   v[kECt25] = energy_outside25;
   v[kECt20] = energy_outside20;
   v[kECt15] = energy_outside15;
   v[kP1] = p1;
   v[kP2] = p2;
   v[kP3] = p3;
   v[kP4] = p4;
   v[kD1] = (track1 != track_end ? track1->pionHelix()->d0() : 1000.);
   v[kD2] = (track2 != track_end ? track2->pionHelix()->d0() : 1000.);
   v[kD3] = (track3 != track_end ? track3->pionHelix()->d0() : 1000.);
   v[kD4] = (track4 != track_end ? track4->pionHelix()->d0() : 1000.);
   v[kZ1] = (track1 != track_end ? track1->pionHelix()->z0() : 1000.);
   v[kZ2] = (track2 != track_end ? track2->pionHelix()->z0() : 1000.);
   v[kZ3] = (track3 != track_end ? track3->pionHelix()->z0() : 1000.);
   v[kZ4] = (track4 != track_end ? track4->pionHelix()->z0() : 1000.);
   v[kT1] = (track1 != track_end ? track1->pionHelix()->cotTheta() : 1000.);
   v[kT2] = (track2 != track_end ? track2->pionHelix()->cotTheta() : 1000.);
   v[kT3] = (track3 != track_end ? track3->pionHelix()->cotTheta() : 1000.);
   v[kT4] = (track4 != track_end ? track4->pionHelix()->cotTheta() : 1000.);
   v[kF1] = (track1 != track_end ? track1->pionHelix()->phi0() : 1000.);
   v[kF2] = (track2 != track_end ? track2->pionHelix()->phi0() : 1000.);
   v[kF3] = (track3 != track_end ? track3->pionHelix()->phi0() : 1000.);
   v[kF4] = (track4 != track_end ? track4->pionHelix()->phi0() : 1000.);
   v[kME1] = (track1 != track_end                &&
	      track1->trackShowerMatch().valid()    ?
	      track1->trackShowerMatch()->matchedEnergy() : 1000.);
   v[kME2] = (track2 != track_end                &&
	      track2->trackShowerMatch().valid()    ?
	      track2->trackShowerMatch()->matchedEnergy() : 1000.);
   v[kME3] = (track3 != track_end                &&
	      track3->trackShowerMatch().valid()    ?
	      track3->trackShowerMatch()->matchedEnergy() : 1000.);
   v[kME4] = (track4 != track_end                &&
	      track4->trackShowerMatch().valid()    ?
	      track4->trackShowerMatch()->matchedEnergy() : 1000.);
   v[kMD1] = (track1 != track_end                &&
	      track1->trackShowerMatch().valid()    ?
	      track1->trackShowerMatch()->distance() : 1000.);
   v[kMD2] = (track2 != track_end                &&
	      track2->trackShowerMatch().valid()    ?
	      track2->trackShowerMatch()->distance() : 1000.);
   v[kMD3] = (track3 != track_end                &&
	      track3->trackShowerMatch().valid()    ?
	      track3->trackShowerMatch()->distance() : 1000.);
   v[kMD4] = (track4 != track_end                &&
	      track4->trackShowerMatch().valid()    ?
	      track4->trackShowerMatch()->distance() : 1000.);
   v[kE1] = e1;
   v[kE2] = e2;
   v[kE3] = e3;
   v[kE4] = e4;
   v[kShT1] = (shower1 != shower_end ? shower1->attributes().theta() : 1000.);
   v[kShT2] = (shower2 != shower_end ? shower2->attributes().theta() : 1000.);
   v[kShT3] = (shower3 != shower_end ? shower3->attributes().theta() : 1000.);
   v[kShT4] = (shower4 != shower_end ? shower4->attributes().theta() : 1000.);
   v[kP2x] = ptwo.x();
   v[kP2y] = ptwo.y();
   v[kP2z] = ptwo.z();
   v[kP4x] = pfour.x();
   v[kP4y] = pfour.y();
   v[kP4z] = pfour.z();
   v[kPAllx] = pall.x();
   v[kPAlly] = pall.y();
   v[kPAllz] = pall.z();
   v[kPEPx] = props->totalMomentumVect().x();
   v[kPEPy] = props->totalMomentumVect().y();
   v[kPEPz] = props->totalMomentumVect().z();

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
SuperCuts::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
SuperCuts::endRun( Frame& iFrame )         // anal4 equiv.
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
