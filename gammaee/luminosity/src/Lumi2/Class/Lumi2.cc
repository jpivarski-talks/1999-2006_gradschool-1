// -*- C++ -*-
//
// Package:     Lumi2
// Module:      Lumi2
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Mar  7 14:43:59 EST 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Lumi2/Lumi2.h"
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
static const char* const kFacilityString = "Processor.Lumi2" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Lumi2::Lumi2( void )               // anal1
   : Processor( "Lumi2" )
   , m_haveL4("haveL4", this, true)
   , m_smearOrigin("smearOrigin", this, false)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Lumi2::event,    Stream::kEvent );
   //bind( &Lumi2::beginRun, Stream::kBeginRun );
   //bind( &Lumi2::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Lumi2::~Lumi2()                    // anal5
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
Lumi2::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Lumi2::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
Lumi2::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "l1tt", "l1rt", "l1el", "l1bb", "l1eb", "rawtk", "ntrack", "ebeam",
      "epe1", "epe2", "epp1", "epp2", "ccen", "neue", "chen", "l4dec",
      "sh1e", "sh1cos", "sh1phi", "sh1e925", "sh1wide", "sh1mat", "sh1ang",
      "sh2e", "sh2cos", "sh2phi", "sh2e925", "sh2wide", "sh2mat", "sh2ang",
      "sh3e", "sh3cos", "sh3phi", "sh3e925", "sh3wide", "sh3mat", "sh3ang",
      "sh4e", "sh4cos", "sh4phi", "sh4e925", "sh4wide", "sh4mat", "sh4ang",
      "m12", "m123", "m1234",
      "hits",
      "tr1p", "tr1cos", "tr1phi",
      "tr2p", "tr2cos", "tr2phi",
      "tr3p", "tr3cos", "tr3phi",
      "tr4p", "tr4cos", "tr4phi",
      "c12r", "c12z", "c12z2", "c12z3",
      "c13r", "c13z", "c13z2", "c13z3",
      "c14r", "c14z", "c14z2", "c14z3",
      "c23r", "c23z", "c23z2", "c23z3",
      "c24r", "c24z", "c24z2", "c24z3",
      "c34r", "c34z", "c34z2", "c34z3",
      "nvxfit",
      "v1chi", "v1x", "v1y", "v1z",
      "v2chi", "v2x", "v2y", "v2z",
      "v3chi", "v3x", "v3y", "v3z",
      "v4chi", "v4x", "v4y", "v4z",
      "pmiss", "d0close", "z0close", "myntk", "run"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Lumi2::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

