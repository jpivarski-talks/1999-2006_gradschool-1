// -*- C++ -*-
//
// Package:     Convert
// Module:      Convert
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri Apr  8 15:23:53 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Convert/Convert.h"
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
#include "EventType/EventType.h"
#include "Level4Proc/Level4Decision.h"
#include "BeamEnergy/BeamEnergy.h"
#include "BeamSpot/BeamSpot.h"
#include "TrackRoot/TRSubdetectorLists.h"
#include "Navigation/NavTkShMatch.h"
#include "CleoDB/DBEventHeader.h"
#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "RandomModule/RandomGenerator.h"
#include "VXFitVeeCandidate/VXFitVeeConversion.h"
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
static const char* const kFacilityString = "Processor.Convert" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.40 2005/02/10 16:03:57 chengp Exp $";
static const char* const kTagString = "$Name: v07_02_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Convert::Convert( void )               // anal1
   : Processor( "Convert" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Convert::event,    Stream::kEvent );
   //bind( &Convert::beginRun, Stream::kBeginRun );
   //bind( &Convert::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Convert::~Convert()                    // anal5
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
Convert::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Convert::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
Convert::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   const char* label[kNumEntries] = {
      "tracks", "oldtk", "trig", "eltrack", "ebeam",
      "e1", "e1cos", "e1cot", "e1phi",
      "e2", "e2cos", "e2cot", "e2phi", "acop",
      "cnum", "cen", "cbig", "cang", "ccos", "cacop",
      "epho", "mcvx", "mcvy", "mcvz",
      "vchi2", "vx", "vy", "vz",
      "t1px", "t1py", "t1pz", "t1d0", "t1z0",
      "t2px", "t2py", "t2pz", "t2d0", "t2z0",
      "t3px", "t3py", "t3pz", "t3d0", "t3z0",
      "svrad", "svphi", "svd", "visen", "known"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Convert::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   static int runningcount;
   if (!head->monteCarlo()  &&  runningcount > 300000)
      return ActionBase::kPassed;
   if (props->firstLargestEShower() / eBeam->value() > 0.9)
      runningcount++;

   float v[kNumEntries];
   for (int i = 0;  i < kNumEntries;  i++) v[i] = -1000.;

   v[k_ebeam] = eBeam->value();

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks, "GoodThings");
   FATable<NavTrack>::const_iterator t1, t2, t3;
   t1 = t2 = t3 = tracks.end();

   for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	track_iter != tracks.end();
	++track_iter) {
      if (t1 == tracks.end()  ||
	  t1->electronFit()->momentum().mag() < track_iter->electronFit()->momentum().mag()) {
	 t3 = t2;
	 t2 = t1;
	 t1 = track_iter;
      }
      else if (t2 == tracks.end()  ||
	       t2->electronFit()->momentum().mag() < track_iter->electronFit()->momentum().mag()) {
	 t3 = t2;
	 t2 = track_iter;
      }
      else if (t3 == tracks.end()  ||
	       t3->electronFit()->momentum().mag() < track_iter->electronFit()->momentum().mag()) {
	 t3 = track_iter;
      }
   }

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers, "GoodThings");

   // Used in the 8-11 Apr ntuples, turned off 13 Apr for unbiased MC ("again")
//    if (showers.size() == 0  ||
//        showers.begin()->attributes().energy()/eBeam->value() < 0.5  ||
//        (tracks.size() > 0  &&
// 	tracks.begin()->pionFit()->momentum().mag()/eBeam->value() > 0.6))
//       return ActionBase::kFailed;

   // 14 Apr ("deeper"), I put this remarkably-similar cut back in:
