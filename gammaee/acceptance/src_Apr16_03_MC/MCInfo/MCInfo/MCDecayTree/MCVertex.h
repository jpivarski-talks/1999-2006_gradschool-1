#if !defined(MCINFO_MCVERTEX_H)
#define MCINFO_MCVERTEX_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCVertex
// 
// Description: A container of the particles produced at an interaction,
//              as well as the interaction properties themselves
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sun Jan 10 14:57:24 EST 1999
// $Id: MCVertex.h,v 1.8 2002/05/03 18:59:02 lkg Exp $
//
// Revision history
//
// $Log: MCVertex.h,v $
// Revision 1.8  2002/05/03 18:59:02  lkg
// add routine to translate the coordinate system
//
// Revision 1.7  2002/01/20 19:09:39  lkg
// new member fcn to check decay mode vs actual children
//
// Revision 1.6  2001/12/19 18:11:21  lkg
// add support for radiative decays: look for one extra photon in decay
//
// Revision 1.5  2000/07/19 15:49:43  lkg
// * add test/search functions to find vertex w/ a particular parent
// * add search functions (MCDecayTree) that allow user to specify a
//   starting vertex iterator (reimplement original search fcn's to call
//   new fcn's with start specified by vBegin())
//
// Revision 1.4  2000/05/01 22:50:45  lkg
// StorageHelper-related changes: added valueType arg for MCListItr typedefs and == and != operators
//
// Revision 1.3  1999/10/19 21:54:03  lkg
// * replace return and argument types using the enum "interaction" to use
//   Count
// * add a member fcn that allows a single child to be added at a time
// * add a dumpHeader() member fcn that prints a header for the info output
//   by the MCVertex <<() operator
//
// Revision 1.2  1999/07/06 21:35:48  lkg
// Add reverse_iterator and const_reverse_iterator and associated rbegin/rend
// functions.  Eliminate the lengthy names (vertexIterator) -- just too much
//
// Revision 1.1  1999/06/22 21:30:03  lkg
// First real version of MCInfo in repository
//

// system include files
#include <vector>
//#include <string>

// user include files
#include "MCInfo/MCDecayTree/interaction_types.h"
#include "MCInfo/MCDecayTree/MCTreeNode.h"
#include "MCInfo/MCDecayTree/MCListItr.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Vector/LorentzVector.h"

// forward declarations
 #include "C++Std/fwd_ostream.h"
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
class MCParticle;
class MCDecayMode;

class MCVertex : public MCTreeNode
{
      // ---------- friend classes and functions ---------------
      friend ostream& operator<<(ostream& aStream,
				 const MCVertex& aVertex);
      
      friend class MCParticle;

   public:

      // ---------- constants, enums and typedefs --------------
      static GeV kEnergyConservationTolerance;

      typedef STL_VECTOR( MCParticle* )   pList;

      //
      // ------- define the various iterator classes -------
      //
      typedef MCListItr< pList::iterator, MCParticle, MCParticle >              pIterator;
      typedef MCListItr< pList::const_iterator, const MCParticle, MCParticle > 
                                                              const_pIterator;
      typedef MCListItr< pList::reverse_iterator, MCParticle, MCParticle > 
	                                                    reverse_pIterator;
      typedef MCListItr< pList::const_reverse_iterator, const MCParticle, MCParticle > 
                                                      const_reverse_pIterator;

      // --- synonyms
      typedef         const_pIterator         const_iterator;  // STL-like
      typedef               pIterator               iterator;  // STL-like
      typedef const_reverse_pIterator const_reverse_iterator;  // STL-like
      typedef       reverse_pIterator       reverse_iterator;  // STL-like

      // ---------- Constructors and destructor ----------------

      // standard CONSTRUCTORS are PROTECTED -- use newVertex to
      // get a pointer to a Vertex created on the heap.
      
      virtual ~MCVertex();
      
      // ---------- const member functions ---------------------
      
      // what kind of interaction was this
      Count type() const;
      
      //
      // query interaction based on daughters, parent, interaction type
      //
      // For all of the methods below:
      // 0) All methods provided w/ either QQ_id or name (string) for
      //    specifying mode (cannot mix and match)
      // 1) will match parent if given. 
      // 2) default behaviour will find the mode specified or the
      //    conjugate MODE (ie, retaining flavor relationship between
      //    parent,daughter). For flavor specific, pass "false" as 3rd arg
      // 3) a) Looks for a DECAY if interaction type not specified.
      //    b) Use interaction type kiAnyInteraction if you don't care
      //       about the specific mechanism
      
