// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCVertex
// 
// Description: Holds the properties associated with an interaction or
//              decay vertex: parent, position, time, etc.,  Acts as
//              a container holding the children particles produced.
//
// Implementation:
//   We only add children particles as complete sets.  That way, we can
//   reliably check that conservation laws are observed in a decay.
//
//     Required routines for creating new Vertex classes that inherit 
//     from MCVertex.  See notes for corresponding routines in MCVertex
//       a) copy constructor of form
//         MyVertex( const MyVertex& rhs, MCParticle* parentPart = 0 )
//       b) clone function of form
//         MyVertex* clone( MCParticle* newProdVertex = 0 )
//       c) dump function for use with the MCVertex << friend operator
//         ostream* dump( ostream& ) const;
//
// Author:      Lawrence Gibbons
// Created:     Sun Jan 10 14:57:27 EST 1999
// $Id: MCVertex.cc,v 1.19 2003/05/19 20:23:13 lkg Exp $
//
// Revision history
//
// $Log: MCVertex.cc,v $
// Revision 1.19  2003/05/19 20:23:13  lkg
// in dump utilities, use formattable version of vector or point
//
// Revision 1.18  2003/01/29 19:15:30  cdj
// get iomanip header from C++Std package
//
// Revision 1.17  2002/05/03 19:45:28  lkg
// add routine to translate the coordinate system
//
// Revision 1.16  2002/01/20 20:13:57  lkg
// bug fix for decay mode consistency check
//
// Revision 1.15  2002/01/20 19:08:14  lkg
// improve implementation dealing w/ checks of expected vs actual children
//
// Revision 1.14  2001/12/19 18:11:19  lkg
// add support for radiative decays: look for one extra photon in decay
//
// Revision 1.13  2001/10/22 19:09:29  lkg
// loosen default E&p conservation tolerance
//
// Revision 1.12  2001/09/10 20:03:16  cleo3
// replaced use of list with an array (more efficient and compiles under Solaris8)
//
// Revision 1.11  2001/03/20 16:46:21  pappas
// Patch to deal with fix to CLHEP; HepLorentzVector constructor changed.
//
// Revision 1.10  2001/02/14 02:35:43  lkg
// Don't set the list of expected daughters if the decay mode is
// an "unknown" mode.
//
// Revision 1.9  2000/07/19 15:49:32  lkg
// * add test/search functions to find vertex w/ a particular parent
// * add search functions (MCDecayTree) that allow user to specify a
//   starting vertex iterator (reimplement original search fcn's to call
//   new fcn's with start specified by vBegin())
//
// Revision 1.8  2000/05/01 22:50:42  lkg
// StorageHelper-related changes: added valueType arg for MCListItr typedefs and == and != operators
//
// Revision 1.7  2000/03/29 02:43:08  lkg
// Comment out (better!) versions of operator << for CLHEP vector and 4-vector
// classes.  Caused conflict when users tried to link w/ CLHEP
//
// Revision 1.6  2000/01/26 16:48:56  lkg
// Add kiRadiativePairProduction to the nonfatal interaction lsit
//
// Revision 1.5  1999/11/02 23:35:53  lkg
// bug fix in isType mem. fcn. for conjugate modes. Missed a sort
//
// Revision 1.4  1999/10/30 22:29:09  lkg
// When adding particles to a decay vertex, allow the model to have mixed
// any particles that can mix, even though there is not an explicit decay
// mode for that process
//
// Revision 1.3  1999/10/19 21:54:21  lkg
// * replace return and argument types using the enum "interaction" to use
//   Count
// * add a member fcn that allows a single child to be added at a time
// * add a dumpHeader() member fcn that prints a header for the info output
//   by the MCVertex <<() operator
// * pretty up the output of the <<() operator
//
// Revision 1.2  1999/07/07 00:04:41  lkg
// Add reverse_iterator and const_reverse_iterator with associated rbegin/rend
// member functions.  Delete typedefs for "long names" like vertexIterator or
// particleIterator -- just got to be too much.
//
// Revision 1.1  1999/06/22 21:28:50  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>
#include "C++Std/iomanip.h"

#include <vector>
#include "STLUtility/fwd_vector.h"

// user include files
#include "Experiment/report.h"
#include "Experiment/units.h"
#include "MCInfo/MCParticleProperty/MCDecayMode.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCDecayTree/MCVertex.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCIdManager.h"
#include "MCInfo/MCDecayTree/MCIdMngrPtr.h"
#include "MCInfo/Utility/quoteDecay.h"
#include "MCInfo/Utility/quoteChildren.h"
#include "MCInfo/Utility/FormatablePoint3D.h"

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

