// -*- C++ -*-
//
// Package:     UpsToLeptons
// Module:      UpsToLeptons
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Wed Sep 11 13:15:35 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "UpsToLeptons/UpsToLeptons.h"
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

#include "CleoDB/DBEventHeader.h"
#include "BunchFinder/BunchDecision.h"
#include "TrackletBunchFinder/TrackletBunchDecision.h"
#include "Navigation/NavShower.h"
#include "Navigation/NavTkShMatch.h"
#include "C3cc/CcShowerAttributes.h"
#include "EventProperties/EventProperties.h"

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
static const char* const kFacilityString = "Processor.UpsToLeptons" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.31 2002/06/12 20:06:57 cleo3 Exp $";
static const char* const kTagString = "$Name: v06_06_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
UpsToLeptons::UpsToLeptons( void )               // anal1
   : Processor( "UpsToLeptons" )
   , m_parent( "parent", this, "UPS3" )
   , m_passElectrons( "passE", this, false )
   , m_passMuons( "passMu", this, false )
   , m_passTaus( "passTau", this, false )
   , m_total(0)
   , m_electrons(0)
   , m_muons(0)
   , m_taus(0)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &UpsToLeptons::event,    Stream::kEvent );
   //bind( &UpsToLeptons::beginRun, Stream::kBeginRun );
   //bind( &UpsToLeptons::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

UpsToLeptons::~UpsToLeptons()                    // anal5
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
UpsToLeptons::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
UpsToLeptons::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)

   if ( m_passElectrons.value() )
      report( SYSTEM, kFacilityString )
	 << "electrons: " << m_electrons << " / " << m_total << " = "
	 << double(m_electrons) / double(m_total) << endl;
   if ( m_passMuons.value() )
      report( SYSTEM, kFacilityString )
	 << "muons:     " << m_muons << " / " << m_total << " = "
	 << double(m_muons) / double(m_total) << endl;
   if ( m_passTaus.value() )
      report( SYSTEM, kFacilityString )
	 << "taus:      " << m_taus << " / " << m_total << " = "
	 << double(m_taus) / double(m_total) << endl;
}


// ---------------- standard place to book histograms ---------------
void
UpsToLeptons::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
UpsToLeptons::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;
   m_total++;

   if ( m_total % 1000 == 0 ) {
      if ( m_passElectrons.value() )
	 report( NOTICE, kFacilityString )
	    << "electrons: " << m_electrons << " / " << m_total << " = "
	    << double(m_electrons) / double(m_total) << endl;
      if ( m_passMuons.value() )
	 report( NOTICE, kFacilityString )
	    << "muons:     " << m_muons << " / " << m_total << " = "
	    << double(m_muons) / double(m_total) << endl;
      if ( m_passTaus.value() )
	 report( NOTICE, kFacilityString )
	    << "taus:      " << m_taus << " / " << m_total << " = "
	    << double(m_taus) / double(m_total) << endl;
   }

   FAItem< MCDecayTree > decayTree;
   extract( iFrame.record( Stream::kEvent ), decayTree, "Generator" );
   MCDecayTree::const_vIterator viter;
   MCDecayTree::const_vIterator vbegin = decayTree->vBegin();
   MCDecayTree::const_vIterator vend = decayTree->vEnd();

   vector< string > electrons;
   electrons.push_back( "E+" );
   electrons.push_back( "E-" );
   vector< string > muons;
   muons.push_back( "MU+" );
   muons.push_back( "MU-" );
   vector< string > taus;
   taus.push_back( "TAU+" );
   taus.push_back( "TAU-" );

   for ( viter = vbegin;  viter != vend;  viter++ ) {
      if ( m_passElectrons.value()  &&
	   viter->isType(electrons, m_parent.value().c_str()) ) {
	 m_electrons++;
	 return ActionBase::kPassed;
      }

      if ( m_passMuons.value()  &&
	   viter->isType(muons, m_parent.value().c_str()) ) {
	 m_muons++;
	 return ActionBase::kPassed;
      }

      if ( m_passTaus.value()  &&
	   viter->isType(taus, m_parent.value().c_str()) ) {
	 m_taus++;
	 return ActionBase::kPassed;
      }
   }

   return ActionBase::kFailed;
}

/*
ActionBase::ActionResult
UpsToLeptons::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
UpsToLeptons::endRun( Frame& iFrame )         // anal4 equiv.
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
