// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      T_map_string_UInt16
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
#include <map>

typedef string                        _map_key_ ;
typedef UInt16                        _map_contents_ ;
typedef less< _map_key_ >             _map_compare_ ;

#include "STLUtility/instantiate_map.h"
