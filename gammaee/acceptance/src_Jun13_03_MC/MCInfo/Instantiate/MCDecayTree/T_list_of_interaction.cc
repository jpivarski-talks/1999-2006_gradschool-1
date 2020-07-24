// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_list_of_MCVertex.cc
// 
// Description: Instantiate a list holding MCVertex*
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_list_of_interaction.cc,v 1.5 2002/12/06 16:42:14 cleo3 Exp $
//
// Revision history
//
// $Log: T_list_of_interaction.cc,v $
// Revision 1.5  2002/12/06 16:42:14  cleo3
// deal with g++ namespace instantiation bug
//
// Revision 1.4  2001/09/10 20:08:01  cleo3
// changed to just instantiate find for pointers
//
// Revision 1.3  2001/02/18 22:14:09  cleo3
// added include of algorithm
//
// Revision 1.2  1999/10/19 21:57:32  lkg
// * Change typing from the enum "interaction" to Count
//
// Revision 1.1  1999/06/22 21:29:15  lkg
// First real version of MCInfo in repository
//
//

#include "Experiment/Experiment.h"

// system include files
// user include files
#include "MCInfo/MCDecayTree/interaction_types.h"

// STL classes
#include <algorithm>

// forward declarations

// need to instantiate the "find" command
#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
#undef STD_PREFIX
#define STD_PREFIX
namespace std {
#endif
template const interaction* STD_PREFIX find(
   const interaction*,
   const interaction* ,
    const interaction& );

template const interaction* STD_PREFIX find(
   const interaction*,
   const interaction*,
    const Count& );
#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
}
#endif
