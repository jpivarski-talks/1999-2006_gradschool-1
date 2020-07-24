// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_vector_of_MCDecayMode.cc
// 
// Description: Instantiate a vector holding MCDecayMode
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_vector_of_MCDecayMode.cc,v 1.1 1999/06/22 21:29:30 lkg Exp $
//
// Revision history
//
// $Log: T_vector_of_MCDecayMode.cc,v $
// Revision 1.1  1999/06/22 21:29:30  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:11:22  lkg
// Initial MCInfo sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCParticleProperty/MCDecayMode.h"

// STL classes
#include <vector>
#include <map>

// forward declarations

typedef MCDecayMode _vector_contents_;

#include "STLUtility/instantiate_vector.h"
