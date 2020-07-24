// -*- C++ -*-
//
// Package:     EventTypeFilterProc
// Module:      EventTypeFilterProc_DONT_TOUCH2
// 
// Description: DONT TOUCH THIS FILE!
//
//              Factory method to create processor EventTypeFilterProc:
//              creates a new EventTypeFilterProc instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Thu Jul 26 12:10:56 EDT 2001
// $Id: EventTypeFilterProc_DONT_TOUCH2.cc,v 1.1.1.1 2001/07/31 18:14:14 bkh Exp $
//
// Revision history
//
// $Log: EventTypeFilterProc_DONT_TOUCH2.cc,v $
// Revision 1.1.1.1  2001/07/31 18:14:14  bkh
// imported EventTypeFilterProc sources
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif             

// user include files
#include "EventTypeFilterProc/EventTypeFilterProc.h"

// STL classes
#include <string>

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: EventTypeFilterProc_DONT_TOUCH2.cc,v 1.1.1.1 2001/07/31 18:14:14 bkh Exp $";
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
   return new EventTypeFilterProc;
}

const char*
versionString( void )
{
   return kTagString;
}

