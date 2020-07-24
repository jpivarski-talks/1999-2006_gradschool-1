// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_getline_ifstream.cc
// 
// Description: Instantiate the istream getline function for an ifstream
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_getline_ifstream.cc,v 1.5 2002/12/06 16:42:14 cleo3 Exp $
//
// Revision history
//
// $Log: T_getline_ifstream.cc,v $
// Revision 1.5  2002/12/06 16:42:14  cleo3
// deal with g++ namespace instantiation bug
//
// Revision 1.4  2002/11/21 21:11:55  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.3  2001/09/10 20:08:58  cleo3
// removed stream.h and used proper bug flag
//
// Revision 1.2  2001/02/19 02:36:05  cleo3
// minor modifications needed to compile on linux
//
// Revision 1.1  1999/06/22 21:29:06  lkg
// First real version of MCInfo in repository
//
//

#include "Experiment/Experiment.h"

#include <string>
#include "C++Std/iostream.h"
#include "C++Std/fstream.h"

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

#if defined(ISTREAM_IS_A_CLASS_BUG)
template ifstream& STD_PREFIX getline(ifstream&, string& );
template ifstream& STD_PREFIX getline(ifstream&, string&, char );
#else
#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
#undef STD_PREFIX
#define STD_PREFIX
namespace std {
#endif
template istream& STD_PREFIX getline(istream&, string& );
template istream& STD_PREFIX getline(istream&, string&, char );
#if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
}
#endif
#endif
