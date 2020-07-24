// -*- C++ -*-
//
// Package:     <EventVertexProd>
// Module:      EventVertexInfoProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Michael Watkins
// Created:     Thu May 30 14:41:32 EDT 2002
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
#include "Experiment/units.h"  // for converting to/from standard CLEO units
#include "DAException/DAException.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAItem.h"

#include "EventVertexProd/EventVertexInfoProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#include "EventVertexProd/EventVertexPrivateProxy.h"
#include "EventVertexProd/EventVertexProd.h"
#include "EventVertexProd/EventVertexHolder.h"

#include "EventVertex/EventVertexInfo.h"


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
static const char* const kFacilityString = "EventVertexProd.EventVertexInfoProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: proxyone.cc,v 1.12 2000/12/04 19:11:16 cdj Exp $";
static const char* const kTagString = "$Name: v03_06_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
EventVertexInfoProxy::EventVertexInfoProxy()
   : m_EventVertexInfo( 0 )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &EventVertexInfoProxy::boundMethod, Stream::kBeginRun );
}

// EventVertexInfoProxy::EventVertexInfoProxy( const EventVertexInfoProxy& iproxy )
// {
//   *this = iproxy;
// }

EventVertexInfoProxy::~EventVertexInfoProxy()
{
   delete m_EventVertexInfo ;
}

//
// assignment operators
//
// const EventVertexInfoProxy& EventVertexInfoProxy::operator=( const EventVertexInfoProxy& iproxy )
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
EventVertexInfoProxy::invalidateCache()
{
   delete m_EventVertexInfo ;
   m_EventVertexInfo = 0 ;
}

const EventVertexInfoProxy::value_type*
EventVertexInfoProxy::faultHandler( const Record& iRecord,
                                    const DataKey& iKey )
{

   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_EventVertexInfo );

   //if an exception is thrown during this function, p_EventVertexInfo will
   // automatically delete the object it is refering to
   auto_ptr<EventVertexInfo> p_EventVertexInfo;

   // ---------- create the new object --------------------
   //Extract the EventVertexPrivate
   FAItem< EventVertexPrivate > eventVertexPrivate;
   report( DEBUG, kFacilityString ) << "extracting EventVertexPrivate" <<endl;
   extract( iRecord , eventVertexPrivate );

   report( DEBUG, kFacilityString ) << "assigning vectors" <<endl;
   
   STL_VECTOR(NavTrack::Identifier) vectorOfTrackIDs = eventVertexPrivate->vectorOfTrackIDs();
   STL_VECTOR(double) vectorOfVertexChi2             = eventVertexPrivate->vectorOfChiSquares();
   STL_VECTOR(double) vectorOfTrackChi2              = eventVertexPrivate->vectorOfRemovedTrackChi2();
   
   p_EventVertexInfo.reset( new EventVertexInfo( vectorOfTrackIDs,
                                                 vectorOfVertexChi2,
                                                 vectorOfTrackChi2) );
   
   //Since no exception happened, tell p_EventVertexInfo to give its pointer to
   // m_EventVertexInfo
   return ( m_EventVertexInfo = p_EventVertexInfo.release() ) ;
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
//EventVertexInfoProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< EventVertexInfo >;

PROXY_BIND_METHOD( EventVertexInfoProxy )
//-----------------------------------------------

