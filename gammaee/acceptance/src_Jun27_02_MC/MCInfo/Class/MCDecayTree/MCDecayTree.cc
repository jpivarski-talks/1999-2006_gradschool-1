// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCDecayTree
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Sat Jan  9 13:32:32 EST 1999
// $Id: MCDecayTree.cc,v 1.9 2002/05/03 19:44:35 lkg Exp $
//
// Revision history
//
// $Log: MCDecayTree.cc,v $
// Revision 1.9  2002/05/03 19:44:35  lkg
// convert strings -> QQIDs before launching on searches
//
// Revision 1.8  2002/02/05 03:23:06  lkg
// use new constant-time MCParticle, MCVertex lookup via MCIdManager
//
// Revision 1.7  2002/01/20 19:06:49  lkg
// getParticle called by getParticle, rather than vice-versa; throw exception if reference nonexistant particle; same for vertex
//
// Revision 1.6  2001/12/19 18:11:04  lkg
// add particle/vertex lookup that returns an iterator (already used internally)
//
// Revision 1.5  2000/07/19 15:49:32  lkg
// * add test/search functions to find vertex w/ a particular parent
// * add search functions (MCDecayTree) that allow user to specify a
//   starting vertex iterator (reimplement original search fcn's to call
//   new fcn's with start specified by vBegin())
//
// Revision 1.4  2000/05/01 22:44:15  lkg
// Added == and != operators, needed for StorageHelpers
//
// Revision 1.3  1999/10/19 21:42:26  lkg
// * Don't use enum type "iterator" as a fcn return type, use Count instead.  Get
//   conversion problems for users with "iterator"
// * add non-const versions of getParticle[Ptr] and getVertex[Ptr] fcn's
// * change copy constructor to do a DEEP COPY -- the particles/vertices get
// * copied made, not just a copy of the ptr to the top particle
//
// Revision 1.2  1999/07/07 13:08:22  lkg
// Add an iterator over the "stable" particles in the decay tree:
// MCDecayTree::const_sIterator typedef'd to MCStablePartItr
//
// Revision 1.1  1999/06/22 21:28:48  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
//#include <iostream.h>

// user include files
#include "Experiment/report.h"
#include "Experiment/units.h"
#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCNoParticleExistsException.h"
#include "MCInfo/MCDecayTree/MCNoVertexExistsException.h"
#include "MCInfo/MCDecayTree/MCIdManager.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCDecayTree" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCDecayTree.cc,v 1.9 2002/05/03 19:44:35 lkg Exp $";
static const char* const kTagString = "$Name: v03_02_02 $";

static const MCParticle* kNullPartPtr( 0 );
static const STL_VECTOR( MCParticle* )::size_type kTopSize( 1 );
//
// static data member definitions
//

// c*tau cutoff between "stable" and "nonstable" is 1 cm
const Meters MCDecayTree::kStableCTauCutoff( 0.01*k_m );

//
// constructors and destructor
//
MCDecayTree::MCDecayTree(DABoolean ownTree) : 
   m_topParticle( 0 ),
   m_topParticleV( *new STL_VECTOR( MCParticle* )(kTopSize) ),
   m_manageTreeMemory( ownTree ) { m_topParticleV[0] = 0; }

MCDecayTree::MCDecayTree( MCParticle* topParticle, DABoolean ownTree ) :
   m_topParticle( topParticle ),
   m_topParticleV( *new STL_VECTOR( MCParticle* )(kTopSize,topParticle) ),
   m_manageTreeMemory( ownTree ) {}

MCDecayTree::MCDecayTree( const MCParticle* topParticle ) :
   m_topParticle( const_cast<MCParticle*>(topParticle ) ),
   m_topParticleV( *new STL_VECTOR( MCParticle* )(kTopSize) ),
   m_manageTreeMemory( false ) {
      m_topParticleV[0] = m_topParticle;
}

MCDecayTree::MCDecayTree( const MCDecayTree& rhs ) :

   m_topParticle( rhs.m_topParticle->clone() ),
   m_topParticleV( *new STL_VECTOR( MCParticle* )(kTopSize) ),
   m_manageTreeMemory( true ) {
      m_topParticleV[0] = m_topParticle;
}

