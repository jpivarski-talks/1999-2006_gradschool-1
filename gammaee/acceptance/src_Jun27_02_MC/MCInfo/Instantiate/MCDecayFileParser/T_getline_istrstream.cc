// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      T_getline_istrstream.cc
// 
// Description: Instantiate the istream getline function for an istrstream
//
//
// Author:      Lawrence Gibbons
// Created:     Sat Nov  7 16:48:05 EST 1998
// $Id: T_getline_istrstream.cc,v 1.3 2001/09/10 20:08:59 cleo3 Exp $
//
// Revision history
//
// $Log: T_getline_istrstream.cc,v $
// Revision 1.3  2001/09/10 20:08:59  cleo3
// removed stream.h and used proper bug flag
//
// Revision 1.2  2001/02/19 02:36:05  cleo3
// minor modifications needed to compile on linux
//
// Revision 1.1  1999/06/22 21:29:08  lkg
// First real version of MCInfo in repository
//
//

#include "Experiment/Experiment.h"

#include <string>
#include <strstream.h>
#include "C++Std/iostream.h"

#if !defined(NO_STD_NAMESPACE_BUG)
#define STD_PREFIX std::
#else
#define STD_PREFIX
#endif

#if defined(ISTREAM_IS_A_CLASS_BUG)
template istrstream& STD_PREFIX getline(istrstream&, string& );
template istrstream& STD_PREFIX getline(istrstream&, string&, char );
#endif
