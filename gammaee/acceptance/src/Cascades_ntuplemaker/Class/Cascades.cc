// -*- C++ -*-
//
// Package:     Cascades
// Module:      Cascades
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Apr  6 13:37:00 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Cascades/Cascades.h"
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
static const char* const kFacilityString = "Processor.Cascades" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Cascades::Cascades( void )               // anal1
   : Processor( "Cascades" )
//    , m_triggerInfo("triggerInfo", this, true)
//    , m_mcInfo("mcInfo", this, true)
   , m_tracks(0)
   , m_showers(0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Cascades::event,    Stream::kEvent );
   //bind( &Cascades::beginRun, Stream::kBeginRun );
   //bind( &Cascades::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Cascades::~Cascades()                    // anal5
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
Cascades::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Cascades::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
Cascades::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;
	    
   const char* label[kNumEntries] = {
      "mass", // "ahits1", "ahits2", "shits1", "shits2",
      "p1x", "p1y", "p1z",
      "p2x", "p2y", "p2z",
//      "photon", "e9e25", "e1e9",
      "she1", "she2",
//      "dist1", "dist2",
      "tre1", "tre2",
      "tracks", "visen", "ccen",
      "p2", "p2drop", "e1", "e1drop",
//      "ci", "cidrop", "wz", "wzdrop",
      "run", "ebeam", "neue", "q",
      "hadron", "radtau", "eltrack", "twotrack",
      "axial", "stereo", "cblo", "cbmd",
      "rawtk", "pmiss", "tr1", "tr2", "trperp1", "trperp2", "e2",
//      "l4dec", "l4tracks",
//      "mcpipx", "mcpipy", "mcpipz", "mcpimx", "mcpimy", "mcpimz", "mcupsx", "mcupsy", "mcupsz", 
//      "mctype"
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
Cascades::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();
   FATable<NavTrack>::const_iterator track_iter, other_iter;
   
//    for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
//       m_tracks++;
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
//   } // end loop over tracks (histogramming)

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator showers_end = showers.end();
   FATable<NavShower>::const_iterator shower_iter;

//    for (shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
//       m_showers++;
//       if (m_showers <= 100000) {
// 	 m_shower_status->fill(shower_iter->attributes().status());
// 	 m_shower_energy->fill(shower_iter->attributes().energy() / eBeam->value());
//       } // end if we haven't collected enough
//   } // end loop over showers (histogramming)

   FAItem<MagneticField> bField;
   extract(iFrame.record(Stream::kStartRun), bField);

   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   double bestConstraint = 1000.;
   FATable<NavTrack>::const_iterator pion1(tracks_end), pion2(tracks_end);
   HepVector3D pion1_p(0., 0., 0.), pion2_p(0., 0., 0.);
   for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
       if (
	  track_iter->pionFit()->momentum().mag() < 0.85 * eBeam->value()                                    &&

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
 	  track_iter->pionFit()->momentum().mag() > 0.01 * eBeam->value()                                    &&
 	  track_iter->pionFit()->momentum().mag() < 1.5 * eBeam->value()                                     &&
 	  fabs(track_iter->pionHelix()->cotTheta()) < 3.0424                                                 &&
 	  sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) < 0.5   &&
 	  sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) < 0.25
 	 ) {

 	 for (other_iter = track_iter;  other_iter != tracks_end;  ++other_iter) {
 	    if (
	       other_iter != track_iter                                                                           &&
	       other_iter->pionFit()->momentum().mag() < 0.85 * eBeam->value()                                    &&

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
 	       other_iter->pionFit()->momentum().mag() > 0.01 * eBeam->value()                                    &&
 	       other_iter->pionFit()->momentum().mag() < 1.5 * eBeam->value()                                     &&
 	       fabs(other_iter->pionHelix()->cotTheta()) < 3.0424                                                 &&
 	       sqrt(fabs(other_iter->pionHelix()->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) < 0.5   &&
 	       sqrt(fabs(other_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) < 0.25
 	       ) {

	       double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
	       KTHelix track(*track_iter->pionHelix());
	       KTHelix other(*other_iter->pionHelix());
	       if (
		  calc_intersection(tx, ty, tz, tsig2z, tzsep, track, other)                 &&
		  fabs(tzsep) < 0.005                                                        &&
		  sqrt(sqr(tx - spot->center().x()) + sqr(ty - spot->center().y())) < 0.005  &&
		  fabs(tz) < 0.05
		  ) {
		  double radius = sqrt(sqr(tx) + sqr(ty));
		  double track_moved, other_moved;
		  if (track.moveToRadius(radius, track_moved) == KTMoveControl::kMoveOK  &&
		      other.moveToRadius(radius, other_moved) == KTMoveControl::kMoveOK     ) {
		     HepVector3D track_p = track.momentum(bField->BField(HepPoint3D(tx, ty, tz)));
		     HepVector3D other_p = other.momentum(bField->BField(HepPoint3D(tx, ty, tz)));

		     // the mass constraint
		     const double m1s = 9.465;  // this is where I see the peak (due to missing bfudge?)
		     const double mpi2 = 0.13957018 * 0.13957018;

		     double constraint = sqrt(sqr(2.*eBeam->value()
						  - sqrt(track_p.mag2() + mpi2)
						  - sqrt(other_p.mag2() + mpi2))
					      - (track_p + other_p).mag2());

		     if (fabs(constraint - m1s) < 0.02) {
			bestConstraint = constraint;
			if (track_iter->pionHelix()->curvature() > 0.) {
			   pion1 = track_iter;
			   pion2 = other_iter;
			   pion1_p = track_p;
			   pion2_p = other_p;
			}
			else {
			   pion1 = other_iter;
			   pion2 = track_iter;
			   pion1_p = other_p;
			   pion2_p = track_p;
			}
		     } // end if this is a new bestConstraint

		  } // end if the moveToRadius works for both
	       } // end if we were able to calculate an intersection

	    } // end if other_iter is suitable for being an L4 track and an EventProperties->nbChargedTracks track
 	 } // end loop over other_iter
       } // end if track_iter is suitable for being an L4 track and an EventProperties->nbChargedTracks track
   } // end loop over track_iter

//    FAItem<MCDecayTree> tree;
//    extract(iFrame.record(Stream::kEvent), tree, "Generator");
//    MCDecayTree::const_vIterator viter;
//    MCDecayTree::const_vIterator tree_vend = tree->vEnd();
//    const MCParticlePropertyStore& mcppstore =
//       tree->topParticle().properties().store();
//    const int ups1 = mcppstore.nameToQQId("Upsilon");
//    const int ups2 = mcppstore.nameToQQId("Upsilon(2S)");
//    const int eplus = mcppstore.nameToQQId("e+");
//    const int eminus = mcppstore.nameToQQId("e-");
//    const int muplus = mcppstore.nameToQQId("mu+");
//    const int muminus = mcppstore.nameToQQId("mu-");
//    const int tauplus = mcppstore.nameToQQId("tau+");
//    const int tauminus = mcppstore.nameToQQId("tau-");
//    const int piplus = mcppstore.nameToQQId("pi+");
//    const int piminus = mcppstore.nameToQQId("pi-");
//    const int gamm = mcppstore.nameToQQId("gamma");
//    bool goodcascade = false;
//    for (viter = tree->vBegin();  viter != tree_vend;  ++viter)
//       if (viter->parent().properties().QQId() == ups1) {
// 	 v[k_mctype] = 0.;
// 	 MCVertex::const_pIterator chiter;
// 	 MCVertex::const_pIterator viter_pend = viter->pEnd();
// 	 bool eplus_ = false;
// 	 bool eminus_ = false;
// 	 bool muplus_ = false;
// 	 bool muminus_ = false;
// 	 bool tauplus_ = false;
// 	 bool tauminus_ = false;
// 	 for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
// 	    if (chiter->properties().QQId() == eplus) eplus_ = true;
// 	    if (chiter->properties().QQId() == eminus) eminus_ = true;
// 	    if (chiter->properties().QQId() == muplus) muplus_ = true;
// 	    if (chiter->properties().QQId() == muminus) muminus_ = true;
// 	    if (chiter->properties().QQId() == tauplus) tauplus_ = true;
// 	    if (chiter->properties().QQId() == tauminus) tauminus_ = true;
// 	 }
// 	 if (eplus_ && eminus_) v[k_mctype] = 1.;
// 	 if (muplus_ && muminus_) v[k_mctype] = 2.;
// 	 if (tauplus_ && tauminus_) v[k_mctype] = 3.;
//       }
//       else if (viter->parent().properties().QQId() == ups2) {
// 	 bool ups1_ = false;
// 	 bool piplus_ = false;
// 	 bool piminus_ = false;
// 	 MCVertex::const_pIterator chiter;
// 	 MCVertex::const_pIterator viter_pend = viter->pEnd();
// 	 for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
// 	    if (chiter->properties().QQId() == ups1) ups1_ = true;
// 	    if (chiter->properties().QQId() == piplus) piplus_ = true;
// 	    if (chiter->properties().QQId() == piminus) piminus_ = true;
// 	 }
// 	 if (ups1_ && piplus_ && piminus_) goodcascade = true;
//       }

//    if (!goodcascade) return ActionBase::kPassed;

//    if (m_mcInfo.value()) {
//       FAItem<MCDecayTree> tree;
//       extract(iFrame.record(Stream::kEvent), tree, "Generator");
//       MCDecayTree::const_vIterator viter;
//       MCDecayTree::const_vIterator tree_vend = tree->vEnd();
//       const MCParticlePropertyStore& mcppstore =
// 	 tree->topParticle().properties().store();
//       const int ups1 = mcppstore.nameToQQId("Upsilon");
//       const int ups2 = mcppstore.nameToQQId("Upsilon(2S)");
//       const int ups3 = mcppstore.nameToQQId("Upsilon(3S)");
//       const int piplus = mcppstore.nameToQQId("pi+");
//       const int piminus = mcppstore.nameToQQId("pi-");

//       bool upspipi = false;
//       HepVector3D pip, pim, ups;
//       for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
// 	 if (viter->parent().properties().QQId() == ups2  ||
// 	     viter->parent().properties().QQId() == ups3    ) {
// 	    MCVertex::const_pIterator chiter;
// 	    MCVertex::const_pIterator viter_pend = viter->pEnd();
// 	    bool piplus_(false), piminus_(false), ups1_(false);
// 	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
// 	       if (chiter->properties().QQId() == piplus)  {piplus_ = true;   pip = chiter->momentum();}
// 	       if (chiter->properties().QQId() == piminus) {piminus_ = true;  pim = chiter->momentum();}
// 	       if (chiter->properties().QQId() == ups1)    {ups1_ = true;     ups = chiter->momentum();}
// 	    } // end loop over children
// 	    if (piplus_ && piminus_ && ups1_) upspipi = true;
// 	 } // end if upsilon
//       } // end loop over vertices
//       if (upspipi) {
// 	 v[k_mcpipx] = pip.x();
// 	 v[k_mcpipy] = pip.y();
// 	 v[k_mcpipz] = pip.z();
// 	 v[k_mcpimx] = pim.x();
// 	 v[k_mcpimy] = pim.y();
// 	 v[k_mcpimz] = pim.z();
// 	 v[k_mcupsx] = ups.x();
// 	 v[k_mcupsy] = ups.y();
// 	 v[k_mcupsz] = ups.z();
//       }
//       else {
// 	 v[k_mcpipx] = -1000.;
// 	 v[k_mcpipy] = -1000.;
// 	 v[k_mcpipz] = -1000.;
// 	 v[k_mcpimx] = -1000.;
// 	 v[k_mcpimy] = -1000.;
// 	 v[k_mcpimz] = -1000.;
// 	 v[k_mcupsx] = -1000.;
// 	 v[k_mcupsy] = -1000.;
// 	 v[k_mcupsz] = -1000.;
//       }
//    }
//    else { // not even Monte Carlo
//       v[k_mcpipx] = -2000.;
//       v[k_mcpipy] = -2000.;
//       v[k_mcpipz] = -2000.;
//       v[k_mcpimx] = -2000.;
//       v[k_mcpimy] = -2000.;
//       v[k_mcpimz] = -2000.;
//       v[k_mcupsx] = -2000.;
//       v[k_mcupsy] = -2000.;
//       v[k_mcupsz] = -2000.;
//    }

//   if (bestConstraint == 1000.) {
//       if (m_mcInfo.value()) {
// 	 if (v[k_mcpipx] != -1000.  ||
// 	     v[k_mcpipy] != -1000.  ||
// 	     v[k_mcpipz] != -1000.  ||
// 	     v[k_mcpimx] != -1000.  ||
// 	     v[k_mcpimy] != -1000.  ||
// 	     v[k_mcpimz] != -1000.  ||
// 	     v[k_mcupsx] != -1000.  ||
// 	     v[k_mcupsy] != -1000.  ||
// 	     v[k_mcupsz] != -1000.    ) m_ntuple->fill(v);
// 	 return ActionBase::kPassed;
//       }
// else
//       return ActionBase::kPassed;
//   }

   if (bestConstraint != 1000.) {
      float v[kNumEntries];
      for (int i = 0;  i < kNumEntries;  i++) v[i] = -2000.;

      v[k_mass] = bestConstraint;
//       v[k_ahits1] = pion1->pionQuality()->numberSubdetectorHitLayers(TRSubdetectorLists::kDR3Axial);
//       v[k_ahits2] = pion2->pionQuality()->numberSubdetectorHitLayers(TRSubdetectorLists::kDR3Axial);
//       v[k_shits1] = pion1->pionQuality()->numberSubdetectorHitLayers(TRSubdetectorLists::kDR3Stereo);
//       v[k_shits2] = pion2->pionQuality()->numberSubdetectorHitLayers(TRSubdetectorLists::kDR3Stereo);
      if (pion1 != tracks_end  &&  pion2 != tracks_end) {
	 v[k_p1x] = pion1_p.x();
	 v[k_p1y] = pion1_p.y();
	 v[k_p1z] = pion1_p.z();
	 v[k_p2x] = pion2_p.x();
	 v[k_p2y] = pion2_p.y();
	 v[k_p2z] = pion2_p.z();
      }
//    v[k_photon] = 0.;
//    v[k_e9e25] = -1.;
//    v[k_e1e9] = -1.;
//    for (shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
//       if (shower_iter->attributes().e9oe25OK()      &&
// 	  shower_iter->attributes().e9oe25() > 0.9  &&
// 	  shower_iter->attributes().e1oe9() > 0.7   &&
	  
// 	  shower_iter->noTrackMatch()        && 
// 	  shower_iter->noTrackMatchConReg()  &&
// 	  (!shower_iter->bremTrack().valid() ||
// 	   (shower_iter->bremTrack()->trackShowerMatch().valid()  &&
// 	    shower_iter->bremTrack()->trackShowerMatch()->eOverP()<0.5))) { 
// 	 if (shower_iter->attributes().energy() > v[k_photon]) {
// 	    v[k_photon] = shower_iter->attributes().energy();
// 	    v[k_e9e25] = shower_iter->attributes().e9oe25();
// 	    v[k_e1e9] = shower_iter->attributes().e1oe9();
// 	 }
//       } // end if photon-like and isolated
//    } // end first loop over showers
//    if (v[k_photon] == 0.) {
//       for (shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
// 	 if (shower_iter->noTrackMatch()        && 
// 	     shower_iter->noTrackMatchConReg()  &&
// 	     (!shower_iter->bremTrack().valid() ||
// 	      (shower_iter->bremTrack()->trackShowerMatch().valid()  &&
// 	       shower_iter->bremTrack()->trackShowerMatch()->eOverP()<0.5))) { 
// 	    if (shower_iter->attributes().energy() > v[k_photon]) {
// 	       v[k_photon] = shower_iter->attributes().energy();
// 	       v[k_e9e25] = shower_iter->attributes().e9oe25();
// 	       v[k_e1e9] = shower_iter->attributes().e1oe9();
// 	    }
// 	 } // end if isolated
//       } // end second loop over showers
//    } // end if we need to go fishing again

      vector<NavShower::Identifier> skipShowers;
      if (pion1 != tracks_end  &&  pion2 != tracks_end) {
	 v[k_she1] = 0.;
//	 v[k_dist1] = 1000.;
	 if (pion1->trackShowerMatch().valid()) {
	    FATable<NavShower> matshows = pion1->trackShowerMatch()->navShowers();
	    FATable<NavShower>::const_iterator matshows_end = matshows.end();
	    for (shower_iter = matshows.begin();  shower_iter != matshows_end;  ++shower_iter) {
	       if (shower_iter->attributes().status()  &&
		   shower_iter->attributes().energy() > 0.01 * eBeam->value()) {
		  v[k_she1] += shower_iter->attributes().energy();
		  skipShowers.push_back(shower_iter->identifier());
	       }
	    }
//	    v[k_dist1] = pion1->trackShowerMatch()->distance();
	 }
	 v[k_she1] /= 2. * eBeam->value();

	 v[k_she2] = 0.;
//	 v[k_dist2] = 1000.;
	 if (pion2->trackShowerMatch().valid()) {
	    FATable<NavShower> matshows = pion2->trackShowerMatch()->navShowers();
	    FATable<NavShower>::const_iterator matshows_end = matshows.end();
	    for (shower_iter = matshows.begin();  shower_iter != matshows_end;  ++shower_iter) {
	       if (shower_iter->attributes().status()  &&
		   shower_iter->attributes().energy() > 0.01 * eBeam->value()) {
		  v[k_she2] += shower_iter->attributes().energy();
		  skipShowers.push_back(shower_iter->identifier());
	       }
	    }
//	    v[k_dist2] = pion2->trackShowerMatch()->distance();
	 }
	 v[k_she2] /= 2. * eBeam->value();

	 v[k_tre1] = pion1->pionFit()->energy();
	 if (pion1->trackShowerMatch().valid()          &&
	     pion1->trackShowerMatch()->eOverP() > 0.5  &&
	     pion1->bremShowers().size() > 0              ) {
	    FATable<NavShower> matshows = pion1->bremShowers();
	    FATable<NavShower>::const_iterator matshows_end = matshows.end();
	    for (shower_iter = matshows.begin();  shower_iter != matshows_end;  ++shower_iter) {
	       if (shower_iter->attributes().energy() > 0.01*eBeam->value()) {
		  v[k_tre1] += shower_iter->attributes().energy();
	       }
	    }
	 }
	 v[k_tre1] /= 2. * eBeam->value();
	 v[k_tre1] *= (pion1->pionHelix()->curvature() > 0. ? 1. : -1.);

	 v[k_tre2] = pion2->pionFit()->energy();
	 if (pion2->trackShowerMatch().valid()          &&
	     pion2->trackShowerMatch()->eOverP() > 0.5  &&
	     pion2->bremShowers().size() > 0              ) {
	    FATable<NavShower> matshows = pion2->bremShowers();
	    FATable<NavShower>::const_iterator matshows_end = matshows.end();
	    for (shower_iter = matshows.begin();  shower_iter != matshows_end;  ++shower_iter) {
	       if (shower_iter->attributes().energy() > 0.01*eBeam->value()) {
		  v[k_tre2] += shower_iter->attributes().energy();
	       }
	    }
	 }
	 v[k_tre2] /= 2. * eBeam->value();
	 v[k_tre2] *= (pion2->pionHelix()->curvature() > 0. ? 1. : -1.);
      }

      FAItem<EventProperties> props;
      extract(iFrame.record(Stream::kEvent), props);
      v[k_tracks] = float(props->nbChargedTracks());
      v[k_visen] = (props->neutralEnergy() + props->chargedEnergy()) / 2. / eBeam->value();  // subtract tre1+tre2 from this
      v[k_ccen] = props->ccTotalEnergy() / 2. / eBeam->value();  // subtract she1+she2 from this

      v[k_p2] = props->secondLargestPTrack() / eBeam->value();
      double p1(0.), p2(0.);
      for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
	 if (
	    // EventProperties track cuts
	    track_iter->pionQuality()->fit()                                                                   &&
	    !track_iter->pionQuality()->fitAbort()                                                             &&
	    (track_iter->pionQuality()->degreesOfFreedom() <= 0  ||
	     track_iter->pionQuality()->chiSquare() / double(track_iter->pionQuality()->degreesOfFreedom()) < 100.)    &&
	    track_iter->seedQuality()->numberHitsExpected() > 0                                                &&
	    track_iter->seedQuality()->numberLayers() / double(track_iter->seedQuality()->numberHitsExpected()) > 0.5  &&
	    track_iter->seedQuality()->numberLayers() / double(track_iter->seedQuality()->numberHitsExpected()) < 1.2  &&
	    fabs(track_iter->pionHelix()->d0()) < 0.03                                                         &&
	    fabs(track_iter->pionHelix()->position().z()) < 0.18                                               &&
	    track_iter->pionFit()->momentum().mag() > 0.01 * eBeam->value()                                    &&
	    track_iter->pionFit()->momentum().mag() < 1.5 * eBeam->value()                                     &&
	    fabs(track_iter->pionHelix()->cotTheta()) < 3.0424                                                 &&
	    sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) < 0.5   &&
	    sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) < 0.25              &&

	    // Exclude the pions I have in hand
	    track_iter != pion1  &&
	    track_iter != pion2
	    ) {
	    double p = track_iter->pionFit()->momentum().mag();
	    if (p > p1) {
	       p2 = p1;
	       p1 = p;
	    }
	    else if (p > p2) {
	       p2 = p;
	    }
	 } // end if passes cuts
      } // end loop over tracks
      v[k_p2drop] = p2 / eBeam->value();

      v[k_e1] = props->firstLargestEShower() / eBeam->value();
      double e1drop(0.);
      for (shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
	 if (
	    // EventProperties shower cuts
	    shower_iter->attributes().status()  &&
	    shower_iter->attributes().energy() > 0.01 * eBeam->value()) {

	    if (shower_iter->attributes().energy() > e1drop) {
	       // Exclude the pions I have in hand
	       bool onSkipList = false;
	       vector<NavShower::Identifier>::const_iterator skipShowers_end = skipShowers.end();
	       for (vector<NavShower::Identifier>::const_iterator skipShowers_iter = skipShowers.begin();
		    skipShowers_iter != skipShowers_end;
		    ++skipShowers_iter) {
		  if (*skipShowers_iter == shower_iter->identifier()) {
		     onSkipList = true;
		     break;
		  }
	       } // end loop over skip list

	       if (!onSkipList) e1drop = shower_iter->attributes().energy();
	    } // end if this is a new big shower
	 } // end if passes cuts
      } // end loop over showers
      v[k_e1drop] = e1drop / eBeam->value();

