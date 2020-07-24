// -*- C++ -*-
//
// Package:     <EvtGenModels>
// Module:      EvtGenModels_DONT_TOUCH.cc
// 
// Description: factory function to create EvtGenModels
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Anders Ryd
// Created:     Fri Sep 12 21:22:48 EDT 2003
// $Id: EvtGenModels_DONT_TOUCH.cc,v 1.1.1.1 2003/10/07 02:48:12 ryd Exp $
//
// Revision history
//
// $Log: EvtGenModels_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  2003/10/07 02:48:12  ryd
// imported EvtGenModels sources
//
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "EvtGenModels/EvtGenModels.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: EvtGenModels_DONT_TOUCH.cc,v 1.1.1.1 2003/10/07 02:48:12 ryd Exp $";
static const char* const kTagString = "$Name:  $";

//
// function definitions
//

extern "C" { 
   Module* makeModule( void ); 
   const char* versionString( void );
}

Module*
makeModule( void )
{
   return new EvtGenModels;
}

const char*
versionString( void )
{
   return kTagString;
}