//    if (showers.size() == 0  ||
//        showers.begin()->attributes().energy()/eBeam->value() < 0.5  ||
//        (t1 != tracks.end()  &&  t1->electronFit()->momentum().mag()/eBeam->value() > 0.6))
//       return ActionBase::kFailed;
   // 18 Apr: "deeper" really ought to have cut on the second-largest track
   // I'm going to try to run "deeper2" without a subcollection (equivalent to "deeper_again")
   // (but of course, "deeper_again" has a cut on p1, not p2)
   if (showers.size() == 0  ||
       showers.begin()->attributes().energy()/eBeam->value() < 0.5  ||
       (t2 != tracks.end()  &&  t2->electronFit()->momentum().mag()/eBeam->value() > 0.6))
      return ActionBase::kFailed;

   v[k_tracks] = tracks.size();

   v[k_oldtk] = props->nbChargedTracks();

   FAItem<TriggerL1Data> trigger;
   extract(iFrame.record(Stream::kEvent), trigger);

   v[k_trig] = trigger->isBarrelBhabha();
   if (head->run() > 200000) {
      const UInt32 tLine2 (trigger->getTriggerLines(TriggerL1Data::kBoard2Number));
      v[k_trig] = (trigger->isBarrelBhabha()                           ||
		   trigger->isEndcapBhabha()                           ||
// 		   ( 0 != ( tLine2 & TriggerL1Data::kNeut2bm ) )       ||
// 		   ( 0 != ( tLine2 & TriggerL1Data::kNeut1bm1em ) )    ||
// 		   ( 0 != ( tLine2 & TriggerL1Data::kNeut1bm2bl ) )    ||
// 		   ( 0 != ( tLine2 & TriggerL1Data::kNeut1bm1bl1el ) ) ||
// 		   ( 0 != ( tLine2 & TriggerL1Data::kNeut1bm1bl ) )    ||
// 		   ( 0 != ( tLine2 & TriggerL1Data::kNeut1bh1bm ) )    || 
// 		   ( 0 != ( tLine2 & TriggerL1Data::kPhotonA ) )       || 
// 		   ( 0 != ( tLine2 & TriggerL1Data::kPhotonB ) )       || 
// 		   ( 0 != ( tLine2 & TriggerL1Data::kPhotonC ) )       || 
// 		   ( 0 != ( tLine2 & TriggerL1Data::kPhotonD ) )         );
		   ( 0 != ( tLine2 & 0x40 ) )           ||
		   ( 0 != ( tLine2 & 0x80 ) )           ||
		   ( 0 != ( tLine2 & 0x100 ) )          ||
		   ( 0 != ( tLine2 & 0x200 ) )          ||
		   ( 0 != ( tLine2 & 0x400 ) )          ||
		   ( 0 != ( tLine2 & 0x800 ) )          || 
		   ( 0 != ( tLine2 & 0x100000 ) )       || 
		   ( 0 != ( tLine2 & 0x200000 ) )       || 
		   ( 0 != ( tLine2 & 0x400000 ) )       || 
		   ( 0 != ( tLine2 & 0x800000 ) )         );
   }

   v[k_eltrack] = trigger->isElTrack();

