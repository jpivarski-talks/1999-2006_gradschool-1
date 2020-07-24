// -*- C++ -*-
//
// Package:     TrackFitter
// Module:      T_ElectronFitCathodeHitLattice
// 
// Description: Template instantiation of FAItem< ElectronFitCathodeHitLattice>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Werner Sun
// Created:     Mon Sep  6 14:45:44 EDT 1999
// $Id: T_ElectronFitCathodeHitLattice.cc,v 1.2 2000/02/24 17:38:17 wsun Exp $
//
// Revision history
//
// $Log: T_ElectronFitCathodeHitLattice.cc,v $
// Revision 1.2  2000/02/24 17:38:17  wsun
// Updated for storage helpers.
//
// Revision 1.1  1999/09/10 20:24:04  wsun
// First submission.
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <set>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "TrackFitter/TrackFitCathodeHitLink.h"

#include <vector>
#include <set>
#include <map>

#include "TrackFitter/Storage/instantiatestore_trackhitlattice.h"
#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE( ElectronFitCathodeHitLattice )
#include "FrameAccess/instantiate_one.h"

#include "StorageManagement/SMLatticeStorageHelper.h"
#include "TrackFitter/Storage/LatticeLinkTrackFitCathodeHitLatticeStorageHelper.h"

INSTANTIATESTORE_TRACKHITLATTICE(Electron,Cathode)

#include "StorageManagement/instantiate_latticehelper.h"