static const char* const kFacilityString = "MCInfo.MCVertex" ;
// use the tighter tolerances when decay models are fixed
// GeV MCVertex::kEnergyConservationTolerance = 3e-5;
GeV MCVertex::kEnergyConservationTolerance = 135.*k_MeV;

static const int kPhotonQQId = 1;
static const string kPhotonName( "GAMM" );

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCVertex.cc,v 1.19 2003/05/19 20:23:13 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCVertex::MCVertex( Count interactionType,
		    MCParticle* theParent,
		    HepPoint3D thePosition, 
		    Double theTime,
		    HepLorentzVector currentParentMomentum ) :
   MCTreeNode(),
   m_interactionType( interactionType ),
   m_pParentParticle( theParent ),
   m_vertexPosition( thePosition ),
   m_time( theTime ),
   m_parentMomentumAtVertex( currentParentMomentum ),
   m_particleList(),
   m_childIdList( *new STL_VECTOR( QQ_id ) ),
   m_childNameList( *new STL_VECTOR( string ) ),
   m_pDecayMode( 0 )
{
   // attach this vertex to the parent and its tree
   m_pParentParticle->addVertex( this );
}

// the copy constructor does a deep copy.  Classes that inherit from
// this class must provide a copy constructor with these arguments,
// but this MCVertex base class will manage the deep copy aspects
MCVertex::MCVertex( const MCVertex& rhsVertex, MCParticle* parentPart ) :
   MCTreeNode( parentPart ), 
   m_interactionType( rhsVertex.m_interactionType ),
   m_pParentParticle( 0 ),
   m_vertexPosition( rhsVertex.m_vertexPosition ),
   m_time( rhsVertex.m_time ),
   m_parentMomentumAtVertex( rhsVertex.m_parentMomentumAtVertex ),
   m_particleList(),
   m_childIdList( *new STL_VECTOR( QQ_id ) ),
   m_childNameList( *new STL_VECTOR( string ) ),
   m_pDecayMode( rhsVertex.m_pDecayMode )
{
   setParentParticle( parentPart );
   //
   // Each vertex owns the vertices in its list of vertices, so we
   // must replicate each vertex here.
   //

   // inform the ID manager that we are about to begin the cloning descent
   // down the tree below this particle => delay ID resetting
   manager().copyStarting();

   // create the copies of the children
   copyAndSetChildren( rhsVertex.m_particleList );

   // inform the ID manager that we have finished the cloning of this vertex
   // If this is the top of the clone, the id's will get reset by the
   // manager
   manager().copyDone();
}

MCVertex::~MCVertex() {

   delete &m_childIdList;
   delete &m_childNameList;

   // delete all of the particles owned by this vertex
   typedef pList::iterator directItr;
   directItr done = m_particleList.end();
   for (directItr itPart = m_particleList.begin(); itPart != done; ++itPart) {
      delete *itPart;
   }
}

//
// member functions
//
MCVertex::pIterator
MCVertex::pBegin() {
   pIterator theBeginning( m_particleList.begin() );
   return theBeginning;
}

MCVertex::pIterator
MCVertex::pEnd() {
   pIterator theEnd( m_particleList.end() );
   return theEnd;
}

MCVertex::reverse_pIterator
MCVertex::rpBegin() {
   reverse_pIterator theBeginning( m_particleList.rbegin() );
   return theBeginning;
}

MCVertex::reverse_pIterator
MCVertex::rpEnd() {
   reverse_pIterator theEnd( m_particleList.rend() );
   return theEnd;
}

void
MCVertex::setParentParticle( MCParticle* theParent ) {

   // store the pointer to the parent
   m_pParentParticle = theParent;

   // update the manager to be the parent particle's manager
   updateManager( theParent->manager() );
}

void
MCVertex::setDecayMode( const MCDecayMode& theDecayMode, DABoolean isRadiativeDecay ) {
   
   // set the member item
   m_pDecayMode = &theDecayMode;

   // clear out the list of daughter Id's.  We will set it to
   // the daughters ID's for this decay mode if this mode ALWAYS
   // returns the same set of daughters (ie, the list of daugthers
   // is deterministic)
   m_childIdList.clear();
   m_childNameList.clear();

   // if we can, get the list of daughters from the decay mode
   if ( theDecayMode.deterministic() && 
	theDecayMode.identifier() != MCDecayMode::kUnknownMode ) {
      for ( Count i = 0; i != theDecayMode.numberChildren(); ++i ) {
	 m_childIdList.push_back( theDecayMode.childType(i) );
	 m_childNameList.push_back( theDecayMode.childName(i) );
      }
      if ( isRadiativeDecay ) {
         m_childIdList.push_back( kPhotonQQId ); // assumes photon QQId remains at 1
         m_childNameList.push_back( kPhotonName ); // assumes photon QQ name remains GAMM
         setRadiativeDecay();
      }
   }

   // sort the id list for easier comparison later on
   sort( m_childIdList.begin(), m_childIdList.end() );
}

