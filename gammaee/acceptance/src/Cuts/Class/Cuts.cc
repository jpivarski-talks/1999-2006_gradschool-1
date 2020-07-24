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
// Created:     Mon Apr 12 15:11:11 EDT 2004
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
#include "TriggerInfoProd/TriggerInfo.h"
#include "MagField/MagneticField.h"
#include "CleoDB/DBEventHeader.h"

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
   , m_triggerInfo("triggerInfo", this, true)
   , m_mcInfo("mcInfo", this, true)
   , m_res("res", this, 0)
   , m_tracks(0)
   , m_showers(0)
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
      "t1had", "t1rad", "t1el", "t1tt",
      "tracks", "visen", "ccen",
      "p2", "e1",
      "ci", "wz", "d0close", "z0close",
      "run", "ebeam", "neue", "q",
      "axial", "stereo", "cblo", "cbmd",
      "rawtk", "pmiss", "tr1", "tr2", "trperp1", "trperp2", "e2",
      "shperp", "shdot",
      "l4dec", "l4tracks",
      "mctype", // "mctrack", "mcfid",
      "wpz", "cotthp",
      "nbunch", "bbunch",
      "cvisen", "cccen", "cneue",
      "avisen", "accen", "aneue"
   };

// nt/cuts $1 (rawtk>=2&&!(pmiss<0.025&&abs(2-tr1-tr2-pmiss)<0.2)).or.rawtk<2
// nt/cuts $2 trperp1>-0.999998&&trperp2>-0.999998
// nt/cuts $3 sqrt((e1-1)**2+(e2-1)**2)>0.1

   m_ntuple = iHistoManager.ntuple(
      1, "ntuple", kNumEntries, 262144, label);

//    // L4 track conditions
//    m_track_originUsed = iHistoManager.histogram("track originUsed", 2, -0.5, 1.5);
//    m_track_hitfrac = iHistoManager.histogram("track hitfrac", 100, 0., 0.8);
//    m_track_cosTheta = iHistoManager.histogram("track seed abscosTheta (cut above bin 93)", 100, 0., 1.);
//    m_track_seedredchi2 = iHistoManager.histogram("track seed reducedChi2", 100, 0., 40.);
//    m_track_seedd0 = iHistoManager.histogram("track seed absd0", 100, 0., 0.05);
//    m_track_seedz0 = iHistoManager.histogram("track seed absz0", 100, 0., 0.3);

//    // EventProperties track conditions
//    m_track_fit = iHistoManager.histogram("track fit", 2, -0.5, 1.5);
//    m_track_fitAbort = iHistoManager.histogram("track fitAbort", 2, -0.5, 1.5);
//    m_track_reducedchi2 = iHistoManager.histogram("track pion reducedChi2", 100, 0., 200.);
//    m_track_layerfrac_low = iHistoManager.histogram("track layerfrac low", 100, 0., 1.);
//    m_track_layerfrac_high = iHistoManager.histogram("track layerfrac high", 100, 0., 2.4);
//    m_track_piond0 = iHistoManager.histogram("track pion absd0", 100, 0., 0.06);
//    m_track_pionz = iHistoManager.histogram("track pion absz", 100, 0., 0.36);
//    m_track_poeB_low = iHistoManager.histogram("track povereBeam low", 100, 0., 0.02);
//    m_track_poeB_high = iHistoManager.histogram("track povereBeam high", 100, 0., 3.);
//    m_track_cotTheta = iHistoManager.histogram("track pion absCotTheta", 100, 0., 2.*3.0424);
//    m_track_errcotTheta = iHistoManager.histogram("track errCotTheta", 100, 0., 1.);
//    m_track_errZ0 = iHistoManager.histogram("track errZ0", 100, 0., 0.5);

//    // Closest Intersection conditions
//    m_track_invcurvature = iHistoManager.histogram("track invcurvature", 100, 0., 0.84);
//    m_track_nullerrmat = iHistoManager.histogram("track nullerrmat", 2, -0.5, 1.5);