//       v[k_ci] = 1000.;
//       v[k_cidrop] = 1000.;
//       double znumer = 0.;
//       double zdenom = 0.;
//       double znumer_drop = 0.;
//       double zdenom_drop = 0.;
//       for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
// 	 if (! track_iter->seedQuality()->originUsed()            &&
// 	     ! track_iter->pionQuality()->fitAbort()              &&
// 	     1./fabs(track_iter->pionHelix()->curvature()) > 0.42  &&
// 	     ! track_iter->pionHelix()->hasNullErrorMatrix()        
// 	    ) {
// 	    // Secondary track loop to calculate pairwise intersections
// 	    for (other_iter = track_iter;  other_iter != tracks_end;  ++other_iter) {
// 	       if (other_iter != track_iter  &&
// 		   ! other_iter->seedQuality()->originUsed()            &&
// 		   ! other_iter->pionQuality()->fitAbort()              &&
// 		   1./fabs(other_iter->pionHelix()->curvature()) > 0.42  &&
// 		   ! other_iter->pionHelix()->hasNullErrorMatrix()        
// 		  ) { 
// 		  double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
// 		  KTHelix track(*track_iter->pionHelix());
// 		  KTHelix other(*other_iter->pionHelix());
// 		  if (calc_intersection(tx, ty, tz, tsig2z, tzsep, track, other)) {
// 		     double perp(sqrt(sqr(tx - spot->center().x()) + sqr(ty - spot->center().y())));
// 		     double z_uncert2(tsig2z + sqr(tzsep) +
// 				      sqr(tx - spot->center().x()) +
// 				      sqr(ty - spot->center().y()));

