// -*- C++ -*-
//
// Package:     UpsilonGammaEEAnalysisProc
// Module:      UpsilonGammaEEAnalysisProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue May  3 14:36:21 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "UpsilonGammaEEAnalysisProc/UpsilonGammaEEAnalysisProc.h"
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
static const char* const kFacilityString = "Processor.UpsilonGammaEEAnalysisProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
UpsilonGammaEEAnalysisProc::UpsilonGammaEEAnalysisProc( void )               // anal1
   : Processor( "UpsilonGammaEEAnalysisProc" )
   , m_goodBunch("goodBunch", this, true)
   , m_ellell("ellell", this, false)
   , m_photos("photos", this, false)
   , m_runstats("runstats", this, true)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &UpsilonGammaEEAnalysisProc::event,    Stream::kEvent );
   //bind( &UpsilonGammaEEAnalysisProc::beginRun, Stream::kBeginRun );
   //bind( &UpsilonGammaEEAnalysisProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

   m_run = 0;
   m_mc_all = 0;
   m_mc_badbunch = 0;
   m_mc_ellell = 0;
   m_mc_photos = 0;

}

UpsilonGammaEEAnalysisProc::~UpsilonGammaEEAnalysisProc()                    // anal5
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
UpsilonGammaEEAnalysisProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
UpsilonGammaEEAnalysisProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
   m_cut.print();
   m_cut.print_extra();

   m_hadron.print();
   m_hadron.print_extra();

   m_hadroncool.print();
   m_hadroncool.print_extra();

   m_oldhadron.print();
   m_oldhadron.print_extra();

   m_oldhadronall.print();
   m_oldhadronall.print_extra();

   m_gamgam.print();
   m_gamgam.print_extra();

   m_trackless.print();
   m_trackless.print_extra();

   m_bhabha.print();
   m_bhabha.print_extra();

   m_mupair.print();
   m_mupair.print_extra();

   m_bhabhatwotrack.print();
   m_bhabhatwotrack.print_extra();

   m_mupairtwotrack.print();
   m_mupairtwotrack.print_extra();

   m_cosmic.print();
   m_cosmic.print_extra();

   m_beamgase.print();
   m_beamgase.print_extra();

   m_beamgasp.print();
   m_beamgasp.print_extra();

   m_brokenshower.print();
   m_brokenshower.print_extra();

   m_brokenshower2.print();
   m_brokenshower2.print_extra();

   m_ccstudy1.print();
   m_ccstudy1.print_extra();

//    m_ccstudy2.print();
//    m_ccstudy2.print_extra();

//    m_ccstudy3.print();
//    m_ccstudy3.print_extra();

//    m_ccstudy4.print();
//    m_ccstudy4.print_extra();

   cout << "PYTHON rec.mc_all = " << m_mc_all << endl;
   cout << "PYTHON rec.mc_badbunch = " << m_mc_badbunch << endl;
   cout << "PYTHON rec.mc_ellell = " << m_mc_ellell << endl;
   cout << "PYTHON rec.mc_photos = " << m_mc_photos << endl;
}


// ---------------- standard place to book histograms ---------------
void
UpsilonGammaEEAnalysisProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   m_cut.histbook(iHistoManager);
   m_cut.histbook_extra(iHistoManager);

   m_hadron.histbook(iHistoManager);
   m_hadron.histbook_extra(iHistoManager);

   m_hadroncool.histbook(iHistoManager);
   m_hadroncool.histbook_extra(iHistoManager);

   m_oldhadron.histbook(iHistoManager);
   m_oldhadron.histbook_extra(iHistoManager);

   m_oldhadronall.histbook(iHistoManager);
   m_oldhadronall.histbook_extra(iHistoManager);

   m_gamgam.histbook(iHistoManager);
   m_gamgam.histbook_extra(iHistoManager);

   m_trackless.histbook(iHistoManager);
   m_trackless.histbook_extra(iHistoManager);

   m_bhabha.histbook(iHistoManager);
   m_bhabha.histbook_extra(iHistoManager);

   m_mupair.histbook(iHistoManager);
   m_mupair.histbook_extra(iHistoManager);

   m_bhabhatwotrack.histbook(iHistoManager);
   m_bhabhatwotrack.histbook_extra(iHistoManager);

   m_mupairtwotrack.histbook(iHistoManager);
   m_mupairtwotrack.histbook_extra(iHistoManager);

   m_cosmic.histbook(iHistoManager);
   m_cosmic.histbook_extra(iHistoManager);

   m_beamgase.histbook(iHistoManager);
   m_beamgase.histbook_extra(iHistoManager);

   m_beamgasp.histbook(iHistoManager);
   m_beamgasp.histbook_extra(iHistoManager);

   m_brokenshower.histbook(iHistoManager);
   m_brokenshower.histbook_extra(iHistoManager);

   m_brokenshower2.histbook(iHistoManager);
   m_brokenshower2.histbook_extra(iHistoManager);

   m_ccstudy1.histbook(iHistoManager);
   m_ccstudy1.histbook_extra(iHistoManager);

//    m_ccstudy2.histbook(iHistoManager);
//    m_ccstudy2.histbook_extra(iHistoManager);

//    m_ccstudy3.histbook(iHistoManager);
//    m_ccstudy3.histbook_extra(iHistoManager);

//    m_ccstudy4.histbook(iHistoManager);
//    m_ccstudy4.histbook_extra(iHistoManager);

   const char* label[kNumEntries] = {
      "run", "event", "trig", "type",
      "d0close", "anyz", "p1x", "p1y", "p1z", "p2x", "p2y", "p2z",
      "visen", "coolvisen", "frozenvisen", "tracks", "rawtk",
      "oppositesides", "e1", "e2", "e3", "phi1", "cos1", "phi2", "cos2",
      "oppositecharge", "eisr", "econstr", "cosp", "cosn",
      "wpz", "pdotp", "ccen", "neue", "l4dec", "chen"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
UpsilonGammaEEAnalysisProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);

   FAItem<RunStats> stats;
   if (m_runstats.value()) extract(iFrame.record(Stream::kBeginRun), stats);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   HepPoint3D bs;
   if (head->run() == 126828) bs = HepPoint3D(-0.000717, 0.000718, 0.000837);
   else if (head->run() == 126920) bs = HepPoint3D(-0.000839, 0.000712, 0.000656);
   else if (head->run() == 126922) bs = HepPoint3D(-0.000839, 0.000712, 0.000656);
   else if (head->run() == 126785) bs = HepPoint3D(-0.000752, 0.000714, 0.000894);
   else if (head->run() == 128706) bs = HepPoint3D(-0.000583, 0.000561, -0.002893);
   else if (head->run() == 128736) bs = HepPoint3D(-0.000583, 0.000561, -0.002893);
   else if (head->run() == 128741) bs = HepPoint3D(-0.000583, 0.000561, -0.002893);
   else if (head->run() == 128748) bs = HepPoint3D(-0.000583, 0.000561, -0.002893);
   else if (head->monteCarlo()) bs = HepPoint3D(0.,0.,0.);
   else {
      FAItem<BeamSpot> spot;
      extract(iFrame.record(Stream::kBeginRun), spot);
      bs = spot->center();
   }

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<EventType> type;
   extract(iFrame.record(Stream::kEvent), type);

   FAItem<TriggerL1Data> trig;
   extract(iFrame.record(Stream::kEvent), trig);

   FAItem<Level4Decision> l4dec;
   extract(iFrame.record(Stream::kEvent), l4dec);

   FAItem<BunchDecision> bunch;
   if (head->monteCarlo()) extract(iFrame.record(Stream::kEvent), bunch);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator showers_end = showers.end();

   FAItem<MCDecayTree> tree;
   if (head->monteCarlo()) extract(iFrame.record(Stream::kEvent), tree, "Generator");

   if (!head->monteCarlo()) {
      if (m_run == 0) m_run = head->run();
      // this should only be used on one run at a time
      assert(m_run == head->run());
   }

   if (m_runstats.value()) {
      if (head->number() > stats->lastEvNum()) {
	 report(SYSTEM, kFacilityString)
	    << "DISASTERA: event " << head->number() << " is beyond lastEvNum = " << stats->lastEvNum()
	    << " ; type is " << (type->known() ? "known" : "unknown") << endl;
      }
      if (m_mc_all > stats->nEvents()) {
	 report(SYSTEM, kFacilityString)
	    << "DISASTERB: event " << head->number() << " is beyond nEvents = " << stats->nEvents()
	    << " ; type is " << (type->known() ? "known" : "unknown") << endl;
      }
   }

   if (head->monteCarlo()) {
      m_mc_all++;

      bool goodbunch = (bunch->numberOfTestedBunches() < 15  &&
			bunch->bestBunchNumber() < 10);
      if (!goodbunch) m_mc_badbunch++;

      bool ellell = false;
      bool photos = false;
      const MCParticlePropertyStore& mcppstore =
	 tree->topParticle().properties().store();
      const int ups1 = mcppstore.nameToQQId("Upsilon");
      const int ups2 = mcppstore.nameToQQId("Upsilon(2S)");
      const int ups3 = mcppstore.nameToQQId("Upsilon(3S)");
      const int eplus = mcppstore.nameToQQId("e+");
      const int eminus = mcppstore.nameToQQId("e-");
      const int muplus = mcppstore.nameToQQId("mu+");
      const int muminus = mcppstore.nameToQQId("mu-");
      const int photon = mcppstore.nameToQQId("gamma");
      MCDecayTree::const_vIterator viter;
      MCDecayTree::const_vIterator tree_vend = tree->vEnd();
      for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
	 if (viter->parent().properties().QQId() == ups1  ||
	     viter->parent().properties().QQId() == ups2  ||
	     viter->parent().properties().QQId() == ups3    ) {
	    bool saw_eplus = false, saw_eminus = false;
	    bool saw_muplus = false, saw_muminus = false;
	    bool saw_photon = false;

	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	       if (chiter->properties().QQId() == eplus) saw_eplus = true;
	       if (chiter->properties().QQId() == eminus) saw_eminus = true;
	       if (chiter->properties().QQId() == muplus) saw_muplus = true;
	       if (chiter->properties().QQId() == muminus) saw_muminus = true;
	       if (chiter->properties().QQId() == photon) saw_photon = true;
	    }

	    if ((saw_eplus && saw_eminus) || (saw_muplus && saw_muminus)) ellell = true;
	    if (ellell && saw_photon) photos = true;
	 }
      }

      if (ellell) m_mc_ellell++;
      if (photos) m_mc_photos++;

      if (m_goodBunch.value() && !goodbunch) return ActionBase::kFailed;
      if (!m_goodBunch.value() && goodbunch) return ActionBase::kFailed;

      if (m_ellell.value() && !ellell) return ActionBase::kFailed;
      if (!m_ellell.value() && ellell) return ActionBase::kFailed;

      if (m_photos.value() && !photos) return ActionBase::kFailed;
      if (!m_photos.value() && photos) return ActionBase::kFailed;
   }

   /////////////////////////////////////////////////////////////

   double d0close = -1000.;
   double z0close = -1000.;
   double znumer = 0.;
   double zdenom = 0.;
   for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	track_iter != tracks_end;  ++track_iter) {
      KTHelix movetrack(*track_iter->pionHelix());
      double distance_moved;
      movetrack.moveToReferencePoint(bs,
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
	      other_iter != tracks_end;  ++other_iter) {
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
		  double perp(sqrt(sqr(tx - bs.x()) + sqr(ty - bs.y())));
		  double z_uncert2(tsig2z + sqr(tzsep) +
				   sqr(tx - bs.x()) +
				   sqr(ty - bs.y()));

		  znumer += tz / z_uncert2;
		  zdenom += 1. / z_uncert2;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over tracks

   double wz = -1000.;
   if (zdenom != 0.) {
      wz = znumer / zdenom;
      wz -= bs.z();
   }   

   double ccen = 0.;
   double neue = 0.;
   double neue_barrel = 0.;
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();
	shower_iter != showers_end;  ++shower_iter) {
      if (shower_iter->attributes().energy() > 0.01*eBeam->value()   &&
	  shower_iter->attributes().status()                         &&
	  // differs from EventProperties in requiring !hot
	  !shower_iter->attributes().hot()) {
	 ccen += shower_iter->attributes().energy();

	 if (shower_iter->noTrackMatch()                                &&
	     // data was processed in pre-2004 releases, so reject ConReg as well
	     shower_iter->noTrackMatchConReg()                            &&
	     (!shower_iter->bremTrack().valid()  ||
	      (shower_iter->bremTrack()->trackShowerMatch().valid()  &&
	       shower_iter->bremTrack()->trackShowerMatch()->eOverP() < 0.5))) {
	    neue += shower_iter->attributes().energy();

	    if (shower_iter->attributes().goodBarrel()) {
	       neue_barrel += shower_iter->attributes().energy();
	    }
	 }
      }
   }
   double coolvisen = (props->chargedEnergy() + neue) / 2. / eBeam->value();
   double frozenvisen = (props->chargedEnergy() + neue_barrel) / 2. / eBeam->value();
   neue = neue / 2. / eBeam->value();
   neue_barrel = neue_barrel / 2. / eBeam->value();
   ccen = ccen / 2. / eBeam->value();

   FATable<NavShower>::const_iterator s1 = showers_end;
   FATable<NavShower>::const_iterator s2 = showers_end;
   FATable<NavShower>::const_iterator s3 = showers_end;
   FATable<NavShower>::const_iterator breaks1 = showers_end;
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();
	shower_iter != showers_end;  ++shower_iter) {
      if (shower_iter->attributes().energy() > 0.01*eBeam->value()   &&
	  shower_iter->attributes().status()                         &&
          // differs from EventProperties in requiring !hot
	  !shower_iter->attributes().hot()) {
	 if (s1 == showers_end  ||  s1->attributes().energy() < shower_iter->attributes().energy()) {
	    s3 = s2;
	    s2 = s1;
	    s1 = shower_iter;
	 }
	 else if (s2 == showers_end  ||  s2->attributes().energy() < shower_iter->attributes().energy()) {
	    s3 = s2;
	    s2 = shower_iter;
	 }
	 else if (s3 == showers_end  ||  s3->attributes().energy() < shower_iter->attributes().energy()) {
	    s3 = shower_iter;
	 }

	 if (shower_iter->attributes().goodBarrel()) {
	    if (breaks1 == showers_end  ||  breaks1->attributes().energy() < shower_iter->attributes().energy()) {
	       breaks1 = shower_iter;
	    }
	 }
      }
   }
   double breake1 = -1000.;
   if (breaks1 != showers_end) breake1 = breaks1->attributes().energy() / eBeam->value();

   bool oppositesides = false;
   double e1 = 0.;
   double e2 = 0.;
   double e3 = 0.;
   int ring1 = -1000;
   int ring2 = -1000;
   int cell1 = -1000;
   int cell2 = -1000;
   double westphi = -1000.;
   double eastphi = -1000.;
   double westcotT = -1000.;
   double eastcotT = -1000.;
   double cotT = -1000.;
   if (s1 != showers_end  &&  s2 != showers_end) {
      oppositesides = cos(s1->attributes().theta()) * cos(s2->attributes().theta()) < 0.;
      e1 = s1->attributes().energy() / eBeam->value();
      e2 = s2->attributes().energy() / eBeam->value();
      ring1 = s1->attributes().ringId();
      ring2 = s2->attributes().ringId();
      cell1 = (s1->attributes().bigCellId() + 11) % 128;
      cell2 = (s2->attributes().bigCellId() + 11) % 128;

      if (oppositesides) {
	 FATable<NavShower>::const_iterator west = (cos(s1->attributes().theta()) > 0. ? s1 : s2);
	 FATable<NavShower>::const_iterator east = (cos(s1->attributes().theta()) > 0. ? s2 : s1);
	 if (true) {
	    double d = west->attributes().distance();
	    double th = west->attributes().theta();
	    double ph = west->attributes().phi();
	    westphi = atan2(d*sin(th)*sin(ph) - bs.y(),
			    d*sin(th)*cos(ph) - bs.x());
	    westcotT = (d*cos(th) - bs.z()) /
	       sqrt(sqr(d*sin(th)*cos(ph) - bs.x()) +
		    sqr(d*sin(th)*sin(ph) - bs.y()));
	 }
	 if (true) {
	    double d = east->attributes().distance();
	    double th = east->attributes().theta();
	    double ph = east->attributes().phi();
	    eastphi = atan2(d*sin(th)*sin(ph) - bs.y(),
			    d*sin(th)*cos(ph) - bs.x());
	    eastcotT = (d*cos(th) - bs.z()) /
	       sqrt(sqr(d*sin(th)*cos(ph) - bs.x()) +
		    sqr(d*sin(th)*sin(ph) - bs.y()));
	 }
	 cotT = (westcotT - eastcotT)/2.;
      }

      if (s3 != showers_end) {
	 e3 = s3->attributes().energy() / eBeam->value();
      }
   }

   bool oppositecharge = false;
   double eisr = -1000.;
   double econstraint = -1000.;
   double cos1 = -1000.;
   double cos2 = -1000.;
   double cosp = -1000.;
   double cosn = -1000.;
   FATable<NavTrack>::const_iterator t1 = tracks.find(props->firstTrackIdentifier());
   FATable<NavTrack>::const_iterator t2 = tracks.find(props->secondTrackIdentifier());
   if (t1 != tracks_end  &&  t2 != tracks_end) {
      oppositecharge = t1->pionHelix()->curvature() * t2->pionHelix()->curvature() < 0.;
      if (head->monteCarlo()) {
	 eisr = (t1->pionFit()->momentum() + t2->pionFit()->momentum()).mag();
      }
      else {
	 eisr = (t1->pionFit()->momentum() + t2->pionFit()->momentum() + Hep3Vector(0.025,0.,0.)).mag();
      }
      econstraint = 2.*eBeam->value() - t1->pionFit()->momentum().mag() - t2->pionFit()->momentum().mag() - eisr;
      
      eisr = eisr / eBeam->value();
      econstraint = econstraint / 2. / eBeam->value();

      cos1 = t1->pionHelix()->cotTheta() / sqrt(1. + sqr(t1->pionHelix()->cotTheta()));
      cos2 = t2->pionHelix()->cotTheta() / sqrt(1. + sqr(t2->pionHelix()->cotTheta()));

      if (oppositecharge) {
	 if (t1->pionHelix()->curvature() > 0.) {
	    cosp = cos1;
	    cosn = cos2;
	 }
	 else {
	    cosp = cos2;
	    cosn = cos1;
	 }
      }
   }

   double wpz = -1000.;
   for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
	track_iter != tracks_end;  ++track_iter) {
      if (! track_iter->seedQuality()->originUsed()             &&
	  ! track_iter->pionQuality()->fitAbort()               &&
	  1./fabs(track_iter->pionHelix()->curvature()) > 0.42  &&
	  ! track_iter->pionHelix()->hasNullErrorMatrix()       &&
	  // this is what differs from the wz cuts:
	  sqrt(fabs(track_iter->pionFit()->errorMatrix()(
		       KTKinematicData::kPz, KTKinematicData::kPz))) < 1.) {
	 if (wpz == -1000.) wpz = 0.;
	 wpz += track_iter->pionFit()->pz();
      }
   }
   if (wpz != -1000.) wpz = wpz / eBeam->value();

   double pdotp = -1000.;
