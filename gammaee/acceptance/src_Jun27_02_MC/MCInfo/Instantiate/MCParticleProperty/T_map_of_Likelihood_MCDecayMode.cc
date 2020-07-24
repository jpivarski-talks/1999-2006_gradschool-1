// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_map_of_MCDecayMode.cc
// 
// Description: Instantiate a map w/ a Likelihood key holding MCDecayMode*
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_map_of_Likelihood_MCDecayMode.cc,v 1.1 1999/06/22 21:29:27 lkg Exp $
//
// Revision history
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCParticleProperty/MCDecayMode.h"

// STL classes
#include <map>
#include <vector>

// forward declarations

// instantiate the map
typedef Likelihood _map_key_;
typedef const MCDecayMode* _map_contents_;
typedef less<_map_key_> _map_compare_;
#include "STLUtility/instantiate_map.h"
