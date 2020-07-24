// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCParticle
// 
// Description: <one line class summary>
//
// Implementation:
//     1) When one initially creates a particle, either through a
//        constructor or the clone/copy operation, it is at the
//        "top" of its decay tree.  Only when it is explicitly added
//        to a vertex does it become the member of the tree of a parent.
//
//     Required routines for creating new Particle classes that inherit 
//     from MCParticle.  See notes for corresponding routines in MCParticle
//       a) copy constructor of form
//         MyParticle( const MyParticle& rhs, MCVertex* prodVertex = 0 )
//       b) clone function of form
//         MyParticle* clone( MCVertex* newProdVertex = 0 )
//       c) dump function for use with the MCParticle << friend operator
//         ostream* dump( ostream& ) const;
//
//     

// Author:      Lawrence Gibbons
// Created:     Sun Jan 10 14:57:12 EST 1999
// $Id: MCParticle.cc,v 1.16 2003/02/03 20:24:43 bkh Exp $
//
// Revision history
//
// $Log: MCParticle.cc,v $
// Revision 1.16  2003/02/03 20:24:43  bkh
// Add new unwinding function
//
// Revision 1.15  2003/01/29 19:15:29  cdj
// get iomanip header from C++Std package
//
// Revision 1.14  2002/12/06 16:51:03  cleo3
// deal with new return type for stream::setf
//
// Revision 1.13  2002/08/16 15:17:38  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.12  2002/05/03 19:45:28  lkg
// add routine to translate the coordinate system
//
// Revision 1.11  2002/02/05 03:35:37  lkg
// call updateId in constructor to get assignment of ID from MCIdManager and proper tracking of id->pointer
//
// Revision 1.10  2001/09/27 15:41:45  tom
// Added more output to second death vertex error msg
//
// Revision 1.9  2000/10/06 18:24:59  bkh
// Add constructor with MCParticleProperty and KTKinematicData
//
// Revision 1.8  2000/10/04 21:20:24  bkh
// Add default constructor, assignment operator
//
// Revision 1.7  2000/05/01 22:50:41  lkg
// StorageHelper-related changes: added valueType arg for MCListItr typedefs and == and != operators
//
// Revision 1.6  2000/03/29 02:43:07  lkg
// Comment out (better!) versions of operator << for CLHEP vector and 4-vector
// classes.  Caused conflict when users tried to link w/ CLHEP
//
// Revision 1.5  1999/10/30 22:29:43  lkg
// Improved error messages
//
// Revision 1.4  1999/10/19 21:47:42  lkg
// * Add static dumpHeader() member fcn, which will print out column headings
//   for output created by the << operator (which invokes the dump function)
// * create particle with helicity undefined by default, rather than 0
//
// Revision 1.3  1999/07/22 20:53:13  lkg
// Check for a 3rd special helicity value when dumping an MCParticle
//
// Revision 1.2  1999/07/07 00:04:40  lkg
// Add reverse_iterator and const_reverse_iterator with associated rbegin/rend
// member functions.  Delete typedefs for "long names" like vertexIterator or
// particleIterator -- just got to be too much.
//
// Revision 1.1  1999/06/22 21:28:49  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <list>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>
#include "C++Std/iostream.h"
#include "C++Std/iomanip.h"

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCVertex.h"
#include "MCInfo/MCDecayTree/MCIdManager.h"
#include "MCInfo/MCDecayTree/MCIdMngrPtr.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <list>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCParticle" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCParticle.cc,v 1.16 2003/02/03 20:24:43 bkh Exp $";
static const char* const kTagString = "$Name: v03_09_00 $";

//
// constructors and destructor
//

MCParticle::MCParticle() :
   KTKinematicData(),
   MCTreeNode(),
   m_particleType( &MCParticleProperty::unknown() ),
   m_helicity( 0 ),
   m_pProductionVertex( 0 ),
   m_vertexList(),
   m_deathVertex( 0 )
{
   updateId();
}


