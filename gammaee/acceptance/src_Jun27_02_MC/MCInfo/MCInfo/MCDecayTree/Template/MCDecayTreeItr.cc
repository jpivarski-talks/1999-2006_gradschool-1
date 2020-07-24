// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCDecayTreeItr
// 
// Description: A dereferencing fwd iterator that can traverse either the
//              MCVertex*/MCParticle* objects in an MCDecayTree
//
// Implementation:
//     The iterator makes use of iterators defined for the container-like
//     nature of MCVertex (which holds MCParticle*) and MCParticle (which
//     holds MCVertex*).  This implementation assumes that the class
//     T is a container for a second class, T_hidden, which in turn
//     acts as a container of objects of type T.  For example, MCParticle
//     acts as a container of MCVertex objects, while each MCVertex
//     object is a container of MCParticle objects.  If we wish only to see
//     the MCParticle objects in the MCDecayTree, then MCVertex would be
//     the T_hidden class in the following description.
//
//     As one iterates over objects of the class T (eg. MCParticles), 
//     which holds objects of type T_hidden (eg. MCVertexes), a queue is 
//     created by querying T_hidden's  begin() and end() iterators.  T_hidden,
//     recall, is a container of more objects of type T.  One therefore
//     iterates over a T_hidden container, and when the end of one container
//     is reached, a new one is popped off of the queue, and iteration
//     resumes over that new container.
//     
//     When the queue of begin/end iterators is exhausted, a null iterator
//     with the m_endIterator flag set **true**  is returned.  This is
//     the instance of iterator returned by the default constructor, so
//     the "end()" function of a container using this iterator can be
//     implemented by returning an MCDecayTreeItr created via the
//     default constructor.
//
//     The comparison operation first checks whether both LHS and RHS of
//     the comparison have m_endIterator "true".  In that case, the
//     iterators are declared equal.  If both are false, then the
//     T_iter iterators must be equal.
//     
//     
//
// Author:      Lawrence Gibbons
// Created:     Sat Feb 13 17:09:44 EST 1999
// $Id: MCDecayTreeItr.cc,v 1.2 1999/07/06 21:33:01 lkg Exp $
//
// Revision history
//
// $Log: MCDecayTreeItr.cc,v $
// Revision 1.2  1999/07/06 21:33:01  lkg
// Rework operator++ and updateQueue to get sensible ordering given the
// MCTreeId's assigned to the particles/vertexes
//
// Revision 1.1  1999/06/22 21:30:08  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCDecayTree/MCDecayTreeItr.h"

