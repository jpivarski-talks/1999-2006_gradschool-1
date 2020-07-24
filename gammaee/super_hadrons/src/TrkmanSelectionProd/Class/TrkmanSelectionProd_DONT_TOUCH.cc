// -*- C++ -*-
//
// Package:     <TrkmanSelectionProd>
// Module:      TrkmanSelectionProd_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor TrkmanSelectionProd:
//              creates a new TrkmanSelectionProd instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Nadia Adam
// Created:     Mon Oct 28 12:14:24 EST 2002
// $Id: TrkmanSelectionProd_DONT_TOUCH.cc,v 1.1.1.1 2002/11/04 18:18:55 nea9 Exp $
//
// Revision history
//
// $Log: TrkmanSelectionProd_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  2002/11/04 18:18:55  nea9
// imported TrkmanSelectionProd
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "TrkmanSelectionProd/TrkmanSelectionProd.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: TrkmanSelectionProd_DONT_TOUCH.cc,v 1.1.1.1 2002/11/04 18:18:55 nea9 Exp $";
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
   return new TrkmanSelectionProd;
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
