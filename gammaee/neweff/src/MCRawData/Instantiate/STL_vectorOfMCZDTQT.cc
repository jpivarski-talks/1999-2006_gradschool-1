// -*- C++ -*-
//
// Package:     MCResponse
// 
// Description: Instantiate STL classes for MCZDTQTResponse
//
//
// Author:      Guangshun Huang
// Created:     Thu Jan 23 2003
// $Id: STL_vectorOfMCZDTQT.cc,v 1.1 2003/02/04 15:23:29 huanggs Exp $
//
// Revision history
//
// $Log: STL_vectorOfMCZDTQT.cc,v $
// Revision 1.1  2003/02/04 15:23:29  huanggs
// first submission
//
//

#include "Experiment/Experiment.h"
// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif /* MULTISET_IS_SEPARATE_FILE_BUG */ 
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCRawData/MCZDTQT.h"

typedef  MCZDTQT* _vector_contents_;

#include "STLUtility/instantiate_vector.h"
