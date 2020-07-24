// -*- C++ -*-
//
// Package:     ReCuts
// Module:      ReCuts
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Jul  6 12:17:22 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ReCuts/ReCuts.h"
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
static const char* const kFacilityString = "Processor.ReCuts" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
ReCuts::ReCuts( void )               // anal1
   : Processor( "ReCuts" )
   , m_mode("mode", this, 0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &ReCuts::event,    Stream::kEvent );
   //bind( &ReCuts::beginRun, Stream::kBeginRun );
   //bind( &ReCuts::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

   m_run = 0;
   m_e1 = 0.;
   m_p2 = 0.;
   m_visen = 0.;
   m_ccen = 0.;
   m_ntracks = 0.;
   m_events = 0;
   m_cosmicEvents = 0;
   m_bgpEvents = 0;
   m_bgeEvents = 0;
   m_ttnumer = 0;
   m_ttdenom = 0;
   for (int i = 0;  i < 16;  i++) m_layerhit[i] = 0;
   m_tracks = 0;
}

ReCuts::~ReCuts()                    // anal5
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
ReCuts::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

   m_run = 0;
   m_e1 = 0.;
   m_p2 = 0.;
   m_visen = 0.;
   m_ccen = 0.;
   m_ntracks = 0.;
   m_events = 0;
   m_cosmicEvents = 0;
   m_bgpEvents = 0;
   m_bgeEvents = 0;
   m_ttnumer = 0;
   m_ttdenom = 0;
   for (int i = 0;  i < 16;  i++) m_layerhit[i] = 0;
   m_tracks = 0;
}

// -------------------- terminate method ----------------------------
void
ReCuts::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)

   if (m_mode.value() == 0) summarize();
}


// ---------------- standard place to book histograms ---------------
void
ReCuts::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
ReCuts::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   if (m_mode.value() == 0) {
      FAItem<DBEventHeader> head;
      extract(iFrame.record(Stream::kEvent), head);
      if (m_run != head->run()) {
	 if (m_run != 0) summarize();
	 m_run = head->run();
	 m_e1 = 0.;
	 m_p2 = 0.;
	 m_visen = 0.;
	 m_ccen = 0.;
	 m_ntracks = 0.;
	 m_events = 0;
	 m_cosmicEvents = 0;
	 m_bgpEvents = 0;
	 m_bgeEvents = 0;
	 m_ttnumer = 0;
	 m_ttdenom = 0;
	 for (int i = 0;  i < 16;  i++) m_layerhit[i] = 0;
	 m_tracks = 0;
      }
   }

   FAItem<TriggerL1Data> triggerDecision;
   extract(iFrame.record(Stream::kEvent), triggerDecision);
   FAItem<Level4Decision> l4dec;
   extract(iFrame.record(Stream::kEvent), l4dec);
   bool passTrig = (triggerDecision->isHadron()  ||
		    triggerDecision->isRadTau()  ||
		    triggerDecision->isElTrack()    );
   report(DEBUG, kFacilityString)
      << "isHadron? " << (triggerDecision->isHadron() ? "yes" : "no") << " "
      << "isRadTau? " << (triggerDecision->isRadTau() ? "yes" : "no") << " "
      << "isElTrack? " << (triggerDecision->isElTrack() ? "yes" : "no") << endl;
//   if (m_mode.value() == 0  &&  !passTrig) return ActionBase::kFailed;
   bool passL4 = l4dec->decision() > 0;
   report(DEBUG, kFacilityString)
      << "L4decision " << l4dec->decision() << endl;
   if (m_mode.value() == 0  &&  !passL4) return ActionBase::kFailed;

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);
   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);
   report(DEBUG, kFacilityString)
      << "eBeam " << eBeam->value() << endl;
   double p2 = props->secondLargestPTrack() / eBeam->value();
   double e1 = props->firstLargestEShower() / eBeam->value();
   double visen = (props->neutralEnergy() + props->chargedEnergy()) / 2. / eBeam->value();
   double ccen = props->ccTotalEnergy() / 2. / eBeam->value();
   double ntracks = double(props->nbChargedTracks());

   report(DEBUG, kFacilityString)
      << "p2 " << p2 << " e1 " << e1 << " visen " << visen << " ccen " << ccen << " ntracks " << ntracks << endl;

   if (m_mode.value() == 0  &&  !(p2 < 0.85)) return ActionBase::kFailed;
   if (m_mode.value() == 0  &&  !(e1 < 0.85)) return ActionBase::kFailed;
