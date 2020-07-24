// -*- C++ -*-
//
// Package:     TuneAgain
// Module:      TuneAgain
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Wed Apr  6 17:59:16 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TuneAgain/TuneAgain.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackDelivery/TDKinematicFit.h"
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "EventProperties/EventProperties.h"
#include "Level4Proc/Level4Decision.h"
#include "BeamEnergy/BeamEnergy.h"
#include "BeamSpot/BeamSpot.h"
#include "CleoDB/DBEventHeader.h"
#include "RandomModule/RandomGenerator.h"



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
static const char* const kFacilityString = "Processor.TuneAgain" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TuneAgain::TuneAgain( void )               // anal1
   : Processor( "TuneAgain" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TuneAgain::event,    Stream::kEvent );
   //bind( &TuneAgain::beginRun, Stream::kBeginRun );
   //bind( &TuneAgain::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

TuneAgain::~TuneAgain()                    // anal5
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
TuneAgain::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TuneAgain::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
TuneAgain::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TuneAgain::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;


   FAItem<TriggerL1Data> l1trig;
   extract(iFrame.record(Stream::kEvent), l1trig);

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FAItem<Level4Decision> l4dec;
   extract(iFrame.record(Stream::kEvent), l4dec);

   FATable<NavShower>::const_iterator showers_end, one, two;
   showers_end = one = two = showers.end();
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
      if (!shower_iter->attributes().hot()  &&  shower_iter->attributes().status()) {
	 if (one == showers_end  ||  shower_iter->attributes().energy() > one->attributes().energy()) {
	    two = one;
	    one = shower_iter;
	 }
	 else if (two == showers_end  ||  shower_iter->attributes().energy() > two->attributes().energy()) {
	    two = shower_iter;
	 }
      }
   }
   
   if (one == showers_end  ||  two == showers_end  || 
       cos(one->attributes().theta())*cos(two->attributes().theta()) > 0.)
      return ActionBase::kFailed;
   FATable<NavShower>::const_iterator west = (cos(one->attributes().theta()) > 0. ? one : two);
   FATable<NavShower>::const_iterator east = (cos(one->attributes().theta()) > 0. ? two : one);
   
   double westphi, eastphi, westcotT, eastcotT;
   double westx, westy, westz, eastx, easty, eastz;
   if (true) {
      double d = west->attributes().distance();
      double th = west->attributes().theta();
      double ph = west->attributes().phi();
      westx = d*sin(th)*cos(ph);
      westy = d*sin(th)*sin(ph);
      westz = d*cos(th);

      westphi = atan2(d*sin(th)*sin(ph),
		      d*sin(th)*cos(ph));
      westcotT = (d*cos(th)) /
	 sqrt(sqr(d*sin(th)*cos(ph)) +
	      sqr(d*sin(th)*sin(ph)));
   }
   if (true) {
      double d = east->attributes().distance();
      double th = east->attributes().theta();
      double ph = east->attributes().phi();
      eastx = d*sin(th)*cos(ph);
      easty = d*sin(th)*sin(ph);
      eastz = d*cos(th);

      eastphi = atan2(d*sin(th)*sin(ph),
		      d*sin(th)*cos(ph));
      eastcotT = (d*cos(th)) /
	 sqrt(sqr(d*sin(th)*cos(ph)) +
	      sqr(d*sin(th)*sin(ph)));
   }
   double cotT = (westcotT - eastcotT)/2.;

   // if it's a gamgam
   if (l1trig->isBarrelBhabha()                              &&
       l4dec->decision() > 0                                 &&
       two->attributes().energy() / eBeam->value() > 0.9     &&
       props->nbChargedTracks() == 0                         &&
       excludeBlockA(westphi, cotT)                          &&
       excludeBlockBC(westphi, cotT)                         &&
       (0.05 < fabs(cotT) && fabs(cotT) < 1.38)              &&
       safeb2b(westcotT, eastcotT)                           &&
       ggacop(westphi, eastphi)                                ) {
      cout << "PYTHON " << westx << " " << westy << " " << westz << " " << eastx << " " << easty << " " << eastz << endl;
   }



   return ActionBase::kPassed;
}

bool TuneAgain::excludeBlockA(double westphi, double cotTheta)
{
   // This will return true if you're OUTSIDE of block A
   return !(-14.0/64.0*M_PI < westphi  &&
	    westphi < 9.0/64.0*M_PI    &&
	    fabs(cotTheta) < 0.54);
}

bool TuneAgain::excludeBlockBC(double westphi, double cotTheta)
{
   // This will return true if you're OUTSIDE of blocks B and C
   return !(-53.0/64.0*M_PI < westphi  &&
	    westphi < -14.0/64.0*M_PI    &&
	    fabs(cotTheta) > 0.95);
}

bool TuneAgain::safeb2b(double cotTheta1, double cotTheta2)
{
   return (fabs(cotTheta1 + cotTheta2) < 0.1);
}

bool TuneAgain::ggacop(double phi1, double phi2)
{
   return (fabs(sin(phi1 - phi2)) < 0.04);
}

bool TuneAgain::bbacop(double phi1, double phi2)
{
   return (0.04 < fabs(sin(phi1 - phi2))  &&
	   fabs(sin(phi1 - phi2)) < 0.25);
}

/*
ActionBase::ActionResult
TuneAgain::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
TuneAgain::endRun( Frame& iFrame )         // anal4 equiv.
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
