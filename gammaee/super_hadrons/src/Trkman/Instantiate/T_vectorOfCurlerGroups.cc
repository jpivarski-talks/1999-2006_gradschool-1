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
// $Id: T_vectorOfCurlerGroups.cc,v 1.1 2002/11/04 18:30:13 nea9 Exp $
//
// Revision history
//
// $Log: T_vectorOfCurlerGroups.cc,v $
// Revision 1.1  2002/11/04 18:30:13  nea9
// New CleoIII Trkman files added
//
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



