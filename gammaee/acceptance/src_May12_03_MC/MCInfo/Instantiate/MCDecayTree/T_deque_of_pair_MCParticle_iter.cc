// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_deque_of_pair_MCParticle_iter.cc
// 
// Description: Instantiate a deque of a pair of MCParticle::const_iterator's
//
//
// Author:      Lawrence Gibbons
// Created:     Thu Jun 17 20:48:05 EST 1999
// $Id: T_deque_of_pair_MCParticle_iter.cc,v 1.1 1999/06/22 21:29:12 lkg Exp $
//
// Revision history
//
// $Log: T_deque_of_pair_MCParticle_iter.cc,v $
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
#include "MCInfo/MCDecayTree/MCParticle.h"

// STL classes
#include <deque>


template class pair< MCParticle::const_iterator, MCParticle::const_iterator >;

typedef pair< MCParticle::const_iterator, MCParticle::const_iterator >
                                                           _deque_contents_;

#include "STLUtility/instantiate_deque.h"
