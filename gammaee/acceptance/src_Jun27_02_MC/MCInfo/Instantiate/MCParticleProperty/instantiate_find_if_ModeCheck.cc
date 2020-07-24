// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      instantiate_find_if_ModeCheck.cc
// 
// Description: Instantiate the find_if function to find the decay mode
//              of a given kind
//
//
// Author:      Lawrence Gibbons
// Created:     Thu Jun 10 16:08:05 EST 1999
// $Id: instantiate_find_if_ModeCheck.cc,v 1.1 1999/06/22 21:29:35 lkg Exp $
//
// Revision history
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <algorithm>
#include <functional>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCParticleProperty/MCDecayMode.h"

// STL classes
#include <vector>
#include <algorithm>
#include <functional>

// forward declarations
#include "STLUtility/fwd_vector.h"

// instantiate the find algorithm used
typedef STL_VECTOR( MCDecayMode )::const_iterator _find_if_iterator_ ;
typedef MCDecayMode::ModeCheck                    _find_if_predicate_ ;
#include "STLUtility/instantiate_find_if.h"
