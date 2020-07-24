// -*- C++ -*-
//
// Package:     MCInfo
// Module:      T_DriverMCDecayTree
// 
// Description: Instantiate FrameAccess Classes for MCDecayTree
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Jul  8 14:52:49 EDT 1999
// $Id: T_MCDecayTree.cc,v 1.3 2000/07/07 15:01:51 lkg Exp $
//
// Revision history
//
// $Log: T_MCDecayTree.cc,v $
// Revision 1.3  2000/07/07 15:01:51  lkg
// add various include <stack> to fix OSF compilation
//
// Revision 1.2  2000/05/01 22:50:43  lkg
// StorageHelper-related changes: added valueType arg for MCListItr typedefs and == and != operators
//
// Revision 1.1  1999/07/22 14:05:54  lkg
// Instantiation for an FAItem< MCDecayTree >
//
//

#include "Experiment/Experiment.h"

#include <deque>

// user include files
#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/Storage/MCDecayTreeStorageHelper.h"
#include "MCInfo/Storage/MCParticleStorageHelper.h"
#include "MCInfo/Storage/MCVertexStorageHelper.h"

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE( MCDecayTree )
//Use the following if 'MCDecayTree' contains a ','
// also make sure there are no blank spaces within 'MCDecayTree'
/* INSTANTIATE_ONE_1_COMMA( MCDecayTree ) */
#include "FrameAccess/instantiate_one.h"

// define static global variables for the various storage helpers, which
// causes the helpers to register themselves with "the system"
// (normally we peons would simply call SM_REGISTER_STORAGE( xxx ))
static MCDecayTreeStorageHelper s_MCDecayTreeStorageHelper;
static MCVertexStorageHelper    s_MCVertexStorageHelper;
static MCParticleStorageHelper  s_MCParticleStorageHelper( s_MCDecayTreeStorageHelper, s_MCVertexStorageHelper );