//    FATable<NavTrack>::const_iterator anyt1 = tracks_end;
//    FATable<NavTrack>::const_iterator anyt2 = tracks_end;
//    for (FATable<NavTrack>::const_iterator track_iter = tracks.begin();
// 	track_iter != tracks_end;  ++track_iter) {
//       if (anyt1 == tracks_end  ||  anyt1->pionFit()->momentum().mag() < track_iter->pionFit()->momentum().mag()) {
// 	 anyt2 = anyt1;
// 	 anyt1 = track_iter;
//       }
//       else if (anyt2 == tracks_end  ||  anyt2->pionFit()->momentum().mag() < track_iter->pionFit()->momentum().mag()) {
// 	 anyt2 = track_iter;
//       }
//    }
//    if (anyt1 != tracks_end  &&  anyt2 != tracks_end) {
//       pdotp = anyt1->pionFit()->momentum().unit().dot(anyt2->pionFit()->momentum().unit());
//    }

   if (props->firstTrackIdentifier() > 0  &&
       props->secondTrackIdentifier() > 0) {
      FATable<NavTrack>::const_iterator tr1 = tracks.find(props->firstTrackIdentifier());
      FATable<NavTrack>::const_iterator tr2 = tracks.find(props->secondTrackIdentifier());
      if (tr1 != tracks.end()  &&  tr2 != tracks.end()) {
	 pdotp = tr1->pionFit()->momentum().unit().dot(tr2->pionFit()->momentum().unit());
      }
   }

   /////////////////////////////////////////////////////////////

   float v[GEE_Cut::kNumEntries];
   for (int i = 0;  i < GEE_Cut::kNumEntries;  i++) v[i] = -1000.;

   v[GEE_Cut::k_run] = head->run();
   v[GEE_Cut::k_event] = head->number();
   v[GEE_Cut::k_ebeam] = eBeam->value();
   if (m_runstats.value()) {
      v[GEE_Cut::k_eventfrac] = v[GEE_Cut::k_event] / float(stats->lastEvNum());
   }

   v[GEE_Cut::k_trignum] = (trig->isElTrack() ? 1. : 0.) + (trig->isRadTau() ? 2. : 0.) + (trig->isHadron() ? 4. : 0.);
   v[GEE_Cut::k_bbtrig] = (trig->isBarrelBhabha() ? 1. : 0.);
   v[GEE_Cut::k_tttrig] = (trig->isTwoTrack() ? 1. : 0.);
   v[GEE_Cut::k_eltrig] = (trig->isElTrack() ? 1. : 0.);
   v[GEE_Cut::k_hadtrig] = (trig->isHadron() ? 1. : 0.);

   v[GEE_Cut::k_d0close] = d0close;
   v[GEE_Cut::k_z0close] = z0close;
   v[GEE_Cut::k_logd0close] = log10(fabs(d0close));
   v[GEE_Cut::k_logz0close] = log10(fabs(z0close));
   v[GEE_Cut::k_wz] = wz;
   v[GEE_Cut::k_logwz] = log10(fabs(wz));
   v[GEE_Cut::k_criticalz0close] = (wz == -1000. ? z0close : -1000.);
   v[GEE_Cut::k_criticallogz0close] = (wz == -1000. ? log10(fabs(z0close)) : -1000.);
   v[GEE_Cut::k_anyz] = (wz == -1000. ? z0close : wz);
   v[GEE_Cut::k_loganyz] = (wz == -1000. ? (z0close == -1000. ? -1000. : log10(z0close)) : log10(wz));
   v[GEE_Cut::k_p1] = props->firstLargestPTrack() / eBeam->value();
   v[GEE_Cut::k_p2] = props->secondLargestPTrack() / eBeam->value();
   v[GEE_Cut::k_visen] = (props->chargedEnergy() + props->neutralEnergy()) / 2. / eBeam->value();
   v[GEE_Cut::k_coolvisen] = coolvisen;
   v[GEE_Cut::k_frozenvisen] = frozenvisen;

   v[GEE_Cut::k_tracks] = props->nbChargedTracks();  // these are "quality" tracks
   v[GEE_Cut::k_rawtk] = tracks.size();              // these ain't
   v[GEE_Cut::k_oppositesides] = oppositesides;
   v[GEE_Cut::k_e1] = e1;
   v[GEE_Cut::k_e2] = e2;
   v[GEE_Cut::k_e1GeV] = e1 * eBeam->value();
   v[GEE_Cut::k_e2GeV] = e2 * eBeam->value();
   v[GEE_Cut::k_e3GeV] = e3 * eBeam->value();
   if (oppositesides) v[GEE_Cut::k_1_is_west] = (cos(s1->attributes().theta()) > 0 ? 1. : 0.);
   v[GEE_Cut::k_ring1] = ring1;
   v[GEE_Cut::k_ring2] = ring2;
   v[GEE_Cut::k_cell1] = cell1;
   v[GEE_Cut::k_cell2] = cell2;
   v[GEE_Cut::k_westphi] = westphi;
   v[GEE_Cut::k_eastphi] = eastphi;
   v[GEE_Cut::k_westcotT] = westcotT;
   v[GEE_Cut::k_eastcotT] = eastcotT;
   v[GEE_Cut::k_cotT] = cotT;
   v[GEE_Cut::k_thetab2b] = westcotT + eastcotT;
   v[GEE_Cut::k_phib2b] = sin(westphi - eastphi);

   v[GEE_Cut::k_oppositecharge] = oppositecharge;
   v[GEE_Cut::k_eisr] = eisr;
   v[GEE_Cut::k_econstr] = econstraint;
   v[GEE_Cut::k_cos1] = cos1;
   v[GEE_Cut::k_cos2] = cos2;
   v[GEE_Cut::k_cosp] = cosp;
   v[GEE_Cut::k_cosn] = cosn;

   v[GEE_Cut::k_wpz] = wpz;
   v[GEE_Cut::k_pdotp] = pdotp;
   v[GEE_Cut::k_logpdotp] = log10(1.-fabs(pdotp));
   v[GEE_Cut::k_ccen] = ccen;
   v[GEE_Cut::k_neue] = neue;

   v[GEE_Cut::k_l4dec] = l4dec->decision();
   v[GEE_Cut::k_olde1] = props->firstLargestEShower() / eBeam->value();
   v[GEE_Cut::k_olde2] = props->secondLargestEShower() / eBeam->value();
   v[GEE_Cut::k_oldccen] = props->ccTotalEnergy() / 2. / eBeam->value();
   v[GEE_Cut::k_ccenGeV] = ccen * 2. * eBeam->value();
   v[GEE_Cut::k_chen] = props->chargedEnergy() / 2. / eBeam->value();
   v[GEE_Cut::k_breake1] = breake1;

   /////////////////////////////////////////////////////////////

   m_cut.update(v);
   m_cut.fill();
   m_cut.fill_extra();

   m_hadron.update(v);
   m_hadron.fill();
   m_hadron.fill_extra();

   m_hadroncool.update(v);
   m_hadroncool.fill();
   m_hadroncool.fill_extra();

   m_oldhadron.update(v);
   m_oldhadron.fill();
   m_oldhadron.fill_extra();

   m_oldhadronall.update(v);
   m_oldhadronall.fill();
   m_oldhadronall.fill_extra();

   m_gamgam.update(v);
   m_gamgam.fill();
   m_gamgam.fill_extra();

   m_trackless.update(v);
   m_trackless.fill();
   m_trackless.fill_extra();

   m_bhabha.update(v);
   m_bhabha.fill();
   m_bhabha.fill_extra();

   m_mupair.update(v);
   m_mupair.fill();
   m_mupair.fill_extra();

   m_bhabhatwotrack.update(v);
   m_bhabhatwotrack.fill();
   m_bhabhatwotrack.fill_extra();

   m_mupairtwotrack.update(v);
   m_mupairtwotrack.fill();
   m_mupairtwotrack.fill_extra();

   m_cosmic.update(v);
   m_cosmic.fill();
   m_cosmic.fill_extra();

   m_beamgase.update(v);
   m_beamgase.fill();
   m_beamgase.fill_extra();

   m_beamgasp.update(v);
   m_beamgasp.fill();
   m_beamgasp.fill_extra();

   m_brokenshower.update(v);
   m_brokenshower.fill();
   m_brokenshower.fill_extra();

   m_brokenshower2.update(v);
   m_brokenshower2.fill();
   m_brokenshower2.fill_extra();

   m_ccstudy1.update(v);
   m_ccstudy1.fill();
   m_ccstudy1.fill_extra();

//    m_ccstudy2.update(v);
//    m_ccstudy2.fill();
//    m_ccstudy2.fill_extra();

//    m_ccstudy3.update(v);
//    m_ccstudy3.fill();
//    m_ccstudy3.fill_extra();

