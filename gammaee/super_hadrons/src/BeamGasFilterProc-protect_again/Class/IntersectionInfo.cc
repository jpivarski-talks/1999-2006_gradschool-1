// -*- C++ -*-
//
// Package:     BeamGasFilterProc
// Module:      IntersectionInfo
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Feb  4 18:22:49 EST 2003
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
#include "BeamGasFilterProc/IntersectionInfo.h"


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "BeamGasFilterProc.IntersectionInfo" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
IntersectionInfo::IntersectionInfo(double closestIntersection, double eventZ)
   : m_closestIntersection(closestIntersection)
   , m_eventZ(eventZ)
{
}

IntersectionInfo::IntersectionInfo( const IntersectionInfo& rhs )
   : m_closestIntersection(rhs.closestIntersection())
   , m_eventZ(rhs.eventZ())
{
   // do actual copying here; if you implemented
   // operator= correctly, you may be able to use just say      
   // *this = rhs;
}

IntersectionInfo::~IntersectionInfo()
{
}

//
// assignment operators
//
// const IntersectionInfo& IntersectionInfo::operator=( const IntersectionInfo& rhs )
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

//
// static member functions
//
