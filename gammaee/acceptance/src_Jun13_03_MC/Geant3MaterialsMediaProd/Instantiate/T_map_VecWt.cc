// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      T_map_VecWt.cc
// 
// Description: Instantiate map class
//
// Implementation:
//
// Author:      Brian Heltsley
// Created:     Thu Nov 05 16:25:23 EDT 1998
//
// Revision history
//
//
//
//

#include "Experiment/Experiment.h"

// system include files

#include <string>
#include <vector>
#include <map>

#include "Geant3MaterialsMediaProd/G3iMakeMaterials.h"

typedef string                    _map_key_ ;
typedef G3iMakeMaterials::VecWt   _map_contents_ ;
typedef less< _map_key_ >         _map_compare_ ;

#include "STLUtility/instantiate_map.h"
