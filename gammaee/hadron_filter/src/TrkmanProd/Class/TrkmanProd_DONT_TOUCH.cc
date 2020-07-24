// -*- C++ -*-
//
// Package:     <TrkmanProd>
// Module:      TrkmanProd_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor TrkmanProd:
//              creates a new TrkmanProd instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Thomas Meyer
// Created:     Mon Jan 14 11:28:13 EST 2002
// $Id: TrkmanProd_DONT_TOUCH.cc,v 1.1.1.1 2002/01/28 13:57:19 tom Exp $
//
// Revision history
//
// $Log: TrkmanProd_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  2002/01/28 13:57:19  tom
// Imported TrkmanProd sources
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "TrkmanProd/TrkmanProd.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: TrkmanProd_DONT_TOUCH.cc,v 1.1.1.1 2002/01/28 13:57:19 tom Exp $";
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
   return new TrkmanProd;
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