MCParticle::MCParticle( const MCParticleProperty& particleType,
			const KTKinematicData&    kinDat        ) :
   KTKinematicData( kinDat ) ,
   MCTreeNode(),
   m_particleType( &particleType ),
   m_helicity( 0 ),
   m_pProductionVertex( 0 ),
   m_vertexList(),
   m_deathVertex( 0 )
{
   updateId();
   setMass( particleType.mass() ) ;
}

MCParticle::MCParticle( const MCParticleProperty& particleType,
			const HepLorentzVector&   the4Momentum,
			const HepPoint3D&         productionPnt ) :
   KTKinematicData( the4Momentum.vect(),  
		    productionPnt, 
		    the4Momentum.mag(),
		    particleType.charge() ),
   MCTreeNode(),
   m_particleType( &particleType ),
   m_helicity( 0 ),
   m_pProductionVertex( 0 ),
   m_vertexList(),
   m_deathVertex( 0 )
{
   updateId();
}

MCParticle::MCParticle( const MCParticleProperty& particleType,
			      MCVertex*           productionVertex,
			const HepLorentzVector&   the4Momentum ) :
   KTKinematicData( the4Momentum.vect(),  
		    HepPoint3D(), 
		    the4Momentum.mag(),  // aka, the mass
		    particleType.charge() ),
   MCTreeNode( productionVertex ),
   m_particleType( &particleType ),
   m_helicity( SimpleHelicity::kUndefinedHelicity ),
   m_pProductionVertex( productionVertex ),
   m_vertexList(),
   m_deathVertex( 0 )
{
   updateId();
   if ( productionVertex != 0 ) { setProductionVertex( productionVertex ); }
}

MCParticle::MCParticle( const MCParticleProperty& particleType,
			Double                    resonantMass,
			const HepPoint3D&         productionPnt ) :
   KTKinematicData( Hep3Vector(),  
		    productionPnt, 
		    resonantMass,
		    particleType.charge() ),
   MCTreeNode(),
   m_particleType( &particleType ),
   m_helicity( SimpleHelicity::kUndefinedHelicity ),
   m_pProductionVertex( 0 ),
   m_vertexList(),
   m_deathVertex( 0 )
{
   updateId();
}

MCParticle::MCParticle( const MCParticleProperty& particleType,
    		              Double              resonantMass,
			      MCVertex*           productionVertex ) :
   KTKinematicData( Hep3Vector(),  
		    HepPoint3D(), 
		    resonantMass,
		    particleType.charge() ),
   MCTreeNode( productionVertex ),
   m_particleType( &particleType ),
   m_helicity( SimpleHelicity::kUndefinedHelicity ),
   m_pProductionVertex( productionVertex ),
   m_vertexList(),
   m_deathVertex( 0 )
{ 
   updateId();
   if ( productionVertex != 0 ) { setProductionVertex( productionVertex ); }
}

MCParticle::MCParticle( const MCParticle& rhsPart, MCVertex* prodVertex ) :
   KTKinematicData( rhsPart ),
   MCTreeNode( prodVertex ),
   m_particleType( rhsPart.m_particleType ),
   m_helicity(rhsPart.m_helicity ),
   m_pProductionVertex( prodVertex ),
   m_vertexList(),
   m_deathVertex( 0 )
{
   // if we have specified a different production vertex, make sure the
   // kinematic data has this vertex as it's origin
   if ( prodVertex != 0 ) { setPosition( prodVertex->position() ); }


   //
   // Each particle owns the vertices in its list of vertices, so we
   // must replicate each vertex here
   //

   // inform the ID manager that we are about to begin the cloning descent
   // down the tree below this particle => delay ID resetting
   manager().copyStarting();
   
   // clone any vertices (which makes a deep copy, so you get any
   // particle chains attached to the vertex as well), and add
   // them to the vertex list.
   const_vIterator done  = rhsPart.vEnd();
   for ( const_vIterator itVertex = rhsPart.vBegin();
	 itVertex != done;
	 ++itVertex ) {
      addVertex( itVertex->clone(this) );
   }

   // inform the ID manager that we have finished the cloning of this particle
   // If this is the top of the clone, the id's will get reset by the
   // manager
   manager().copyDone();
}

