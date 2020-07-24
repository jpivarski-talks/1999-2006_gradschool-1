// -*- C++ -*-
//
// Package:     Cuts
// Module:      Cuts
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri Mar  5 11:36:58 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Cuts/Cuts.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCTrackTagger/MCTrackTagsByMCParticle.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "Level3TagWord/Level3TagWord.h"
#include "Level4Proc/Level4Decision.h"
#include "BeamEnergy/BeamEnergy.h"
#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"
#include "Navigation/NavShower.h"
#include "Navigation/NavTkShMatch.h"
#include "BeamSpot/BeamSpot.h"
#include "EventProperties/EventProperties.h"
#include "EventType/EventType.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"
#include "Level4Proc/Level4DecisionProxy.h"
#include "StupidProd/Stupid.h"
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
static const char* const kFacilityString = "Processor.Cuts" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Cuts::Cuts( void )               // anal1
   : Processor( "Cuts" )
   , m_usingQQ("usingQQ", this, false)
   , m_usingEvtGen("usingEvtGen", this, false)
   , m_wantLeptons("wantLeptons", this, false)
   , m_lookForStupid("lookForStupid", this, true)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Cuts::event,    Stream::kEvent );
   //bind( &Cuts::beginRun, Stream::kBeginRun );
   //bind( &Cuts::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Cuts::~Cuts()                    // anal5
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
Cuts::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Cuts::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
Cuts::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "d0close", "z0close",
      "ebeam", "ntracks",
      "e1", "e2", "p1", "p2", "pmiss", "pnext", "pfound",
      "shxy", "shz", "shphi1", "shphi2", "shcosth1", "shcosth2",
      "ephalf", "epwhole", "epdouble",
      "trxy", "trz", "d0miss", "z0miss", "trphi1", "trphi2", "trcosth1", "trcosth2",
      "trperp1", "trperp2", "trperp3", "trperp4",
      "rawntracks", "visen", "ccen", "neue", "q", "wrphi", "wz", "pass", "trigger", "trax",
      "twopions", "pi1x", "pi1y", "pi1z", "pi2x", "pi2y", "pi2z"
   };
   m_ntuple = iHistoManager.ntuple(
      1, "plain", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Cuts::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   if (m_usingQQ.value()  ||  m_usingEvtGen.value()) {
      FAItem<MCDecayTree> tree;
      extract(iFrame.record(Stream::kEvent), tree, "Generator");
      MCDecayTree::const_vIterator viter;
      MCDecayTree::const_vIterator tree_vend = tree->vEnd();

      const MCParticlePropertyStore& mcppstore =
	 tree->topParticle().properties().store();

      int ups1, ups2, ups3, eplus, eminus, muplus, muminus, gamm;
      if (m_usingQQ.value()) {
	 ups1 = mcppstore.nameToQQId("UPS1");
	 ups2 = mcppstore.nameToQQId("UPS2");
	 ups3 = mcppstore.nameToQQId("UPS3");
	 eplus = mcppstore.nameToQQId("E+");
	 eminus = mcppstore.nameToQQId("E-");
	 muplus = mcppstore.nameToQQId("MU+");
	 muminus = mcppstore.nameToQQId("MU-");
	 gamm = mcppstore.nameToQQId("GAMM");
      }
      else {
	 ups1 = mcppstore.nameToQQId("Upsilon");
	 ups2 = mcppstore.nameToQQId("Upsilon(2S)");
	 ups3 = mcppstore.nameToQQId("Upsilon(3S)");
	 eplus = mcppstore.nameToQQId("e+");
	 eminus = mcppstore.nameToQQId("e-");
	 muplus = mcppstore.nameToQQId("mu+");
	 muminus = mcppstore.nameToQQId("mu-");
	 gamm = mcppstore.nameToQQId("gamma");
      }

      bool ups_to_leptons = false;
      for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
	 if (viter->parent().properties().QQId() == ups1  ||
	     viter->parent().properties().QQId() == ups2  ||
	     viter->parent().properties().QQId() == ups3    ) {
	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();

	    bool eplus_, eminus_, muplus_, muminus_;
	    eplus_ = eminus_ = muplus_ = muminus_ = false;
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	       if (chiter->properties().QQId() == eplus) eplus_ = true;
	       if (chiter->properties().QQId() == eminus) eminus_ = true;
	       if (chiter->properties().QQId() == muplus) muplus_ = true;
	       if (chiter->properties().QQId() == muminus) muminus_ = true;
	    } // end loop over children
	    if ((eplus_ && eminus_) || (muplus_ && muminus_)) ups_to_leptons = true;
	 } // end if upsilon
      } // end loop over vertices

      if ( m_wantLeptons.value()  &&  !ups_to_leptons) return ActionBase::kFailed;
      if (!m_wantLeptons.value()  &&   ups_to_leptons) return ActionBase::kFailed;
   }

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();

   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   float d0close = 1000.;
   float z0close = 1000.;
   float ci_perp = 1000.;
   double znumer = 0.;
   double zdenom = 0.;
   FATable<NavTrack>::const_iterator track_iter;
   double interx, intery;
   for (track_iter = tracks.begin();
	track_iter != tracks_end;
	++track_iter) {
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
	 for (FATable<NavTrack>::const_iterator other_iter = track_iter;
	      other_iter != tracks_end;
	      ++other_iter) {
	    if (other_iter != track_iter  &&
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
		  if (perp < ci_perp) {
		     ci_perp = perp;
		     interx = tx;
		     intery = ty;
		  }

		  // uncertainty in the z intersection + mismatch in z + mismatch in perp
		  double z_uncert2(tsig2z + sqr(tzsep) +
				   sqr(tx - spot->center().x()) +
				   sqr(ty - spot->center().y()));
		  znumer += tz / z_uncert2;
		  zdenom += 1. / z_uncert2;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over tracks

   double weighted_z = 1000.;
   if (zdenom != 0.) {
      weighted_z = znumer / zdenom;
      weighted_z -= spot->center().z();
   }

   FAItem<MagneticField> bField;
   extract(iFrame.record(Stream::kStartRun), bField);

   float twopions = 0.;
   HepVector3D pi1(0., 0., 0.);
   HepVector3D pi2(0., 0., 0.);
   const double energy_splitting = 10.3552 - 9.46030; // E_U(3S) - E_U(1S) in GeV
   const double pion_mass2 = sqr(0.13957018); // GeV
   if (ci_perp < 1000.  &&  weighted_z < 1000.) {
      HepPoint3D intersection(interx, intery, weighted_z);
      HepVector3D bFieldThere(bField->BField(intersection));
      if (m_usingQQ.value()  ||  m_usingEvtGen.value()) {
	 FAItem<MCDecayTree> tree;
	 extract(iFrame.record(Stream::kEvent), tree, "Generator");
	 MCDecayTree::const_vIterator viter;
	 MCDecayTree::const_vIterator tree_vend = tree->vEnd();

	 FATable<MCTrackTagsByMCParticle> mctags;
	 extract(iFrame.record(Stream::kEvent), mctags);

	 const MCParticlePropertyStore& mcppstore =
	    tree->topParticle().properties().store();

	 int ups1, ups3, piplus, piminus;
	 if (m_usingQQ.value()) {
	    ups1 = mcppstore.nameToQQId("UPS1");
	    ups3 = mcppstore.nameToQQId("UPS3");
	    piplus = mcppstore.nameToQQId("PI+");
	    piminus = mcppstore.nameToQQId("PI-");
	 }
	 else {
	    ups1 = mcppstore.nameToQQId("Upsilon");
	    ups3 = mcppstore.nameToQQId("Upsilon(3S)");
	    piplus = mcppstore.nameToQQId("pi+");
	    piminus = mcppstore.nameToQQId("pi-");
	 }

	 for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
	    if (viter->parent().properties().QQId() == ups3) {
	       MCVertex::const_pIterator chiter;
	       MCVertex::const_pIterator viter_pend = viter->pEnd();

	       bool piplus_, piminus_, ups1_;
	       piplus_ = piminus_ = ups1_ = false;
	       HepVector3D try1(0., 0., 0.);
	       HepVector3D try2(0., 0., 0.);
	       for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
		  if (chiter->properties().QQId() == piplus) {
		     piplus_ = true;
		     FATable<MCTrackTagsByMCParticle>::const_iterator tag = mctags.find(chiter->identifier());
		     if (tag != mctags.end()  &&  tag->isMatched()) {
			FATable<NavTrack>::const_iterator best = tracks.find(tag->bestTrackID());
			KTHelix movetrack(*best->pionHelix());
			double distance_moved;
			movetrack.moveToRadius(ci_perp, distance_moved, KTMoveControl::kDirectionEither);
			HepPoint3D placement = intersection - movetrack.referencePoint();

			if (placement.perp() < 0.001  &&  fabs(placement.z()) < 0.01) {
			   try1 = movetrack.momentum(bFieldThere);
			}
			else {
			   try1 = HepVector3D(1000., 1000., 1000.);
			}
		     } // end if we have a match
		  } // end if this is a piplus
		  if (chiter->properties().QQId() == piminus) {
		     piminus_ = true;
		     FATable<MCTrackTagsByMCParticle>::const_iterator tag = mctags.find(chiter->identifier());
		     if (tag != mctags.end()  &&  tag->isMatched()) {
			FATable<NavTrack>::const_iterator best = tracks.find(tag->bestTrackID());
			KTHelix movetrack(*best->pionHelix());
			double distance_moved;
			movetrack.moveToRadius(ci_perp, distance_moved, KTMoveControl::kDirectionEither);
			HepPoint3D placement = intersection - movetrack.referencePoint();

			if (placement.perp() < 0.001  &&  fabs(placement.z()) < 0.01) {
			   try2 = movetrack.momentum(bFieldThere);
			}
			else {
			   try2 = HepVector3D(1000., 1000., 1000.);
			}
		     } // end if we have a match
		  } // end if this is a piminus
		  if (chiter->properties().QQId() == ups1) ups1_ = true;
	       } // end loop over children
	       if (piplus_ && piminus_ && ups1_) {
		  if (try1.x() < 1000.  &&  try2.x() < 1000.) {
		     twopions = (sqrt(try1.mag2() + pion_mass2) +
				 sqrt(try2.mag2() + pion_mass2)  );
		  }
		  else twopions = 1000.;
		  pi1 = try1;
		  pi2 = try2;
	       } // end if this is a U(3S) --> pi+ pi- U(1S) decay
	    } // end if upsilon
	 } // end loop over vertices
      }
      else {
	 for (track_iter = tracks.begin();
	      track_iter != tracks_end;
	      ++track_iter) {
	    KTHelix movetrack1(*track_iter->pionHelix());
	    double distance_moved1;
	    movetrack1.moveToRadius(ci_perp, distance_moved1, KTMoveControl::kDirectionEither);
	    HepPoint3D placement1 = intersection - movetrack1.referencePoint();

	    if (placement1.perp() < 0.001  &&  fabs(placement1.z()) < 0.01) {

	       HepVector3D try1 = movetrack1.momentum(bFieldThere);

	       for (FATable<NavTrack>::const_iterator other_iter = track_iter;
		    other_iter != tracks_end;
		    ++other_iter) {
		  if (track_iter->pionHelix()->curvature() * other_iter->pionHelix()->curvature() < 0.) {

		     KTHelix movetrack2(*other_iter->pionHelix());
		     double distance_moved2;
		     movetrack2.moveToRadius(ci_perp, distance_moved2, KTMoveControl::kDirectionEither);
		     HepPoint3D placement2 = intersection - movetrack2.referencePoint();

		     if (placement2.perp() < 0.001  &&  fabs(placement2.z()) < 0.01) {
			HepVector3D try2 = movetrack2.momentum(bFieldThere);
	 
			double twotryons = (sqrt(try1.mag2() + pion_mass2) +
					    sqrt(try2.mag2() + pion_mass2)  );
			if (fabs(twotryons - energy_splitting) < 0.05  &&  (try1 + try2).mag() < 0.4) {
			   twopions = twotryons;
			   pi1 = try1;
			   pi2 = try2;
			}
		     } // end if second track is in the right place
		  } // end if second track is the right sign
	       } // end loop over second track
	    } // end if first track is in the right place
	 } // end loop over first track
      } // end if we have a good vertex
   } // if there's an intersection
   
   FAItem<BeamEnergy> beamEnergy;
   extract(iFrame.record(Stream::kStartRun), beamEnergy);
   float eBeam = beamEnergy->value();

   FAItem<EventProperties> prop;
   extract(iFrame.record(Stream::kEvent), prop);

   float ntracks = prop->nbChargedTracks();

   float e1 = prop->firstLargestEShower() / eBeam;
   float e2 = prop->secondLargestEShower() / eBeam;
   float p1 = prop->firstLargestPTrack() / eBeam;
   float p2 = prop->secondLargestPTrack() / eBeam;

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator shower_end = showers.end();

   // To do: make some sort of showers-only momentum balance: how much
   // energy in which hemisphere, etc.
   float ephalf = 0.;
   float epwhole = 0.;
   float epdouble = 0.;
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();
	shower_iter != shower_end;
	++shower_iter) {
      if (!shower_iter->attributes().hot()) {
	 ephalf += shower_iter->attributes().energy() * sqrt(fabs(1./tan(shower_iter->attributes().theta())));
	 epwhole += shower_iter->attributes().energy() * fabs(1./tan(shower_iter->attributes().theta()));
	 epdouble += shower_iter->attributes().energy() * sqr(fabs(1./tan(shower_iter->attributes().theta())));
      }
   }

   float shxy = 0.;
   float shz = 0.;
   float shphi1 = 3.*M_PI;
   float shphi2 = 3.*M_PI;
   float shcosth1 = 2.;
   float shcosth2 = 2.;
   if (prop->firstShowerIdentifier() != 0  &&  prop->secondShowerIdentifier() != 0) {
      FATable<NavShower>::const_iterator shower1 = showers.find(prop->firstShowerIdentifier());
      FATable<NavShower>::const_iterator shower2 = showers.find(prop->secondShowerIdentifier());
      
      HepVector3D sh1 = shower1->attributes().momentum();  sh1 *= 1./sh1.mag();
      HepVector3D sh2 = shower2->attributes().momentum();  sh2 *= 1./sh2.mag();

      shxy = sh1.x() * sh2.x() + sh1.y() * sh2.y();
      shz = sh1.z() * sh2.z();

      shphi1 = shower1->attributes().phi();
      shphi2 = shower2->attributes().phi();

      shcosth1 = cos(shower1->attributes().theta());
      shcosth2 = cos(shower2->attributes().theta());
   }

   FATable<NavTrack>::const_iterator track1 = tracks.end();
   FATable<NavTrack>::const_iterator track2 = tracks.end();
   if (prop->firstTrackIdentifier() != 0  &&  prop->secondTrackIdentifier() != 0) {
      track1 = tracks.find(prop->firstTrackIdentifier());
      track2 = tracks.find(prop->secondTrackIdentifier());
   }
   else if (tracks.size() >= 2) {
      double firstp = 0.;
      double secondp = 0.;
      for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	   track_iter != tracks_end;
	   ++track_iter) {
	 double thisp = track_iter->pionFit()->momentum().mag();
	 if (thisp > firstp) {
	    secondp = firstp;
	    track2 = track1;

	    firstp = thisp;
	    track1 = track_iter;
	 }
	 else if (thisp > secondp) {
	    secondp = thisp;
	    track2 = track_iter;
	 }
      }
      p1 = (track1->pionHelix()->curvature() > 0. ? 1. : -1.) * firstp / eBeam;
      p2 = (track2->pionHelix()->curvature() > 0. ? 1. : -1.) * secondp / eBeam;
   }

   float pmiss = 1000.;
   float pnext = 1000.;
   float pfound = 1000.;
   float trxy = 2.;
   float trz = 2.;
   float trperp1 = 2.;
   float trperp2 = 2.;
   float trperp3 = 2.;
   float trperp4 = 2.;
   float d0miss = 1000.;
   float z0miss = 1000.;
   float trphi1 = 3.*M_PI;
   float trphi2 = 3.*M_PI;
   float trcosth1 = 2.;
   float trcosth2 = 2.;
   if (track1 != tracks_end  &&  track2 != tracks_end) {
      pmiss = (track1->pionFit()->momentum() + track2->pionFit()->momentum()).mag() / eBeam;

      FATable<NavShower>::const_iterator found_shower = showers.end();
      for (FATable<NavShower>::const_iterator shower_iter = showers.begin();
	   shower_iter != shower_end;
	   ++shower_iter) {
	 float ptry = (track1->pionFit()->momentum() +
		       track2->pionFit()->momentum() +
		       shower_iter->attributes().momentum()).mag() / eBeam;

	 if (!shower_iter->attributes().hot()  &&
	     shower_iter->noTrackMatch()       &&
	     shower_iter->noTrackMatchConReg()    ) {

	    if (fabs(2. - fabs(p1) - fabs(p2) - shower_iter->attributes().energy()/eBeam - ptry) < 
		fabs(2. - fabs(p1) - fabs(p2) - shower_iter->attributes().energy()/eBeam - pnext)) {
	       pnext = ptry;
	       pfound = shower_iter->attributes().energy()/eBeam;
	       found_shower = shower_iter;
	    } // end if this is a better choice
	 } // end if a neutral shower
      } // end loop over showers

      if (track1->pionHelix()->curvature() < 0.) p1 *= -1.;
      if (track2->pionHelix()->curvature() < 0.) p2 *= -1.;

      HepVector3D tr1 = track1->pionFit()->momentum();  tr1 *= 1./tr1.mag();
      HepVector3D tr2 = track2->pionFit()->momentum();  tr2 *= 1./tr2.mag();

      trxy = tr1.x() * tr2.x() + tr1.y() * tr2.y();
      trz = tr1.z() * tr2.z();

      d0miss = track1->pionHelix()->d0() + track2->pionHelix()->d0();
      z0miss = track1->pionHelix()->z0() - track2->pionHelix()->z0();

      trphi1 = track1->pionHelix()->phi0();
      trphi2 = track2->pionHelix()->phi0();

      // define trperps after you already have trphi1 and trphi2
      trperp1 = cos(trphi1) * cos(trphi2) + sin(trphi1) * sin(trphi2);

      HepVector3D extrap2 = HepVector3D(-0.033, 0., 0.) * (eBeam/4.750);
      trperp2 = (cos(trphi1) * (eBeam*cos(trphi2) - extrap2.x()) + sin(trphi1) * (eBeam*sin(trphi2) - extrap2.y()))
	 / sqrt(sqr(eBeam*cos(trphi2) - extrap2.x()) + sqr(eBeam*sin(trphi2) - extrap2.y()));

      if (found_shower != showers.end()) {
	 HepVector3D extrap3 = found_shower->attributes().momentum();
	 trperp3 = (cos(trphi1) * (eBeam*cos(trphi2) - extrap3.x()) + sin(trphi1) * (eBeam*sin(trphi2) - extrap3.y()))
	    / sqrt(sqr(eBeam*cos(trphi2) - extrap3.x()) + sqr(eBeam*sin(trphi2) - extrap3.y()));

	 HepVector3D extrap4 = extrap2 + found_shower->attributes().momentum();
	 trperp4 = (cos(trphi1) * (eBeam*cos(trphi2) - extrap4.x()) + sin(trphi1) * (eBeam*sin(trphi2) - extrap4.y()))
	    / sqrt(sqr(eBeam*cos(trphi2) - extrap4.x()) + sqr(eBeam*sin(trphi2) - extrap4.y()));
      }

      trcosth1 = track1->pionHelix()->cotTheta() / sqrt(sqr(track1->pionHelix()->cotTheta()) + 1.);
      trcosth2 = track2->pionHelix()->cotTheta() / sqrt(sqr(track2->pionHelix()->cotTheta()) + 1.);
   }

   float v[kNumEntries];
   v[k_d0Close] = d0close;
   v[k_z0Close] = z0close;
   v[k_eBeam] = eBeam;
   v[k_ntracks] = ntracks;
   v[k_e1] = e1;
   v[k_e2] = e2;
   v[k_p1] = p1;
   v[k_p2] = p2;
   v[k_pmiss] = pmiss;
   v[k_pnext] = pnext;
   v[k_pfound] = pfound;
   v[k_shxy] = shxy;
   v[k_shz] = shz;
   v[k_shphi1] = shphi1;
   v[k_shphi2] = shphi2;
   v[k_shcosth1] = shcosth1;
   v[k_shcosth2] = shcosth2;
   v[k_ephalf] = ephalf;
   v[k_epwhole] = epwhole;
   v[k_epdouble] = epdouble;
   v[k_trxy] = trxy;
   v[k_trz] = trz;
   v[k_d0miss] = d0miss;
   v[k_z0miss] = z0miss;
   v[k_trphi1] = trphi1;
   v[k_trphi2] = trphi2;
   v[k_trcosth1] = trcosth1;
   v[k_trcosth2] = trcosth2;
   v[k_trperp1] = trperp1;
   v[k_trperp2] = trperp2;
   v[k_trperp3] = trperp3;
   v[k_trperp4] = trperp4;

   v[k_rawntracks] = tracks.size();
   v[k_visen] = (prop->chargedEnergy() + prop->neutralEnergy());
   v[k_ccen] = prop->ccTotalEnergy();
   v[k_neue] = prop->neutralEnergy();
   v[k_q] = float(prop->netCharge());
   v[k_wrphi] = ci_perp;
   v[k_wz] = weighted_z;

   FAItem<EventType> type;
   extract(iFrame.record(Stream::kEvent), type);
   v[k_pass] = ((type->bhaGamAll() ? 1. : 0.) +
		(type->radLepAll() ? 10. : 0.) +
		(type->tauAll()    ? 100. : 0.) +
		(type->hadron()    ? 1000. : 0.) +
		(type->known()     ? 10000. : 0.));

   FAItem<TriggerL1Data> decision1;
   extract(iFrame.record(Stream::kEvent), decision1);

   FAItem<Level4Decision> decision4;
   extract(iFrame.record(Stream::kEvent), decision4);

   v[k_trigger] = (decision4->decision() +
		   (decision1->isTwoTrack() ? 10. : 0.) +
		   (decision1->isRandom()   ? 100. : 0.));

   if (m_lookForStupid.value()) {
      FAItem<Stupid> stupid;
      extract(iFrame.record(Stream::kEvent), stupid);
      int trax = 0;
      if (stupid->tracks0() > trax) trax = stupid->tracks0();
      if (stupid->tracks1() > trax) trax = stupid->tracks1();
      if (stupid->tracks2() > trax) trax = stupid->tracks2();
      if (stupid->tracks3() > trax) trax = stupid->tracks3();
      v[k_trax] = float(trax);
   }
   else {
      v[k_trax] = -1.;
   }

   v[k_twopions] = twopions;
   v[k_pi1x] = pi1.x();
   v[k_pi1y] = pi1.y();
   v[k_pi1z] = pi1.z();
   v[k_pi2x] = pi2.x();
   v[k_pi2y] = pi2.y();
   v[k_pi2z] = pi2.z();

   m_ntuple->fill(v);

   if (v[k_trigger] < 100  &&
       (ntracks>=2  &&  !(pfound<100  &&  pfound<0.1  &&  pnext<0.1  &&
			  2-abs(p1)-abs(p2)-pmiss < 2-abs(p1)-abs(p2)-pfound-pnext+0.05  &&
			  2-abs(p1)-abs(p2)-pmiss < 0.5)
	||  ntracks<2)  &&
       trperp1>-0.99998  &&  trperp2>-0.99998  &&  trperp4>-0.99998  &&
       ((v[k_rawntracks]>0 && fabs(z0close)<0.06) || v[k_rawntracks]==0)
      ) return ActionBase::kPassed;
   else return ActionBase::kFailed;
}

/*
ActionBase::ActionResult
Cuts::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Cuts::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/


DABoolean Cuts::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
				       KTHelix& a, KTHelix& b)
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

DABoolean Cuts::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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

//
// const member functions
//

//
// static member functions
//
