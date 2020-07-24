#if !defined(EVENTVERTEXPROD_EVENTVERTEXPRIVATE_H)
#define EVENTVERTEXPROD_EVENTVERTEXPRIVATE_H
// -*- C++ -*-
//
// Package:     <EventVertexProd>
// Module:      EventVertexPrivate
// 
/**\class EventVertex EventVertexPrivate.h EventVertexProd/EventVertexPrivate.h

 Description:   Class of Event Vertex Private
                holds info on the location of the event vertex and of
                the tracks in and removed from the vertex

 Usage:
    <usage>

*/
//
// Author:      Roy A. Briere, Michael Earl Watkins
// Created:     Mon Mar 18 17:02:16 EST 2002
// $Id$
//
// Revision history
//
// $Log$

// system include files

// user include files

#include <vector>
#include <stdlib.h>
#include <map>

#include <memory.h> 
//vertexing
//#include "VXFit/VXFitInterfaceVertex.h"
//#include "VXFit/VXFitVeeCandidate.h"
//#include "VXFit/VXFittable.h"
// forward declarations
#include "STLUtility/fwd_vector.h"
#include "Navigation/NavTrack.h"

class EventVertexPrivate
{
      // ---------- friend classes and functions ---------------
      
   public:

      // ---------- constants, enums and typedefs --------------
      enum EventTypes {kGoodEvent,
                       kTooFewInitial,
                       kTooFewPassKinCuts,
                       kTooManyChi2Drop,
                       kVertexingFails};
      enum ErrorMatrix {kX=1,
                        kY,
                        kZ};
      
      // ---------- Constructors and destructor ----------------
      EventVertexPrivate(
         const Hep3Vector&                       vertexPosition,
         const HepSymMatrix&                     vertexErrMatrix,
         const double&                           vertexChiSquare,
         const Count&                            numTrackPassKinCuts,
         const Count&                            numTrackFinalVertex,
         const Count&                            vertexType,
         const STL_VECTOR(NavTrack::Identifier)& vectorOfTrackIDs,
         const STL_VECTOR(double)&               vectorOfChiSquares,
         const STL_VECTOR(double)&               vectorOfRemovedTrackChi2,
         const DABoolean&                        trackCutNorm);
      virtual ~EventVertexPrivate();
      
      // ---------- member functions ---------------------------
      inline Hep3Vector                       vertexPosition()           const;
      inline HepSymMatrix                     vertexErrMatrix()          const;
      inline double                           vertexChiSquare()          const;
      inline Count                            numTrackPassKinCuts()      const;
      inline Count                            numTrackFinalVertex()      const;
      inline Count                            vertexType()               const;
      inline STL_VECTOR(NavTrack::Identifier) vectorOfTrackIDs()         const;
      inline STL_VECTOR(double)               vectorOfChiSquares()       const;
      inline STL_VECTOR(double)               vectorOfRemovedTrackChi2() const;
      inline DABoolean                        trackCutNorm()             const;
      
      // ---------- const member functions ---------------------
      // Define equality operators for implementation of StorageHelper
      DABoolean operator ==(const EventVertexPrivate& rhs) const;
      DABoolean operator !=(const EventVertexPrivate& rhs) const;

      // ---------- static member functions --------------------
      
   protected:
      // ---------- protected member functions -----------------
      
      // ---------- protected const member functions -----------
      
   private:
      // ---------- Constructors and destructor ----------------
      // default copy constructor ok for storage helper
      // EventVertexPrivate( const EventVertexPrivate& );
      
      // ---------- assignment operator(s) ---------------------
      // use default for storage helper
      // const EventVertexPrivate& operator=( const EventVertexPrivate& );
      
      // ---------- private member functions -------------------
      
      // ---------- private const member functions -------------
      
      // ---------- data members -------------------------------
      Hep3Vector                       m_vertexPosition;
      HepSymMatrix                     m_vertexErrMatrix;
      double                           m_vertexChiSquare;
      Count                            m_numTrackPassKinCuts;
      Count                            m_numTrackFinalVertex;
      Count                            m_vertexType;
      STL_VECTOR(NavTrack::Identifier) m_vectorOfTrackIDs;
      STL_VECTOR(double)               m_vectorOfChiSquares;
      STL_VECTOR(double)               m_vectorOfRemovedTrackChi2;
      DABoolean                        m_trackCutNorm;
  // ---------- static data members ------------------------

};

// inline function definitions
inline Hep3Vector EventVertexPrivate::vertexPosition() const
{
   return m_vertexPosition;
}

inline HepSymMatrix EventVertexPrivate::vertexErrMatrix() const
{
   return m_vertexErrMatrix;
}

inline double EventVertexPrivate::vertexChiSquare() const
{
   return m_vertexChiSquare;
}

inline Count EventVertexPrivate::numTrackPassKinCuts() const
{
   return m_numTrackPassKinCuts;
}

inline Count EventVertexPrivate::numTrackFinalVertex() const
{
  return m_numTrackFinalVertex;
}

inline Count EventVertexPrivate::vertexType() const
{
  return m_vertexType;
}
inline STL_VECTOR(NavTrack::Identifier) EventVertexPrivate::vectorOfTrackIDs() const
{
   return m_vectorOfTrackIDs;
}
inline STL_VECTOR(double) EventVertexPrivate::vectorOfChiSquares() const
{
   return m_vectorOfChiSquares;
}
inline STL_VECTOR(double) EventVertexPrivate::vectorOfRemovedTrackChi2() const
{
   return m_vectorOfRemovedTrackChi2;
}
inline DABoolean EventVertexPrivate::trackCutNorm() const
{
   return m_trackCutNorm;
}
// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "EventVertexPrivate/Template/EventVertexPrivate.cc"
//#endif

#endif /* EVENTVERTEXPROD_EVENTVERTEXPRIVATE_H */
