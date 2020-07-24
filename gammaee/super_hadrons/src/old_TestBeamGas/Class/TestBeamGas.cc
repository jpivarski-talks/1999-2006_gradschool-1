// -*- C++ -*-
//
// Package:     TestBeamGas
// Module:      TestBeamGas
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Feb  4 16:45:09 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TestBeamGas/TestBeamGas.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"

#include "CleoDB/DBEventHeader.h"
#include "EventProperties/EventProperties.h"
#include "BeamSpot/BeamSpot.h"
#include "BeamEnergy/BeamEnergy.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"

//RICH example 
//Dedx example
//Event Shape example


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
static const char* const kFacilityString = "Processor.TestBeamGas" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_01 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TestBeamGas::TestBeamGas( void )               // anal1
   : Processor( "TestBeamGas" )
   , m_closestIntersectionCut( "closestIntersectionCut", this, 0.005 )
   , m_weightedZCut( "weightedZCut", this, 0.05 )
   , m_weightedZCleverness( "weightedZCleverness", this, 0. )
   , m_explicitBeamSpot( "explicitBeamSpot", this, false )
   , m_beamX( "beamX", this, 0. )
   , m_beamY( "beamY", this, 0. )
   , m_beamZ( "beamZ", this, 0. )
   , m_beam_x(0.)
   , m_beam_y(0.)
   , m_beam_z(0.)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TestBeamGas::event,    Stream::kEvent );
   bind( &TestBeamGas::beginRun, Stream::kBeginRun );
   //bind( &TestBeamGas::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

