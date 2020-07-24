// -*- C++ -*-
//
// Package:     StupidProd
// Module:      T_Stupid
// 
// Description: Instantiate Classes for Stupid
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Mar 22 01:38:43 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// user include files
#include "StupidProd/Stupid.h"

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE( Stupid )
//Use the following if 'Stupid' contains a ','
// also make sure there are no blank spaces within 'Stupid'
/* INSTANTIATE_ONE_1_COMMA( Stupid ) */
#include "FrameAccess/instantiate_one.h"

#include "StupidProd/StupidStorageHelper.h"
SM_REGISTER_STORAGE(StupidStorageHelper)
