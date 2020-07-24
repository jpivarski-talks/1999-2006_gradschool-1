// -*- C++ -*-
//
// Package:     ChiBMC
// Module:      ChiBMC
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Feb 16 18:51:32 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ChiBMC/ChiBMC.h"
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
static const char* const kFacilityString = "Processor.ChiBMC" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
ChiBMC::ChiBMC( void )               // anal1
   : Processor( "ChiBMC" )
   , m_mc("mc", this, 0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &ChiBMC::event,    Stream::kEvent );
   //bind( &ChiBMC::beginRun, Stream::kBeginRun );
   //bind( &ChiBMC::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

ChiBMC::~ChiBMC()                    // anal5
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
ChiBMC::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
ChiBMC::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
ChiBMC::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;


}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
ChiBMC::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<MCDecayTree> tree;
   extract(iFrame.record(Stream::kEvent), tree, "Generator");
   MCDecayTree::const_vIterator viter;
   MCDecayTree::const_vIterator tree_vend = tree->vEnd();

   const MCParticlePropertyStore& mcppstore =
      tree->topParticle().properties().store();
   const int ups1 = mcppstore.nameToQQId("UPS1");
   const int muplus = mcppstore.nameToQQId("MU+");
   const int muminus = mcppstore.nameToQQId("MU-");
   const int chib0 = mcppstore.nameToQQId("CHIB0");
   const int chib1 = mcppstore.nameToQQId("CHIB1");
   const int chib2 = mcppstore.nameToQQId("CHIB2");
   const int gamm = mcppstore.nameToQQId("GAMM");

   bool two_muons = false;
   bool chib0_to_upsilon = false;
   bool chib1_to_upsilon = false;
   bool chib2_to_upsilon = false;
   for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
      if (viter->parent().properties().QQId() == ups1) {

	 MCVertex::const_pIterator chiter;
	 MCVertex::const_pIterator viter_pend = viter->pEnd();
	 
	 int children = 0;
	 bool muplus_ = false;
	 bool muminus_ = false;
	 for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	    children++;
	    if (chiter->properties().QQId() == muplus) muplus_ = true;
	    if (chiter->properties().QQId() == muminus) muminus_ = true;
	 } // end loop over children
	 if (children == 2 && muplus_ && muminus_) two_muons = true;
      } // end if parent is an upsilon
      else if (viter->parent().properties().QQId() == chib0  ||
	       viter->parent().properties().QQId() == chib1  ||
	       viter->parent().properties().QQId() == chib2     ) {

	 MCVertex::const_pIterator chiter;
	 MCVertex::const_pIterator viter_pend = viter->pEnd();
	 
	 int children = 0;
	 bool gamm_, ups1_;
	 gamm_ = ups1_ = false;
	 for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	    children++;
	    if (chiter->properties().QQId() == gamm) gamm_ = true;
	    if (chiter->properties().QQId() == ups1) ups1_ = true;
	 } // end loop over children
	 if (children == 2 && gamm_ && ups1_) {
	    if (viter->parent().properties().QQId() == chib0) chib0_to_upsilon = true;
	    if (viter->parent().properties().QQId() == chib1) chib1_to_upsilon = true;
	    if (viter->parent().properties().QQId() == chib2) chib2_to_upsilon = true;
	 } // end if we see chib to upsilon
      } // end else if parent is a chib
   } // end loop over vertices

   if (m_mc.value() == 0  &&
       (chib0_to_upsilon && two_muons))
      return ActionBase::kPassed;

   if (m_mc.value() == 1  &&
       (chib1_to_upsilon && two_muons))
      return ActionBase::kPassed;

   if (m_mc.value() == 2  &&
       (chib2_to_upsilon && two_muons))
      return ActionBase::kPassed;

   if (m_mc.value() == -1  &&
       (!(chib0_to_upsilon && two_muons) &&
	!(chib1_to_upsilon && two_muons) &&
	!(chib2_to_upsilon && two_muons)   ))
      return ActionBase::kPassed;

   return ActionBase::kFailed;
}

/*
ActionBase::ActionResult
ChiBMC::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
ChiBMC::endRun( Frame& iFrame )         // anal4 equiv.
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
