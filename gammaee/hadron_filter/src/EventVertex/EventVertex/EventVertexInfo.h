#if !defined(EVENTVERTEX_EVENTVERTEXINFO_H)
#define EVENTVERTEX_EVENTVERTEXINFO_H
// -*- C++ -*-
//
// Package:     <EventVertexInfo>
// Module:      EventVertexInfo
// 
/**\class EventVertexInfo EventVertexInfo.h EventVertexInfo/EventVertexInfo.h

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

class EventVertexInfo
{
      // ---------- friend classes and functions ---------------
      
   public:

      // ---------- constants, enums and typedefs --------------
      
      // ---------- Constructors and destructor ----------------
      EventVertexInfo(
         const STL_VECTOR(NavTrack::Identifier)& vectorOfTrackIDs,
         const STL_VECTOR(double)&               vectorOfChiSquares,
         const STL_VECTOR(double)&               vectorOfRemovedTrackChi2);
      virtual ~EventVertexInfo();
      
      // ---------- member functions ---------------------------
      inline STL_VECTOR(NavTrack::Identifier) vectorOfTrackIDs()         const;
      inline STL_VECTOR(double)               vectorOfChiSquares()       const;
      inline STL_VECTOR(double)               vectorOfRemovedTrackChi2() const;
      
      // ---------- const member functions ---------------------
      // Define equality operators for implementation of StorageHelper
      DABoolean operator ==(const EventVertexInfo& rhs) const;
      DABoolean operator !=(const EventVertexInfo& rhs) const;

      // ---------- static member functions --------------------
      
   protected:
      // ---------- protected member functions -----------------
      
      // ---------- protected const member functions -----------
      
   private:
      // ---------- Constructors and destructor ----------------
      // default copy constructor ok for storage helper
      // EventVertexInfo( const EventVertexInfo& );
      
      // ---------- assignment operator(s) ---------------------
      // use default for storage helper
      // const EventVertexInfo& operator=( const EventVertexInfo& );
      
      // ---------- private member functions -------------------
      
      // ---------- private const member functions -------------
      
      // ---------- data members -------------------------------

      STL_VECTOR(NavTrack::Identifier) m_vectorOfTrackIDs;
      STL_VECTOR(double)               m_vectorOfChiSquares;
      STL_VECTOR(double)               m_vectorOfRemovedTrackChi2;

  // ---------- static data members ------------------------

};

// inline function definitions

inline STL_VECTOR(NavTrack::Identifier) EventVertexInfo::vectorOfTrackIDs() const
{
   return m_vectorOfTrackIDs;
}
inline STL_VECTOR(double) EventVertexInfo::vectorOfChiSquares() const
{
   return m_vectorOfChiSquares;
}
inline STL_VECTOR(double) EventVertexInfo::vectorOfRemovedTrackChi2() const
{
   return m_vectorOfRemovedTrackChi2;
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "EventVertexInfo/Template/EventVertexInfo.cc"
//#endif

#endif /* EVENTVERTEX_EVENTVERTEXINFO_H */