void
MCVertex::updateManager( MCIdManager& theManager ) {

   // don't do anything if we are already using this manager
   if ( &theManager != &(manager()) ) {
      // make sure we are in the correct Tree
      setManager( theManager );

//      // propagate the new information down to the daughter particles
//      // by invoking updateManager( theManager ) for each particle
//      for_each( pBegin(), pEnd(), 
//		   bind2nd(mem_fun_ref(&updateManager),theManager) );
// non-STL version of above
      pIterator done = pEnd();
      for ( pIterator itPart = pBegin(); itPart != done; ++itPart ) {
	 itPart->updateManager( theManager );
      }
   }
}

void
MCVertex::updateId() {
   manager().resetId( *this );
}

void
MCVertex::updateChildrenIds() {

   // need to do 2 iterations over daughter list, store begin/end
   pIterator done  = pEnd();
   pIterator start = pBegin();

   // At initial writing, Solaris gets scope of itPart wrong.
   // Define it here for now.  Do it right later if Solaris gets
   // fixed
   pIterator itPart;

   // first, reset the particle id's so that they are in order
   for ( itPart = start; itPart != done;  ++itPart )  {
      itPart->updateId();
   }

   // next, tell each particle to propagate the information
   for ( itPart = start; itPart != done;  ++itPart )  {
      itPart->updateChildrenIds();
   }
}

DABoolean
MCVertex::copyAndSetChildren( const pList& newChildren ) {

   // inform the manager that we are about to modify this tree
   manager().additionStarting();

   // delete any former children
   clearChildren();

   // copy the children via clone.  The form of clone used will 
   // automatically take care of setting the production vertex
   const_pIterator done = newChildren.end();
   for(const_pIterator itPart = newChildren.begin(); itPart != done; ++itPart){
      m_particleList.push_back( itPart->clone(this) );
   }

   // inform the manager that we are done our modifications, so it
   // can renumber the ids
   manager().additionDone();

   // check that the interaction conserves charge, energy and momentum
   // (if it is expected to conserve them)
   if ( MCVertex::conservingInteraction( m_interactionType ) ) {
      if ( ! checkConservedQuantities() ) {
         assert( false );
         ::exit(1);
      }
   }

   // update the local list of Child types
   updateTypeList();

   return true;
}

