// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_deque_of_vector_of_double.cc
// 
// Description: Instantiate a deque of vector<double>
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_deque_of_vector_of_double.cc,v 1.1 1999/06/22 21:29:05 lkg Exp $
//
// Revision history
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCTypes.h"

// STL classes
#include <vector>
#include <deque>

// forward declarations
#include "STLUtility/fwd_vector.h"

// For Sun, we seem to need to play some shenanigans to get the compiler
// to autoinstantiate vector<Double>.  Otherwise, it thinks vector<Double>
// is not a complete type definition and the compiler can't autoinstantiate 
// the vector

#if defined(SUNCC)
typedef Double _vector_contents_;
#include "STLUtility/instantiate_vector.h"
#endif

// For other compilers, the vector<Double> is explicitly instantiated 
// elsewhere.  Don't instantiate here as well or we end up with symbol
// clashes in the libraries.  So, only need to instantiate the deque here.

typedef STL_VECTOR( Double ) _deque_contents_;
#include "STLUtility/instantiate_deque.h"
