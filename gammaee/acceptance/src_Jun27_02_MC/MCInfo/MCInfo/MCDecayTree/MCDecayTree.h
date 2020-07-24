#if !defined(MCINFO_MCDECAYTREE_H)
#define MCINFO_MCDECAYTREE_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCDecayTree
// 
// Description: Provide iteration and search methods for the hierarchical
//              decay tree.
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sat Jan  9 13:32:28 EST 1999
// $Id: MCDecayTree.h,v 1.9 2001/12/19 18:11:08 lkg Exp $
//
// Revision history
//
// $Log: MCDecayTree.h,v $
// Revision 1.9  2001/12/19 18:11:08  lkg
// add particle/vertex lookup that returns an iterator (already used internally)
//
// Revision 1.8  2000/07/19 15:49:43  lkg
// * add test/search functions to find vertex w/ a particular parent
// * add search functions (MCDecayTree) that allow user to specify a
//   starting vertex iterator (reimplement original search fcn's to call
//   new fcn's with start specified by vBegin())
//
// Revision 1.7  2000/07/07 01:42:23  lkg
// move non-const member fcn out of const fcn list
//
// Revision 1.6  2000/05/04 17:51:29  cdj
// added non-const topParticle() used during storage
//
// Revision 1.5  2000/05/01 22:44:17  lkg
// Added == and != operators, needed for StorageHelpers
//
// Revision 1.4  1999/10/19 21:40:30  lkg
// * Don't use enum type "iterator" as a fcn return type, use Count instead.  Get
//   conversion problems for users with "iterator"
// * add non-const versions of getParticle[Ptr] and getVertex[Ptr] fcn's
//
// Revision 1.3  1999/07/07 13:09:46  lkg
// Add an iterator over the "stable" particles in the decay tree:
// MCDecayTree::const_sIterator typedef'd to MCStablePartItr
//
// Revision 1.2  1999/07/06 21:21:46  lkg
// minor formatting changes
//
// Revision 1.1  1999/06/22 21:29:58  lkg
// First real version of MCInfo in repository
//

// system include files

// user include files
#include "MCInfo/MCDecayTree/MCDecayTreeItr.h"
#include "MCInfo/MCDecayTree/MCStablePartItr.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCVertex.h"

// forward declarations
#include "C++Std/fwd_ostream.h"

class MCDecayTree
{
      // ---------- friend classes and functions ---------------

      // default output operator for the Decay Tree object
      friend ostream& operator<<(ostream& aStream, 
				 const MCDecayTree& aTree);

   public:
      // ---------- constants, enums and typedefs --------------

      // iterator over particles in the tree
      typedef MCDecayTreeItr< const MCParticle, 
	                      MCVertex::const_pIterator >   const_pIterator;

      // iterator over the vertices in the tree
      typedef MCDecayTreeItr< const MCVertex, 
	                      MCParticle::const_vIterator > const_vIterator;

      // iterator over STABLE particles in the tree
      typedef MCStablePartItr                               const_sIterator;

      // lifetime cutoff to be used in defining "stable" particles.  These
      // are the particles, that, for example, GEANT would track.  Default
      // is 0.01 meters (c*tau_life)
      static const Meters kStableCTauCutoff;

      // ---------- Constructors and destructor ----------------
      MCDecayTree( DABoolean ownTree = true );
      MCDecayTree( MCParticle* topParticle, DABoolean ownTree = true  );
      MCDecayTree( const MCParticle* topParticle );

      MCDecayTree( const MCDecayTree& rhs ); // deep copy! will replicate tree

      virtual ~MCDecayTree();

      // ---------- member functions ---------------------------
      // set the top parent in this tree.
      void setParent( MCParticle*, DABoolean ownTree = true ); 
      MCParticle& topParticle() { return *m_topParticle; }

      // ---------- const member functions ---------------------

      const MCParticle& topParticle() const { return *m_topParticle; }

      // allow iteration over all of the MCParticles contained in
      // the daughter tree
      const_pIterator pBegin() const; // first in tree
      const_pIterator pEnd()  const;  // one past end

      // allow iteration over all of the STABLE MCParticles contained in
      // the daughter tree
      const_sIterator sBegin() const; // first in tree
      const_sIterator sEnd()  const;  // one past end

      // allow iteration over all of the MCVertices contained in
      // the daughter tree
      const_vIterator vBegin() const; // first in tree
      const_vIterator vEnd() const;   // one past end of tree

      // Get a decay tree that is a branch of this tree
      // --- make a tree w/ a particular particle at top
      const MCDecayTree subTree( const_pIterator   ) const;
      const MCDecayTree subTree( const MCParticle& ) const;
      // --- make a tree w/ the parent Particle of a vertex at top
      const MCDecayTree subTree( const_vIterator   ) const;
      const MCDecayTree subTree( const MCVertex&   ) const;