// 		     if (perp < v[k_ci]) v[k_ci] = perp;
// 		     znumer += tz / z_uncert2;
// 		     zdenom += 1. / z_uncert2;

// 		     if (track_iter != pion1  &&  track_iter != pion2  &&  other_iter != pion1  &&  other_iter != pion2) {
// 			if (perp < v[k_ci]) v[k_ci] = perp;
// 			znumer_drop += tz / z_uncert2;
// 			zdenom_drop += 1. / z_uncert2;
// 		     }

// 		  } // end if successful intersection
// 	       } // end if secondary track passes quality cuts
// 	    } // end loop over secondary track

// 	 } // end if primary track passes quality cuts
//       } // end loop over tracks

//       v[k_wz] = 1000.;
//       if (zdenom != 0.) {
// 	 v[k_wz] = znumer / zdenom;
// 	 v[k_wz] -= spot->center().z();
//       }   

//       v[k_wzdrop] = 1000.;
//       if (zdenom_drop != 0.) {
// 	 v[k_wzdrop] = znumer_drop / zdenom_drop;
// 	 v[k_wzdrop] -= spot->center().z();
//       }   

      FAItem<DBEventHeader> dbhead;
      extract(iFrame.record(Stream::kEvent), dbhead);

      v[k_run] = dbhead->run();
      v[k_ebeam] = eBeam->value();
      v[k_neue] = props->neutralEnergy() / 2. / eBeam->value();
      v[k_q] = float(props->netCharge());

      FAItem<TriggerL1Data> triggerDecision;
      extract(iFrame.record(Stream::kEvent), triggerDecision);
      v[k_hadron] = triggerDecision->isHadron();
      v[k_radtau] = triggerDecision->isRadTau();
      v[k_eltrack] = triggerDecision->isElTrack();
      v[k_twotrack] = triggerDecision->isTwoTrack();