MCDecayTree::~MCDecayTree() {
   if ( m_manageTreeMemory ) { delete m_topParticle; }
   delete &m_topParticleV;
}


//
// assignment operators
//
// const MCDecayTree& MCDecayTree::operator=( const MCDecayTree& rhs )
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

void
MCDecayTree::setParent( MCParticle* topParticle, DABoolean ownTree ) {


   m_topParticle = topParticle;
   m_topParticleV[0] = topParticle;
   m_manageTreeMemory = ownTree;
}


//
// const member functions
//

// -- begin/end functions for iteration
MCDecayTree::const_pIterator 
MCDecayTree::pBegin() const {
   if ( m_topParticleV[0] == 0 ) { return pEnd(); }

   MCVertex::const_iterator tmpVBegin( m_topParticleV.begin() );
   MCVertex::const_iterator tmpVEnd(   m_topParticleV.end() );
 
   MCDecayTree::const_pIterator theStart( tmpVBegin, tmpVEnd );
   return theStart;
}

MCDecayTree::const_pIterator 
MCDecayTree::pEnd() const {
   return const_pIterator::endIterator();
}

MCDecayTree::const_sIterator 
MCDecayTree::sBegin() const {
   MCDecayTree::const_sIterator theStart( pBegin() );
   return theStart;
}

MCDecayTree::const_sIterator 
MCDecayTree::sEnd() const {
   return const_sIterator::endIterator();
}

MCDecayTree::const_vIterator 
MCDecayTree::vBegin() const {
   if ( m_topParticleV[0] == 0 ) { return vEnd(); }

   const MCParticle& theTopPart( *(m_topParticleV[0]) );
   MCDecayTree::const_vIterator 
      theStart( theTopPart.vBegin(), theTopPart.vEnd() );
   return theStart;
}

MCDecayTree::const_vIterator 
MCDecayTree::vEnd() const {
   return  const_vIterator::endIterator();
}

// -- subTree functions
const MCDecayTree 
MCDecayTree::subTree( const_pIterator aPartItr  ) const {
   return subTree( *aPartItr );
}

const MCDecayTree 
MCDecayTree::subTree( const MCParticle& aPart ) const {
   MCDecayTree tmpTree( &aPart );
   return tmpTree;
}

const MCDecayTree 
MCDecayTree::subTree( const_vIterator aVtxItr  ) const {
   return subTree( aVtxItr->parent() );
}

const MCDecayTree 
MCDecayTree::subTree( const MCVertex& aVtx     ) const {
   return subTree( aVtx.parent() );
}

MCDecayTree::const_pIterator
MCDecayTree::pFind( Count treeId ) const {

   // start from particlePtr, for which we have constant-time access
   const MCParticle* pPart = getParticlePtr( treeId );
   if ( pPart == 0 ) {return pEnd();}
   if ( pPart == m_topParticle ) {return pBegin();}
   
   // if we make it here, the particle should be in the middle of the
   // tree. Still need to do a bit of work to transform the pointer into 
   // an MCDecayTree iterator
   const MCVertex* productionVertex = pPart->productionVertex();
   const_pIterator itPart( productionVertex->pBegin(), productionVertex->pEnd() );
   for ( ; itPart->id() != treeId ; ++itPart ) {}
   
   return itPart;
}

const MCParticle& 
MCDecayTree::getParticle( Count treeId ) const {

   const MCParticle* pPart = getParticlePtr( treeId );
   if ( pPart == 0 ) {
   	throw MCNoParticleExistsException( treeId );
   }
   return *pPart;
}

const MCParticle*
MCDecayTree::getParticlePtr( Count treeId ) const {
   
   const MCParticle* pPart( 0 );
   if ( m_topParticle != 0 ) {
      // direct access via MCIdManager
      const MCParticle& constTop = *m_topParticle;
      const MCIdManager& idManager = constTop.manager();
      pPart = idManager.getParticle( treeId );
   }
   return pPart;
}

