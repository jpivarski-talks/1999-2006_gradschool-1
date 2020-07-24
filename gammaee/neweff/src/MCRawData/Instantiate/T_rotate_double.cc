// -*- C++ -*-
//
// Package:     MCRawData
// Module:      T_fill_float
// 
// Description: instantiate fill for a float
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Jun 08 15:07:04 EDT 1999
// $Id: T_rotate_double.cc,v 1.1 1999/06/10 20:22:33 bkh Exp $
//
// Revision history
//
// $Log: T_rotate_double.cc,v $
// Revision 1.1  1999/06/10 20:22:33  bkh
// Better stab at CC simulation
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <vector>
#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <vector>
#include <algorithm>

typedef double*                           _rotate_iterator_        ;
typedef vector< double >::difference_type _rotate_difference_type_ ;

#include "STLUtility/instantiate_rotate.h"
