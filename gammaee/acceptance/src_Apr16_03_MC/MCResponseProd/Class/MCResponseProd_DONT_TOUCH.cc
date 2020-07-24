// -*- C++ -*-
//
// Package:     <MCResponseProd>
// Module:      MCResponseProd_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor MCResponseProd:
//              creates a new MCResponseProd instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      John J O'Neill
// Created:     Mon Apr 12 11:34:57 EDT 1999
// $Id: MCResponseProd_DONT_TOUCH.cc,v 1.1.1.1 1999/04/16 20:07:32 jjo Exp $
//
// Revision history
//
// $Log: MCResponseProd_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  1999/04/16 20:07:32  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo) 
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "MCResponseProd/MCResponseProd.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCResponseProd_DONT_TOUCH.cc,v 1.1.1.1 1999/04/16 20:07:32 jjo Exp $";
static const char* const kTagString = "$Name: v06_02_05 $";

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
   return new MCResponseProd;
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