DABoolean
MCVertex::setChildren( const pList& newChildren ) {

   typedef pList::const_iterator directItr;

   // if there was a decay at this vertex, make sure that we
   // have the decay mode information
   if ( m_interactionType == kiDecay && m_pDecayMode == 0 ) {
      m_childIdList.clear();
      m_childNameList.clear();
      directItr done = newChildren.end();
      for (directItr itChild = newChildren.begin(); 
	   itChild != done; ++itChild) {
	 m_childIdList.push_back( (*itChild)->properties().QQId() );
	 m_childNameList.push_back( (*itChild)->properties().name() );
      }
      const MCParticleProperty& parentProps( m_pParentParticle->properties() );
      MCParticleProperty::const_iterator thisDecayMode = 
	   parentProps.findDecayMode( m_childIdList );

      // a potential for a failed search is a radiative decay, which will
      // add an extra photon to the list of daughters (relative to those in the
      // listed in the decay mode)
      if ( thisDecayMode == parentProps.end() ) {
         STL_VECTOR( QQ_id )::iterator gammaPosition = 
            find_if( m_childIdList.begin(), m_childIdList.end(),
                     bind2nd(equal_to<QQ_id>(), kPhotonQQId));
         // found a photon, so check if we can find a decay mode with one
         // fewer photons
         if ( gammaPosition !=  m_childIdList.end() ) {
            // create a new list with the photon removed
            STL_VECTOR( QQ_id ) testList;
            STL_VECTOR( QQ_id )::iterator newStart =
               copy( m_childIdList.begin(), gammaPosition, testList.begin() );
            copy( ++gammaPosition, m_childIdList.end(), newStart );
            // try to look up the new decay mode
            thisDecayMode = parentProps.findDecayMode( testList );
            // if successful, flag this as a radiative decay
            if ( thisDecayMode != parentProps.end() ) {
            	m_radiativeDecay = true;
            }
         }
      }
      // if the daughters still aren't found, it's probably because QQ's
      // awful handling of information in the presence of mixing
      if ( thisDecayMode == parentProps.end() ) {
	 const MCParticlePropertyStore& store = parentProps.store();
	 typedef STL_VECTOR( QQ_id )::iterator tIter;
	 int done = m_childIdList.size();
	 for ( int qIt = 0; 
	       (thisDecayMode == parentProps.end()) && (qIt != done); 
	       ++qIt ) {
	    // get the property of the next daughter and check if it mixes
	    const MCParticleProperty& thisProp = store[m_childIdList[qIt]];
	    if ( thisProp.mixable() ) {
	       // create a new temporary list with the particle replaced
	       // by the conjugate to which it mixes
	       STL_VECTOR( QQ_id ) tl2( m_childIdList );
	       tl2[qIt] = store.conjugateQQ( tl2[qIt] );
	       thisDecayMode = parentProps.findDecayMode( tl2 );
	    }
	 }
      }
      if ( thisDecayMode == parentProps.end() ) {
	 report( WARNING, kFacilityString )
	    << "Could not find decay mode in parent particle property" << '\n'
	    << " ## that corresponds to " << '\n' << " ## "
	    << quoteDecay( m_pParentParticle->properties().name(), m_childNameList )
	    << endl;
      } else {
	 setDecayMode( *thisDecayMode );
      }
   }

   // inform the manager that we are about to modify this tree
   manager().additionStarting();

   // delete any former children.
   clearChildren();

   // store the pointers to the children, informing the children about
   // their productionVertex
   directItr done = newChildren.end();
   for (directItr itChild = newChildren.begin(); itChild != done; ++itChild) {

      // tell the child to which decay chain it belongs
      (*itChild)->setProductionVertex( this );
      
      // push the child onto the list of children
      m_particleList.push_back( *itChild );
   }
    
   // check that the interaction conserves charge, energy and momentum
   // if it is expected to
   if ( MCVertex::conservingInteraction( m_interactionType ) ) {
      if ( ! checkConservedQuantities() ) {
         assert( false );
         ::exit(1);
      }
   }

   // inform the manager that we are done our modifications, so it
   // can renumber the ids
   manager().additionDone();

   // update the local list of Child types
   updateTypeList();

   return true;
}

DABoolean
MCVertex::addChild( MCParticle* newParticle )
{
   // check that the interaction conserves charge, energy and momentum
   // if it is expected to
   if ( MCVertex::conservingInteraction( m_interactionType ) ) {
      report( DEBUG, kFacilityString )
	 << "Adding children singly for a conserving interaction NOT"
	 << "recommended" << endl
	 << "Charge/momentum/energy conservation will NOT be verified"
	 << endl;
   }

   // inform the manager that we are about to modify this tree
   manager().additionStarting();

   // tell the child to which decay chain it belongs
   newParticle->setProductionVertex( this );
   
   // push the child onto the list of children
   m_particleList.push_back( newParticle );


   // inform the manager that we are done our modifications, so it
   // can renumber the ids
   manager().additionDone();

   // update the local list of Child types
   updateTypeList();
   
   return true;   
}

void
MCVertex::clearChildren() {

   if ( ! m_particleList.empty() ) {
      typedef pList::iterator directItr;
      directItr done( m_particleList.end() );
      for (directItr itPart(m_particleList.begin()); itPart != done; ++itPart){
	 delete *itPart;
      }
      m_particleList.clear();
   }
}   

void
MCVertex::updateTypeList() {
   m_childIdList.clear();
   m_childNameList.clear();
   const MCVertex& stillThis( *this );
   const_pIterator done = stillThis.pEnd();
   for ( const_pIterator itChild = stillThis.pBegin(); 
	 itChild != done; ++itChild ) {
      m_childIdList.push_back( itChild->properties().QQId() );
      m_childNameList.push_back( itChild->properties().name() );
   }
   // sort the list for use later on
   sort( m_childIdList.begin(), m_childIdList.end() );
}