//    if (showers.size() == 0) {
//       m_ntuple->fill(v);
//       return ActionBase::kPassed;
//    }
   assert(showers.size() > 0);

   FATable<NavShower>::const_iterator s1 (showers.begin());
   const double e1   ( s1->attributes().energy()/eBeam->value() ) ;
   const Hep3Vector v1 ( s1->attributes().momentum() ) ;
   const double cos1 ( v1.cosTheta() ) ;

   v[k_e1] = e1;
   v[k_e1cos] = cos1;
   v[k_e1cot] = 1.0/tan(s1->attributes().theta());
   v[k_e1phi] = s1->attributes().phi();

   if (showers.size() > 1) {
      FATable<NavShower>::const_iterator s2 (showers.begin()+1);

      const double e2   ( s2->attributes().energy()/eBeam->value() ) ;
 
      const Hep3Vector v2 ( s2->attributes().momentum() ) ;
      const double cos2 ( v2.cosTheta() ) ;
      const double acop ( fabs( fabs( v1.phi() - v2.phi() ) - M_PI ) ) ;

      v[k_e2] = e2;
      v[k_e2cos] = cos2;
      v[k_e2cot] = 1.0/tan(s2->attributes().theta());
      v[k_e2phi] = s2->attributes().phi();
      v[k_acop] = acop;
   }

   int num_showers = 0;
   double total_energy = 0.;
   double biggest = 0.;
   double biggest_angle, biggest_cos, biggest_acop;
   for (FATable<NavShower>::const_iterator s = showers.begin();
	s != showers.end();
	++s) {
      if (s->attributes().momentum().unit().dot(v1.unit()) < -0.95) {
	 num_showers++;
	 total_energy += s->attributes().energy();
	 if (s->attributes().energy() > biggest) {
	    biggest = s->attributes().energy();
	    biggest_angle = s->attributes().momentum().unit().dot(v1.unit());
	    const Hep3Vector v2 (s->attributes().momentum());
	    biggest_cos = v2.cosTheta();
	    biggest_acop = fabs( fabs( v1.phi() - v2.phi() ) - M_PI );
	 }
      }
   }

   v[k_cnum] = num_showers;
   v[k_cen] = total_energy;
   if (v[k_cnum] > 0) {
      v[k_cbig] = biggest;
      v[k_cang] = biggest_angle;
      v[k_ccos] = biggest_cos;
      v[k_cacop] = biggest_acop;
   }

   if (head->monteCarlo()) {
      FAItem<MCDecayTree> tree;
      extract(iFrame.record(Stream::kEvent), tree);
      MCDecayTree::const_vIterator viter;
      MCDecayTree::const_vIterator tree_vend = tree->vEnd();

      const MCParticlePropertyStore& mcppstore =
	 tree->topParticle().properties().store();

      const int gamm = mcppstore.nameToQQId("GAMM");
      const int eplus = mcppstore.nameToQQId("E+");
      const int eminus = mcppstore.nameToQQId("E-");

      double epho = 0.;
      HepPoint3D where;
      for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
	 if (viter->parent().properties().QQId() == gamm  &&  viter->parent().energy() > epho) {
	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();
	    bool eplus_ = false, eminus_ = false;
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	       if (chiter->properties().QQId() == eplus) eplus_ = true;
	       if (chiter->properties().QQId() == eminus) eminus_ = true;
	    }
	    if (eplus_  &&  eminus_  &&  viter->position().unit().dot(v1.unit()) < 0.95) {
	       epho = viter->parent().energy();
	       where = viter->position();
	    }
	 }
      }

      if (epho > 0.) {
	 v[k_epho] = epho;
	 v[k_mcvx] = where.x();
	 v[k_mcvy] = where.y();
	 v[k_mcvz] = where.z();
      }
   }

   FATable<VXFitVeeConversion> vxfit;
   extract(iFrame.record(Stream::kEvent), vxfit);

   FATable<VXFitVeeConversion>::const_iterator vbestchi2 = vxfit.end();
   for (FATable<VXFitVeeConversion>::const_iterator v = vxfit.begin();
	v != vxfit.end();
	++v) {
      if (vbestchi2 == vxfit.end()  ||  vbestchi2->fitChiSquare() > v->fitChiSquare()) vbestchi2 = v;
   }
   if (vbestchi2 != vxfit.end()) {
      v[k_vchi2] = vbestchi2->fitChiSquare();
      v[k_vx] = vbestchi2->guessVertex().x();
      v[k_vy] = vbestchi2->guessVertex().y();
      v[k_vz] = vbestchi2->guessVertex().z();
   }

   if (t1 != tracks.end()) {
      v[k_t1px] = t1->electronFit()->momentum().x();
      v[k_t1py] = t1->electronFit()->momentum().y();
      v[k_t1pz] = t1->electronFit()->momentum().z();
      v[k_t1d0] = t1->pionHelix()->d0();
      v[k_t1z0] = t1->pionHelix()->z0();
   }
   if (t2 != tracks.end()) {
      v[k_t2px] = t2->electronFit()->momentum().x();
      v[k_t2py] = t2->electronFit()->momentum().y();
      v[k_t2pz] = t2->electronFit()->momentum().z();
      v[k_t2d0] = t2->pionHelix()->d0();
      v[k_t2z0] = t2->pionHelix()->z0();
   }
   if (t3 != tracks.end()) {
      v[k_t3px] = t3->electronFit()->momentum().x();
      v[k_t3py] = t3->electronFit()->momentum().y();
      v[k_t3pz] = t3->electronFit()->momentum().z();
      v[k_t3d0] = t3->pionHelix()->d0();
      v[k_t3z0] = t3->pionHelix()->z0();
   }

   if (t1 != tracks.end()  &&  t2 != tracks.end()) {
      const double epsilon = 1e-10;
      double dummy, lophi, hiphi;
      TRHelixFit h1 = *t1->electronHelix();
      TRHelixFit h2 = *t2->electronHelix();

      FAItem<BeamSpot> spot;
      extract(iFrame.record(Stream::kBeginRun), spot);

      bool broke = false;
      broke = broke || (h1.moveToReferencePoint(spot->center(), dummy, KTMoveControl::kDirectionEither) != KTMoveControl::kMoveOK);
      broke = broke || (h2.moveToReferencePoint(spot->center(), dummy, KTMoveControl::kDirectionEither) != KTMoveControl::kMoveOK);

      double hirad = 0.3;
      double lorad = abs(h1.d0());
      if (abs(h2.d0()) > lorad) lorad = abs(h2.d0());
      lorad += 0.001;

      broke = broke || (h1.moveToCylinder(spot->center(), HepVector3D(0.,0.,1.), lorad, dummy, KTMoveControl::kDirectionEither) != KTMoveControl::kMoveOK);
      broke = broke || (h2.moveToCylinder(spot->center(), HepVector3D(0.,0.,1.), lorad, dummy, KTMoveControl::kDirectionEither) != KTMoveControl::kMoveOK);
      lophi = sin(h1.phi0() - h2.phi0());

      broke = broke || (h1.moveToCylinder(spot->center(), HepVector3D(0.,0.,1.), hirad, dummy, KTMoveControl::kDirectionEither) != KTMoveControl::kMoveOK);
      broke = broke || (h2.moveToCylinder(spot->center(), HepVector3D(0.,0.,1.), hirad, dummy, KTMoveControl::kDirectionEither) != KTMoveControl::kMoveOK);
      hiphi = sin(h1.phi0() - h2.phi0());

      if (!broke  &&  lophi * hiphi < 0.) {
	 double midrad, midphi;
	 
	 while (!broke  &&  abs(lophi) > epsilon  &&  abs(hiphi) > epsilon) {
	    midrad = -lophi * (hirad - lorad)/(hiphi - lophi) + lorad;

	    broke = broke || (h1.moveToCylinder(spot->center(), HepVector3D(0.,0.,1.), midrad, dummy, KTMoveControl::kDirectionEither) != KTMoveControl::kMoveOK);
	    broke = broke || (h2.moveToCylinder(spot->center(), HepVector3D(0.,0.,1.), midrad, dummy, KTMoveControl::kDirectionEither) != KTMoveControl::kMoveOK);
	    midphi = sin(h1.phi0() - h2.phi0());

	    if (lophi * midphi >= 0.) {
	       lorad = midrad;
	       lophi = midphi;
	    }
	    if (hiphi * midphi >= 0.) {
	       hirad = midrad;
	       hiphi = midphi;
	    }
	 }
	 
	 if (!broke) {
	    if (abs(lophi) < abs(hiphi)) {
	       v[k_svrad] = lorad;
	       v[k_svphi] = lophi;
	    }
	    else {
	       v[k_svrad] = hirad;
	       v[k_svphi] = hiphi;
	    }
	    v[k_svd] = (h1.referencePoint() - h2.referencePoint()).mag();
	 }

      }
   }

   v[k_visen] = (props->neutralEnergy() + props->chargedEnergy()) / eBeam->value();

   FAItem<EventType> eventtype;
   extract(iFrame.record(Stream::kEvent), eventtype);

   v[k_known] = (eventtype->known() ? 1. : 0.);

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
Convert::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Convert::endRun( Frame& iFrame )         // anal4 equiv.
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


