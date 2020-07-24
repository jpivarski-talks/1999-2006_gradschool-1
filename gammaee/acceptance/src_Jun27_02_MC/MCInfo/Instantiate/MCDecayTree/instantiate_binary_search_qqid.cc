// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      instantiate_binary_search_qqid.cc
// 
// Description: instantiate the STL binary search algorithm used for a vector
//              if QQ_id
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Jun 12 14:31:05 EST 1998
// $Id: instantiate_binary_search_qqid.cc,v 1.1 1999/06/22 21:29:16 lkg Exp $
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

// instantiate the unary fcn class needed
typedef QQ_id  _binary_search_value_type_ ;
typedef STL_VECTOR( _binary_search_value_type_ )::iterator
                                                     _binary_search_iterator_ ;
#include "STLUtility/instantiate_binary_search.h"
