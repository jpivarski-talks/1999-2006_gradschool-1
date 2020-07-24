// -*- C++ -*-
//
// Package:     EventTypeFilterProc
// Module:      T_sortEnergyHit
// 
// Description: instantiate algorithm sort
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Thu Apr 29 13:54:24 EDT 1999
// $Id: T_sortPairList.cc,v 1.1.1.1 2001/07/31 18:14:14 bkh Exp $
//
// Revision history
//
// $Log: T_sortPairList.cc,v $
// Revision 1.1.1.1  2001/07/31 18:14:14  bkh
// imported EventTypeFilterProc sources
//
// Revision 1.1.1.1  2001/01/17 22:21:36  bkh
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files

#include "EventTypeFilterProc/EventTypeFilterProc.h"

// STL classes
#include <vector>
#include <algorithm>

//
// constants, enums and typedefs
//

typedef EventTypeFilterProc::PairList Vec ;


typedef Vec::iterator                      _sort_iterator_      ;
typedef Vec::value_type                    _sort_value_type_    ;
typedef EventTypeFilterProc::ComparePairs  _sort_compare_class_ ;

#include "STLUtility/instantiate_sort_compare.h"




