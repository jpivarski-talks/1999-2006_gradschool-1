// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_map_of_pdgid_qqid.cc
// 
// Description: Instantiate a map w/ a string key holding QQ_id's
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_map_of_pdgid_qqid.cc,v 1.1 1999/06/22 21:29:27 lkg Exp $
//
// Revision history
//
// $Log: T_map_of_pdgid_qqid.cc,v $
// Revision 1.1  1999/06/22 21:29:27  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:11:22  lkg
// Initial MCInfo sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCTypes.h"

// STL classes
#include <map>

// forward declarations

typedef QQ_id _map_key_;
typedef PDG_id _map_contents_;
typedef less<_map_key_> _map_compare_;

#include "STLUtility/instantiate_map.h"
