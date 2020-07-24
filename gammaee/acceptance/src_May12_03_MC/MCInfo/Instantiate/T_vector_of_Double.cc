// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_vector_of_Double.cc
// 
// Description: Instantiate a vector holding Double
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_vector_of_Double.cc,v 1.1 1999/06/22 21:29:02 lkg Exp $
//
// Revision history
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// STL classes
#include <vector>

typedef Double _vector_contents_;
#include "STLUtility/instantiate_vector.h"
