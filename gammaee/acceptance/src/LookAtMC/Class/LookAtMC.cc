// -*- C++ -*-
//
// Package:     LookAtMC
// Module:      LookAtMC
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Feb 14 11:44:38 EST 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "LookAtMC/LookAtMC.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "EventProperties/EventProperties.h"
#include "BeamEnergy/BeamEnergy.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"


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
static const char* const kFacilityString = "Processor.LookAtMC" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
LookAtMC::LookAtMC( void )               // anal1
   : Processor( "LookAtMC" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &LookAtMC::event,    Stream::kEvent );
   //bind( &LookAtMC::beginRun, Stream::kBeginRun );
   //bind( &LookAtMC::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

LookAtMC::~LookAtMC()                    // anal5
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
LookAtMC::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
LookAtMC::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
LookAtMC::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_meas_thrust_dir = iHistoManager.histogram(100, "Cos([Q]) of thrust axis (measured particles)", 100, -1., 1.);
   m_meas_thrust_mag = iHistoManager.histogram(200, "Thrust magnitude (measured particles)", 100, 0., 1.);

   m_COMPlanarity = iHistoManager.histogram(300, "COM planarity", 100, 0., 2.);
   m_TMomPlanarity = iHistoManager.histogram(400, "TMom planarity", 100, 0., 2.);
   m_thrust_mag = iHistoManager.histogram(500, "Thrust magnitude", 100, 0., 1.);
   m_thrust_dir = iHistoManager.histogram(600, "Cos([Q]) of thrust axis", 100, -1., 1.);

   m_even = 0;
   m_odd = 0;
   m_unknown = 0;

   m_failp = 0;
   m_allp = 0;
   m_failm = 0;
   m_allm = 0;
   m_fail0 = 0;
   m_all0 = 0;

   m_mesons = iHistoManager.histogram(1000, "Mesons in failures", 10, -0.5, 9.5);
   m_baryons = iHistoManager.histogram(1001, "Baryons in failures", 10, -0.5, 9.5);
   m_strangers = iHistoManager.histogram(1002, "Strangers in failures", 10, -0.5, 9.5);
   m_charmers = iHistoManager.histogram(1003, "Charmers in failures", 10, -0.5, 9.5);
   m_mesons_all = iHistoManager.histogram(1004, "Mesons in all", 10, -0.5, 9.5);
   m_baryons_all = iHistoManager.histogram(1005, "Baryons in all", 10, -0.5, 9.5);
   m_strangers_all = iHistoManager.histogram(1006, "Strangers in all", 10, -0.5, 9.5);
   m_charmers_all = iHistoManager.histogram(1007, "Charmers in all", 10, -0.5, 9.5);

   m_mass_failures = iHistoManager.histogram(2000, "[S] mass of failures", 100, 0., 10.);
   m_mass2_failures = iHistoManager.histogram(2001, "[S] mass^2! of failures", 100, 0., 10.);
   m_mass_all = iHistoManager.histogram(2002, "[S] mass of all", 100, 0., 10.);
   m_mass2_all = iHistoManager.histogram(2003, "[S] mass^2! of all", 100, 0., 10.);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
