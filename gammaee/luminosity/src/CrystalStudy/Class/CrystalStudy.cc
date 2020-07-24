// -*- C++ -*-
//
// Package:     CrystalStudy
// Module:      CrystalStudy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Thu Apr 14 11:41:14 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "CrystalStudy/CrystalStudy.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "EventProperties/EventProperties.h"
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"

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
static const char* const kFacilityString = "Processor.CrystalStudy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.40 2005/02/10 16:03:57 chengp Exp $";
static const char* const kTagString = "$Name: v07_02_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
CrystalStudy::CrystalStudy( void )               // anal1
   : Processor( "CrystalStudy" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &CrystalStudy::event,    Stream::kEvent );
   //bind( &CrystalStudy::beginRun, Stream::kBeginRun );
   //bind( &CrystalStudy::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

CrystalStudy::~CrystalStudy()                    // anal5
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
CrystalStudy::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
CrystalStudy::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
CrystalStudy::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   const char* label[kNumEntries] = {
   "hot1", "en1", "ener1", "th1", "ther1", "phi1", "phier1", "d1", "e9251", "mass1", "wid1", "zwid1", "neff1", "nhit1", "nhitu1", "ring1", "cell1", "naive1", "thb1", "phb1", "thp1", "php1", "pock1", 
      "hot2", "en2", "ener2", "th2", "ther2", "phi2", "phier2", "d2", "e9252", "mass2", "wid2", "zwid2", "neff2", "nhit2", "nhitu2", "ring2", "cell2", "naive2", "thb2", "phb2", "thp2", "php2", "pock2", 
   };
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
CrystalStudy::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);
   if (props->nbChargedTracks() > 1) return ActionBase::kFailed;

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator s1 = showers.find(props->firstShowerIdentifier());
   FATable<NavShower>::const_iterator s2 = showers.find(props->secondShowerIdentifier());
   
   float v[kNumEntries];
   for (int i = 0;  i < kNumEntries;  i++) v[i] = -1000.;

   if (s1 != showers.end()) {
      v[k_hot1] = s1->attributes().hot();
      v[k_en1] = s1->attributes().energy();
      v[k_ener1] = s1->attributes().errEnergy();
      v[k_th1] = s1->attributes().theta();
      v[k_ther1] = s1->attributes().errTheta();
      v[k_phi1] = s1->attributes().phi();
      v[k_phier1] = s1->attributes().errPhi();
      v[k_d1] = s1->attributes().distance();
      v[k_e9251] = s1->attributes().e9oe25();
      v[k_mass1] = s1->attributes().mass();
      v[k_wid1] = s1->attributes().width();
      v[k_zwid1] = s1->attributes().zWidth();
      v[k_neff1] = s1->attributes().nEffective();
      v[k_nhit1] = s1->attributes().nHits();
      v[k_nhitu1] = s1->attributes().nHitsUsed();
      v[k_ring1] = s1->attributes().ringId();
      v[k_cell1] = s1->attributes().bigCellId();
      v[k_naive1] = s1->attributes().naiveEnergy();
      v[k_thb1] = s1->attributes().thetaBlock();
      v[k_phb1] = s1->attributes().phiBlock();
      v[k_thp1] = s1->attributes().thetaPock();
      v[k_php1] = s1->attributes().phiPock();
      v[k_pock1] = s1->attributes().pocket();
   }

   if (s2 != showers.end()) {
      v[k_hot2] = s2->attributes().hot();
      v[k_en2] = s2->attributes().energy();
      v[k_ener2] = s2->attributes().errEnergy();
      v[k_th2] = s2->attributes().theta();
      v[k_ther2] = s2->attributes().errTheta();
      v[k_phi2] = s2->attributes().phi();
      v[k_phier2] = s2->attributes().errPhi();
      v[k_d2] = s2->attributes().distance();
      v[k_e9252] = s2->attributes().e9oe25();
      v[k_mass2] = s2->attributes().mass();
      v[k_wid2] = s2->attributes().width();
      v[k_zwid2] = s2->attributes().zWidth();
      v[k_neff2] = s2->attributes().nEffective();
      v[k_nhit2] = s2->attributes().nHits();
      v[k_nhitu2] = s2->attributes().nHitsUsed();
      v[k_ring2] = s2->attributes().ringId();
      v[k_cell2] = s2->attributes().bigCellId();
      v[k_naive2] = s2->attributes().naiveEnergy();
      v[k_thb2] = s2->attributes().thetaBlock();
      v[k_phb2] = s2->attributes().phiBlock();
      v[k_thp2] = s2->attributes().thetaPock();
      v[k_php2] = s2->attributes().phiPock();
      v[k_pock2] = s2->attributes().pocket();
   }

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
CrystalStudy::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
CrystalStudy::endRun( Frame& iFrame )         // anal4 equiv.
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
