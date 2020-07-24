// -*- C++ -*-
#if !defined(MCINFO_SIMPLEHELICITY_H)
#define MCINFO_SIMPLEHELICITY_H
//
// Package:     <MCInfo>
// Module:      SimpleHelicity
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar  6 18:05:13 EST 1999
// $Id: SimpleHelicity.h,v 1.4 2001/12/19 18:12:19 lkg Exp $
//
// Revision history
//
// $Log: SimpleHelicity.h,v $
// Revision 1.4  2001/12/19 18:12:19  lkg
// eliminate use of ReferenceCountingPointers. add operator[]
//
// Revision 1.3  1999/07/22 20:54:54  lkg
// Add a 3rd "special value" for helicity, since in .rp files the other 2
// special values get pegged at -63.5
//
// Revision 1.2  1999/07/06 19:41:28  lkg
// Add standard constants for cases when QQ's simple helicity is (a) undefined,
// that is, no helicity specified, or (b) a more realistic handling of the
// spin density is used in the decay mode (eg., EvtGen)
//
// Revision 1.1  1999/06/22 21:30:15  lkg
// First real version of MCInfo in repository
//

// system include files

// user include files
#include "MCInfo/MCTypes.h"

// STL
#include <vector>
#include <map>

// forward declarations
#include "C++Std/fwd_ostream.h"
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"

class SimpleHelicity
{
      // ---------- friend classes and functions ---------------
      friend ostream& operator<<( ostream&, const SimpleHelicity& );

   public:
      // ---------- constants, enums and typedefs --------------
      static const Helicity kUndefinedHelicity; // no specific helicity state
      static const Helicity kTrueHelicity;      // more realistic handling of
                                                // polarization (eg EvtGen)
      static const Helicity kRoarUndefinedHelicity; //both of above in .rp file
      typedef STL_MAP( string, Helicity ) ChildHelicities;
      friend ostream& operator<<( ostream&, 
				  const SimpleHelicity::ChildHelicities& );

      // ---------- Constructors and destructor ----------------
      SimpleHelicity();
      SimpleHelicity( const SimpleHelicity& ); // implement deep copy
      virtual ~SimpleHelicity();

      // ---------- member functions ---------------------------
      void addHelicityConfig( Likelihood, const ChildHelicities& );

      // ---------- const member functions ---------------------
      // Throw a helicity configuration: will need a random number
      // generator module for actual implementation
      const ChildHelicities& throwConfig() const;


      // equality
      DABoolean operator==( const SimpleHelicity& rhs ) const;
      DABoolean operator!=( const SimpleHelicity& rhs ) const {
	 return ! operator==( rhs );
      };

      //  *********** NOT INTENDED FOR PUBLIC USE **********
      // Instantiation woes cause this to be moved out of private:
      // a little stucture in our lives to help organization of implementation.
      struct HelicityConfig {
	    Likelihood                       configProbability;
	    SimpleHelicity::ChildHelicities  helicities;

	    HelicityConfig() :
	       configProbability( 0 ),
	       helicities() {};

	    HelicityConfig(Likelihood theProb,
			   const SimpleHelicity::ChildHelicities& theConfig) :
	       configProbability( theProb ),
	       helicities( theConfig ) {};

	    HelicityConfig( const HelicityConfig& rhs ) :
	       configProbability( rhs.configProbability ),
	       helicities( rhs.helicities ) {};
	    
	    ~HelicityConfig() {};

	    DABoolean operator==( const HelicityConfig& rhs ) const {
	       return ( (configProbability == rhs.configProbability) &&
		      (helicities == rhs.helicities) );
	    };

	    DABoolean operator!=( const HelicityConfig& rhs ) const {
	       return ! operator==( rhs );
	    };
      };

      // for storage
      int numberOfConfigs() const;
      const SimpleHelicity::HelicityConfig& operator[]( int ) const;

   private:

      // ---------- Constructors and destructor ----------------

      // ---------- assignment operator(s) ---------------------
      const SimpleHelicity& operator=( const SimpleHelicity& ); // deep copy
                                                                // if needed

      // ---------- private struct's ---------------------------

      // ---------- data members -------------------------------
      
      // for use in building the helicity list: keep the current
      // sum of the configuration probabilities added so far
      Likelihood m_probabilitySum;

      // maintain a list of each configuration.  This will get used
      // to build the configuration map as configurations are added.
      STL_VECTOR( HelicityConfig )& m_configurationList;

      // create a map of the integrated probability (normalized to
      // unity) vs each configuration
      STL_MAP( Likelihood, ChildHelicities* )& m_configurationMap;

      // for consistency checking between configurations passed
      Count m_numDaughtersExpected;
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/SimpleHelicity.cc"
//#endif

#endif /* MCINFO_SIMPLEHELICITY_H */