LookAtMC::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);
   m_meas_thrust_dir->fill(props->thrustAxis().cosTheta());
   m_meas_thrust_mag->fill(props->thrustAxis().mag());

   FAItem<MCDecayTree> tree;
   extract(iFrame.record(Stream::kEvent), tree, "Generator");
   MCDecayTree::const_vIterator viter;
   MCDecayTree::const_vIterator tree_vend = tree->vEnd();

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   const MCParticlePropertyStore& mcppstore =
      tree->topParticle().properties().store();
   const int qcd = mcppstore.nameToQQId("string");

   vector<int> geven, godd;
   godd.push_back(mcppstore.nameToQQId("pi+"));
   godd.push_back(mcppstore.nameToQQId("pi-"));
   godd.push_back(mcppstore.nameToQQId("pi0"));
   godd.push_back(mcppstore.nameToQQId("omega"));
   godd.push_back(mcppstore.nameToQQId("omega(2S)"));
   godd.push_back(mcppstore.nameToQQId("pi(2S)+"));
   godd.push_back(mcppstore.nameToQQId("pi(2S)-"));
   godd.push_back(mcppstore.nameToQQId("pi(2S)0"));
   godd.push_back(mcppstore.nameToQQId("phi"));
   godd.push_back(mcppstore.nameToQQId("a_00"));
   godd.push_back(mcppstore.nameToQQId("a_0+"));
   godd.push_back(mcppstore.nameToQQId("a_0-"));
   godd.push_back(mcppstore.nameToQQId("h_1"));
   godd.push_back(mcppstore.nameToQQId("h'_1"));
   godd.push_back(mcppstore.nameToQQId("a_10"));
   godd.push_back(mcppstore.nameToQQId("a_1+"));
   godd.push_back(mcppstore.nameToQQId("a_1-"));
   godd.push_back(mcppstore.nameToQQId("a_20"));
   godd.push_back(mcppstore.nameToQQId("a_2+"));
   godd.push_back(mcppstore.nameToQQId("a_2-"));

   geven.push_back(mcppstore.nameToQQId("eta"));
   geven.push_back(mcppstore.nameToQQId("eta(2S)"));
   geven.push_back(mcppstore.nameToQQId("eta'"));
   geven.push_back(mcppstore.nameToQQId("rho+"));
   geven.push_back(mcppstore.nameToQQId("rho-"));
   geven.push_back(mcppstore.nameToQQId("rho0"));
   geven.push_back(mcppstore.nameToQQId("rho(2S)+"));
   geven.push_back(mcppstore.nameToQQId("rho(2S)-"));
   geven.push_back(mcppstore.nameToQQId("rho(2S)0"));
   geven.push_back(mcppstore.nameToQQId("rho(3S)+"));
   geven.push_back(mcppstore.nameToQQId("rho(3S)-"));
   geven.push_back(mcppstore.nameToQQId("rho(3S)0"));
   geven.push_back(mcppstore.nameToQQId("f_0"));
   geven.push_back(mcppstore.nameToQQId("f'_0"));
   geven.push_back(mcppstore.nameToQQId("b_10"));
   geven.push_back(mcppstore.nameToQQId("b_1+"));
   geven.push_back(mcppstore.nameToQQId("b_1-"));
   geven.push_back(mcppstore.nameToQQId("f_1"));
   geven.push_back(mcppstore.nameToQQId("f'_1"));
   geven.push_back(mcppstore.nameToQQId("f_2"));
   geven.push_back(mcppstore.nameToQQId("f_0(1500)"));
   geven.push_back(mcppstore.nameToQQId("f'_2"));

   int n0 = mcppstore.nameToQQId("n0");
   int anti_n0 = mcppstore.nameToQQId("anti-n0");

