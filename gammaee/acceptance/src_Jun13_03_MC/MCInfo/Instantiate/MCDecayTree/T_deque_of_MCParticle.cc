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
// $Id: T_deque_of_MCParticle.cc,v 1.1 2000/07/07 18:01:21 cdj Exp $
//
// Revision history
//
// $Log: T_deque_of_MCParticle.cc,v $
// Revision 1.1  2000/07/07 18:01:21  cdj
// added instantiation of deque<MCParticle*> needed for OSF
//
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

class MCParticle;

typedef MCParticle* _deque_contents_;

#include "STLUtility/instantiate_deque.h"
