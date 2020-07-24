// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      T_vector_WtdElt.cc
// 
// Description: instantiate vector
//
// Implementation:
//
// Author:      Brian Heltsley
// Created:     Thu Nov 05 15:21:27 EST 1998
//
// Revision history
//
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Geant3MaterialsMediaProd/G3iMakeMaterials.h"

// STL classes
#include <vector>

typedef G3iMakeMaterials::WtdElt _vector_contents_;

#include "STLUtility/instantiate_vector.h"


