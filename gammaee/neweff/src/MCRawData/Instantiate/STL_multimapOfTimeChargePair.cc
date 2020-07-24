// -*- C++ -*-
//
// Package:     MCResponse
// 
// Description: Instantiate STL classes for MCDRTQT
//
//
// Author:      Adam Lyon
// Created:     22 Oct 99
// $Id: STL_multimapOfTimeChargePair.cc,v 1.1 1999/11/02 23:59:38 lyon Exp $
//
// Revision history
//
// $Log: STL_multimapOfTimeChargePair.cc,v $
// Revision 1.1  1999/11/02 23:59:38  lyon
// Moved from MCResponse
//
// Revision 1.1  1999/10/26 22:10:46  lyon
// Files necessary for MCDRTQT
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif /* MULTISET_IS_SEPARATE_FILE_BUG */ 
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif /* MULTISET_IS_SEPARATE_FILE_BUG */ 

// user include files

#include "MCRawData/MCDRTQT.h"
typedef  TimeChargePair _multiset_contents_;
typedef  less<TimeChargePair> _multiset_compare_;

#include "STLUtility/instantiate_multiset.h"