MCVertex::pList&
MCVertex::fillChildrenTemplate( MCVertex::pList& blankLst,
				const STL_VECTOR(QQ_id)& pTypes ) {

   // make sure that we are starting with a blank slate
   blankLst.clear();

   // get access to the particle property store of the parent, so
   // that we can get the property objects of the children
   const MCParticlePropertyStore& store = 
      m_pParentParticle->properties().store();

   Count done = pTypes.size();
   for( Count iPart = 0; iPart != done; ++iPart ) {
      const MCParticleProperty& childProp = store[pTypes[iPart]];
      HepLorentzVector child4Mom( 0, 0, 0, childProp.mass() );
      blankLst.push_back(new MCParticle(childProp, child4Mom, position()));
      MCParticle* chkPart = blankLst.back();
   }

   return blankLst;
}

MCVertex::pList& MCVertex::fillChildrenTemplate( pList& blankLst ) {
   // implement using more general version, passing child list
   fillChildrenTemplate( blankLst, m_childIdList );
   return blankLst;
}

void
MCVertex::setPosition( const HepPoint3D& thePosition ) {
   m_vertexPosition = thePosition;
}

void
MCVertex::setTime( Double theTime ) {
   m_time = theTime;
}

void
MCVertex::setLocalParentMomentum( const HepLorentzVector& theParentMomentum ) {
   m_parentMomentumAtVertex = theParentMomentum;
}

void
MCVertex::setRadiativeDecay() {
   m_radiativeDecay = true;
}

void 
MCVertex::translateCoordinates( const Hep3Vector& translationVector ) {
   HepPoint3D newPosition = position() + translationVector;
   setPosition( newPosition );
   pIterator endPosition = end();
   for ( pIterator particle = begin(); particle != endPosition; ++particle ) {
   	particle->translateCoordinates( translationVector );
   }
}

//
// const member functions --------------------------------------
//

DABoolean
MCVertex::checkDecayModeConsistency() const {
   if ( m_pDecayMode == 0 ) {
   	return false;
   }
   // pass check if hadronization results in non-specific final state (*qq* stuff)
   if ( ! m_pDecayMode->deterministic() ) {
   	return true;
   }
   STL_VECTOR( QQ_id ) childrenExpected( m_pDecayMode->childrenTypes() );
   if ( m_radiativeDecay ) {
   	childrenExpected.push_back( kPhotonQQId );
   }
   sort( childrenExpected.begin(), childrenExpected.end() );
   return childrenExpected == m_childIdList;
}


DABoolean
MCVertex::checkConservedQuantities() const {
//
   
   HepLorentzVector totalChildMomentum( 0.0, 0.0, 0.0, 0.0 );
   ElectronCharge  totalChildCharge = 0;
   const_pIterator endList = pEnd();
   for (const_pIterator itChild = m_particleList.begin(); 
	itChild != endList; ++itChild) {
      totalChildMomentum += itChild->lorentzMomentum();
      totalChildCharge   += itChild->properties().charge();
   }

   // check charge conservation
   if ( totalChildCharge != m_pParentParticle->properties().charge() ) {
      report( ERROR, kFacilityString )
	 << "charge nonconservation in " 
	 << quoteDecay(m_pParentParticle->properties().name(),m_childNameList);
      return false;
   }

   // check E and p conservation
   const HepLorentzVector& parentMom = m_pParentParticle->lorentzMomentum();
   Double eDiff = abs(totalChildMomentum.e()   - parentMom.e());
   Double pDiff = abs(totalChildMomentum.rho() - parentMom.rho());
      
   if ( eDiff > kEnergyConservationTolerance || 
	pDiff > kEnergyConservationTolerance ) {
      report( WARNING, kFacilityString )
	 << "E/p momentum conservation out of Tolerance for" 
	 << '\n' << " ## "
	 << quoteDecay(m_pParentParticle->properties().name(),m_childNameList)
	 << " eDiff/pDiff/Tolerance "
	 << eDiff << "/" << pDiff << "/" << kEnergyConservationTolerance
	 << endl;
//      return false; // don't abort, just warn
   }
   
   return true;
}


Count
MCVertex::type() const {
   return m_interactionType;
}

DABoolean
MCVertex::radiativeDecay() const {
   return m_radiativeDecay;
}

DABoolean 
MCVertex::isType( const STL_VECTOR( string )& daughters,
		  const string parent,
		  DABoolean alsoFindConjugate,
		  Count type ) const {

   // duck out early if the type is incorrect
   if ( type != m_interactionType && type != kiAnyInteraction) {return false;}

   // we will need the property store for name/QQ_id conversions
   const MCParticlePropertyStore& theStore = 
      m_pParentParticle->properties().store();

   // MCParticlePropertyStore will return kUnknownQQid if the parent
   // is unknown (in particular, if not specified in the call, defaults
   // to
   QQ_id parentId = theStore.nameToQQId( parent );

   // translate to QQ_id's
   MCParticlePropertyStore::TransNameToQQ translate( theStore );
   STL_VECTOR( QQ_id ) qqDaughters( daughters.size() );
   transform( daughters.begin(), daughters.end(),
	      qqDaughters.begin(), translate );

   // use the QQ_id implementation for the detailed check
   return isType( qqDaughters, parentId, alsoFindConjugate, type );
}

