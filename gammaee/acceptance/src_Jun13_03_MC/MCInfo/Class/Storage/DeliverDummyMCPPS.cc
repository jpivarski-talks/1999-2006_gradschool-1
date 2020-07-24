// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      DeliverDummyMCPPS
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Sun Apr  2 17:27:35 EDT 2000
// $Id: DeliverDummyMCPPS.cc,v 1.1 2001/12/19 18:20:07 lkg Exp $
//
// Revision history
//
// $Log: DeliverDummyMCPPS.cc,v $
// Revision 1.1  2001/12/19 18:20:07  lkg
// add storage helpers for particle properties
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
#include "Experiment/report.h"
#include "MCInfo/Storage/DeliverDummyMCPPS.h"

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

static const char* const kFacilityString = "MCInfo.DeliverDummyMCPPS" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DeliverDummyMCPPS.cc,v 1.1 2001/12/19 18:20:07 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_02 $";

//
// static data member definitions
//
DeliverDummyMCPPS* DeliverDummyMCPPS::m_instance = 0;

//
// constructors and destructor
//
DeliverDummyMCPPS::DeliverDummyMCPPS() :
   m_dummyPropStore( new MCParticlePropertyStore() )
{
   m_dummyPropStore->setVersion( 666 );

   // first build a dummy pi+ property and add it to the dummy store
   MCParticleProperty dummyProp(
      string ( "Joe" ), // name 
      QQ_id ( 3 ), // qqId 
      Stable_id ( 4 ), // stableId 
      PDG_id ( 5 ), // pdgId 
      Geant_id ( 6 ), // geantId 
      Double ( -2 ), // charge 
      Double ( 0.00008 ), // ctau 
      Double ( 0.9 ), // mass 
      Double ( 0.123 ), // width 
      Double ( 0.000 ), // minMass 
      Double ( 0.246 ), // maxMass 
      Double ( 0.5 ), // spin 
      Double ( 1 ), // parity 
      Double ( -1 ), // cParity 
      DABoolean ( false ) ); // mixable 
   m_dummyPropStore->addProperty( dummyProp );

   MCParticleProperty dummyPropToo(
      string ( "babyJoe" ), // name 
      QQ_id ( 4 ), // qqId 
      Stable_id ( 5 ), // stableId 
      PDG_id ( 6 ), // pdgId 
      Geant_id ( 7 ), // geantId 
      Double ( -1 ), // charge 
      Double ( 0.00008 ), // ctau 
      Double ( 0.4 ), // mass 
      Double ( 0.123 ), // width 
      Double ( 0.000 ), // minMass 
      Double ( 0.246 ), // maxMass 
      Double ( 0.5 ), // spin 
      Double ( 1 ), // parity 
      Double ( -1 ), // cParity 
      DABoolean ( false ) ); // mixable 
   m_dummyPropStore->addProperty( dummyPropToo );

   // rather than doing a "replace", get the particle from the
   // store and cast away the const'ness
   MCParticleProperty* joePointer = 
      &(m_dummyPropStore->getModifiableUsingName("Joe"));

   STL_VECTOR( QQ_id ) daughters;
   daughters.push_back( 4 );
   daughters.push_back( 4 );
   SimpleHelicity* noSH = 0;
   SimpleAngularHelicity* noSAH = 0;
   m_dummyDecayMode = new MCDecayMode( joePointer,
				       0.995, 
				       daughters, 
				       321, 
				       noSH,
				       noSAH );
   joePointer->addDecayMode( *m_dummyDecayMode );
}

// DeliverDummyMCPPS::DeliverDummyMCPPS( const DeliverDummyMCPPS& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

DeliverDummyMCPPS::~DeliverDummyMCPPS()
{}

//
// assignment operators
//
// const DeliverDummyMCPPS& DeliverDummyMCPPS::operator=( const DeliverDummyMCPPS& rhs )
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
MCParticlePropertyStore&
DeliverDummyMCPPS::dummyMCParticlePropertyStore() {
   return *m_dummyPropStore;
}

MCParticleProperty&
DeliverDummyMCPPS::dummyMCParticleProperty() {
   MCParticleProperty& dummyPropRef = m_dummyPropStore->getModifiableUsingName("Joe");
   return dummyPropRef;
}

MCDecayMode&
DeliverDummyMCPPS::dummyMCDecayMode() {
   return *m_dummyDecayMode;
}

//
// static member functions
//
DeliverDummyMCPPS&
DeliverDummyMCPPS::instance( void ) {
   // If there does not exist an object yet, create one on the heap
   if ( m_instance == 0 ) {
      m_instance = new DeliverDummyMCPPS();
   }
   
   return *m_instance;
}
