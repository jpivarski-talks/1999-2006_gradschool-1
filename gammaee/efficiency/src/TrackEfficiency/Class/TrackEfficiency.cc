// -*- C++ -*-
//
// Package:     TrackEfficiency
// Module:      TrackEfficiency
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Jul  8 13:04:40 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TrackEfficiency/TrackEfficiency.h"
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

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

#include "CleoDB/DBEventHeader.h"

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
static const char* const kFacilityString = "Processor.TrackEfficiency" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//


//
// constructors and destructor
//
TrackEfficiency::TrackEfficiency( void )               // anal1
   : Processor( "TrackEfficiency" )
   , m_isMC("isMC", this, false)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TrackEfficiency::event,    Stream::kEvent );
   //bind( &TrackEfficiency::beginRun, Stream::kBeginRun );
   //bind( &TrackEfficiency::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

TrackEfficiency::~TrackEfficiency()                    // anal5
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
TrackEfficiency::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TrackEfficiency::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
TrackEfficiency::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "run", "event",
      "fit", "chi2", "dof", "expect", "layers",
      "d0", "z0", "p", "cotth", "errct", "errz0",
      "curv", "phi0", "mctag"
   };
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label );
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TrackEfficiency::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   static int taucount = 0;

   FAItem<DBEventHeader> dbeventheader;
   extract(iFrame.record(Stream::kEvent), dbeventheader);

   FATable<NavTrack> navtrack;
   extract(iFrame.record(Stream::kEvent), navtrack);
   FATable<NavTrack>::const_iterator navtrack_end = navtrack.end();

// You wisely included showers in the Makefile!  :)
//    FATable<NavShower> navshower;
//    extract(iFrame.record(Stream::kEvent), navshower);
//    FATable<NavShower>::const_iterator navshower_end = navshower.end();

   FAItem<MCDecayTree> decaytree;
   if (m_isMC.value()) {
      FAItem<MCDecayTree> gendecaytree;
      extract(iFrame.record(Stream::kEvent), decaytree);
      extract(iFrame.record(Stream::kEvent), gendecaytree, "Generator");

      for (MCDecayTree::const_vIterator gendecaytree_iter = gendecaytree->vBegin();
	   gendecaytree_iter != gendecaytree_end;
	   ++gendecaytree_iter) {
	 int parent(gendecaytree_iter->parentPtr()->properties().QQId());

	 if (gendecaytree_iter->size() == 2) {
	    int first(gendecaytree_iter->pBegin()->properties().QQId());
	    int second((++(gendecaytree_iter->pBegin()))->properties().QQId());

	    if ( (first == eplus   &&  second == eminus)  ||
		 (first == eminus  &&  second == eplus)      ) {
	       return ActionBase::kFailed;
	    } else if ( (first == muplus   &&  second == muminus)  ||
			(first == muminus  &&  second == muplus)      ) {
	       return ActionBase::kFailed;
	    } else if ( (first == tauplus   &&  second == tauminus)  ||
			(first == tauminus  &&  second == tauplus)      ) {
	       taucount++;
	       if ( taucount % 4 != 0 ) return ActionBase::kFailed;
	    }
	 }
      } // end loop over gendecaytree

   }

   for (FATable<NavTrack>::const_iterator navtrack_iter = navtrack.begin();
	navtrack_iter != navtrack_end;
	++navtrack_iter) {
      float v[kNumEntries];

      v[kRun] = dbeventheader->run();
      v[kEvent] = dbeventheader->number();

      v[kFit] = (navtrack_iter->pionQuality()->fit()      &&
		 !navtrack_iter->pionQuality()->fitAbort()   );
      v[kChi2] = navtrack_iter->pionQuality()->chiSquare();
      v[kDOF] = navtrack_iter->pionQuality()->degreesOfFreedom();
      v[kHitsExpected] = navtrack_iter->seedQuality()->numberHitsExpected();
      v[kLayersSeen] = navtrack_iter->seedQuality()->numberLayers();
      v[kD0] = navtrack_iter->pionHelix()->d0();
      v[kZ0] = navtrack_iter->pionHelix()->z0();
      v[kMomentum] = navtrack_iter->pionFit()->momentum().mag();
      v[kCotTheta] = navtrack_iter->pionHelix()->cotTheta();
      v[kErrCotTheta] = navtrack_iter->pionHelix()->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta);
      v[kErrZ0] = navtrack_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0);

      v[kCurvature] = navtrack_iter->pionHelix()->curvature();
      v[kPhi0] = navtrack_iter->pionHelix()->phi0();

      if (m_isMC.value()) {
	 if (navtrack_iter->mcTag().valid()) {
	    const string& particleName = navtrack_iter->mcTag()->properties().name();

	    if ((particleName == "E+")  ||  (particleName == "E-")) v[kMCTag] = 1.;
	    else if ((particleName == "MU+")  ||  (particleName == "MU-")) v[kMCTag] = 2.;
	    else if ((particleName == "PI+")  ||  (particleName == "PI-")) v[kMCTag] = 3.;
	    else if ((particleName == "K+")  ||  (particleName == "K-")) v[kMCTag] = 4.;
	    else if ((particleName == "P+")  ||  (particleName == "AP+")) v[kMCTag] = 5.;
	    else v[kMCTag] = 10.;

	 } else {
	    v[kMCTag] = 0.;
	 } // track has no mctag

      } else {
	 v[kMCTag] = 0.;
      }

      m_ntuple->fill(v);
   }

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
TrackEfficiency::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
TrackEfficiency::endRun( Frame& iFrame )         // anal4 equiv.
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
