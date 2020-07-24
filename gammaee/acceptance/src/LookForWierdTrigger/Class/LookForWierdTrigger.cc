// -*- C++ -*-
//
// Package:     LookForWierdTrigger
// Module:      LookForWierdTrigger
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Jun  7 11:57:04 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "LookForWierdTrigger/LookForWierdTrigger.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "CleoDB/DBEventHeader.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "EventProperties/EventProperties.h"
#include "BeamEnergy/BeamEnergy.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCTrackTagger/MCTrackTagsByMCParticle.h"

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
static const char* const kFacilityString = "Processor.LookForWierdTrigger" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.25 2002/01/25 20:42:06 ajm36 Exp $";
static const char* const kTagString = "$Name: v06_03_01 $";

//
// static data member definitions
//


//
// constructors and destructor
//
LookForWierdTrigger::LookForWierdTrigger( void )               // anal1
   : Processor( "LookForWierdTrigger" )
   , m_run(0)
   , m_total(0)
   , m_03(0)
   , m_075(0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &LookForWierdTrigger::event,    Stream::kEvent );
   //bind( &LookForWierdTrigger::beginRun, Stream::kBeginRun );
   //bind( &LookForWierdTrigger::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

LookForWierdTrigger::~LookForWierdTrigger()                    // anal5
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
LookForWierdTrigger::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
LookForWierdTrigger::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)

   if (m_run != 0) summarize();
}


// ---------------- standard place to book histograms ---------------
void
LookForWierdTrigger::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
LookForWierdTrigger::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

//    FAItem<DBEventHeader> head;
//    extract(iFrame.record(Stream::kEvent), head);

//    if (head->run() != m_run) {
//       if (m_run != 0) summarize();
//       m_run = head->run();
//    }

//    FAItem<TriggerL1Data> trig;
//    extract(iFrame.record(Stream::kEvent), trig);

//    if (trig->isElTrack()) {
//       FAItem<EventProperties> props;
//       extract(iFrame.record(Stream::kEvent), props);

//       if (props->ccTotalEnergy() < 9.46030*0.03) m_03++;
//       if (props->ccTotalEnergy() < 9.46030*0.075) m_075++;
//       m_total++;
//    }

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);
   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);
   FAItem<MCDecayTree> tree;
   extract(iFrame.record(Stream::kEvent), tree);

   const MCParticlePropertyStore& mcppstore =
      tree->topParticle().properties().store();
   const int qcd = mcppstore.nameToQQId("string");
   MCDecayTree::const_vIterator viter;
   MCDecayTree::const_vIterator tree_vend = tree->vEnd();
   
   int strangers = 0;
   int baryons = 0;
   int decays = 0;
   int particles = 0;
   for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
      if (viter->parent().properties().QQId() == qcd) {
	 MCVertex::const_pIterator chiter;
	 MCVertex::const_pIterator viter_pend = viter->pEnd();
	 
	    for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
// 	       report(SYSTEM, kFacilityString)
// 		  << chiter->energy()/2./eBeam->value()
// 		  << (chiter->properties().strange() ? " strange" : "        ")
// 		  << (chiter->properties().baryon() ? " baryon" : "       ")
// 		  << " " << chiter->properties().name() << " " << chiter->momentum() << endl;

	       if (chiter->properties().strange()) strangers++;
	       if (chiter->properties().baryon()) baryons++;
	       particles++;
	    }
      }

      if (viter->position().perp() > 0.005  &&  viter->position().perp() < 0.05)
 	 decays++;
   }

   double visen = (props->chargedEnergy() + props->neutralEnergy())/2./eBeam->value();

   cout << "BONK " << visen << " " << decays << " " << strangers << " " << baryons << " " << particles << endl;

   return ActionBase::kPassed;
}

void
LookForWierdTrigger::summarize() {
   if (m_total == 0) {
      report(SYSTEM, kFacilityString)
	 << "Run " << m_run << " had no ElTrack events!" << endl;
   }
   else {
      report(SYSTEM, kFacilityString)
	 << "Run " << m_run
	 << " belowthree " << double(m_03)/double(m_total)
	 << " belowsevenfive " << double(m_075)/double(m_total) << endl;
   }

   m_total = 0;
   m_03 = 0;
   m_075 = 0;
}

/*
ActionBase::ActionResult
LookForWierdTrigger::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
LookForWierdTrigger::endRun( Frame& iFrame )         // anal4 equiv.
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
