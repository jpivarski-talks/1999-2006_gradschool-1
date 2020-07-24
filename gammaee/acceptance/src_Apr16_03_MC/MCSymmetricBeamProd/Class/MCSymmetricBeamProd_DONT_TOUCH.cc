// -*- C++ -*-
//
// Package:     <MCSymmetricBeamProd>
// Module:      MCSymmetricBeamProd_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor MCSymmetricBeamProd:
//              creates a new MCSymmetricBeamProd instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Lawrence Gibbons
// Created:     Fri Jan 19 15:30:52 EST 2001
// $Id: MCSymmetricBeamProd_DONT_TOUCH.cc,v 1.1.1.1 2001/01/31 21:10:50 lkg Exp $
//
// Revision history
//
// $Log: MCSymmetricBeamProd_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  2001/01/31 21:10:50  lkg
// imported MCSymmetricBeamProd source
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "MCSymmetricBeamProd/MCSymmetricBeamProd.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCSymmetricBeamProd_DONT_TOUCH.cc,v 1.1.1.1 2001/01/31 21:10:50 lkg Exp $";
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
   return new MCSymmetricBeamProd;
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
