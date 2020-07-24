// -*- C++ -*-
//
// Package:     EventTypeFilterProc
// Module:      EventTypeFilterProc_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Definition of bind action
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Thu Jul 26 12:10:58 EDT 2001
// $Id: EventTypeFilterProc_DONT_TOUCH.cc,v 1.1.1.1 2001/07/31 18:14:14 bkh Exp $
//
// Revision history
//
// $Log: EventTypeFilterProc_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  2001/07/31 18:14:14  bkh
// imported EventTypeFilterProc sources
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "EventTypeFilterProc/EventTypeFilterProc.h"
#include "Processor/Action.h"                

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: EventTypeFilterProc_DONT_TOUCH.cc,v 1.1.1.1 2001/07/31 18:14:14 bkh Exp $";
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
EventTypeFilterProc::bind(
   ActionBase::ActionResult (EventTypeFilterProc::*iMethod)( Frame& ),
   const Stream::Type& iStream )
{
   bindAction( iStream, new Action<EventTypeFilterProc>( iMethod, this ) );
}

//
// const member functions
//

//
// static member functions
//
