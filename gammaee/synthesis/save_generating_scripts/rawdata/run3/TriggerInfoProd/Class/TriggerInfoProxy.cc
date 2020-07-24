// -*- C++ -*-
//
// Package:     <TriggerInfoProd>
// Module:      TriggerInfoProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Mon Apr  5 12:24:26 EDT 2004
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

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"

#include "TriggerInfoProd/TriggerInfoProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#include "TriggerData/TriggerData.h" 
#include "CleoDB/DBEventHeader.h"

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
static const char* const kFacilityString = "TriggerInfoProd.TriggerInfoProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: proxyone.cc,v 1.12 2000/12/04 19:11:16 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
TriggerInfoProxy::TriggerInfoProxy()
   : m_TriggerInfo( 0 )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &TriggerInfoProxy::boundMethod, Stream::kBeginRun );
}

// TriggerInfoProxy::TriggerInfoProxy( const TriggerInfoProxy& iproxy )
// {
//   *this = iproxy;
// }

TriggerInfoProxy::~TriggerInfoProxy()
{
   delete m_TriggerInfo ;
}

//
// assignment operators
//
// const TriggerInfoProxy& TriggerInfoProxy::operator=( const TriggerInfoProxy& iproxy )
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
TriggerInfoProxy::invalidateCache()
{
   delete m_TriggerInfo ;
   m_TriggerInfo = 0 ;
}

const TriggerInfoProxy::value_type*
TriggerInfoProxy::faultHandler( const Record& iRecord,
			      const DataKey& iKey )
{

   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_TriggerInfo );

   //if an exception is thrown during this function, p_TriggerInfo will
   // automatically delete the object it is refering to
   auto_ptr<TriggerInfo> p_TriggerInfo;
   
   FAItem<TriggerData> trigger;
   extract(iRecord, trigger);

   FAItem<DBEventHeader> header;
   extract(iRecord, header);

   int bucket = -1;
   if (header->monteCarlo()) {
      bucket = -2;
   }
   else if (trigger.valid()) {
      bucket = trigger->getLumiL1AcceptBucket();
   }

   if (bucket == -1) {
      p_TriggerInfo.reset(new TriggerInfo());
   }
   else if (bucket == -2) {
      int axial(0), stereo(0), cblo(0), cbmd(0);

      for (int b = 0;  b < 4;  b++) {
	 if (trigger->getAxTrackCount(b) > axial) {
	    axial = trigger->getAxTrackCount(b);
	 }
	 if (trigger->getLoTrackCount(b) + trigger->getHiTrackCount(b) > stereo) {
	    stereo = trigger->getLoTrackCount(b) + trigger->getHiTrackCount(b);
	 }
	 if (trigger->getCBLoCount(b) > cblo) {
	    cblo = trigger->getCBLoCount(b);
	 }
	 if (trigger->getCBMdCount(b) > cbmd) {
	    cbmd = trigger->getCBMdCount(b);
	 }
      }

      p_TriggerInfo.reset(new TriggerInfo(axial, stereo, cblo, cbmd));
   }
   else {
      p_TriggerInfo.reset(new TriggerInfo(
			     trigger->getAxTrackCount(bucket),
			     trigger->getLoTrackCount(bucket) + trigger->getHiTrackCount(bucket),
			     trigger->getCBLoCount(bucket),
			     trigger->getCBMdCount(bucket)));
   }

   //Since no exception happened, tell p_TriggerInfo to give its pointer to
   // m_TriggerInfo
   return ( m_TriggerInfo = p_TriggerInfo.release() ) ;
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
//TriggerInfoProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< TriggerInfo >;

PROXY_BIND_METHOD( TriggerInfoProxy )
//-----------------------------------------------

