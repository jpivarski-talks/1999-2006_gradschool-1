// -*- C++ -*-
//
// Package:     UpsilonGammaEECascadesProc
// Module:      UpsilonGammaEECascadesProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue May 17 19:49:06 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "UpsilonGammaEECascadesProc/UpsilonGammaEECascadesProc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "CleoDB/DBEventHeader.h"
#include "RunInfo/RunStats.h"
#include "BeamEnergy/BeamEnergy.h"
#include "BeamSpot/BeamSpot.h"
#include "EventProperties/EventProperties.h"
#include "EventType/EventType.h"

#include "TriggerL1Data/TriggerL1Data.h"
#include "TriggerInfoProd/TriggerInfo.h"
#include "Level4Proc/Level4Decision.h"
#include "BunchFinder/BunchDecision.h"

#include "Navigation/NavTrack.h"
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "Navigation/NavTkShMatch.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

#include "RandomModule/RandomGenerator.h"
#include "MagField/MagneticField.h"

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
static const char* const kFacilityString = "Processor.UpsilonGammaEECascadesProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
UpsilonGammaEECascadesProc::UpsilonGammaEECascadesProc( void )               // anal1
   : Processor( "UpsilonGammaEECascadesProc" )
   , m_twotrack("twotrack", this, true)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &UpsilonGammaEECascadesProc::event,    Stream::kEvent );
   //bind( &UpsilonGammaEECascadesProc::beginRun, Stream::kBeginRun );
   //bind( &UpsilonGammaEECascadesProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

UpsilonGammaEECascadesProc::~UpsilonGammaEECascadesProc()                    // anal5
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
UpsilonGammaEECascadesProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
UpsilonGammaEECascadesProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
UpsilonGammaEECascadesProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here
   const char* label[kNumEntries] = {
      "m", "x", "y", "z", "zsep", "p1x", "p1y", "p1z", "p2x", "p2y", "p2z",
      "tracks", "chen", "neue", "cneue", "fneue", "ccen", "cccen", "fccen",
      "p1", "p2", "eop1", "eop2",
      "d0close", "z0close", "wz", "thad", "trad", "tel",
      "axish", "sterish", "cbloish", "mctag",
      "axial", "cblo", "cbmd",
      "cblo1", "cblo2", "l4tracks", "ebeam", "tt"
   };

   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
UpsilonGammaEECascadesProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   const double m1s = 9.46030;
   const double mpi2 = 0.13957018 * 0.13957018;

   FAItem<TriggerL1Data> trig;
   extract(iFrame.record(Stream::kEvent), trig);

   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);

   if (m_twotrack.value()) {
      if (!head->monteCarlo()) {
	 if (!trig->isTwoTrack()) return ActionBase::kFailed;
      }
   }
   else {
      if (!trig->isHadron()) return ActionBase::kFailed;
   }

   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   FAItem<MagneticField> bField;
   extract(iFrame.record(Stream::kStartRun), bField);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);
   double ebeam = eBeam->value();

   int mctag = 0;
   if (head->monteCarlo()) {
      ebeam = 5.01163;

      FAItem<BunchDecision> bunch;
      extract(iFrame.record(Stream::kEvent), bunch);
      if (!(bunch->numberOfTestedBunches() < 15  &&
	    bunch->bestBunchNumber() < 10)) {
	 mctag = 10;
      }

//       FAItem<MCDecayTree> tree;
//       extract(iFrame.record(Stream::kEvent), tree, "Generator");
//       const MCParticlePropertyStore& mcppstore =
// 	 tree->topParticle().properties().store();
//       const int ups1 = mcppstore.nameToQQId("Upsilon");
//       const int ups2 = mcppstore.nameToQQId("Upsilon(2S)");
//       const int piplus = mcppstore.nameToQQId("pi+");
//       const int piminus = mcppstore.nameToQQId("pi-");

//       bool saw_mode = false;
//       MCDecayTree::const_vIterator viter;
//       MCDecayTree::const_vIterator tree_vend = tree->vEnd();
//       for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
// 	 if (viter->parent().properties().QQId() == ups2) {
// 	    bool saw_ups1 = false;
// 	    bool saw_piplus = false;
// 	    bool saw_piminus = false;
// 	    Hep3Vector piplus_p, piminus_p;

// 	    MCVertex::const_pIterator chiter;
// 	    MCVertex::const_pIterator viter_pend = viter->pEnd();
// 	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
// 	       if (chiter->properties().QQId() == ups1) saw_ups1 = true;
// 	       if (chiter->properties().QQId() == piplus) {
// 		  saw_piplus = true;
// 		  piplus_p = chiter->momentum();
// 	       }
// 	       if (chiter->properties().QQId() == piminus) {
// 		  saw_piminus = true;
// 		  piminus_p = chiter->momentum();
// 	       }
// 	    }

// 	    if (saw_ups1  &&  saw_piplus  &&  saw_piminus) {
// 	       saw_mode = true;

// 	       cout << "mode: " << piplus_p << " " << piminus_p << " " << ebeam << endl;

// 	       double constraint = sqrt(sqr(2.*ebeam
// 					    - sqrt(piplus_p.mag2() + mpi2)
// 					    - sqrt(piminus_p.mag2() + mpi2))
// 					- (piplus_p + piminus_p).mag2());
// 	       cout << "constraint: " << constraint << " = sqrt(sqr(" << 2.*ebeam
// 		    << " - " << sqrt(piplus_p.mag2() + mpi2) << " - " << sqrt(piminus_p.mag2() + mpi2)
// 		    << ") - (" << (piplus_p + piminus_p) << ").mag2())" << endl;
// 	    }
// 	 }
//       }

//       if (!saw_mode) cout << "mode is missing!!!" << endl;

      FAItem<MCDecayTree> tree;
      extract(iFrame.record(Stream::kEvent), tree, "Generator");
      const MCParticlePropertyStore& mcppstore =
	 tree->topParticle().properties().store();
      const int ups1 = mcppstore.nameToQQId("Upsilon");
      const int eplus = mcppstore.nameToQQId("e+");
      const int eminus = mcppstore.nameToQQId("e-");
      const int muplus = mcppstore.nameToQQId("mu+");
      const int muminus = mcppstore.nameToQQId("mu-");
      const int tauplus = mcppstore.nameToQQId("tau+");
      const int tauminus = mcppstore.nameToQQId("tau-");

      MCDecayTree::const_vIterator viter;
      MCDecayTree::const_vIterator tree_vend = tree->vEnd();
      for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
	 if (viter->parent().properties().QQId() == ups1) {
	    bool saw_eplus = false;
	    bool saw_eminus = false;
	    bool saw_muplus = false;
	    bool saw_muminus = false;
	    bool saw_tauplus = false;
	    bool saw_tauminus = false;

	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	       if (chiter->properties().QQId() == eplus) saw_eplus = true;
	       if (chiter->properties().QQId() == eminus) saw_eminus = true;
	       if (chiter->properties().QQId() == muplus) saw_muplus = true;
	       if (chiter->properties().QQId() == muminus) saw_muminus = true;
	       if (chiter->properties().QQId() == tauplus) saw_tauplus = true;
	       if (chiter->properties().QQId() == tauminus) saw_tauminus = true;
	    }
	    
	    if (saw_eplus && saw_eminus) mctag += 1;
	    else if (saw_muplus && saw_muminus) mctag += 2;
	    else if (saw_tauplus && saw_tauminus) mctag += 3;
	 }
      }
   }

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator track_iter, other_iter;
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();

   vector<double> mlist;
   vector<FATable<NavTrack>::const_iterator> mpion1;
   vector<FATable<NavTrack>::const_iterator> mpion2;
   vector<double> mx;
   vector<double> my;
   vector<double> mz;
   vector<double> mzsep;
   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
       if (
	  track_iter->pionFit()->momentum().perp() > 0.150                                                   &&
	  track_iter->pionFit()->momentum().mag() < 0.6                                                      &&

 	  // L4 conditions
 	  !track_iter->seedQuality()->originUsed()                                                           &&
 	  track_iter->seedQuality()->numberHitsExpected() > 0                                                &&
 	  track_iter->seedQuality()->numberHits() / double(track_iter->seedQuality()->numberHitsExpected()) >= 0.4   &&
 	  sqrt(1. - 1./(1.+sqr(track_iter->seedTrack()->cotTheta()))) <= 0.93                                &&
 	  track_iter->seedQuality()->chiSquare() < track_iter->seedQuality()->degreesOfFreedom() * 20.       &&
 	  fabs(track_iter->seedTrack()->d0()) < 0.025                                                        &&
 	  fabs(track_iter->seedTrack()->z0()) < 0.15                                                         &&

 	  // EventProperties conditions
 	  track_iter->pionQuality()->fit()                                                                   &&
 	  !track_iter->pionQuality()->fitAbort()                                                             &&
 	  (track_iter->pionQuality()->degreesOfFreedom() <= 0  ||
 	   track_iter->pionQuality()->chiSquare() / double(track_iter->pionQuality()->degreesOfFreedom()) < 100.)    &&
 	  track_iter->seedQuality()->numberHitsExpected() > 0                                                &&
 	  track_iter->seedQuality()->numberLayers() / double(track_iter->seedQuality()->numberHitsExpected()) > 0.5  &&
 	  track_iter->seedQuality()->numberLayers() / double(track_iter->seedQuality()->numberHitsExpected()) < 1.2  &&
 	  fabs(track_iter->pionHelix()->d0()) < 0.03                                                         &&
 	  fabs(track_iter->pionHelix()->position().z()) < 0.18                                               &&
 	  track_iter->pionFit()->momentum().mag() > 0.01 * ebeam                                    &&
 	  track_iter->pionFit()->momentum().mag() < 1.5 * ebeam                                     &&
 	  fabs(track_iter->pionHelix()->cotTheta()) < 3.0424                                                 &&
 	  sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) < 0.5   &&
 	  sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) < 0.25
 	 ) {

 	 for (other_iter = track_iter;  other_iter != tracks_end;  ++other_iter) {
 	    if (
	       other_iter != track_iter                                                                           &&
	       other_iter->pionFit()->momentum().perp() > 0.150                                                   &&
	       other_iter->pionFit()->momentum().mag() < 0.6                                                      &&
	       track_iter->pionHelix()->curvature() * other_iter->pionHelix()->curvature() < 0.                   &&

 	       // L4 conditions
 	       !other_iter->seedQuality()->originUsed()                                                           &&
 	       other_iter->seedQuality()->numberHitsExpected() > 0                                                &&
 	       other_iter->seedQuality()->numberHits() / double(other_iter->seedQuality()->numberHitsExpected()) >= 0.4   &&
 	       sqrt(1. - 1./(1.+sqr(other_iter->seedTrack()->cotTheta()))) <= 0.93                                &&
 	       other_iter->seedQuality()->chiSquare() < other_iter->seedQuality()->degreesOfFreedom() * 20.       &&
 	       fabs(other_iter->seedTrack()->d0()) < 0.025                                                        &&
 	       fabs(other_iter->seedTrack()->z0()) < 0.15                                                         &&

 	       // EventProperties conditions
 	       other_iter->pionQuality()->fit()                                                                   &&
 	       !other_iter->pionQuality()->fitAbort()                                                             &&
 	       (other_iter->pionQuality()->degreesOfFreedom() <= 0  ||
 		other_iter->pionQuality()->chiSquare() / double(other_iter->pionQuality()->degreesOfFreedom()) < 100.)    &&
 	       other_iter->seedQuality()->numberHitsExpected() > 0                                                &&
 	       other_iter->seedQuality()->numberLayers() / double(other_iter->seedQuality()->numberHitsExpected()) > 0.5  &&
 	       other_iter->seedQuality()->numberLayers() / double(other_iter->seedQuality()->numberHitsExpected()) < 1.2  &&
 	       fabs(other_iter->pionHelix()->d0()) < 0.03                                                         &&
 	       fabs(other_iter->pionHelix()->position().z()) < 0.18                                               &&
 	       other_iter->pionFit()->momentum().mag() > 0.01 * ebeam                                    &&
 	       other_iter->pionFit()->momentum().mag() < 1.5 * ebeam                                     &&
 	       fabs(other_iter->pionHelix()->cotTheta()) < 3.0424                                                 &&
 	       sqrt(fabs(other_iter->pionHelix()->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) < 0.5   &&
 	       sqrt(fabs(other_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) < 0.25
 	       ) {
	       

	       double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
	       KTHelix track(*track_iter->pionHelix());
	       KTHelix other(*other_iter->pionHelix());
	       if (
		  calc_intersection(tx, ty, tz, tsig2z, tzsep, track, other)                 &&
		  fabs(tzsep) < 0.025                                                        &&
		  sqrt(sqr(tx - spot->center().x()) + sqr(ty - spot->center().y())) < 0.005  &&
		  fabs(tz) < 0.05
		  ) {
		  double track_moved, other_moved;
		  if (track.moveToLine(HepPoint3D(tx, ty, 0.), HepVector3D(0., 0., 1.), track_moved) == KTMoveControl::kMoveOK  &&
		      other.moveToLine(HepPoint3D(tx, ty, 0.), HepVector3D(0., 0., 1.), other_moved) == KTMoveControl::kMoveOK     ) {
		     HepVector3D track_p = track.momentum(bField->BField(HepPoint3D(tx, ty, tz)));
		     HepVector3D other_p = other.momentum(bField->BField(HepPoint3D(tx, ty, tz)));

		     double constraint = sqrt(sqr(2.*ebeam
						  - sqrt(track_p.mag2() + mpi2)
						  - sqrt(other_p.mag2() + mpi2))
					      - (track_p + other_p).mag2());

		     if (fabs(constraint - m1s) < 0.02) {
			mlist.push_back(constraint);
			mpion1.push_back(track_iter);
			mpion2.push_back(other_iter);
			mx.push_back(tx);
			my.push_back(ty);
			mz.push_back(tz);
			mzsep.push_back(tzsep);
		     }
		  }
	       }
// 	       if (m < 0.  ||  fabs(constraint - m1s) < fabs(m - m1s)) {
// 		  m2 = m;
// 		  pion1_2 = pion1;
// 		  pion2_2 = pion2;

// 		  m = constraint;
// 		  pion1 = track_iter;
// 		  pion2 = other_iter;
// 	       }
// 	       else if (m2 < 0.  ||  fabs(constraint - m1s) < fabs(m2 - m1s)) {
// 		  m2 = constraint;
// 		  pion1_2 = track_iter;
// 		  pion2_2 = other_iter;
// 	       }
	    }
	 }
       }
   }

   if (mlist.size() == 0) return ActionBase::kFailed;

   RandomGenerator& random(RandomGenerator::instance());
   int index = -1;
   while (index < 0 || index >= mlist.size())
      index = floor(random.flat() * mlist.size());
   double m = mlist[index];
   FATable<NavTrack>::const_iterator pion1 = mpion1[index];
   FATable<NavTrack>::const_iterator pion2 = mpion2[index];
   double x = mx[index];
   double y = my[index];
   double z = mz[index];
   double zsep = mzsep[index];

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator showers_end = showers.end();

   float v[kNumEntries];
   for (int i = 0;  i < kNumEntries;  i++) v[i] = -1000.;

   v[k_m] = m;
   v[k_x] = x;
   v[k_y] = y;
   v[k_z] = z;
   v[k_zsep] = zsep;

//   v[k_m] = m * (pion1->pionHelix()->curvature() * pion2->pionHelix()->curvature() < 0. ? 1. : -1.);
//    if (m2 >= 0.) {
//       v[k_m2] = m2 * (pion1_2->pionHelix()->curvature() * pion2_2->pionHelix()->curvature() < 0. ? 1. : -1.);
//    }

   v[k_thad] = (trig->isHadron() ? 1. : 0.);
   v[k_trad] = (trig->isRadTau() ? 1. : 0.);
   v[k_tel] = (trig->isElTrack() ? 1. : 0.);
   v[k_tt] = (trig->isTwoTrack() ? 1. : 0.);

   v[k_p1x] = pion1->pionFit()->momentum().x();
   v[k_p1y] = pion1->pionFit()->momentum().y();
   v[k_p1z] = pion1->pionFit()->momentum().z();
   v[k_p2x] = pion2->pionFit()->momentum().x();
   v[k_p2y] = pion2->pionFit()->momentum().y();
   v[k_p2z] = pion2->pionFit()->momentum().z();

   v[k_tracks] = props->nbChargedTracks() - 2;
   v[k_ebeam] = ebeam;

   double d0close = -1000.;
   double z0close = -1000.;
   double znumer = 0.;
   double zdenom = 0.;
   double chen = 0.;
   double p1 = 0.;
   double p2 = 0.;
   v[k_l4tracks] = 0.;
   FATable<NavTrack>::const_iterator t1 = tracks_end;
   FATable<NavTrack>::const_iterator t2 = tracks_end;
   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
      if (track_iter != pion1  &&  track_iter != pion2) {

	 if (!track_iter->seedQuality()->originUsed()                                                           &&
	     track_iter->seedQuality()->numberHitsExpected() > 0                                                &&
	     track_iter->seedQuality()->numberHits() / double(track_iter->seedQuality()->numberHitsExpected()) >= 0.4   &&
	     sqrt(1. - 1./(1.+sqr(track_iter->seedTrack()->cotTheta()))) <= 0.93                                &&
	     track_iter->seedQuality()->chiSquare() < track_iter->seedQuality()->degreesOfFreedom() * 20.       &&
	     fabs(track_iter->seedTrack()->d0()) < 0.025                                                        &&
	     fabs(track_iter->seedTrack()->z0()) < 0.15) {
	    v[k_l4tracks] += 1.;
	 }

	 if (track_iter->pionQuality()->fit()                                                                   &&
	     !track_iter->pionQuality()->fitAbort()                                                             &&
	     (track_iter->pionQuality()->degreesOfFreedom() <= 0  ||
	      track_iter->pionQuality()->chiSquare() / double(track_iter->pionQuality()->degreesOfFreedom()) < 100.)    &&
	     track_iter->seedQuality()->numberHitsExpected() > 0                                                &&
	     track_iter->seedQuality()->numberLayers() / double(track_iter->seedQuality()->numberHitsExpected()) > 0.5  &&
	     track_iter->seedQuality()->numberLayers() / double(track_iter->seedQuality()->numberHitsExpected()) < 1.2  &&
	     fabs(track_iter->pionHelix()->d0()) < 0.03                                                         &&
	     fabs(track_iter->pionHelix()->position().z()) < 0.18                                               &&
	     track_iter->pionFit()->momentum().mag() > 0.01 * ebeam                                    &&
	     track_iter->pionFit()->momentum().mag() < 1.5 * ebeam                                     &&
	     fabs(track_iter->pionHelix()->cotTheta()) < 3.0424                                                 &&
	     sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) < 0.5   &&
	     sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) < 0.25) {
	    
	    double pmag = track_iter->pionFit()->momentum().mag();
	    chen += track_iter->pionFit()->energy();

	    if( track_iter->trackShowerMatch().valid()          &&
		0.5 < track_iter->trackShowerMatch()->eOverP()  &&
		0   < track_iter->bremShowers().size()                )
	    {
	       FATable< NavShower > show ( track_iter->bremShowers() ) ;
	       for( FATable< NavShower >::const_iterator iS ( show.begin() ) ;
		    iS != show.end() ; ++iS )
	       {
		  const CcGeV esh ( iS->attributes().energy() ) ; 
		  if( esh > 0.01*ebeam )
		  {
		     pmag  += esh ;
		     chen += esh ;
		  }
	       }
	    }

	    if (t1 == tracks_end  ||  p1 < pmag) {
	       t2 = t1;
	       p2 = p1;

	       t1 = track_iter;
	       p1 = pmag;
	    }
	    else if (t2 == tracks_end  ||  p2 < pmag) {
	       t2 = track_iter;
	       p2 = pmag;
	    }

	 } // end if this non-pion is a quality track

	 KTHelix movetrack(*track_iter->pionHelix());
	 double distance_moved;
	 movetrack.moveToReferencePoint(spot->center(),
					distance_moved,
					KTMoveControl::kDirectionEither);
	 if (fabs(movetrack.d0()) < fabs(d0close)) d0close = movetrack.d0();
	 if (fabs(movetrack.z0()) < fabs(z0close)) z0close = movetrack.z0();

	 if (! track_iter->seedQuality()->originUsed()            &&
	     ! track_iter->pionQuality()->fitAbort()              &&
	     1./fabs(track_iter->pionHelix()->curvature()) > 0.42  &&
	     ! track_iter->pionHelix()->hasNullErrorMatrix()        
	    ) {

	    // Secondary track loop to calculate pairwise intersections
	    for (other_iter = track_iter;  other_iter != tracks_end;  ++other_iter) {
	       if (other_iter != track_iter                             &&
		   other_iter != pion1  &&  other_iter != pion2         &&
		   ! other_iter->seedQuality()->originUsed()            &&
		   ! other_iter->pionQuality()->fitAbort()              &&
		   1./fabs(other_iter->pionHelix()->curvature()) > 0.42  &&
		   ! other_iter->pionHelix()->hasNullErrorMatrix()        
		  ) { 

		  double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
		  KTHelix track(*track_iter->pionHelix());
		  KTHelix other(*other_iter->pionHelix());
		  if (calc_intersection(tx, ty, tz, tsig2z, tzsep, track, other)) {
		     double perp(sqrt(sqr(tx - spot->center().x()) + sqr(ty - spot->center().y())));
		     double z_uncert2(tsig2z + sqr(tzsep) +
				      sqr(tx - spot->center().x()) +
				      sqr(ty - spot->center().y()));

		     znumer += tz / z_uncert2;
		     zdenom += 1. / z_uncert2;

		  } // end if successful intersection
	       } // end if secondary track passes quality cuts and isn't one of the pions
	    } // end loop over secondary track

	 } // end if primary track passes quality cuts
      } // end if not one of the pions
   } // end loop over tracks

   double wz = -1000.;
   if (zdenom != 0.) {
      wz = znumer / zdenom;
      wz -= spot->center().z();
   }   

   double ccen = 0.;
   double cccen = 0.;
   double fccen = 0.;

   double neue = 0.;
   double cneue = 0.;
   double fneue = 0.;

   v[k_cbloish] = 0.;
   v[k_cblo1] = 0.;
   v[k_cblo2] = 0.;
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();
	shower_iter != showers_end;
	++shower_iter) {
      if (shower_iter->attributes().energy() > 0.01*ebeam  &&
	  shower_iter->attributes().status()) {

	 bool matched_to_pion = false;
	 const FATable<NavTkShMatch> matches = shower_iter->trackMatches();
	 for (FATable<NavTkShMatch>::const_iterator mat_iter = matches.begin();
	      mat_iter != matches.end();
	      ++mat_iter) {
	    if (mat_iter->trackId() == pion1->identifier()  ||
		mat_iter->trackId() == pion2->identifier()    )
	       matched_to_pion = true;
	 }

	 if (shower_iter->attributes().energy() > 0.4  &&
	     shower_iter->attributes().goodBarrel()) {
	    v[k_cblo1] += 1.;
	 }
	 if (shower_iter->attributes().energy() > 0.4  &&
	     shower_iter->attributes().goodBarrel()    &&
	     !matched_to_pion) {
	    v[k_cblo2] += 1.;
	 }

	 if (!matched_to_pion) {
	    if (shower_iter->attributes().energy() > 0.35) {
	       v[k_cbloish] += 1.;
	    } // end if cbloish

	    ccen += shower_iter->attributes().energy();
	    if (!shower_iter->attributes().hot()) {
	       cccen += shower_iter->attributes().energy();
	       if (shower_iter->attributes().goodBarrel()) {
		  fccen += shower_iter->attributes().energy();
	       } // end if goodBarrel
	    } // end if not hot

	    if (shower_iter->noTrackMatch()        &&
		shower_iter->noTrackMatchConReg()  &&
		(!shower_iter->bremTrack().valid()  ||
		 (shower_iter->bremTrack()->trackShowerMatch().valid() &&
		  shower_iter->bremTrack()->trackShowerMatch()->eOverP() < 0.5))) {
	       neue += shower_iter->attributes().energy();
	       if (!shower_iter->attributes().hot()) {
		  cneue += shower_iter->attributes().energy();
		  if (shower_iter->attributes().goodBarrel()) {
		     fneue += shower_iter->attributes().energy();
		  } // end if goodBarrel
	       } // end if not hot
	    } // end if neutral

	 } // end if not matched to pion
      } // end if quality shower
   } // end loop over showers

   v[k_chen] = chen / m1s;

   v[k_ccen] = ccen / m1s;
   v[k_cccen] = cccen / m1s;
   v[k_fccen] = fccen / m1s;

   v[k_neue] = neue / m1s;
   v[k_cneue] = cneue / m1s;
   v[k_fneue] = fneue / m1s;

   v[k_d0close] = d0close;
   v[k_z0close] = z0close;
   v[k_wz] = wz;

   v[k_p1] = p1 / m1s * 2.;
   v[k_p2] = p2 / m1s * 2.;

   if (t1 != tracks_end  &&  t1->trackShowerMatch().valid()) {
      v[k_eop1] = t1->trackShowerMatch()->eOverP();
   }
   if (t2 != tracks_end  &&  t2->trackShowerMatch().valid()) {
      v[k_eop2] = t2->trackShowerMatch()->eOverP();
   }

   v[k_axish] = 0.;
   v[k_sterish] = 0.;
   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
      if (track_iter != pion1  &&  track_iter != pion2) {
	 if (track_iter->pionFit()->momentum().perp() > 0.150) {
	    v[k_axish] += 1.;
	    
	    if (
	       // L4 conditions
	       !track_iter->seedQuality()->originUsed()                                                           &&
	       track_iter->seedQuality()->numberHitsExpected() > 0                                                &&
	       track_iter->seedQuality()->numberHits() / double(track_iter->seedQuality()->numberHitsExpected()) >= 0.4   &&
	       sqrt(1. - 1./(1.+sqr(track_iter->seedTrack()->cotTheta()))) <= 0.93                                &&
	       track_iter->seedQuality()->chiSquare() < track_iter->seedQuality()->degreesOfFreedom() * 20.       &&
	       fabs(track_iter->seedTrack()->d0()) < 0.025                                                        &&
	       fabs(track_iter->seedTrack()->z0()) < 0.15                                                         &&

	       // EventProperties conditions
	       track_iter->pionQuality()->fit()                                                                   &&
	       !track_iter->pionQuality()->fitAbort()                                                             &&
	       (track_iter->pionQuality()->degreesOfFreedom() <= 0  ||
		track_iter->pionQuality()->chiSquare() / double(track_iter->pionQuality()->degreesOfFreedom()) < 100.)    &&
	       track_iter->seedQuality()->numberHitsExpected() > 0                                                &&
	       track_iter->seedQuality()->numberLayers() / double(track_iter->seedQuality()->numberHitsExpected()) > 0.5  &&
	       track_iter->seedQuality()->numberLayers() / double(track_iter->seedQuality()->numberHitsExpected()) < 1.2  &&
	       fabs(track_iter->pionHelix()->d0()) < 0.03                                                         &&
	       fabs(track_iter->pionHelix()->position().z()) < 0.18                                               &&
	       track_iter->pionFit()->momentum().mag() > 0.01 * ebeam                                    &&
	       track_iter->pionFit()->momentum().mag() < 1.5 * ebeam                                     &&
	       fabs(track_iter->pionHelix()->cotTheta()) < 3.0424                                                 &&
	       sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) < 0.5   &&
	       sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) < 0.25
	       ) {
	       
	       v[k_sterish] += 1.;

	    }
	 }
      }
   }

   if (head->monteCarlo()) {
      FAItem<TriggerInfo> trigger;
      extract(iFrame.record(Stream::kEvent), trigger);

      v[k_axial] = trigger->axial();
      v[k_cblo] = trigger->cblo();
      v[k_cbmd] = trigger->cbmd();

      v[k_mctag] = mctag;
   }

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
UpsilonGammaEECascadesProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
UpsilonGammaEECascadesProc::endRun( Frame& iFrame )         // anal4 equiv.
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

