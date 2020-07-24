// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      DeliverDummyMCDT
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Sun Apr  2 17:27:35 EDT 2000
// $Id: DeliverDummyMCDT.cc,v 1.2 2001/12/19 18:12:28 lkg Exp $
//
// Revision history
//
// $Log: DeliverDummyMCDT.cc,v $
// Revision 1.2  2001/12/19 18:12:28  lkg
// don't build privaty dummy propert store.  Use dummy store created for property Storage Helpers
//
// Revision 1.1  2000/05/01 22:40:23  lkg
// added storage helpers to repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
#include <map>
#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "MCInfo/Storage/DeliverDummyMCDT.h"
#include "MCInfo/Storage/DeliverDummyMCPPS.h"

#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCVertex.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
#include <map>
#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.DeliverDummyMCDT" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DeliverDummyMCDT.cc,v 1.2 2001/12/19 18:12:28 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_00 $";

//
// static data member definitions
//
DeliverDummyMCDT* DeliverDummyMCDT::m_instance = 0;

//
// constructors and destructor
//
DeliverDummyMCDT::DeliverDummyMCDT() :
   m_dummyDecayTree()
{
   //get the dummy joe particle from the dummy particle property store
   const MCParticleProperty& joeProperty = 
      DeliverDummyMCPPS::instance().dummyMCParticleProperty();

   // Now create a dummy particle
   HepPoint3D parentPosition( 0.001, 0.002, 0.003 );
   double energy = sqrt( 1.1*1.1 + 1.2*1.2 + 1.3*1.3 + 0.139570*0.139570 );
   HepLorentzVector lorentzMomentum( 1.1, 1.2, 1.3, 2.087937 );
   MCParticle* dummyPart = new MCParticle( joeProperty,
					   lorentzMomentum,
					   parentPosition );

   // Now create a dummy vertex
   HepPoint3D vertexPosition( 0.01,  0.02,  0.03  );
   MCVertex* dummyVertex = MCVertex::newVertex( kiRangeOut, 
						dummyPart,
						vertexPosition,
						0.04,
						lorentzMomentum );

   // finally, assign the particle/vertex to the decayTree
   m_dummyDecayTree.setParent( dummyPart );
}

// DeliverDummyMCDT::DeliverDummyMCDT( const DeliverDummyMCDT& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

DeliverDummyMCDT::~DeliverDummyMCDT()
{
}

//
// assignment operators
//
// const DeliverDummyMCDT& DeliverDummyMCDT::operator=( const DeliverDummyMCDT& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//

//
// const member functions
//
MCDecayTree&
DeliverDummyMCDT::dummyMCDecayTree() {
   return m_dummyDecayTree;
}

MCParticle&
DeliverDummyMCDT::dummyMCParticle() {
   return m_dummyDecayTree.topParticle();
}

MCVertex&
DeliverDummyMCDT::dummyMCVertex() {
   return *(m_dummyDecayTree.topParticle().vBegin());
}

//
// static member functions
//
DeliverDummyMCDT&
DeliverDummyMCDT::instance( void ) {
   // If there does not exist an object yet, create one on the heap
   if ( m_instance == 0 ) {
      m_instance = new DeliverDummyMCDT();
   }
   
   return *m_instance;
}
