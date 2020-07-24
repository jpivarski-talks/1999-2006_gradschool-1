// -*- C++ -*-
//
// Package:     MCConv
// Module:      MCConv
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Mar 21 14:44:32 EST 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "MCConv/MCConv.h"
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
static const char* const kFacilityString = "Processor.MCConv" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCConv::MCConv( void )               // anal1
   : Processor( "MCConv" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &MCConv::event,    Stream::kEvent );
   //bind( &MCConv::beginRun, Stream::kBeginRun );
   //bind( &MCConv::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

MCConv::~MCConv()                    // anal5
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
MCConv::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
MCConv::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
MCConv::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
MCConv::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<MCDecayTree> tree;
   extract(iFrame.record(Stream::kEvent), tree);
   MCDecayTree::const_vIterator viter;
   MCDecayTree::const_vIterator tree_vend = tree->vEnd();

   const MCParticlePropertyStore& mcppstore =
      tree->topParticle().properties().store();

   const int gamm = mcppstore.nameToQQId("GAMM");
   const int eplus = mcppstore.nameToQQId("E+");
   const int eminus = mcppstore.nameToQQId("E-");

//    vector<HepPoint3D> converts;

   for (viter = tree->vBegin();  viter != tree_vend;  ++viter) {
      if (viter->parent().properties().QQId() == gamm  &&  viter->parent().energy() > 4.) {

	 MCVertex::const_pIterator chiter;
	 MCVertex::const_pIterator viter_pend = viter->pEnd();
	 bool eplus_ = false, eminus_ = false;
	 int num = 0;
	 for (chiter = viter->pBegin();  chiter != viter_pend;  ++chiter) {
	    if (chiter->properties().QQId() == eplus) eplus_ = true;
	    if (chiter->properties().QQId() == eminus) eminus_ = true;
	    num++;
	 }
	 
	 if (num == 2  &&  eplus_  &&  eminus_  &&  viter->position().perp() < 0.8) {
// 	    converts.push_back(viter->position());
	    report(SYSTEM, kFacilityString) << "CONVERT "
					    << " " << viter->position().x()
					    << " " << viter->position().y()
					    << " " << viter->position().z() << endl;
	 }
      }
   }

//    if (converts.size() > 0) {
//       for (int i = 0;  i < converts.size();  i++) {
// 	 cout << "CONVERT " << converts.size()
// 	      << " " << converts[i].x()
// 	      << " " << converts[i].y()
// 	      << " " << converts[i].z() << endl;
//       }
//    }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
MCConv::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
MCConv::endRun( Frame& iFrame )         // anal4 equiv.
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
