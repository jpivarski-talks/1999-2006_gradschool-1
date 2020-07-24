// -*- C++ -*-
//
// Package:     DiagnoseTrackMatching
// Module:      DiagnoseTrackMatching
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Feb 25 13:09:07 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "DiagnoseTrackMatching/DiagnoseTrackMatching.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"


#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
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
static const char* const kFacilityString = "Processor.DiagnoseTrackMatching" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_01 $";

//
// static data member definitions
//



//
// constructors and destructor
//
DiagnoseTrackMatching::DiagnoseTrackMatching( void )               // anal1
   : Processor( "DiagnoseTrackMatching" )
   , m_track_track(0)
   , m_notrack_track(0)
   , m_track_notrack(0)
   , m_notrack_notrack(0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &DiagnoseTrackMatching::event,    Stream::kEvent );
   //bind( &DiagnoseTrackMatching::beginRun, Stream::kBeginRun );
   //bind( &DiagnoseTrackMatching::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

DiagnoseTrackMatching::~DiagnoseTrackMatching()                    // anal5
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
DiagnoseTrackMatching::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
DiagnoseTrackMatching::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
DiagnoseTrackMatching::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
DiagnoseTrackMatching::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable );

   int track_track(0), notrack_track(0), track_notrack(0), notrack_notrack(0);

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();
   for (FATable< NavShower >::const_iterator showerItr = showerBegin; 
        showerItr != showerEnd ; ++showerItr )
   {
      if ( showerItr->attributes().energy() > 0.030  &&
	   ! showerItr->attributes().hot() ) {

	 if ( showerItr->noTrackMatch() ) {
	    if ( showerItr->noTrackMatchConReg() )
	       notrack_notrack++;
	    else
	       notrack_track++;
	 }
	 else {
	    if ( showerItr->noTrackMatchConReg() )
	       track_notrack++;
	    else
	       track_track++;
	 } // end if if else else four cases

      } // end passes quality cuts
   } // end loop over showers

   m_track_track += track_track;
   m_notrack_track += notrack_track;
   m_track_notrack += track_notrack;
   m_notrack_notrack += notrack_notrack;

   printf("        %15s | %15s             %15s | %15s\n", "ConRegTrack", "NoConRegTrack", "ConRegTrack", "NoConRegTrack");
   printf("        %15s-+-%15s             %15s-+-%15s\n", "---------------", "---------------", "---------------", "---------------");
   printf("  track %15d | %15d       track %15d | %15d\n", track_track, track_notrack, m_track_track, m_track_notrack);
   printf("        %15s-+-%15s             %15s-+-%15s\n", "---------------", "---------------", "---------------", "---------------");
   printf("noTrack %15d | %15d     noTrack %15d | %15d\n", notrack_track, notrack_notrack, m_notrack_track, m_notrack_notrack);
   printf("        %15s-+-%15s             %15s-+-%15s\n", "---------------", "---------------", "---------------", "---------------");
   printf("\n");

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
DiagnoseTrackMatching::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
DiagnoseTrackMatching::endRun( Frame& iFrame )         // anal4 equiv.
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
