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
// $Id: instantiate_find_if_ChildHelicity_map.cc,v 1.1 1999/06/22 21:29:33 lkg Exp $
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

// instantiate the binder class to be used in the find algorithm
typedef greater_equal< pair<const _map_key_,_map_contents_> > _binary_predicate_ ;

// instantiate the find algorithm used
typedef STL_MAP(_map_key_,_map_contents_)::iterator _find_if_iterator_ ;
typedef binder2nd< _binary_predicate_ >             _find_if_predicate_ ;
#include "STLUtility/instantiate_find_if.h"
