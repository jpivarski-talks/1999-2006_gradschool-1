// -*- C++ -*-
#if !defined(MCINFO_SIMPLEANGULARHELICITY_H)
#define MCINFO_SIMPLEANGULARHELICITY_H
//
// Package:     <MCInfo>
// Module:      SimpleAngularHelicity
// 
// Description: Describes the dN/dcosTheta distribution for the decay of
//              a particle into a particular final state when the parent is
//              in a given definite helicity state.
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar  6 21:18:56 EST 1999
// $Id: SimpleAngularHelicity.h,v 1.2 2001/12/19 18:12:19 lkg Exp $
//
// Revision history
//
// $Log: SimpleAngularHelicity.h,v $
// Revision 1.2  2001/12/19 18:12:19  lkg
// eliminate use of ReferenceCountingPointers. add operator[]
//
// Revision 1.1  1999/06/22 21:30:15  lkg
// First real version of MCInfo in repository
//

// system include files
//#include <iostream.h>

// user include files
#include "MCInfo/MCTypes.h"

// forward declarations
#include "C++Std/fwd_ostream.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"

class SimpleAngularHelicity
{
      // ---------- friend classes and functions ---------------
      friend ostream& operator<<( ostream&, const SimpleAngularHelicity& );

   public:
      // ---------- constants, enums and typedefs --------------
      typedef STL_VECTOR( Double ) CosThetaDep;
      typedef pair< const Helicity, CosThetaDep > HelicitySpec;

      // ---------- Constructors and destructor ----------------
      SimpleAngularHelicity();
      SimpleAngularHelicity( const SimpleAngularHelicity& ); // deep copy
      virtual ~SimpleAngularHelicity();

      // ---------- member functions ---------------------------

      // add configuration for a given helicity
      void addHelicityState( Helicity, const CosThetaDep& );

      // ---------- const member functions ---------------------

      // Throw a cosTheta value based on the coefficients
      // a_i stored for that configuration.
      double throwCosTheta( Helicity ) const;

      // return the a_i coefficients stored for a given helicity state
      const CosThetaDep& getHelicityParams( Helicity ) const;
      
      DABoolean operator==( const SimpleAngularHelicity& rhs ) const;
      
      // for storage
      Count numberOfConfigs() const {
	 return m_angularDistribs.size();
      }
      const HelicitySpec& operator[]( int ) const;

   private:
      static Double diceThrow();

      // ---------- Constructors and destructor ----------------

      // ---------- assignment operator(s) ---------------------
      const SimpleAngularHelicity& operator=( const SimpleAngularHelicity& ); // stop default

      static const CosThetaDep& flatParameterization();
      
      // ---------- data members -------------------------------
      STL_MAP( Helicity, CosThetaDep )& m_angularDistribs;
};

// inline function definitions

#endif /* MCINFO_SIMPLEANGULARHELICITY_H */