//    m_ccstudy4.update(v);
//    m_ccstudy4.fill();
//    m_ccstudy4.fill_extra();

   //////////////////////////////////////////////////////////

   float w[kNumEntries];
   w[k_run] = head->run();
   w[k_event] = head->number();
   w[k_trig] = ((trig->isHadron()       ? 1.     : 0.) +
		(trig->isRadTau()       ? 10.    : 0.) +
		(trig->isElTrack()      ? 100.   : 0.) +
		(trig->isTwoTrack()     ? 1000.  : 0.) +
		(trig->isBarrelBhabha() ? 10000. : 0.));
   w[k_type] = ((m_hadroncool.survive() ? 1.       : 0.) +
		(m_gamgam.survive()     ? 10.      : 0.) +
		(m_bhabha.survive()     ? 100.     : 0.) +
		(m_mupair.survive()     ? 1000.    : 0.) +
		(m_cosmic.survive()     ? 10000.   : 0.) +
		(m_beamgase.survive()   ? 100000.  : 0.) +
		(m_beamgasp.survive()   ? 1000000. : 0.));
   w[k_d0close] = d0close;
   w[k_anyz] = (wz == -1000. ? z0close : wz);
   if (t1 != tracks.end()) {
      w[k_p1x] = t1->pionFit()->momentum().x();
      w[k_p1y] = t1->pionFit()->momentum().y();
      w[k_p1z] = t1->pionFit()->momentum().z();
   }
   else {
      w[k_p1x] = -1000.;
      w[k_p1y] = -1000.;
      w[k_p1z] = -1000.;
   }
   if (t2 != tracks.end()) {
      w[k_p2x] = t2->pionFit()->momentum().x();
      w[k_p2y] = t2->pionFit()->momentum().y();
      w[k_p2z] = t2->pionFit()->momentum().z();
   }
   else {
      w[k_p2x] = -1000.;
      w[k_p2y] = -1000.;
      w[k_p2z] = -1000.;
   }
   w[k_visen] = (props->chargedEnergy() + props->neutralEnergy()) / 2. / eBeam->value();
   w[k_coolvisen] = coolvisen;
   w[k_frozenvisen] = frozenvisen;
   w[k_tracks] = props->nbChargedTracks();
   w[k_rawtk] = tracks.size();
   w[k_oppositesides] = oppositesides;
   w[k_e1] = e1;
   w[k_e2] = e2;
   w[k_e3] = e3;
   if (s1 != showers_end) {
      double d = s1->attributes().distance();
      double th = s1->attributes().theta();
      double ph = s1->attributes().phi();
      w[k_phi1] = atan2(d*sin(th)*sin(ph) - bs.y(),
		      d*sin(th)*cos(ph) - bs.x());
      w[k_cos1] = (d*cos(th) - bs.z()) /
	 sqrt(sqr(d*sin(th)*cos(ph) - bs.x()) +
	      sqr(d*sin(th)*sin(ph) - bs.y()) +
	      sqr(d*cos(th) - bs.z()));
   }
   else {
      w[k_phi1] = -1000.;
      w[k_cos1] = -1000.;
   }
   if (s2 != showers_end) {
      double d = s2->attributes().distance();
      double th = s2->attributes().theta();
      double ph = s2->attributes().phi();
      w[k_phi2] = atan2(d*sin(th)*sin(ph) - bs.y(),
		      d*sin(th)*cos(ph) - bs.x());
      w[k_cos2] = (d*cos(th) - bs.z()) /
	 sqrt(sqr(d*sin(th)*cos(ph) - bs.x()) +
	      sqr(d*sin(th)*sin(ph) - bs.y()) +
	      sqr(d*cos(th) - bs.z()));
   }
   else {
      w[k_phi1] = -1000.;
      w[k_cos1] = -1000.;
   }
   w[k_oppositecharge] = oppositecharge;
   w[k_eisr] = eisr;
   w[k_econstr] = econstraint;
   w[k_cosp] = cosp;
   w[k_cosn] = cosn;
   w[k_wpz] = wpz;
   w[k_pdotp] = pdotp;
   w[k_ccen] = ccen;
   w[k_neue] = neue;
   w[k_l4dec] = l4dec->decision();
   w[k_chen] = props->chargedEnergy() / 2. / eBeam->value();
   m_ntuple->fill(w);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
UpsilonGammaEEAnalysisProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
UpsilonGammaEEAnalysisProc::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

bool
UpsilonGammaEEAnalysisProc::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep, KTHelix& a, KTHelix& b)
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
UpsilonGammaEEAnalysisProc::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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

GEE_Cut::GEE_Cut()
{
   m_name = string("all");
}

void GEE_Cut::prepare_hist(int release, int var, int bins, double low, double high, const char* name)
{
   m_hist.push_back(NULL);
   m_hist_var.push_back(var);
   m_hist_name.push_back(name);
   m_hist_release.push_back(release);
   m_hist_bins.push_back(bins);
   m_hist_loww.push_back(low);
   m_hist_high.push_back(high);
}

void GEE_Cut::prepare_count(const char* name)
{
   m_cut.push_back(false);
   m_cut_tight.push_back(false);
   m_count_name.push_back(name);
   m_count_release.push_back(0);
   m_count_tighten.push_back(0);
}

void GEE_Cut::histbook(HIHistoManager& iHistoManager)
{
   m_vstime = iHistoManager.histogram(m_name+string("_vstime"), 100, 0., 1.);

   for (int j = 0;  j < m_hist.size();  j++) {
      m_hist[j] = iHistoManager.histogram(
	 m_name+m_hist_name[j], m_hist_bins[j], m_hist_loww[j], m_hist_high[j]);
   }
}

void GEE_Cut::histbook_extra(HIHistoManager& iHistoManager)
{
}

void GEE_Cut::update(float* event) {
   v = event;

   m_run = v[k_run];
   m_lastevent = v[k_event];
   m_ebeam = v[k_ebeam];
}

bool GEE_Cut::survive()
{
   bool tmp = true;
   for (int i = 0;  i < m_cut.size();  i++) {
      tmp = tmp && m_cut[i];
   }
   return tmp;
}

void GEE_Cut::fill()
{
   for (int j = 0;  j < m_hist.size();  j++) {
      bool fillit = true;
      for (int i = 0;  i < m_cut.size();  i++) {
	 if (m_hist_release[j] != i) {
	    fillit = fillit && m_cut[i];
	 }
      }
      
      if (fillit) {
	 m_hist[j]->fill(v[m_hist_var[j]]);
      }
   }

   if (survive()) m_count++;
   for (int j = 0;  j < m_cut.size();  j++) {
      bool fillit = true;
      for (int i = 0;  i < m_cut.size();  i++) {
	 if (i != j) {
	    fillit = fillit && m_cut[i];
	 }
      }

      if (fillit) {
	 m_count_release[j]++;
      }
   }
   for (int j = 0;  j < m_cut.size();  j++) {
      if (survive() && m_cut_tight[j]) {
	 m_count_tighten[j]++;
      }
   }

   if (survive()) m_vstime->fill(v[k_eventfrac]);
}

void GEE_Cut::fill_extra()
{
}

void GEE_Cut::print()
{
   // only the superclass gets to print out this header
   if (m_cut.size() == 0) {
      cout << "PYTHON rec = RunRecord()" << endl;
      cout << "PYTHON rec.run = " << m_run << endl;
      cout << "PYTHON rec.lastevent = " << m_lastevent << endl;
      cout << "PYTHON rec.ebeam = " << m_ebeam << endl;
   }

   cout << "PYTHON rec." << m_name.c_str() << " = " << m_count << endl;
   for (int j = 0;  j < m_cut.size();  j++) {
      cout << "PYTHON rec." << m_name.c_str() << "_release_" << m_count_name[j]
	   << " = " << m_count_release[j] << endl;
      cout << "PYTHON rec." << m_name.c_str() << "_tighten_" << m_count_name[j]
	   << " = " << m_count_tighten[j] << endl;
   }

   for (int j = 0;  j < m_hist.size();  j++) {
      print_hist1(m_name + string("_") + m_hist_name[j], m_hist[j]);
   }
   print_hist1(m_name + string("_vstime"), m_vstime);
}

void GEE_Cut::print_extra()
{
}

void GEE_Cut::print_hist1(string& name, HIHist1D* hist)
{
   cout << "PYTHON rec." << name.c_str() << " = hist.h1("
	<< hist->nChannels() << ", " << hist->lowEdge() << ", " << hist->highEdge()
	<< ", vals=[";
   for (int i = 1;  i <= hist->nChannels();  i++) cout << hist->channelValue(i) << ", ";
   cout << "], underflow=" << hist->underflow()
	<< ", overflow=" << hist->overflow() << ").rootn()" << endl;
}

void GEE_Cut::print_hist2(string& name, HIHist2D* hist)
{
   cout << "PYTHON rec." << name.c_str() << " = Numeric.array([";
   for (int i = 1;  i <= hist->nChannelsX();  i++) {
      cout << "[";
      for (int j = 1;  j <= hist->nChannelsY();  j++) {
	 cout << hist->channelValue(i,j) << ", ";
      }
      cout << "], ";
   }
   cout << "])" << endl;
}

////////////////////////////////////////////////

GEE_Hadron::GEE_Hadron()
{
   m_name = string("hadron");

   prepare_hist(0, k_trignum,              8, -0.5,  7.5,  "trig");
   prepare_hist(1, k_d0close,            120, -0.06, 0.06, "d0close");
   prepare_hist(1, k_logd0close,         140, -7.,   0.,   "logd0close");
   prepare_hist(2, k_wz,                 100, -0.10, 0.10, "wz");
   prepare_hist(2, k_logwz,              120, -6.,   0.,   "logwz");
   prepare_hist(2, k_criticalz0close,    100, -0.10, 0.10, "criticalz0close");
   prepare_hist(2, k_criticallogz0close, 120, -6.,   0.,   "criticallogz0close");
   prepare_hist(2, k_anyz,               100, -0.10, 0.10, "anyz");
   prepare_hist(2, k_loganyz,            120, -6.,   0.,   "loganyz");
   prepare_hist(3, k_p1,                 120,  0.,   1.2,  "p1");
   prepare_hist(4, k_coolvisen,          120,  0.,   1.2,  "cvisen");
   prepare_hist(4, k_visen,              120,  0.,   1.2,  "hotvisen");
   prepare_hist(4, k_frozenvisen,        120,  0.,   1.2,  "fvisen");
   prepare_hist(-1,k_tracks,              19, -0.5, 18.5,  "tracks");

   prepare_count("trig");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("p1");
   prepare_count("fvisen");
   prepare_count("l4dec");
}

void GEE_Hadron::update(float* event) {
   v = event;

   m_cut[0] = (v[k_trignum] > 0);
   m_cut[1] = (fabs(v[k_d0close]) < 0.005);
   m_cut[2] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[3] = (v[k_p1] < 0.8);
   m_cut[4] = (v[k_frozenvisen] > 0.4);
   m_cut[5] = (v[k_l4dec] > 0.);

   m_cut_tight[0] = (v[k_trignum] > 5);
   m_cut_tight[1] = (fabs(v[k_d0close]) < 0.001);
   m_cut_tight[2] = (fabs(v[k_wz]) < 0.04  ||
		       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.04));
   m_cut_tight[3] = (v[k_p1] < 0.7);
   m_cut_tight[4] = (v[k_frozenvisen] > 0.5);
   m_cut_tight[5] = m_cut[5];
}

void GEE_Hadron::histbook_extra(HIHistoManager& iHistoManager)
{
   m_g2tracks = 0;
   m_g4tracks = 0;

   m_trignum = iHistoManager.histogram("r_trig", 8, -0.5, 7.5);
   m_d0close = iHistoManager.histogram("r_d0close", 120, -0.06, 0.06);
   m_logd0close = iHistoManager.histogram("r_logd0close", 140, -7., 0.);
   m_wz = iHistoManager.histogram("r_wz", 100, -0.10, 0.10);
   m_logwz = iHistoManager.histogram("r_logwz", 120, -6., 0.);
   m_criticalz0close = iHistoManager.histogram("r_criticalz0close", 100, -0.10, 0.10);
   m_criticallogz0close = iHistoManager.histogram("r_criticallogz0close", 120, -6., 0.);
   m_anyz = iHistoManager.histogram("r_anyz", 100, -0.10, 0.10);
   m_loganyz = iHistoManager.histogram("r_anyz", 120, -6., 0.);
   m_p1 = iHistoManager.histogram("r_p1", 120, 0., 1.2);
   m_coolvisen = iHistoManager.histogram("r_cvisen", 120, 0., 1.2);
   m_hotvisen = iHistoManager.histogram("r_hotvisen", 120, 0., 1.2);
   m_frozenvisen = iHistoManager.histogram("r_fvisen", 120, 0., 1.2);
   m_tracks = iHistoManager.histogram("r_tracks", 19, -0.5, 18.5);

   m_trignum_count = 0;
   m_d0close_count = 0;
   m_wz_count = 0;
   m_p1_count = 0;
   m_frozenvisen_count = 0;
   m_l4dec_count = 0;

   m_p1fail = 0;
   m_p1fail_bhabha = 0;
   m_p1fail_mupair = 0;
}

void GEE_Hadron::fill_extra()
{
   m_trignum->fill(v[k_trignum]);

   if (m_cut[0] && m_cut[1] && m_cut[2] && !m_cut[3] && m_cut[4] && m_cut[5]) {
      m_p1fail++;

      if ((v[k_trignum] > 0) &&
	  (v[k_oppositecharge] > 0) &&
	  (v[k_p2] > 0.7) &&
	  (fabs(v[k_d0close]) < 0.005) &&
	  (fabs(v[k_wz]) < 0.075  ||  (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075)) &&
	  (v[k_eisr] < 0.2) &&
	  (v[k_econstr] < 0.2) &&
	  ((v[k_cos1] < 0.79  &&  v[k_cos2] < 0.76) || (v[k_cos1] < 0.76  &&  v[k_cos2] < 0.79)) &&
	  (v[k_e2] > 0.4) &&
	  (v[k_l4dec] > 0)) {
	 m_p1fail_bhabha++;
      }
      if ((v[k_trignum] > 0) &&
	  (v[k_oppositecharge] > 0) &&
	  (v[k_p2] > 0.7) &&
	  (fabs(v[k_d0close]) < 0.005) &&
	  (fabs(v[k_wz]) < 0.075  ||  (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075)) &&
	  (v[k_eisr] < 0.2) &&
	  (v[k_econstr] < 0.2) &&
	  ((v[k_cos1] < 0.79  &&  v[k_cos2] < 0.76) || (v[k_cos1] < 0.76  &&  v[k_cos2] < 0.79)) &&
	  (v[k_e2GeV] < 1.) &&
	  (v[k_l4dec] > 0)) {
	 m_p1fail_mupair++;
      }
   }

   if (m_cut[0]) {
      m_trignum_count++;

      m_d0close->fill(v[k_d0close]);
      m_logd0close->fill(v[k_logd0close]);
      
      if (m_cut[1]) {
	 m_d0close_count++;

	 m_wz->fill(v[k_wz]);
	 m_logwz->fill(v[k_logwz]);
	 m_criticalz0close->fill(v[k_criticalz0close]);
	 m_criticallogz0close->fill(v[k_criticallogz0close]);
	 m_anyz->fill(v[k_anyz]);
	 m_loganyz->fill(v[k_loganyz]);

	 if (m_cut[2]) {
	    m_wz_count++;

	    m_p1->fill(v[k_p1]);

	    if (m_cut[3]) {
	       m_p1_count++;

	       m_coolvisen->fill(v[k_coolvisen]);
	       m_hotvisen->fill(v[k_visen]);
	       m_frozenvisen->fill(v[k_frozenvisen]);

	       if (m_cut[4]) {
		  m_frozenvisen_count++;

		  if (m_cut[5]) {
		     m_l4dec_count++;

		     m_tracks->fill(v[k_tracks]);

		     if (v[k_tracks] > 2) {
			m_g2tracks++;

			if (v[k_tracks] > 4) {
			   m_g4tracks++;
			}
		     }
		  }
	       }
	    }
	 }
      }
   }
}