//    // EventProperties shower conditions
//    m_shower_status = iHistoManager.histogram("shower status", 2, -0.5, 1.5);
//    m_shower_energy = iHistoManager.histogram("shower energy / eBeam", 100, 0., 0.02);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Cuts::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   float v[kNumEntries];
   for (int i = 0;  i < kNumEntries;  i++) v[i] = -3000.;

   if (m_mcInfo.value()) {
      FAItem<MCDecayTree> tree;
      extract(iFrame.record(Stream::kEvent), tree);
      MCDecayTree::const_vIterator viter;
      MCDecayTree::const_vIterator tree_vend = tree->vEnd();
      MCDecayTree::const_pIterator piter;
      MCDecayTree::const_pIterator tree_pend = tree->pEnd();

      const MCParticlePropertyStore& mcppstore =
	 tree->topParticle().properties().store();

      const int ups1 = mcppstore.nameToQQId("Upsilon");
      const int ups2 = mcppstore.nameToQQId("Upsilon(2S)");
      const int ups3 = mcppstore.nameToQQId("Upsilon(3S)");
      const int eplus = mcppstore.nameToQQId("e+");
      const int eminus = mcppstore.nameToQQId("e-");
      const int muplus = mcppstore.nameToQQId("mu+");
      const int muminus = mcppstore.nameToQQId("mu-");
      const int tauplus = mcppstore.nameToQQId("tau+");
      const int tauminus = mcppstore.nameToQQId("tau-");
      const int gamm = mcppstore.nameToQQId("gamma");
      const int piplus = mcppstore.nameToQQId("pi+");
      const int piminus = mcppstore.nameToQQId("pi-");
      const int kplus = mcppstore.nameToQQId("K+");
      const int kminus = mcppstore.nameToQQId("K-");
      const int pplus = mcppstore.nameToQQId("p+");
      const int pminus = mcppstore.nameToQQId("anti-p-");
      const int dplus = mcppstore.nameToQQId("deuteron");
      const int dminus = mcppstore.nameToQQId("anti-deuteron");
      const int glue = mcppstore.nameToQQId("string");

      bool really_prompt = true;

      bool ups_to_ee = false;
      bool ups_to_mumu = false;
      bool ups_to_tautau = false;
      int ups_to_lepphotons = 0;
      bool ups_to_gluons = false;
      bool ups_to_ggpho = false;
      bool ups_isnt_123 = false;
      bool truly_leptonic = false;
      for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
	 bool bigthree = (viter->parent().properties().QQId() == ups1  ||
			  viter->parent().properties().QQId() == ups2  ||
			  viter->parent().properties().QQId() == ups3    );

	 bool anybbbar = (viter->parent().properties().QQId() == 95  ||
			  viter->parent().properties().QQId() == 97  ||
			  viter->parent().properties().QQId() == 98  ||
			  viter->parent().properties().QQId() == 100  ||
			  viter->parent().properties().QQId() == 101  ||
			  viter->parent().properties().QQId() == 102  ||
			  viter->parent().properties().QQId() == 103  ||
			  viter->parent().properties().QQId() == 104  ||
			  viter->parent().properties().QQId() == 105  ||
			  viter->parent().properties().QQId() == 577  ||
			  viter->parent().properties().QQId() == 578  ||
			  viter->parent().properties().QQId() == 579  ||
			  viter->parent().properties().QQId() == 580  ||
			  viter->parent().properties().QQId() == 581  ||
			  viter->parent().properties().QQId() == 582  ||
			  viter->parent().properties().QQId() == 584  ||
			  viter->parent().properties().QQId() == 585  ||
			  viter->parent().properties().QQId() == 586    );
	 
	 assert(m_res.value() == 1  ||  m_res.value() == 2  ||  m_res.value() == 3);
	 bool prompt_(false);
	 if (viter->parent().properties().QQId() == ups1  &&  m_res.value() == 1) prompt_ = true;
	 if (viter->parent().properties().QQId() == ups2  &&  m_res.value() == 2) prompt_ = true;
	 if (viter->parent().properties().QQId() == ups3  &&  m_res.value() == 3) prompt_ = true;

	 if (anybbbar  &&  !prompt_) really_prompt = false;

	 if (anybbbar) {
	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();

	    bool eplus_(false), eminus_(false), muplus_(false);
	    bool muminus_(false), tauplus_(false), tauminus_(false);
	    int photons_(0);
	    bool glue_(false);
	    bool ups1_(false);
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	       if (chiter->properties().QQId() == eplus) eplus_ = true;
	       if (chiter->properties().QQId() == eminus) eminus_ = true;
	       if (chiter->properties().QQId() == muplus) muplus_ = true;
	       if (chiter->properties().QQId() == muminus) muminus_ = true;
	       if (chiter->properties().QQId() == tauplus) tauplus_ = true;
	       if (chiter->properties().QQId() == tauminus) tauminus_ = true;
	       if (chiter->properties().QQId() == gamm) photons_++;
	       if (chiter->properties().QQId() == glue) glue_ = true;
	       if (chiter->properties().QQId() == ups1) ups1_ = true;
	    } // end loop over children
	    if (bigthree && eplus_ && eminus_) ups_to_ee = true;
	    if (bigthree && muplus_ && muminus_) ups_to_mumu = true;
	    if (bigthree && tauplus_ && tauminus_) ups_to_tautau = true;
	    if (ups_to_ee  ||  ups_to_mumu  ||  ups_to_tautau) ups_to_lepphotons = photons_;
	    if (glue_) {
	       if (photons_ > 0) ups_to_ggpho = true;
	       else ups_to_gluons = true;
	    } // end if we saw a glue string
	    if (viter->parent().properties().QQId() == 100) {
	       if (!(photons_ == 1  &&  ups1_)) ups_to_gluons = true;
	    } // end if it's a chi_b0(1P)
	    if (ups_to_gluons  &&  !bigthree) ups_isnt_123 = true;
	    if (prompt_  &&  ((eplus_ && eminus_)  ||
			      (muplus_ && muminus_)  ||
			      (tauplus_ && tauminus_)  )) truly_leptonic = true;

	 } // end if bbbar
      } // end loop over vertices

      if (really_prompt) return ActionBase::kFailed;

      v[k_mctype] = 0.;
      if (ups_to_ee) v[k_mctype] = 10.;
      if (ups_to_mumu) v[k_mctype] = 20.;
      if (ups_to_tautau) v[k_mctype] = 30.;
      if (ups_to_ee  ||  ups_to_mumu  ||  ups_to_tautau) {
	 v[k_mctype] += ups_to_lepphotons;
      }
      if (ups_to_ggpho) v[k_mctype] = 40.;
      if (ups_to_gluons) {
	 v[k_mctype] = 50.;
	 if (ups_isnt_123) v[k_mctype] = 51.;
      }
      v[k_mctype] *= (truly_leptonic ? -1 : 1);

      assert(v[k_mctype] != 0);
      assert((ups_to_ee ? 1 : 0) +
	     (ups_to_mumu ? 1 : 0) +
	     (ups_to_tautau ? 1 : 0) +
	     (ups_to_ggpho ? 1 : 0) +
	     (ups_to_gluons ? 1 : 0)
	     == 1);

