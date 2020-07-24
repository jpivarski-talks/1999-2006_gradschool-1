#if !defined(MCINFO_MCIDMANAGER_H)
#define MCINFO_MCIDMANAGER_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCIdManager
// 
// Description: Serves Particle/Vertex ID Numbers for a decay tree
//
// Usage:
//    The natural method of dealing with a deep copy of a decay tree is to
//    descend down the entire branch hanging off of one node in
//    the tree before copying the next sibling node (and it's branch).
//    This makes additions of new branches to the tree quite simple, but
//    does not lead to "automatic ID numbering" scheme that an end-user
//    would find natural.
//
//    As a result, a server class to deal with the ID's has been implemented.
//    This class simplifies assignment of ID's in the Particle and Vertex
//    classes, so that the following ordering of ID's can be maintained:
//
//                             P1
//                            /  \
//                           V1  V2
//                           /  / | \
//                          P2 P3 P4 P5
//                              |
//                              V3
//                             /  \
//                            P6  P7
//
//    That is, the particle ID's from a given vertex will be sequential,
//    and the vertex ID's from a given particle will also be sequential.
//
// Author:      Chris Jones / Lawrence Gibbons
// Created:     Sat Mar 20 15:18:00 EST 1999
// $Id: MCIdManager.h,v 1.2 2002/02/05 03:25:38 lkg Exp $
//
// Revision history
//
// $Log: MCIdManager.h,v $
// Revision 1.2  2002/02/05 03:25:38  lkg
// add vectors and access functions for constant-time particle or vertex look-up
//
// Revision 1.1  1999/06/22 21:30:00  lkg
// First real version of MCInfo in repository
//

// system include files
#include <vector>

// user include files
#include "STLUtility/fwd_vector.h"

// forward declarations
class MCTreeNode;
class MCParticle;
class MCVertex;

class MCIdManager
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      MCIdManager( MCTreeNode* topNode );

      virtual ~MCIdManager();

      // ---------- member functions ---------------------------

      // inform this ID manager that a deep copy of a (sub)tree, or
      // an addition of a new Node to the tree, is starting
      void copyStarting();
      void additionStarting();

      // inform this ID manager that the deep copy or addition has completed
      void copyDone();
      void additionDone();

      // reset a Node's ID to the last unused ID.  This is 
      // overloaded for each type of node in the tree (particle 
      // and vertex) so that we know which type of ID to serve
      void resetId( MCParticle& aParticle );
      void resetId( MCVertex&   aVertex );


      // To allow every Node in the tree to point at this server,
      // a smart reference-counting pointer is implemented.  The
      // following fcn's keep track of the number of references
      // to this server
      void addReference();
      void removeReference();

      // ---------- const member functions ---------------------
      DABoolean hasRefs() const;
      
      // to allow efficient access to a particle based on its
      // decay tree ID, the ID Manager keeps track of the
      // particle <-> id association.  Use these functions for
      // efficient (constant time) access
      const MCParticle* getParticle( Count particleId ) const;
      const MCVertex* getVertex( Count vertexId ) const;
      
      // ---------- const member functions ---------------------
	static Count startingIdentifier();
	      
   protected:
   
      // request the ID manager to reset the id's starting from
      // the top of the tree
      void assignIdentifiers();
      
      // reset the ID->pointer mapping vectors
      void initializeIdMaps();
      
   private:
      // ---------- Constructors and destructor ----------------
      MCIdManager(); // stop default: we always want a tree top
      MCIdManager( const MCIdManager& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const MCIdManager& operator=( const MCIdManager& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      // the topmost node of this tree.  This ID manager will ask the
      // top of the tree to update the ID's of particle's in it's
      // tree when necessary
      MCTreeNode* m_topNode;
      
      // the last Vertex and Particle ID's assigned
      Count m_lastVertexId;
      Count m_lastParticleId;

      // tactic for delaying updating of ID's when attempting a
      // deep copy of a particle delay.  Only do actual updating
      // when cloneLevel == 0.
      Count m_copyLevel;

      // for reference-counting smart pointer implementation
      Count m_refCount;

      // Vectors for constant-time access to particles and vertices
      // based on tree-id
      STL_VECTOR( MCParticle* ) m_particleList;
      STL_VECTOR( MCVertex* ) m_vertexList;
      // ---------- static data members ------------------------
};

// inline function definitions
inline void MCIdManager::additionStarting() { copyStarting(); }
inline void MCIdManager::additionDone() { copyDone(); }
inline const MCParticle* MCIdManager::getParticle( Count particleId ) const {
   if ( particleId < 1 || particleId >= m_particleList.size() ) {return 0;}
   return m_particleList[particleId];
}

inline const MCVertex* MCIdManager::getVertex( Count vertexId ) const {
   if ( vertexId < 1 || vertexId >= m_vertexList.size() ) {return 0;}
   return m_vertexList[vertexId];
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/MCIdManager.cc"
//#endif

#endif /* MCINFO_MCIDMANAGER_H */
