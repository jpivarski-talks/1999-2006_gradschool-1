// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_list_of_MCParticle.cc
// 
// Description: Instantiate a list holding MCParticle*
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_list_of_MCParticle.cc,v 1.1 1999/06/22 21:29:13 lkg Exp $
//
// Revision history
//
// $Log: T_list_of_MCParticle.cc,v $
// Revision 1.1  1999/06/22 21:29:13  lkg
// First real version of MCInfo in repository
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCDecayTree/MCParticle.h"

// STL classes
#include <vector>

// forward declarations

typedef MCParticle* _vector_contents_;

#include "STLUtility/instantiate_vector.h"
