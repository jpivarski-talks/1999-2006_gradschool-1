// -*- C++ -*-
//
// Package:     GetRadBhas
// Module:      GetRadBhas
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Sep 21 15:12:33 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "GetRadBhas/GetRadBhas.h"
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
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "BeamEnergy/BeamEnergy.h"
#include "EventProperties/EventProperties.h"
#include "Navigation/NavTkShMatch.h"

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
static const char* const kFacilityString = "Processor.GetRadBhas" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
GetRadBhas::GetRadBhas( void )               // anal1
   : Processor( "GetRadBhas" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &GetRadBhas::event,    Stream::kEvent );
   //bind( &GetRadBhas::beginRun, Stream::kBeginRun );
   //bind( &GetRadBhas::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

GetRadBhas::~GetRadBhas()                    // anal5
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
GetRadBhas::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
GetRadBhas::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
GetRadBhas::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   const char* label[kNumEntries] = {
      "e1", "e2", "e3",
      "p1x", "p1y", "p1z", "p2x", "p2y", "p2z", "p3x", "p3y", "p3z",
      "m1", "m2", "m3", "tracks", "ccen", "ebeam", "radtau"};
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label);
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
GetRadBhas::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<TriggerL1Data> trig;
   extract(iFrame.record(Stream::kEvent), trig);

   if (!trig->isElTrack()) return ActionBase::kFailed;

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator shower1, shower2, shower3;
   FATable<NavShower>::const_iterator shower_end = showers.end();

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   if (props->firstShowerIdentifier() == 0   ||
       props->secondShowerIdentifier() == 0  ||
       props->thirdShowerIdentifier() == 0     ) return ActionBase::kFailed;

   shower1 = showers.find(props->firstShowerIdentifier());
   shower2 = showers.find(props->secondShowerIdentifier());
   shower3 = showers.find(props->thirdShowerIdentifier());
   if (shower1 == shower_end  ||  shower2 == shower_end  ||  shower3 == shower_end) return ActionBase::kFailed;

   if (shower2->attributes().energy() > 0.95 * eBeam->value()) return ActionBase::kFailed;
   if (shower3->attributes().energy() < 0.08 * eBeam->value()) return ActionBase::kFailed;

   double total_energy = (shower1->attributes().energy() +
			  shower2->attributes().energy() +
			  shower3->attributes().energy()  );
   if (abs(total_energy - 2. * eBeam->value()) > 1) return ActionBase::kFailed;

   double perp1 = shower1->attributes().momentum().perp();
   double perp2 = shower2->attributes().momentum().perp();

   double a_phi1 = shower1->attributes().phi()-acos(1.15*0.44674/2./perp1)-M_PI*3./2.;
   double a_phi2 = shower2->attributes().phi()+acos(1.15*0.44674/2./perp2)+M_PI*3./2.;
   Hep3Vector a_momentum1 = Hep3Vector(cos(a_phi1)*perp1,
				       sin(a_phi1)*perp1,
				       shower1->attributes().momentum().z());
   Hep3Vector a_momentum2 = Hep3Vector(cos(a_phi2)*perp2,
				       sin(a_phi2)*perp2,
				       shower2->attributes().momentum().z());
   Hep3Vector a_total_momentum = (a_momentum1 + a_momentum2 +
				  shower3->attributes().momentum());

   double b_phi1 = shower1->attributes().phi()+acos(1.15*0.44674/2./perp1)+M_PI*3./2.;
   double b_phi2 = shower2->attributes().phi()-acos(1.15*0.44674/2./perp2)-M_PI*3./2.;
   Hep3Vector b_momentum1 = Hep3Vector(cos(b_phi1)*perp1,
				       sin(b_phi1)*perp1,
				       shower1->attributes().momentum().z());
   Hep3Vector b_momentum2 = Hep3Vector(cos(b_phi2)*perp2,
				       sin(b_phi2)*perp2,
				       shower2->attributes().momentum().z());
   Hep3Vector b_total_momentum = (b_momentum1 + b_momentum2 +
				  shower3->attributes().momentum());

   char which = 'a';
   double total_momentum_mag = a_total_momentum.mag();
   if (b_total_momentum.mag() < a_total_momentum.mag()) {
      which = 'b';
      total_momentum_mag = b_total_momentum.mag();
   }
   if (total_momentum_mag > 1) return ActionBase::kFailed;

   if (shower1->noSimpleMatch()  &&  shower2->noSimpleMatch()) return ActionBase::kFailed;

   float v[kNumEntries];
   v[k_e1] = shower1->attributes().energy();
   v[k_e2] = shower2->attributes().energy();
   v[k_e3] = shower3->attributes().energy();
   if (which == 'a') {
      v[k_p1x] = a_momentum1.x();
      v[k_p1y] = a_momentum1.y();
      v[k_p1z] = a_momentum1.z();
      v[k_p2x] = a_momentum2.x();
      v[k_p2y] = a_momentum2.y();
      v[k_p2z] = a_momentum2.z();
   }
   else {
      v[k_p1x] = b_momentum1.x();
      v[k_p1y] = b_momentum1.y();
      v[k_p1z] = b_momentum1.z();
      v[k_p2x] = b_momentum2.x();
      v[k_p2y] = b_momentum2.y();
      v[k_p2z] = b_momentum2.z();
   }
   v[k_p3x] = shower3->attributes().momentum().x();
   v[k_p3y] = shower3->attributes().momentum().y();
   v[k_p3z] = shower3->attributes().momentum().z();
   v[k_m1] = !shower1->noSimpleMatch();
   v[k_m2] = !shower2->noSimpleMatch();
   v[k_m3] = !shower3->noSimpleMatch();
   v[k_tracks] = props->nbChargedTracks();
   v[k_ccen] = props->ccTotalEnergy();
   v[k_ebeam] = eBeam->value();
   v[k_radtau] = trig->isRadTau();
   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
GetRadBhas::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
GetRadBhas::endRun( Frame& iFrame )         // anal4 equiv.
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
