// -*- C++ -*-
//
// Package:     <EvtGenProd>
// Module:      EvtGenProd_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor EvtGenProd:
//              creates a new EvtGenProd instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Anders Ryd
// Created:     Sat Sep 13 17:58:54 EDT 2003
// $Id: EvtGenProd_DONT_TOUCH.cc,v 1.1.1.1 2003/10/07 02:48:57 ryd Exp $
//
// Revision history
//
// $Log: EvtGenProd_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  2003/10/07 02:48:57  ryd
// imported EvtGenProd sources
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "EvtGenProd/EvtGenProd.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: EvtGenProd_DONT_TOUCH.cc,v 1.1.1.1 2003/10/07 02:48:57 ryd Exp $";
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
   return new EvtGenProd;
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