      // exact match on daughter list. 
      DABoolean isType( const STL_VECTOR( string )& daughters,
			const string parent = "",
			DABoolean alsoFindConjugate = true,
			Count type = kiDecay ) const;
      DABoolean isType( const STL_VECTOR( QQ_id )& daughters,
			QQ_id parent = MCParticleProperty::kUnknownQQId,
			DABoolean alsoFindConjugate = true,
			Count type = kiDecay ) const;

      // contains a particular daughter
      DABoolean isTypeWith( const string& daughter,
			    const string  parent = "",
			    DABoolean alsoFindConjugate = true,
			    Count type = kiDecay ) const;

      DABoolean isTypeWith( QQ_id daughter,
			    QQ_id parent = MCParticleProperty::kUnknownQQId,
			    DABoolean alsoFindConjugate = true,
			    Count type = kiDecay ) const;

      // contains a particular daughter
      DABoolean isTypeWithParent( const string parent,
				  DABoolean alsoFindConjugate = true,
				  Count type = kiDecay ) const;

      DABoolean isTypeWithParent( QQ_id parent,
				  DABoolean alsoFindConjugate = true,
				  Count type = kiDecay ) const;

      // 
      //
      // Particle container: const access
      //

      // the number of children
      Count nChildren() const;
      Count size()      const;    // standard container synonym for nChildren
      Count empty()     const;    // related standard container function

      // for iteration over the the child particles produced
      const_pIterator               pBegin() const;
      const_iterator                 begin() const; // standard container name
      const_pIterator               pEnd()   const;
      const_iterator                 end()   const; // standard container name

      const_reverse_pIterator      rpBegin() const;
      const_reverse_iterator        rbegin() const; // standard container name
      const_reverse_pIterator      rpEnd()   const;
      const_reverse_iterator        rend()   const; // standard container name
      //
      // Interaction/decay queries
      //

      
      // does the parent particle disappear as a result of the
      // interaction at this vertex
      DABoolean fatalInteraction() const;
      
      // access to parent MCParticle
      const MCParticle& parent() const;
      const MCParticle* parentPtr() const;

      // location of the interaction
      const HepPoint3D& position() const;
      
      // time of the interaction
      Double time() const;
      
      // 4 momentum of parent *at this vertex*
      const HepLorentzVector& localParentMomentum() const;
      
      // check if charge and momentum were conserved at this vertex
      DABoolean checkConservedQuantities() const;
      
      // check if the daughter list agrees with the decay mode
      DABoolean checkDecayModeConsistency() const;
      
      // access to the DecayMode property used (for decays only)
      const MCDecayMode& decayMode() const;

      // was this a radiative decay? (photon added to expected daughter list)
      DABoolean radiativeDecay() const;
      
      // ---------- virtual const member functions -------------
      
      // A virtual CLONE/NEW functions for creating and copying
      // derived classes with the user manipulating only the base
      // class.  Classes that inherit from this base class
      // should provide implementations of these functions so that
      // the base class only is not accidentally sliced out
      
      virtual MCVertex* clone( MCParticle* newParentPart = 0 ) const;
      
      // A virtual DUMP function allows derived classes to override
      // or augment the output provided via the "<<" operator.
      virtual ostream& dump( ostream& ) const;
      
      DABoolean operator==( const MCVertex& rhs ) const;
      DABoolean operator!=( const MCVertex& rhs ) const;

      // ---------- member functions ---------------------------
      
      
      // 
      //  Particle container: non-const access
      //

      pIterator              pBegin(); //
      iterator                begin(); // standard container version
      pIterator              pEnd();   //
      iterator                end();   // standard container version

      reverse_pIterator     rpBegin(); //
      reverse_iterator       rbegin(); // standard container version
      reverse_pIterator     rpEnd();   //
      reverse_iterator       rend();   // standard container version

      //
      // member functions for constructing this vertex
      //

      // for the special case of this being a decay, allow the
      // implementer to set a pointer to the decay mode
      virtual void setDecayMode( const MCDecayMode& decayMode,
                                 DABoolean radiativeDecay = false );