DABoolean 
MCVertex::isType( const STL_VECTOR( QQ_id )& daughters,
		  QQ_id wantParent,
		  DABoolean alsoFindConjugate,
		  Count type ) const {
   // duck out early if the type is incorrect
   if ( type != m_interactionType && type != kiAnyInteraction) {return false;}

   // we will need the property store for dealing with the conjugate particles
   const MCParticlePropertyStore& store = 
      m_pParentParticle->properties().store();

   // keep track of the daughter checks we will need to make
   DABoolean checkSpecifiedDaughters( true );
   DABoolean checkConjugateDaughters( alsoFindConjugate );

   // duck out on parent type if a parent has been specified, and
   // identify which flavor of daughter to look for
   if ( wantParent != MCParticleProperty::kUnknownQQId ) {
      QQ_id thisParent( m_pParentParticle->properties().QQId() );
      // check the parent
      if ( wantParent == thisParent ) { // match on specified flavor
	 checkConjugateDaughters = false;
      } else if ( alsoFindConjugate ) { // wants to check match on conjugate
	 QQ_id wantConjugate( store.conjugateQQ( wantParent ) );
	 if ( wantConjugate == thisParent ) { // match on conjugate
	    checkSpecifiedDaughters = false;
	 } else { // both matches have failed
	    return false;
	 }
      } else { // flavor specific match request failes
	 return false;
      }
   }

   //
   // check the specified list of daughters
   //
   if ( checkSpecifiedDaughters ) {
      // make a temporary list and sort it that we can sort
      STL_VECTOR( QQ_id ) sorted( daughters );
      sort( sorted.begin(), sorted.end() );
      
      // check this list against the (sorted) list of actual daughters
      checkSpecifiedDaughters = 
	 equal( sorted.begin(),sorted.end(),m_childIdList.begin() );
   }

   if ( checkConjugateDaughters ) {
      MCParticlePropertyStore::TransQQToConj translate( store );
      STL_VECTOR( QQ_id ) sorted( daughters.size() );
      transform( daughters.begin(), daughters.end(), 
		 sorted.begin(), translate );
      sort( sorted.begin(), sorted.end() );
      checkConjugateDaughters =
	 equal( sorted.begin(),sorted.end(),m_childIdList.begin() );
   }

   return checkSpecifiedDaughters || checkConjugateDaughters;

}

DABoolean 
MCVertex::isTypeWith( const string& daughter,
		      const string  wantParent,
		      DABoolean alsoFindConjugate,
		      Count type ) const {
   // duck out early if the type is incorrect
   if ( type != m_interactionType && type != kiAnyInteraction) {return false;}

   // transform to QQ_id
   const MCParticlePropertyStore& store =  m_pParentParticle->properties().store();
   QQ_id parentId   = store.nameToQQId( wantParent );
   QQ_id daughterId = store.nameToQQId( daughter );
   
   // use the QQ_id implementation
   return isTypeWith( daughterId, parentId, alsoFindConjugate, type );
}

DABoolean 
MCVertex::isTypeWith( QQ_id daughter,
		      QQ_id wantParent,
		      DABoolean alsoFindConjugate,
		      Count type ) const {
   // duck out early if the type is incorrect
   if ( type != m_interactionType && type != kiAnyInteraction) {return false;}

   // we will need the property store for dealing with the conjugate particles
   const MCParticlePropertyStore& store = 
      m_pParentParticle->properties().store();

   // keep track of the daughter checks we will need to make
   DABoolean checkSpecifiedDaughter( true );
   DABoolean checkConjugateDaughter( alsoFindConjugate );

   // duck out on parent type if a parent has been specified, and
   // identify which flavor of daughter to look for
   if ( wantParent != MCParticleProperty::kUnknownQQId ) {
      QQ_id thisParent( m_pParentParticle->properties().QQId() );
      // check the parent
      if ( wantParent == thisParent ) { // match on specified flavor
	 checkConjugateDaughter = false;
      } else if ( alsoFindConjugate ) { // wants to check match on conjugate
	 QQ_id wantConjugate( store.conjugateQQ( wantParent ) );
	 if ( wantConjugate == thisParent ) { // match on conjugate
	    checkSpecifiedDaughter = false;
	 } else { // both matches have failed
	    return false;
	 }
      } else { // flavor specific match request failes
	 return false;
      }
   }

   // check the daughter flavor passed (if not matched to conj. parent)
   if ( checkSpecifiedDaughter ) {
      checkSpecifiedDaughter = 
	 binary_search(m_childIdList.begin(), m_childIdList.end(), daughter);
   }

   // check the conjugate daughter flavor (if not matched to spec. parent)
   if ( checkConjugateDaughter ) {
      QQ_id conjugateD( store.conjugateQQ( daughter ) );
      checkConjugateDaughter = 
	 binary_search(m_childIdList.begin(), m_childIdList.end(), conjugateD);
   }

   return checkSpecifiedDaughter || checkConjugateDaughter;
}


