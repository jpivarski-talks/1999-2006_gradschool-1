// -*- C++ -*-
//
// Package:     <MCTriggerPhaseProd>
// Module:      MCTriggerPhaseProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Wed Jan 31 16:44:21 EST 2001
// $Id: MCTriggerPhaseProxy.cc,v 1.3 2001/12/13 22:08:21 bkh Exp $
//
// Revision history
//
// $Log: MCTriggerPhaseProxy.cc,v $
// Revision 1.3  2001/12/13 22:08:21  bkh
// Fix bug in returned value of smeared trigger phase to
// be the "wrapped" version not the rounded version so
// the value is guaranteed to be 0-->60
//
// Revision 1.2  2001/02/07 02:45:30  lkg
// Added a parameter to allow a specification of a width for gaussian smearing
// of the trigger phase.  Defaults to 0, in which case smearing code is
// short circuited.  Conveniently cures stupid compilation problem at the
// same time.
//
// Revision 1.1.1.1  2001/02/05 16:17:26  lkg
// imported MCTriggerPhaseProd source
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

#include "MCTriggerPhaseProd/MCTriggerPhaseProxy.h"
#include "MCTriggerPhaseProd/MCTriggerPhaseProd.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#include "RandomModule/RandomGenerator.h"

#include "MCBeam/MCTrueRfBucket.h"
#include "C3trig/TrigStream.h"
#include "DBTRIGCesrOffset.hh"
#include "FrameAccess/FAConstants.h"

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
static const char* const kFacilityString = "MCTriggerPhaseProd.MCTriggerPhaseProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCTriggerPhaseProxy.cc,v 1.3 2001/12/13 22:08:21 bkh Exp $";
static const char* const kTagString = "$Name: v01_02_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCTriggerPhaseProxy::MCTriggerPhaseProxy( const MCTriggerPhaseProd* callingProducer )
   : m_MCTriggerPhase( 0 ),
     m_callingProducer( callingProducer )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &MCTriggerPhaseProxy::boundMethod, Stream::kBeginRun );
}

// MCTriggerPhaseProxy::MCTriggerPhaseProxy( const MCTriggerPhaseProxy& iproxy )
// {
//   *this = iproxy;
// }

MCTriggerPhaseProxy::~MCTriggerPhaseProxy()
{
   delete m_MCTriggerPhase ;
}

//
// assignment operators
//
// const MCTriggerPhaseProxy& MCTriggerPhaseProxy::operator=( const MCTriggerPhaseProxy& iproxy )
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
MCTriggerPhaseProxy::invalidateCache()
{
   delete m_MCTriggerPhase ;
   m_MCTriggerPhase = 0 ;
}

const MCTriggerPhaseProxy::value_type*
MCTriggerPhaseProxy::faultHandler( const Record& iRecord,
			      const DataKey& iKey )
{

   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_MCTriggerPhase );


   // get the absolute CESR phase
   FAItem<MCTrueRfBucket> rfBucket;
   extract( iRecord, rfBucket );

   // get the Trigger phase of the first RF bucket. (This is in 14 ns
   // buckets, NOT 42 ns buckets)
   // train1 car1 coincides w/ the first 2 ns bucket (bucket #0)
   FAConstants<DBTRIGCesrOffset> train1Car1Offset;
   extract(iRecord.frame().record(TrigStream::kTrigCesrOffset), 
	   train1Car1Offset);
   int train1Car1Phase = train1Car1Offset.front().get_Offset();
   

   // convert the 2 ns rf bucket number to 14 ns, and add in the trigger
   // offset.  There are 183 possible 14 ns buckets in CESR, so take the
   // result modulo 183
   int triggerPhase14 = ( (rfBucket->bucketNumber() / 7) + train1Car1Phase )
			  % 183;

   // now convert this to a 42 ns trigger phase
   int triggerPhase42 = triggerPhase14 / 3;

   // there is smearing.  Add a hook to do the smearing
   int smearedTriggerPhase42 = smearTriggerPhase( triggerPhase42 );

   // work our way back to the 2 ns phase at the beginning of the
   // smeared trigger phase
   int smearedTriggerPhase14 = smearedTriggerPhase42 * 3;
   int zeroedTriggerPhase14 = (smearedTriggerPhase14 
			       - train1Car1Phase + 183) % 183;
   int cesrPhaseAtTriggerPhaseEdge = zeroedTriggerPhase14 * 7;

   // Now we can get the last information we want, the offset of the true
   // 2 ns CESR phase relative to the smeared trigger phase
   int cesrPhaseOffset = rfBucket->bucketNumber() 
     - cesrPhaseAtTriggerPhaseEdge;

   //if an exception is thrown during this function, p_MCTriggerPhase will
   // automatically delete the object it is referring to
   auto_ptr<MCTriggerPhase> 
     p_MCTriggerPhase( new MCTriggerPhase( cesrPhaseOffset, 
					   smearedTriggerPhase42 ) );

   //Since no exception happened, tell p_MCTriggerPhase to give its pointer to
   // m_MCTriggerPhase
   return ( m_MCTriggerPhase = p_MCTriggerPhase.release() ) ;
}

//
// private member functions
//
int
MCTriggerPhaseProxy::smearTriggerPhase( int unsmearedTriggerPhase ) {

   // no smearing
   if ( m_callingProducer->triggerPhaseWidth() == 0 ) {
      return unsmearedTriggerPhase;
   }
      
   // --- smear phase with a simple gaussian ---
   // Initialize Random Generator
   RandomGenerator& random( RandomGenerator::instance() );

   // smear phase with via a gaussian.  Accomplish by smearing around
   // no shift, then adding in 0.5 to allow use of greatest integer fcn.
   double width = m_callingProducer->triggerPhaseWidth();
   double phaseSmearing = random.gauss( 0, width ) + 0.5;
   double smearedPhase = phaseSmearing + unsmearedTriggerPhase;
   int roundedSmearedPhase = floor( smearedPhase );

   // There are 61 valid trigger phases.  Wrap phases around.
   int wrappedSmearedPhase = (roundedSmearedPhase + 61) % 61;

//   return roundedSmearedPhase; // the wrong thing to do!
   return wrappedSmearedPhase;
}
//
// static member functions
//

//
// 'bound' functions
//

//void
//MCTriggerPhaseProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< MCTriggerPhase >;

PROXY_BIND_METHOD( MCTriggerPhaseProxy )
//-----------------------------------------------

