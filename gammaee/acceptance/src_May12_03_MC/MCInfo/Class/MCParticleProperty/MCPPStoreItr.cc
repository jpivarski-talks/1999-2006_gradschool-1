// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCPPStoreItr
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Fri Apr  6 14:21:51 EDT 2001
// $Id: MCPPStoreItr.cc,v 1.1 2001/05/12 17:45:26 lkg Exp $
//
// Revision history
//
// $Log: MCPPStoreItr.cc,v $
// Revision 1.1  2001/05/12 17:45:26  lkg
// implement a dereferencing iterator for the particle property store, and provide begin and end member fcn's for it
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCParticleProperty/MCPPStoreItr.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCPPStoreItr" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCPPStoreItr.cc,v 1.1 2001/05/12 17:45:26 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCPPStoreItr::MCPPStoreItr( baseItr anIterator, baseItr endIterator ) :
   derefItr( anIterator ),
   m_trueEndItr( endIterator )
{}

MCPPStoreItr::MCPPStoreItr( const MCPPStoreItr& rhs ) :
   derefItr( rhs ),
   m_trueEndItr( rhs.m_trueEndItr )
{}

MCPPStoreItr::~MCPPStoreItr()
{}

//
// assignment operators
//
const MCPPStoreItr& 
MCPPStoreItr::operator=( const MCPPStoreItr& rhs )
{
  if( this != &rhs ) {
     derefItr::operator=( rhs );
  }

  return *this;
}

//
// member functions
//
MCPPStoreItr&
MCPPStoreItr::operator++() {
   do {
      derefItr::operator++() ; 
   } while( bareIterator() != m_trueEndItr &&
	    ( (*bareIterator() == 0) ||
	      ( (*bareIterator() != 0) &&
	        ((*this)->QQId() == MCParticleProperty::kUnknownQQId) ) 
	    ) );
   return *this;
}

MCPPStoreItr
MCPPStoreItr::operator++(int) {
   MCPPStoreItr before( *this );
   ++(*this); // use prefix operator
   return( before );
}
