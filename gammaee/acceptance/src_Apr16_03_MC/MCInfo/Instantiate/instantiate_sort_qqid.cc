// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      instantiate_sort_qqid.cc
// 
// Description: instantiate the STL transform algorithm used to sort a
//              vector of QQ_id
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: instantiate_sort_qqid.cc,v 1.1 1999/06/22 21:29:02 lkg Exp $
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
#include "MCInfo/MCTypes.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

// STL classes
#include <vector>
#include <algorithm>
#include <functional>

// forward declarations
#include "STLUtility/fwd_vector.h"

// do the instantiate
typedef QQ_id  _sort_value_type_ ;
typedef STL_VECTOR( _sort_value_type_ )::iterator _sort_iterator_ ;
#include "STLUtility/instantiate_sort.h"
