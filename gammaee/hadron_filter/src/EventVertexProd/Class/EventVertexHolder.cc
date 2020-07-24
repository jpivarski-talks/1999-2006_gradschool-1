// -*- C++ -*-
//
// Package:     <package>
// Module:      EventVertexHolder
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Michael Watkins
// Created:     Mon Apr 29 16:51:38 EDT 2002
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
#include "EventVertexProd/EventVertexHolder.h"
#include "Experiment/report.h"
//
// constants, enums and typedefs
//

static const char* const kFacilityString = "package.EventVertexHolder" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: skeleton.cc,v 1.6 2001/01/03 16:25:23 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
EventVertexHolder::EventVertexHolder(Module* iModule)
   :
   m_eventVertexParam ( "EventVXMenu"  , iModule),
   m_Param_d0      ( "max_d0"           , &m_eventVertexParam, d0Param              ),
   m_Param_z0      ( "max_z0"           , &m_eventVertexParam, z0Param              ),
   m_Param_TMom    ( "min_TrkMom"       , &m_eventVertexParam, momParam             ),
   m_Param_MinTrk  ( "min_NumTrk"       , &m_eventVertexParam, NumMinTrkParam       ),
   m_Param_MaxChi2 ( "max_Chi2perTrack" , &m_eventVertexParam, MaxChi2perTrackParam ),
   m_Param_TrackCutNorm ( "TrackCutNorm"      , &m_eventVertexParam, TrackCutNormParam       )
{
   //help strings for the Parameters
   string help_d0 = "float for max. abs(d0) for tracks to be vertexed \n";
   string help_z0 = "float for max. abs(z0) for tracks to be vertexed \n";
   string help_TMom = "float for min. track momentum to be vertexed \n";
   string help_MinTrk = "float for min. number of tracks to be vertexed \n";
   string help_MaxChi2 = "float for max. chi2 contribution of a track to the vertex \n";
   string help_TrackCutNorm = "bool for normalizing track chi2 contributions\n";
   //set help strings
   m_Param_d0.setHelpString(help_d0);
   m_Param_z0.setHelpString(help_z0);
   m_Param_TMom.setHelpString(help_TMom);
   m_Param_MinTrk.setHelpString(help_MinTrk);
   m_Param_MaxChi2.setHelpString(help_MaxChi2);
   m_Param_TrackCutNorm.setHelpString(help_TrackCutNorm);
}

// EventVertexHolder::EventVertexHolder( const EventVertexHolder& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

EventVertexHolder::~EventVertexHolder()
{
}

//
// assignment operators
//
// const EventVertexHolder& EventVertexHolder::operator=( const EventVertexHolder& rhs )
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
