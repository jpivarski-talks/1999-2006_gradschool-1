#if !defined(MCINFO_MCDECAYTREEITR_H)
#define MCINFO_MCDECAYTREEITR_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCDecayTreeItr
// 
// Description: A dereferencing fwd iterator that can traverse either the
//              MCVertex*/MCParticle* objects in an MCDecayTree
//
// Usage:
//    This is a template class meant to implement a convenient
//    iterator that can navigate the tree structure of a decay tree.
//    
//    
//
// Author:      Lawrence Gibbons
// Created:     Sat Feb 13 13:18:44 EST 1999
// $Id: MCDecayTreeItr.h,v 1.3 1999/07/22 14:07:08 lkg Exp $
//
// Revision history
//
// $Log: MCDecayTreeItr.h,v $
// Revision 1.3  1999/07/22 14:07:08  lkg
// add utility include
//
// Revision 1.2  1999/07/06 21:22:33  lkg
// implementation notes update
//
// Revision 1.1  1999/06/22 21:29:58  lkg
// First real version of MCInfo in repository
//

// system include files
#include <utility>

// user include files

// forward declarations
#include "STLUtility/fwd_deque.h"

typedef long relative_address;

template < class T, class T_iter >
class MCDecayTreeItr
{
      // ---------- private typedefs ---------------
      typedef MCDecayTreeItr< T, T_iter > self;
      typedef pair< T_iter, T_iter > tPair;

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      // default constructor
      MCDecayTreeItr();

      // constructor based on an iterator of type T_iter
      MCDecayTreeItr( const T_iter& anIterator, const T_iter& nextEndIter );

      // copy constructor
      MCDecayTreeItr( const self& rhs );

      // assignment operator
      const MCDecayTreeItr& operator=( const self& rhs );

      virtual ~MCDecayTreeItr();

      // ---------- member functions ---------------------------
      self& operator++();
      self  operator++(int);

      self& operator+=( relative_address n);
      
      // ---------- const member functions ---------------------

      // dereferencing operators
      T& operator*();
      T* operator->();

      // comparison operators
      DABoolean operator==( const self& anMCDecayTreeItr ) const;
      DABoolean operator!=( const self& anMCDecayTreeItr ) const;

      // iterator addition
      self  operator+(  relative_address n) const;

      // ---------- static member functions --------------------
      static self endIterator() { return MCDecayTreeItr< T, T_iter >(); };
	  
   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- private member functions -------------------
      void updateQueue();
      void oneNodeQueueUpdate( const T& aNode );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // is this an end Iterator?
      DABoolean m_endIterator;

      // hold an iterator over intermediate containers of objects
      // of type T
      T_iter m_iterator;
      
      // need to store the end of the temporary container
      T_iter m_subcontainerEnd;
      
      // queue for the container boundaries.  To get the desired numbering
      // scheme, when a container is popped off of the queue, each
      // object A (of type T) is queried **in reverse order** about the
      // containers (of T) held by the each of the T_hidden objects held
      // by A
      STL_DEQUE( tPair )& m_moreToCome;
      
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "MCInfo/MCDecayTree/Template/MCDecayTreeItr.cc"
#endif

#endif /* MCINFO_MCDECAYTREEITR_H */