//       OLD CLASSIFICATION
//       if (ups_to_leptons) v[k_mctype] = 1.;
//       else if (ups_to_taus) v[k_mctype] = 2.;
//       else v[k_mctype] = 3.;

//       int charticles = 0;
//       int fiducicles = 0;
//       for (piter = tree->pBegin();  piter != tree_pend;  ++piter) {
// 	 if (piter->properties().QQId() == eplus    ||
// 	     piter->properties().QQId() == eminus   ||
// 	     piter->properties().QQId() == muplus   ||
// 	     piter->properties().QQId() == muminus  ||
// 	     piter->properties().QQId() == piplus   ||
// 	     piter->properties().QQId() == piminus  ||
// 	     piter->properties().QQId() == kplus    ||
// 	     piter->properties().QQId() == kminus   ||
// 	     piter->properties().QQId() == pplus    ||
// 	     piter->properties().QQId() == pminus   ||
// 	     piter->properties().QQId() == dplus    ||
// 	     piter->properties().QQId() == dminus     ) {
// 	    HepPoint3D source = piter->productionVertex()->position();
// 	    if (source.perp() < 0.70) {
// 	       bool good = source.perp() < 0.015  &&  fabs(source.z()) < 0.05;
// 	       if (piter->dead()) {
// 		  HepPoint3D sink = piter->deathVertex()->position();
// 		  good = good &&  sink.perp() > 0.36;
// 	       }
// 	       good = good &&  fabs(cos(piter->momentum().theta())) < 0.928;
	    
// 	       charticles++;
// 	       if (good) fiducicles++;
// 	    } // end if inside the DR at least
// 	 } // end switch
//       } // end loop over particles

//       v[k_mctrack] = charticles;
//       v[k_mcfid] = fiducicles;

      FAItem<BunchDecision> m_bunchDecision;
      extract(iFrame.record(Stream::kEvent), m_bunchDecision);

      v[k_nbunch] = m_bunchDecision->numberOfTestedBunches();
      v[k_bbunch] = m_bunchDecision->bestBunchNumber();
   } // end if this is mc
   else {
      v[k_mctype] = -1.;
//       v[k_mctrack] = -1.;
//       v[k_mcfid] = -1;
   }

   FAItem<TriggerL1Data> triggerDecision;
   extract(iFrame.record(Stream::kEvent), triggerDecision);

// NO!!!
//    if (!triggerDecision->isHadron()   &&
//        !triggerDecision->isRadTau()   &&
//        !triggerDecision->isElTrack()  &&
//        !triggerDecision->isTwoTrack()   ) return ActionBase::kFailed;

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();
   FATable<NavTrack>::const_iterator track_iter, other_iter;
   
   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
      m_tracks++;
//       if (m_tracks <= 100000) {
// 	 m_track_originUsed->fill(track_iter->seedQuality()->originUsed());
// 	 if (track_iter->seedQuality()->numberHitsExpected() <= 0) m_track_hitfrac->fill(0.);
// 	 else m_track_hitfrac->fill(track_iter->seedQuality()->numberHits() / double(track_iter->seedQuality()->numberHitsExpected()));
// 	 m_track_cosTheta->fill(sqrt(1. - 1./(1.+sqr(track_iter->seedTrack()->cotTheta()))));
// 	 if (track_iter->seedQuality()->degreesOfFreedom() <= 0) m_track_seedredchi2->fill(1000.);
// 	 else m_track_seedredchi2->fill(track_iter->seedQuality()->chiSquare() / double(track_iter->seedQuality()->degreesOfFreedom()));
// 	 m_track_seedd0->fill(fabs(track_iter->seedTrack()->d0()));
// 	 m_track_seedz0->fill(fabs(track_iter->seedTrack()->z0()));

