// -*- C++ -*-
//
// Package:     <MCInfoDelivery>
// Module:      MCInfoDelivery_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor MCInfoDelivery:
//              creates a new MCInfoDelivery instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Lawrence Gibbons
// Created:     Mon Dec  7 17:05:28 EST 1998
// $Id: MCInfoDelivery_DONT_TOUCH.cc,v 1.1.1.1 1999/07/07 01:51:22 lkg Exp $
//
// Revision history
//
// $Log: MCInfoDelivery_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  1999/07/07 01:51:22  lkg
// initial MCInfoDelivery
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "MCInfoDelivery/MCInfoDelivery.h"

// STL classes

//
// constants, enums and typedefs
//

//
// function definitions
//

// ---------------------------factory method -------------------
extern "C" {
   Producer* makeProducer( void );
}

Producer*
makeProducer( void )
{
   return new MCInfoDelivery;
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
