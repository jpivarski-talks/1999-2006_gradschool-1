#if !defined(EVENTVERTEX_EVENTVERTEX_H)
#define EVENTVERTEX_EVENTVERTEX_H
// -*- C++ -*-
//
// Package:     <EventVertex>
// Module:      EventVertex
// 
/**\class EventVertex EventVertex.h EventVertex/EventVertex.h

 Description:   Class of Event Vertex

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

class EventVertex
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
      EventVertex(
         const Hep3Vector&   vertexPosition,
         const HepSymMatrix& vertexErrMatrix,
         const double&       vertexChiSquare,
         const Count&        vertexType,
         const DABoolean&    trackCutNorm,
         const Count&        numTrackPassKinCuts,
         const Count&        numTrackRemoved,
         const Count&        numTrackFinalVertex);
      virtual ~EventVertex();
      
      // ---------- member functions ---------------------------
      inline Hep3Vector   vertexPosition()      const;
      inline HepSymMatrix vertexErrMatrix()     const;
      inline double       vertexChiSquare()     const;
      inline Count        vertexType()          const;
      inline DABoolean    trackCutNorm()        const;      
      inline Count        numTrackPassKinCuts() const;
      inline Count        numTrackRemoved()     const;
      inline Count        numTrackFinalVertex() const;
      // ---------- const member functions ---------------------
      // Define equality operators for implementation of StorageHelper
      DABoolean operator ==(const EventVertex& rhs) const;
      DABoolean operator !=(const EventVertex& rhs) const;

      // ---------- static member functions --------------------
      
   protected:
      // ---------- protected member functions -----------------
      
      // ---------- protected const member functions -----------
      
   private:
      // ---------- Constructors and destructor ----------------
      // default copy constructor ok for storage helper
      // EventVertex( const EventVertex& );
      
      // ---------- assignment operator(s) ---------------------
      // use default for storage helper
      // const EventVertex& operator=( const EventVertex& );
      
      // ---------- private member functions -------------------
      
      // ---------- private const member functions -------------
      
      // ---------- data members -------------------------------
      Hep3Vector   m_vertexPosition;
      HepSymMatrix m_vertexErrMatrix;
      double       m_vertexChiSquare;
      Count        m_vertexType;
      DABoolean    m_trackCutNorm;
      Count        m_numTrackPassKinCuts;
      Count        m_numTrackRemoved;
      Count        m_numTrackFinalVertex;
  // ---------- static data members ------------------------

};

// inline function definitions

inline Hep3Vector EventVertex::vertexPosition() const
{
   return m_vertexPosition;
}

inline HepSymMatrix EventVertex::vertexErrMatrix() const
{
   return m_vertexErrMatrix;
}

inline double EventVertex::vertexChiSquare() const
{
   return m_vertexChiSquare;
}


inline Count EventVertex::vertexType() const
{
  return m_vertexType;
}

inline DABoolean EventVertex::trackCutNorm() const
{
   return m_trackCutNorm;
}

inline Count EventVertex::numTrackPassKinCuts() const
{
   return m_numTrackPassKinCuts;
}

inline Count EventVertex::numTrackRemoved() const
{
   return m_numTrackRemoved;
}

inline Count EventVertex::numTrackFinalVertex() const
{
  return m_numTrackFinalVertex;
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "EventVertex/Template/EventVertex.cc"
//#endif

#endif /* EVENTVERTEX_EVENTVERTEX_H */