//    if (m_triggerInfo.value()) {
      FAItem<TriggerInfo> triggerInfo;
      extract(iFrame.record(Stream::kEvent), triggerInfo);
      v[k_axial] = triggerInfo->axial();
      v[k_stereo] = triggerInfo->stereo();
      v[k_cblo] = triggerInfo->cblo();
      v[k_cbmd] = triggerInfo->cbmd();
//    }
//    else {
//       v[k_axial] = -1.;
//       v[k_stereo] = -1.;
//       v[k_cblo] = -1.;
//       v[k_cbmd] = -1.;
//    }

      // Now some variables copied over from Cuts
      // "rawtk", "pmiss", "tr1", "tr2", "trperp1", "trperp2", "e2"
      v[k_rawtk] = tracks.size();

      FATable<NavTrack>::const_iterator track1(tracks_end), track2(tracks_end);
      double firstp(0.), secondp(0.);
      for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
	 if (
	    track_iter != pion1  &&  track_iter != pion2  &&

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
	    track_iter->pionFit()->momentum().mag() > 0.01 * eBeam->value()                                    &&
	    track_iter->pionFit()->momentum().mag() < 1.5 * eBeam->value()                                     &&
	    fabs(track_iter->pionHelix()->cotTheta()) < 3.0424                                                 &&
	    sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) < 0.5   &&
	    sqrt(fabs(track_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) < 0.25
	    ) {
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
	 } // end if passes
      } // end loop over tracks
      if (track1 == tracks_end  ||  track2 == tracks_end) {
	 for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
	    if (track_iter != pion1  &&  track_iter != pion2) {
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
	    } // end if passes
	 } // end loop over tracks
      } // end if desperate

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
      }

      double e2drop(0.);
      for (shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
	 if (
	    // EventProperties shower cuts
	    shower_iter->attributes().status()  &&
	    shower_iter->attributes().energy() > 0.01 * eBeam->value()) {

	    if (shower_iter->attributes().energy() > e2drop) {
	       // Exclude the pions I have in hand
	       bool onSkipList = false;
	       vector<NavShower::Identifier>::const_iterator skipShowers_end = skipShowers.end();
	       for (vector<NavShower::Identifier>::const_iterator skipShowers_iter = skipShowers.begin();
		    skipShowers_iter != skipShowers_end;
		    ++skipShowers_iter) {
		  if (*skipShowers_iter == shower_iter->identifier()) {
		     onSkipList = true;
		     break;
		  }
	       } // end loop over skip list

	       if (!onSkipList) e2drop = shower_iter->attributes().energy();
	    } // end if this is a new big shower
	 } // end if passes cuts
      } // end loop over showers
      v[k_e2] = e2drop / eBeam->value();