TestBeamGas::~TestBeamGas()                    // anal5
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
TestBeamGas::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TestBeamGas::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
TestBeamGas::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_charge = iHistoManager.histogram(
      100, "charge (bkh)", 31, -15.5, 15.5);
   m_raw_charge = iHistoManager.histogram(
      150, "raw charge (me)", 31, -15.5, 15.5);

   m_z = iHistoManager.histogram(
      200, "z (me)", 30, -0.15, 0.15);
   m_z_p1 = iHistoManager.histogram(
      201, "z (me) Q.ge.1", 30, -0.15, 0.15);
   m_z_m1 = iHistoManager.histogram(
      202, "z (me) Q.le.-1", 30, -0.15, 0.15);
   m_z_p2 = iHistoManager.histogram(
      203, "z (me) Q.ge.2", 30, -0.15, 0.15);
   m_z_m2 = iHistoManager.histogram(
      204, "z (me) Q.le.-2", 30, -0.15, 0.15);
   m_z_rp1 = iHistoManager.histogram(
      251, "z (me) rawQ.ge.1", 30, -0.15, 0.15);
   m_z_rm1 = iHistoManager.histogram(
      252, "z (me) rawQ.le.-1", 30, -0.15, 0.15);
   m_z_rp2 = iHistoManager.histogram(
      253, "z (me) rawQ.ge.2", 30, -0.15, 0.15);
   m_z_rm2 = iHistoManager.histogram(
      254, "z (me) rawQ.le.-2", 30, -0.15, 0.15);

   m_neutralEnergy = iHistoManager.histogram(
      300, "neutral energy (bkh)", 36, 0., 12.);
   m_neutralEnergy_p1 = iHistoManager.histogram(
      301, "neutral energy (bkh) Q.ge.1", 36, 0., 12.);
   m_neutralEnergy_m1 = iHistoManager.histogram(
      302, "neutral energy (bkh) Q.le.-1", 36, 0., 12.);
   m_neutralEnergy_p2 = iHistoManager.histogram(
      303, "neutral energy (bkh) Q.ge.2", 36, 0., 12.);
   m_neutralEnergy_m2 = iHistoManager.histogram(
      304, "neutral energy (bkh) Q.le.-2", 36, 0., 12.);
   m_neutralEnergy_rp1 = iHistoManager.histogram(
      351, "neutral energy (bkh) rawQ.ge.1", 36, 0., 12.);
   m_neutralEnergy_rm1 = iHistoManager.histogram(
      352, "neutral energy (bkh) rawQ.le.-1", 36, 0., 12.);
   m_neutralEnergy_rp2 = iHistoManager.histogram(
      353, "neutral energy (bkh) rawQ.ge.2", 36, 0., 12.);
   m_neutralEnergy_rm2 = iHistoManager.histogram(
      354, "neutral energy (bkh) rawQ.le.-2", 36, 0., 12.);

   m_visibleEnergy = iHistoManager.histogram(
      400, "visible energy (bkh)", 36, 0., 12.);
   m_visibleEnergy_p1 = iHistoManager.histogram(
      401, "visible energy (bkh) Q.ge.1", 36, 0., 12.);
   m_visibleEnergy_m1 = iHistoManager.histogram(
      402, "visible energy (bkh) Q.le.-1", 36, 0., 12.);
   m_visibleEnergy_p2 = iHistoManager.histogram(
      403, "visible energy (bkh) Q.ge.2", 36, 0., 12.);
   m_visibleEnergy_m2 = iHistoManager.histogram(
      404, "visible energy (bkh) Q.le.-2", 36, 0., 12.);
   m_visibleEnergy_rp1 = iHistoManager.histogram(
      451, "visible energy (bkh) rawQ.ge.1", 36, 0., 12.);
   m_visibleEnergy_rm1 = iHistoManager.histogram(
      452, "visible energy (bkh) rawQ.le.-1", 36, 0., 12.);
   m_visibleEnergy_rp2 = iHistoManager.histogram(
      453, "visible energy (bkh) rawQ.ge.2", 36, 0., 12.);
   m_visibleEnergy_rm2 = iHistoManager.histogram(
      454, "visible energy (bkh) rawQ.le.-2", 36, 0., 12.);

   m_shower_energy = iHistoManager.histogram(
      500, "CC energy (me)", 36, 0., 12.);
   m_shower_energy_p1 = iHistoManager.histogram(
      501, "CC energy (me) Q.ge.1", 36, 0., 12.);
   m_shower_energy_m1 = iHistoManager.histogram(
      502, "CC energy (me) Q.le.-1", 36, 0., 12.);
   m_shower_energy_p2 = iHistoManager.histogram(
      503, "CC energy (me) Q.ge.2", 36, 0., 12.);
   m_shower_energy_m2 = iHistoManager.histogram(
      504, "CC energy (me) Q.le.-2", 36, 0., 12.);
   m_shower_energy_rp1 = iHistoManager.histogram(
      551, "CC energy (me) rawQ.ge.1", 36, 0., 12.);
   m_shower_energy_rm1 = iHistoManager.histogram(
      552, "CC energy (me) rawQ.le.-1", 36, 0., 12.);
   m_shower_energy_rp2 = iHistoManager.histogram(
      553, "CC energy (me) rawQ.ge.2", 36, 0., 12.);
   m_shower_energy_rm2 = iHistoManager.histogram(
      554, "CC energy (me) rawQ.le.-2", 36, 0., 12.);

   m_num_showers = iHistoManager.histogram(
      600, "num showers (me)", 41, -0.5, 40.5);
   m_num_showers_p1 = iHistoManager.histogram(
      601, "num showers (me) Q.ge.1", 41, -0.5, 40.5);
   m_num_showers_m1 = iHistoManager.histogram(
      602, "num showers (me) Q.le.-1", 41, -0.5, 40.5);
   m_num_showers_p2 = iHistoManager.histogram(
      603, "num showers (me) Q.ge.2", 41, -0.5, 40.5);
   m_num_showers_m2 = iHistoManager.histogram(
      604, "num showers (me) Q.le.-2", 41, -0.5, 40.5);
   m_num_showers_rp1 = iHistoManager.histogram(
      651, "num showers (me) rawQ.ge.1", 41, -0.5, 40.5);
   m_num_showers_rm1 = iHistoManager.histogram(
      652, "num showers (me) rawQ.le.-1", 41, -0.5, 40.5);
   m_num_showers_rp2 = iHistoManager.histogram(
      653, "num showers (me) rawQ.ge.2", 41, -0.5, 40.5);
   m_num_showers_rm2 = iHistoManager.histogram(
      654, "num showers (me) rawQ.le.-2", 41, -0.5, 40.5);

   m_matched1 = iHistoManager.histogram(
      700, "matched energy 1 (bkh)", 30, 0., 1.5);
   m_matched1_p1 = iHistoManager.histogram(
      701, "matched energy 1 (bkh) Q.ge.1", 30, 0., 1.5);
   m_matched1_m1 = iHistoManager.histogram(
      702, "matched energy 1 (bkh) Q.le.-1", 30, 0., 1.5);
   m_matched1_p2 = iHistoManager.histogram(
      703, "matched energy 1 (bkh) Q.ge.2", 30, 0., 1.5);
   m_matched1_m2 = iHistoManager.histogram(
      704, "matched energy 1 (bkh) Q.le.-2", 30, 0., 1.5);
   m_matched1_rp1 = iHistoManager.histogram(
      751, "matched energy 1 (bkh) rawQ.ge.1", 30, 0., 1.5);
   m_matched1_rm1 = iHistoManager.histogram(
      752, "matched energy 1 (bkh) rawQ.le.-1", 30, 0., 1.5);
   m_matched1_rp2 = iHistoManager.histogram(
      753, "matched energy 1 (bkh) rawQ.ge.2", 30, 0., 1.5);
   m_matched1_rm2 = iHistoManager.histogram(
      754, "matched energy 1 (bkh) rawQ.le.-2", 30, 0., 1.5);

   m_matched2 = iHistoManager.histogram(
      800, "matched energy 2 (bkh)", 30, 0., 1.5);
   m_matched2_p1 = iHistoManager.histogram(
      801, "matched energy 2 (bkh) Q.ge.1", 30, 0., 1.5);
   m_matched2_m1 = iHistoManager.histogram(
      802, "matched energy 2 (bkh) Q.le.-1", 30, 0., 1.5);
   m_matched2_p2 = iHistoManager.histogram(
      803, "matched energy 2 (bkh) Q.ge.2", 30, 0., 1.5);
   m_matched2_m2 = iHistoManager.histogram(
      804, "matched energy 2 (bkh) Q.le.-2", 30, 0., 1.5);
   m_matched2_rp1 = iHistoManager.histogram(
      851, "matched energy 2 (bkh) rawQ.ge.1", 30, 0., 1.5);
   m_matched2_rm1 = iHistoManager.histogram(
      852, "matched energy 2 (bkh) rawQ.le.-1", 30, 0., 1.5);
   m_matched2_rp2 = iHistoManager.histogram(
      853, "matched energy 2 (bkh) rawQ.ge.2", 30, 0., 1.5);
   m_matched2_rm2 = iHistoManager.histogram(
      854, "matched energy 2 (bkh) rawQ.le.-2", 30, 0., 1.5);

   m_shower1 = iHistoManager.histogram(
      900, "energy 1 (me)", 30, 0., 3.);
   m_shower1_p1 = iHistoManager.histogram(
      901, "energy 1 (me) Q.ge.1", 30, 0., 3.);
   m_shower1_m1 = iHistoManager.histogram(
      902, "energy 1 (me) Q.le.-1", 30, 0., 3.);
   m_shower1_p2 = iHistoManager.histogram(
      903, "energy 1 (me) Q.ge.2", 30, 0., 3.);
   m_shower1_m2 = iHistoManager.histogram(
      904, "energy 1 (me) Q.le.-2", 30, 0., 3.);
   m_shower1_rp1 = iHistoManager.histogram(
      951, "energy 1 (me) rawQ.ge.1", 30, 0., 3.);
   m_shower1_rm1 = iHistoManager.histogram(
      952, "energy 1 (me) rawQ.le.-1", 30, 0., 3.);
   m_shower1_rp2 = iHistoManager.histogram(
      953, "energy 1 (me) rawQ.ge.2", 30, 0., 3.);
   m_shower1_rm2 = iHistoManager.histogram(
      954, "energy 1 (me) rawQ.le.-2", 30, 0., 3.);

   m_shower2 = iHistoManager.histogram(
      1000, "energy 2 (me)", 30, 0., 1.5);
   m_shower2_p1 = iHistoManager.histogram(
      1001, "energy 2 (me) Q.ge.1", 30, 0., 1.5);
   m_shower2_m1 = iHistoManager.histogram(
      1002, "energy 2 (me) Q.le.-1", 30, 0., 1.5);
   m_shower2_p2 = iHistoManager.histogram(
      1003, "energy 2 (me) Q.ge.2", 30, 0., 1.5);
   m_shower2_m2 = iHistoManager.histogram(
      1004, "energy 2 (me) Q.le.-2", 30, 0., 1.5);
   m_shower2_rp1 = iHistoManager.histogram(
      1051, "energy 2 (me) rawQ.ge.1", 30, 0., 1.5);
   m_shower2_rm1 = iHistoManager.histogram(
      1052, "energy 2 (me) rawQ.le.-1", 30, 0., 1.5);
   m_shower2_rp2 = iHistoManager.histogram(
      1053, "energy 2 (me) rawQ.ge.2", 30, 0., 1.5);
   m_shower2_rm2 = iHistoManager.histogram(
      1054, "energy 2 (me) rawQ.le.-2", 30, 0., 1.5);

   m_shower3 = iHistoManager.histogram(
      1100, "energy 3 (me)", 30, 0., 1.5);
   m_shower3_p1 = iHistoManager.histogram(
      1101, "energy 3 (me) Q.ge.1", 30, 0., 1.5);
   m_shower3_m1 = iHistoManager.histogram(
      1102, "energy 3 (me) Q.le.-1", 30, 0., 1.5);
   m_shower3_p2 = iHistoManager.histogram(
      1103, "energy 3 (me) Q.ge.2", 30, 0., 1.5);
   m_shower3_m2 = iHistoManager.histogram(
      1104, "energy 3 (me) Q.le.-2", 30, 0., 1.5);
   m_shower3_rp1 = iHistoManager.histogram(
      1151, "energy 3 (me) rawQ.ge.1", 30, 0., 1.5);
   m_shower3_rm1 = iHistoManager.histogram(
      1152, "energy 3 (me) rawQ.le.-1", 30, 0., 1.5);
   m_shower3_rp2 = iHistoManager.histogram(
      1153, "energy 3 (me) rawQ.ge.2", 30, 0., 1.5);
   m_shower3_rm2 = iHistoManager.histogram(
      1154, "energy 3 (me) rawQ.le.-2", 30, 0., 1.5);

   m_shower4 = iHistoManager.histogram(
      1200, "energy 4 (me)", 30, 0., 1.5);
   m_shower4_p1 = iHistoManager.histogram(
      1201, "energy 4 (me) Q.ge.1", 30, 0., 1.5);
   m_shower4_m1 = iHistoManager.histogram(
      1202, "energy 4 (me) Q.le.-1", 30, 0., 1.5);
   m_shower4_p2 = iHistoManager.histogram(
      1203, "energy 4 (me) Q.ge.2", 30, 0., 1.5);
   m_shower4_m2 = iHistoManager.histogram(
      1204, "energy 4 (me) Q.le.-2", 30, 0., 1.5);
   m_shower4_rp1 = iHistoManager.histogram(
      1251, "energy 4 (me) rawQ.ge.1", 30, 0., 1.5);
   m_shower4_rm1 = iHistoManager.histogram(
      1252, "energy 4 (me) rawQ.le.-1", 30, 0., 1.5);
   m_shower4_rp2 = iHistoManager.histogram(
      1253, "energy 4 (me) rawQ.ge.2", 30, 0., 1.5);
   m_shower4_rm2 = iHistoManager.histogram(
      1254, "energy 4 (me) rawQ.le.-2", 30, 0., 1.5);

   m_shower5 = iHistoManager.histogram(
      1300, "energy 5 (me)", 30, 0., 1.5);
   m_shower5_p1 = iHistoManager.histogram(
      1301, "energy 5 (me) Q.ge.1", 30, 0., 1.5);
   m_shower5_m1 = iHistoManager.histogram(
      1302, "energy 5 (me) Q.le.-1", 30, 0., 1.5);
   m_shower5_p2 = iHistoManager.histogram(
      1303, "energy 5 (me) Q.ge.2", 30, 0., 1.5);
   m_shower5_m2 = iHistoManager.histogram(
      1304, "energy 5 (me) Q.le.-2", 30, 0., 1.5);
   m_shower5_rp1 = iHistoManager.histogram(
      1351, "energy 5 (me) rawQ.ge.1", 30, 0., 1.5);
   m_shower5_rm1 = iHistoManager.histogram(
      1352, "energy 5 (me) rawQ.le.-1", 30, 0., 1.5);
   m_shower5_rp2 = iHistoManager.histogram(
      1353, "energy 5 (me) rawQ.ge.2", 30, 0., 1.5);
   m_shower5_rm2 = iHistoManager.histogram(
      1354, "energy 5 (me) rawQ.le.-2", 30, 0., 1.5);

   const char* label[kNumEntries] = {
      "q", "rq", 
      "z", "neue", "vise", "mat1", "mat2", "nsh", "cce", 
      "sh1", "sh2", "sh3", "sh4", "sh5" };
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label );
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TestBeamGas::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   double z(calc_z(iFrame));

   FAItem<EventProperties> prop;
   extract(iFrame.record(Stream::kEvent), prop);
   
