// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawData_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor MCRawData:
//              creates a new MCRawData instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:24:00 EST 1999
// $Id: MCRawData_DONT_TOUCH.cc,v 1.1.1.1 1999/02/25 20:29:11 bkh Exp $
//
// Revision history
//
// $Log: MCRawData_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  1999/02/25 20:29:11  bkh
// imported MCRawData sources
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "MCRawData/MCRawData.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCRawData_DONT_TOUCH.cc,v 1.1.1.1 1999/02/25 20:29:11 bkh Exp $";
static const char* const kTagString = "$Name:  $";

//
// function definitions
//

extern "C" {
   Producer* makeProducer( void );
   const char* versionString( void );
}

Producer*
makeProducer( void )
{
   return new MCRawData;
}

const char*
versionString( void )
{
   return kTagString;
}

//
// static data member definitions
//

//
// member functions
//

//
// const member functions
//

//
// static member functions
//
