// -*- C++ -*-
//
// Package:     <Geant3MaterialsMediaProd>
// Module:      Geant3MaterialsMediaProd_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor Geant3MaterialsMediaProd:
//              creates a new Geant3MaterialsMediaProd instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec 14 10:58:53 EST 1999
// $Id: Geant3MaterialsMediaProd_DONT_TOUCH.cc,v 1.1.1.1 1999/12/15 18:35:50 bkh Exp $
//
// Revision history
//
// $Log: Geant3MaterialsMediaProd_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  1999/12/15 18:35:50  bkh
// imported Geant3MaterialsMediaProd sources
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "Geant3MaterialsMediaProd/Geant3MaterialsMediaProd.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: Geant3MaterialsMediaProd_DONT_TOUCH.cc,v 1.1.1.1 1999/12/15 18:35:50 bkh Exp $";
static const char* const kTagString = "$Name: v01_01_00 $";

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
   return new Geant3MaterialsMediaProd;
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
