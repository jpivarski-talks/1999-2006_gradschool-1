// -*- C++ -*-
//
// File:    T_find_TrkmanLattice.cc
// Package: TrkmanLattice
// Module:  Trkman
// 
// Description: Instantiate find<>() functions for TrkmanLattice
//
//
// Author:      Jon Thaler
// Created:     June 12, 2001
//
// Revision history
//
// $Log: T_find_TrkmanLattice.cc,v $
// Revision 1.1.1.1  2002/01/28 13:56:14  tom
// Imported Trkman library sources
//
/* ******************************************************************** */

#include "Experiment/Experiment.h"

// SYSTEM INCLUDE FILES
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <algorithm>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// STL CLASSES
#include <algorithm>

//-------------------------------------------+
// find is declared as:                      |
// template<T1,T2> T1 find(T1,T1,const T2&); |
//-------------------------------------------+
template       int* STD_PREFIX find(      int*,       int*, const int&);
template const int* STD_PREFIX find(const int*, const int*, const int&);