// STL classes
#include <deque>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCDecayTreeItr" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCDecayTreeItr.cc,v 1.2 1999/07/06 21:33:01 lkg Exp $";
static const char* const kTagString = "$Name: v03_02_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
template< class T, class T_iter >
MCDecayTreeItr< T, T_iter >::MCDecayTreeItr() :
   m_endIterator( true ),
   m_moreToCome( *new STL_DEQUE( tPair ) ) {

   // make sure we could create the deque.
   if( 0 == &m_moreToCome )
   {
      report( EMERGENCY, kFacilityString )
	 << "out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }  
}

template< class T, class T_iter >
MCDecayTreeItr< T, T_iter >::MCDecayTreeItr( const T_iter& anIterator, 
					     const T_iter& nextEndIter ) :
   m_iterator( anIterator ),
   m_subcontainerEnd( nextEndIter ),
   m_endIterator( false ),
   m_moreToCome( *new STL_DEQUE( tPair ) ) {
   // make sure we could create the deque.
   if( 0 == &m_moreToCome )
   {
      report( EMERGENCY, kFacilityString )
	 << "out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }  

   if ( anIterator != nextEndIter ) {
      // get the deque initialized with the current container's information
      updateQueue();
   } else {
      m_endIterator = true;
   }
}

template< class T, class T_iter >
MCDecayTreeItr< T, T_iter >::MCDecayTreeItr( const MCDecayTreeItr& rhs ) :
   m_endIterator( rhs.m_endIterator ),
   m_iterator( rhs.m_iterator ),
   m_subcontainerEnd( rhs.m_subcontainerEnd ),
   m_moreToCome( *new STL_DEQUE( tPair )( rhs.m_moreToCome ) ) {
   // make sure we could create the deque.
   if( 0 == &m_moreToCome )
   {
      report( EMERGENCY, kFacilityString )
	 << "out of memory" << endl;
      assert( false );
      ::exit( 1 );
   }  
}

template< class T, class T_iter >
MCDecayTreeItr< T, T_iter >::~MCDecayTreeItr()
{
   delete &m_moreToCome;
}

//
// assignment operators
//
template< class T, class T_iter >
const MCDecayTreeItr< T, T_iter >& 
MCDecayTreeItr< T, T_iter >::operator=(const MCDecayTreeItr& rhs)
{
  if( this != &rhs ) 
  {
     m_endIterator     = rhs.m_endIterator;
     m_iterator        = rhs.m_iterator;
     m_subcontainerEnd = rhs.m_subcontainerEnd;
     m_moreToCome      = rhs.m_moreToCome;
  }
  return *this;
}

//
// member functions
//
template< class T, class T_iter >
MCDecayTreeItr< T, T_iter >&
MCDecayTreeItr< T, T_iter >::operator++()        // prefix
{
   // if we are already at the end, quit
   if ( m_endIterator ) { return *this; }

   // (pre!)increment the iterator, checking if we hit the end of the
   // current container
   if ( ++m_iterator == m_subcontainerEnd ) {

      // if there are no further containers in the queue, POOF!, the
      // iterator turns into an end iterator
      if ( m_moreToCome.empty() ) {
	 m_endIterator = true;
      } else {

	 // get access to the top begin/end pair
	 tPair& containerOnDeck( m_moreToCome.front() );
	 // update the current container
	 m_iterator        = containerOnDeck.first;
	 m_subcontainerEnd = containerOnDeck.second;
	 // pop the begin/end pair off of the top of the deque
	 m_moreToCome.pop_front();
      
	 // bring the queue up-to-date with the info in the new container
	 updateQueue();
      } // m_moreToCome.empty()
   } // pre-incremented m_iterator comparison

      return *this;
}

template< class T, class T_iter >
void
MCDecayTreeItr< T, T_iter >::oneNodeQueueUpdate( const T& aNode ) {

   // Iterate over all of the objects of type T_hidden contained by
   // the object "aNode".  Reminder -- T is a container of T_hidden objects
   typename T::const_reverse_iterator done = aNode.rend();
   for ( typename T::const_reverse_iterator iterT = aNode.rbegin();
	 iterT != done;
	 ++iterT ) {
      // Query each T_hidden to see if it holds any objects of type T
      // --- form a begin/end iterator pair
      tPair beginEnd( iterT->begin(), iterT->end() );
      // -- if the container isn't empty, push the pair onto the queue's end
      if ( beginEnd.first != beginEnd.second ) {
	 m_moreToCome.push_front( beginEnd );
      }
   } // iterT loop

}

template< class T, class T_iter >
void
MCDecayTreeItr< T, T_iter >::updateQueue() {
   // if this is an "end" iterator, do nothing
   if ( m_endIterator ) return;

   // we need to "reverse iterate" over the objects in the current
   // container, to get the containers of their children pushed
   // onto the queue in the desired order.  The following implementation
   // **assumes** that T_iter is a **bidrectional iterator**.  This is
   // true for the MCListItr class as implemented.
   //
   // It is assumed that updateQueue will be invoked as soon as a new
   // container has been entered, so m_iterator will point at the first
   // element of the container
   T_iter last( m_subcontainerEnd );
   while ( m_iterator != last ) { oneNodeQueueUpdate( *--last ); }
}

template< class T, class T_iter >
MCDecayTreeItr< T, T_iter >
MCDecayTreeItr< T, T_iter >::operator++(int)     // postfix
{
   MCDecayTreeItr< T, T_iter > before( *this );
   ++(*this); // use prefix operator
   return( before );
}


template< class T, class T_iter >
MCDecayTreeItr< T, T_iter >&
MCDecayTreeItr< T, T_iter >::operator+=( relative_address n )
{
   for ( relative_address i = 0; i != n; ++i, ++*this ) {}
   return *this;
}


//
// const member functions
//

template< class T, class T_iter >
T&
MCDecayTreeItr< T, T_iter >::operator*() {
   if ( m_endIterator ) {
      report( WARNING, kFacilityString )
	 << "Attempt to dereference an MCDecayTree end() iterator"
	 << endl;
   }
   return( *m_iterator );
}


template< class T, class T_iter >
T*
MCDecayTreeItr< T, T_iter >::operator->() {
   return( m_iterator.operator->() );
}


template< class T, class T_iter >
DABoolean
MCDecayTreeItr< T, T_iter >::operator==( const self& anItr ) const {
   // two "end iterators" are by definition equal
   if ( m_endIterator && anItr.m_endIterator )
   {
      return true;
   }

   // an "end iterator" and a "normal" iterator are not equal.  We now from
   // above that at least one is *not* an "end iterator"
   if ( m_endIterator || anItr.m_endIterator )
   {
      return false;
   }

   // if both are "normal" iterators, they are equal if they point
   // at the same object
   return ( m_iterator == anItr.m_iterator );
}


template< class T, class T_iter >
DABoolean
MCDecayTreeItr< T, T_iter >::operator!=( const self& anItr ) const {
   return !( *this == anItr ); // use ==
}


template< class T, class T_iter >
MCDecayTreeItr< T, T_iter >
MCDecayTreeItr< T, T_iter >::operator+( relative_address n ) const {
   MCDecayTreeItr< T, T_iter > tempItr( *this );
   for( relative_address i = 0; i != n; ++i, ++tempItr ) {}
   return tempItr;
}


//
// static member functions
//
