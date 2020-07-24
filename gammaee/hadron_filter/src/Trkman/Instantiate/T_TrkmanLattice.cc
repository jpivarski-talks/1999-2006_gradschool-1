// -*- C++ -*-
//
// File:    T_TrkmanLattice.cc
// Package: TrkmanLattice
// Module:  Trkman
// 
// Description: Instantiate TrkmanLattice (Lattice is a template)
//
// Implementation:
//   Process with mklattice to generate a useable file.
//   Put the resulting files, T_Lattice.cc and T_find_for_Lattice.cc,
//   in the Instantiate directory.
//
// Author:      Jon Thaler
// Created:     June 12, 2001
//
// Revision history
//
// $Log: T_TrkmanLattice.cc,v $
// Revision 1.1.1.1  2002/01/28 13:56:14  tom
// Imported Trkman library sources
//
/* ******************************************************************** */

//---------------+
// CLEO includes |
//---------------+
#include "Experiment/Experiment.h"
#include "Experiment/types.h"

//-------------------------------------------------------------+
// Turn off auto-instantiation of "" name string (for Solaris) |
//-------------------------------------------------------------+
#define HETEROCONTAINER_HCTYPETAGTEMPLATE_CC

//--------------------------+
// Deal with compiler bugs. |
//--------------------------+
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif

//-------------------------+
// User include files      |
//  * The left  data type. |
//  * The right data type. |
//  * the LinkData   type. |
//-------------------------+
#include "TrackDelivery/TDTrack.h"
#include "Trkman/TrkmanLink.h"

//-------------------------------+
// Specify Lattice linkage here. |
//-------------------------------+
typedef TDTrack    _left_lattice_type_;
typedef TDTrack    _right_lattice_type_;
typedef TrkmanLink _linkdata_type_;

//--------------------------------------------------------------+
// Control which instantiations are actually done.              |
// This is needed due to difficulty automating template         |
// instantiation in all cases.  Most of the time, only RIGHTID  |
// is left undone (it's usually the same type as LEFTID).       |
//--------------------------------------------------------------+
#define INSTANTIATE_LATTICE_VECTOR_LINK
// #define INSTANTIATE_LATTICE_VECTOR_LEFTID
// #define INSTANTIATE_LATTICE_VECTOR_RIGHTID
#define INSTANTIATE_LATTICE_VECTOR_LEFTNODE
#define INSTANTIATE_LATTICE_VECTOR_RIGHTNODE

#include "Lattice/instantiate_Lattice.h"
