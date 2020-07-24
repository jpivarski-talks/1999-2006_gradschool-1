// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_map_of_string_commandparser.cc
// 
// Description: Instantiate a map w/ a string key holding CommandParser*
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_map_of_string_commandparser.cc,v 1.1 1999/06/22 21:29:09 lkg Exp $
//
// Revision history
//
// $Log: T_map_of_string_commandparser.cc,v $
// Revision 1.1  1999/06/22 21:29:09  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:16:41  lkg
// Initial MCDecayFileParser sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <string>

// user include files
#include "MCInfo/MCDecayFileParser/CommandParser.h"

// STL classes
#include <map>


// forward declarations

typedef string _map_key_;
typedef CommandParser* _map_contents_;
typedef less<_map_key_> _map_compare_;

#include "STLUtility/instantiate_map.h"
