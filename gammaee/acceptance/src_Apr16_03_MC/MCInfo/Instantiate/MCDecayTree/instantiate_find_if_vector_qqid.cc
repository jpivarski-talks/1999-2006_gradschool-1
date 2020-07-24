// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      instantiate_find_if_vector_qqid.cc
// 
// Description: Instantiate the find_if function to find a qqid
//              in a vector of qqid's
//
//
// Author:      Lawrence Gibbons
// Created:     Thu Jun 10 16:08:05 EST 1999
// $Id: instantiate_find_if_vector_qqid.cc,v 1.1 2001/12/21 20:30:34 lkg Exp $
//
// Revision history
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <algorithm>
#include <functional>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCTypes.h"

// STL classes
#include <vector>
#include <algorithm>
#include <functional>

// forward declarations
#include "STLUtility/fwd_vector.h"

// instantiate the binder class to be used in the find algorithm
typedef equal_to< QQ_id > _binary_predicate_ ;

// instantiate the find algorithm used
typedef STL_VECTOR( QQ_id )::iterator   _find_if_iterator_ ;
typedef binder2nd< _binary_predicate_ > _find_if_predicate_ ;
#include "STLUtility/instantiate_find_if.h"

