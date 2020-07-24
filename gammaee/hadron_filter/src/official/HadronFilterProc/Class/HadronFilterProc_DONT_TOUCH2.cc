// -*- C++ -*-
//
// Package:     HadronFilterProc
// Module:      HadronFilterProc_DONT_TOUCH2
// 
// Description: DONT TOUCH THIS FILE!
//
//              Factory method to create processor HadronFilterProc:
//              creates a new HadronFilterProc instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Jim Pivarski
// Created:     Wed Oct 16 11:23:37 EDT 2002
// $Id: HadronFilterProc_DONT_TOUCH2.cc,v 1.1.1.1 2002/10/16 17:40:04 mccann Exp $
//
// Revision history
//
// $Log: HadronFilterProc_DONT_TOUCH2.cc,v $
// Revision 1.1.1.1  2002/10/16 17:40:04  mccann
// A processor that uses tracking to filter out beam wall/beam gas.
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif             

// user include files
#include "HadronFilterProc/HadronFilterProc.h"

// STL classes
#include <string>

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: HadronFilterProc_DONT_TOUCH2.cc,v 1.1.1.1 2002/10/16 17:40:04 mccann Exp $";
static const char* const kTagString = "$Name:  $";

//
// function definitions
//

extern "C" {
   Processor* makeProcessor( void );
   const char* versionString( void );
}

Processor*
makeProcessor( void )
{
   return new HadronFilterProc;
}

const char*
versionString( void )
{
   return kTagString;
}

