// -*- C++ -*-
//
// Package:     BiggestSystematic
// Module:      BiggestSystematic
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Nov 30 16:20:35 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "BiggestSystematic/BiggestSystematic.h"
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

#include "EventProperties/EventProperties.h"
#include "BeamEnergy/BeamEnergy.h"
#include "BeamSpot/BeamSpot.h"
#include "Navigation/NavTkShMatch.h"
#include "TriggerL1Data/TriggerL1Data.h"
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
static const char* const kFacilityString = "Processor.BiggestSystematic" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
BiggestSystematic::BiggestSystematic( void )               // anal1
   : Processor( "BiggestSystematic" )
   , m_mc("mc", this, 0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &BiggestSystematic::event,    Stream::kEvent );
   //bind( &BiggestSystematic::beginRun, Stream::kBeginRun );
   //bind( &BiggestSystematic::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

BiggestSystematic::~BiggestSystematic()                    // anal5
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
BiggestSystematic::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
BiggestSystematic::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
BiggestSystematic::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "rawtk", "tracks", "pmiss", "tr1", "tr2", "visen", "ccen", "d0close", "z0close",
      "t1px", "t1py", "t1pz", "t1e",
      "t2px", "t2py", "t2pz", "t2e",
      "t3px", "t3py", "t3pz", "t3e",
      "t4px", "t4py", "t4pz", "t4e",
      "u1px", "u1py", "u1pz", "u1e",
      "u2px", "u2py", "u2pz", "u2e",
      "u3px", "u3py", "u3pz", "u3e",
      "u4px", "u4py", "u4pz", "u4e",
      "neue", "vecpx", "vecpy", "vecpz", "scapt", "scapz", "goodtk",
      "trig", "wz", "e1", "p2", "tttrig", "mctype",
      "mcinv", "mcprompt", "mult"
   };
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
BiggestSystematic::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();
   FATable<NavTrack>::const_iterator track_iter, other_iter;

   FATable<NavTrack> goodtracks;
   extract(iFrame.record(Stream::kEvent), goodtracks, "TrkmanApproved");
   FATable<NavTrack>::const_iterator goodtracks_end = goodtracks.end();

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator showers_end = showers.end();

   FAItem<TriggerL1Data> triggerDecision;
   extract(iFrame.record(Stream::kEvent), triggerDecision);

   float v[kNumEntries];
   for (int i = 0;  i < kNumEntries;  i++) v[i] = -3000.;

   v[k_mcinv] = 0;
   v[k_mccas] = 0;
   int mult_prompt = 0;
   int mult_glue = 0;
   if (m_mc.value() > 0) {
      FAItem<MCDecayTree> tree;
      extract(iFrame.record(Stream::kEvent), tree);
      FAItem<MCDecayTree> gtree;
      extract(iFrame.record(Stream::kEvent), gtree, "Generator");
      MCDecayTree::const_vIterator viter;
      MCDecayTree::const_vIterator tree_vend = tree->vEnd();
      MCDecayTree::const_pIterator piter;
      MCDecayTree::const_pIterator gtree_pend = gtree->pEnd();
      
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

      const int nu_e = mcppstore.nameToQQId("nu_e");
      const int nu_mu = mcppstore.nameToQQId("nu_mu");
      const int nu_tau = mcppstore.nameToQQId("nu_tau");
      const int nubar_e = mcppstore.nameToQQId("anti-nu_e");
      const int nubar_mu = mcppstore.nameToQQId("anti-nu_mu");
      const int nubar_tau = mcppstore.nameToQQId("anti-nu_tau");
      const int klong = mcppstore.nameToQQId("K_L0");
      const int neutron = mcppstore.nameToQQId("n0");
      const int antineutron = mcppstore.nameToQQId("anti-n0");

      const int vpho = mcppstore.nameToQQId("vpho");

      bool really_prompt = true;

      bool ups_to_ee = false;
      bool ups_to_mumu = false;
      bool ups_to_tautau = false;
      int ups_to_lepphotons = 0;
      bool ups_to_gluons = false;
      bool ups_to_ggpho = false;
      bool ups_isnt_123 = false;
      bool truly_leptonic = false;

//       report(DEBUG, kFacilityString) << "no?" << endl;
//       HepPoint3D eventVertex(0.,0.,0.);
//       for (piter = gtree->pBegin();  piter != gtree_pend;  ++piter) {
// 	 if (piter->properties().QQId() == vpho)
// 	    eventVertex = piter->deathVertex()->position();
//       }
//       report(DEBUG, kFacilityString) << "yes?" << endl;

      for (piter = gtree->pBegin();  piter != gtree_pend;  ++piter) {
	 if (piter->properties().QQId() == nu_e        ||
	     piter->properties().QQId() == nu_mu       ||
	     piter->properties().QQId() == nu_tau      ||
	     piter->properties().QQId() == nubar_e     ||
	     piter->properties().QQId() == nubar_mu    ||
	     piter->properties().QQId() == nubar_tau   ||
	     piter->properties().QQId() == klong       ||
	     piter->properties().QQId() == neutron     ||
	     piter->properties().QQId() == antineutron   ) {
	    v[k_mcinv]++;
	 }

// 	 report(DEBUG, kFacilityString) << "ready" << endl;
// 	 report(DEBUG, kFacilityString) << "dead: " << piter->dead() << endl;
// 	 if (piter->dead()) report(DEBUG, kFacilityString) << "deathVertex: " << piter->deathVertex()->position() << endl;
// 	 if (!piter->dead()  ||
// 	     (piter->deathVertex()->position() - eventVertex).mag() > 0.005) v[k_mult]++;
// 	 report(DEBUG, kFacilityString) << "all done" << endl;
      }
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
	 
	 assert(m_mc.value() == 1  ||  m_mc.value() == 2  ||  m_mc.value() == 3);
	 bool prompt_(false);
	 if (viter->parent().properties().QQId() == ups1  &&  m_mc.value() == 1) prompt_ = true;
	 if (viter->parent().properties().QQId() == ups2  &&  m_mc.value() == 2) prompt_ = true;
	 if (viter->parent().properties().QQId() == ups3  &&  m_mc.value() == 3) prompt_ = true;

	 if (anybbbar  &&  !prompt_) really_prompt = false;

	 if (viter->parent().properties().QQId() == glue) {
	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();
	    cout << "DG:";
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter)
	       if (chiter->properties().QQId() != gamm) {
		  cout << " " << chiter->properties().name();
		  mult_glue++;
	       }
	    cout << endl;
	 }

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

	       if (prompt_) mult_prompt++;
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

      if (really_prompt) v[k_mccas] = 1;

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

      if (mult_glue > 0) v[k_mult] = mult_glue;
