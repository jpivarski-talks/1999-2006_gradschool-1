// -*- C++ -*-
//
// Package:     MCResponse
// 
// Description: Instantiate STL classes for MCDRTQTResponse
//
//
// Author:      Adam Lyon
// Created:     22 Oct 99
// $Id: STL_vectorOfMCDRTQT.cc,v 1.1 1999/11/02 23:59:38 lyon Exp $
//
// Revision history
//
// $Log: STL_vectorOfMCDRTQT.cc,v $
// Revision 1.1  1999/11/02 23:59:38  lyon
// Moved from MCResponse
//
// Revision 1.1  1999/10/26 22:10:47  lyon
// Files necessary for MCDRTQTResponse
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
#include "MCRawData/MCDRTQT.h"

typedef  MCDRTQT* _vector_contents_;

#include "STLUtility/instantiate_vector.h"
