// -*- C++ -*-
//
// Package:     <EventVertexProd>
// Module:      EventVertexPrivate
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
#include "EventVertexProd/EventVertexPrivate.h"
#include <stdlib.h>
//vertexing
//#include "VXFit/VXFitInterfaceVertex.h"
//#include "VXFit/VXFitVeeCandidate.h"
//#include "VXFit/VXFittable.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "EventVertexProd.EventVertexPrivate" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
EventVertexPrivate::EventVertexPrivate(const Hep3Vector&           vertexPosition,
                                       const HepSymMatrix&         vertexErrMatrix,
                                       const double&               vertexChiSquare,
                                       const Count&                numTrackPassKinCuts,
                                       const Count&                numTrackFinalVertex,
                                       const Count&                vertexType,
                                       const STL_VECTOR(NavTrack::Identifier)&   vectorOfTrackIDs,
                                       const STL_VECTOR(double)&   vectorOfChiSquares,
                                       const STL_VECTOR(double)&   vectorOfRemovedTrackChi2,
                                       const DABoolean&            trackCutNorm):
   m_vertexPosition           (vertexPosition),
   m_vertexErrMatrix          (vertexErrMatrix),
   m_vertexChiSquare          (vertexChiSquare),
   m_numTrackPassKinCuts      (numTrackPassKinCuts),
   m_numTrackFinalVertex      (numTrackFinalVertex),
   m_vertexType               (vertexType),
   m_vectorOfTrackIDs         (vectorOfTrackIDs),
   m_vectorOfChiSquares       (vectorOfChiSquares),
   m_vectorOfRemovedTrackChi2 (vectorOfRemovedTrackChi2),
   m_trackCutNorm             (trackCutNorm)
{
}


// EventVertexPrivate::EventVertexPrivate( const EventVertexPrivate& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

EventVertexPrivate::~EventVertexPrivate()
{
}

//
// assignment operators
//
// const EventVertexPrivate& EventVertexPrivate::operator=( const EventVertexPrivate& rhs )
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
DABoolean EventVertexPrivate::operator ==(const EventVertexPrivate& rhs) const
{
   return
      m_vertexPosition           == rhs.vertexPosition()           &&
      m_vertexErrMatrix          == rhs.vertexErrMatrix()          &&
      m_vertexChiSquare          == rhs.vertexChiSquare()          &&
      m_numTrackPassKinCuts      == rhs.numTrackPassKinCuts()      &&
      m_numTrackFinalVertex      == rhs.numTrackFinalVertex()      &&
      m_vertexType               == rhs.vertexType()               &&
      m_vectorOfTrackIDs         == rhs.vectorOfTrackIDs()         &&
      m_vectorOfChiSquares       == rhs.vectorOfChiSquares()       &&
      m_vectorOfRemovedTrackChi2 == rhs.vectorOfRemovedTrackChi2() &&
      m_trackCutNorm             == rhs.trackCutNorm() ;
}

DABoolean EventVertexPrivate::operator !=(const EventVertexPrivate& rhs) const
{
  return !((*this) == rhs);
}

//
// static member functions
//
