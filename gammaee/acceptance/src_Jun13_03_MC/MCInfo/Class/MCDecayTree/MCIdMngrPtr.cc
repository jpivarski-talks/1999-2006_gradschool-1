// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCIdMngrPtr
// 
// Description: Reference-counting pointer for the MCIdMngr class
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar 20 17:15:37 EST 1999
// $Id: MCIdMngrPtr.cc,v 1.2 2002/02/05 03:29:47 lkg Exp $
//
// Revision history
//
// $Log: MCIdMngrPtr.cc,v $
// Revision 1.2  2002/02/05 03:29:47  lkg
// add const dereferencing
//
// Revision 1.1  1999/06/22 21:28:49  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

// user include files
//#include "Experiment/report.h"
#include "MCInfo/MCDecayTree/MCIdMngrPtr.h"
#include "MCInfo/MCDecayTree/MCIdManager.h"

// STL classes

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCIdMngrPtr" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCIdMngrPtr.cc,v 1.2 2002/02/05 03:29:47 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCIdMngrPtr::MCIdMngrPtr() : m_pManager( 0 )
{}

MCIdMngrPtr::MCIdMngrPtr( MCIdManager* aManager ) :
   m_pManager( aManager ) 
{
   if ( 0 != m_pManager ) { m_pManager->addReference(); }
}

MCIdMngrPtr::MCIdMngrPtr( const MCIdMngrPtr& rhs ) :
   m_pManager( rhs.m_pManager ) 
{
   if ( 0 != m_pManager ) { m_pManager->addReference(); }
}

MCIdMngrPtr::~MCIdMngrPtr()
{
   // eliminate the reference to the manager that "this" pointer
   // currently points at (if any)
   if ( 0 != m_pManager ) {
      m_pManager->removeReference();
      // delete that manager if this was the last pointer to it
      if ( ! (m_pManager->hasRefs()) ) { delete m_pManager; }
   }
}

//
// assignment operators
//
const MCIdMngrPtr& MCIdMngrPtr::operator=( const MCIdMngrPtr& rhs ) {

  if( this != &rhs ) {
     // first, eliminate the reference to the manager that "this" pointer
     // currently points at (if any)
     if ( 0 != m_pManager ) {
	m_pManager->removeReference();
	// delete that manager if this was the last pointer to it
	if ( ! (m_pManager->hasRefs()) ) { delete m_pManager; }
     }

     // now update pointer, to "rhs"'s pointer, and update the reference
     // count of the manager (if any) to which "this" now points
     m_pManager = rhs.m_pManager;
     if ( m_pManager != 0 ) { m_pManager->addReference(); }
  }

  return *this;
}

//
// member functions
//
MCIdManager& 
MCIdMngrPtr::operator*() {
 
   assert( 0 != m_pManager );
   return *m_pManager;
}
//
// const member functions
//
const MCIdManager& 
MCIdMngrPtr::operator*() const {
 
   assert( 0 != m_pManager );
   return *m_pManager;
}

DABoolean 
MCIdMngrPtr::operator==( const MCIdMngrPtr& anotherPtr ) {
   return m_pManager == anotherPtr.m_pManager;
}

DABoolean 
MCIdMngrPtr::operator!=( const MCIdMngrPtr& anotherPtr ) {
   return m_pManager != anotherPtr.m_pManager;
}

//
// static member functions
//