      // set/replace all of the children particles.  **COPIES**
      // the children (along with any tree hanging off of any
      // child), so the user is reponsible for deleting any temporary
      // children passed in.
      // Two variations:
      //  - setChildren: does not make a copy, assumes that caller has
      //      created Children on the heap, and that MCVertex will take
      //      control of the children
      //  - copyAndSetChildren:  makes a copy of the children, explicitly
      //      taking over management of the memory
      //
      // Derived vertex classes may wish to implement a validity check,
      // or to calculate a matrix element based the children and throw dice,
      // so allow for communication of this operation's success
      virtual DABoolean setChildren( const pList& children );
      virtual DABoolean copyAndSetChildren( const pList& children );

      // This class will ADD a single child particle to a vertex, not changing
      // the current children.  It should **ONLY** be used in the case of
      // a nonconserving interaction
      virtual DABoolean addChild( MCParticle* newParticle );

      // ask this vertex to fill a pList of the children it expects.
      // This null argument will ONLY work if vertex is a decay mode w/ 
      // a deterministic list of children.
      // DANGER: this fcn will create particles on the heap.  It is the
      // calling fcn's job to delete these particles if they are no longer
      // used, eg., if copyAndSetChildren is used rather than setChildren.
      virtual pList& fillChildrenTemplate( pList& );
      virtual pList& fillChildrenTemplate( pList&, const STL_VECTOR(QQ_id)& );

      // modifying the interaction parameters
      // --- location of the interaction
      void setPosition( const HepPoint3D& thePosition );
      
      // time of the interaction
      void setTime( Double theTime );
      
      // 4 momentum of parent *at this vertex*
      void setLocalParentMomentum( const HepLorentzVector& theParentMomentum );
      
      // flag this as a radiative decay
      void setRadiativeDecay();
      
      // translate the coordinate system for this particle (and descendents)
      void translateCoordinates( const Hep3Vector& translationVector );

      // ---------- static member functions --------------------
      // dump a header listing column contents for the dump command
      static ostream& dumpHeader( ostream& );

      static void setEnergyConservationTolerance( Double );


      // to create a vertex for any kind of an interaction
      static MCVertex* 
	 newVertex( Count vertexType,
		    MCParticle* theParent,
		    HepPoint3D  thePosition = HepPoint3D(), 
		    Double theTime = 0,
		    HepLorentzVector currentParentMomentum = HepLorentzVector());

      static MCVertex*
	 newVertex( Count vertexType,
		    MCParticle& theParent,
		    HepPoint3D thePosition = HepPoint3D(), 
		    Double theTime = 0,
		    HepLorentzVector currentParentMomentum = HepLorentzVector());
      
      // to create an interaction for a specific decay mode
      static MCVertex* 
	 newVertex( const MCDecayMode& aMode,
		    MCParticle* theParent,
		    HepPoint3D thePosition = HepPoint3D(), 
		    Double theTime = 0,
		    HepLorentzVector currentParentMomentum = HepLorentzVector());
      
      static MCVertex* 
	 newVertex( const MCDecayMode&,
		    MCParticle& theParent,
		    HepPoint3D thePosition = HepPoint3D(), 
		    Double theTime = 0,
		    HepLorentzVector currentParentMomentum = HepLorentzVector());

      static DABoolean fatal( Count );
      
      static DABoolean conservingInteraction( Count );
      
   protected:
      // ---------- protected member functions -----------------
      
      // the constructors are protected.  Force the implementer
      // of a decay model to use the newVertex (to create)
      // or clone (to copy) functions, which guarantee that

      // the vertex is created on the heap, not the stack.  The
      // parent particle will then look after management of the
      // daughter vertex memory (without the daughter being
      // inadvertently zapped.
      
      // constructor -- any kind of interaction
      MCVertex( Count vertexType,
		MCParticle* theParent,
		HepPoint3D thePosition = HepPoint3D(), 
		Double theTime = 0,
		HepLorentzVector currentParentMomentum = HepLorentzVector() );

      // copy constructor,  with or without a parent particle specified
      MCVertex( const MCVertex&, MCParticle* parentPart = 0 );
      
      // make this vertex points to the proper Parent Particle
      void setParentParticle( MCParticle* );

      // update the manager that deals with the decay tree bookkeeping
      void updateManager( MCIdManager& );

      // update the Id of this particle in the tree
      void updateId();

