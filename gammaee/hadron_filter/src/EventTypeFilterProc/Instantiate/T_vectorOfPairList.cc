// -*- C++ -*-
//
// Package:     EventTypeFilterProc
// Module:      T_vector
// 
// Description: instantiate vector
//
// Implementation:
//
// Author:      Brian Heltsley
// Created:     Thu Apr 29 15:21:27 EST 1999
// $Id: T_vectorOfPairList.cc,v 1.1.1.1 2001/07/31 18:14:14 bkh Exp $
//
// Revision history
//
// $Log: T_vectorOfPairList.cc,v $
// Revision 1.1.1.1  2001/07/31 18:14:14  bkh
// imported EventTypeFilterProc sources
//
// Revision 1.1.1.1  2001/01/17 22:21:37  bkh
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
//#include <utility>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "EventTypeFilterProc/EventTypeFilterProc.h"

// STL classes
#include <vector>

typedef EventTypeFilterProc::PairInts  _vector_contents_;

#include "STLUtility/instantiate_vector.h"

#include "STLUtility/instantiate_vector_of_vector.h"
