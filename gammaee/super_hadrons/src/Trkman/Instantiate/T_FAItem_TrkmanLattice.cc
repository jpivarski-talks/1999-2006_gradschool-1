// -*- C++ -*-
//
// File:    T_FAItem_TrkmanLattice.cc
// Package: TrkmanLattice    
// Module:  Trkman
// 
// Description: Instantiate FAItem of TrkmanLattice
//
// Implementation:
//
// Author:      Thomas Meyer
// Created:     Thu Jan 24 09:37:49 EST 2002
//
// Revision history
//
// $Log: T_FAItem_TrkmanLattice.cc,v $
// Revision 1.2  2002/11/04 18:30:12  nea9
// New CleoIII Trkman files added
//
// Revision 1.1.1.1  2002/01/28 13:56:14  tom
// Imported Trkman library sources
//
/* ******************************************************************** */

//---------------+
// CLEO includes |
//---------------+
#include "Experiment/Experiment.h"

//--------------------------+
// Deal with compiler bugs. |
//--------------------------+
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif

//-------------------------+
// User include files      |
//-------------------------+
#include "Trkman/TrkmanLattice.h"

//-------------------//
// STL include files //
//-------------------//
#include <vector>
#include <map>

//-----------------------------------//
// instantiate FrameAccess templates //
//-----------------------------------//
#include "FrameAccess/instantiate_macros.h" 

INSTANTIATE_ONE( TrkmanLattice )

#include "FrameAccess/instantiate_one.h"

#include "StorageManagement/SMLatticeStorageHelper.h"
typedef SMLatticeStorageHelper< TrkmanLattice > TrkmanLatticeStorageHelper;
SM_REGISTER_STORAGE( TrkmanLatticeStorageHelper );
