// -*- C++ -*-
//
// Package:     Lumi
// Module:      Lumi
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Nov  9 15:11:23 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Lumi/Lumi.h"
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

#include "TrackRoot/TRSeedTrackQuality.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "EventProperties/EventProperties.h"
#include "Level4Proc/Level4Decision.h"
#include "Level3TagWord/Level3TagWord.h"
#include "BeamEnergy/BeamEnergy.h"
#include "BeamSpot/BeamSpot.h"
#include "TrackRoot/TRSubdetectorLists.h"
#include "DedxInfo/DedxInfo.h"
#include "Navigation/NavRich.h"
#include "Navigation/NavTkShMatch.h"
#include "CleoDB/DBEventHeader.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

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
static const char* const kFacilityString = "Processor.Lumi" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Lumi::Lumi( void )               // anal1
   : Processor( "Lumi" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Lumi::event,    Stream::kEvent );
   //bind( &Lumi::beginRun, Stream::kBeginRun );
   //bind( &Lumi::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Lumi::~Lumi()                    // anal5
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
Lumi::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Lumi::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
Lumi::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "l1tt", "l1rt", "l1el", "l1bb", "l1eb",
//      "l3acc", "l3class", "l4dec",
      "rawtk", "ntk", "ebeam", "e1", "e2", "p1", "p2", "ccen", "neue", "chen",
      "pos1", "pos2",
      "s1costh", "s2costh", "s1phi", "s2phi",
      "t1costh", "t2costh", "t1phi", "t2phi",
//      "expect", "allhit", "chi2", "dof",
      "d0close", "z0close", "pmiss",
//      "axlay", "stlay",
//        "esig1", "esig2", "musig1", "musig2",
//        "ell1", "ell2", "mull1", "mull2",
      "s1e925", "s2e925", "mccosth", "s1wide", "s2wide"
   };
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Lumi::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   float v[kNumEntries];
   v[k_l1tt] = -1;
   v[k_l1rt] = -1;
   v[k_l1el] = -1;
   v[k_l1bb] = -1;
   v[k_l1eb] = -1;
//    v[k_l3acc] = -1;
//    v[k_l3class] = -1;
//    v[k_l4dec] = -1;
   v[k_rawtk] = -1;
   v[k_ntk] = -1;
   v[k_ebeam] = -1.;
   v[k_e1] = -0.1;
   v[k_e2] = -0.1;
   v[k_p1] = -0.1;
   v[k_p2] = -0.1;
   v[k_ccen] = -0.1;
   v[k_neue] = -0.1;
   v[k_chen] = -0.1;
   v[k_pos1] = -1;
   v[k_pos2] = -1;
   v[k_s1costh] = -1.5;
   v[k_s2costh] = -1.5;
   v[k_s1phi] = -4.;
   v[k_s2phi] = -4.;
   v[k_t1costh] = -1.5;
   v[k_t2costh] = -1.5;
   v[k_t1phi] = -4.;
   v[k_t2phi] = -4.;
//    v[k_expect] = 0;
//    v[k_allhit] = 0;
//    v[k_chi2] = 0.;
//    v[k_dof] = 0;
   v[k_d0close] = -1.;
   v[k_z0close] = -1.;
   v[k_pmiss] = -1.;