//    if ( abs(z)>0.05  &&  prop->neutralEnergy() < 1. ) {
//       FAItem< MCDecayTree > decayTree;
//       extract( iFrame.record( Stream::kEvent ), decayTree, "Generator" );
//       MCDecayTree::const_vIterator end = decayTree->vEnd();
//       for ( MCDecayTree::const_vIterator viter = decayTree->vBegin();
// 	    viter != end;
// 	    viter++ ) {
// 	 viter->dump( report( SYSTEM, kFacilityString ) );
// 	 report( SYSTEM, kFacilityString ) << endl;
//       }

//       return ActionBase::kPassed;
//    }

//    return ActionBase::kFailed;

   int charge(prop->netCharge());
   double neutralEnergy(prop->neutralEnergy());
   double visibleEnergy(prop->eVis());
   double matched1(prop->firstMatchedEnergy());
   double matched2(prop->secondMatchedEnergy());

   FATable<NavTrack> track;
   extract(iFrame.record(Stream::kEvent), track);
   FATable<NavTrack>::const_iterator track_end = track.end();

   int raw_charge(0);

   for ( FATable<NavTrack>::const_iterator track_iter = track.begin();
	 track_iter != track_end;
	 ++track_iter )
      raw_charge += (track_iter->pionHelix()->curvature() > 0. ? 1 : -1 );

   FATable<NavShower> shower;
   extract(iFrame.record(Stream::kEvent), shower);
   FATable<NavShower>::const_iterator shower_end = shower.end();

   FAItem<BeamEnergy> beam;
   extract(iFrame.record(Stream::kStartRun), beam);

   int num_showers(0);
   double shower_energy(0.);
   double shower1(0.);
   double shower2(0.);
   double shower3(0.);
   double shower4(0.);
   double shower5(0.);

   for ( FATable<NavShower>::const_iterator shower_iter = shower.begin();
	 shower_iter != shower_end;
	 ++shower_iter )
      if ( !shower_iter->attributes().hot()                        &&
	   shower_iter->attributes().status()                      &&
	   shower_iter->attributes().energy() > 0.01*beam->value()    ) {
	 num_showers++;
	 shower_energy += shower_iter->attributes().energy();

	 double energy(shower_iter->attributes().energy());
	 if ( energy > shower1 ) {
	    shower5 = shower4;
	    shower4 = shower3;
	    shower3 = shower2;
	    shower2 = shower1;
	    shower1 = energy;
	 }
	 else if ( energy > shower2 ) {
	    shower5 = shower4;
	    shower4 = shower3;
	    shower3 = shower2;
	    shower2 = energy;
	 }
	 else if ( energy > shower3 ) {
	    shower5 = shower4;
	    shower4 = shower3;
	    shower3 = energy;
	 }
	 else if ( energy > shower4 ) {
	    shower5 = shower4;
	    shower4 = energy;
	 }
	 else if ( energy > shower5 ) {
	    shower5 = energy;
	 }
      } // end if shower good/loop over showers

   m_charge->fill(charge);
   m_raw_charge->fill(raw_charge);

   m_z->fill(z);
   if ( charge >= 1 ) m_z_p1->fill(z);
   if ( charge <= -1 ) m_z_m1->fill(z);
   if ( charge >= 2 ) m_z_p2->fill(z);
   if ( charge <= -2 ) m_z_m2->fill(z);
   if ( raw_charge >= 1 ) m_z_rp1->fill(z);
   if ( raw_charge <= -1 ) m_z_rm1->fill(z);
   if ( raw_charge >= 2 ) m_z_rp2->fill(z);
   if ( raw_charge <= -2 ) m_z_rm2->fill(z);

   m_neutralEnergy->fill(neutralEnergy);
   if ( charge >= 1 ) m_neutralEnergy_p1->fill(neutralEnergy);
   if ( charge <= -1 ) m_neutralEnergy_m1->fill(neutralEnergy);
   if ( charge >= 2 ) m_neutralEnergy_p2->fill(neutralEnergy);
   if ( charge <= -2 ) m_neutralEnergy_m2->fill(neutralEnergy);
   if ( raw_charge >= 1 ) m_neutralEnergy_rp1->fill(neutralEnergy);
   if ( raw_charge <= -1 ) m_neutralEnergy_rm1->fill(neutralEnergy);
   if ( raw_charge >= 2 ) m_neutralEnergy_rp2->fill(neutralEnergy);
   if ( raw_charge <= -2 ) m_neutralEnergy_rm2->fill(neutralEnergy);

   m_visibleEnergy->fill(visibleEnergy);
   if ( charge >= 1 ) m_visibleEnergy_p1->fill(visibleEnergy);
   if ( charge <= -1 ) m_visibleEnergy_m1->fill(visibleEnergy);
   if ( charge >= 2 ) m_visibleEnergy_p2->fill(visibleEnergy);
   if ( charge <= -2 ) m_visibleEnergy_m2->fill(visibleEnergy);
   if ( raw_charge >= 1 ) m_visibleEnergy_rp1->fill(visibleEnergy);
   if ( raw_charge <= -1 ) m_visibleEnergy_rm1->fill(visibleEnergy);
   if ( raw_charge >= 2 ) m_visibleEnergy_rp2->fill(visibleEnergy);
   if ( raw_charge <= -2 ) m_visibleEnergy_rm2->fill(visibleEnergy);

   m_matched1->fill(matched1);
   if ( charge >= 1 ) m_matched1_p1->fill(matched1);
   if ( charge <= -1 ) m_matched1_m1->fill(matched1);
   if ( charge >= 2 ) m_matched1_p2->fill(matched1);
   if ( charge <= -2 ) m_matched1_m2->fill(matched1);
   if ( raw_charge >= 1 ) m_matched1_rp1->fill(matched1);
   if ( raw_charge <= -1 ) m_matched1_rm1->fill(matched1);
   if ( raw_charge >= 2 ) m_matched1_rp2->fill(matched1);
   if ( raw_charge <= -2 ) m_matched1_rm2->fill(matched1);

   m_matched2->fill(matched2);
   if ( charge >= 1 ) m_matched2_p1->fill(matched2);
   if ( charge <= -1 ) m_matched2_m1->fill(matched2);
   if ( charge >= 2 ) m_matched2_p2->fill(matched2);
   if ( charge <= -2 ) m_matched2_m2->fill(matched2);
   if ( raw_charge >= 1 ) m_matched2_rp1->fill(matched2);
   if ( raw_charge <= -1 ) m_matched2_rm1->fill(matched2);
   if ( raw_charge >= 2 ) m_matched2_rp2->fill(matched2);
   if ( raw_charge <= -2 ) m_matched2_rm2->fill(matched2);

   m_num_showers->fill(num_showers);
   if ( charge >= 1 ) m_num_showers_p1->fill(num_showers);
   if ( charge <= -1 ) m_num_showers_m1->fill(num_showers);
   if ( charge >= 2 ) m_num_showers_p2->fill(num_showers);
   if ( charge <= -2 ) m_num_showers_m2->fill(num_showers);
   if ( raw_charge >= 1 ) m_num_showers_rp1->fill(num_showers);
   if ( raw_charge <= -1 ) m_num_showers_rm1->fill(num_showers);
   if ( raw_charge >= 2 ) m_num_showers_rp2->fill(num_showers);
   if ( raw_charge <= -2 ) m_num_showers_rm2->fill(num_showers);

   m_shower_energy->fill(shower_energy);
   if ( charge >= 1 ) m_shower_energy_p1->fill(shower_energy);
   if ( charge <= -1 ) m_shower_energy_m1->fill(shower_energy);
   if ( charge >= 2 ) m_shower_energy_p2->fill(shower_energy);
   if ( charge <= -2 ) m_shower_energy_m2->fill(shower_energy);
   if ( raw_charge >= 1 ) m_shower_energy_rp1->fill(shower_energy);
   if ( raw_charge <= -1 ) m_shower_energy_rm1->fill(shower_energy);
   if ( raw_charge >= 2 ) m_shower_energy_rp2->fill(shower_energy);
   if ( raw_charge <= -2 ) m_shower_energy_rm2->fill(shower_energy);

   m_shower1->fill(shower1);
   if ( charge >= 1 ) m_shower1_p1->fill(shower1);
   if ( charge <= -1 ) m_shower1_m1->fill(shower1);
   if ( charge >= 2 ) m_shower1_p2->fill(shower1);
   if ( charge <= -2 ) m_shower1_m2->fill(shower1);
   if ( raw_charge >= 1 ) m_shower1_rp1->fill(shower1);
   if ( raw_charge <= -1 ) m_shower1_rm1->fill(shower1);
   if ( raw_charge >= 2 ) m_shower1_rp2->fill(shower1);
   if ( raw_charge <= -2 ) m_shower1_rm2->fill(shower1);

   m_shower2->fill(shower2);
   if ( charge >= 1 ) m_shower2_p1->fill(shower2);
   if ( charge <= -1 ) m_shower2_m1->fill(shower2);
   if ( charge >= 2 ) m_shower2_p2->fill(shower2);
   if ( charge <= -2 ) m_shower2_m2->fill(shower2);
   if ( raw_charge >= 1 ) m_shower2_rp1->fill(shower2);
   if ( raw_charge <= -1 ) m_shower2_rm1->fill(shower2);
   if ( raw_charge >= 2 ) m_shower2_rp2->fill(shower2);
   if ( raw_charge <= -2 ) m_shower2_rm2->fill(shower2);

   m_shower3->fill(shower3);
   if ( charge >= 1 ) m_shower3_p1->fill(shower3);
   if ( charge <= -1 ) m_shower3_m1->fill(shower3);
   if ( charge >= 2 ) m_shower3_p2->fill(shower3);
   if ( charge <= -2 ) m_shower3_m2->fill(shower3);
   if ( raw_charge >= 1 ) m_shower3_rp1->fill(shower3);
   if ( raw_charge <= -1 ) m_shower3_rm1->fill(shower3);
   if ( raw_charge >= 2 ) m_shower3_rp2->fill(shower3);
   if ( raw_charge <= -2 ) m_shower3_rm2->fill(shower3);

   m_shower4->fill(shower4);
   if ( charge >= 1 ) m_shower4_p1->fill(shower4);
   if ( charge <= -1 ) m_shower4_m1->fill(shower4);
   if ( charge >= 2 ) m_shower4_p2->fill(shower4);
   if ( charge <= -2 ) m_shower4_m2->fill(shower4);
   if ( raw_charge >= 1 ) m_shower4_rp1->fill(shower4);
   if ( raw_charge <= -1 ) m_shower4_rm1->fill(shower4);
   if ( raw_charge >= 2 ) m_shower4_rp2->fill(shower4);
   if ( raw_charge <= -2 ) m_shower4_rm2->fill(shower4);

   m_shower5->fill(shower5);
   if ( charge >= 1 ) m_shower5_p1->fill(shower5);
   if ( charge <= -1 ) m_shower5_m1->fill(shower5);
   if ( charge >= 2 ) m_shower5_p2->fill(shower5);
   if ( charge <= -2 ) m_shower5_m2->fill(shower5);
   if ( raw_charge >= 1 ) m_shower5_rp1->fill(shower5);
   if ( raw_charge <= -1 ) m_shower5_rm1->fill(shower5);
   if ( raw_charge >= 2 ) m_shower5_rp2->fill(shower5);
   if ( raw_charge <= -2 ) m_shower5_rm2->fill(shower5);

   float v[kNumEntries];
   v[kCharge] = charge;
   v[kRawCharge] = raw_charge;
   v[kZ] = z;
   v[kNeutralenergy] = neutralEnergy;
   v[kVisibleenergy] = visibleEnergy;
   v[kMatched1] = matched1;
   v[kMatched2] = matched2;
   v[kNumShowers] = num_showers;
   v[kShowerEnergy] = shower_energy;
   v[kShower1] = shower1;
   v[kShower2] = shower2;
   v[kShower3] = shower3;
   v[kShower4] = shower4;
   v[kShower5] = shower5;
   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

