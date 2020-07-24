// -*- C++ -*-
//
// File:    TrkmanLattice.h
// Package: TrkmanLattice
// Module:  Trkman
// 
/**\class TrkmanLattice TrkmanLattice.h Trkman/TrkmanLattice.h

 Description: Good Track <-> Bad Tracks Lattice from Trkman

 Usage:
 The left nodes are the "good" TrkmanApproved tracks
 The right nodes are the "bad" tracks, e.g. the other tracks
   in a curler group.
 The link data describes the group: curler/ghost/wee and other
   info.

*/
//
// Author:      Thomas Meyer
// Created:     Thu Jan 17 15:04:50 EST 2002
// $Id: TrkmanLattice.h,v 1.1.1.1 2002/01/28 13:56:13 tom Exp $
//
// Revision history
//
// $Log: TrkmanLattice.h,v $
// Revision 1.1.1.1  2002/01/28 13:56:13  tom
// Imported Trkman library sources
//
/* ******************************************************************** */
#ifndef TRKMAN_TRKMANLATTICE_H
#define TRKMAN_TRKMANLATTICE_H

// SYSTEM INCLUDE FILES

// USER INCLUDE FILES
#include "Lattice/Lattice.h"

#include "TrackDelivery/TDTrack.h"
#include "Trkman/TrkmanLink.h"

// FORWARD DECLARATIONS

typedef Lattice< TDTrack, TDTrack, TrkmanLink > TrkmanLattice;

// INLINE FUNCTION DEFINITIONS

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "Trkman/Template/TrkmanLattice.cc"
//#endif

#endif /* TRKMAN_TRKMANLATTICE_H */
