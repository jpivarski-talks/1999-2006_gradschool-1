// -*- C++ -*-
//
// Package:     <package>
// Module:      TMClassificationProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Nadia Adam
// Created:     Tue Oct 22 14:49:20 EDT 2002
// $Id: TMClassificationProxy.cc,v 1.1 2002/11/04 18:38:48 nea9 Exp $
//
// Revision history
//
// $Log: TMClassificationProxy.cc,v $
// Revision 1.1  2002/11/04 18:38:48  nea9
// New CleoIII Trkman
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#include <memory>  //for auto_ptr

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"

#include "TrkmanProd/TMClassificationProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#include "Trkman/TMCurlers.h"
#include "Trkman/TMClassification.h"
#include "Trkman/TMData.h"

#include "Navigation/NavTrack.h" 
#include "BeamSpot/BeamSpot.h"


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
static const char* const kFacilityString = "TrkmanProd.TMClassificationProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: TMClassificationProxy.cc,v 1.1 2002/11/04 18:38:48 nea9 Exp $";
static const char* const kTagString = "$Name:  $";

#define iout report( INFO, kFacilityString )

typedef FATable< NavTrack > NavTrackTable;
typedef FAItem<  NavTrack > NavTrackItem;
typedef FATable< NavTrack >::const_iterator NavTrackConstIt;

//
// static data member definitions
//

//
// constructors and destructor
//
TMClassificationProxy::TMClassificationProxy()
   : m_TMClassification( 0 )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &TMClassificationProxy::boundMethod, Stream::kBeginRun );
}

// TMClassificationProxy::TMClassificationProxy( const TMClassificationProxy& iproxy )
// {
//   *this = iproxy;
// }

TMClassificationProxy::~TMClassificationProxy()
{
   delete m_TMClassification ;
}

//
// assignment operators
//
// const TMClassificationProxy& TMClassificationProxy::operator=( const TMClassificationProxy& iproxy )
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
TMClassificationProxy::invalidateCache()
{
   delete m_TMClassification ;
   m_TMClassification = 0 ;
}

const TMClassificationProxy::value_type*
TMClassificationProxy::faultHandler( const Record& iRecord,
				     const DataKey& iKey )
{

   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_TMClassification );

   // **********************************************************************
   // Extract NavTracks from Frame
   // **********************************************************************
   NavTrackTable tracks;
   extract(iRecord, tracks);

   // **********************************************************************
   // Extract the Beam Spot
   // **********************************************************************
   FAItem< BeamSpot > beamSpot;
   extract( iRecord.frame().record(Stream::kBeginRun), beamSpot );

   TMData* data = new TMData( tracks, beamSpot );

   //Get the classifications for each track from Trkman
   m_TMClassification = new TMClassification( tracks, data );
   delete data;

   return ( m_TMClassification ) ;
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
//TMClassificationProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< TMClassification >;

PROXY_BIND_METHOD( TMClassificationProxy )
//-----------------------------------------------