//    const int allids[506] = {1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 21, 11, -11, 12, -12, 13, -13, 14, -14, 15, -15, 16, -16, 17, -17, 18, -18, 22, 10022, 91, 20022, 23, 24, -24, 25, 28, 29, 32, 33, 34, -34, 35, 36, 37, -37, 40, -40, 41, 42, -42, 81, 82, -82, 83, 84, -84, 85, -85, 86, -86, 87, -87, 88, -88, 89, -89, 90, -90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 111, 211, -211, 210, -210, 20111, 20211, -20211, 221, 20221, 331, 113, 110, 213, -213, 30113, 30213, -30213, 40113, 40213, -40213, 223, 220, 30223, 333, 330, 10111, 10211, -10211, 10221, 10331, 10113, 10213, -10213, 10223, 10333, 20113, 20213, -20213, 20223, 20333, 115, 215, -215, 225, 50221, 335, 311, -311, 310, 130, 321, -321, 313, -313, 323, -323, 10311, -10311, 10321, -10321, 10313, -10313, 10323, -10323, 315, -315, 325, -325, 20313, -20313, 20323, -20323, 100313, -100313, 100323, -100323, 30313, -30313, 30323, -30323, 317, -317, 327, -327, 319, -319, 329, -329, 411, -411, 421, -421, 413, -413, 423, -423, 10411, -10411, 10421, -10421, 10413, -10413, 10423, -10423, 415, -415, 425, -425, 20413, -20413, 20423, -20423, 431, -431, 433, -433, 10431, -10431, 10433, -10433, 435, -435, 20433, -20433, 30411, -30411, 30421, -30421, 30413, -30413, 30423, -30423, 511, -511, 521, -521, 513, -513, 523, -523, 10511, -10511, 10521, -10521, 10513, -10513, 10523, -10523, 515, -515, 525, -525, 20513, -20513, 20523, -20523, 531, -531, 533, -533, 10531, -10531, 10533, -10533, 535, -535, 20533, -20533, 541, -541, 543, -543, 10541, -10541, 10543, -10543, 545, -545, 20543, -20543, 441, 20441, 443, 440, 100443, 30443, 50443, 60443, 70443, 10443, 10441, 20443, 445, 551, 20551, 40551, 553, 30553, 60553, 70553, 80553, 10553, 40553, 100553, 10551, 20553, 555, 30551, 50553, 10555, 50551, 110553, 20555, 40555, 60555, 120553, 30555, 557, 130553, 50555, 10557, 1114, -1114, 2110, -2110, 2112, -2112, 2114, -2114, 2210, -2210, 2212, -2212, 2214, -2214, 2224, -2224, 3112, -3112, 3114, -3114, 3122, -3122, 13122, -13122, 3124, -3124, 23122, -23122, 33122, -33122, 13124, -13124, 43122, -43122, 53122, -53122, 3126, -3126, 13126, -13126, 13212, -13212, 13214, -13214, 23212, -23212, 3216, -3216, 3212, -3212, 3214, -3214, 3222, -3222, 3224, -3224, 3312, -3312, 3314, -3314, 3322, -3322, 3324, -3324, 3334, -3334, 4112, -4112, 4114, -4114, 4122, -4122, 4132, -4132, 4212, -4212, 4214, -4214, 4222, -4222, 4224, -4224, 4232, -4232, 4312, -4312, 4314, -4314, 4322, -4322, 4324, -4324, 4332, -4332, 4334, -4334, 5112, -5112, 5114, -5114, 5122, -5122, 5132, -5132, 5212, -5212, 5214, -5214, 5222, -5222, 5224, -5224, 5232, -5232, 5312, -5312, 5314, -5314, 5322, -5322, 5324, -5324, 5332, -5332, 5334, -5334, 1101, -1101, 2101, -2101, 2201, -2201, 3101, -3101, 3201, -3201, 3301, -3301, 4101, -4101, 4201, -4201, 4301, -4301, 4401, -4401, 5101, -5101, 5201, -5201, 5301, -5301, 5401, -5401, 5501, -5501, 1103, -1103, 2103, -2103, 2203, -2203, 3103, -3103, 3203, -3203, 3303, -3303, 4103, -4103, 4203, -4203, 4303, -4303, 4403, -4403, 5103, -5103, 5203, -5203, 5303, -5303, 5403, -5403, 5503, -5503, 1011, -1011, 1021, -1021, 1012, -1012, 1022, -1022, 100, 30343, -30343, 30353, -30353, 30363, -30363};
//    const double allmasses[506] = {0.0099, 0.0099, 0.0056, 0.0056, 0.199, 0.199, 1.35, 1.35, 5., 5., 175., 175., 400., 400., 500., 500., 0, 0.000510999, 0.000510999, 0, 0, 0.1056584, 0.1056584, 0, 0, 1.7770, 1.7770, 0, 0, 400., 400., 0, 0, 0, 0, 0, 0, 91.187, 80.419, 80.419, 200., 0, 0, 500., 900., 500., 500., 300., 300., 300., 300., 5000., 5000., 1., 1., 1., 1., 0, 0, 0, 2.0, 2.0, 5.0, 5.0, 175., 175., 400., 400., 500., 500., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.134976, 0.139570, 0.139570, 0, 0, 1.30, 1.30, 1.30, 0.54784, 1.297, 0.95777, 0.7685, 0, 0.7685, 0.7685, 1.46, 1.46, 1.46, 1.70, 1.70, 1.70, 0.78257, 0, 1.42, 1.01941, 0, 0.9835, 0.9835, 0.9835, 1.000, 1.4, 1.231, 1.231, 1.231, 1.17, 1.40, 1.23, 1.23, 1.23, 1.2822, 1.4268, 1.318, 1.318, 1.318, 1.275, 1.500, 1.525, 0.49767, 0.49767, 0.49767, 0.49767, 0.49368, 0.49368, 0.8961, 0.8961, 0.8916, 0.8916, 1.429, 1.429, 1.429, 1.429, 1.273, 1.273, 1.273, 1.273, 1.432, 1.432, 1.425, 1.425, 1.402, 1.402, 1.402, 1.402, 1.414, 1.414, 1.414, 1.414, 1.717, 1.717, 1.717, 1.717, 1.776, 1.776, 1.776, 1.776, 2.045, 2.045, 2.045, 2.045, 1.8693, 1.8693, 1.8645, 1.8645, 2.010, 2.010, 2.0067, 2.0067, 2.40, 2.40, 2.40, 2.40, 2.427, 2.427, 2.4222, 2.4222, 2.459, 2.459, 2.4589, 2.4589, 2.461, 2.461, 2.461, 2.461, 1.9686, 1.9686, 2.1124, 2.1124, 2.5, 2.5, 2.53535, 2.53535, 2.5735, 2.5735, 2.56, 2.56, 2.58, 2.58, 2.58, 2.58, 2.64, 2.64, 2.64, 2.64, 5.2794, 5.2794, 5.2791, 5.2791, 5.3248, 5.3248, 5.3246, 5.3246, 5.697, 5.697, 5.697, 5.697, 5.679, 5.679, 5.679, 5.679, 5.692, 5.692, 5.692, 5.692, 5.740, 5.740, 5.740, 5.740, 5.36930, 5.36930, 5.4163, 5.4163, 5.766, 5.766, 5.810, 5.810, 5.853, 5.853, 5.840, 5.840, 6.594, 6.594, 6.602, 6.602, 7.25, 7.25, 7.30, 7.30, 7.350, 7.350, 7.40, 7.40, 2.9798, 3.594, 3.09687, 0, 3.686111, 3.7699, 4.040, 4.159, 4.415, 3.52614, 3.4150, 3.51051, 3.55618, 9.403, 9.997, 10.335, 9.46030, 10.02326, 10.3552, 10.57500, 10.865, 9.875, 10.25500, 10.51600, 9.8599, 9.8927, 9.9126, 10.2321, 10.2552, 10.2685, 10.50070, 10.51600, 10.52640, 10.157, 10.441, 10.15010, 10.15620, 10.15990, 10.43490, 10.44060, 10.44430, 1.234, 1.234, 0, 0, 0.9395656, 0.9395656, 1.233, 1.233, 0, 0, 0.9382723, 0.9382723, 1.232, 1.232, 1.231, 1.231, 1.197436, 1.197436, 1.3872, 1.3872, 1.115684, 1.115684, 1.407, 1.407, 1.5195, 1.5195, 1.6, 1.6, 1.67, 1.67, 1.69, 1.69, 1.8, 1.8, 1.81, 1.81, 1.82, 1.82, 1.83, 1.83, 1.66, 1.66, 1.67, 1.67, 1.75, 1.75, 1.775, 1.775, 1.19255, 1.19255, 1.3837, 1.3837, 1.18937, 1.18937, 1.3828, 1.3828, 1.32132, 1.32132, 1.5350, 1.5350, 1.3149, 1.3149, 1.5318, 1.5318, 1.67245, 1.67245, 2.45206, 2.45206, 2.53, 2.53, 2.2849, 2.2849, 2.4703, 2.4703, 2.4534, 2.4534, 2.53, 2.53, 2.45285, 2.45285, 2.53, 2.53, 2.4656, 2.4656, 2.55, 2.55, 2.6438, 2.6438, 2.55, 2.55, 2.64, 2.64, 2.704, 2.704, 2.8, 2.8, 5.80, 5.80, 5.81, 5.81, 5.641, 5.641, 5.84, 5.84, 5.80, 5.80, 5.81, 5.81, 5.80, 5.80, 5.81, 5.81, 5.84, 5.84, 5.96, 5.96, 5.97, 5.97, 5.96, 5.96, 5.97, 5.97, 6.12, 6.12, 6.13, 6.13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.8756134, 1.8756134, 2.80925, 2.80925, 2.80923, 2.80923, 3.727417, 3.727417, 0, 1.6000, 1.6000, 1.6000, 1.6000, 1.8000, 1.8000};

   int theg = -1000;

   vector<Hep3Vector> particles;
   Hep3Vector totalp(0.,0.,0.);
   for (viter = tree->vBegin();  viter != tree_vend;  ++viter)
      if (viter->parent().properties().QQId() == qcd) {
	 MCVertex::const_pIterator chiter;
	 MCVertex::const_pIterator viter_pend = viter->pEnd();

	 bool allknown = true;
	 int g = 1;
	 for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	    particles.push_back(chiter->momentum());
	    totalp += chiter->momentum();

	    bool known = false;
	    int id = chiter->properties().QQId();
	    for (vector<int>::const_iterator iter = godd.begin();  iter != godd.end();  ++iter)
	       if (id == *iter) { known = true;  g *= -1; }
	    for (vector<int>::const_iterator iter = geven.begin();  iter != geven.end();  ++iter)
	       if (id == *iter) { known = true;  g *= 1; }
	    if (! known) allknown = false;
	 }
	 if (allknown) {
	    if (g == 1) {m_even++; theg = 1;}
	    else {m_odd++; theg = -1;}
	 }
	 else {m_unknown++; theg = 0;}
      }
   vector<Hep3Vector>::const_iterator pbegin = particles.begin();
   vector<Hep3Vector>::const_iterator pend = particles.end();
   
   // calculate planarity
   double denom1 = 8.*pow(eBeam->value(), 3.);
   double denom2 = 0.;
   double sum = 0;
   vector<Hep3Vector>::const_iterator itPart1;
   for ( itPart1 = pbegin; itPart1 != pend; ++itPart1 )
   {   
      double p1 = itPart1->mag();
      denom2 += p1*p1*p1;
      if ( itPart1+1 != pend ) 
      {
	 vector<Hep3Vector>::const_iterator itPart2;
	 for ( itPart2 = itPart1+1; itPart2 != pend; ++itPart2 )
	 { 
	    double p2 = itPart2->mag();
	    denom2 += 3.*(p1*p1*p2 + p2*p2*p1);
	    if ( itPart2+1 != pend )
	    {
	       Hep3Vector p1_cross_p2 = 
		  (itPart1->unit()).cross(itPart2->unit());
	       vector<Hep3Vector>::const_iterator itPart3;
	       for ( itPart3 = itPart2+1; 
		     itPart3 != pend; ++itPart3 )
	       { 
		  double pNorm = 6.*p1*p2*itPart3->mag();
		  double pncake = (p1_cross_p2.dot(itPart3->unit()));    
		  denom2 += pNorm;
		  sum += pNorm*pncake*pncake;
	       }
	    }
	 }
      }
   }
   double COMPlanarity = sum/denom1;
   double TMomPlanarity = sum/denom2;

   // calculate thrust
   particles.push_back(totalp*(-0.5));
   pbegin = particles.begin();
   pend = particles.end();
   Hep3Vector P(0.,0.,0.);
   Hep3Vector P1(0.,0.,0.);
   Hep3Vector P2(0.,0.,0.);
   Hep3Vector P12(0.,0.,0.);
   Hep3Vector pJet(0.,0.,0.);
   double psqMax = 0.;
   double pDot = 0.;
   int IUP1 = 0;
   int IUP2 = 0;
   int IUP3 = 0;
   for ( itPart1 = pbegin; itPart1 != pend; ++itPart1 )
   {
      if ( itPart1 == pend-1 ) IUP1 = 1;
      IUP2 = 0;
      vector<Hep3Vector>::const_iterator itPart2;
      for ( itPart2 = pbegin; itPart2 != pend; ++itPart2 )
      {
	 if ( itPart1 != itPart2 )
	 {
	    if ( itPart2 == pend-1 ) IUP2 = 1;
	    P = Hep3Vector(0.,0.,0.);
	    // get the normal to the plane
	    Hep3Vector p1_Cross_p2 = itPart1->cross((*itPart2));
	    if ( (IUP1 != 1) && (IUP2 != 1) ) pDot = (pend-1)->dot(p1_Cross_p2);
	    if ( (pDot >= 0.) || (IUP1 == 1) || (IUP2 == 1) )
	    {
	       // Select the right side of the plane
	       IUP3 = 0;
	       vector<Hep3Vector>::const_iterator itPart3;
	       for ( itPart3 = pbegin; itPart3 != pend; ++itPart3 )
	       {
		  if ( (itPart3 != itPart1) && (itPart3 != itPart2) )
		  {
		     pDot = itPart3->dot(p1_Cross_p2);
		     if ( pDot >= 0. )
		     {
			if (itPart3 == pend-1) IUP3 = 1;
			P += (*itPart3);
		     } 
		  }
	       }
	       P1 = P + (*itPart1);
	       P2 = P + (*itPart2);
	       P12 = P1 + (*itPart2);
	       if ( P.mag2() > psqMax )
	       {
		  if ( IUP3 == 1 )
		  {
		     psqMax = P.mag2();
		     pJet = P;
		  }
	       }
	       if ( P1.mag2() > psqMax )
	       {
		  if ( (IUP3 == 1) || (IUP1 == 1) )
		  {
		     psqMax = P1.mag2();
		     pJet = P1;
		  }
	       }
	       if ( P2.mag2() > psqMax )
	       {
		  if ( (IUP3 == 1) || (IUP2 == 1) )
		  {
		     psqMax = P2.mag2();
		     pJet = P2;
		  }
	       }
	       if ( P12.mag2() > psqMax )
	       {
		  psqMax = P12.mag2();
		  pJet = P12;
	       }
	    }
	 }
      }
   }
   double denMax = 0.;
   double rNumer = 0.;
   for ( itPart1 = pbegin; itPart1 != pend; ++itPart1 )
   {  
      rNumer += fabs(itPart1->dot(pJet.unit()));
      denMax += itPart1->mag();
   }	
   double thrust_mag = rNumer/denMax;
   Hep3Vector thrust_dir = pJet.unit();

   // fill histograms!
   m_COMPlanarity->fill(COMPlanarity);
   m_TMomPlanarity->fill(TMomPlanarity);
   m_thrust_mag->fill(thrust_mag);
   m_thrust_dir->fill(thrust_dir.cosTheta());

   FAItem<TriggerL1Data> triggerDecision;
   extract(iFrame.record(Stream::kEvent), triggerDecision);

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator tracks_end = tracks.end();
   FATable<NavTrack>::const_iterator track_iter, other_iter;
   
   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   double d0close = 1000.;
   double z0close = 1000.;
   double ci = 1000.;
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

		  if (perp < ci) ci = perp;
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

   if ((triggerDecision->isHadron()  ||  triggerDecision->isRadTau()  ||  triggerDecision->isElTrack())  &&
       abs(d0close) < 0.005  &&
       props->firstLargestEShower() / eBeam->value() < 0.85  &&
       props->secondLargestPTrack() / eBeam->value() < 0.85  &&
       abs(wz) < 0.075) {
      double visen = (props->neutralEnergy() + props->chargedEnergy()) / 2. / eBeam->value();

      if (theg == 1) {
	 if (visen < 0.35) m_failp++;
	 m_allp++;
      }
      else if (theg == -1) {
	 if (visen < 0.35) m_failm++;
	 m_allm++;
      }
      else if (theg == 0) {
	 if (visen < 0.35) m_fail0++;
	 m_all0++;
      }
      else report(SYSTEM, kFacilityString) << "WTF?" << endl;

//       if (m_all0 % 1000 == 0)
// 	 report(SYSTEM, kFacilityString)
// 	    << "G-even: " << m_failp << " / " << m_allp << endl
// 	    << "G-odd: " << m_failm << " / " << m_allm << endl
// 	    << "G-other: " << m_fail0 << " / " << m_all0 << endl;

      double maxctau = 0.;
      double maxctauofall = 0.;
      int mesons = 0;
      int baryons = 0;
      int strangers = 0;
      int charmers = 0;
      
      int strange_baryons = 0;
      int nonstrange_baryons = 0;

      double maxctau_baryon = 0.;
      bool has_neutrons = false;

      double massy = 0.;
      double massy2 = 0.;

      for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
	 if (viter->parent().properties().ctau() > maxctauofall) maxctauofall = viter->parent().properties().ctau();
	 
	 if (viter->parent().properties().QQId() == qcd) {
	    MCVertex::const_pIterator chiter;
	    MCVertex::const_pIterator viter_pend = viter->pEnd();
	    
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	       if (chiter->properties().ctau() > maxctau) maxctau = chiter->properties().ctau();
	       if (chiter->properties().meson()) mesons++;
	       if (chiter->properties().baryon()) baryons++;
	       if (chiter->properties().strange()) strangers++;
	       if (chiter->properties().charmed()) charmers++;

	       if (chiter->properties().strange()  &&  chiter->properties().baryon()) strange_baryons++;
	       if (!chiter->properties().strange()  &&  chiter->properties().baryon()) nonstrange_baryons++;

	       if (chiter->properties().baryon()  &&
		   chiter->properties().ctau() > maxctau_baryon  &&
		   chiter->properties().QQId() != n0  &&
		   chiter->properties().QQId() != anti_n0)
		  maxctau_baryon = chiter->properties().ctau();

	       if (chiter->properties().QQId() == n0  ||
		   chiter->properties().QQId() == anti_n0) has_neutrons = true;

// 	       int theid = chiter->properties().QQId();
// 	       double themass = 0.;
// 	       for (int i = 0;  i < 506;  i++) if (allids[i] == theid) themass = allmasses[i];
	       massy += chiter->properties().mass();
	       massy2 += sqr(chiter->properties().mass());
	    }
	 }
      }

      static int events_strange_baryons = 0;
      static int events_nonstrange_baryons = 0;
      static int events = 0;
      static int failures_strange_baryons = 0;
      static int failures_nonstrange_baryons = 0;
      static int failures = 0;

      if (visen < 0.35) {
	 m_mesons->fill(mesons);
	 m_baryons->fill(baryons);
	 m_strangers->fill(strangers);
	 m_charmers->fill(charmers);

// 	 for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
// // 	    if (viter->parent().properties().ctau() == maxctauofall) {
// // 	       report(SYSTEM, kFacilityString) << "Failed visen; max ctau of all is " << maxctauofall
// // 					       << " particle is " << viter->parent().properties().name() << endl;
// // 	    }
	 
// 	    if (viter->parent().properties().QQId() == qcd) {
// 	       MCVertex::const_pIterator chiter;
// 	       MCVertex::const_pIterator viter_pend = viter->pEnd();
	    
// 	       for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
// // 		  if (chiter->properties().ctau() == maxctau) {
// // 		     report(SYSTEM, kFacilityString) << "Failed visen; max ctau of string is " << maxctau
// // 						     << " particle is " << chiter->properties().name() << endl;
// // 		  }
// 		  if (chiter->properties().baryon()  &&  chiter->properties().ctau() == maxctau_baryon) {
// 		     report(SYSTEM, kFacilityString) << "Failed visen; max ctau of baryon is " << maxctau_baryon
// 						     << " (excluding neutrons) particle is " << chiter->properties().name()
// 						     << (has_neutrons ? " (this event HAS neutrons)" : "") << endl;
// 		  }
// 	       }
// 	    }
// 	 }

	 if (strange_baryons > 0) failures_strange_baryons++;
	 if (nonstrange_baryons > 0) failures_nonstrange_baryons++;
	 failures++;

	 m_mass_failures->fill(massy);
	 m_mass2_failures->fill(massy2);
      }
      m_mesons_all->fill(mesons);
      m_baryons_all->fill(baryons);
      m_strangers_all->fill(strangers);
      m_charmers_all->fill(charmers);
      if (strange_baryons > 0) events_strange_baryons++;
      if (nonstrange_baryons > 0) events_nonstrange_baryons++;
      events++;

//       if (events % 1000 == 0)
// 	 report(SYSTEM, kFacilityString)
// 	    << "failed with strange baryons: " << failures_strange_baryons << " / " << events_strange_baryons << endl
// 	    << "failed with nonstrange baryons: " << failures_nonstrange_baryons << " / " << events_nonstrange_baryons << endl
// 	    << "failed: " << failures << " / " << events << endl;

      m_mass_all->fill(massy);
      m_mass2_all->fill(massy2);
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
LookAtMC::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
LookAtMC::endRun( Frame& iFrame )         // anal4 equiv.
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

DABoolean LookAtMC::calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
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

DABoolean LookAtMC::arclength_test(double x, double y, KTHelix& a, KTHelix& b)
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