void GEE_Hadron::print_extra()
{
   cout << "PYTHON rec." << m_name.c_str() << "_g2tracks = " << m_g2tracks << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_g4tracks = " << m_g4tracks << endl;

   print_hist1(m_name + string("_r_trignum"), m_trignum);
   print_hist1(m_name + string("_r_d0close"), m_d0close);
   print_hist1(m_name + string("_r_logd0close"), m_logd0close);
   print_hist1(m_name + string("_r_wz"), m_wz);
   print_hist1(m_name + string("_r_logwz"), m_logwz);
   print_hist1(m_name + string("_r_criticalz0close"), m_criticalz0close);
   print_hist1(m_name + string("_r_criticallogz0close"), m_criticallogz0close);
   print_hist1(m_name + string("_r_anyz"), m_wz);
   print_hist1(m_name + string("_r_loganyz"), m_logwz);
   print_hist1(m_name + string("_r_p1"), m_p1);
   print_hist1(m_name + string("_r_coolvisen"), m_coolvisen);
   print_hist1(m_name + string("_r_hotvisen"), m_hotvisen);
   print_hist1(m_name + string("_r_frozenvisen"), m_frozenvisen);
   print_hist1(m_name + string("_r_tracks"), m_tracks);

   cout << "PYTHON rec." << m_name.c_str() << "_trignum_count = " << m_trignum_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_d0close_count = " << m_d0close_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_wz_count = " << m_wz_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_p1_count = " << m_p1_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_frozenvisen_count = " << m_frozenvisen_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_l4dec_count = " << m_l4dec_count << endl;

   cout << "PYTHON rec." << m_name.c_str() << "_p1fail = " << m_p1fail << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_p1fail_bhabha = " << m_p1fail_bhabha << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_p1fail_mupair = " << m_p1fail_mupair << endl;
}

////////////////////////////////////////////////

GEE_HadronCool::GEE_HadronCool()
{
   m_name = string("hadroncool");

   prepare_hist(0, k_trignum,              8, -0.5,  7.5,  "trig");
   prepare_hist(1, k_d0close,            120, -0.06, 0.06, "d0close");
   prepare_hist(1, k_logd0close,         140, -7.,   0.,   "logd0close");
   prepare_hist(2, k_wz,                 100, -0.10, 0.10, "wz");
   prepare_hist(2, k_logwz,              120, -6.,   0.,   "logwz");
   prepare_hist(2, k_criticalz0close,    100, -0.10, 0.10, "criticalz0close");
   prepare_hist(2, k_criticallogz0close, 120, -6.,   0.,   "criticallogz0close");
   prepare_hist(2, k_anyz,               100, -0.10, 0.10, "anyz");
   prepare_hist(2, k_loganyz,            120, -6.,   0.,   "loganyz");
   prepare_hist(3, k_p1,                 120,  0.,   1.2,  "p1");
   prepare_hist(4, k_coolvisen,          120,  0.,   1.2,  "cvisen");
   prepare_hist(4, k_visen,              120,  0.,   1.2,  "hotvisen");
   prepare_hist(4, k_frozenvisen,        120,  0.,   1.2,  "fvisen");
   prepare_hist(-1,k_tracks,              19, -0.5, 18.5,  "tracks");

   prepare_count("trig");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("p1");
   prepare_count("cvisen");
   prepare_count("l4dec");
}

void GEE_HadronCool::update(float* event) {
   v = event;

   m_cut[0] = (v[k_trignum] > 0);
   m_cut[1] = (fabs(v[k_d0close]) < 0.005);
   m_cut[2] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[3] = (v[k_p1] < 0.8);
   m_cut[4] = (v[k_coolvisen] > 0.4);
   m_cut[5] = (v[k_l4dec] > 0.);

   m_cut_tight[0] = (v[k_trignum] > 5);
   m_cut_tight[1] = (fabs(v[k_d0close]) < 0.001);
   m_cut_tight[2] = (fabs(v[k_wz]) < 0.04  ||
		       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.04));
   m_cut_tight[3] = (v[k_p1] < 0.7);
   m_cut_tight[4] = (v[k_coolvisen] > 0.5);
   m_cut_tight[5] = m_cut[5];
}

void GEE_HadronCool::histbook_extra(HIHistoManager& iHistoManager)
{
   m_g2tracks = 0;
   m_g4tracks = 0;

   m_trignum = iHistoManager.histogram("r_trig", 8, -0.5, 7.5);
   m_d0close = iHistoManager.histogram("r_d0close", 120, -0.06, 0.06);
   m_logd0close = iHistoManager.histogram("r_logd0close", 140, -7., 0.);
   m_wz = iHistoManager.histogram("r_wz", 100, -0.10, 0.10);
   m_logwz = iHistoManager.histogram("r_logwz", 120, -6., 0.);
   m_criticalz0close = iHistoManager.histogram("r_criticalz0close", 100, -0.10, 0.10);
   m_criticallogz0close = iHistoManager.histogram("r_criticallogz0close", 120, -6., 0.);
   m_anyz = iHistoManager.histogram("r_anyz", 100, -0.10, 0.10);
   m_loganyz = iHistoManager.histogram("r_anyz", 120, -6., 0.);
   m_p1 = iHistoManager.histogram("r_p1", 120, 0., 1.2);
   m_coolvisen = iHistoManager.histogram("r_cvisen", 120, 0., 1.2);
   m_hotvisen = iHistoManager.histogram("r_hotvisen", 120, 0., 1.2);
   m_frozenvisen = iHistoManager.histogram("r_fvisen", 120, 0., 1.2);
   m_tracks = iHistoManager.histogram("r_tracks", 19, -0.5, 18.5);

   m_trignum_count = 0;
   m_d0close_count = 0;
   m_wz_count = 0;
   m_p1_count = 0;
   m_coolvisen_count = 0;
   m_l4dec_count = 0;

   m_p1fail = 0;
   m_p1fail_bhabha = 0;
   m_p1fail_mupair = 0;
}

void GEE_HadronCool::fill_extra()
{
   m_trignum->fill(v[k_trignum]);

   if (m_cut[0] && m_cut[1] && m_cut[2] && !m_cut[3] && m_cut[4] && m_cut[5]) {
      m_p1fail++;

      if ((v[k_trignum] > 0) &&
	  (v[k_oppositecharge] > 0) &&
	  (v[k_p2] > 0.7) &&
	  (fabs(v[k_d0close]) < 0.005) &&
	  (fabs(v[k_wz]) < 0.075  ||  (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075)) &&
	  (v[k_eisr] < 0.2) &&
	  (v[k_econstr] < 0.2) &&
	  ((v[k_cos1] < 0.79  &&  v[k_cos2] < 0.76) || (v[k_cos1] < 0.76  &&  v[k_cos2] < 0.79)) &&
	  (v[k_e2] > 0.4) &&
	  (v[k_l4dec] > 0)) {
	 m_p1fail_bhabha++;
      }
      if ((v[k_trignum] > 0) &&
	  (v[k_oppositecharge] > 0) &&
	  (v[k_p2] > 0.7) &&
	  (fabs(v[k_d0close]) < 0.005) &&
	  (fabs(v[k_wz]) < 0.075  ||  (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075)) &&
	  (v[k_eisr] < 0.2) &&
	  (v[k_econstr] < 0.2) &&
	  ((v[k_cos1] < 0.79  &&  v[k_cos2] < 0.76) || (v[k_cos1] < 0.76  &&  v[k_cos2] < 0.79)) &&
	  (v[k_e2GeV] < 1.) &&
	  (v[k_l4dec] > 0)) {
	 m_p1fail_mupair++;
      }
   }

   if (m_cut[0]) {
      m_trignum_count++;

      m_d0close->fill(v[k_d0close]);
      m_logd0close->fill(v[k_logd0close]);
      
      if (m_cut[1]) {
	 m_d0close_count++;

	 m_wz->fill(v[k_wz]);
	 m_logwz->fill(v[k_logwz]);
	 m_criticalz0close->fill(v[k_criticalz0close]);
	 m_criticallogz0close->fill(v[k_criticallogz0close]);
	 m_anyz->fill(v[k_anyz]);
	 m_loganyz->fill(v[k_loganyz]);

	 if (m_cut[2]) {
	    m_wz_count++;

	    m_p1->fill(v[k_p1]);

	    if (m_cut[3]) {
	       m_p1_count++;

	       m_coolvisen->fill(v[k_coolvisen]);
	       m_hotvisen->fill(v[k_visen]);
	       m_frozenvisen->fill(v[k_frozenvisen]);

	       if (m_cut[4]) {
		  m_coolvisen_count++;

		  if (m_cut[5]) {
		     m_l4dec_count++;

		     m_tracks->fill(v[k_tracks]);

		     if (v[k_tracks] > 2) {
			m_g2tracks++;

			if (v[k_tracks] > 4) {
			   m_g4tracks++;
			}
		     }
		  }
	       }
	    }
	 }
      }
   }
}

void GEE_HadronCool::print_extra()
{
   cout << "PYTHON rec." << m_name.c_str() << "_g2tracks = " << m_g2tracks << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_g4tracks = " << m_g4tracks << endl;

   print_hist1(m_name + string("_r_trignum"), m_trignum);
   print_hist1(m_name + string("_r_d0close"), m_d0close);
   print_hist1(m_name + string("_r_logd0close"), m_logd0close);
   print_hist1(m_name + string("_r_wz"), m_wz);
   print_hist1(m_name + string("_r_logwz"), m_logwz);
   print_hist1(m_name + string("_r_criticalz0close"), m_criticalz0close);
   print_hist1(m_name + string("_r_criticallogz0close"), m_criticallogz0close);
   print_hist1(m_name + string("_r_anyz"), m_wz);
   print_hist1(m_name + string("_r_loganyz"), m_logwz);
   print_hist1(m_name + string("_r_p1"), m_p1);
   print_hist1(m_name + string("_r_coolvisen"), m_coolvisen);
   print_hist1(m_name + string("_r_hotvisen"), m_hotvisen);
   print_hist1(m_name + string("_r_frozenvisen"), m_frozenvisen);
   print_hist1(m_name + string("_r_tracks"), m_tracks);

   cout << "PYTHON rec." << m_name.c_str() << "_trignum_count = " << m_trignum_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_d0close_count = " << m_d0close_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_wz_count = " << m_wz_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_p1_count = " << m_p1_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_coolvisen_count = " << m_coolvisen_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_l4dec_count = " << m_l4dec_count << endl;

   cout << "PYTHON rec." << m_name.c_str() << "_p1fail = " << m_p1fail << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_p1fail_bhabha = " << m_p1fail_bhabha << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_p1fail_mupair = " << m_p1fail_mupair << endl;
}

////////////////////////////////////////////////

GEE_Oldhadron::GEE_Oldhadron()
{
   m_name = string("oldhadron");

   prepare_hist(0, k_trignum,              8, -0.5,  7.5,  "trig");
   prepare_hist(1, k_d0close,            120, -0.06, 0.06, "d0close");
   prepare_hist(1, k_logd0close,         140, -7.,   0.,   "logd0close");
   prepare_hist(2, k_wz,                 100, -0.10, 0.10, "wz");
   prepare_hist(2, k_logwz,              120, -6.,   0.,   "logwz");
   prepare_hist(2, k_criticalz0close,    100, -0.10, 0.10, "criticalz0close");
   prepare_hist(2, k_criticallogz0close, 120, -6.,   0.,   "criticallogz0close");
   prepare_hist(2, k_anyz,               100, -0.10, 0.10, "anyz");
   prepare_hist(2, k_loganyz,            120, -6.,   0.,   "loganyz");
   prepare_hist(3, k_olde1,              120,  0.,   1.2,  "olde1");
   prepare_hist(4, k_p2,                 120,  0.,   1.2,  "p2");
   prepare_hist(5, k_visen,              120,  0.,   1.2,  "visen");
   prepare_hist(-1,k_wpz,                100, -1.,   1.,   "wpz");
   prepare_hist(5, k_wpz,                100, -1.,   1.,   "wpz_twophoton");
   prepare_hist(-1,k_pdotp,              100, -1.,   1.,   "pdotp");
   prepare_hist(-1,k_logpdotp,           100, -10.,  0.,   "logpdotp");
   prepare_hist(5, k_pdotp,              100, -1.,   1.,   "pdotp_twophoton");
   prepare_hist(5, k_logpdotp,           100, -10.,  0.,   "logpdotp_twophoton");

   prepare_count("trig");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("olde1");
   prepare_count("p2");
   prepare_count("visen");
   prepare_count("l4dec");
}

void GEE_Oldhadron::update(float* event) {
   v = event;

   m_cut[0] = (v[k_trignum] > 0);
   m_cut[1] = (fabs(v[k_d0close]) < 0.005);
   m_cut[2] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[3] = (v[k_olde1] < 0.85);
   m_cut[4] = (v[k_p2] < 0.85);
   m_cut[5] = (v[k_visen] > 0.35);
   m_cut[6] = (v[k_l4dec] > 0);

   m_cut_tight[0] = (v[k_trignum] > 5);
   m_cut_tight[1] = (fabs(v[k_d0close]) < 0.001);
   m_cut_tight[2] = (fabs(v[k_wz]) < 0.04  ||
		       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.04));
   m_cut_tight[3] = (v[k_olde1] < 0.75);
   m_cut_tight[4] = (v[k_p2] < 0.75);
   m_cut_tight[5] = (v[k_visen] > 0.45);
   m_cut_tight[6] = m_cut[6];

}

