// -*- C++ -*-
//
// Package:     TriggerInfoProd
// Module:      T_TriggerInfo
// 
// Description: Instantiate Classes for TriggerInfo
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Apr  5 12:24:26 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// user include files
#include "TriggerInfoProd/TriggerInfo.h"

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE( TriggerInfo )
//Use the following if 'TriggerInfo' contains a ','
// also make sure there are no blank spaces within 'TriggerInfo'
/* INSTANTIATE_ONE_1_COMMA( TriggerInfo ) */
#include "FrameAccess/instantiate_one.h"

#include "TriggerInfoProd/TriggerInfoStorageHelper.h"
SM_REGISTER_STORAGE(TriggerInfoStorageHelper)