MCParticle::~MCParticle()
{
   // delete all the vertices owned by this particle
   vList::iterator endVertex = m_vertexList.end();

   for ( vList::iterator itVertex = m_vertexList.begin();
	 itVertex != endVertex;
	 ++itVertex ) {
      delete *itVertex;
   }
}

const MCParticle& 
MCParticle::operator=( const MCParticle& rhs )
{
   if( this != &rhs )
   {
      KTKinematicData::operator=( rhs )             ;
      m_particleType      = rhs.m_particleType      ;
      m_helicity          = rhs.m_helicity          ;
      m_pProductionVertex = rhs.m_pProductionVertex ;
      m_vertexList        = rhs.m_vertexList        ;
      m_deathVertex       = rhs.m_deathVertex       ;
   }
   return *this ;
}

//
// const member functions
//
const MCParticleProperty&
MCParticle::properties() const {
   return *m_particleType;
}

Helicity
MCParticle::helicity() const {
   return m_helicity;
}

Count
MCParticle::nVertices() const {
   return m_vertexList.size();
}

Count
MCParticle::empty() const {
   return m_vertexList.empty();
}

MCParticle::const_vIterator
MCParticle::vBegin() const {
   const_vIterator theBeginning( m_vertexList.begin() );
   return theBeginning;
}

MCParticle::const_vIterator 
MCParticle::vEnd() const {
   const_vIterator theEnd( m_vertexList.end() );
   return theEnd;
}

MCParticle::const_reverse_vIterator
MCParticle::rvBegin() const {
   const_reverse_vIterator theBeginning( m_vertexList.rbegin() );
   return theBeginning;
}

MCParticle::const_reverse_vIterator 
MCParticle::rvEnd() const {
   const_reverse_vIterator theEnd( m_vertexList.rend() );
   return theEnd;
}

const MCVertex*
MCParticle::deathVertex() const {
   return m_deathVertex;
}

const MCVertex*
MCParticle::productionVertex() const {
   return m_pProductionVertex;
}

MCParticle*
MCParticle::clone( MCVertex* newProdVertex ) const {
// Note: when implementing the clone function for a derived class
// myMCPartice, that clone fcn should be implemented as
// return new myMCParticle( *this, newProdVertex );

   // make a deep copy, but let it have a new production vertex
   return new MCParticle( *this, newProdVertex );
}

ostream&
MCParticle::dump( ostream& theStream ) const {

   Count prodVertexId( 0 );
   if ( m_pProductionVertex != 0 ) {
      prodVertexId = m_pProductionVertex->id();
   }

   // save the stream state
   // -- when we can use stdio, use the following
   //           fmtflags oldflags = theStream.setf(ios::showpoint);
#if defined(USING_IOSTREAM_H_BUG)
   typedef int fmtflags;
#else
   typedef ios_base::fmtflags fmtflags;
#endif
   fmtflags oldflags = theStream.setf(ios::showpoint);
   int oldprecision = theStream.precision();

   // -- dump tree id and QQId/Name
   theStream
      << setw(4)           << id()
      << setw(4)           << m_particleType->QQId() << " ";
//   theStream.setf( ios::left );
   theStream
      << setw(5)           << m_particleType->name();
//   theStream.setf( ios::right );

   // dump the four momentum
   theStream << " ";

   theStream.setf(ios::fixed,ios::floatfield);
   theStream.precision(6);
   theStream << setw(9)    << lorentzMomentum() << " ";

   // the helicity information
   theStream.precision(1);
   if ( m_helicity == SimpleHelicity::kUndefinedHelicity ||
	m_helicity == SimpleHelicity::kRoarUndefinedHelicity ) {
      theStream << "----" ;
   } else if ( m_helicity == SimpleHelicity::kTrueHelicity ) {
      theStream << "true" ;
   } else {
      theStream
	 << setw(4)        << m_helicity;
   }

   // dump the production and number of interaction vertices
   if ( m_pProductionVertex != 0 ) {
      theStream
	 << setw(3)  	   << prodVertexId << " "
	 << setw(3)  	   << m_pProductionVertex->parent().id() << " ";
   } else {
      theStream
	 << "  -   - ";
   }
   theStream
      << setw(3)  	   << nVertices() << " ";

   // dump some decay vertex information
   if ( nVertices() > 0 ) {
      const_vIterator done  = end();
      const_vIterator start = begin();
      for ( const_vIterator itVert = start; itVert != done; ++itVert ) {
	 Count nChildren = (*itVert).nChildren();
	 if ( itVert != start ) { theStream << '\n' << setw(73) << " "; }
	 theStream << setw(4) << (*itVert).id() << setw(3) << nChildren;
	 if ( nChildren > 0 ) { 
	    theStream << setw(3) << ( *((*itVert).begin()) ).id();
	 } else { theStream << "    "; }
      } // loop over vertices
   } // if there is a vertex

   // restore the stream state
   theStream.setf( oldflags );
   theStream.precision( oldprecision);
   return theStream;
}

