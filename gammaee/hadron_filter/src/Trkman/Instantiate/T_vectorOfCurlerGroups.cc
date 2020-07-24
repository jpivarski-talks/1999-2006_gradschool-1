// -*- C++ -*-
//
// Package:     Trkman
// Module:      T_vectorOfCurlerGroups
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Nadia Adam
// Created:     Wed Feb 13 16:17:42 EST 2002
// $Id$
//
// Revision history
//
// $Log$
#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
//#include <utility>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Trkman/TMCurlers.h"

// STL classes
#include <vector>

typedef TMCurlers::CurlerGroup  _vector_contents_;

#include "STLUtility/instantiate_vector.h"