////////////////////////////////////////////////

GEE_Oldhadronall::GEE_Oldhadronall()
{
   m_name = string("oldhadronall");

   prepare_hist(0, k_trignum,              8, -0.5,  7.5,  "trig");
   prepare_hist(1, k_d0close,            120, -0.06, 0.06, "d0close");
   prepare_hist(1, k_logd0close,         140, -7.,   0.,   "logd0close");
   prepare_hist(2, k_wz,                 100, -0.10, 0.10, "wz");
   prepare_hist(2, k_logwz,              120, -6.,   0.,   "logwz");
   prepare_hist(2, k_criticalz0close,    100, -0.10, 0.10, "criticalz0close");
   prepare_hist(2, k_criticallogz0close, 120, -6.,   0.,   "criticallogz0close");
   prepare_hist(2, k_anyz,               100, -0.10, 0.10, "anyz");
   prepare_hist(2, k_loganyz,            120, -6.,   0.,   "loganyz");
   prepare_hist(3, k_olde1,              120,  0.,   1.2,  "olde1");
   prepare_hist(4, k_p2,                 120,  0.,   1.2,  "p2");
   prepare_hist(5, k_visen,              120,  0.,   1.2,  "visen");
   prepare_hist(7, k_tracks,              19, -0.5, 18.5,  "tracks");
   prepare_hist(8, k_oldccen,            120,  0.,   1.2,  "oldccen");

   prepare_count("trig");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("olde1");
   prepare_count("p2");
   prepare_count("visen");
   prepare_count("l4dec");
   prepare_count("tracks");
   prepare_count("oldccen");
}

void GEE_Oldhadronall::update(float* event) {
   v = event;

   m_cut[0] = (v[k_trignum] > 0);
   m_cut[1] = (fabs(v[k_d0close]) < 0.005);
   m_cut[2] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[3] = (v[k_olde1] < 0.85);
   m_cut[4] = (v[k_p2] < 0.85);
   m_cut[5] = (v[k_visen] > 0.35);
   m_cut[6] = (v[k_l4dec] > 0);
   m_cut[7] = (v[k_tracks] >= 2);
   m_cut[8] = (v[k_oldccen] < 0.85);

   m_cut_tight[0] = (v[k_trignum] > 5);
   m_cut_tight[1] = (fabs(v[k_d0close]) < 0.001);
   m_cut_tight[2] = (fabs(v[k_wz]) < 0.04  ||
		       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.04));
   m_cut_tight[3] = (v[k_olde1] < 0.75);
   m_cut_tight[4] = (v[k_p2] < 0.75);
   m_cut_tight[5] = (v[k_visen] > 0.45);
   m_cut_tight[6] = m_cut[6];
   m_cut_tight[7] = (v[k_tracks] >= 3);
   m_cut_tight[8] = (v[k_oldccen] < 0.75);

}

void GEE_Oldhadronall::histbook_extra(HIHistoManager& iHistoManager)
{
   m_trignum = iHistoManager.histogram("r_trig", 8, -0.5, 7.5);
   m_d0close = iHistoManager.histogram("r_d0close", 120, -0.06, 0.06);
   m_logd0close = iHistoManager.histogram("r_logd0close", 140, -7., 0.);
   m_olde1 = iHistoManager.histogram("r_olde1", 120, 0., 1.2);
   m_p2 = iHistoManager.histogram("r_p2", 120, 0., 1.2);
   m_wz = iHistoManager.histogram("r_wz", 100, -0.10, 0.10);
   m_logwz = iHistoManager.histogram("r_logwz", 120, -6., 0.);
   m_criticalz0close = iHistoManager.histogram("r_criticalz0close", 100, -0.10, 0.10);
   m_criticallogz0close = iHistoManager.histogram("r_criticallogz0close", 120, -6., 0.);
   m_anyz = iHistoManager.histogram("r_anyz", 100, -0.10, 0.10);
   m_loganyz = iHistoManager.histogram("r_loganyz", 120, -6., 0.);
   m_visen = iHistoManager.histogram("r_visen", 120, 0., 1.2);
   m_tracks = iHistoManager.histogram("r_tracks", 19, -0.5, 18.5);
   m_oldccen = iHistoManager.histogram("r_oldccen", 120, 0., 1.2);

   m_trignum_count = 0;
   m_d0close_count = 0;
   m_olde1_count = 0;
   m_p2_count = 0;
   m_wz_count = 0;
   m_visen_count = 0;
   m_tracks_count = 0;
   m_ccen_count = 0;
   m_l4dec_count = 0;
}

void GEE_Oldhadronall::fill_extra()
{
   m_trignum->fill(v[k_trignum]);
   
   if (m_cut[0]) {
      m_trignum_count++;

      m_d0close->fill(v[k_d0close]);
      m_logd0close->fill(v[k_logd0close]);
      
      if (m_cut[1]) {
	 m_d0close_count++;

	 m_olde1->fill(v[k_olde1]);

	 if (m_cut[3]) {
	    m_olde1_count++;

	    m_p2->fill(v[k_p2]);

	    if (m_cut[4]) {
	       m_p2_count++;

	       m_wz->fill(v[k_wz]);
	       m_logwz->fill(v[k_logwz]);
	       m_criticalz0close->fill(v[k_criticalz0close]);
	       m_criticallogz0close->fill(v[k_criticallogz0close]);
	       m_anyz->fill(v[k_anyz]);
	       m_loganyz->fill(v[k_loganyz]);

	       if (m_cut[2]) {
		  m_wz_count++;

		  m_visen->fill(v[k_visen]);

		  if (m_cut[5]) {
		     m_visen_count++;

		     m_tracks->fill(v[k_tracks]);
		     
		     if (m_cut[7]) {
			m_tracks_count++;

			if (m_cut[6]) {
			   m_l4dec_count++;

			   m_oldccen->fill(v[k_oldccen]);
			}
		     }
		  }
	       }
	    }
	 }
      }
   }
}

void GEE_Oldhadronall::print_extra()
{
   print_hist1(m_name + string("_r_trignum"), m_trignum);
   print_hist1(m_name + string("_r_d0close"), m_d0close);
   print_hist1(m_name + string("_r_logd0close"), m_logd0close);
   print_hist1(m_name + string("_r_olde1"), m_olde1);
   print_hist1(m_name + string("_r_p2"), m_p2);
   print_hist1(m_name + string("_r_wz"), m_wz);
   print_hist1(m_name + string("_r_logwz"), m_logwz);
   print_hist1(m_name + string("_r_criticalz0close"), m_criticalz0close);
   print_hist1(m_name + string("_r_criticallogz0close"), m_criticallogz0close);
   print_hist1(m_name + string("_r_anyz"), m_wz);
   print_hist1(m_name + string("_r_loganyz"), m_logwz);
   print_hist1(m_name + string("_r_visen"), m_visen);
   print_hist1(m_name + string("_r_tracks"), m_tracks);
   print_hist1(m_name + string("_r_oldccen"), m_oldccen);

   cout << "PYTHON rec." << m_name.c_str() << "_trignum_count = " << m_trignum_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_d0close_count = " << m_d0close_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_olde1_count = " << m_olde1_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_p2_count = " << m_p2_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_wz_count = " << m_wz_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_visen_count = " << m_visen_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_tracks_count = " << m_tracks_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_ccen_count = " << m_ccen_count << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_l4dec_count = " << m_l4dec_count << endl;
}

////////////////////////////////////////////////

GEE_Gamgam::GEE_Gamgam()
{
   m_name = string("gamgam");

   prepare_hist(2, k_e2,                 120,  0.,   1.2,  "e2");
   prepare_hist(3, k_tracks,               5, -0.5,  4.5,  "tracks");
   prepare_hist(6, k_thetab2b,           100, -0.2,  0.2,  "thetab2b");
   prepare_hist(7, k_phib2b,             120, -0.30, 0.30, "phib2b");
   prepare_hist(8, k_cotT,               138,  0.,   1.38, "cotT");
   prepare_hist(-1,k_cotT,               138,  0.,   1.38, "cotT_cut");
   prepare_hist(-1,k_westphi,            128, -M_PI, M_PI, "westphi");

   prepare_count("trig");
   prepare_count("l4dec");
   prepare_count("e2");
   prepare_count("tracks");
   prepare_count("excludeA");
   prepare_count("excludeBC");
   prepare_count("thetab2b");
   prepare_count("phib2b");
   prepare_count("thetarange");
   prepare_count("excludemismap");
   prepare_count("oppositesides");
}

void GEE_Gamgam::update(float* event) {
   v = event;

   m_cut[0] = (v[k_bbtrig] > 0);
   m_cut[1] = (v[k_l4dec] > 0);
   m_cut[2] = (v[k_e2] > 0.7);
   m_cut[3] = (v[k_tracks] == 0);
   m_cut[4] = !(-0.68722 < v[k_westphi] && v[k_westphi] < 0.44179 && fabs(v[k_cotT]) < 0.54);
   m_cut[5] = !(-2.60163 < v[k_westphi] && v[k_westphi] < 0.68722 && fabs(v[k_cotT]) > 0.95);
   m_cut[6] = (fabs(v[k_thetab2b]) < 0.1);
   m_cut[7] = (fabs(v[k_phib2b]) < 0.04);
   m_cut[8] = ((0.05 < fabs(v[k_westcotT])  &&  0.15 < fabs(v[k_eastcotT]))  ||
	       (0.15 < fabs(v[k_westcotT])  &&  0.05 < fabs(v[k_eastcotT]))    )  &&
      ((fabs(v[k_westcotT]) < 1.28  &&  fabs(v[k_eastcotT]) < 1.18)  ||
       (fabs(v[k_westcotT]) < 1.18  &&  fabs(v[k_eastcotT]) < 1.28)    );
   m_cut[9] = !(-0.4 < v[k_westphi] && v[k_westphi] < -0.3);
   m_cut[10] = (v[k_oppositesides] > 0);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = m_cut[1];
   m_cut_tight[2] = (v[k_e2] > 0.9);
   m_cut_tight[3] = (v[k_eltrig] == 0.);
   m_cut_tight[4] = m_cut[4];
   m_cut_tight[5] = m_cut[5];
   m_cut_tight[6] = (fabs(v[k_thetab2b]) < 0.05);
   m_cut_tight[7] = (fabs(v[k_phib2b]) < 0.02);
   m_cut_tight[8] = ((0.05 < fabs(v[k_westcotT])  &&  0.15 < fabs(v[k_eastcotT]))  ||
		     (0.15 < fabs(v[k_westcotT])  &&  0.05 < fabs(v[k_eastcotT]))    )  &&
      ((fabs(v[k_westcotT]) < 1.18  &&  fabs(v[k_eastcotT]) < 1.08)  ||
       (fabs(v[k_westcotT]) < 1.08  &&  fabs(v[k_eastcotT]) < 1.18)    );
   m_cut_tight[9] = m_cut[9];
   m_cut_tight[10] = m_cut[10];
}

void GEE_Gamgam::histbook_extra(HIHistoManager& iHistoManager)
{
   m_numer = iHistoManager.histogram("cotT_numer", 138, 0., 1.38);
   m_denom = iHistoManager.histogram("cotT_denom", 138, 0., 1.38);
   m_wherewest = iHistoManager.histogram("wherewest", 128, -0.5, 127.5, 34, 34.5, 68.5);
   m_whereeast = iHistoManager.histogram("whereeast", 128, -0.5, 127.5, 34, 0.5, 34.5);
   m_wherewest_noexclude = iHistoManager.histogram("wherewest_noexclude", 128, -0.5, 127.5, 34, 34.5, 68.5);
   m_whereeast_noexclude = iHistoManager.histogram("whereeast_noexclude", 128, -0.5, 127.5, 34, 0.5, 34.5);
   m_e3GeVin = iHistoManager.histogram("e3GeVin", 125, 0.060, 0.185);
   m_e3GeVout = iHistoManager.histogram("e3GeVout", 125, 0.060, 0.185);
   m_pureggin = 0;
   m_pureggout = 0;
}

void GEE_Gamgam::fill_extra()
{
   bool survive_most = true;
   for (int i = 0;  i < m_cut.size();  i++) {
      if (i != 0  &&  i != 3  &&  i != 7) {
	 survive_most = survive_most && m_cut[i];
      }
   }
      
   if (survive_most                                         &&
       v[k_tracks] >= 2.                                    &&
       0.04 < fabs(v[k_phib2b]) && fabs(v[k_phib2b]) < 0.25    ) {

      m_denom->fill(v[k_cotT]);
      if (v[k_bbtrig] > 0.) m_numer->fill(v[k_cotT]);
   }

   /// 

   survive_most = true;
   for (int i = 0;  i < m_cut.size();  i++) {
      if (i != 4  &&  i != 5  &&  i != 9) {
	 survive_most = survive_most && m_cut[i];
      }
   }
   if (survive_most) { // all except exclusion blocks
      if (v[k_1_is_west] == 1.) {
	 m_wherewest_noexclude->fill(v[k_cell1], v[k_ring1]);
	 m_whereeast_noexclude->fill(v[k_cell2], v[k_ring2]);
      }
      else {
	 m_wherewest_noexclude->fill(v[k_cell2], v[k_ring2]);
	 m_whereeast_noexclude->fill(v[k_cell1], v[k_ring1]);
      }
   }

   ///

   if (survive()) { // all cuts
      if (v[k_1_is_west] == 1.) {
	 m_wherewest->fill(v[k_cell1], v[k_ring1]);
	 m_whereeast->fill(v[k_cell2], v[k_ring2]);
      }
      else {
	 m_wherewest->fill(v[k_cell2], v[k_ring2]);
	 m_whereeast->fill(v[k_cell1], v[k_ring1]);
      }


      bool in = ((fabs(v[k_westcotT]) < 1.18  &&  fabs(v[k_eastcotT]) < 1.08)  ||
		 (fabs(v[k_westcotT]) < 1.08  &&  fabs(v[k_eastcotT]) < 1.18)    );

      if (in) {
	 m_e3GeVin->fill(v[k_e3GeV]);
	 if (v[k_e3GeV] < 0.060) m_pureggin++;
      }
      else {
	 m_e3GeVout->fill(v[k_e3GeV]);
	 if (v[k_e3GeV] < 0.060) m_pureggout++;
      }
   }
}

