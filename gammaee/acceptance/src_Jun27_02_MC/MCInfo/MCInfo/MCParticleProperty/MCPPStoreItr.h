// -*- C++ -*-
#if !defined(MCINFO_MCPPSTOREITR_H)
#define MCINFO_MCPPSTOREITR_H
//
// Package:     <MCInfo>
// Module:      MCPPStoreItr
// 
/**\class MCPPStoreItr MCPPStoreItr.h MCInfo/MCPPStoreItr.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Fri Apr  6 13:22:41 EDT 2001
// $Id: MCPPStoreItr.h,v 1.1 2001/05/12 17:45:28 lkg Exp $
//
// Revision history
//
// $Log: MCPPStoreItr.h,v $
// Revision 1.1  2001/05/12 17:45:28  lkg
// implement a dereferencing iterator for the particle property store, and provide begin and end member fcn's for it
//

// system include files

// user include files
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCDecayTree/MCListItr.h"

// forward declarations
#include "STLUtility/fwd_vector.h"

class MCPPStoreItr : 
   public MCListItr< 
             STL_VECTOR( MCParticleProperty* )::const_iterator, 
             const MCParticleProperty, 
             MCParticleProperty >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef STL_VECTOR( MCParticleProperty* )::const_iterator baseItr;
      typedef MCListItr< STL_VECTOR( MCParticleProperty* )::const_iterator, 
	                 const MCParticleProperty, 
	                 MCParticleProperty > derefItr;

      // ---------- Constructors and destructor ----------------

      MCPPStoreItr( baseItr anIterator = baseItr(), 
		    baseItr endIterator = baseItr() );

      // copy constructor
      MCPPStoreItr( const MCPPStoreItr& rhs );

      // assignment operator
      const MCPPStoreItr& operator=( const MCPPStoreItr& rhs );


      virtual ~MCPPStoreItr();

      // ---------- member functions ---------------------------
      // These supplant those implemented in MCListItr

      MCPPStoreItr& operator++();
      MCPPStoreItr  operator++(int);

   private:
      // inhibit access to these operations for safety
      MCPPStoreItr& operator--();
      MCPPStoreItr  operator--(int);
      
      // ---------- data members -------------------------------
      baseItr m_trueEndItr;
};

#endif /* MCINFO_MCPPSTOREITR_H */