MCDecayTree::const_vIterator
MCDecayTree::vFind( Count treeId ) const {

   // start from vertexPtr, for which we have constant-time access
   const MCVertex* pVertex = getVertexPtr( treeId );
   if ( pVertex == 0 ) {return vEnd();}
   
   // if we made it here, the vertex is in the tree (and has a parent).
   // Still need to do a bit of work to transform the pointer into 
   // an MCDecayTree iterator
   const MCParticle& parent = pVertex->parent();
   const_vIterator itVert( parent.vBegin(), parent.vEnd() );
   for ( ; itVert->id() != treeId ; ++itVert ) {}
   
   return itVert;
}

const MCVertex& 
MCDecayTree::getVertex( Count treeId ) const {
   const MCVertex* pVert = getVertexPtr( treeId );
   if ( pVert == 0 ) {
   	throw MCNoVertexExistsException( treeId );
   }
   return *pVert;
}

const MCVertex*
MCDecayTree::getVertexPtr( Count treeId ) const {

   const MCVertex* pVertex( 0 );
   if ( m_topParticle != 0 ) {
      // direct access via MCIdManager
      const MCParticle& constTop = *m_topParticle;
      const MCIdManager& idManager = constTop.manager();
      pVertex = idManager.getVertex( treeId );
   }
   return pVertex;
}


// non-const versions of the last four functions
MCParticle& 
MCDecayTree::getParticle( Count treeId ) {

   const MCDecayTree* treeCopy = this;
   return const_cast<MCParticle&>( treeCopy->getParticle( treeId ) );
}

MCParticle*
MCDecayTree::getParticlePtr( Count treeId ) {

   return &getParticle( treeId );
}

MCVertex& 
MCDecayTree::getVertex( Count treeId ) {

   const MCDecayTree* treeCopy = this;
   return const_cast<MCVertex&>( treeCopy->getVertex( treeId ) );
}

MCVertex*
MCDecayTree::getVertexPtr( Count treeId ) {

   return &getVertex( treeId );
}

//----------------------------------------------------------------------
MCDecayTree::const_vIterator
MCDecayTree::findVertex( const STL_VECTOR( string )& daughters,
			 const string parent,
			 DABoolean alsoFindConjugate,
			 Count type ) const {
   return findVertex( vBegin(), daughters, parent, alsoFindConjugate, type );
}


MCDecayTree::const_vIterator
MCDecayTree::findVertex( const_vIterator startSearch,
			 const STL_VECTOR( string )& daughters,
			 const string parent,
			 DABoolean alsoFindConjugate,
			 Count type ) const {

   // convert to qq id for efficiency
   const MCParticlePropertyStore& store = m_topParticle->properties().store();
   QQ_id parentId   = store.nameToQQId( parent );
   STL_VECTOR( QQ_id ) idList( daughters.size() );
   STL_VECTOR( QQ_id )::iterator iId = idList.begin() ;
   for ( STL_VECTOR( string )::const_iterator iName = daughters.begin();
	 iId != idList.end() ; ++iId, ++iName ) {
      *iId = store.nameToQQId( *iName );
   }

   const_vIterator done( vEnd() );
   const_vIterator itV;
   for ( itV = startSearch;
	 itV != done && ! itV->isType(idList,parentId,alsoFindConjugate,type);
	 ++itV ) {}

   return itV;
}

MCDecayTree::const_vIterator
MCDecayTree::findVertex( const STL_VECTOR(QQ_id )& daughters,
			 QQ_id parent,
			 DABoolean alsoFindConjugate,
			 Count type ) const {
   return findVertex( vBegin(), daughters, parent, alsoFindConjugate, type );
}

MCDecayTree::const_vIterator
MCDecayTree::findVertex( const_vIterator startSearch,
			 const STL_VECTOR(QQ_id )& daughters,
			 QQ_id parent,
			 DABoolean alsoFindConjugate,
			 Count type ) const {
   const_vIterator done( vEnd() );
   const_vIterator itV;
   for ( itV = startSearch;
	 itV != done && ! itV->isType(daughters,parent,alsoFindConjugate,type);
	 ++itV ) {}

   return itV;
}

//----------------------------------------------------------------------
MCDecayTree::const_vIterator
MCDecayTree::findVertexWith( const string& daughter,
			     const string parent,
			     DABoolean alsoFindConjugate,
			     Count type ) const {
   return findVertexWith( vBegin(), daughter, parent, alsoFindConjugate, type);
}