void GEE_Gamgam::print_extra()
{
   print_hist1(m_name + string("_cotTnumer"), m_numer);
   print_hist1(m_name + string("_cotTdenom"), m_denom);
   print_hist2(m_name + string("_wherewest"), m_wherewest);
   print_hist2(m_name + string("_whereeast"), m_whereeast);
   print_hist2(m_name + string("_wherewest_noexclude"), m_wherewest_noexclude);
   print_hist2(m_name + string("_whereeast_noexclude"), m_whereeast_noexclude);
   print_hist1(m_name + string("_e3GeVin"), m_e3GeVin);
   print_hist1(m_name + string("_e3GeVout"), m_e3GeVout);
   cout << "PYTHON rec." << m_name.c_str() << "_pureggin = " << m_pureggin << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_pureggout = " << m_pureggout << endl;
}

////////////////////////////////////////////////

GEE_Trackless::GEE_Trackless()
{
   m_name = string("trackless");

   prepare_hist(2, k_e2,                 120,  0.,   1.2,  "e2");
   prepare_hist(3, k_rawtk,                5, -0.5,  4.5,  "rawtk");
   prepare_hist(6, k_thetab2b,           100, -0.2,  0.2,  "thetab2b");
   prepare_hist(3, k_phib2b,             120, -0.30, 0.30, "phib2b");  // this breaks pattern
   prepare_hist(8, k_cotT,               138,  0.,   1.38, "cotT");

   prepare_count("trig");
   prepare_count("l4dec");
   prepare_count("e2");
   prepare_count("rawtk");
   prepare_count("excludeA");
   prepare_count("excludeBC");
   prepare_count("thetab2b");
   prepare_count("phib2b");
   prepare_count("thetarange");
   prepare_count("excludemismap");
   prepare_count("oppositesides");
}

void GEE_Trackless::update(float* event) {
   v = event;

   m_cut[0] = (v[k_bbtrig] > 0);
   m_cut[1] = (v[k_l4dec] > 0);
   m_cut[2] = (v[k_e2] > 0.7);
   m_cut[3] = (v[k_rawtk] == 0);
   m_cut[4] = !(-0.68722 < v[k_westphi] && v[k_westphi] < 0.44179 && fabs(v[k_cotT]) < 0.54);
   m_cut[5] = !(-2.60163 < v[k_westphi] && v[k_westphi] < 0.68722 && fabs(v[k_cotT]) > 0.95);
   m_cut[6] = (fabs(v[k_thetab2b]) < 0.1);
   m_cut[7] = (0.04 < fabs(v[k_phib2b]) && fabs(v[k_phib2b]) < 0.25);
   m_cut[8] = ((0.05 < fabs(v[k_westcotT])  &&  0.15 < fabs(v[k_eastcotT]))  ||
	       (0.15 < fabs(v[k_westcotT])  &&  0.05 < fabs(v[k_eastcotT]))    )  &&
      ((fabs(v[k_westcotT]) < 1.28  &&  fabs(v[k_eastcotT]) < 1.18)  ||
       (fabs(v[k_westcotT]) < 1.18  &&  fabs(v[k_eastcotT]) < 1.28)    );
   m_cut[9] = !(-0.4 < v[k_westphi] && v[k_westphi] < -0.3);
   m_cut[10] = (v[k_oppositesides] > 0);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = m_cut[1];
   m_cut_tight[2] = (v[k_e2] > 0.9);
   m_cut_tight[3] = (v[k_eltrig] == 0);
   m_cut_tight[4] = m_cut[4];
   m_cut_tight[5] = m_cut[5];
   m_cut_tight[6] = (fabs(v[k_thetab2b]) < 0.05);
   m_cut_tight[7] = (0.06 < fabs(v[k_phib2b]) && fabs(v[k_phib2b]) < 0.25);
   m_cut_tight[8] = ((0.05 < fabs(v[k_westcotT])  &&  0.15 < fabs(v[k_eastcotT]))  ||
		     (0.15 < fabs(v[k_westcotT])  &&  0.05 < fabs(v[k_eastcotT]))    )  &&
      ((fabs(v[k_westcotT]) < 1.18  &&  fabs(v[k_eastcotT]) < 1.08)  ||
       (fabs(v[k_westcotT]) < 1.08  &&  fabs(v[k_eastcotT]) < 1.18)    );
   m_cut_tight[9] = m_cut[9];
   m_cut_tight[10] = m_cut[10];
}

void GEE_Trackless::histbook_extra(HIHistoManager& iHistoManager)
{
   m_vstime_releasetrack = iHistoManager.histogram("vstime_releasetrack", 100, 0., 1.);
   m_vstime_tightentrack = iHistoManager.histogram("vstime_releasetrack", 100, 0., 1.);
}

void GEE_Trackless::fill_extra()
{
   bool survive = true;
   for (int i = 0;  i < m_cut.size();  i++) {
      if (i != 3) {
	 survive = survive && m_cut[i];
      }
   }

   if (survive) {
      m_vstime_releasetrack->fill(v[k_eventfrac]);
      
      if (m_cut[3]  &&  m_cut_tight[3]) {
	 m_vstime_tightentrack->fill(v[k_eventfrac]);
      }
   }
}

void GEE_Trackless::print_extra()
{
   print_hist1(m_name + string("_vstime_releasetrack"), m_vstime_releasetrack);
   print_hist1(m_name + string("_vstime_tightentrack"), m_vstime_tightentrack);
}

////////////////////////////////////////////////

GEE_Bhabha::GEE_Bhabha()
{
   m_name = string("bhabha");

   prepare_hist(0, k_trignum,              8, -0.5,  7.5,  "trig");
   prepare_hist(2, k_p2,                 120,  0.,   1.2,  "p2");
   prepare_hist(3, k_d0close,            120, -0.06, 0.06, "d0close");
   prepare_hist(3, k_logd0close,         140, -7.,   0.,   "logd0close");
   prepare_hist(4, k_wz,                 100, -0.10, 0.10, "wz");
   prepare_hist(4, k_logwz,              120, -6.,   0.,   "logwz");
   prepare_hist(4, k_criticalz0close,    100, -0.10, 0.10, "criticalz0close");
   prepare_hist(4, k_criticallogz0close, 120, -6.,   0.,   "criticallogz0close");
   prepare_hist(4, k_anyz,               100, -0.10, 0.10, "anyz");
   prepare_hist(4, k_loganyz,            120, -6.,   0.,   "loganyz");
   prepare_hist(5, k_eisr,               100,  0.,   1.,   "eisr");
   prepare_hist(6, k_econstr,            100,  0.,   1.,   "econstr");
   prepare_hist(7, k_cosp,               100, -1.,   1.,   "cosp");
   prepare_hist(7, k_cosn,               100, -1.,   1.,   "cosn");
   prepare_hist(8, k_e2,                 120,  0.,   1.2,  "e2");

   prepare_count("trig");
   prepare_count("oppositecharge");
   prepare_count("p2");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("eisr");
   prepare_count("econstr");
   prepare_count("costh");
   prepare_count("e2");
   prepare_count("l4dec");
}

void GEE_Bhabha::update(float* event) {
   v = event;

   m_cut[0] = (v[k_trignum] > 0);
   m_cut[1] = (v[k_oppositecharge] > 0);
   m_cut[2] = (v[k_p2] > 0.7);
   m_cut[3] = (fabs(v[k_d0close]) < 0.005);
   m_cut[4] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[5] = (v[k_eisr] < 0.2);
   m_cut[6] = (v[k_econstr] < 0.2);
   m_cut[7] = (v[k_cos1] < 0.79  &&  v[k_cos2] < 0.76) || (v[k_cos1] < 0.76  &&  v[k_cos2] < 0.79);
   m_cut[8] = (v[k_e2] > 0.4);
   m_cut[9] = (v[k_l4dec] > 0);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = m_cut[1];
   m_cut_tight[2] = (v[k_p2] > 0.9);
   m_cut_tight[3] = (fabs(v[k_d0close]) < 0.001);
   m_cut_tight[4] = (fabs(v[k_wz]) < 0.04  ||
		     (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.04));
   m_cut_tight[5] = (v[k_eisr] < 0.1);
   m_cut_tight[6] = (v[k_econstr] < 0.1);
   m_cut_tight[7] = (v[k_cos1] < 0.69  &&  v[k_cos2] < 0.66) || (v[k_cos1] < 0.66  &&  v[k_cos2] < 0.69);
   m_cut_tight[8] = (v[k_e2] > 0.5);
   m_cut_tight[9] = m_cut[9];
}

void GEE_Bhabha::histbook_extra(HIHistoManager& iHistoManager)
{
   m_numer = iHistoManager.histogram("bhabish cotT_numer", 138, 0., 1.38);
   m_denom = iHistoManager.histogram("bhabish cotT_denom", 138, 0., 1.38);
   m_phib2b = iHistoManager.histogram("phib2b", 120, -0.3, 0.3);
}

void GEE_Bhabha::fill_extra()
{
   if (survive()) {
      m_phib2b->fill(v[k_phib2b]);

      bool gg0 = true; // (v[k_bbtrig] > 0);
      bool gg1 = true; // (v[k_l4dec] > 0);
      bool gg2 = (v[k_e2] > 0.7);
      bool gg3 = true; // (v[k_tracks] == 0);
      bool gg4 = !(-0.68722 < v[k_westphi] && v[k_westphi] < 0.44179 && fabs(v[k_cotT]) < 0.54);
      bool gg5 = !(-2.60163 < v[k_westphi] && v[k_westphi] < 0.68722 && fabs(v[k_cotT]) > 0.95);
      bool gg6 = (fabs(v[k_thetab2b]) < 0.1);
      bool gg7 = true; // (fabs(v[k_phib2b]) < 0.04);
      bool gg8 = ((0.05 < fabs(v[k_westcotT])  &&  0.15 < fabs(v[k_eastcotT]))  ||
		  (0.15 < fabs(v[k_westcotT])  &&  0.05 < fabs(v[k_eastcotT]))    )  &&
	 ((fabs(v[k_westcotT]) < 1.28  &&  fabs(v[k_eastcotT]) < 1.18)  ||
	  (fabs(v[k_westcotT]) < 1.18  &&  fabs(v[k_eastcotT]) < 1.28)    );
      bool gg9 = !(-0.4 < v[k_westphi] && v[k_westphi] < -0.3);
      bool gg10 = (v[k_oppositesides] > 0);

      if (gg0 && gg1 && gg2 && gg3 && gg4 && gg5 && gg6 && gg7 && gg8 && gg9 && gg10) {
	 m_denom->fill(v[k_cotT]);
	 if (v[k_bbtrig] > 0.) m_numer->fill(v[k_cotT]);
      }
   }
}

void GEE_Bhabha::print_extra()
{
   print_hist1(m_name + string("_cotTnumer"), m_numer);
   print_hist1(m_name + string("_cotTdenom"), m_denom);
   print_hist1(m_name + string("_phib2b"), m_phib2b);
}

////////////////////////////////////////////////

GEE_BhabhaTwoTrack::GEE_BhabhaTwoTrack()
{
   m_name = string("bhabhatwotrack");

   prepare_hist(2, k_p2,                 120,  0.,   1.2,  "p2");
   prepare_hist(3, k_d0close,            120, -0.06, 0.06, "d0close");
   prepare_hist(3, k_logd0close,         140, -7.,   0.,   "logd0close");
   prepare_hist(4, k_wz,                 100, -0.10, 0.10, "wz");
   prepare_hist(4, k_logwz,              120, -6.,   0.,   "logwz");
   prepare_hist(4, k_criticalz0close,    100, -0.10, 0.10, "criticalz0close");
   prepare_hist(4, k_criticallogz0close, 120, -6.,   0.,   "criticallogz0close");
   prepare_hist(4, k_anyz,               100, -0.10, 0.10, "anyz");
   prepare_hist(4, k_loganyz,            120, -6.,   0.,   "loganyz");
   prepare_hist(5, k_eisr,               100,  0.,   1.,   "eisr");
   prepare_hist(6, k_econstr,            100,  0.,   1.,   "econstr");
   prepare_hist(7, k_cosp,               100, -1.,   1.,   "cosp");
   prepare_hist(7, k_cosn,               100, -1.,   1.,   "cosn");
   prepare_hist(8, k_e2,                 120,  0.,   1.2,  "e2");

   prepare_count("trig");
   prepare_count("oppositecharge");
   prepare_count("p2");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("eisr");
   prepare_count("econstr");
   prepare_count("costh");
   prepare_count("e2");
   prepare_count("l4dec");
}

void GEE_BhabhaTwoTrack::update(float* event) {
   v = event;

   m_cut[0] = (v[k_tttrig] > 0);
   m_cut[1] = (v[k_oppositecharge] > 0);
   m_cut[2] = (v[k_p2] > 0.7);
   m_cut[3] = (fabs(v[k_d0close]) < 0.005);
   m_cut[4] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[5] = (v[k_eisr] < 0.2);
   m_cut[6] = (v[k_econstr] < 0.2);
   m_cut[7] = ((v[k_cos1] < 0.79  &&  v[k_cos2] < 0.76) || (v[k_cos1] < 0.76  &&  v[k_cos2] < 0.79));
   m_cut[8] = (v[k_e2] > 0.4);
   m_cut[9] = (v[k_l4dec] > 0);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = m_cut[1];
   m_cut_tight[2] = (v[k_p2] > 0.9);
   m_cut_tight[3] = (fabs(v[k_d0close]) < 0.001);
   m_cut_tight[4] = (fabs(v[k_wz]) < 0.04  ||
		     (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.04));
   m_cut_tight[5] = (v[k_eisr] < 0.1);
   m_cut_tight[6] = (v[k_econstr] < 0.1);
   m_cut_tight[7] = ((v[k_cos1] < 0.69  &&  v[k_cos2] < 0.66) || (v[k_cos1] < 0.66  &&  v[k_cos2] < 0.69)) && (v[k_cosp] < 0.);
   m_cut_tight[8] = (v[k_e2] > 0.5);
   m_cut_tight[9] = m_cut[9];
}

////////////////////////////////////////////////

