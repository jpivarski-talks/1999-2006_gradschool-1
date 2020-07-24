// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_map_of_Helicity_CosThetaDep.cc
// 
// Description: Instantiate a map w/ a Helicity (Double) key holding
//              a CosThetaDep (vector<double>)
//
//
#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#include <vector>
#include <functional>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCTypes.h"
#include "MCInfo/MCParticleProperty/SimpleAngularHelicity.h"

// STL classes
#include <map>
#include <vector>
#include <functional>

// forward declarations
#include "STLUtility/fwd_map.h"
#include "STLUtility/fwd_vector.h"

// CosThetaDep is a vector<double>.  This gets instantiated elsewhere,
// so don't do it here.

// instantiate the map itself, though
#define DO_EQUAL_INSTANTIATION
typedef Helicity _map_key_;
typedef SimpleAngularHelicity::CosThetaDep _map_contents_;
typedef less<_map_key_>      _map_compare_;
#include "STLUtility/instantiate_map.h"
