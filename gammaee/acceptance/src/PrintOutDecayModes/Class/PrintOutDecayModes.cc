// -*- C++ -*-
//
// Package:     PrintOutDecayModes
// Module:      PrintOutDecayModes
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Jun  7 14:49:08 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "PrintOutDecayModes/PrintOutDecayModes.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCVertex.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

#include "EventProperties/EventProperties.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "BeamEnergy/BeamEnergy.h"

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
static const char* const kFacilityString = "Processor.PrintOutDecayModes" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
PrintOutDecayModes::PrintOutDecayModes( void )               // anal1
   : Processor( "PrintOutDecayModes" )
   , m_firsttime(true)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &PrintOutDecayModes::event,    Stream::kEvent );
   //bind( &PrintOutDecayModes::beginRun, Stream::kBeginRun );
   //bind( &PrintOutDecayModes::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

PrintOutDecayModes::~PrintOutDecayModes()                    // anal5
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
PrintOutDecayModes::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
PrintOutDecayModes::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
PrintOutDecayModes::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
PrintOutDecayModes::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<MCDecayTree> tree;
   extract(iFrame.record(Stream::kEvent), tree, "Generator");

   if (m_firsttime) {
      const MCParticlePropertyStore& mcppstore =
	 tree->topParticle().properties().store();

      MCPPStoreItr iter = mcppstore.begin();
      MCPPStoreItr end = mcppstore.end();

      for (; iter != end;  ++iter) report(SYSTEM, kFacilityString)
	 << "PARTICLE " << iter->QQId() << " " << iter->name()
	 << " PDG " << iter->PDGId() << " GEANT " << iter->geantId()
	 << " mass " << iter->mass() << " spin " << iter->spin()
	 << " parity " << iter->parity() << " cparity " << iter->cParity()
	 << " size " << iter->size() << endl;

      m_firsttime = false;
   }

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<TriggerL1Data> trig;
   extract(iFrame.record(Stream::kEvent), trig);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   bool pass_trigger = trig->isHadron() || trig->isRadTau() || trig->isElTrack();
   bool pass_visen = (props->chargedEnergy() + props->neutralEnergy()) / 2. / eBeam->value() > 0.2;
   bool pass_antibhabha = ((props->nbChargedTracks() > 4)                         ||
			   (props->ccTotalEnergy() / 2. / eBeam->value() < 0.75)  ||
			   (props->firstMatchedEnergy() / eBeam->value() < 0.75)    );
   bool pass_antimupair = ((props->nbChargedTracks() > 4)                         ||
			   (props->ccTotalEnergy() / 2. / eBeam->value() > 0.15)    );
   int cutlevel = 0;
   if (pass_trigger) cutlevel = 1;
   if (pass_trigger && pass_visen) cutlevel = 2;
   if (pass_trigger && pass_visen && pass_antibhabha) cutlevel = 3;
   if (pass_trigger && pass_visen && pass_antibhabha && pass_antimupair) cutlevel = 4;

   report(SYSTEM, kFacilityString) << "BEGIN";
   recurse(false, tree->topParticle());
   report(SYSTEM, kFacilityString) << "CUT" << cutlevel << "END" << endl;

   return ActionBase::kPassed;
}

void PrintOutDecayModes::recurse(bool space, const MCParticle& particle) {
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

/*
ActionBase::ActionResult
PrintOutDecayModes::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
PrintOutDecayModes::endRun( Frame& iFrame )         // anal4 equiv.
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
