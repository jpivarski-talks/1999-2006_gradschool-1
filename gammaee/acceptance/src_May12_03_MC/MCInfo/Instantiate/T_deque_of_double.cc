// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_deque_of_double.cc
// 
// Description: Instantiate a deque of Double
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_deque_of_double.cc,v 1.1 1999/06/22 21:29:01 lkg Exp $
//
// Revision history
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCTypes.h"

// STL classes
#include <deque>


typedef Double _deque_contents_;
#include "STLUtility/instantiate_deque.h"