DABoolean
MCParticle::operator==( const MCParticle& rhs ) const {
   DABoolean testAll =
     (m_particleType->QQId() == rhs.m_particleType->QQId()) &&
     (m_helicity == rhs.m_helicity) &&
     (size() == rhs.size());
   
   // if good so far, check that the daughters are all identical
   if ( testAll ) {
     const_vIterator thisIter = vBegin();
     const_vIterator thatIter = rhs.vBegin();
     const_vIterator theEnd = vEnd();
     for( ; testAll && (thisIter != theEnd); ++thisIter, ++thatIter ) {
       testAll = testAll && (*thisIter == *thatIter);
     }
   }

   return testAll;
}

DABoolean
MCParticle::operator!=( const MCParticle& rhs ) const {
  return !(*this == rhs);
}

const MCParticle* 
MCParticle::unwindToInsideRZ( const double aRadius ,
			      const double aZ        ) const 
{
   const MCParticle* returnValue ( this ) ;

//   cout << "    ========== MC Id = " << identifier() 
//	<< ", name = " << properties().name() << endl ;
   const MCVertex* vertex ( productionVertex() ) ;
   if( 0 != vertex )
   {
      const HepPoint3D& birthPos ( vertex->position() ) ;
//      cout << " ********** vertex = " << birthPos << endl ;

      if( 0 > aRadius ||
	  0 > aZ         ) // unwind to initial particle
      {
	 if( vertex->parent().identifier() != 1 )
	 {
	    returnValue = vertex->parent().unwindToInsideRZ() ;
	 }
      }
      else
      {
	 if( aRadius < birthPos.perp()            ||
	     aZ      < fabs( birthPos.z() )             )
	 {
	    returnValue = vertex->parent().unwindToInsideRZ( aRadius, aZ ) ;
//	    cout << " ################## setting returnvalue from winding for "
//		 << returnValue->identifier() << endl ;
	 }
      }
   }
   else
   {
      returnValue = 0 ;
//      cout << " @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ setting retval= 0 !"<<endl;
   }
//   if( returnValue == this ) cout << "________________returning this " <<
//				identifier() << endl ;
   return returnValue ;
}

//
// member functions
//
MCParticle::vIterator
MCParticle::vBegin() {
   vIterator theBeginning( m_vertexList.begin() );
   return theBeginning;
}

MCParticle::vIterator
MCParticle::vEnd() {
   vIterator theEnd( m_vertexList.end() );
   return theEnd;
}

MCParticle::reverse_vIterator
MCParticle::rvBegin() {
   reverse_vIterator theBeginning( m_vertexList.rbegin() );
   return theBeginning;
}

MCParticle::reverse_vIterator
MCParticle::rvEnd() {
   reverse_vIterator theEnd( m_vertexList.rend() );
   return theEnd;
}

MCVertex*
MCParticle::deathVertex()
{
   return m_deathVertex;
}

void
MCParticle::setHelicity( Helicity newHelicity ) {
   m_helicity = newHelicity;
}

