// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      instantiate_find_if_pIter_CheckId.cc
// 
// Description: Instantiate the find_if function to find an MCParticle
//              with a specific ID in an MCDecayTree
//
//
// Author:      Lawrence Gibbons
// Created:     Thu Jun 10 16:08:05 EST 1999
// $Id: instantiate_find_if_MCDecayTree_pIter.cc,v 1.1 1999/06/22 21:29:17 lkg Exp $
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
#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCTreeNode.h"

// STL classes
#include <vector>
#include <algorithm>
#include <functional>

// forward declarations
#include "STLUtility/fwd_vector.h"

// instantiate the find algorithm used
typedef MCDecayTree::const_pIterator _find_if_iterator_ ;
typedef MCTreeNode::CheckId          _find_if_predicate_ ;
#include "STLUtility/instantiate_find_if.h"
