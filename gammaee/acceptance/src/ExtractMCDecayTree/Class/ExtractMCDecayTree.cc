// -*- C++ -*-
//
// Package:     ExtractMCDecayTree
// Module:      ExtractMCDecayTree
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Thu May  6 14:32:16 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ExtractMCDecayTree/ExtractMCDecayTree.h"
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

#include "MCTriggerPhase/MCTriggerPhase.h"
#include "MCBeam/MCTrueRfBucket.h"
#include "MCBeam/MCBeamParticles.h"
#include "MCBeam/MCEventVertex.h"

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
static const char* const kFacilityString = "Processor.ExtractMCDecayTree" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

// Some handy typedefs for accessing MC information
typedef MCDecayTree::const_vIterator MCVertexConstIt;
typedef MCDecayTree::const_pIterator MCPartConstIt;
typedef MCVertex::const_pIterator    MCChildConstIt;

//
// static data member definitions
//


// These are functions you might write to identify certain
//   signal decays in a general decay tree
// In your own code, you might consider making these member functions

// Checks whether a particular decay vertex is a B decay
static
DABoolean
isBDecay( const MCVertex& vtx )
{
   const MCParticleProperty& parent = vtx.parent().properties();
 
   // Is this a B?
   // (You might instead consider using the bottom() member function
   //   in MCParticleProprty . . .)
   if ((parent.name() == "B+") ||
       (parent.name() == "B-") ||
       (parent.name() == "B0") ||
       (parent.name() == "B0B"))
   {
      return true;
   }

   return false;
}

// Checks whether a particular decay vertex is B -> X_u l nu
static
DABoolean
isBXulnu( const MCVertex& vtx )
{
   // Is this a B decay?
   if (!isBDecay(vtx)) return false;

   // To be a signal B -> Xu l nu decay, we want all daughters to either
   //   be a lepton, neutrino, or non-charmed
   
   // Loop over daughters of the vertex
   int numNeutrinos = 0;
   int numLeptons   = 0;
   MCChildConstIt   childEnd = vtx.pEnd();
   for (MCChildConstIt child = vtx.pBegin();
        child != childEnd; ++child)
   {
      const MCParticleProperty& childProp = child->properties();
      
      if (childProp.neutrino()) ++numNeutrinos;
      if (childProp.lepton())   ++numLeptons;

      if (childProp.charmed()) return false;
   }
   
   return ((numNeutrinos == 1) && (numLeptons == 1));
}

//
// constructors and destructor
//
ExtractMCDecayTree::ExtractMCDecayTree( void )               // anal1
   : Processor( "ExtractMCDecayTree" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &ExtractMCDecayTree::event,    Stream::kEvent );
   //bind( &ExtractMCDecayTree::beginRun, Stream::kBeginRun );
   //bind( &ExtractMCDecayTree::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

ExtractMCDecayTree::~ExtractMCDecayTree()                    // anal5
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
ExtractMCDecayTree::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
ExtractMCDecayTree::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
ExtractMCDecayTree::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
ExtractMCDecayTree::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;


   // ************************
   // MC Decay Tree example
   // ************************

   // Extract decay tree for this event
   // N.B. Default usage tag is appropriate for DriverDelivery, where we
   //   just want whatever is reconstituted from the roar file.
   // The "Generator" usage tag is used with QQDriverDelivery to access
   //   just the QQ decay tree before/without the particles added by cleog.
   // This is only relevant for MC generation when one needs to
   //   distinguish between the two.
   FAItem< MCDecayTree > decayTree;
   extract( iFrame.record( Stream::kEvent ), decayTree, "Generator" );

   // Some things we can do with the decay tree:

   // A. Let's see what we got
   report(SYSTEM, kFacilityString) << (*decayTree) << endl;

//    FAItem<MCTriggerPhase> triggerphase;
//    extract( iFrame.record( Stream::kEvent ), triggerphase );

//    FAItem<MCTrueRfBucket> truerfbucket;
//    extract( iFrame.record( Stream::kEvent ), truerfbucket );

//    FAItem<MCBeamParticles> beamparticles;
//    extract( iFrame.record( Stream::kEvent ), beamparticles );

//    FAItem<MCEventVertex> eventvertex;
//    extract( iFrame.record( Stream::kEvent ), eventvertex );





//    // B. Iterate over all particles in the tree and count the number
//    //    of Klongs

//    // Get access to the underlying MCParticlePropertyStore
//    // (The only way to do this right now)
//    const MCParticlePropertyStore& mcppstore =
//      decayTree->topParticle().properties().store();
 
//    // For convenience, let's turn the particle name into a QQ Id
//    int qqid1 = mcppstore.nameToQQId("K0L");
 
//    // And we'll want the charge conjugate as well
//    // (Well, not for Klong, but you might want it for other types
//    //   of particles)
//    int qqid2 = mcppstore.conjugateQQ(qqid1);
  
//    int numKlong = 0;

//    // Now step through all particles in the tree
//    MCPartConstIt treeBegin = decayTree->pBegin();
//    MCPartConstIt treeEnd   = decayTree->pEnd();
//    for( MCPartConstIt partItr = treeBegin; 
//         partItr != treeEnd ; ++partItr )
//    {
//       const MCParticleProperty& partProp = partItr->properties();

//       // Print out particle name and it's four-momentum
//       report( INFO, kFacilityString )
//          << "Particle: "
//          << partItr->properties().name()
//          << " (QQ Id: " << partItr->properties().QQId() << ") "
//          << "p4 = " << partItr->lorentzMomentum()
//          << endl;

//       // Check if this is a Klong
//       if ((partProp.QQId() == qqid1) || (partProp.QQId() == qqid2))
//       {
//         ++numKlong;
//       }
//    }

//    report( INFO, kFacilityString )
//       << "Number of KL: " << numKlong << endl;

//    // C. Look for a B -> X_u l nu decay by iterating over all
//    //    vertices in the decay tree

//    // Start/stop
//    MCVertexConstIt vtxBegin = decayTree->vBegin();
//    MCVertexConstIt vtxEnd   = decayTree->vEnd();
 
//    for (MCVertexConstIt vtx = vtxBegin; vtx != vtxEnd; ++vtx)
//    {
//       // Check if this is (the) signal vertex
//       if (isBXulnu(*vtx))
//       {
//          // Loop over daughters and find the neutrino
//          MCChildConstIt   childEnd = vtx->pEnd();
//          for (MCChildConstIt child = vtx->pBegin();
//               child != childEnd; ++child)
//          {
//             const MCParticleProperty& childProp = child->properties();
            
//             // Identify the neutrino flavor
//             if (childProp.neutrino())
//             {
//                report( DEBUG, kFacilityString )
//                  << "Found the signal decay. The neutrino is a "
//                  << childProp.name() << endl;
//             }
//          }
         
//          // Break out of loop since we found what we wanted
//          // You could do whatever else you wanted here instead
//          break;
//       }
//    }



   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
ExtractMCDecayTree::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
ExtractMCDecayTree::endRun( Frame& iFrame )         // anal4 equiv.
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