// 	 m_track_fit->fill(track_iter->pionQuality()->fit());
// 	 m_track_fitAbort->fill(track_iter->pionQuality()->fitAbort());
// 	 if (track_iter->pionQuality()->degreesOfFreedom() <= 0) m_track_reducedchi2->fill(0.);
// 	 else m_track_reducedchi2->fill(track_iter->pionQuality()->chiSquare() / double(track_iter->pionQuality()->degreesOfFreedom()));
// 	 if (track_iter->seedQuality()->numberHitsExpected() <= 0) {
// 	    m_track_layerfrac_low->fill(0.);
// 	    m_track_layerfrac_high->fill(0.);
// 	 } else {
// 	    m_track_layerfrac_low->fill(track_iter->seedQuality()->numberLayers() / double(track_iter->seedQuality()->numberHitsExpected()));
// 	    m_track_layerfrac_high->fill(track_iter->seedQuality()->numberLayers() / double(track_iter->seedQuality()->numberHitsExpected()));
// 	 }
// 	 m_track_piond0->fill(fabs(track_iter->pionHelix()->d0()));
// 	 m_track_pionz->fill(fabs(track_iter->pionHelix()->position().z()));
// 	 m_track_poeB_low->fill(track_iter->pionFit()->momentum().mag() / eBeam->value());
// 	 m_track_poeB_high->fill(track_iter->pionFit()->momentum().mag() / eBeam->value());
// 	 m_track_cotTheta->fill(fabs(track_iter->pionHelix()->cotTheta()));
// 	 m_track_errcotTheta->fill(sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))));
// 	 m_track_errZ0->fill(sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))));