//   if (m_mode.value() == 0  &&  !(visen > 0.35)) return ActionBase::kFailed;
   if (m_mode.value() == 0  &&  !(ccen < 0.85)) return ActionBase::kFailed;
   if (m_mode.value() == 0  &&  !(ntracks > 1)) return ActionBase::kFailed;

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();
   FATable<NavTrack>::const_iterator track_iter, other_iter;
   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   double d0close = 1000.;
   double z0close = 1000.;
//    double ci = 1000.;
   double znumer = 0.;
   double zdenom = 0.;
   double wpz = 0.;
   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
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

	 if (sqrt(fabs(track_iter->pionFit()->errorMatrix()(
			  KTKinematicData::kPz, KTKinematicData::kPz))) < 1.) {
	    wpz += track_iter->pionFit()->pz();
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

// 		  if (perp < ci) ci = perp;
		  znumer += tz / z_uncert2;
		  zdenom += 1. / z_uncert2;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over tracks

   double wz = 1000.;
   if (zdenom != 0.) {
      wz = znumer / zdenom;
      wz -= spot->center().z();
   }   

   report(DEBUG, kFacilityString)
      << "d0close " << d0close << " z0close " << z0close << " wz " << wz << endl;

//    double rawtk = tracks.size();
//    double pmiss = 1000.;
//    double tr1 = 1000.;
//    double tr2 = 1000.;
//    double shdot = 1000.;

//    if (m_fillNtuple.value()) {
//       FATable<NavTrack>::const_iterator track1(tracks_end), track2(tracks_end);
//       if (props->nbChargedTracks() >= 2  &&  props->firstTrackIdentifier() != 0  &&  props->secondTrackIdentifier() != 0) {
// 	 track1 = tracks.find(props->firstTrackIdentifier());
// 	 track2 = tracks.find(props->secondTrackIdentifier());
//       }
//       else if (tracks.size() >= 2) {
// 	 double firstp(0.), secondp(0.);
// 	 for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
// 	    double thisp = track_iter->pionFit()->momentum().mag();
// 	    if (thisp > firstp) {
// 	       secondp = firstp;
// 	       track2 = track1;

// 	       firstp = thisp;
// 	       track1 = track_iter;
// 	    }
// 	    else if (thisp > secondp) {
// 	       secondp = thisp;
// 	       track2 = track_iter;
// 	    }
// 	 }
//       }
//       if (track1 != tracks_end  &&  track2 != tracks_end) {
// 	 pmiss = (track1->pionFit()->momentum() + track2->pionFit()->momentum()).mag() / eBeam->value();
// 	 tr1 = track1->pionFit()->momentum().mag() / eBeam->value();
// 	 tr2 = track2->pionFit()->momentum().mag() / eBeam->value();
//       }

//       FATable<NavShower> showers;
//       extract(iFrame.record(Stream::kEvent), showers);
//       FATable<NavShower>::const_iterator showers_end = showers.end();
//       FATable<NavShower>::const_iterator shower_iter;
//       FATable<NavShower>::const_iterator shower1(showers_end), shower2(showers_end);
//       double shower1e(0.), shower2e(0.);
//       for (shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
// 	 if (!shower_iter->attributes().hot()   &&
// 	     shower_iter->attributes().status()   ) {
// 	    double thise = shower_iter->attributes().energy();
// 	    if (thise > shower1e) {
// 	       shower2e = shower1e;
// 	       shower2 = shower1;
	    
// 	       shower1e = thise;
// 	       shower1 = shower_iter;
// 	    }
// 	    else if (thise > shower2e) {
// 	       shower2e = thise;
// 	       shower2 = shower_iter;
// 	    }
// 	 }
//       } // end loop over showers
//       if (shower1 != showers_end  &&  shower2 != showers_end) {
// 	 shdot = shower1->attributes().momentum().dot(shower2->attributes().momentum())
// 	    / shower1->attributes().energy() / shower2->attributes().energy();
//       }
//    }

   double trperp1 = 1000.;
   if (0.075 < abs(wz) < 0.4) {
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
	 double phi1 = track1->pionHelix()->phi0();
	 double phi2 = track2->pionHelix()->phi0();
	 trperp1 = cos(phi1)*cos(phi2) + sin(phi1)*sin(phi2);
      }
   }

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator showers_end(showers.end());
   double accen = 0.;
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
	    if (!showerItr->noTrackMatch()  ||  
		!((absCosTheta > 0.84  &&  showerEnergy < 0.06)  ||
		  (absCosTheta > 0.4   &&  showerEnergy < 0.03)    ))
	       accen += showerEnergy;
	 }

      } // end loop over good showers
   } // end loop over showers


   bool passOuterLimits = (abs(d0close) < 0.005  &&
			   ((wz > 800  &&  abs(z0close) < 0.075) || (wz < 800  &&  abs(wz) < 0.075)));
   bool gassy = (abs(d0close) < 0.02    &&
		 0.075 < abs(wz) < 0.4  &&
		 -0.9 < trperp1 < 0.9);
   bool positronic = (wpz > 1.);
   bool electronic = (wpz < -1.);

   if (!passOuterLimits  &&
       passTrig          &&
       e1 < 0.85         &&
       p2 < 0.85         &&
       visen > 0.35      &&
       ccen < 0.85       &&
       ntracks > 1       &&
       passL4            &&
       gassy                ) {
      if (positronic) m_bgpEvents++;
      else if (electronic) m_bgeEvents++;
   }

   if (passTrig     &&
       e1 < 0.85    &&
       p2 < 0.85    &&
       visen > 0.2  &&
       ccen < 0.85  &&
       ntracks > 1  &&
       passL4       &&
       trperp1 < -0.999                &&
       accen/2./eBeam->value() <= 0.2  &&
       abs(z0close) > 0.075)
      m_cosmicEvents++;

   if (triggerDecision->isTwoTrack()                                              &&
       abs(d0close) < 0.005                                                       &&
       e1 < 0.85                                                                  &&
       p2 < 0.85                                                                  &&
       ((wz > 800  &&  abs(z0close) < 0.075) || (wz < 800  &&  abs(wz) < 0.075))  &&
       visen > 0.35                                                               &&
       props->chargedEnergy()/2./eBeam->value() > 0.35                            &&
       ccen < 0.85                                                                &&
       ntracks > 1                                                                &&
       passL4) {
      if (passTrig) m_ttnumer++;
      m_ttdenom++;
   }

   bool pass = (passTrig                                                                   &&
		abs(d0close) < 0.005                                                       &&
		e1 < 0.85                                                                  &&
		p2 < 0.85                                                                  &&
		((wz > 800  &&  abs(z0close) < 0.075) || (wz < 800  &&  abs(wz) < 0.075))  &&
		visen > 0.35                                                                &&
		ccen < 0.85                                                                &&
		ntracks > 1                                                                &&
		passL4);

   if (pass)
      for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
	 m_tracks++;
	 for (int i = 0;  i < 16;  i++)
	    if (track_iter->pionQuality()->isLayerHit(TRSubdetectorLists::kDR3Axial, i+1)) m_layerhit[i]++;
      }

   if (m_mode.value() == 2) {
      pass = (passTrig                                                                   &&
	      abs(d0close) < 0.005                                                       &&
	      e1 < 0.85                                                                  &&
	      p2 < 0.85                                                                  &&
	      ((wz > 800  &&  abs(z0close) < 0.075) || (wz < 800  &&  abs(wz) < 0.075))  &&
	      visen > 0.35                                                                &&
	      ccen < 1.00                                                                &&
	      ntracks > 1                                                                &&
	      passL4);
   }

   if (m_mode.value() == 3) {
      pass = (passTrig                                                                   &&
	      abs(d0close) < 0.005                                                       &&
	      e1 < 0.85                                                                  &&
	      p2 < 0.85                                                                  &&
	      ((wz > 800  &&  abs(z0close) < 0.075) || (wz < 800  &&  abs(wz) < 0.075))  &&
	      ccen < 0.85                                                                &&
	      ntracks > 1                                                                &&
	      passL4);
   }

   if (m_mode.value() == 0) {
      if (pass) {
	 report(DEBUG, kFacilityString) << "passed and counted!" << endl;

	 m_e1 += e1;
	 m_p2 += p2;
	 m_visen += visen;
	 m_ccen += ccen;
	 m_ntracks += double(ntracks);
	 m_events++;
      }
      
      return (pass ? ActionBase::kPassed : ActionBase::kFailed);
   }
   else if (m_mode.value() == 1  ||  m_mode.value() == 2  ||  m_mode.value() == 3) {
      FAItem<MCDecayTree> tree;
      extract(iFrame.record(Stream::kEvent), tree, "Generator");

      int cutlevel = 0;
      if (pass) cutlevel = 4;

      report(SYSTEM, kFacilityString) << "BEGIN";
      recurse(false, tree->topParticle());
      report(SYSTEM, kFacilityString) << "CUT" << cutlevel << "END" << endl;

//       FAItem<MCDecayTree> tree;
//       extract(iFrame.record(Stream::kEvent), tree);
//       MCDecayTree::const_vIterator viter;
//       MCDecayTree::const_vIterator tree_vend = tree->vEnd();
//       MCDecayTree::const_pIterator piter;
//       MCDecayTree::const_pIterator tree_pend = tree->pEnd();

//       const MCParticlePropertyStore& mcppstore =
// 	 tree->topParticle().properties().store();

//       const int vpho = mcppstore.nameToQQId("vpho");
//       const int gamma = mcppstore.nameToQQId("gamma");
//       const int e_minus = mcppstore.nameToQQId("e-");
//       const int e_plus = mcppstore.nameToQQId("e+");
//       const int nue = mcppstore.nameToQQId("nu_e");
//       const int anti_nue = mcppstore.nameToQQId("anti-nu_e");
//       const int mu_minus = mcppstore.nameToQQId("mu-");
//       const int mu_plus = mcppstore.nameToQQId("mu+");
//       const int numu = mcppstore.nameToQQId("nu_mu");
//       const int anti_numu = mcppstore.nameToQQId("anti-nu_mu");
//       const int tau_minus = mcppstore.nameToQQId("tau-");
//       const int tau_plus = mcppstore.nameToQQId("tau+");
//       const int nutau = mcppstore.nameToQQId("nu_tau");
//       const int anti_nutau = mcppstore.nameToQQId("anti-nu_tau");
//       const int pi_plus = mcppstore.nameToQQId("pi+");
//       const int pi_minus = mcppstore.nameToQQId("pi-");
//       const int pi0 = mcppstore.nameToQQId("pi0");
//       const int excited_K_minus = mcppstore.nameToQQId("K*-")
//       const int excited_K_plus = mcppstore.nameToQQId("K*+")
//       const int Upsilon_1S = mcppstore.nameToQQId("Upsilon(1S)");
//       const int Upsilon_2S = mcppstore.nameToQQId("Upsilon(2S)");
//       const int Upsilon_3S = mcppstore.nameToQQId("Upsilon(3S)");
//       const int chi_b0_1P = mcppstore.nameToQQId("chi_b0(1P)");
//       const int chi_b1_1P = mcppstore.nameToQQId("chi_b1(1P)");
//       const int chi_b2_1P = mcppstore.nameToQQId("chi_b2(1P)");
//       const int chi_b0_2P = mcppstore.nameToQQId("chi_b0(2P)");
//       const int chi_b1_2P = mcppstore.nameToQQId("chi_b1(2P)");
//       const int chi_b2_2P = mcppstore.nameToQQId("chi_b2(2P)");
//       const int Upsilon_1_2D = mcppstore.nameToQQId("Upsilon_1(2D)");
//       const int Upsilon_2_2D = mcppstore.nameToQQId("Upsilon_2(2D)");
//       const int Upsilon_1_1D = mcppstore.nameToQQId("Upsilon_1(1D)");
//       const int Upsilon_2_1D = mcppstore.nameToQQId("Upsilon_2(1D)");
//       const int Upsilon_3_2D = mcppstore.nameToQQId("Upsilon_3(2D)");
//       const int Upsilon_3_1D = mcppstore.nameToQQId("Upsilon_3(1D)");
//       const int chi_b0_3P = mcppstore.nameToQQId("chi_b0(3P)");
//       const int chi_b1_3P = mcppstore.nameToQQId("chi_b1(3P)");
//       const int chi_b2_3P = mcppstore.nameToQQId("chi_b2(3P)");
//       const int glue_string = mcppstore.nameToQQId("string");
      
      return ActionBase::kPassed;
   }
   else assert(false);      
}