GEE_Mupair::GEE_Mupair()
{
   m_name = string("mupair");

   prepare_hist(0, k_trignum,              8, -0.5,  7.5,  "trig");
   prepare_hist(2, k_p2,                 120,  0.,   1.2,  "p2");
   prepare_hist(3, k_d0close,            120, -0.06, 0.06, "d0close");
   prepare_hist(3, k_logd0close,         140, -7.,   0.,   "logd0close");
   prepare_hist(4, k_wz,                 100, -0.10, 0.10, "wz");
   prepare_hist(4, k_logwz,              120, -6.,   0.,   "logwz");
   prepare_hist(4, k_criticalz0close,    100, -0.10, 0.10, "criticalz0close");
   prepare_hist(4, k_criticallogz0close, 120, -6.,   0.,   "criticallogz0close");
   prepare_hist(4, k_anyz,               100, -0.10, 0.10, "anyz");
   prepare_hist(4, k_loganyz,            120, -6.,   0.,   "loganyz");
   prepare_hist(5, k_eisr,               100,  0.,   1.,   "eisr");
   prepare_hist(6, k_econstr,            100,  0.,   1.,   "econstr");
   prepare_hist(7, k_cosp,               100, -1.,   1.,   "cosp");
   prepare_hist(7, k_cosn,               100, -1.,   1.,   "cosn");
   prepare_hist(8, k_e2GeV,              100,  0.,   2.,   "e2GeV");

   prepare_count("trig");
   prepare_count("oppositecharge");
   prepare_count("p2");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("eisr");
   prepare_count("econstr");
   prepare_count("costh");
   prepare_count("e2GeV");
   prepare_count("l4dec");
}

void GEE_Mupair::update(float* event) {
   v = event;

   m_cut[0] = (v[k_trignum] > 0);
   m_cut[1] = (v[k_oppositecharge] > 0);
   m_cut[2] = (v[k_p2] > 0.7);
   m_cut[3] = (fabs(v[k_d0close]) < 0.005);
   m_cut[4] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[5] = (v[k_eisr] < 0.2);
   m_cut[6] = (v[k_econstr] < 0.2);
   m_cut[7] = (v[k_cos1] < 0.79  &&  v[k_cos2] < 0.76) || (v[k_cos1] < 0.76  &&  v[k_cos2] < 0.79);
   m_cut[8] = (v[k_e2GeV] < 1.);
   m_cut[9] = (v[k_l4dec] > 0);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = m_cut[1];
   m_cut_tight[2] = (v[k_p2] > 0.9);
   m_cut_tight[3] = (fabs(v[k_d0close]) < 0.001);
   m_cut_tight[4] = (fabs(v[k_wz]) < 0.04  ||
		     (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.04));
   m_cut_tight[5] = (v[k_eisr] < 0.1);
   m_cut_tight[6] = (v[k_econstr] < 0.1);
   m_cut_tight[7] = (v[k_cos1] < 0.69  &&  v[k_cos2] < 0.66) || (v[k_cos1] < 0.66  &&  v[k_cos2] < 0.69);
   m_cut_tight[8] = (v[k_e2GeV] < 0.5);
   m_cut_tight[9] = m_cut[9];
}

////////////////////////////////////////////////

GEE_MupairTwoTrack::GEE_MupairTwoTrack()
{
   m_name = string("mupairtwotrack");

   prepare_hist(2, k_p2,                 120,  0.,   1.2,  "p2");
   prepare_hist(3, k_d0close,            120, -0.06, 0.06, "d0close");
   prepare_hist(3, k_logd0close,         140, -7.,   0.,   "logd0close");
   prepare_hist(4, k_wz,                 100, -0.10, 0.10, "wz");
   prepare_hist(4, k_logwz,              120, -6.,   0.,   "logwz");
   prepare_hist(4, k_criticalz0close,    100, -0.10, 0.10, "criticalz0close");
   prepare_hist(4, k_criticallogz0close, 120, -6.,   0.,   "criticallogz0close");
   prepare_hist(4, k_anyz,               100, -0.10, 0.10, "anyz");
   prepare_hist(4, k_loganyz,            120, -6.,   0.,   "loganyz");
   prepare_hist(5, k_eisr,               100,  0.,   1.,   "eisr");
   prepare_hist(6, k_econstr,            100,  0.,   1.,   "econstr");
   prepare_hist(7, k_cosp,               100, -1.,   1.,   "cosp");
   prepare_hist(7, k_cosn,               100, -1.,   1.,   "cosn");
   prepare_hist(8, k_e2GeV,              100,  0.,   2.,   "e2GeV");

   prepare_count("trig");
   prepare_count("oppositecharge");
   prepare_count("p2");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("eisr");
   prepare_count("econstr");
   prepare_count("costh");
   prepare_count("e2GeV");
   prepare_count("l4dec");
}

void GEE_MupairTwoTrack::update(float* event) {
   v = event;

   m_cut[0] = (v[k_tttrig] > 0);
   m_cut[1] = (v[k_oppositecharge] > 0);
   m_cut[2] = (v[k_p2] > 0.7);
   m_cut[3] = (fabs(v[k_d0close]) < 0.005);
   m_cut[4] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[5] = (v[k_eisr] < 0.2);
   m_cut[6] = (v[k_econstr] < 0.2);
   m_cut[7] = ((v[k_cos1] < 0.79  &&  v[k_cos2] < 0.76) || (v[k_cos1] < 0.76  &&  v[k_cos2] < 0.79));
   m_cut[8] = (v[k_e2GeV] < 1.);
   m_cut[9] = (v[k_l4dec] > 0);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = m_cut[1];
   m_cut_tight[2] = (v[k_p2] > 0.9);
   m_cut_tight[3] = (fabs(v[k_d0close]) < 0.001);
   m_cut_tight[4] = (fabs(v[k_wz]) < 0.04  ||
		     (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.04));
   m_cut_tight[5] = (v[k_eisr] < 0.1);
   m_cut_tight[6] = (v[k_econstr] < 0.1);
   m_cut_tight[7] = ((v[k_cos1] < 0.69  &&  v[k_cos2] < 0.66) || (v[k_cos1] < 0.66  &&  v[k_cos2] < 0.69)) && (v[k_cosp] < 0.);
   m_cut_tight[8] = (v[k_e2GeV] < 0.5);
   m_cut_tight[9] = m_cut[9];
}

////////////////////////////////////////////////

GEE_Cosmic::GEE_Cosmic()
{
   m_name = string("cosmic");

   prepare_hist(1, k_tracks,               5, -0.5,  4.5,  "tracks");
   prepare_hist(2, k_d0close,            120, -0.06, 0.06, "d0close");
   prepare_hist(2, k_logd0close,         140, -7.,   0.,   "logd0close");
   prepare_hist(3, k_pdotp,              100, -1.,   1.,   "pdotp");
   prepare_hist(3, k_logpdotp,           100, -10.,  0.,   "logpdotp");
   prepare_hist(4, k_ccenGeV,            150,  0.,   3.,   "ccenGeV");
   prepare_hist(6, k_visen,              120,  0.,   1.2,  "visen");
   prepare_hist(6, k_coolvisen,          120,  0.,   1.2,  "cvisen");

   prepare_count("trig");
   prepare_count("rawtk");
   prepare_count("d0close");
   prepare_count("pdotp");
   prepare_count("ccenGeV");
   prepare_count("l4dec");
}

void GEE_Cosmic::update(float* event) {
   v = event;

   m_cut[0] = (v[k_trignum] > 0);
   m_cut[1] = (v[k_tracks] >= 2);
   m_cut[2] = (0.005 < fabs(v[k_d0close]));
   m_cut[3] = (v[k_pdotp] != -1000.  &&  fabs(v[k_pdotp]) > 0.999);
   m_cut[4] = (v[k_ccenGeV] < 2.);
   m_cut[5] = (v[k_l4dec] > 0);
   m_cut[6] = (v[k_coolvisen] > 0.04);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = m_cut[1];
   m_cut_tight[2] = (0.010 < fabs(v[k_d0close]));
   m_cut_tight[3] = (v[k_pdotp] != -1000.  &&  fabs(v[k_pdotp]) > 0.9999);
   m_cut_tight[4] = (v[k_ccenGeV] < 1.);
   m_cut_tight[5] = m_cut[5];
   m_cut_tight[6] = m_cut[6];
}

////////////////////////////////////////////////

GEE_BeamgasE::GEE_BeamgasE()
{
   m_name = string("beamgase");

   prepare_hist(1, k_tracks,              19, -0.5, 18.5,  "tracks");
   prepare_hist(2, k_d0close,            120, -0.06, 0.06, "d0close");
   prepare_hist(2, k_logd0close,         140, -7.,   0.,   "logd0close");
   prepare_hist(3, k_wz,                 100, -0.10, 0.10, "wz");
   prepare_hist(3, k_logwz,              120, -6.,   0.,   "logwz");
   prepare_hist(3, k_criticalz0close,    100, -0.10, 0.10, "criticalz0close");
   prepare_hist(3, k_criticallogz0close, 120, -6.,   0.,   "criticallogz0close");
   prepare_hist(3, k_anyz,               100, -0.10, 0.10, "anyz");
   prepare_hist(3, k_loganyz,            120, -6.,   0.,   "loganyz");
   prepare_hist(4, k_pdotp,              100, -1.,   1.,   "pdotp");
   prepare_hist(4, k_logpdotp,           100, -10.,  0.,   "logpdotp");
   prepare_hist(5, k_wpz,                100, -1.,   1.,   "wpz");
   prepare_hist(7, k_visen,              120,  0.,   1.2,  "visen");
   prepare_hist(7, k_coolvisen,          120,  0.,   1.2,  "cvisen");
   prepare_hist(-1,k_ccenGeV,            150,  0.,   3.,   "ccenGeV");

   prepare_count("trig");
   prepare_count("tracks");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("pdotp");
   prepare_count("wpz");
   prepare_count("l4dec");
   prepare_count("visen");
}

void GEE_BeamgasE::update(float* event) {
   v = event;

   m_cut[0] = (v[k_trignum] > 0);
   m_cut[1] = (v[k_tracks] >= 2);
   m_cut[2] = (fabs(v[k_d0close]) < 0.005);
   m_cut[3] = ((v[k_wz] != -1000. && fabs(v[k_wz]) > 0.075) || (v[k_wz] == -1000.  &&  (fabs(v[k_z0close]) > 0.075)));
   m_cut[4] = (fabs(v[k_pdotp]) < 0.9);
   m_cut[5] = (v[k_wpz] != -1000.  &&  v[k_wpz] < -0.1);
   m_cut[6] = (v[k_l4dec] > 0);
   m_cut[7] = (v[k_coolvisen] > 0.04);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = (v[k_tracks] >= 3);
   m_cut_tight[2] = (fabs(v[k_d0close]) < 0.001);
   m_cut_tight[3] = ((v[k_wz] != -1000. && fabs(v[k_wz]) > 0.10) || (v[k_wz] == -1000.  &&  (fabs(v[k_z0close]) > 0.10)));
   m_cut_tight[4] = (fabs(v[k_pdotp]) < 0.8);
   m_cut_tight[5] = (v[k_wpz] != -1000.  &&  fabs(v[k_wpz]) < 0.5);
   m_cut_tight[6] = m_cut[6];
   m_cut_tight[7] = m_cut[7];
}

////////////////////////////////////////////////

GEE_BeamgasP::GEE_BeamgasP()
{
   m_name = string("beamgasp");

   prepare_hist(1, k_tracks,              19, -0.5, 18.5,  "tracks");
   prepare_hist(2, k_d0close,            120, -0.06, 0.06, "d0close");
   prepare_hist(2, k_logd0close,         140, -7.,   0.,   "logd0close");
   prepare_hist(3, k_wz,                 100, -0.10, 0.10, "wz");
   prepare_hist(3, k_logwz,              120, -6.,   0.,   "logwz");
   prepare_hist(3, k_criticalz0close,    100, -0.10, 0.10, "criticalz0close");
   prepare_hist(3, k_criticallogz0close, 120, -6.,   0.,   "criticallogz0close");
   prepare_hist(3, k_anyz,               100, -0.10, 0.10, "anyz");
   prepare_hist(3, k_loganyz,            120, -6.,   0.,   "loganyz");
   prepare_hist(4, k_pdotp,              100, -1.,   1.,   "pdotp");
   prepare_hist(4, k_logpdotp,           100, -10.,  0.,   "logpdotp");
   prepare_hist(5, k_wpz,                100, -1.,   1.,   "wpz");
   prepare_hist(7, k_visen,              120,  0.,   1.2,  "visen");
   prepare_hist(7, k_coolvisen,          120,  0.,   1.2,  "cvisen");
   prepare_hist(-1,k_ccenGeV,            150,  0.,   3.,   "ccenGeV");

   prepare_count("trig");
   prepare_count("tracks");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("pdotp");
   prepare_count("wpz");
   prepare_count("l4dec");
   prepare_count("visen");
}

void GEE_BeamgasP::update(float* event) {
   v = event;

   m_cut[0] = (v[k_trignum] > 0);
   m_cut[1] = (v[k_tracks] >= 2);
   m_cut[2] = (fabs(v[k_d0close]) < 0.005);
   m_cut[3] = ((v[k_wz] != -1000. && fabs(v[k_wz]) > 0.075) || (v[k_wz] == -1000.  &&  (fabs(v[k_z0close]) > 0.075)));
   m_cut[4] = (fabs(v[k_pdotp]) < 0.9);
   m_cut[5] = (v[k_wpz] != -1000.  &&  v[k_wpz] > 0.1);
   m_cut[6] = (v[k_l4dec] > 0);
   m_cut[7] = (v[k_coolvisen] > 0.04);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = (v[k_tracks] >= 3);
   m_cut_tight[2] = (fabs(v[k_d0close]) < 0.001);
   m_cut_tight[3] = ((v[k_wz] != -1000. && fabs(v[k_wz]) > 0.10) || (v[k_wz] == -1000.  &&  (fabs(v[k_z0close]) > 0.10)));
   m_cut_tight[4] = (fabs(v[k_pdotp]) < 0.8);
   m_cut_tight[5] = (v[k_wpz] != -1000.  &&  fabs(v[k_wpz]) < 0.5);
   m_cut_tight[6] = m_cut[6];
   m_cut_tight[7] = m_cut[7];
}

////////////////////////////////////////////////

GEE_BrokenShower::GEE_BrokenShower()
{
   m_name = string("brokenshower");

   prepare_hist(0, k_e1,                 100,  0.,   2.,   "e1");

   prepare_count("e1");
}

