// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_vector_of_HelicityConfig.cc
// 
// Description: Instantiate a vector holding HelicityConfig
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_vector_of_HelicityConfig.cc,v 1.2 1999/07/06 19:32:04 lkg Exp $
//
// Revision history
//
// $Log: T_vector_of_HelicityConfig.cc,v $
// Revision 1.2  1999/07/06 19:32:04  lkg
// Modify/add instantiation files for change of Helicity from int -> double
//
// Revision 1.1  1999/06/22 21:29:29  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:11:22  lkg
// Initial MCInfo sources
//

#include "Experiment/Experiment.h"

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCParticleProperty/SimpleHelicity.h"

// STL classes
#include <vector>
#include <map>
#include <string>

// forward declarations
#include "STLUtility/fwd_vector.h"

#define DO_EQUAL_INSTANTIATION
typedef SimpleHelicity::HelicityConfig _vector_contents_;
#include "STLUtility/instantiate_vector.h"
