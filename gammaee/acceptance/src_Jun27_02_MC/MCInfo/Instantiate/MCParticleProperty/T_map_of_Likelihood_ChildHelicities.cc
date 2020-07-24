// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_map_of_pdgid_qqid.cc
// 
// Description: Instantiate a map w/ a string key holding QQ_id's
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_map_of_Likelihood_ChildHelicities.cc,v 1.1 1999/06/22 21:29:26 lkg Exp $
//
// Revision history
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCParticleProperty/SimpleHelicity.h"

// STL classes
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

// instantiate the map
typedef Likelihood _map_key_;
typedef SimpleHelicity::ChildHelicities* _map_contents_;
typedef less<_map_key_> _map_compare_;
#include "STLUtility/instantiate_map.h"

// instantiate the binder class to be used in the find algorithm
typedef greater_equal< pair<_map_key_,_map_contents_> > _binary_predicate_ ;

