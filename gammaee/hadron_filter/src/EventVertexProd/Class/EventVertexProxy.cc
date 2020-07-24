// -*- C++ -*-
//
// Package:     <package>
// Module:      EventVertexProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Michael Watkins
// Created:     Thu May 30 14:41:19 EDT 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#include <memory>  //for auto_ptr

// user include files
#include "Experiment/report.h"

#include "EventVertexProd/EventVertexProxy.h"
#include "EventVertexProd/EventVertexProd.h"
#include "EventVertexProd/EventVertexHolder.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAItem.h"

#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

//Tracking
#include "Navigation/NavTrack.h"
#include "TrackRoot/TRTrackCandidateFitQuality.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRTrackQuality.h"

//vertexing
#include "VXFit/VXFitInterfaceVertex.h"
//#include "VXFit/VXFitVeeCandidate.h"
#include "VXFit/VXFittable.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "EventVertexProd.EventVertexProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: proxyone.cc,v 1.12 2000/12/04 19:11:16 cdj Exp $";
static const char* const kTagString = "$Name: v03_06_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
EventVertexProxy::EventVertexProxy()
   : m_EventVertex( 0 )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &EventVertexProxy::boundMethod, Stream::kBeginRun );
}

// EventVertexProxy::EventVertexProxy( const EventVertexProxy& iproxy )
// {
//   *this = iproxy;
// }

EventVertexProxy::~EventVertexProxy()
{
   delete m_EventVertex ;
}

//
// assignment operators
//
// const EventVertexProxy& EventVertexProxy::operator=( const EventVertexProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }

//
// member functions
//
void
EventVertexProxy::invalidateCache()
{
   delete m_EventVertex ;
   m_EventVertex = 0 ;
}

const EventVertexProxy::value_type*
EventVertexProxy::faultHandler( const Record& iRecord,
			      const DataKey& iKey )
{

   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_EventVertex );

   //if an exception is thrown during this function, p_EventVertex will
   // automatically delete the object it is refering to
   auto_ptr<EventVertex> p_EventVertex;

   //Extract the EventVertexPrivate
   FAItem< EventVertexPrivate > eventVertexPrivate;
   report( DEBUG, kFacilityString ) << "extracting EventVertexPrivate" <<endl;
   extract( iRecord , eventVertexPrivate );

   Hep3Vector vertexPosition      = eventVertexPrivate->vertexPosition();
   HepSymMatrix vertexErrorMatrix(3, 0.);
   vertexErrorMatrix              = eventVertexPrivate->vertexErrMatrix();
   double finalVertexChi2         = eventVertexPrivate->vertexChiSquare();
   Count eventFlag                = eventVertexPrivate->vertexType();
   DABoolean cutNormFlag          = eventVertexPrivate->trackCutNorm();
   report( DEBUG, kFacilityString ) << "assigning numbers" <<endl;
   Count numberTrackPassKinCuts = eventVertexPrivate->numTrackPassKinCuts();
   Count numberTrackRemoved     = eventVertexPrivate->vectorOfRemovedTrackChi2().size();
   Count numberTrackFinalVertex = eventVertexPrivate->numTrackFinalVertex();
   
   //pack into the EventVertex
   p_EventVertex.reset( new EventVertex( vertexPosition,
                                         vertexErrorMatrix,
                                         finalVertexChi2,
                                         eventFlag,
                                         cutNormFlag,
                                         numberTrackPassKinCuts,
                                         numberTrackRemoved,
                                         numberTrackFinalVertex ) );

   
   //Since no exception happened, tell p_EventVertex to give its pointer to
   // m_EventVertex
   return ( m_EventVertex = p_EventVertex.release() ) ;
}

//
// const member functions
//

//
// static member functions
//

//
// 'bound' functions
//

//void
//EventVertexProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< EventVertex >;

PROXY_BIND_METHOD( EventVertexProxy )
//-----------------------------------------------