/*
ActionBase::ActionResult
ReCuts::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
ReCuts::endRun( Frame& iFrame )         // anal4 equiv.
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

void ReCuts::summarize()
{
   cout << "RUNA " << m_run << " has " << m_events << " events, "
	<< m_cosmicEvents << " *253/1933 = " << double(m_cosmicEvents)*253.0/1933.0 << " cosmics, "
	<< m_bgeEvents << " *52/14 = " << double(m_bgeEvents)*52.0/14.0 << " electronBG, "
	<< m_bgpEvents << " *21/9 = " << double(m_bgpEvents)*21.0/9.0 << " positronBG" << endl
	<< "RUNB " << m_run << " averages "
	<< m_e1/double(m_events) << " "
	<< m_p2/double(m_events) << " "
	<< m_visen/double(m_events) << " "
	<< m_ccen/double(m_events) << " "
	<< m_ntracks/double(m_events) << endl
	<< "RUNC " << m_run
	<< " ttcheck = " << m_ttnumer << " / " << m_ttdenom << " = " << double(m_ttnumer)/double(m_ttdenom) << " layers ";
   for (int i = 0;  i < 16;  i++)
      cout << double(m_layerhit[i])/double(m_tracks) << " ";
   cout << "numbertracks is " << m_tracks << endl;
}

DABoolean ReCuts::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean ReCuts::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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


void ReCuts::recurse(bool space, const MCParticle& particle) {
   if (space) report(SYSTEM, kFacilityString) << " ";
   report(SYSTEM, kFacilityString) << particle.properties().QQId();

   const MCVertex* dv = particle.deathVertex();
   if (dv && dv->nChildren() > 0) {
      report(SYSTEM, kFacilityString) << "(";

      MCVertex::const_pIterator begin = dv->pBegin();
      MCVertex::const_pIterator end = dv->pEnd();
      MCVertex::const_pIterator iter;

      // They're always short lists
      int veto = -999999;
      bool unfirst = false;

      for (int which = 0;  which < dv->nChildren();  which++) {
	 int minimum = 999999;
	 for (iter = begin;  iter != end;  ++iter) {
	    int id = iter->properties().QQId();
	    if (id > veto  &&  id < minimum) minimum = id;
	 } // end (first) loop over children

	 for (iter = begin;  iter != end;  ++iter) {
	    int id = iter->properties().QQId();
	    if (id == minimum) {
	       recurse(unfirst, *iter);
	       unfirst = true;
	    }
	 } // end (second) loop over children

	 veto = minimum;
      } // end loop over number of children

      report(SYSTEM, kFacilityString) << ")";
   } // end if the particle has children
}
