// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCStablePartItr
// 
// Description: A forward iterator that iterates over only the STABLE
//              particles in a decay tree, where "stable" is defined
//              via the current QQ lifetime-based definition.  The
//              cutoff is defined by MCDecayTree::kStableCTauCutoff
//
// Implementation:
//     
//
// Author:      Lawrence Gibbons
// Created:     Sat Feb 13 17:09:44 EST 1999
// $Id: MCStablePartItr.cc,v 1.2 2001/05/11 16:58:41 lkg Exp $
//
// Revision history
//
// $Log: MCStablePartItr.cc,v $
// Revision 1.2  2001/05/11 16:58:41  lkg
// Handle particles with infinite lifetimes (flagged in QQ by ctau = -1)
// properly.
//
// Revision 1.1  1999/07/07 13:08:23  lkg
// Add an iterator over the "stable" particles in the decay tree:
// MCDecayTree::const_sIterator typedef'd to MCStablePartItr
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCDecayTree/MCStablePartItr.h"
#include "MCInfo/MCDecayTree/MCDecayTree.h"

// STL classes
#include <deque>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCStablePartItr" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCStablePartItr.cc,v 1.2 2001/05/11 16:58:41 lkg Exp $";
static const char* const kTagString = "$Name: v03_02_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCStablePartItr::MCStablePartItr() :
   m_endIterator( const_pIterator() ),
   m_iterator(    const_pIterator() ) {}

MCStablePartItr::MCStablePartItr( const const_pIterator& pItr ) :
   m_endIterator( const_pIterator() ),
   m_iterator( pItr ) {
   double ctau = (*m_iterator).properties().ctau();
   if ( (ctau >= 0) && (ctau < MCDecayTree::kStableCTauCutoff) ) {
      ++*this;
   }
}

MCStablePartItr::MCStablePartItr( const MCStablePartItr& rhs ) :
   m_endIterator( rhs.m_endIterator ),
   m_iterator(    rhs.m_iterator ) {}

MCStablePartItr::~MCStablePartItr() {}

//
// assignment operators
//
const MCStablePartItr& 
MCStablePartItr::operator=(const MCStablePartItr& rhs)
{
  if( this != &rhs ) {
     m_iterator    = rhs.m_iterator;
     m_endIterator = rhs.m_endIterator;
  }
  return *this;
}

//
// member functions
//
MCStablePartItr&
MCStablePartItr::operator++()        // prefix
{
   // preincrement, if we are already at the end, quit.  This works
   // even if we were already at the end
   if ( ++m_iterator == m_endIterator ) { return *this; }

   // use ++ recursively to get to the next stable particle
   Double myLifetime( m_iterator->properties().ctau() );
   if ( myLifetime >= 0 && myLifetime < MCDecayTree::kStableCTauCutoff ) {
      return ++(*this);
   }
   return *this;
}

MCStablePartItr
MCStablePartItr::operator++(int)     // postfix
{
   MCStablePartItr before( *this );
   ++(*this); // use prefix operator
   return( before );
}


MCStablePartItr&
MCStablePartItr::operator+=( relative_address n )
{
   for ( relative_address i = 0; i != n; ++i, ++*this ) {}
   return *this;
}


//
// const member functions
//

const MCParticle&
MCStablePartItr::operator*() {
   if ( m_iterator == m_endIterator ) {
      report( WARNING, kFacilityString )
	 << "Attempt to dereference an end() iterator"
	 << endl;
   }
   return( *m_iterator );
}


const MCParticle*
MCStablePartItr::operator->() {
   return( m_iterator.operator->() );
}


DABoolean
MCStablePartItr::operator==( const self& anItr ) const {
   return ( m_iterator == anItr.m_iterator );
}


DABoolean
MCStablePartItr::operator!=( const self& anItr ) const {
   return !( *this == anItr ); // use ==
}


MCStablePartItr
MCStablePartItr::operator+( relative_address n ) const {
   MCStablePartItr tempItr( *this );
   for( relative_address i = 0; i != n; ++i, ++tempItr ) {}
   return tempItr;
}