      // update the ID's of any children new to this tree
      void updateChildrenIds();
      
      DABoolean operator==( const MCParticle& rhs ) const;
      DABoolean operator!=( const MCParticle& rhs ) const;
      // ---------- protected const member functions -----------
      
   private:
      // ---------- Constructors and destructor ----------------
      MCVertex(); // stop default, vertex must always have a parent
      
      // clears out the list of children
      void clearChildren();

      // ---------- assignment operator(s) ---------------------
      const MCVertex& operator=( const MCVertex& ); // implement deep copy
      
      
      // ---------- private member functions -------------------
      void updateTypeList();

      // ---------- data members -------------------------------
      
      // Vertex Parameters
      // --- where
      HepPoint3D m_vertexPosition;
      // --- when
      Double m_time;
      // --- parent momentum when the interaction occurred
      HepLorentzVector m_parentMomentumAtVertex;
      
      // the type of interaction that occurred
      Count m_interactionType;
      
      // the list of children produced at this vertex
      pList m_particleList;
      
      // the parent of this particle
      MCParticle* m_pParentParticle;
      
      // for bona-fide decays, pointer to the decay mode used for
      // this decay
      const MCDecayMode* m_pDecayMode;
      
      // flag if this is a radiative decay
      DABoolean m_radiativeDecay;
      
      // for quick references, store a local copy of the id's and Names
      // of the children.  The Id list is sorted.
      STL_VECTOR( QQ_id )& m_childIdList;
      STL_VECTOR( string )& m_childNameList;

};

// inline const function definitions
inline MCVertex::const_reverse_iterator
MCVertex::rbegin() const { return rpBegin(); };

inline MCVertex::const_reverse_iterator
MCVertex::rend() const { return rpEnd(); };

inline MCVertex::const_iterator
MCVertex::begin() const { return pBegin(); };

inline MCVertex::const_iterator
MCVertex::end() const { return pEnd(); };

inline Count
MCVertex::size() const { return nChildren(); };

// inline non-const function definitions
inline MCVertex::reverse_iterator
MCVertex::rbegin() { return rpBegin(); };

inline MCVertex::reverse_iterator
MCVertex::rend() { return rpEnd(); };

inline MCVertex::iterator
MCVertex::begin() { return pBegin(); };

inline MCVertex::iterator
MCVertex::end() { return pEnd(); };

inline MCVertex* MCVertex::newVertex( Count interType,
				      MCParticle& theParent,
				      HepPoint3D thePosition,
				      Double theTime,
				      HepLorentzVector currentParentMomentum ) {
   return newVertex( interType, &theParent, thePosition, theTime,
		     currentParentMomentum );
};

inline MCVertex* MCVertex::newVertex( const MCDecayMode& theDecayMode,
				      MCParticle& theParent,
				      HepPoint3D thePosition,
				      Double theTime,
				      HepLorentzVector currentParentMomentum ) {
   return newVertex( theDecayMode, &theParent, thePosition, theTime,
		     currentParentMomentum );
};

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/MCVertex.cc"
//#endif



//
// If the ability to convert from pIterator to const_pIterator is needed,
// replace the first two typedefs at the start of the class definition to
// with the following classes
//
//      class const_pIterator;
//      class pIterator : public MCListItr< pList::iterator, MCParticle >
//      {
//	 friend class MCVertex::const_pIterator;
//	 public: 
//	    typedef MCListItr< pList::iterator, MCParticle > baseItr;
//	    pIterator() : baseItr() {};
//	    pIterator( const pList::iterator& anItr ) : baseItr(anItr) {};
//	    pIterator( const pIterator& rhs ) : baseItr( rhs ) {};
//      };
//
//      class const_pIterator : public MCListItr< pList::const_iterator, const MCParticle >
//      {
//	 public:
//	    typedef MCListItr< pList::const_iterator, const MCParticle > baseItr;
//	    const_pIterator() : baseItr() {};
//	    const_pIterator( const pList::const_iterator& anItr ) : 
//	       baseItr(anItr) {};
//	    const_pIterator( pIterator nonConstItr ) : 
//	       baseItr( nonConstItr.bareIterator() ) {};
//	    const_pIterator( const const_pIterator& rhs ) : baseItr( rhs ) {};
//      };

#endif /* MCINFO_MCVERTEX_H */