//    v[k_axlay] = 0;
//    v[k_stlay] = 0;
//     v[k_esig1] = -100.;
//     v[k_esig2] = -100.;
//     v[k_musig1] = -100.;
//     v[k_musig2] = -100.;
//     v[k_ell1] = -100000.;
//     v[k_ell2] = -100000.;
//     v[k_mull1] = -100000.;
//     v[k_mull2] = -100000.;
   v[k_s1e925] = -1.;
   v[k_s2e925] = -1.;
   v[k_mccosth] = -1.;
   v[k_s1wide] = -1.;
   v[k_s2wide] = -1.;

   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);
   if (head->monteCarlo()) {
      FAItem<MCDecayTree> decayTree;
      extract(iFrame.record(Stream::kEvent), decayTree, "Generator");
      MCDecayTree::const_vIterator vertex_end = decayTree->vEnd();

      double big1 = 0.;
      double big1costheta = 0.;
      double big2 = 0.;
      double big2costheta = 0.;

      const string gamm = "GAMM";
      const string eplus = "E+";
      const string eminus = "E-";

      MCDecayTree::const_pIterator particle_end = decayTree->pEnd();
      for (MCDecayTree::const_pIterator particle_iter = decayTree->pBegin();
	   particle_iter != particle_end;
	   ++particle_iter) {
	 if (particle_iter->properties().name() == gamm   ||
	     particle_iter->properties().name() == eplus  ||
	     particle_iter->properties().name() == eminus   ) {
	    if (particle_iter->energy() > big1) {
	       big2 = big1;
	       big2costheta = big1costheta;

	       big1 = particle_iter->energy();
	       big1costheta = particle_iter->momentum().cosTheta();
	    }
	    else if (particle_iter->energy() > big2) {
	       big2 = particle_iter->energy();
	       big2costheta = particle_iter->momentum().cosTheta();
	    }
	 } // end if gamma
      } // end loop over particles

      if (big1 > 0.  &&  big2 > 0.) v[k_mccosth] = abs(big1costheta - big2costheta)/2.;
   } // end if this is Monte Carlo

   FAItem<TriggerL1Data> l1trig;
   extract(iFrame.record(Stream::kEvent), l1trig);

   v[k_l1tt] = l1trig->isTwoTrack();
   v[k_l1rt] = l1trig->isRadTau();
   v[k_l1el] = l1trig->isElTrack();
   v[k_l1bb] = l1trig->isBarrelBhabha();
   v[k_l1eb] = l1trig->isEndcapBhabha();

//    FAItem<Level3TagWord> l3tag;
//    extract(iFrame.record(Stream::kEvent), l3tag);

//    v[k_l3acc] = l3tag->acceptCode();
//    v[k_l3class] = l3tag->classCode();

//    FAItem<Level4Decision> l4dec;
//    extract(iFrame.record(Stream::kEvent), l4dec);

