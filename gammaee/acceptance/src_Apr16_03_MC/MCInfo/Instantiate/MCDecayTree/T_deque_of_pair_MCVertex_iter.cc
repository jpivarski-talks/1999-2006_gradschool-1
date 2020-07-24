// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_deque_of_pair_MCParticle_iter.cc
// 
// Description: Instantiate a deque of a pair of MCVertex::const_iterator's
//
//
// Author:      Lawrence Gibbons
// Created:     Thu Jun  17 20:48:05 EST 1999
// $Id: T_deque_of_pair_MCVertex_iter.cc,v 1.1 1999/06/22 21:29:12 lkg Exp $
//
// Revision history
//
// $Log: T_deque_of_pair_MCVertex_iter.cc,v $
// Revision 1.1  1999/06/22 21:29:12  lkg
// First real version of MCInfo in repository
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCDecayTree/MCVertex.h"

// STL classes
#include <deque>


template class pair< MCVertex::const_iterator, MCVertex::const_iterator >;

typedef pair< MCVertex::const_iterator, MCVertex::const_iterator >
                                                           _deque_contents_;

#include "STLUtility/instantiate_deque.h"
