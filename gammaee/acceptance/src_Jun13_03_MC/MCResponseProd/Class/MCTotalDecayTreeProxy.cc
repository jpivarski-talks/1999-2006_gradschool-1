// -*- C++ -*-
//
// Package:     MCResponseProd
// Module:      MCTotalDecayTreeProxy
// 
// Description: 
//
// Implementation:  Conform to interface expected for an MCResponse proxy
//                  1) invoke MCResponseProd's triggerGeantEvent fcn as
//                     first step of proxy
//                  2) bind an updateBeginRun fcn to beginRun that invokes
//                     MCResponsProd's updateBeginRun
//     
//
// Author:      Lawrence Gibbons
// Created:     Wed Oct 27 15:58:25 EDT 1999
// $Id: MCTotalDecayTreeProxy.cc,v 1.3 2000/04/19 17:27:55 lkg Exp $
//
// Revision history
//
// $Log: MCTotalDecayTreeProxy.cc,v $
// Revision 1.3  2000/04/19 17:27:55  lkg
// No longer explicitly holds the decay tree pointer explicity.  Communicates
// with MCResponseProd for access/deletion of the tree.  Avoids memory
// leak that occurred when a tree was created by MCResponseProd, but no one
// extracted a tree from the frame, so the MCTotalDecayTreeProxy's pointer
// was never set. Hence, the tree was never deleted.
//
// Revision 1.2  2000/04/19 00:44:21  pg
// Added protection against TOO MANY HITS case. Extract Si geometry from SVAlignment stream.
//
// Revision 1.1  2000/01/26 23:39:04  lkg
// A proxy that conforms to the behaviour of the MCResponse-type proxies
// that trigger GEANT.  It supplies the geant-modified decay tree that
// gets formed in MCResponseProd::triggerGeantEvent.
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"

#include "MCResponseProd/MCTotalDecayTreeProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

// Producer that calls this proxy
#include "MCResponseProd/MCResponseProd.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kReport = "MCResponseProd.MCTotalDecayTreeProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCTotalDecayTreeProxy.cc,v 1.3 2000/04/19 17:27:55 lkg Exp $";
static const char* const kTagString = "$Name: v06_02_06 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCTotalDecayTreeProxy::MCTotalDecayTreeProxy( MCResponseProd& iProducer ) :
   m_producer( &iProducer )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   bind( &MCTotalDecayTreeProxy::updateBeginRun, Stream::kBeginRun );
}

// MCTotalDecayTreeProxy::MCTotalDecayTreeProxy( const MCTotalDecayTreeProxy& iproxy )
// {
//   *this = iproxy;
// }

MCTotalDecayTreeProxy::~MCTotalDecayTreeProxy()
{
   m_producer->deleteGeantModifiedDecayTree();
}

//
// assignment operators
//
// const MCTotalDecayTreeProxy& MCTotalDecayTreeProxy::operator=( const MCTotalDecayTreeProxy& iproxy )
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
MCTotalDecayTreeProxy::invalidateCache()
{
   // Tell the producer that we need to trigger geant for the next event
   m_producer->invalidateGeantEvent() ;

   // have the producer kill the decay tree it holds
   m_producer->deleteGeantModifiedDecayTree();
}

const MCTotalDecayTreeProxy::value_type*
MCTotalDecayTreeProxy::faultHandler( const Record& iRecord,
				     const DataKey& iKey )
{
   // Phase 1 - run Geant
   // Trigger Geant for this event.
   // m_producer points to the producer providing this proxy (MCResponseProd)
   // and call the function triggerGeantEvent to trigger Geant if it hasn't
   // been done for this event.
   report( DEBUG, kReport ) << "Calling triggerGeantEvent" << endl;
   m_producer->triggerGeantEvent( iRecord.frame() );

   // Phase 2 - get the MCDecayTree that gets updated as GEANT runs from
   // MCResponseProd, and insert that tree into the frame
   return ( m_producer->geantModifiedDecayTree() ) ;
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
void MCTotalDecayTreeProxy::updateBeginRun( const Record& iRecord )
{
   // Make sure Cleog begin run data is valid.
   // This bindable proxy is tied to the beginRun stream.
   // m_producer points to MCResponseProd producer which has the function
   // updateCleogBeginRun which checks if begin run is valid

   m_producer->updateCleogBeginRun(  iRecord.frame() );
}


//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< MCDecayTree >;

PROXY_BIND_METHOD( MCTotalDecayTreeProxy )
//-----------------------------------------------

