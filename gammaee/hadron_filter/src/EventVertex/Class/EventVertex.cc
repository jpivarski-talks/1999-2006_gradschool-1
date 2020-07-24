// -*- C++ -*-
//
// Package:     <EventVertex>
// Module:      EventVertex
// 
// Description: Class of Event Vertex
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Roy A. Briere, Michael Earl Watkins
// Created:     Mon Mar 18 17:02:09 EST 2002
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
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"
#include "EventVertex/EventVertex.h"
#include <stdlib.h>
//vertexing
//#include "VXFit/VXFitInterfaceVertex.h"
//#include "VXFit/VXFitVeeCandidate.h"
//#include "VXFit/VXFittable.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "EventVertex.EventVertex" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
EventVertex::EventVertex(
                         const Hep3Vector&           vertexPosition,
                         const HepSymMatrix&         vertexErrMatrix,
                         const double&               vertexChiSquare,
			 const Count&                vertexType,
                         const DABoolean&            trackCutNorm,
			 const Count&                numTrackPassKinCuts,
			 const Count&                numTrackRemoved,
                         const Count&                numTrackFinalVertex):
    m_vertexPosition           (vertexPosition),
    m_vertexErrMatrix          (vertexErrMatrix),
    m_vertexChiSquare          (vertexChiSquare),
    m_vertexType               (vertexType),
    m_trackCutNorm             (trackCutNorm),
    m_numTrackPassKinCuts      (numTrackPassKinCuts),
    m_numTrackRemoved          (numTrackRemoved),
    m_numTrackFinalVertex      (numTrackFinalVertex)
{
}

// EventVertex::EventVertex( const EventVertex& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

EventVertex::~EventVertex()
{
}

//
// assignment operators
//
// const EventVertex& EventVertex::operator=( const EventVertex& rhs )
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
DABoolean EventVertex::operator ==(const EventVertex& rhs) const
{
   return
      m_vertexPosition           == rhs.vertexPosition()           &&
      m_vertexErrMatrix          == rhs.vertexErrMatrix()          &&
      m_vertexChiSquare          == rhs.vertexChiSquare()          &&
      m_vertexType               == rhs.vertexType()               &&
      m_trackCutNorm             == rhs.trackCutNorm()             &&
      m_numTrackPassKinCuts      == rhs.numTrackPassKinCuts()      &&
      m_numTrackRemoved          == rhs.numTrackRemoved()          &&
      m_numTrackFinalVertex      == rhs.numTrackFinalVertex();
}

DABoolean EventVertex::operator !=(const EventVertex& rhs) const
{
  return !((*this) == rhs);
}

//
// static member functions
//
