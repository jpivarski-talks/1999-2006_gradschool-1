// -*- C++ -*-
//
// Package:     Quickie
// Module:      Quickie
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Fri May  6 18:34:03 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Quickie/Quickie.h"
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
static const char* const kFacilityString = "Processor.Quickie" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Quickie::Quickie( void )               // anal1
   : Processor( "Quickie" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Quickie::event,    Stream::kEvent );
   //bind( &Quickie::beginRun, Stream::kBeginRun );
   //bind( &Quickie::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Quickie::~Quickie()                    // anal5
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
Quickie::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Quickie::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
Quickie::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Quickie::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

//    if (props->firstLargestEShower() > 7.5) return ActionBase::kPassed;
//    return ActionBase::kFailed;

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);

   bool haveone = false;
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();
	shower_iter != showers.end();
	++shower_iter) {
      if (cos(shower_iter->attributes().theta()) > 0.85  &&
	  atan2(sin(shower_iter->attributes().phi()), cos(shower_iter->attributes().phi())) > 1.5  &&
	  shower_iter->attributes().energy() > 0.100) {
	 haveone = true;
      }
   }
   
   if (haveone && props->secondLargestEShower() < 3.) {
      report(SYSTEM, kFacilityString) << "visen = " << props->chargedEnergy() + props->neutralEnergy() << endl;
      return ActionBase::kPassed;
   }
   return ActionBase::kFailed;
}

/*
ActionBase::ActionResult
Quickie::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Quickie::endRun( Frame& iFrame )         // anal4 equiv.
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