DABoolean 
MCVertex::isTypeWithParent( const string  wantParent,
			    DABoolean alsoFindConjugate,
			    Count type ) const {

   // duck out early if the type is incorrect
   if ( type != m_interactionType && type != kiAnyInteraction) {return false;}

   // transform to QQ_id
   const MCParticlePropertyStore& store =  m_pParentParticle->properties().store();
   QQ_id parentId   = store.nameToQQId( wantParent );

   // use the QQ_id implementation
   return isTypeWithParent( parentId, alsoFindConjugate, type );
}

DABoolean 
MCVertex::isTypeWithParent( QQ_id wantParent,
			    DABoolean alsoFindConjugate,
			    Count type ) const {

   // duck out early if the type is incorrect
   if ( type != m_interactionType && type != kiAnyInteraction) {return false;}

   // we will need the property store for dealing with the conjugate particles
   const MCParticlePropertyStore& store = 
      m_pParentParticle->properties().store();

   // keep track of the daughter checks we will need to make
   DABoolean foundIt( false );
   DABoolean foundConjugate( false );

   QQ_id thisParent( m_pParentParticle->properties().QQId() );
   // check the parent
   if ( wantParent == thisParent ) { // match on specified flavor
      foundIt = true;
   } else if ( alsoFindConjugate ) { // wants to check match on conjugate
      QQ_id wantConjugate( store.conjugateQQ( wantParent ) );
      foundConjugate = (wantConjugate == thisParent);  // match on conjugate
   }

   return foundIt || foundConjugate;
}

Count 
MCVertex::nChildren() const {
   return m_particleList.size();
}

Count 
MCVertex::empty() const {
   return m_particleList.empty();
}

MCVertex::const_pIterator
MCVertex::pBegin() const {
   const_pIterator theBeginning( m_particleList.begin() );
   return theBeginning;
}

MCVertex::const_pIterator
MCVertex::pEnd() const {
   const_pIterator theEnd( m_particleList.end() );
   return theEnd;
}

MCVertex::const_reverse_pIterator
MCVertex::rpBegin() const {
   const_reverse_pIterator theBeginning( m_particleList.rbegin() );
   return theBeginning;
}

MCVertex::const_reverse_pIterator
MCVertex::rpEnd() const {
   const_reverse_pIterator theEnd( m_particleList.rend() );
   return theEnd;
}

const MCParticle& 
MCVertex::parent() const {
   return *m_pParentParticle;
}

const MCParticle* 
MCVertex::parentPtr() const {
   return m_pParentParticle;
}

MCVertex*
MCVertex::clone( MCParticle* newParentPart ) const
{
// Note: when implementing the clone function for a derived class
// myMCVertex, that clone fcn should be implemented as
// return new myMCVertex( *this, newParentPart );

   // make a deep copy, but let it have a new parent particle
   return new MCVertex( *this, newParentPart );
}

ostream&
MCVertex::dump( ostream& theStream ) const {

   // save the stream state
   // -- when we can use stdio, use the following
   //           fmtflags oldflags = theStream.setf(ios::showpoint);
   int oldflags = theStream.setf(ios::showpoint);
   int oldprecision = theStream.precision();

   // this needs fleshing out
   theStream
      << setw(4) << id()
      << setw(4) << nChildren() 
      << setw(4) << type() << " ";

   FormatablePoint3D dumpPoint( position() );
   theStream.setf(ios::fixed,ios::floatfield);
   theStream.width(9);
   theStream.precision(6);
   theStream 
      << dumpPoint << " ";
   theStream.setf(ios::scientific,ios::floatfield);
   theStream 
      << setw(9) << time() << ": ";
   theStream.setf(ios::fixed,ios::floatfield);
   theStream 
      << setw(5)
      << quoteDecay( m_pParentParticle->properties().name(), m_childNameList );

   return theStream;
}

