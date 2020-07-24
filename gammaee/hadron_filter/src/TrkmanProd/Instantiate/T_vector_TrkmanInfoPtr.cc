// -*- C++ -*-
//
// File:    T_vector_TrkmanInfoPtr.cc
// Package: TrkmanInfo
// Module:  TrkmanProd
// 
// Description: Instantiate vector< TrkmanInfo* >
//
// Implementation:
//
// Author:      Thomas Meyer
// Created:     Thu Jan 17 11:36:37 EST 2002
// $Id: T_vector_TrkmanInfoPtr.cc,v 1.1.1.1 2002/01/28 13:57:19 tom Exp $
//
// Revision history
//
// $Log: T_vector_TrkmanInfoPtr.cc,v $
// Revision 1.1.1.1  2002/01/28 13:57:19  tom
// Imported TrkmanProd sources
//
/* ******************************************************************** */

#include "Experiment/Experiment.h"

// SYSTEM INCLUDE FILES
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// USER INCLUDE FILES
//#include "TrkmanProd/TrkmanInfo.h"

// STL classes
#include <vector>

class TrkmanInfo;

typedef TrkmanInfo* _vector_contents_;

#include "STLUtility/instantiate_vector.h"