void
MCParticle::setProductionVertex( MCVertex* theProductionVertex ) {

   // store the pointer to the parent
   m_pProductionVertex = theProductionVertex;

   // set the position to be that of the vertex
   setPosition( theProductionVertex->position() );
      
   // update the manager to be the production vertex's manager
   updateManager( theProductionVertex->manager() );
}

void
MCParticle::updateManager( MCIdManager& theManager ) {

   // don't do anything if we are already using this manager
   if ( &theManager != &(manager()) ) {
      // make sure we are in the correct Tree
      setManager( theManager );

      // propagate the new information down to the daughter particles
      vIterator done = vEnd();
      for ( vIterator itVert = vBegin();
	    itVert != done;
	    ++itVert ) {
	 itVert->updateManager( theManager );
      }
   }
}

void
MCParticle::addVertex( MCVertex* newInteraction )
{
   // inform the manager that we are about to modify this tree
   manager().additionStarting();

   // make sure that the Vertex really points to this particle.
   // This also has the vertex update its ID manager
   newInteraction->setParentParticle( this );

   // add the vertex to the list
   m_vertexList.push_back( newInteraction );

   // if this particle will die in this interaction, flag this as
   // the deathVertex
   if ( newInteraction->fatalInteraction() )
   {
      if ( m_deathVertex != 0 )
      {
 	 report( ERROR, kFacilityString )
	    << "attempt to add fatal interaction vertex to particle "
	    << "that is already dead."
	    << '\n' << "Particle:" 
	    << '\n' << *this
	    << '\n' << "previous decay vertex:"
	    << '\n' << *m_deathVertex
	    << '\n' << "new decay vertex:"
	    << '\n' << *newInteraction
	    << endl;
 	 assert( false );
 	 ::exit( 1 );
      } else {
	 m_deathVertex = newInteraction;
      }
   }

   // inform the manager that the tree modification is done, which will
   // trigger ID updating
   manager().additionDone();
}

void
MCParticle::updateId() {
   manager().resetId( *this );
}

void
MCParticle::updateChildrenIds() {

   // will do 2 iterations over daughter list, store begin/end
   vIterator done  = vEnd();
   vIterator start = vBegin();
   
   // solaris seems to have the wrong scope for itVert -- outside
   // of the for-loop if I use "for (vIterator itVert = start; ..."
   // So, define it just once locally.
   vIterator itVert;

   // first, reset the vertex id's.  This keeps all vertices of
   // one particle grouped together
   for ( itVert = start; itVert != done;  ++itVert )  {
      itVert->updateId();
   }

   // next, tell each vertex to have its children update their Ids
   for ( itVert = start; itVert != done;  ++itVert )  {
      itVert->updateChildrenIds();
   }
}
void 
MCParticle::translateCoordinates( const Hep3Vector& translationVector ) {
   HepPoint3D newPosition = position() + translationVector;
   setPosition( newPosition );
   vIterator endPosition = end();
   for ( vIterator vertex = begin(); vertex != endPosition; ++vertex ) {
   	vertex->translateCoordinates( translationVector );
   }
}


//
// static member functions
//
ostream&
MCParticle::dumpHeader( ostream& theStream ) {
   theStream
      << '\n'
      << "    " << "     " << "     " << setw(43) << "  "
      << "    " << " Prod" << "     " << "Interactions"
      << '\n'
      << " id " << "QQId " << " Name" << " Four momentum" << setw(28) << " "
      << " hel " << " Vtx" << " Par " << " #  " << " id #d 1st"
      << '\n';

      return theStream;
}
//
// friend functions
//

// default output operator for the particle object
// implement using the virtual DUMP function so that
// derived objects may enhance/replace the default dump
// provided here
ostream& operator<<(ostream& s, const MCParticle& theParticle)
{
   return theParticle.dump( s );
}

/* comment out this nicer implementation so that users can link with
// CLHEP properly
ostream& operator <<(ostream& s, const HepLorentzVector &q)
{
  int userWidth = s.width();
  return s << setw(0) << "(" 
           << setw(userWidth) << q.x() << "," 
	   << setw(userWidth) << q.y() << ","
           << setw(userWidth) << q.z() << ";" 
	   << setw(userWidth) << q.t() << ")";
}
*/