MCDecayTree::const_vIterator
MCDecayTree::findVertexWith( const_vIterator startSearch,
			     const string& daughter,
			     const string parent,
			     DABoolean alsoFindConjugate,
			     Count type ) const {

   // convert to qq id for efficiency
   const MCParticlePropertyStore& store = m_topParticle->properties().store();
   QQ_id parentId   = store.nameToQQId( parent );
   QQ_id daughterId = store.nameToQQId( daughter );

   const_vIterator done( vEnd() );
   const_vIterator itV;
   for (itV = startSearch;
	itV != done && ! itV->isTypeWith(daughterId,parentId,alsoFindConjugate,type);
	++itV ) {}

   return itV;
}

MCDecayTree::const_vIterator
MCDecayTree::findVertexWith( QQ_id daughter,
			     QQ_id parent,
			     DABoolean alsoFindConjugate,
			     Count type ) const {
   return findVertexWith( vBegin(), daughter, parent, alsoFindConjugate, type);
}

MCDecayTree::const_vIterator
MCDecayTree::findVertexWith( const_vIterator startSearch,
			     QQ_id daughter,
			     QQ_id parent,
			     DABoolean alsoFindConjugate,
			     Count type ) const {
   const_vIterator done( vEnd() );
   const_vIterator itV;
   for (itV = startSearch;
	itV != done && ! itV->isTypeWith(daughter,parent,alsoFindConjugate,type);
	++itV ) {}

   return itV;
}

//----------------------------------------------------------------------
MCDecayTree::const_vIterator
MCDecayTree::findVertexWithParent( const string  parent,
				   DABoolean alsoFindConjugate,
				   Count type ) const {
  return findVertexWithParent( vBegin(), parent, alsoFindConjugate, type );
}

MCDecayTree::const_vIterator
MCDecayTree::findVertexWithParent( const_vIterator startingVertex,
				   const string  parent,
				   DABoolean alsoFindConjugate,
				   Count type ) const {

   // convert to qq id for efficiency
   const MCParticlePropertyStore& store = m_topParticle->properties().store();
   QQ_id parentId   = store.nameToQQId( parent );

   const_vIterator done( vEnd() );
   const_vIterator itV;
   for (itV = startingVertex;
	itV != done && ! itV->isTypeWithParent(parentId,alsoFindConjugate,type);
	++itV ) {}

   return itV;
}

// b) using QQ_id to specify parent
MCDecayTree::const_vIterator 
MCDecayTree::findVertexWithParent( QQ_id parent,
				   DABoolean alsoFindConjugate,
				   Count type ) const {
  return findVertexWithParent( vBegin(), parent, alsoFindConjugate, type );
}

MCDecayTree::const_vIterator 
MCDecayTree::findVertexWithParent( const_vIterator startingVertex,
				   QQ_id parent,
				   DABoolean alsoFindConjugate,
				   Count type ) const {
   const_vIterator done( vEnd() );
   const_vIterator itV;
   for (itV = startingVertex;
	itV != done && ! itV->isTypeWithParent(parent,alsoFindConjugate,type);
	++itV ) {}

   return itV;
}

//----------------------------------------------------------------------

DABoolean
MCDecayTree::operator==( const MCDecayTree& rhs ) const {
   return *m_topParticle == *(rhs.m_topParticle);
}

DABoolean
MCDecayTree::operator!=( const MCDecayTree& rhs ) const {
  return !( *this == rhs );
}

//
// friend member functions
//
ostream& operator<<( ostream& s, const MCDecayTree& aTree ) {

   // list all of the particles
   s << "Particles: " << MCParticle::dumpHeader;
   MCDecayTree::const_pIterator pDone = aTree.pEnd();
   for ( MCDecayTree::const_pIterator iPart = aTree.pBegin();
	 iPart != pDone; ++iPart ) {
      s << *iPart << '\n';
   }

   // list all of the vertices
   s << '\n' << '\n' << "Vertices: " << MCVertex::dumpHeader;
   MCDecayTree::const_vIterator vDone = aTree.vEnd();
   for ( MCDecayTree::const_vIterator iVert = aTree.vBegin();
	 iVert != vDone; ++iVert ) {
      s << *iVert << '\n';
   }

   return s;
}
