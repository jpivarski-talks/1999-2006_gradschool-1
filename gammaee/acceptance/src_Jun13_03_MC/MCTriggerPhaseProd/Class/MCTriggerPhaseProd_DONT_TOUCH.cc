// -*- C++ -*-
//
// Package:     <MCTriggerPhaseProd>
// Module:      MCTriggerPhaseProd_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor MCTriggerPhaseProd:
//              creates a new MCTriggerPhaseProd instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Lawrence Gibbons
// Created:     Wed Jan 31 16:43:50 EST 2001
// $Id: MCTriggerPhaseProd_DONT_TOUCH.cc,v 1.1.1.1 2001/02/05 16:17:26 lkg Exp $
//
// Revision history
//
// $Log: MCTriggerPhaseProd_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  2001/02/05 16:17:26  lkg
// imported MCTriggerPhaseProd source
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "MCTriggerPhaseProd/MCTriggerPhaseProd.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCTriggerPhaseProd_DONT_TOUCH.cc,v 1.1.1.1 2001/02/05 16:17:26 lkg Exp $";
static const char* const kTagString = "$Name: v01_02_00 $";

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
   return new MCTriggerPhaseProd;
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