//    FAItem<MCDecayTree> tree;
//    extract(iFrame.record(Stream::kEvent), tree, "Generator");
//    MCDecayTree::const_vIterator viter;
//    MCDecayTree::const_vIterator tree_vend = tree->vEnd();
//    MCDecayTree::const_pIterator piter;
//    MCDecayTree::const_pIterator tree_pend = tree->pEnd();
//    const MCParticlePropertyStore& mcppstore =
//       tree->topParticle().properties().store();
//    const int gamm = mcppstore.nameToQQId("gamma");
//    const int eplus = mcppstore.nameToQQId("e+");
//    const int eminus = mcppstore.nameToQQId("e-");
//    for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
//       report(SYSTEM, kFacilityString)
// 	 << "interaction: " << viter->position() << endl;
//    }
//    return ActionBase::kPassed;

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
   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);
   FAItem<Level4Decision> l4dec;
   if (m_haveL4.value()) extract(iFrame.record(Stream::kEvent), l4dec);
   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);
   FATable<VXFitVeeConversion> vxfit;
   extract(iFrame.record(Stream::kEvent), vxfit);

   HepVector3D bs = spot->center();
   if (m_smearOrigin.value()) {
      RandomGenerator& random(RandomGenerator::instance());
      bs.setX(random.gauss(0., 0.000325));
      bs.setY(random.gauss(0., 0.000006));
      if (random.flat() > 0.237)
	 bs.setZ(random.gauss(0., 0.671*M_SQRT2*0.01273));
      else
	 bs.setZ(random.gauss(0., 0.469*M_SQRT2*0.01273));
   }

   float v[kNumEntries];
   for (int i = 0;  i < kNumEntries;  i++) v[i] = -1000.;

   v[k_run] = head->run();
   v[k_l1tt] = l1trig->isTwoTrack();
   v[k_l1rt] = l1trig->isRadTau();
   v[k_l1el] = l1trig->isElTrack();
   v[k_l1bb] = l1trig->isBarrelBhabha();
   v[k_l1eb] = l1trig->isEndcapBhabha();
   v[k_rawtk] = tracks.size();
   v[k_ntrack] = props->nbChargedTracks();
   v[k_ebeam] = eBeam->value();
   v[k_epe1] = props->firstLargestEShower() / eBeam->value();
   v[k_epe2] = props->secondLargestEShower() / eBeam->value();
   v[k_epp1] = props->firstLargestPTrack() / eBeam->value();
   v[k_epp2] = props->secondLargestPTrack() / eBeam->value();
   v[k_ccen] = props->ccTotalEnergy() / 2. / eBeam->value();
   v[k_neue] = props->neutralEnergy() / 2. / eBeam->value();
   v[k_chen] = props->chargedEnergy() / 2. / eBeam->value();
   if (m_haveL4.value()) v[k_l4dec] = l4dec->decision();

   v[k_nvxfit] = vxfit.size();
   FATable<VXFitVeeConversion>::const_iterator vxfit_iter = vxfit.begin(), vxfit_end = vxfit.end();
   FATable<VXFitVeeConversion>::const_iterator vbest1, vbest2, vbest3, vbest4;
   vbest1 = vbest2 = vbest3 = vbest4 = vxfit_end;
   for (; vxfit_iter != vxfit_end;  ++vxfit_iter) {
      if (vbest1 == vxfit_end  ||  vbest1->fitChiSquare() > vxfit_iter->fitChiSquare()) {
	 vbest4 = vbest3;
	 vbest3 = vbest2;
	 vbest2 = vbest1;
	 vbest1 = vxfit_iter;
      }
      else if (vbest2 == vxfit_end  ||  vbest2->fitChiSquare() > vxfit_iter->fitChiSquare()) {
	 vbest4 = vbest3;
	 vbest3 = vbest2;
	 vbest2 = vxfit_iter;
      } 
      else if (vbest3 == vxfit_end  ||  vbest3->fitChiSquare() > vxfit_iter->fitChiSquare()) {
	 vbest4 = vbest3;
	 vbest3 = vxfit_iter;
      }
      else if (vbest4 == vxfit_end  ||  vbest4->fitChiSquare() > vxfit_iter->fitChiSquare()) {
	 vbest4 = vxfit_iter;
      }
   }
   if (vbest1 != vxfit_end) {
      v[k_v1chi] = vbest1->fitChiSquare();
      v[k_v1x]   = vbest1->guessVertex().x();
      v[k_v1y]   = vbest1->guessVertex().y();
      v[k_v1z]   = vbest1->guessVertex().z();
   }
   if (vbest2 != vxfit_end) {
      v[k_v2chi] = vbest2->fitChiSquare();
      v[k_v2x]   = vbest2->guessVertex().x();
      v[k_v2y]   = vbest2->guessVertex().y();
      v[k_v2z]   = vbest2->guessVertex().z();
   }
   if (vbest3 != vxfit_end) {
      v[k_v3chi] = vbest3->fitChiSquare();
      v[k_v3x]   = vbest3->guessVertex().x();
      v[k_v3y]   = vbest3->guessVertex().y();
      v[k_v3z]   = vbest3->guessVertex().z();
   }
   if (vbest4 != vxfit_end) {
      v[k_v4chi] = vbest4->fitChiSquare();
      v[k_v4x]   = vbest4->guessVertex().x();
      v[k_v4y]   = vbest4->guessVertex().y();
      v[k_v4z]   = vbest4->guessVertex().z();
   }

   FATable<NavShower>::const_iterator sh1, sh2, sh3, sh4, showers_end;
   sh1 = sh2 = sh3 = sh4 = showers_end = showers.end();
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
      if (!shower_iter->attributes().hot()  &&  shower_iter->attributes().status()) {
	 if (sh1 == showers_end  ||  shower_iter->attributes().energy() > sh1->attributes().energy()) {
	    sh4 = sh3;
	    sh3 = sh2;
	    sh2 = sh1;
	    sh1 = shower_iter;
	 }
	 else if (sh2 == showers_end  ||  shower_iter->attributes().energy() > sh2->attributes().energy()) {
	    sh4 = sh3;
	    sh3 = sh2;
	    sh2 = shower_iter;
	 }
	 else if (sh3 == showers_end  ||  shower_iter->attributes().energy() > sh3->attributes().energy()) {
	    sh4 = sh3;
	    sh3 = shower_iter;
	 }
	 else if (sh4 == showers_end  ||  shower_iter->attributes().energy() > sh4->attributes().energy()) {
	    sh4 = shower_iter;
	 }
      }
   }
   if (sh1 != showers_end) {
      v[k_sh1e] = sh1->attributes().energy();
      double d = sh1->attributes().distance();
      double th = sh1->attributes().theta();
      double ph = sh1->attributes().phi();
      v[k_sh1cos] = (d*cos(th) - bs.z()) /
	 sqrt(sqr(d*sin(th)*cos(ph) - bs.x()) +
	      sqr(d*sin(th)*sin(ph) - bs.y()) +
	      sqr(d*cos(th) - bs.z()));
      v[k_sh1phi] = atan2(d*sin(th)*sin(ph) - bs.y(),
			  d*sin(th)*cos(ph) - bs.x());
      v[k_sh1e925] = sh1->attributes().e9oe25();
      v[k_sh1wide] = sh1->attributes().width();
      v[k_sh1mat] = (sh1->noSimpleMatch() ? -1000. : sh1->simpleMatch()->pionFit()->momentum().mag() / eBeam->value());
      v[k_sh1ang] = (sh1->noSimpleMatch() ? -1000. : sh1->angSimpleMatch());
   }
   if (sh2 != showers_end) {
      v[k_sh2e] = sh2->attributes().energy();
      double d = sh2->attributes().distance();
      double th = sh2->attributes().theta();
      double ph = sh2->attributes().phi();
      v[k_sh2cos] = (d*cos(th) - bs.z()) /
	 sqrt(sqr(d*sin(th)*cos(ph) - bs.x()) +
	      sqr(d*sin(th)*sin(ph) - bs.y()) +
	      sqr(d*cos(th) - bs.z()));
      v[k_sh2phi] = atan2(d*sin(th)*sin(ph) - bs.y(),
			  d*sin(th)*cos(ph) - bs.x());
      v[k_sh2e925] = sh2->attributes().e9oe25();
      v[k_sh2wide] = sh2->attributes().width();
      v[k_sh2mat] = (sh2->noSimpleMatch() ? -1000. : sh2->simpleMatch()->pionFit()->momentum().mag() / eBeam->value());
      v[k_sh2ang] = (sh2->noSimpleMatch() ? -1000. : sh2->angSimpleMatch());
   }
   if (sh3 != showers_end) {
      v[k_sh3e] = sh3->attributes().energy();
      double d = sh3->attributes().distance();
      double th = sh3->attributes().theta();
      double ph = sh3->attributes().phi();
      v[k_sh3cos] = (d*cos(th) - bs.z()) /
	 sqrt(sqr(d*sin(th)*cos(ph) - bs.x()) +
	      sqr(d*sin(th)*sin(ph) - bs.y()) +
	      sqr(d*cos(th) - bs.z()));
      v[k_sh3phi] = atan2(d*sin(th)*sin(ph) - bs.y(),
			  d*sin(th)*cos(ph) - bs.x());
      v[k_sh3e925] = sh3->attributes().e9oe25();
      v[k_sh3wide] = sh3->attributes().width();
      v[k_sh3mat] = (sh3->noSimpleMatch() ? -1000. : sh3->simpleMatch()->pionFit()->momentum().mag() / eBeam->value());
      v[k_sh3ang] = (sh3->noSimpleMatch() ? -1000. : sh3->angSimpleMatch());
   }
   if (sh4 != showers_end) {
      v[k_sh4e] = sh4->attributes().energy();
      double d = sh4->attributes().distance();
      double th = sh4->attributes().theta();
      double ph = sh4->attributes().phi();
      v[k_sh4cos] = (d*cos(th) - bs.z()) /
	 sqrt(sqr(d*sin(th)*cos(ph) - bs.x()) +
	      sqr(d*sin(th)*sin(ph) - bs.y()) +
	      sqr(d*cos(th) - bs.z()));
      v[k_sh4phi] = atan2(d*sin(th)*sin(ph) - bs.y(),
			  d*sin(th)*cos(ph) - bs.x());
      v[k_sh4e925] = sh4->attributes().e9oe25();
      v[k_sh4wide] = sh4->attributes().width();
      v[k_sh4mat] = (sh4->noSimpleMatch() ? -1000. : sh4->simpleMatch()->pionFit()->momentum().mag() / eBeam->value());
      v[k_sh4ang] = (sh4->noSimpleMatch() ? -1000. : sh4->angSimpleMatch());
   }

   if (sh1 != showers_end  &&  sh2 != showers_end) {
      v[k_m12] = sqrt(sqr(sh1->attributes().energy() + sh2->attributes().energy()) -
		      (sh1->attributes().momentum() + sh2->attributes().momentum()).mag2());
   }
   if (sh1 != showers_end  &&  sh2 != showers_end  &&  sh3 != showers_end) {
      v[k_m123] = sqrt(sqr(sh1->attributes().energy() + sh2->attributes().energy() + sh3->attributes().energy()) -
		       (sh1->attributes().momentum() + sh2->attributes().momentum() + sh3->attributes().momentum()).mag2());
   }
   if (sh1 != showers_end  &&  sh2 != showers_end  &&  sh3 != showers_end  &&  sh4 != showers_end) {
      v[k_m1234] = sqrt(sqr(sh1->attributes().energy() + sh2->attributes().energy() + sh3->attributes().energy() + sh4->attributes().energy()) -
			(sh1->attributes().momentum() + sh2->attributes().momentum() + sh3->attributes().momentum() + sh4->attributes().momentum()).mag2());
   }

   v[k_hits] = 0.;
   v[k_d0close] = 1000.;
   v[k_z0close] = 1000.;
   v[k_myntk] = 0.;
   FATable<NavTrack>::const_iterator tr1, tr2, tr3, tr4, tracks_end;
   tr1 = tr2 = tr3 = tr4 = tracks_end = tracks.end();
   for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
      v[k_hits] += track_iter->pionQuality()->numberSubdetectorHits(TRSubdetectorLists::kDR3Axial) +
	 track_iter->pionQuality()->numberSubdetectorHits(TRSubdetectorLists::kDR3Stereo);

      KTHelix movetrack(*track_iter->pionHelix());
      double distance_moved;
      movetrack.moveToReferencePoint(bs,
				     distance_moved,
				     KTMoveControl::kDirectionEither);
      if (fabs(movetrack.d0()) < fabs(v[k_d0close])) v[k_d0close] = movetrack.d0();
      if (fabs(movetrack.z0()) < fabs(v[k_z0close])) v[k_z0close] = movetrack.z0();

      const UInt32 trackID ( track_iter->identifier() ) ;
      FAItem< TRTrackFitQuality > pionQuality( track_iter->pionQuality() );
      const DABoolean trackFitOK ( pionQuality->fit()       &&
				   !pionQuality->fitAbort()     );
      const double dof         ( pionQuality->degreesOfFreedom() ) ;
      const double reducedChi2 ( dof > 0 ? pionQuality->chiSquare()/dof : 0 ) ;
      const double hitFraction ( pionQuality->numberHitsExpected() > 0 ? 
				 pionQuality->ratioNumberHitsToExpected() : 0 );
      FAItem< TDKinematicFit > pion ( track_iter->pionFit() ) ;
      GeV          pTk ( pion->momentum().mag() ) ;
      const int    qTk ( pion->charge()<0 ? ceil( pion->charge() - 0.5 ) :
			 floor( pion->charge() + 0.5 ) ) ;
      const GeV eTk ( track_iter->trackShowerMatch().valid() ?
		      track_iter->trackShowerMatch()->matchedEnergy() : 0 ) ;
      FAItem< TRHelixFit > helix ( track_iter->pionHelix() ) ;
      const double adacd       ( fabs( helix->d0() ) ) ;
      const double az0         ( fabs( helix->position().z() ) ) ;
      const double phi0        ( helix->phi0() ) ;
      const double aCotTheta   ( fabs( helix->cotTheta() ) ) ;
      const double errCotTheta ( sqrt( fabs(
					  helix->errorMatrix()( KTHelix::kCotTheta, KTHelix::kCotTheta ) ) ) ) ;
      const double errz0       ( sqrt( fabs(
					  helix->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) ) ) ) ;
      const DABoolean thisTrackIsGood ( trackFitOK
					&& reducedChi2 < 100.0
					&& hitFraction > 0.5
					&& hitFraction < 1.2
					&& adacd       < 0.03
					&& az0         < 0.18
					&& pTk         > 0.01*eBeam->value()
					&& pTk         < 1.500*eBeam->value()
					&& aCotTheta   < 3.0424 // |cosTh|<0.95
					&& errCotTheta < 0.5
					&& errz0       < 0.25 ) ;
      if( thisTrackIsGood ) {
	 v[k_myntk]++;

	 if (tr1 == tracks_end  ||  track_iter->pionFit()->momentum().mag() > tr1->pionFit()->momentum().mag()) {
	    tr4 = tr3;
	    tr3 = tr2;
	    tr2 = tr1;
	    tr1 = track_iter;
	 }
	 else if (tr2 == tracks_end  ||  track_iter->pionFit()->momentum().mag() > tr2->pionFit()->momentum().mag()) {
	    tr4 = tr3;
	    tr3 = tr2;
	    tr2 = track_iter;
	 }
	 else if (tr3 == tracks_end  ||  track_iter->pionFit()->momentum().mag() > tr3->pionFit()->momentum().mag()) {
	    tr4 = tr3;
	    tr3 = track_iter;
	 }
	 else if (tr4 == tracks_end  ||  track_iter->pionFit()->momentum().mag() > tr4->pionFit()->momentum().mag()) {
	    tr4 = track_iter;
	 }
      }
   }
   if (tr1 != tracks_end) {
      v[k_tr1p] = tr1->pionFit()->momentum().mag() * (tr1->pionHelix()->curvature() > 0. ? 1. : -1.);
      v[k_tr1cos] = tr1->pionFit()->momentum().cosTheta();
      v[k_tr1phi] = tr1->pionFit()->momentum().phi();
   }
   if (tr2 != tracks_end) {
      v[k_tr2p] = tr2->pionFit()->momentum().mag() * (tr2->pionHelix()->curvature() > 0. ? 1. : -1.);
      v[k_tr2cos] = tr2->pionFit()->momentum().cosTheta();
      v[k_tr2phi] = tr2->pionFit()->momentum().phi();
   }
   if (tr3 != tracks_end) {
      v[k_tr3p] = tr3->pionFit()->momentum().mag() * (tr3->pionHelix()->curvature() > 0. ? 1. : -1.);
      v[k_tr3cos] = tr3->pionFit()->momentum().cosTheta();
      v[k_tr3phi] = tr3->pionFit()->momentum().phi();
   }
   if (tr4 != tracks_end) {
      v[k_tr4p] = tr4->pionFit()->momentum().mag() * (tr4->pionHelix()->curvature() > 0. ? 1. : -1.);
      v[k_tr4cos] = tr4->pionFit()->momentum().cosTheta();
      v[k_tr4phi] = tr4->pionFit()->momentum().phi();
   }

   if (tr1 != tracks_end  &&  tr2 != tracks_end) {
      double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
      KTHelix track(*tr1->pionHelix());
      KTHelix other(*tr2->pionHelix());
      if (calc_intersection(tx, ty, tz, tsig2z, tzsep, track, other)) {
	 double perp(sqrt(sqr(tx - bs.x()) + sqr(ty - bs.y())));
	 v[k_c12r] = perp;
	 v[k_c12z] = tzsep;
	 v[k_c12z2] = sqrt(tsig2z);
	 v[k_c12z3] = tz;
      }
   }
   if (tr1 != tracks_end  &&  tr3 != tracks_end) {
      double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
      KTHelix track(*tr1->pionHelix());
      KTHelix other(*tr3->pionHelix());
      if (calc_intersection(tx, ty, tz, tsig2z, tzsep, track, other)) {
	 double perp(sqrt(sqr(tx - bs.x()) + sqr(ty - bs.y())));
	 v[k_c13r] = perp;
	 v[k_c13z] = tzsep;
	 v[k_c13z2] = sqrt(tsig2z);
	 v[k_c13z3] = tz;
      }
   }
   if (tr1 != tracks_end  &&  tr4 != tracks_end) {
      double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
      KTHelix track(*tr1->pionHelix());
      KTHelix other(*tr4->pionHelix());
      if (calc_intersection(tx, ty, tz, tsig2z, tzsep, track, other)) {
	 double perp(sqrt(sqr(tx - bs.x()) + sqr(ty - bs.y())));
	 v[k_c14r] = perp;
	 v[k_c14z] = tzsep;
	 v[k_c14z2] = sqrt(tsig2z);
	 v[k_c14z3] = tz;
      }
   }
   if (tr2 != tracks_end  &&  tr3 != tracks_end) {
      double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
      KTHelix track(*tr2->pionHelix());
      KTHelix other(*tr3->pionHelix());
      if (calc_intersection(tx, ty, tz, tsig2z, tzsep, track, other)) {
	 double perp(sqrt(sqr(tx - bs.x()) + sqr(ty - bs.y())));
	 v[k_c23r] = perp;
	 v[k_c23z] = tzsep;
	 v[k_c23z2] = sqrt(tsig2z);
	 v[k_c23z3] = tz;
      }
   } 
   if (tr2 != tracks_end  &&  tr4 != tracks_end) {
     double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
      KTHelix track(*tr2->pionHelix());
      KTHelix other(*tr4->pionHelix());
      if (calc_intersection(tx, ty, tz, tsig2z, tzsep, track, other)) {
	 double perp(sqrt(sqr(tx - bs.x()) + sqr(ty - bs.y())));
	 v[k_c24r] = perp;
	 v[k_c24z] = tzsep;
	 v[k_c24z2] = sqrt(tsig2z);
	 v[k_c24z3] = tz;
      }
   }
   if (tr3 != tracks_end  &&  tr4 != tracks_end) {
      double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
      KTHelix track(*tr3->pionHelix());
      KTHelix other(*tr4->pionHelix());
      if (calc_intersection(tx, ty, tz, tsig2z, tzsep, track, other)) {
	 double perp(sqrt(sqr(tx - bs.x()) + sqr(ty - bs.y())));
	 v[k_c34r] = perp;
	 v[k_c34z] = tzsep;
	 v[k_c34z2] = sqrt(tsig2z);
	 v[k_c34z3] = tz;
      }
   }

   if (tr1 != tracks_end  &&  tr2 != tracks_end) {
      v[k_pmiss] = (tr1->pionFit()->momentum() + tr2->pionFit()->momentum()).mag() / eBeam->value();
   }

   m_ntuple->fill(v);
   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
Lumi2::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Lumi2::endRun( Frame& iFrame )         // anal4 equiv.
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

DABoolean Lumi2::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean Lumi2::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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