ActionBase::ActionResult
TestBeamGas::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   m_beam_x = m_beamX.value();
   m_beam_y = m_beamY.value();
   m_beam_z = m_beamZ.value();

   if ( ! m_explicitBeamSpot.value() ) {
      FAItem< BeamSpot > spot;
      extract( iFrame.record( Stream::kBeginRun ), spot );
      m_beam_x = spot->center().x();
      m_beam_y = spot->center().y();
      m_beam_z = spot->center().z();
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
TestBeamGas::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

double
TestBeamGas::calc_z(Frame& iFrame)
{
   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   double weighted_z(1000.);
   double znumer(0.);
   double zdenom(0.);

   FATable< NavTrack >::const_iterator track_iter;
   FATable< NavTrack >::const_iterator other_iter;
   for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ ) {
      if ( ! track_iter->seedQuality()->originUsed()            &&
	   ! track_iter->pionQuality()->fitAbort()              &&
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&
	   ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {
	 // Secondary track loop to calculate pairwise intersections
	 for ( other_iter = track_iter;  other_iter != tracks_end;  other_iter++ ) {
	    if ( other_iter != track_iter  &&
		 ! other_iter->seedQuality()->originUsed()            &&
		 ! other_iter->pionQuality()->fitAbort()              &&
		 1./abs(other_iter->pionHelix()->curvature()) > 0.42  &&
		 ! other_iter->pionHelix()->hasNullErrorMatrix()        
	       ) { 
	       double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);

	       KTHelix track( *track_iter->pionHelix() );
	       KTHelix other( *other_iter->pionHelix() );

	       if ( calc_intersection( tx, ty, tz, tsig2z, tzsep, track, other ) ) {

		  double perp( sqrt(sqr(tx - m_beam_x) + sqr(ty - m_beam_y)) );

		  if ( abs(m_weightedZCleverness.value() - 0.) < .1 ) {
		     // uncertainty in the z intersection + mismatch in z + mismatch in perp
		     double z_uncert2( tsig2z + sqr(tzsep) + sqr(tx - m_beam_x) + sqr(ty - m_beam_y) );
		     znumer += tz / z_uncert2;
		     zdenom += 1. / z_uncert2;
		  }
		  else if ( abs(m_weightedZCleverness.value() - -1.) < .1 ) {
		     // uncertainty in the z intersection + mismatch in z, cut on perp
		     if ( perp > m_closestIntersectionCut.value() ) {
			double z_uncert2( tsig2z + sqr(tzsep) );
			znumer += tz / z_uncert2;
			zdenom += 1. / z_uncert2;
		     }
		  }
		  else {
		     report(EMERGENCY, kFacilityString)
			<< "unknown weightedZCleverness mode"
			<< m_weightedZCleverness.value() << endl;
		     assert(false);
		  }

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over tracks

   if ( zdenom != 0. ) weighted_z = znumer / zdenom;

   return weighted_z - m_beam_z;
}

DABoolean TestBeamGas::calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
					       KTHelix& a, KTHelix& b )
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
   if ( abs( sqr(xsol1 - xa) + sqr(ysol1a - ya) - sqr(ra) ) <
	abs( sqr(xsol1 - xa) + sqr(ysol1b - ya) - sqr(ra) )   )
      ysol1 = ysol1a;
   else
      ysol1 = ysol1b;

   double ysol2a( yb + sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2b( yb - sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2;
   if ( abs( sqr(xsol2 - xa) + sqr(ysol2a - ya) - sqr(ra) ) <
	abs( sqr(xsol2 - xa) + sqr(ysol2b - ya) - sqr(ra) )   )
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

DABoolean TestBeamGas::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
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

   return ( aarclength > -tailCut  &&  aarclength < M_PI/2./abs(a.curvature()) )  &&
      ( barclength > -tailCut  &&  barclength < M_PI/2./abs(b.curvature()) );
}

//
// const member functions
//

//
// static member functions
//
