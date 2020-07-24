// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_equal_vector_of_qqid.cc
// 
// Description: Instantiate the equal fcn to compare two vectors holding QQ_id
//
// Author:      Lawrence Gibbons
// Created:     Sun Apr 25 22:29:00 EDT 1999
// $Id: T_equal_vector_of_qqid.cc,v 1.1 1999/06/22 21:29:25 lkg Exp $
//
// Revision history
//
// $Log: T_equal_vector_of_qqid.cc,v $
// Revision 1.1  1999/06/22 21:29:25  lkg
// First real version of MCInfo in repository
//
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
#include "STLUtility/fwd_vector.h"

typedef STL_VECTOR( QQ_id )::iterator _equal_iterator1_type_;
typedef STL_VECTOR( QQ_id )::iterator _equal_iterator2_type_;

#include "STLUtility/instantiate_equal.h"
