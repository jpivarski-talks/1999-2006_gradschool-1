// -*- C++ -*-
//
// Package:     <EvtGenModels>
// Module:      EvtGenModels
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Anders Ryd
// Created:     Fri Sep 12 21:22:48 EDT 2003
// $Id: EvtGenModels.cc,v 1.1.1.1 2003/10/07 02:48:12 ryd Exp $
//
// Revision history
//
// $Log: EvtGenModels.cc,v $
// Revision 1.1.1.1  2003/10/07 02:48:12  ryd
// imported EvtGenModels sources
//
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Experiment/report.h"
#include "EvtGenModels/EvtGenModels.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "EvtGenModels.EvtGenModels" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: EvtGenModels.cc,v 1.1.1.1 2003/10/07 02:48:12 ryd Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
EvtGenModels::EvtGenModels()
   : Module( "EvtGenModels", "This is my module" ),
     m_command( "EvtGenModels", this ),
     m_internalCommand( "EvtGenModels", this )
{
}

// EvtGenModels::EvtGenModels( const EvtGenModels& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

EvtGenModels::~EvtGenModels()
{
}

//
// assignment operators
//
// const EvtGenModels& EvtGenModels::operator=( const EvtGenModels& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//

//
// const member functions
//
void
EvtGenModels::printNumber( int iNumber ) const
{
   report( INFO, kFacilityString )
      << "and the number is: " << iNumber << endl;
}

//
// static member functions
//