//    v[k_l4dec] = l4dec->decision();

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);

   v[k_rawtk] = tracks.size();

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   v[k_ntk] = props->nbChargedTracks();
   v[k_ebeam] = eBeam->value();
   v[k_e1] = props->firstLargestEShower() / eBeam->value();
   v[k_e2] = props->secondLargestEShower() / eBeam->value();
   v[k_p1] = props->firstLargestPTrack() / eBeam->value();
   v[k_p2] = props->secondLargestPTrack() / eBeam->value();
   v[k_ccen] = props->ccTotalEnergy() / 2. / eBeam->value();
   v[k_neue] = props->neutralEnergy() / 2. / eBeam->value();
   v[k_chen] = props->chargedEnergy() / 2. / eBeam->value();

   FATable<NavShower>::const_iterator showers_end = showers.end();
   if (props->firstShowerIdentifier() != 0.) {
      FATable<NavShower>::const_iterator shower_iter = showers.find(props->firstShowerIdentifier());
      if (shower_iter != showers_end) {
	 v[k_s1costh] = cos(shower_iter->attributes().theta());
	 v[k_s1phi] = shower_iter->attributes().phi();
	 v[k_s1e925] = shower_iter->attributes().e9oe25();
	 v[k_s1wide] = shower_iter->attributes().width();
      }
   }
   if (props->secondShowerIdentifier() != 0.) {
      FATable<NavShower>::const_iterator shower_iter = showers.find(props->secondShowerIdentifier());
      if (shower_iter != showers_end) {
	 v[k_s2costh] = cos(shower_iter->attributes().theta());
	 v[k_s2phi] = shower_iter->attributes().phi();
	 v[k_s2e925] = shower_iter->attributes().e9oe25();
	 v[k_s2wide] = shower_iter->attributes().width();
      }
   }

   FATable<NavTrack>::const_iterator tracks_end = tracks.end();
   FATable<NavTrack>::const_iterator track1 = tracks_end;
   FATable<NavTrack>::const_iterator track2 = tracks_end;

   if (props->firstTrackIdentifier() != 0) {
      FATable<NavTrack>::const_iterator track_iter = tracks.find(props->firstTrackIdentifier());
      if (track_iter != tracks_end) {
	 v[k_t1costh] = track_iter->pionHelix()->cotTheta() / sqrt(sqr(track_iter->pionHelix()->cotTheta()) + 1.);
	 v[k_t1phi] = track_iter->pionHelix()->phi0();
	 if (track_iter->pionHelix()->curvature() > 0.)
	    v[k_pos1] = 1.;
	 else
	    v[k_pos1] = 0.;
//  	 if (track_iter->dedxInfo().valid()) {
//  	    v[k_esig1] = track_iter->dedxInfo()->eSigma();
//  	    v[k_musig1] = track_iter->dedxInfo()->muSigma();
//  	 }
//  	 if (track_iter->richInfo().valid()) {
//  	    v[k_ell1] = track_iter->richInfo()->electronLogLikelihood();
//  	    v[k_mull1] = track_iter->richInfo()->muonLogLikelihood();
//  	 }
	 track1 = track_iter;
      }
   }
   if (props->secondTrackIdentifier() != 0) {
      FATable<NavTrack>::const_iterator track_iter = tracks.find(props->secondTrackIdentifier());
      if (track_iter != tracks_end) {
	 v[k_t2costh] = track_iter->pionHelix()->cotTheta() / sqrt(sqr(track_iter->pionHelix()->cotTheta()) + 1.);
	 v[k_t2phi] = track_iter->pionHelix()->phi0();
	 if (track_iter->pionHelix()->curvature() > 0.)
	    v[k_pos2] = 1.;
	 else
	    v[k_pos2] = 0.;
//  	 if (track_iter->dedxInfo().valid()) {
//  	    v[k_esig2] = track_iter->dedxInfo()->eSigma();
//  	    v[k_musig2] = track_iter->dedxInfo()->muSigma();
//  	 }
//  	 if (track_iter->richInfo().valid()) {
//  	    v[k_ell2] = track_iter->richInfo()->electronLogLikelihood();
//  	    v[k_mull2] = track_iter->richInfo()->muonLogLikelihood();
//  	 }
	 track2 = track_iter;
      }
   }

   for(FATable<NavTrack>::const_iterator track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
//       int expect = 0;
//       int allhit = 0;
//       double chi2 = 0;
//       int dof = 0;
//       if (track_iter->seedQuality()->numberHitsExpected() > 0) expect = track_iter->seedQuality()->numberHitsExpected();
//       if (track_iter->seedQuality()->numberLayers() > 0)       allhit = track_iter->seedQuality()->numberLayers();
//       if (track_iter->seedQuality()->chiSquare() > 0)          chi2 = track_iter->seedQuality()->chiSquare();
//       if (track_iter->seedQuality()->degreesOfFreedom() > 0)   dof = track_iter->seedQuality()->degreesOfFreedom();
//       v[k_expect] += expect;
//       v[k_allhit] += allhit;
//       v[k_chi2] += chi2;
//       v[k_dof] += dof;

      KTHelix movetrack(*track_iter->pionHelix());
      double distance_moved;
      movetrack.moveToReferencePoint(spot->center(),
				     distance_moved,
				     KTMoveControl::kDirectionEither);
      if (fabs(movetrack.d0()) < fabs(v[k_d0close])) v[k_d0close] = movetrack.d0();
      if (fabs(movetrack.z0()) < fabs(v[k_z0close])) v[k_z0close] = movetrack.z0();
   }

   if (track1 != tracks_end  &&  track2 != tracks_end) {
      v[k_pmiss] = (track1->pionFit()->momentum() + track2->pionFit()->momentum()).mag() / eBeam->value();
   }

//    bool axmap[16];
//    bool stmap[16];
//    for (int i = 1;  i <= 16;  i++) axmap[i-1] = false;
//    for (int i = 1;  i <= 31;  i++) stmap[i-1] = false;
//    for(FATable<NavTrack>::const_iterator track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {   
//       for (int i = 1;  i <= 16;  i++)
// 	 axmap[i-1] = axmap[i-1]  ||  track_iter->pionQuality()->isLayerHit(TRSubdetectorLists::kDR3Axial, i);
//       for (int i = 1;  i <= 31;  i++)
// 	 stmap[i-1] = stmap[i-1]  ||  track_iter->pionQuality()->isLayerHit(TRSubdetectorLists::kDR3Stereo, i);
//    }
//    for (int i = 1;  i <= 16;  i++) if (axmap[i-1]) v[k_axlay]++;
//    for (int i = 1;  i <= 31;  i++) if (stmap[i-1]) v[k_stlay]++;

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
Lumi::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Lumi::endRun( Frame& iFrame )         // anal4 equiv.
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