//       FAItem<Level4Decision> l4dec;
//       extract(iFrame.record(Stream::kEvent), l4dec);
//       v[k_l4dec] = l4dec->decision();
//       v[k_l4tracks] = 0.;
//       for (track_iter = tracks.begin();  track_iter != tracks_end;  ++track_iter) {
// 	 if (
// 	    track_iter != pion1  &&  track_iter != pion2  &&

// 	    // L4 conditions
// 	    !track_iter->seedQuality()->originUsed()                                                           &&
// 	    track_iter->seedQuality()->numberHitsExpected() > 0                                                &&
// 	    track_iter->seedQuality()->numberHits() / double(track_iter->seedQuality()->numberHitsExpected()) >= 0.4   &&
// 	    sqrt(1. - 1./(1.+sqr(track_iter->seedTrack()->cotTheta()))) <= 0.93                                &&
// 	    track_iter->seedQuality()->chiSquare() < track_iter->seedQuality()->degreesOfFreedom() * 20.       &&
// 	    fabs(track_iter->seedTrack()->d0()) < 0.025                                                        &&
// 	    fabs(track_iter->seedTrack()->z0()) < 0.15                                                            ) {
// 	    v[k_l4tracks]++;
// 	 }
//       }

      m_ntuple->fill(v);
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
Cascades::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
  ActionBase::ActionResult
  Cascades::endRun( Frame& iFrame )         // anal4 equiv.
  {
  report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

  return ActionBase::kPassed;
  }
*/

DABoolean Cascades::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean Cascades::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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
