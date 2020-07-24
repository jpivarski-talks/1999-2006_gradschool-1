#if !defined(MCINFO_HELICITYCONFIG_H)
#define MCINFO_HELICITYCONFIG_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      HelicityConfig
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar  6 18:05:13 EST 1999
// $Id: HelicityConfig.h,v 1.1 1999/06/22 21:30:11 lkg Exp $
//
// Revision history
//
// $Log: HelicityConfig.h,v $
// Revision 1.1  1999/06/22 21:30:11  lkg
// First real version of MCInfo in repository
//

// system include files
//#include <iostream.h>

// user include files
#include "MCInfo/MCTypes.h"

// STL
#include <vector>
#include <map>
//#include <string>

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"

struct HelicityConfig {
      Likelihood                       configProbability;
      STL_MAP( string, Helicity )      helicities;
//	    HelicityConfig::ChildHelicities  helicities;
      
      HelicityConfig() :
	 configProbability( 0 ),
	 helicities() {};
      
      HelicityConfig(Likelihood theProb,
		     const STL_MAP( string, Helicity )& theConfig) :
	 configProbability( theProb ),
	 helicities( theConfig ) {};
      
      HelicityConfig( const HelicityConfig& rhs ) :
	 configProbability( rhs.configProbability ),
	 helicities( rhs.helicities ) {};
      
      ~HelicityConfig() {};
};

#endif /* MCINFO_HELICITYCONFIG_H */
