// -*- C++ -*-
//
// Package:     <StupidProd>
// Module:      Stupid
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Mar 22 01:34:14 EST 2004
// $Id$
//
// Revision history
//
// $Log$

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
//#include "Experiment/report.h"
#include "StupidProd/Stupid.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "StupidProd.Stupid" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
Stupid::Stupid(int tracks0, int tracks1, int tracks2, int tracks3)
   : m_tracks0(tracks0)
   , m_tracks1(tracks1)
   , m_tracks2(tracks2)
   , m_tracks3(tracks3)
{
}

Stupid::Stupid( const Stupid& other )
{
   // do actual copying here; if you implemented
   // operator= correctly, you may be able to use just say      

   m_tracks0 = other.tracks0();
   m_tracks1 = other.tracks1();
   m_tracks2 = other.tracks2();
   m_tracks3 = other.tracks3();
   
}

Stupid::~Stupid()
{
}

//
// assignment operators
//
const Stupid& Stupid::operator=( const Stupid& other )
{
   m_tracks0 = other.tracks0();
   m_tracks1 = other.tracks1();
   m_tracks2 = other.tracks2();
   m_tracks3 = other.tracks3();

  return *this;
}

//
// member functions
//

DABoolean Stupid::operator==( const Stupid& other ) const {
   return (other.tracks0() == m_tracks0  &&
	   other.tracks1() == m_tracks1  &&
	   other.tracks2() == m_tracks2  &&
	   other.tracks3() == m_tracks3     );
}

//
// const member functions
//

//
// static member functions
//