      // the particle/vertex of a given ID within this tree
      // --- return reference
      const MCParticle& getParticle( Count treeId ) const;
      const MCVertex&   getVertex(   Count treeId ) const;
      // --- return pointer
      const MCParticle* getParticlePtr( Count treeId ) const;
      const MCVertex*   getVertexPtr(   Count treeId ) const;
      // --- return iterator
      const_pIterator pFind( Count treeId ) const;
      const_vIterator vFind( Count treeId ) const;

      // non-const versions of the particle/vertex return fxns
      MCParticle& getParticle( Count treeId );
      MCVertex&   getVertex(   Count treeId );
      MCParticle* getParticlePtr( Count treeId );
      MCVertex*   getVertexPtr(   Count treeId );

      //
      // some helpers for finding a specific interaction
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
      // ---------------------------------------------------------
      // find a specific interaction: exact match on daughter list. 
      // a) using strings to specify parent/daugthters
      const_vIterator
      findVertex( const STL_VECTOR( string )& daughters,
		  const string parent = "",
		  DABoolean alsoFindConjugate = true,
		  Count type = kiDecay ) const;
      
      const_vIterator
      findVertex( const_vIterator startingVertex,
		  const STL_VECTOR( string )& daughters,
		  const string parent = "",
		  DABoolean alsoFindConjugate = true,
		  Count type = kiDecay ) const;
      
      // b) using QQ_id to specify parent/daughters
      const_vIterator
      findVertex( const STL_VECTOR( QQ_id )& daughters,
		  QQ_id parent = MCParticleProperty::kUnknownQQId,
		  DABoolean alsoFindConjugate = true,
		  Count type = kiDecay ) const;

      const_vIterator
      findVertex( const_vIterator startingVertex,
		  const STL_VECTOR( QQ_id )& daughters,
		  QQ_id parent = MCParticleProperty::kUnknownQQId,
		  DABoolean alsoFindConjugate = true,
		  Count type = kiDecay ) const;

      // ---------------------------------------------------------
      // find a specific interaction: contains a particular daughter
      // a) using strings to specify parent/daugthters
      const_vIterator
      findVertexWith( const string& daughter,
		      const string  parent = "",
		      DABoolean alsoFindConjugate = true,
		      Count type = kiDecay ) const;
      
      const_vIterator
      findVertexWith( const_vIterator startingVertex,
		      const string& daughter,
		      const string  parent = "",
		      DABoolean alsoFindConjugate = true,
		      Count type = kiDecay ) const;
      
      // b) using QQ_id to specify parent/daughters
      const_vIterator 
      findVertexWith( QQ_id daughter,
		      QQ_id parent = MCParticleProperty::kUnknownQQId,
		      DABoolean alsoFindConjugate = true,
		      Count type = kiDecay ) const;
      
      const_vIterator 
      findVertexWith( const_vIterator startingVertex,
		      QQ_id daughter,
		      QQ_id parent = MCParticleProperty::kUnknownQQId,
		      DABoolean alsoFindConjugate = true,
		      Count type = kiDecay ) const;
      
      // ---------------------------------------------------------
      // find a specific interaction: from a particular parent
      // a) using strings to specify parent
      const_vIterator
      findVertexWithParent( const string  parent,
			    DABoolean alsoFindConjugate = true,
			    Count type = kiDecay ) const;
      
      const_vIterator
      findVertexWithParent( const_vIterator startingVertex,
			    const string  parent,
			    DABoolean alsoFindConjugate = true,
			    Count type = kiDecay ) const;
      
      // b) using QQ_id to specify parent
      const_vIterator 
      findVertexWithParent( QQ_id parent,
			    DABoolean alsoFindConjugate = true,
			    Count type = kiDecay ) const;
      
      const_vIterator 
      findVertexWithParent( const_vIterator startingVertex,
			    QQ_id parent,
			    DABoolean alsoFindConjugate = true,
			    Count type = kiDecay ) const;

      DABoolean operator==( const MCDecayTree& rhs ) const;
      DABoolean operator!=( const MCDecayTree& rhs ) const;

      // ---------- static member functions --------------------
      static void setStableLifetimeCutoff( Double );

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- assignment operator(s) ---------------------
      const MCDecayTree& operator=( const MCDecayTree& ); // stop default

      // ---------- private member functions -------------------
      void updateLists();
	  
      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // to get all of our iteration schemes to work out, store
      // the top particle in a vector of length 1.
      MCParticle* m_topParticle;
      STL_VECTOR( MCParticle* )& m_topParticleV;
      DABoolean m_manageTreeMemory;
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/MCDecayTree.cc"
//#endif

#endif /* MCINFO_MCDECAYTREE_H */