DABoolean 
MCVertex::fatalInteraction() const {
   return MCVertex::fatal( m_interactionType );
}


const HepPoint3D&
MCVertex::position() const {
   return m_vertexPosition;
}

Double
MCVertex::time() const {
   return m_time;
}

const HepLorentzVector&
MCVertex::localParentMomentum() const {
   return m_parentMomentumAtVertex;
}

const MCDecayMode&
MCVertex::decayMode() const {

   if ( m_pDecayMode == 0 ) {
      report( EMERGENCY, kFacilityString )
	 << "requested decayMode() in invalid circumstances. "
	 << "Expect your code to crash when you access any "
	 << "member fcn's" << endl;
   }
   return *m_pDecayMode;
}

DABoolean
MCVertex::operator==( const MCVertex& rhs ) const {
   DABoolean testAll =
      (m_interactionType == rhs.m_interactionType) &&
      (m_time == rhs.m_time) &&
      (m_vertexPosition == rhs.m_vertexPosition) &&
      (m_parentMomentumAtVertex == rhs.m_parentMomentumAtVertex) &&
      (size() == rhs.size());
   
   // if good so far, check that the daughters are all identical
   if ( testAll ) {
     const_pIterator thisIter = pBegin();
     const_pIterator thatIter = rhs.pBegin();
     const_pIterator theEnd = pEnd();
     for( ; testAll && (thisIter != theEnd); ++thisIter, ++thatIter ) {
       testAll = testAll && (*thisIter == *thatIter);
     }
   }

   return testAll;
}

DABoolean
MCVertex::operator!=( const MCVertex& rhs ) const {
  return !(*this == rhs);
}

//
// static member functions
//

// as is done in this MCVertex base class, derived classes should implement
// a *protected* constructor, with public access via a "newVertex" function
// that creates a vertex on the heap.  That way, the parent MCParticle can
// guarantee proper memory management
MCVertex*
MCVertex::newVertex( Count interType,
		     MCParticle* theParent, 
		     HepPoint3D thePosition,
		     Double theTime,
		     HepLorentzVector currentParentMomentum ) {
   return new MCVertex( interType, theParent, thePosition, theTime, 
			currentParentMomentum );
}

MCVertex*
MCVertex::newVertex( const MCDecayMode& theDecayMode,
		     MCParticle* theParent, 
		     HepPoint3D thePosition,
		     Double theTime,
		     HepLorentzVector currentParentMomentum ) {
   MCVertex* newVertex = new MCVertex( kiDecay, theParent, thePosition,
				       theTime, currentParentMomentum );
   newVertex->setDecayMode( theDecayMode );

   return newVertex;
}

DABoolean
MCVertex::fatal( Count theType ) {
   static const interaction nonFatalInteractionList[] = {
      kiComptonScattering,
      kiBremsstrahlung,
      kiDeltaRay,
      kiRayleighEffect,
      kiHadronicElasticCoherentInteraction,
      kiHadronicElasticIncoherentInteraction,
      kiMuonNucleusInteraction,
      kiRadiativePairProduction };

   const interaction* end = nonFatalInteractionList + 
                           sizeof(nonFatalInteractionList)/sizeof(interaction);
   const interaction* searchResult = 
      find(nonFatalInteractionList, end, theType);
   return ( searchResult == end );
}

DABoolean
MCVertex::conservingInteraction( Count theType ) {
   static const interaction conservingInteractionList[] = {kiDecay};

   const interaction* end = conservingInteractionList +
      sizeof(conservingInteractionList)/sizeof(interaction);


   // look for theType in the list
   const interaction* searchResult =
      find( conservingInteractionList,
            end,
            theType );
   
   return ( searchResult != end );
}

void
MCVertex::setEnergyConservationTolerance( Double newToler ) {
   kEnergyConservationTolerance = newToler;
}

ostream&
MCVertex::dumpHeader( ostream& aStream ) {
   aStream
      << '\n'
      << "  id" << "  #d" << " typ"
      << " position" << setw(30) 
      << "     time"
      << '\n';

      return aStream;
}
//
// friend functions
//

// default output operator for the vertex object
// implement using the virtual DUMP function so that
// derived objects may enhance/replace the default dump
// provided here
ostream& operator<<(ostream& s, const MCVertex& theVertex) {
   return theVertex.dump( s );
}

