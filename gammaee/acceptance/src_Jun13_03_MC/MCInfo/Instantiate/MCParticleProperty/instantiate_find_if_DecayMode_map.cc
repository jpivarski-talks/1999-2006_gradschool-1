// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      instantiate_find_if_DecayMode_map.cc
// 
// Description: Instantiate the find_if function to pick an MCDecayMode from
//              a map w/ an (integrated) Likelihood as key
//
//
// Author:      Lawrence Gibbons
// Created:     Thu Jun 10 16:08:05 EST 1999
// $Id: instantiate_find_if_DecayMode_map.cc,v 1.1 1999/06/22 21:29:34 lkg Exp $
//
// Revision history
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCParticleProperty/MCDecayMode.h"

// STL classes
#include <map>

// forward declarations
#include "STLUtility/fwd_map.h"

typedef Likelihood _map_key_;
typedef const MCDecayMode* _map_contents_;

// instantiate the binder class to be used in the find algorithm
typedef greater_equal< pair<const _map_key_,_map_contents_> > _binary_predicate_ ;

// instantiate the find algorithm used
typedef STL_MAP(_map_key_,_map_contents_)::iterator _find_if_iterator_ ;
typedef binder2nd< _binary_predicate_ >             _find_if_predicate_ ;
#include "STLUtility/instantiate_find_if.h"
