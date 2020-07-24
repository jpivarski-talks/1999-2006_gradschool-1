// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_vector_of_qqid.cc
// 
// Description: Instantiate a vector holding MCParticleProperty::QQ_id
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_vector_of_qqid.cc,v 1.1 1999/06/22 21:29:31 lkg Exp $
//
// Revision history
//
// $Log: T_vector_of_qqid.cc,v $
// Revision 1.1  1999/06/22 21:29:31  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:11:21  lkg
// Initial MCInfo sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCTypes.h"

// STL classes
#include <vector>

// forward declarations

typedef QQ_id _vector_contents_;

#include "STLUtility/instantiate_vector.h"
