// -*- C++ -*-
//
// File:    T_selection_TrkmanApprover.cc
// Package: TrkmanApprover
// Module:  TrkmanProd
// 
// Description: Instantiate selection prefix Proxy for NavTrack
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Thomas Meyer
// Created:     Wed Sep 12 11:13:46 EDT 2001
// $Id: T_selection_TrkmanApprover.cc,v 1.1.1.1 2002/11/04 18:18:55 nea9 Exp $
//
// Revision history
//
// $Log: T_selection_TrkmanApprover.cc,v $
// Revision 1.1.1.1  2002/11/04 18:18:55  nea9
// imported TrkmanSelectionProd
//
// Revision 1.1.1.1  2002/01/28 13:57:19  tom
// Imported TrkmanProd sources
//
/* ******************************************************************** */

#include "Experiment/Experiment.h"

// SYSTEM INCLUDE FILES
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// USER INCLUDE FILES
#include "Navigation/NavTrack.h"
#include "TrkmanSelectionProd/TrkmanApprover.h"
#include "Selection/instantiate_selection_prefix_proxy.h"

INSTANTIATE_SELECTION_PREFIX_PROXY(NavTrack, TrkmanApprover)
