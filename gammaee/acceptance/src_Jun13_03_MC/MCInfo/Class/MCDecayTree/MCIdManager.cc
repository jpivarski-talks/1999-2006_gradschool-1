// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCIdManager
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar 20 15:18:03 EST 1999
// $Id: MCIdManager.cc,v 1.2 2002/02/05 03:25:36 lkg Exp $
//
// Revision history
//
// $Log: MCIdManager.cc,v $
// Revision 1.2  2002/02/05 03:25:36  lkg
// add vectors and access functions for constant-time particle or vertex look-up
//
// Revision 1.1  1999/06/22 21:28:49  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCDecayTree/MCIdManager.h"
#include "MCInfo/MCDecayTree/MCTreeNode.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCVertex.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCIdManager" ;
static const Count kStartingIdentifier = 1;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCIdManager.cc,v 1.2 2002/02/05 03:25:36 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCIdManager::MCIdManager( MCTreeNode* topNode ) :
   m_topNode( topNode ),
   m_lastVertexId( 0 ),
   m_lastParticleId( 0 ),
   m_copyLevel( 0 ),
   m_refCount( 0 ),
   m_particleList(),
   m_vertexList()
{
   m_particleList.reserve( 45 );
   m_vertexList.reserve( 45 );
   initializeIdMaps();
}

MCIdManager::MCIdManager( const MCIdManager& rhs )
{
   // do actual copying here; if you implemented
   // operator= correctly, you may be able to use just say      
   *this = rhs;
}

MCIdManager::~MCIdManager()
{
}

//
// assignment operators
//
const MCIdManager& MCIdManager::operator=( const MCIdManager& rhs )
{
  if( this != &rhs ) {
     // do actual copying here, plus:
     // "SuperClass"::operator=( rhs );
  }

  return *this;
}

//
// member functions
//
void
MCIdManager::copyStarting() {
   ++m_copyLevel;
}

void
MCIdManager::copyDone() {
   
   // make sure that we don't register more copy levels completing
   // than we had starting
   if ( 0 == m_copyLevel ) {
      report( ERROR, kFacilityString )
	 << "More copy levels in node than should have been possible" << endl;
      assert( false );
      exit( 1 );
   } 
   // otherwise, decrement the copy level, and reset ALL id's in the tree
   // if we've hit all the levels requested
   else if ( 0 == --m_copyLevel ) {

      assignIdentifiers();
   }
}

void
MCIdManager::initializeIdMaps() {
   // reset the id->pointer vectors.  We want to index the
   // vector with id's, which don't start at zero, so we will place a
   // dummy zero pointer into the zero'th position
   m_particleList.clear();
   m_vertexList.clear();
   MCParticle* dummyParticle( 0 );
   MCVertex* dummyVertex( 0 );
   for ( int i = 0; i != kStartingIdentifier; ++i ) {
      m_particleList.push_back( dummyParticle );
      m_vertexList.push_back( dummyVertex );
   }
}

void
MCIdManager::assignIdentifiers() {
   // reset the ID's that have been served so far
   m_lastParticleId = m_lastVertexId = 0;

   // reset the id->pointer mapping vectors   
   initializeIdMaps();
   
   // tell the top node to initiate update its ID's, and to have
   // it's children to update it's id's
   m_topNode->updateId();
   m_topNode->updateChildrenIds();
}

void
MCIdManager::resetId( MCParticle& aParticle ) {
   aParticle.setId( ++m_lastParticleId );
   m_particleList.push_back( &aParticle );
   
#if defined(LKG_DEBUG)
   // sanity check for debugging: get rid of this eventually
   if ( m_lastParticleId != m_particleList[m_lastParticleId]->id() ) {
   	report( EMERGENCY, kFacilityString )
   	   << "particle id disagrees with slot in id->pointer vector: "
   	   << "\n slot = " << m_lastParticleId 
   	   << " id = " << m_particleList[m_lastParticleId]->id()
   	   << endl;
   }
#endif
}

void
MCIdManager::resetId( MCVertex& aVertex ) {
   aVertex.setId( ++m_lastVertexId );
   m_vertexList.push_back( &aVertex );

#if defined(LKG_DEBUG)
   // sanity check for debugging: get rid of this eventually
   if ( m_lastVertexId != m_vertexList[m_lastVertexId]->id() ) {
   	report( EMERGENCY, kFacilityString )
   	   << "vertex id disagrees with slot in id->pointer vector: "
   	   << "\n slot = " << m_lastVertexId 
   	   << " id = " << m_vertexList[m_lastVertexId]->id()
   	   << endl;
   }
#endif
}

void
MCIdManager::addReference() {
   ++m_refCount;
}

void
MCIdManager::removeReference() {

   // we should have at least 1 reference remaining if we are being
   // asked to remove a reference
   assert( m_refCount > 0 );

   --m_refCount;
}

//
// const member functions
//
DABoolean 
MCIdManager::hasRefs() const {
   return ( 0 != m_refCount );
}

//
// static member functions
Count
MCIdManager::startingIdentifier() {
   return kStartingIdentifier;
}

