// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      instantiate_transform_conjugate.cc
// 
// Description: instantiate the STL transform algorithm used for transforming
//              a vector of QQ_id to the Id's of the conjugate particle
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: instantiate_transform_conjugate.cc,v 1.1 1999/06/22 21:29:36 lkg Exp $
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
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

// STL classes
#include <vector>
#include <algorithm>
#include <functional>

// forward declarations
#include "STLUtility/fwd_vector.h"

// instantiate the unary fcn class needed
typedef QQ_id _unary_function_arg_ ;
typedef QQ_id _unary_function_result_ ;
#include "STLUtility/instantiate_unary_function.h"

// instantiate the transform  algorithm used
typedef STL_VECTOR( _unary_function_arg_ )::const_iterator
                                               _transform_in_iterator_ ;
typedef STL_VECTOR( _unary_function_result_ )::iterator
                                               _transform_out_iterator_ ;
typedef MCParticlePropertyStore::TransQQToConj _transform_unary_fcn_ ;
#include "STLUtility/instantiate_transform_specific_unary.h"
