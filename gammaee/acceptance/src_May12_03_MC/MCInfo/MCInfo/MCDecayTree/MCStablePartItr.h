#if !defined(MCINFO_MCSTABLEPARTITR_H)
#define MCINFO_MCSTABLEPARTITR_H
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
//
//    
//
// Author:      Lawrence Gibbons
// Created:     Sat Feb 13 13:18:44 EST 1999
// $Id: MCStablePartItr.h,v 1.1 1999/07/07 13:09:47 lkg Exp $
//
// Revision history
//
// $Log: MCStablePartItr.h,v $
// Revision 1.1  1999/07/07 13:09:47  lkg
// Add an iterator over the "stable" particles in the decay tree:
// MCDecayTree::const_sIterator typedef'd to MCStablePartItr
//
// Revision 1.2  1999/07/06 21:22:33  lkg
// implementation notes update
//
// Revision 1.1  1999/06/22 21:29:58  lkg
// First real version of MCInfo in repository
//

// system include files

// user include files
#include "MCInfo/MCDecayTree/MCDecayTreeItr.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCVertex.h"

// forward declarations

typedef long relative_address;

class MCStablePartItr
{
      // ---------- private typedefs ---------------
      typedef MCStablePartItr self;

   public:
      // ---------- constants, enums and typedefs --------------
      // iterator over particles in the tree
      typedef MCDecayTreeItr< const MCParticle, 
	                      MCVertex::const_pIterator >   const_pIterator;


      // ---------- Constructors and destructor ----------------
      // default constructor
      MCStablePartItr();

      // constructor based on an iterator of type T_iter
      MCStablePartItr( const const_pIterator& pItr );

      // copy constructor
      MCStablePartItr( const self& rhs );

      // assignment operator
      const MCStablePartItr& operator=( const self& rhs );

      virtual ~MCStablePartItr();

      // ---------- member functions ---------------------------
      self& operator++();
      self  operator++(int);

      self& operator+=( relative_address n);
      
      // ---------- const member functions ---------------------

      // dereferencing operators
      const MCParticle& operator*();
      const MCParticle* operator->();

      // comparison operators
      DABoolean operator==( const self& anMCStablePartItr ) const;
      DABoolean operator!=( const self& anMCStablePartItr ) const;

      // iterator addition
      self  operator+(  relative_address n) const;

      // ---------- static member functions --------------------
      static self endIterator() { return MCStablePartItr(); };
	  
   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      const_pIterator m_iterator;
      const_pIterator m_endIterator;
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "MCInfo/MCDecayTree/Template/MCStablePartItr.cc"
#endif

#endif /* MCINFO_MCSTABLEPARTITR_H */