void GEE_BrokenShower::update(float* event) {
   v = event;

   m_cut[0] = (v[k_e1] > 1.2);

   m_cut_tight[0] = (v[k_e1] > 1.5);
}

void GEE_BrokenShower::histbook_extra(HIHistoManager& iHistoManager)
{
   m_where = iHistoManager.histogram("where", 128, -0.5, 127.5, 68, 0.5, 68.5);
   m_where_tight = iHistoManager.histogram("where_tight", 128, -0.5, 127.5, 68, 0.5, 68.5);
}

void GEE_BrokenShower::fill_extra()
{
   if (survive()) {
      m_where->fill(v[k_cell1], v[k_ring1]);
      
      if (m_cut_tight[0]) {
	 m_where_tight->fill(v[k_cell1], v[k_ring1]);
      }
   }
}

void GEE_BrokenShower::print_extra()
{
   print_hist2(m_name + string("_where"), m_where);   
   print_hist2(m_name + string("_where_tight"), m_where);   
}

////////////////////////////////////////////////

GEE_BrokenShower2::GEE_BrokenShower2()
{
   m_name = string("brokenshower2");

   prepare_hist(0, k_breake1,                 100,  0.,   2.,   "e1");

   prepare_count("e1");
}

void GEE_BrokenShower2::update(float* event) {
   v = event;

   m_cut[0] = (v[k_breake1] > 1.2);

   m_cut_tight[0] = (v[k_breake1] > 1.5);
}

void GEE_BrokenShower2::histbook_extra(HIHistoManager& iHistoManager)
{
   m_where = iHistoManager.histogram("where", 128, -0.5, 127.5, 68, 0.5, 68.5);
   m_where_tight = iHistoManager.histogram("where_tight", 128, -0.5, 127.5, 68, 0.5, 68.5);
}

void GEE_BrokenShower2::fill_extra()
{
   if (survive()) {
      m_where->fill(v[k_cell1], v[k_ring1]);
      
      if (m_cut_tight[0]) {
	 m_where_tight->fill(v[k_cell1], v[k_ring1]);
      }
   }
}

void GEE_BrokenShower2::print_extra()
{
   print_hist2(m_name + string("_where"), m_where);   
   print_hist2(m_name + string("_where_tight"), m_where);   
}

////////////////////////////////////////////////

GEE_CCStudy1::GEE_CCStudy1()
{
   m_name = string("ccstudy1");

   prepare_hist(1, k_tracks,              19, -0.5, 18.5,  "tracks");
   prepare_hist(2, k_chen,               120,  0.,   1.2,  "chen");
   prepare_hist(5, k_p1,                 120,  0.,   1.2,  "p1");
   prepare_hist(-1,k_e1GeV,              100,  0.,   4.,   "e1GeV");
   prepare_hist(-1,k_e2GeV,              100,  0.,   4.,   "e2GeV");
   prepare_hist(-1,k_trignum,              8, -0.5,  7.5,  "analtrig");
   prepare_hist(-1,k_frozenvisen,        120,  0.,   1.2,  "fvisen");

   prepare_count("tttrig");
   prepare_count("tracks");
   prepare_count("chen");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("p1");
   prepare_count("l4dec");
}

void GEE_CCStudy1::update(float* event) {
   v = event;

   m_cut[0] = (v[k_tttrig] > 0);
   m_cut[1] = (v[k_tracks] >= 2);
   m_cut[2] = (v[k_chen] > 0.15);  // was 0.04 in old histograms
   m_cut[3] = (fabs(v[k_d0close]) < 0.005);
   m_cut[4] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[5] = (v[k_p1] < 0.8);
   m_cut[6] = (v[k_l4dec] > 0);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = m_cut[1];
   m_cut_tight[2] = m_cut[2];
   m_cut_tight[3] = m_cut[3];
   m_cut_tight[4] = m_cut[4];
   m_cut_tight[5] = m_cut[5];
   m_cut_tight[6] = m_cut[6];
}

void GEE_CCStudy1::histbook_extra(HIHistoManager& iHistoManager)
{
   m_analtrigcount = 0;
   m_analtrigcount_fail = 0;

   m_analtrig_fail = iHistoManager.histogram("analtrig_fail", 8, -0.5, 7.5);   
   m_e1GeV_fail = iHistoManager.histogram("e1GeV_fail", 100, 0., 4.);   
   m_e2GeV_fail = iHistoManager.histogram("e2GeV_fail", 100, 0., 4.);   
}

void GEE_CCStudy1::fill_extra()
{
   if (survive()) {
      if (v[k_trignum] > 0) m_analtrigcount++;
   }
   else {
      if (v[k_trignum] > 0) m_analtrigcount_fail++;

      m_analtrig_fail->fill(v[k_trignum]);
      m_e1GeV_fail->fill(v[k_e1GeV]);
      m_e2GeV_fail->fill(v[k_e2GeV]);
   }
}

void GEE_CCStudy1::print_extra()
{
   cout << "PYTHON rec." << m_name.c_str() << "_analtrigcount = " << m_analtrigcount << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_analtrigcount_fail = " << m_analtrigcount_fail << endl;
   print_hist1(m_name + string("_analtrig_fail"), m_analtrig_fail);   
   print_hist1(m_name + string("_e1GeV_fail"), m_e1GeV_fail);   
   print_hist1(m_name + string("_e2GeV_fail"), m_e2GeV_fail);   
}

////////////////////////////////////////////////

GEE_CCStudy2::GEE_CCStudy2()
{
   m_name = string("ccstudy2");

   prepare_hist(1, k_tracks,              19, -0.5, 18.5,  "tracks");
   prepare_hist(2, k_chen,               120,  0.,   1.2,  "chen");
   prepare_hist(5, k_p1,                 120,  0.,   1.2,  "p1");
   prepare_hist(-1,k_e1GeV,              100,  0.,   4.,   "e1GeV");
   prepare_hist(-1,k_e2GeV,              100,  0.,   4.,   "e2GeV");
   prepare_hist(-1,k_trignum,              8, -0.5,  7.5,  "analtrig");

   prepare_count("tttrig");
   prepare_count("tracks");
   prepare_count("chen");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("p1");
   prepare_count("l4dec");
}

void GEE_CCStudy2::update(float* event) {
   v = event;

   m_cut[0] = (v[k_tttrig] > 0);
   m_cut[1] = (v[k_tracks] >= 3);
   m_cut[2] = (v[k_chen] > 0.04);
   m_cut[3] = (fabs(v[k_d0close]) < 0.005);
   m_cut[4] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[5] = (v[k_p1] < 0.8);
   m_cut[6] = (v[k_l4dec] > 0);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = m_cut[1];
   m_cut_tight[2] = m_cut[2];
   m_cut_tight[3] = m_cut[3];
   m_cut_tight[4] = m_cut[4];
   m_cut_tight[5] = m_cut[5];
   m_cut_tight[6] = m_cut[6];
}

void GEE_CCStudy2::histbook_extra(HIHistoManager& iHistoManager)
{
   m_analtrigcount = 0;
   m_analtrigcount_fail = 0;

   m_analtrig_fail = iHistoManager.histogram("analtrig_fail", 8, -0.5, 7.5);   
   m_e1GeV_fail = iHistoManager.histogram("e1GeV_fail", 100, 0., 4.);   
   m_e2GeV_fail = iHistoManager.histogram("e2GeV_fail", 100, 0., 4.);   
}

void GEE_CCStudy2::fill_extra()
{
   if (survive()) {
      if (v[k_trignum] > 0) m_analtrigcount++;
   }
   else {
      if (v[k_trignum] > 0) m_analtrigcount_fail++;

      m_analtrig_fail->fill(v[k_trignum]);
      m_e1GeV_fail->fill(v[k_e1GeV]);
      m_e2GeV_fail->fill(v[k_e2GeV]);
   }
}

void GEE_CCStudy2::print_extra()
{
   cout << "PYTHON rec." << m_name.c_str() << "_analtrigcount = " << m_analtrigcount << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_analtrigcount_fail = " << m_analtrigcount_fail << endl;
   print_hist1(m_name + string("_analtrig_fail"), m_analtrig_fail);   
   print_hist1(m_name + string("_e1GeV_fail"), m_e1GeV_fail);   
   print_hist1(m_name + string("_e2GeV_fail"), m_e2GeV_fail);   
}

////////////////////////////////////////////////

GEE_CCStudy3::GEE_CCStudy3()
{
   m_name = string("ccstudy3");

   prepare_hist(1, k_tracks,              19, -0.5, 18.5,  "tracks");
   prepare_hist(2, k_chen,               120,  0.,   1.2,  "chen");
   prepare_hist(5, k_p1,                 120,  0.,   1.2,  "p1");
   prepare_hist(-1,k_e1GeV,              100,  0.,   4.,   "e1GeV");
   prepare_hist(-1,k_e2GeV,              100,  0.,   4.,   "e2GeV");
   prepare_hist(-1,k_trignum,              8, -0.5,  7.5,  "analtrig");

   prepare_count("tttrig");
   prepare_count("tracks");
   prepare_count("chen");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("p1");
   prepare_count("l4dec");
}

void GEE_CCStudy3::update(float* event) {
   v = event;

   m_cut[0] = (v[k_tttrig] > 0);
   m_cut[1] = true;
   m_cut[2] = (v[k_chen] > 0.4);
   m_cut[3] = (fabs(v[k_d0close]) < 0.005);
   m_cut[4] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[5] = (v[k_p1] < 0.8);
   m_cut[6] = (v[k_l4dec] > 0);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = m_cut[1];
   m_cut_tight[2] = m_cut[2];
   m_cut_tight[3] = m_cut[3];
   m_cut_tight[4] = m_cut[4];
   m_cut_tight[5] = m_cut[5];
   m_cut_tight[6] = m_cut[6];
}

void GEE_CCStudy3::histbook_extra(HIHistoManager& iHistoManager)
{
   m_analtrigcount = 0;
   m_analtrigcount_fail = 0;

   m_analtrig_fail = iHistoManager.histogram("analtrig_fail", 8, -0.5, 7.5);   
   m_e1GeV_fail = iHistoManager.histogram("e1GeV_fail", 100, 0., 4.);   
   m_e2GeV_fail = iHistoManager.histogram("e2GeV_fail", 100, 0., 4.);   
}

void GEE_CCStudy3::fill_extra()
{
   if (survive()) {
      if (v[k_trignum] > 0) m_analtrigcount++;
   }
   else {
      if (v[k_trignum] > 0) m_analtrigcount_fail++;

      m_analtrig_fail->fill(v[k_trignum]);
      m_e1GeV_fail->fill(v[k_e1GeV]);
      m_e2GeV_fail->fill(v[k_e2GeV]);
   }
}

void GEE_CCStudy3::print_extra()
{
   cout << "PYTHON rec." << m_name.c_str() << "_analtrigcount = " << m_analtrigcount << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_analtrigcount_fail = " << m_analtrigcount_fail << endl;
   print_hist1(m_name + string("_analtrig_fail"), m_analtrig_fail);   
   print_hist1(m_name + string("_e1GeV_fail"), m_e1GeV_fail);   
   print_hist1(m_name + string("_e2GeV_fail"), m_e2GeV_fail);   
}

////////////////////////////////////////////////

GEE_CCStudy4::GEE_CCStudy4()
{
   m_name = string("ccstudy4");

   prepare_hist(1, k_tracks,              19, -0.5, 18.5,  "tracks");
   prepare_hist(2, k_chen,               120,  0.,   1.2,  "chen");
   prepare_hist(5, k_p1,                 120,  0.,   1.2,  "p1");
   prepare_hist(-1,k_e1GeV,              100,  0.,   4.,   "e1GeV");
   prepare_hist(-1,k_e2GeV,              100,  0.,   4.,   "e2GeV");
   prepare_hist(-1,k_trignum,              8, -0.5,  7.5,  "analtrig");

   prepare_count("tttrig");
   prepare_count("tracks");
   prepare_count("chen");
   prepare_count("d0close");
   prepare_count("wz");
   prepare_count("p1");
   prepare_count("l4dec");
}

void GEE_CCStudy4::update(float* event) {
   v = event;

   m_cut[0] = (v[k_hadtrig] > 0);
   m_cut[1] = (v[k_tracks] >= 3);
   m_cut[2] = (v[k_chen] > 0.04);
   m_cut[3] = (fabs(v[k_d0close]) < 0.005);
   m_cut[4] = (fabs(v[k_wz]) < 0.075  ||
	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
   m_cut[5] = (v[k_p1] < 0.8);
   m_cut[6] = (v[k_l4dec] > 0);

   m_cut_tight[0] = m_cut[0];
   m_cut_tight[1] = m_cut[1];
   m_cut_tight[2] = m_cut[2];
   m_cut_tight[3] = m_cut[3];
   m_cut_tight[4] = m_cut[4];
   m_cut_tight[5] = m_cut[5];
   m_cut_tight[6] = m_cut[6];
}

void GEE_CCStudy4::histbook_extra(HIHistoManager& iHistoManager)
{
   m_analtrigcount = 0;
   m_analtrigcount_fail = 0;

   m_analtrig_fail = iHistoManager.histogram("analtrig_fail", 8, -0.5, 7.5);   
   m_e1GeV_fail = iHistoManager.histogram("e1GeV_fail", 100, 0., 4.);   
   m_e2GeV_fail = iHistoManager.histogram("e2GeV_fail", 100, 0., 4.);   
}

void GEE_CCStudy4::fill_extra()
{
   if (survive()) {
      if (v[k_trignum] > 0) m_analtrigcount++;
   }
   else {
      if (v[k_trignum] > 0) m_analtrigcount_fail++;

      m_analtrig_fail->fill(v[k_trignum]);
      m_e1GeV_fail->fill(v[k_e1GeV]);
      m_e2GeV_fail->fill(v[k_e2GeV]);
   }
}

void GEE_CCStudy4::print_extra()
{
   cout << "PYTHON rec." << m_name.c_str() << "_analtrigcount = " << m_analtrigcount << endl;
   cout << "PYTHON rec." << m_name.c_str() << "_analtrigcount_fail = " << m_analtrigcount_fail << endl;
   print_hist1(m_name + string("_analtrig_fail"), m_analtrig_fail);   
   print_hist1(m_name + string("_e1GeV_fail"), m_e1GeV_fail);   
   print_hist1(m_name + string("_e2GeV_fail"), m_e2GeV_fail);   
}