//      else v[k_mult] = mult_prompt;
   }

   v[k_trig] = 0.;
   if (triggerDecision->isHadron())  v[k_trig] += 100.;
   if (triggerDecision->isRadTau())  v[k_trig] += 10.;
   if (triggerDecision->isElTrack()) v[k_trig] += 1.;

   v[k_tttrig] = 0.;
   if (triggerDecision->isTwoTrack()) v[k_tttrig] = 1.;

   v[k_rawtk] = tracks.size();
   v[k_tracks] = props->nbChargedTracks();
   v[k_visen] = (props->neutralEnergy() + props->chargedEnergy()) / 2. / eBeam->value();
   v[k_ccen] = props->ccTotalEnergy() / 2. / eBeam->value();
   v[k_neue] = (props->neutralEnergy()) / 2. / eBeam->value();
   v[k_e1] = props->firstLargestEShower() / eBeam->value();
   v[k_p2] = props->secondLargestPTrack() / eBeam->value();

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
   }

   double znumer = 0.;
   double zdenom = 0.;
   v[k_d0close] = 1000.;
   v[k_z0close] = 1000.;
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

   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
      KTHelix movetrack(*track_iter->pionHelix());
      double distance_moved;
      movetrack.moveToReferencePoint(spot->center(),
				     distance_moved,
				     KTMoveControl::kDirectionEither);
      if (fabs(movetrack.d0()) < fabs(v[k_d0close])) v[k_d0close] = movetrack.d0();
      if (fabs(movetrack.z0()) < fabs(v[k_z0close])) v[k_z0close] = movetrack.z0();
   }

   FATable<NavTrack>::const_iterator t1(tracks_end), t2(tracks_end), t3(tracks_end), t4(tracks_end);
   FATable<NavTrack>::const_iterator u1(tracks_end), u2(tracks_end), u3(tracks_end), u4(tracks_end);
   double t1p(0.), t2p(0.), t3p(0.), t4p(0.);
   double u1p(0.), u2p(0.), u3p(0.), u4p(0.);
   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
      double thisp = track_iter->pionFit()->momentum().mag();
      if (track_iter->pionHelix()->curvature() > 0.) {
	 if (thisp > t1p) {
	    t4p = t3p;
	    t4  = t3;

	    t3p = t2p;
	    t3  = t2;

	    t2p = t1p;
	    t2  = t1;

	    t1p = thisp;
	    t1  = track_iter;
	 }
	 else if (thisp > t2p) {
	    t4p = t3p;
	    t4  = t3;

	    t3p = t2p;
	    t3  = t2;

	    t2p = thisp;
	    t2  = track_iter;
	 }
	 else if (thisp > t3p) {
	    t4p = t3p;
	    t4  = t3;

	    t3p = thisp;
	    t3  = track_iter;
	 }
	 else if (thisp > t4p) {
	    t4p = thisp;
	    t4  = track_iter;
	 }
      }
      else {
	 if (thisp > u1p) {
	    u4p = u3p;
	    u4  = u3;

	    u3p = u2p;
	    u3  = u2;

	    u2p = u1p;
	    u2  = u1;

	    u1p = thisp;
	    u1  = track_iter;
	 }
	 else if (thisp > u2p) {
	    u4p = u3p;
	    u4  = u3;

	    u3p = u2p;
	    u3  = u2;

	    u2p = thisp;
	    u2  = track_iter;
	 }
	 else if (thisp > u3p) {
	    u4p = u3p;
	    u4  = u3;

	    u3p = thisp;
	    u3  = track_iter;
	 }
	 else if (thisp > u4p) {
	    u4p = thisp;
	    u4  = track_iter;
	 }
      }
   }

   v[k_t1px] = v[k_t1py] = v[k_t1pz] = v[k_t1e] = 0.;
   v[k_t2px] = v[k_t2py] = v[k_t2pz] = v[k_t2e] = 0.;
   v[k_t3px] = v[k_t3py] = v[k_t3pz] = v[k_t3e] = 0.;
   v[k_t4px] = v[k_t4py] = v[k_t4pz] = v[k_t4e] = 0.;
   v[k_u1px] = v[k_u1py] = v[k_u1pz] = v[k_u1e] = 0.;
   v[k_u2px] = v[k_u2py] = v[k_u2pz] = v[k_u2e] = 0.;
   v[k_u3px] = v[k_u3py] = v[k_u3pz] = v[k_u3e] = 0.;
   v[k_u4px] = v[k_u4py] = v[k_u4pz] = v[k_u4e] = 0.;
   if (t1 != tracks_end) {
      v[k_t1px] = t1->pionFit()->momentum().x();
      v[k_t1py] = t1->pionFit()->momentum().y();
      v[k_t1pz] = t1->pionFit()->momentum().z();
      if (t1->trackShowerMatch().valid()) v[k_t1e] = t1->trackShowerMatch()->eOverP();
   }
   if (t2 != tracks_end) {
      v[k_t2px] = t2->pionFit()->momentum().x();
      v[k_t2py] = t2->pionFit()->momentum().y();
      v[k_t2pz] = t2->pionFit()->momentum().z();
      if (t2->trackShowerMatch().valid()) v[k_t2e] = t2->trackShowerMatch()->eOverP();
   }
   if (t3 != tracks_end) {
      v[k_t3px] = t3->pionFit()->momentum().x();
      v[k_t3py] = t3->pionFit()->momentum().y();
      v[k_t3pz] = t3->pionFit()->momentum().z();
      if (t3->trackShowerMatch().valid()) v[k_t3e] = t3->trackShowerMatch()->eOverP();
   }
   if (t4 != tracks_end) {
      v[k_t4px] = t4->pionFit()->momentum().x();
      v[k_t4py] = t4->pionFit()->momentum().y();
      v[k_t4pz] = t4->pionFit()->momentum().z();
      if (t4->trackShowerMatch().valid()) v[k_t4e] = t4->trackShowerMatch()->eOverP();
   }
   if (u1 != tracks_end) {
      v[k_u1px] = u1->pionFit()->momentum().x();
      v[k_u1py] = u1->pionFit()->momentum().y();
      v[k_u1pz] = u1->pionFit()->momentum().z();
      if (u1->trackShowerMatch().valid()) v[k_u1e] = u1->trackShowerMatch()->eOverP();
   }
   if (u2 != tracks_end) {
      v[k_u2px] = u2->pionFit()->momentum().x();
      v[k_u2py] = u2->pionFit()->momentum().y();
      v[k_u2pz] = u2->pionFit()->momentum().z();
      if (u2->trackShowerMatch().valid()) v[k_u2e] = u2->trackShowerMatch()->eOverP();
   }
   if (u3 != tracks_end) {
      v[k_u3px] = u3->pionFit()->momentum().x();
      v[k_u3py] = u3->pionFit()->momentum().y();
      v[k_u3pz] = u3->pionFit()->momentum().z();
      if (u3->trackShowerMatch().valid()) v[k_u3e] = u3->trackShowerMatch()->eOverP();
   }
   if (u4 != tracks_end) {
      v[k_u4px] = u4->pionFit()->momentum().x();
      v[k_u4py] = u4->pionFit()->momentum().y();
      v[k_u4pz] = u4->pionFit()->momentum().z();
      if (u4->trackShowerMatch().valid()) v[k_u4e] = u4->trackShowerMatch()->eOverP();
   }

   report(DEBUG, kFacilityString) << "start" << endl;
   v[k_vecpx] = v[k_vecpy] = v[k_vecpz] = v[k_scapt] = v[k_scapz] = 0.;
   HepVector3D vecp(0.,0.,0.);
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();
	shower_iter != showers_end;
	++shower_iter) {
      if (shower_iter->attributes().energy() > 0.01 * eBeam->value()  &&
	  shower_iter->attributes().status() ) {
	 report(DEBUG, kFacilityString) << "  foreach shower" << endl;
	 bool usethis = true;
	 if (shower_iter->trackMatches().valid()  ||  shower_iter->bremTrack().valid()) {
	    if (shower_iter->trackMatches().valid()) {
	       const FATable<NavTkShMatch>& matches = shower_iter->trackMatches();
	       if (matches.size() > 0) report(DEBUG, kFacilityString) << "    there are attached tracks" << endl;
	       FATable<NavTkShMatch>::const_iterator matches_end = matches.end();
	       for (FATable<NavTkShMatch>::const_iterator match_iter = matches.begin();
		    match_iter != matches_end;
		    ++match_iter) {
		  report(DEBUG, kFacilityString) << "      foreach track: ";
		  FATable<NavTrack>::const_iterator goodtrack_iter = goodtracks.find(match_iter->trackId());
		  if (goodtrack_iter != goodtracks_end) {
		     report(DEBUG, kFacilityString) << "it's a goodtrack!" << endl;
		     usethis = false;
		  }
		  else report(DEBUG, kFacilityString) << "it's a suck-o track." << endl;
	       }
	    }
	    if (shower_iter->bremTrack().valid()) {
	       report(DEBUG, kFacilityString) << "    there's a bremtrack: ";
	       FATable<NavTrack>::const_iterator goodtrack_iter = goodtracks.find(shower_iter->bremTrack()->identifier());
	       if (goodtrack_iter != goodtracks_end) {
		  report(DEBUG, kFacilityString) << "it's a goodtrack!" << endl;
		  usethis = false;
	       }
	       else report(DEBUG, kFacilityString) << "it's a suck-o track." << endl;
	    }
	 }

	 if (usethis) {
	    report(DEBUG, kFacilityString) << "  we use this shower" << endl << endl;
	    vecp += shower_iter->attributes().momentum();
	    v[k_scapt] += shower_iter->attributes().momentum().perp();
	    v[k_scapz] += abs(shower_iter->attributes().momentum().z());
	 }
	 else report(DEBUG, kFacilityString) << "  skipping shower" << endl << endl;
      }
   }
   report(DEBUG, kFacilityString) << "end" << endl;
   for(FATable< NavTrack >::const_iterator goodtrack_iter = goodtracks.begin();
	goodtrack_iter != goodtracks_end;
	++goodtrack_iter) {
	 vecp += goodtrack_iter->pionFit()->momentum();
	 v[k_scapt] += goodtrack_iter->pionFit()->momentum().perp();
	 v[k_scapz] += abs(goodtrack_iter->pionFit()->momentum().z());
   }
   v[k_vecpx] = vecp.x();
   v[k_vecpy] = vecp.y();
   v[k_vecpz] = vecp.z();

   v[k_goodtk] = goodtracks.size();

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
BiggestSystematic::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
BiggestSystematic::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

DABoolean BiggestSystematic::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean BiggestSystematic::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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
