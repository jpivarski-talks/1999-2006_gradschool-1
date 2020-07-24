// -*- C++ -*-
//
// Package:     HadronFilterProc
// Module:      HadronFilterProc_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Definition of bind action
//
// Implementation:
//
// Author:      Jim Pivarski
// Created:     Wed Oct 16 11:23:37 EDT 2002
// $Id: HadronFilterProc_DONT_TOUCH.cc,v 1.1.1.1 2002/10/16 17:40:04 mccann Exp $
//
// Revision history
//
// $Log: HadronFilterProc_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  2002/10/16 17:40:04  mccann
// A processor that uses tracking to filter out beam wall/beam gas.
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "HadronFilterProc/HadronFilterProc.h"
#include "Processor/Action.h"                

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: HadronFilterProc_DONT_TOUCH.cc,v 1.1.1.1 2002/10/16 17:40:04 mccann Exp $";
static const char* const kTagString = "$Name:  $";

//
// function definitions
//

//
// static data member definitions
//

//
// member functions
//
// ---------------- binding method to stream -------------------
void
HadronFilterProc::bind(
   ActionBase::ActionResult (HadronFilterProc::*iMethod)( Frame& ),
   const Stream::Type& iStream )
{
   bindAction( iStream, new Action<HadronFilterProc>( iMethod, this ) );
}

//
// const member functions
//

//
// static member functions
//