bool
UpsilonGammaEECascadesProc::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep, KTHelix& a, KTHelix& b)
{
   x = y = z = sig2z = zsep = 1000.;  // To more easily find unchecked failures

   // Express the two helices in terms of (x - xa)^2 + (y - ya)^2 == ra^2
   double ra( 1./2./a.curvature() );
   double xa( -(a.d0() + ra) * sin(a.phi0()) );
   double ya( (a.d0() + ra) * cos(a.phi0()) );

   double rb( 1./2./b.curvature() );
   double xb( -(b.d0() + rb) * sin(b.phi0()) );
   double yb( (b.d0() + rb) * cos(b.phi0()) );

   // Zero or infinitely many solutions
   // I don't want to deal with either case
   if ( xa == xb  &&  ya == yb ) return false;

   double disc( (pow(4.*sqr(ra)*(xa - xb) - 
		     4.*(sqr(rb)*(xa - xb) + 
			 (xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))
		     ,2.) - 16.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))*
		 (pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
		  2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
		  2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
		  pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
		  4.*sqr(rb)*sqr(ya - yb)))/
		(64.*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );
   // no real solutions
   if ( disc < 0 ) return false;

   double pre( (sqr(rb)*(xa - xb) + sqr(ra)*(-xa + xb) + 
		(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))/
	       (2.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))) );

   // The two x solutions
   double xsol1( pre + sqrt( disc ) );
   double xsol2( pre - sqrt( disc ) );

   // Two possibilities for the y solution to each x solution
   double ysol1a( yb + sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1b( yb - sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1;
   if ( fabs( sqr(xsol1 - xa) + sqr(ysol1a - ya) - sqr(ra) ) <
	fabs( sqr(xsol1 - xa) + sqr(ysol1b - ya) - sqr(ra) )   )
      ysol1 = ysol1a;
   else
      ysol1 = ysol1b;

   double ysol2a( yb + sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2b( yb - sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2;
   if ( fabs( sqr(xsol2 - xa) + sqr(ysol2a - ya) - sqr(ra) ) <
	fabs( sqr(xsol2 - xa) + sqr(ysol2b - ya) - sqr(ra) )   )
      ysol2 = ysol2a;
   else
      ysol2 = ysol2b;

   // Calculate the arclength of each solution along the two tracks.
   // Throw out a solution if the particle needs to travel (too far)
   // backward to get to it. If both solutions are okay, take the one
   // closest to the origin.
   DABoolean arclength1_ok( arclength_test( xsol1, ysol1, a, b ) );
   DABoolean arclength2_ok( arclength_test( xsol2, ysol2, a, b ) );
   
   if ( !arclength1_ok  &&  !arclength2_ok ) return false;

   else if ( arclength1_ok  &&  !arclength2_ok ) {
      x = xsol1;  y = ysol1;
   }

   else if ( !arclength1_ok  &&  arclength2_ok ) {
      x = xsol2;  y = ysol2;
   }

   else if ( sqr(xsol1) + sqr(ysol1) < sqr(xsol2) + sqr(ysol2) ) {
      x = xsol1;  y = ysol1;
   }

   else {
      x = xsol2;  y = ysol2;
   }      

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   double az( a.cotTheta() * aarclength + a.z0() );
   double bz( b.cotTheta() * barclength + b.z0() );
   double sig2_az( a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(aarclength)
		   + a.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * aarclength * a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );
   double sig2_bz( b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(barclength)
		   + b.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * barclength * b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );

   z = (az/sig2_az + bz/sig2_bz) / (1./sig2_az + 1./sig2_bz);
   sig2z = 1. / (1./sig2_az + 1./sig2_bz);
   zsep = az - bz;

   // Because it is not useful for the `closest_intersection'
   // algorithm, I had to throw out a great deal of lovely code that
   // calculates uncertanties in x and y.  If you want this, ask me
   // about it.
   return true;
}

bool
UpsilonGammaEECascadesProc::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
{
   const double tailCut = 0.005;

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   return ( aarclength > -tailCut  &&  aarclength < M_PI/2./fabs(a.curvature()) )  &&
      ( barclength > -tailCut  &&  barclength < M_PI/2./fabs(b.curvature()) );
}
