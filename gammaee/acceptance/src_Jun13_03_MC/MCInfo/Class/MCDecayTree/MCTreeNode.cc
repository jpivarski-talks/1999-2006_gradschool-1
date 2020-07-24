// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCTreeNode
// 
// Description: base class for nodes in a decay tree: deals with the ID's
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris Jones / Lawrence Gibbons
// Created:     Sat Mar 20 15:17:31 EST 1999
// $Id: MCTreeNode.cc,v 1.4 2002/09/20 17:51:41 bkh Exp $
//
// Revision history
//
// $Log: MCTreeNode.cc,v $
// Revision 1.4  2002/09/20 17:51:41  bkh
// Undo previous change -- not necessary
//
// Revision 1.2  2002/02/05 03:33:27  lkg
// add public const access to MCIdManager, better Id initialization
//
// Revision 1.1  1999/06/22 21:28:50  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCDecayTree/MCTreeNode.h"
#include "MCInfo/MCDecayTree/MCIdManager.h"

// STL classes


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCTreeNode" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCTreeNode.cc,v 1.4 2002/09/20 17:51:41 bkh Exp $";
static const char* const kTagString = "$Name: v03_09_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCTreeNode::MCTreeNode( MCTreeNode *theParent ) :
   m_idManager(), m_treeId( MCIdManager::startingIdentifier() )
{
   if ( theParent != 0 ) {
      // if this Node has a parent, use the same id Manager as the parent
      m_idManager = &(theParent->manager());
   } else {
      // this Node has no parent, so make it the top of the Tree w/ a new
      // id manager
      m_idManager = new MCIdManager( this );
//      assert( m_idManager != 0 );
   }
}

MCTreeNode::~MCTreeNode()
{
}

//
// member functions
//
void
MCTreeNode::setId( Count newId ) { m_treeId = newId; }

MCIdManager&
MCTreeNode::manager() { return *m_idManager; }

void
MCTreeNode::setManager( MCIdManager& newManager ) {
   m_idManager = &newManager;
}

//
// const member functions
//
Count
MCTreeNode::identifier() const { return m_treeId; }

//
// static member functions
//