// 	 m_track_invcurvature->fill(1./fabs(track_iter->pionHelix()->curvature()));
// 	 m_track_nullerrmat->fill(track_iter->pionHelix()->hasNullErrorMatrix());
//       } // end if we haven't collected enough
   } // end loop over tracks (histogramming)

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator showers_end = showers.end();
   FATable<NavShower>::const_iterator shower_iter;
   FATable<NavShower>::const_iterator shower1(showers_end), shower2(showers_end);

   double e1(0.), e2(0.);
   for (shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
      if (!shower_iter->attributes().hot()   &&
	  shower_iter->attributes().status()   ) {
	 double thise = shower_iter->attributes().energy();
	 if (thise > e1) {
	    e2 = e1;
	    shower2 = shower1;
	    
	    e1 = thise;
	    shower1 = shower_iter;
	 }
	 else if (thise > e2) {
	    e2 = thise;
	    shower2 = shower_iter;
	 }
      }

      m_showers++;
//       if (m_showers <= 100000) {
// 	 m_shower_status->fill(shower_iter->attributes().status());
// 	 m_shower_energy->fill(shower_iter->attributes().energy() / eBeam->value());
//       } // end if we haven't collected enough
   } // end loop over showers (histogramming)
   e1 /= eBeam->value();
   e2 /= eBeam->value();

   FAItem<MagneticField> bField;
   extract(iFrame.record(Stream::kStartRun), bField);

   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   v[k_t1had] = triggerDecision->isHadron();
   v[k_t1rad] = triggerDecision->isRadTau();
   v[k_t1el] = triggerDecision->isElTrack();
   v[k_t1tt] = triggerDecision->isTwoTrack();

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   v[k_tracks] = float(props->nbChargedTracks());
   v[k_visen] = (props->neutralEnergy() + props->chargedEnergy()) / 2. / eBeam->value();
   v[k_ccen] = props->ccTotalEnergy() / 2. / eBeam->value();
   v[k_p2] = props->secondLargestPTrack() / eBeam->value();
   v[k_e1] = props->firstLargestEShower() / eBeam->value();

   v[k_d0close] = 1000.;
   v[k_z0close] = 1000.;
   v[k_ci] = 1000.;
   double znumer = 0.;
   double zdenom = 0.;
   v[k_wpz] = 0.;
   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
      KTHelix movetrack(*track_iter->pionHelix());
      double distance_moved;
      movetrack.moveToReferencePoint(spot->center(),
				     distance_moved,
				     KTMoveControl::kDirectionEither);
      if (fabs(movetrack.d0()) < fabs(v[k_d0close])) v[k_d0close] = movetrack.d0();
      if (fabs(movetrack.z0()) < fabs(v[k_z0close])) v[k_z0close] = movetrack.z0();

      if (! track_iter->seedQuality()->originUsed()            &&
	  ! track_iter->pionQuality()->fitAbort()              &&
	  1./fabs(track_iter->pionHelix()->curvature()) > 0.42  &&
	  ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {

	 if (sqrt(fabs(track_iter->pionFit()->errorMatrix()(
			  KTKinematicData::kPz, KTKinematicData::kPz))) < 1.) {
	    v[k_wpz] += track_iter->pionFit()->pz();
	 }

	 // Secondary track loop to calculate pairwise intersections
	 for (other_iter = track_iter;  other_iter != tracks_end;  ++other_iter) {
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
		  double z_uncert2(tsig2z + sqr(tzsep) +
				   sqr(tx - spot->center().x()) +
				   sqr(ty - spot->center().y()));

		  if (perp < v[k_ci]) v[k_ci] = perp;
		  znumer += tz / z_uncert2;
		  zdenom += 1. / z_uncert2;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over tracks

   v[k_wz] = 1000.;
   if (zdenom != 0.) {
      v[k_wz] = znumer / zdenom;
      v[k_wz] -= spot->center().z();
   }   

   FAItem<DBEventHeader> dbhead;
   extract(iFrame.record(Stream::kEvent), dbhead);
//   cout << "RUNEVENT " << dbhead->run() << " " << dbhead->number() << endl;

   v[k_run] = dbhead->run();
   v[k_ebeam] = eBeam->value();
   v[k_neue] = props->neutralEnergy() / 2. / eBeam->value();
   v[k_q] = float(props->netCharge());

   if (m_triggerInfo.value()) {
      FAItem<TriggerInfo> triggerInfo;
      extract(iFrame.record(Stream::kEvent), triggerInfo);
      v[k_axial] = triggerInfo->axial();
      v[k_stereo] = triggerInfo->stereo();
      v[k_cblo] = triggerInfo->cblo();
      v[k_cbmd] = triggerInfo->cbmd();
   }
   else {
      v[k_axial] = -1.;
      v[k_stereo] = -1.;
      v[k_cblo] = -1.;
      v[k_cbmd] = -1.;
   }

   // Now some variables copied over from Cuts
   // "rawtk", "pmiss", "tr1", "tr2", "trperp1", "trperp2", "e2"
   v[k_rawtk] = tracks.size();

   FATable<NavTrack>::const_iterator track1(tracks_end), track2(tracks_end);
   if (props->nbChargedTracks() >= 2  &&  props->firstTrackIdentifier() != 0  &&  props->secondTrackIdentifier() != 0) {
      track1 = tracks.find(props->firstTrackIdentifier());
      track2 = tracks.find(props->secondTrackIdentifier());
   }
   else if (tracks.size() >= 2) {
      double firstp(0.), secondp(0.);
      for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
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
   }
   if (track1 != tracks_end  &&  track2 != tracks_end) {
      v[k_pmiss] = (track1->pionFit()->momentum() + track2->pionFit()->momentum()).mag() / eBeam->value();
      v[k_tr1] = track1->pionFit()->momentum().mag() / eBeam->value();
      v[k_tr2] = track2->pionFit()->momentum().mag() / eBeam->value();

      double phi1 = track1->pionHelix()->phi0();
      double phi2 = track2->pionHelix()->phi0();
      v[k_trperp1] = cos(phi1)*cos(phi2) + sin(phi1)*sin(phi2);
      HepVector3D extrap2 = HepVector3D(-0.033, 0., 0.) * (eBeam->value()/4.750);
      v[k_trperp2] = (cos(phi1) * (eBeam->value()*cos(phi2) - extrap2.x()) + sin(phi1) * (eBeam->value()*sin(phi2) - extrap2.y()))
	 / sqrt(sqr(eBeam->value()*cos(phi2) - extrap2.x()) + sqr(eBeam->value()*sin(phi2) - extrap2.y()));

      if (track1->pionHelix()->curvature() > 0.  &&  track2->pionHelix()->curvature() < 0.) {
	 v[k_cotthp] = track1->pionHelix()->cotTheta();
      }
      else if (track1->pionHelix()->curvature() < 0.  &&  track2->pionHelix()->curvature() > 0.) {
	 v[k_cotthp] = track2->pionHelix()->cotTheta();
      }
   }
   v[k_e2] = props->secondLargestEShower() / eBeam->value();

   if (shower1 != showers_end  &&  shower2 != showers_end) {
      double phi1 = shower1->attributes().phi();
      double phi2 = shower2->attributes().phi();

      v[k_shperp] = cos(phi1)*cos(phi2) + sin(phi1)*sin(phi2);
      v[k_shdot] = shower1->attributes().momentum().dot(shower2->attributes().momentum())
	 / shower1->attributes().energy() / shower2->attributes().energy();
   }

   FAItem<Level4Decision> l4dec;
   extract(iFrame.record(Stream::kEvent), l4dec);
   v[k_l4dec] = l4dec->decision();
   v[k_l4tracks] = 0.;
   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
       if (
 	  // L4 conditions
 	  !track_iter->seedQuality()->originUsed()                                                           &&
 	  track_iter->seedQuality()->numberHitsExpected() > 0                                                &&
 	  track_iter->seedQuality()->numberHits() / double(track_iter->seedQuality()->numberHitsExpected()) >= 0.4   &&
 	  sqrt(1. - 1./(1.+sqr(track_iter->seedTrack()->cotTheta()))) <= 0.93                                &&
 	  track_iter->seedQuality()->chiSquare() < track_iter->seedQuality()->degreesOfFreedom() * 20.       &&
 	  fabs(track_iter->seedTrack()->d0()) < 0.025                                                        &&
 	  fabs(track_iter->seedTrack()->z0()) < 0.15                                                            ) {
	  v[k_l4tracks]++;
       }
   }

//    if (m_mcInfo.value()) {
//       FAItem<MCDecayTree> tree;
//       extract(iFrame.record(Stream::kEvent), tree);
//       MCDecayTree::const_vIterator viter;
//       MCDecayTree::const_vIterator tree_vend = tree->vEnd();
//       MCDecayTree::const_pIterator piter;
//       MCDecayTree::const_pIterator tree_pend = tree->pEnd();

//       const MCParticlePropertyStore& mcppstore =
// 	 tree->topParticle().properties().store();

//       const int ups1 = mcppstore.nameToQQId("Upsilon");
//       const int ups2 = mcppstore.nameToQQId("Upsilon(2S)");
//       const int ups3 = mcppstore.nameToQQId("Upsilon(3S)");
//       const int eplus = mcppstore.nameToQQId("e+");
//       const int eminus = mcppstore.nameToQQId("e-");
//       const int muplus = mcppstore.nameToQQId("mu+");
//       const int muminus = mcppstore.nameToQQId("mu-");
//       const int tauplus = mcppstore.nameToQQId("tau+");
//       const int tauminus = mcppstore.nameToQQId("tau-");
//       const int gamm = mcppstore.nameToQQId("gamma");
//       const int piplus = mcppstore.nameToQQId("pi+");
//       const int piminus = mcppstore.nameToQQId("pi-");
//       const int kplus = mcppstore.nameToQQId("K+");
//       const int kminus = mcppstore.nameToQQId("K-");
//       const int pplus = mcppstore.nameToQQId("p+");
//       const int pminus = mcppstore.nameToQQId("anti-p-");
//       const int dplus = mcppstore.nameToQQId("deuteron");
//       const int dminus = mcppstore.nameToQQId("anti-deuteron");
//       const int glue = mcppstore.nameToQQId("string");

//       bool ups_to_ee = false;
//       bool ups_to_mumu = false;
//       bool ups_to_tautau = false;
//       int ups_to_lepphotons = 0;
//       bool ups_to_gluons = false;
//       bool ups_to_ggpho = false;
//       bool ups_isnt_123 = false;
//       bool truly_leptonic = false;
//       for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
// 	 bool bigthree = (viter->parent().properties().QQId() == ups1  ||
// 			  viter->parent().properties().QQId() == ups2  ||
// 			  viter->parent().properties().QQId() == ups3    );

// 	 bool anybbbar = (viter->parent().properties().QQId() == 95  ||
// 			  viter->parent().properties().QQId() == 97  ||
// 			  viter->parent().properties().QQId() == 98  ||
// 			  viter->parent().properties().QQId() == 100  ||
// 			  viter->parent().properties().QQId() == 101  ||
// 			  viter->parent().properties().QQId() == 102  ||
// 			  viter->parent().properties().QQId() == 103  ||
// 			  viter->parent().properties().QQId() == 104  ||
// 			  viter->parent().properties().QQId() == 105  ||
// 			  viter->parent().properties().QQId() == 577  ||
// 			  viter->parent().properties().QQId() == 578  ||
// 			  viter->parent().properties().QQId() == 579  ||
// 			  viter->parent().properties().QQId() == 580  ||
// 			  viter->parent().properties().QQId() == 581  ||
// 			  viter->parent().properties().QQId() == 582  ||
// 			  viter->parent().properties().QQId() == 584  ||
// 			  viter->parent().properties().QQId() == 585  ||
// 			  viter->parent().properties().QQId() == 586    );
	 
// 	 assert(m_res.value() == 1  ||  m_res.value() == 2  ||  m_res.value() == 3);
// 	 bool prompt_(false);
// 	 if (viter->parent().properties().QQId() == ups1  &&  m_res.value() == 1) prompt_ = true;
// 	 if (viter->parent().properties().QQId() == ups2  &&  m_res.value() == 2) prompt_ = true;
// 	 if (viter->parent().properties().QQId() == ups3  &&  m_res.value() == 3) prompt_ = true;

// 	 if (anybbbar) {
// 	    MCVertex::const_pIterator chiter;
// 	    MCVertex::const_pIterator viter_pend = viter->pEnd();

// 	    bool eplus_(false), eminus_(false), muplus_(false);
// 	    bool muminus_(false), tauplus_(false), tauminus_(false);
// 	    int photons_(0);
// 	    bool glue_(false);
// 	    bool ups1_(false);
// 	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
// 	       if (chiter->properties().QQId() == eplus) eplus_ = true;
// 	       if (chiter->properties().QQId() == eminus) eminus_ = true;
// 	       if (chiter->properties().QQId() == muplus) muplus_ = true;
// 	       if (chiter->properties().QQId() == muminus) muminus_ = true;
// 	       if (chiter->properties().QQId() == tauplus) tauplus_ = true;
// 	       if (chiter->properties().QQId() == tauminus) tauminus_ = true;
// 	       if (chiter->properties().QQId() == gamm) photons_++;
// 	       if (chiter->properties().QQId() == glue) glue_ = true;
// 	       if (chiter->properties().QQId() == ups1) ups1_ = true;
// 	    } // end loop over children
// 	    if (bigthree && eplus_ && eminus_) ups_to_ee = true;
// 	    if (bigthree && muplus_ && muminus_) ups_to_mumu = true;
// 	    if (bigthree && tauplus_ && tauminus_) ups_to_tautau = true;
// 	    if (ups_to_ee  ||  ups_to_mumu  ||  ups_to_tautau) ups_to_lepphotons = photons_;
// 	    if (glue_) {
// 	       if (photons_ > 0) ups_to_ggpho = true;
// 	       else ups_to_gluons = true;
// 	    } // end if we saw a glue string
// 	    if (viter->parent().properties().QQId() == 100) {
// 	       if (!(photons_ == 1  &&  ups1_)) ups_to_gluons = true;
// 	    } // end if it's a chi_b0(1P)
// 	    if (ups_to_gluons  &&  !bigthree) ups_isnt_123 = true;
// 	    if (prompt_  &&  ((eplus_ && eminus_)  ||
// 			      (muplus_ && muminus_)  ||
// 			      (tauplus_ && tauminus_)  )) truly_leptonic = true;

// 	 } // end if bbbar
//       } // end loop over vertices

//       v[k_mctype] = 0.;
//       if (ups_to_ee) v[k_mctype] = 10.;
//       if (ups_to_mumu) v[k_mctype] = 20.;
//       if (ups_to_tautau) v[k_mctype] = 30.;
//       if (ups_to_ee  ||  ups_to_mumu  ||  ups_to_tautau) {
// 	 v[k_mctype] += ups_to_lepphotons;
//       }
//       if (ups_to_ggpho) v[k_mctype] = 40.;
//       if (ups_to_gluons) {
// 	 v[k_mctype] = 50.;
// 	 if (ups_isnt_123) v[k_mctype] = 51.;
//       }
//       v[k_mctype] *= (truly_leptonic ? -1 : 1);

//       assert(v[k_mctype] != 0);
//       assert((ups_to_ee ? 1 : 0) +
// 	     (ups_to_mumu ? 1 : 0) +
// 	     (ups_to_tautau ? 1 : 0) +
// 	     (ups_to_ggpho ? 1 : 0) +
// 	     (ups_to_gluons ? 1 : 0)
// 	     == 1);

// //       OLD CLASSIFICATION
// //       if (ups_to_leptons) v[k_mctype] = 1.;
// //       else if (ups_to_taus) v[k_mctype] = 2.;
// //       else v[k_mctype] = 3.;

// //       int charticles = 0;
// //       int fiducicles = 0;
// //       for (piter = tree->pBegin();  piter != tree_pend;  ++piter) {
// // 	 if (piter->properties().QQId() == eplus    ||
// // 	     piter->properties().QQId() == eminus   ||
// // 	     piter->properties().QQId() == muplus   ||
// // 	     piter->properties().QQId() == muminus  ||
// // 	     piter->properties().QQId() == piplus   ||
// // 	     piter->properties().QQId() == piminus  ||
// // 	     piter->properties().QQId() == kplus    ||
// // 	     piter->properties().QQId() == kminus   ||
// // 	     piter->properties().QQId() == pplus    ||
// // 	     piter->properties().QQId() == pminus   ||
// // 	     piter->properties().QQId() == dplus    ||
// // 	     piter->properties().QQId() == dminus     ) {
// // 	    HepPoint3D source = piter->productionVertex()->position();
// // 	    if (source.perp() < 0.70) {
// // 	       bool good = source.perp() < 0.015  &&  fabs(source.z()) < 0.05;
// // 	       if (piter->dead()) {
// // 		  HepPoint3D sink = piter->deathVertex()->position();
// // 		  good = good &&  sink.perp() > 0.36;
// // 	       }
// // 	       good = good &&  fabs(cos(piter->momentum().theta())) < 0.928;
	    
// // 	       charticles++;
// // 	       if (good) fiducicles++;
// // 	    } // end if inside the DR at least
// // 	 } // end switch
// //       } // end loop over particles

// //       v[k_mctrack] = charticles;
// //       v[k_mcfid] = fiducicles;

//       FAItem<BunchDecision> m_bunchDecision;
//       extract(iFrame.record(Stream::kEvent), m_bunchDecision);

//       v[k_nbunch] = m_bunchDecision->numberOfTestedBunches();
//       v[k_bbunch] = m_bunchDecision->bestBunchNumber();
//    } // end if this is mc
//    else {
//       v[k_mctype] = -1.;
// //       v[k_mctrack] = -1.;
// //       v[k_mcfid] = -1;
//    }
  
   v[k_cvisen] = 0.;
   v[k_cccen] = 0.;
   v[k_cneue] = 0.;
   v[k_avisen] = 0.;
   v[k_accen] = 0.;
   v[k_aneue] = 0.;
   
   for( FATable< NavTrack >::const_iterator trackItr ( tracks.begin() ) ; 
	trackItr != tracks_end ; ++trackItr ) {
      const UInt32 trackID ( trackItr->identifier() ) ;
      FAItem< TRTrackFitQuality > pionQuality( trackItr->pionQuality() );
      const DABoolean trackFitOK ( pionQuality->fit()       &&
				   !pionQuality->fitAbort()     );
      const double dof         ( pionQuality->degreesOfFreedom() ) ;
      const double reducedChi2 ( dof > 0 ? pionQuality->chiSquare()/dof : 0 ) ;
      const double hitFraction ( pionQuality->numberHitsExpected() > 0 ? 
				 pionQuality->ratioNumberHitsToExpected() : 0 );
      FAItem< TDKinematicFit > pion ( trackItr->pionFit() ) ;
      GeV          pTk ( pion->momentum().mag() ) ;
      const int    qTk ( pion->charge()<0 ? ceil( pion->charge() - 0.5 ) :
			 floor( pion->charge() + 0.5 ) ) ;
      const GeV eTk ( trackItr->trackShowerMatch().valid() ?
		      trackItr->trackShowerMatch()->matchedEnergy() : 0 ) ;
      FAItem< TRHelixFit > helix ( trackItr->pionHelix() ) ;
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
	 v[k_cvisen] += pion->energy();

	 if( trackItr->trackShowerMatch().valid()          &&
	     0.5 < trackItr->trackShowerMatch()->eOverP()  &&
             0   < trackItr->bremShowers().size()                ) {
	    FATable< NavShower > show ( trackItr->bremShowers() ) ;
	    for( FATable< NavShower >::const_iterator iS ( show.begin() ) ;
		 iS != show.end() ; ++iS ) {
	       const CcGeV esh ( iS->attributes().energy() ) ; 
	       if( esh > 0.01*eBeam->value() ) v[k_cvisen] += esh ;
	    }
	 }
      } // end loop over good tracks
   } // end loop over tracks
   v[k_avisen] = v[k_cvisen];

   for( FATable< NavShower >::const_iterator showerItr ( showers.begin() ) ; 
	showerItr != showers_end ; ++showerItr ) 
   { 
      const GeV showerEnergy ( showerItr->attributes().energy() ) ;
      const UInt32 showerID ( showerItr->identifier() ) ;
      const double absCosTheta ( fabs(cos(showerItr->attributes().theta())) );
      if( showerEnergy > 0.01*eBeam->value()         &&
	  showerItr->attributes().status()     ) 
      {
	 if (!showerItr->attributes().hot()            &&
	     showerItr->attributes().bigCellId() != 314   &&
	     showerItr->attributes().bigCellId() != 344   &&
	     showerItr->attributes().bigCellId() != 427   &&
	     showerItr->attributes().bigCellId() != 459   &&
	     showerItr->attributes().bigCellId() != 460   &&
	     showerItr->attributes().bigCellId() != 551   &&
	     showerItr->attributes().bigCellId() != 553   &&
	     showerItr->attributes().bigCellId() != 555   &&
	     showerItr->attributes().bigCellId() != 576   &&
	     showerItr->attributes().bigCellId() != 591   &&
	     showerItr->attributes().bigCellId() != 650   &&
	     showerItr->attributes().bigCellId() != 672   &&
	     showerItr->attributes().bigCellId() != 688   &&
	     showerItr->attributes().bigCellId() != 6990  &&
	     showerItr->attributes().bigCellId() != 6997  &&
	     showerItr->attributes().bigCellId() != 7033  &&
	     showerItr->attributes().bigCellId() != 7034  &&
	     showerItr->attributes().bigCellId() != 7097  &&
	     showerItr->attributes().bigCellId() != 7098  &&
	     showerItr->attributes().bigCellId() != 7657     ) {

	    v[k_cccen] += showerEnergy;
	    if (!showerItr->noTrackMatch()  ||  
		!((absCosTheta > 0.84  &&  showerEnergy < 0.06)  ||
		  (absCosTheta > 0.4   &&  showerEnergy < 0.03)    ))
	       v[k_accen] += showerEnergy;
	 }

	 if( showerItr->noTrackMatch()       && 
	     ( !showerItr->bremTrack().valid() ||
		( showerItr->bremTrack()->trackShowerMatch().valid() &&
		  showerItr->bremTrack()->trackShowerMatch()->eOverP()<0.5 ))) 
	 {
	    if (!showerItr->attributes().hot()            &&
		showerItr->attributes().bigCellId() != 314   &&
		showerItr->attributes().bigCellId() != 344   &&
		showerItr->attributes().bigCellId() != 427   &&
		showerItr->attributes().bigCellId() != 459   &&
		showerItr->attributes().bigCellId() != 460   &&
		showerItr->attributes().bigCellId() != 551   &&
		showerItr->attributes().bigCellId() != 553   &&
		showerItr->attributes().bigCellId() != 555   &&
		showerItr->attributes().bigCellId() != 576   &&
		showerItr->attributes().bigCellId() != 591   &&
		showerItr->attributes().bigCellId() != 650   &&
		showerItr->attributes().bigCellId() != 672   &&
		showerItr->attributes().bigCellId() != 688   &&
		showerItr->attributes().bigCellId() != 6990  &&
		showerItr->attributes().bigCellId() != 6997  &&
		showerItr->attributes().bigCellId() != 7033  &&
		showerItr->attributes().bigCellId() != 7034  &&
		showerItr->attributes().bigCellId() != 7097  &&
		showerItr->attributes().bigCellId() != 7098  &&
		showerItr->attributes().bigCellId() != 7657     ) {
	       v[k_cneue] += showerEnergy;
	       if (!showerItr->noTrackMatch()  ||  
		   !((absCosTheta > 0.84  &&  showerEnergy < 0.06)  ||
		     (absCosTheta > 0.4   &&  showerEnergy < 0.03)    ))
		  v[k_aneue] += showerEnergy;
	    }
	 }

      } // end loop over good showers
   } // end loop over showers

   v[k_cvisen] += v[k_cneue];
   v[k_avisen] += v[k_aneue];

   m_ntuple->fill(v);
   return ActionBase::kPassed;
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
