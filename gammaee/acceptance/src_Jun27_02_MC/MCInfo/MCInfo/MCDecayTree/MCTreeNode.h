#if !defined(MCINFO_MCTREENODE_H)
#define MCINFO_MCTREENODE_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCTreeNode
// 
// Description: base class for nodes in a decay tree: deals with the ID's
//
// Usage:
//    <usage>
//
// Author:      Chris Jones / Lawrence Gibbons
// Created:     Sat Mar 20 15:17:27 EST 1999
// $Id: MCTreeNode.h,v 1.4 2002/02/05 03:33:24 lkg Exp $
//
// Revision history
//
// $Log: MCTreeNode.h,v $
// Revision 1.4  2002/02/05 03:33:24  lkg
// add public const access to MCIdManager, better Id initialization
//
// Revision 1.3  2001/05/13 19:16:41  lyon
// Add typedef Count Identifier -- lattice needs it
//
// Revision 1.2  1999/10/30 12:29:19  cleo3
// updated to work with cxx 6.2
//
// Revision 1.1  1999/06/22 21:30:02  lkg
// First real version of MCInfo in repository
//

// system include files
#include <algorithm>
#include <functional>

// user include files
#include "MCInfo/MCDecayTree/MCIdMngrPtr.h"

// forward declarations
class MCIdManager;

class MCTreeNode
{
      // ---------- friend classes and functions ---------------
      friend class MCIdManager;   // server needs access to updateId,
                                  // updateChildrenIds, setId
   public:

      // -------- typedefs -------
      typedef Count Identifier;

      // ---------- const member functions ---------------------

      // the tree ID: provide shorthand synonym
      Count identifier() const;
      Count id() const;
      
      // allow public const access to the manager
      const MCIdManager& manager() const;

   protected:
      // ---------- Constructors and destructor ----------------
      // default constructor creates a "parentless" Node
      MCTreeNode( MCTreeNode *theParent = 0 );
      virtual ~MCTreeNode();

      // ---------- protected member functions -----------------
      void setId( Count newId );

      // the inheriting classes must supply the algorithm to use for
      // updating the Id, and for updating any Children's ids
      virtual void updateId() = 0;
      virtual void updateChildrenIds() = 0;

      void      setManager( MCIdManager& );
      MCIdManager& manager();

   private:
      // ---------- Constructors and destructor ----------------
      MCTreeNode( const MCTreeNode& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const MCTreeNode& operator=( const MCTreeNode& ); // stop default

      // ---------- data members -------------------------------

      // the id of the node in this tree
      Count m_treeId;

      // the id manager for this tree
      MCIdMngrPtr m_idManager;

   public:
      // ---------- STL helper utilities ---------- 
      struct CheckId : public STD_PREFIX unary_function< const MCTreeNode&, DABoolean > {
	    CheckId( Count id ) : m_idToCheck( id ){};
	    DABoolean operator()( const MCTreeNode& aNode ) {
	       return aNode.id() == m_idToCheck; };
	    Count m_idToCheck;
      };
};

// inline function definitions

inline Count MCTreeNode::id() const { return identifier(); }
inline const MCIdManager& MCTreeNode::manager() const { return *m_idManager; }



#endif /* MCINFO_MCTREENODE_H */
