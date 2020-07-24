// -*- C++ -*-
//
// Package:     NeutralPions
// Module:      NeutralPions
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Apr 22 16:44:23 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "NeutralPions/NeutralPions.h"
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
#include "PhotonDecays/PhdPi0.h"
#include "Navigation/NavPi0ToGG.h"

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
static const char* const kFacilityString = "Processor.NeutralPions" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
NeutralPions::NeutralPions( void )               // anal1
   : Processor( "NeutralPions" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &NeutralPions::event,    Stream::kEvent );
   //bind( &NeutralPions::beginRun, Stream::kBeginRun );
   //bind( &NeutralPions::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

NeutralPions::~NeutralPions()                    // anal5
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
NeutralPions::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
NeutralPions::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
NeutralPions::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here
   const char* label[kNumEntries] = {
      "pi1px", "pi1py", "pi1pz", "pi1sig", "pi1chi2", "pi1pull",
      "pi2px", "pi2py", "pi2pz", "pi2sig", "pi2chi2", "pi2pull",
      "energy", "px", "py", "pz", "mass", "mass2"
   };
   m_u1s = iHistoManager.ntuple(
      1, "u1s", kNumEntries, 262144, label);
   m_u2s = iHistoManager.ntuple(
      2, "u2s", kNumEntries, 262144, label);

   m_piSigmas = iHistoManager.histogram(
      100, "pi sigmas", 100, -8., 8.);
   m_piChisq = iHistoManager.histogram(
      101, "pi chi^2", 1000, 0., 100.);
   m_piPullMass = iHistoManager.histogram(
      102, "pi pullMass", 100, -8., 8.);

   m_mass = iHistoManager.histogram(
      200, "U(3S) recoil mass", 101, 0., 10.1);
   m_mass_narrow = iHistoManager.histogram(
      201, "U(3S) recoil mass", 100, 9.1, 10.1);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
NeutralPions::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

//    FATable<NavTrack> tracks;
//    extract(iFrame.record(Stream::kEvent), tracks);

//    FATable<NavShower> showers;
//    extract(iFrame.record(Stream::kEvent), showers);

   FATable<NavPi0ToGG> pi0s;
   extract(iFrame.record(Stream::kEvent), pi0s);
   FATable<NavPi0ToGG>::const_iterator pi0_end = pi0s.end();

   for ( FATable<NavPi0ToGG>::const_iterator pi0_one = pi0s.begin();
	 pi0_one != pi0_end;
	 ++pi0_one ) {
      m_piSigmas->fill(pi0_one->pi0().numberSigmas());
      m_piChisq->fill(pi0_one->pi0().chisq());
      m_piPullMass->fill(pi0_one->pi0().pullMass());

      if ( pi0_one->pi0().numberSigmas() > -3                    &&
	   pi0_one->pi0().numberSigmas() <  2                    &&
	   pi0_one->pi0().fit()  &&  pi0_one->pi0().converged()  &&
	   pi0_one->pi0().pullMass() > -3                        &&
	   pi0_one->pi0().pullMass() <  2                           ) {

	 for ( FATable<NavPi0ToGG>::const_iterator pi0_two = pi0_one;
	       pi0_two != pi0_end;
	       ++pi0_two ) {
	    if ( pi0_one != pi0_two ) {
	       if ( pi0_two->pi0().numberSigmas() > -3                    &&
		    pi0_two->pi0().numberSigmas() <  2                    &&
		    pi0_two->pi0().fit()  &&  pi0_two->pi0().converged()  &&
		    pi0_two->pi0().pullMass() > -3                        &&
		    pi0_two->pi0().pullMass() <  2                           ) {

		  const PhdPi0& pi1 = pi0_one->pi0();	    
		  const PhdPi0& pi2 = pi0_two->pi0();	    
	    
		  double energy(pi1.energy() + pi2.energy());
		  Hep3Vector momentum(pi1.momentum() + pi2.momentum());
		  Hep3Vector momentum2(pi1.momentum() + pi2.momentum() + Hep3Vector(0.028,0.,0.));
	    
		  const double u1s_mass = 9.46030;
		  const double u2s_mass = 10.02326;
		  const double u3s_mass = 10.3552;
		  double recoil_mass(sqrt(sqr(u3s_mass-energy) - momentum.mag2()));
		  double recoil_mass2(sqrt(sqr(u3s_mass-energy) - momentum2.mag2()));

		  int i;  float v[kNumEntries];  for (i = 0;  i < kNumEntries;  i++) v[i] = 0.;
		  v[kPi1PX] = pi1.momentum().x();
		  v[kPi1PY] = pi1.momentum().y();
		  v[kPi1PZ] = pi1.momentum().z();
		  v[kPi1Sigmas] = pi1.numberSigmas();
		  v[kPi1Chi2] = pi1.chisq();
		  v[kPi1PullMass] = pi1.pullMass();
		  v[kPi2PX] = pi2.momentum().x();
		  v[kPi2PY] = pi2.momentum().y();
		  v[kPi2PZ] = pi2.momentum().z();
		  v[kPi2Sigmas] = pi2.numberSigmas();
		  v[kPi2Chi2] = pi2.chisq();
		  v[kPi2PullMass] = pi2.pullMass();
		  v[kEnergy] = energy;
		  v[kMomentumX] = momentum.x();
		  v[kMomentumY] = momentum.y();
		  v[kMomentumZ] = momentum.z();
		  v[kMass] = recoil_mass;
		  v[kMass2] = recoil_mass2;

		  m_mass->fill(recoil_mass);
		  m_mass_narrow->fill(recoil_mass);

		  if ( abs(recoil_mass - u1s_mass) < 0.050 ) {
		     m_u1s->fill(v);
		     return ActionBase::kPassed;
		  }

		  if ( abs(recoil_mass - u2s_mass) < 0.050 ) {
		     m_u2s->fill(v);
		     return ActionBase::kPassed;
		  }

	       } // if two really is a pi0
	    } // if not the same pi0
	 } // second loop over pi0s
      } // if one really is a pi0
   } // first loop over pi0s

   return ActionBase::kFailed;
}

/*
ActionBase::ActionResult
NeutralPions::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
NeutralPions::endRun( Frame& iFrame )         // anal4 equiv.
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
