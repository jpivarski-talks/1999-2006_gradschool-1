// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      instantiate_equal_vector_double.cc
// 
// Description: instantiate the STL transform algorithm used for transforming
//              a vector of QQ_id to the Id's of the conjugate particle
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: instantiate_equal_MCPPStoreItr.cc,v 1.1 2001/12/19 18:20:16 lkg Exp $
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

// STL classes
#include <vector>
#include <algorithm>
#include <functional>

// user includes
#include "MCInfo/MCParticleProperty/MCPPStoreItr.h"

// instantiate the equal  algorithm
typedef MCPPStoreItr  _equal_iterator1_type_ ;
typedef _equal_iterator1_type_ _equal_iterator2_type_ ;
#include "STLUtility/instantiate_equal.h"
