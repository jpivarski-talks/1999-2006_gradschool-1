// -*- C++ -*-
//
// Package:     ChiSearch
// Module:      ChiSearch
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Sat Apr 23 09:40:27 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ChiSearch/ChiSearch.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
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
static const char* const kFacilityString = "Processor.ChiSearch" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.29 2002/03/19 15:07:23 cdj Exp $";
static const char* const kTagString = "$Name: v06_05_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
ChiSearch::ChiSearch( void )               // anal1
   : Processor( "ChiSearch" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &ChiSearch::event,    Stream::kEvent );
   //bind( &ChiSearch::beginRun, Stream::kBeginRun );
   //bind( &ChiSearch::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

ChiSearch::~ChiSearch()                    // anal5
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
ChiSearch::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
ChiSearch::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
ChiSearch::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "x1", "y1", "z1", "x2", "y2", "z2", "x3", "y3", "z3", "x4", "y4", "z4"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
ChiSearch::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<MCDecayTree> tree;
   extract(iFrame.record(Stream::kEvent), tree, "Generator");
   report(DEBUG, kFacilityString) << *tree << endl;

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator shower_iter = showers.begin();
   FATable<NavShower>::const_iterator shower_end = showers.end();

   FATable<NavShower>::const_iterator s1, s2, s3, s4;
   s1 = s2 = s3 = s4 = shower_end;
   for (; shower_iter != shower_end;  ++shower_iter) {
      if (shower_iter->attributes().status()  &&  !shower_iter->attributes().hot()) {
	 if (s1 == shower_end  ||  s1->attributes().energy() < shower_iter->attributes().energy()) {
	    s4 = s3;
	    s3 = s2;
	    s2 = s1;
	    s1 = shower_iter;
	 }
	 else if (s2 == shower_end  ||  s2->attributes().energy() < shower_iter->attributes().energy()) {
	    s4 = s3;
	    s3 = s2;
	    s2 = shower_iter;
	 }
	 else if (s3 == shower_end  ||  s3->attributes().energy() < shower_iter->attributes().energy()) {
	    s4 = s3;
	    s3 = shower_iter;
	 }
	 else if (s4 == shower_end  ||  s4->attributes().energy() < shower_iter->attributes().energy()) {
	    s4 = shower_iter;
	 }
      }
   }

   float v[kNumEntries];
   for (int i = 0;  i < kNumEntries;  i++) v[i] = -1000.;

   if (s1 != shower_end) {
      v[k_x1] = s1->attributes().momentum().x();
      v[k_y1] = s1->attributes().momentum().y();
      v[k_z1] = s1->attributes().momentum().z();
   }
   if (s2 != shower_end) {
      v[k_x2] = s2->attributes().momentum().x();
      v[k_y2] = s2->attributes().momentum().y();
      v[k_z2] = s2->attributes().momentum().z();
   }
   if (s3 != shower_end) {
      v[k_x3] = s3->attributes().momentum().x();
      v[k_y3] = s3->attributes().momentum().y();
      v[k_z3] = s3->attributes().momentum().z();
   }
   if (s4 != shower_end) {
      v[k_x4] = s4->attributes().momentum().x();
      v[k_y4] = s4->attributes().momentum().y();
      v[k_z4] = s4->attributes().momentum().z();
   }

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
ChiSearch::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
ChiSearch::endRun( Frame& iFrame )         // anal4 equiv.
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
