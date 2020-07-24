// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawZDHitsProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawZDHitsProxy.cc,v 1.12 2003/10/31 18:55:47 huanggs Exp $
//
// Revision history
// $Log: MCRawZDHitsProxy.cc,v $
// Revision 1.12  2003/10/31 18:55:47  huanggs
// INFO->DEBUG
//
// Revision 1.11  2003/06/26 18:06:48  huanggs
// fix
//
// Revision 1.10  2003/04/24 17:38:39  huanggs
// changed with ZDDriftFunctionProd
//
// Revision 1.9  2003/04/24 14:34:10  huanggs
// workable version
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
#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif /* MULTISET_IS_SEPARATE_FILE_BUG */ 
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"

#include "MCRawData/MCRawZDHitsProxy.h"

#include "MCResponse/MCZDResponse.h" 
#include "MCRawData/MCZDTQT.h"

#include "RawData/RawHits.h" 

#include "AZDGeom/AZDSenseWireStore.h"
#include "ZDDriftFunctionProd/ZDDriftFunction.h"
#include "DetectorConfiguration/DetectorConfiguration.h"
#include "DAException/DANoDataException.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif /* MULTISET_IS_SEPARATE_FILE_BUG */ 
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kReport = "MCRawData.MCRawZDHitsProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawZDHitsProxy::MCRawZDHitsProxy(
   const Parameter<DABoolean>& aMakeMCRawZDHits) :
   m_RawZDHits( 0 ) ,
   m_words    ()    ,
   m_makeMCRawZDHits ( aMakeMCRawZDHits )
{
   report ( DEBUG, kReport) 
      << "MakeMCRawZDHits: " << m_makeMCRawZDHits.value() << endl;
   m_words.reserve( 2000 ) ; // allocate reasonable length just once!
}

// MCRawZDHitsProxy::MCRawZDHitsProxy( const MCRawZDHitsProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawZDHitsProxy::~MCRawZDHitsProxy()
{
   delete m_RawZDHits ;
}

//
// assignment operators
//
// const MCRawZDHitsProxy& MCRawZDHitsProxy::operator=( const MCRawZDHitsProxy& iproxy )
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
MCRawZDHitsProxy::invalidateCache()
{
   delete m_RawZDHits ;
   m_RawZDHits = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}

const MCRawZDHitsProxy::value_type*
MCRawZDHitsProxy::faultHandler( const Record&  iRecord ,
				const DataKey& iKey      )
{
   FAItem<DetectorConfiguration>                              iConfig   ;
   extract( iRecord.frame().record( Stream::kBaseGeometry ) , iConfig ) ;
   if( iConfig->useSInotZD() )
   {
      throw DANoDataException< RawZDHits >( iRecord.stream(),iKey ) ;
   }

   assert( 0 == m_RawZDHits ) ;
   assert( m_words.empty()  ) ; // always start out empty


   // check if MCRawZDHits are wanted at all; otherwise leave m_RawZDHits empty 
 
   if ( m_makeMCRawZDHits.value() ) 
   {

   /////// Here we create TQT objects from the responses

   // Make a vector of TQT pointers (one for each wire)
   // The vector index corresponds to cellId-1.
   STL_VECTOR(MCZDTQT*) tqts(AZDSenseWireStore::kNumberOfSenseWires);
  
   // Extract MCZDResponses
   FATable< MCZDResponse > responses ; 
   extract( iRecord, responses ); 
   report(DEBUG, kReport) << "There are " << responses.size() 
			 << " ZD Responses" 
			 << ", and # sense wires = " << tqts.size() << endl;

   // count number of responses that were efficient
   Count numEffResponses = 0;

   // Loop over the responses
   for ( FATable<MCZDResponse>::const_iterator responseIter = responses.begin() ;
	 responseIter != responses.end() ; ++responseIter )
   {
      // Require this response hit to be efficient, 
      if ( responseIter->hitIsEff() )
      {
	 // increment number of efficient responses
	 numEffResponses++;
	 
	 // Get cell id for this response
	 Count cellId = responseIter->cellId();

	 // Do we already have a TQT object for this cell id?
	 if ( tqts[cellId-1] == 0)
	 {
	    
	    // Not there - we make a new one
	    // report(DEBUG, kReport) << "Making new TQT object " << endl;
	    
	    // Stick it in the vector
	    tqts[cellId-1] = new MCZDTQT(*responseIter);
	 }
	 else
	 {
	    // We've already made a TQT for this cell. This must be an
	    // additional hit for this cell. Add the response to the TQT
	    //       report(DEBUG, kReport) << "Using old TQT " << endl;
	    tqts[cellId-1]->addResponse(*responseIter);
	 }

      } // Require efficient response hit
      
   } // loop over repsonses

   // report average efficiency of responses
   Count numResponses = responses.size();
   if ( numResponses != 0 )
   {
      report(DEBUG, kReport) << "Average efficiency of ZD Responses = "
			     <<  float(numEffResponses)/float(numResponses) << endl
			     << "numEffResponses=" << numEffResponses
			     << " numResponses="<< numResponses
			     << endl;
   }

   
   //// Now we use the responses to make raw ZD hits.
   //// If you want to add noise/embed events, you should turn
   //// their raw hits into MCZDResponse objects and add them to the
   //// appropriate TQT's here. The TQT's will then correctly simulate
   //// how times and charges for multiple hits are read out.
   
   // Extract the active ZD geometry
   FAItem< AZDSenseWireStore > senseWireStore;
   extract( (iRecord.frame()).record(Stream::kZDAlignment), senseWireStore);

   // Extract the drift function
   FAItem<ZDDriftFunction> calibration;
   extract( (iRecord.frame()).record(Stream::kBeginRun), calibration);
   
   // Loop over the TQT responses
   for ( unsigned int i = 0 ; i < AZDSenseWireStore::kNumberOfSenseWires;
	 ++i )
   {
     // Does this cell have a TQT (if not, then the cell wasn't hit)
     if ( tqts[i] == 0 ) continue;  // go to the next one

     // Get the TQT
     MCZDTQT* pTqt = tqts[i];

     // Tell it to dump
     //pTqt->dump(report(INFO, kReport));

     // Get the cell ID from this TQT
     int cellId = pTqt->cellId();

     // Get the daqId for this cell id (should use map)
     const ZDDatum::DaqIdType daqId = cellId;

     // Let's get the charge from this TQT
     float totalCharge = pTqt->collectedChargeFromTQT();

     // Let's get the times from the TQT
     STL_VECTOR(float) times = pTqt->driftTimesFromTQT();
     
     // Determine the ADC value for the charge
     ZDDatum::DigiType adc = calibration->charge2adc(cellId, totalCharge );

     // Now we build the raw data words for these hits
     // First the charge:
     ZDDatum::IsTimeType isTime = false;
      ZDDatum::ControlType control = ZDDatum::packControl(isTime);

     // pack and add to the word list
     m_words.push_back(RawHits<ZDDatum>::packRawWord(daqId, control, adc));

     //report(INFO, kReport) << "Adding raw hit daqid " << daqId 
     //                            << " adc " << adc
     //				   << " tdc: ";

     // Now add the times
     isTime = true;
     control = ZDDatum::packControl(isTime);

     // Determine the radius of the layer where this cell resides
     // (from the cell id)
     AZDSenseWireStore::LayerWire layerWire 
       = senseWireStore->layerWire(cellId);
     double layerRadius = senseWireStore->radiusNominal(layerWire.first);
     
     for ( unsigned int j = 0; j < times.size(); ++j )
     {
       
       // Convert the time to tdc
	ZDDatum::DigiType tdc = calibration->time2tdc(cellId, times[j], layerRadius);
       
	m_words.push_back(
	   RawHits<ZDDatum>::packRawWord(daqId, control, tdc));
       //report(INFO, kReport) << tdc << " ";
     }

     //report(INFO, kReport) << endl;

     // We no longer need this TQT - delete it
     delete pTqt;
     tqts[i] = 0;
   } // Loop over TQTs

   // continue here in case no MCRawZDHits were wanted (above)
   }

   m_RawZDHits = new RawZDHits( &(*(m_words.begin())), m_words.size() );

   return m_RawZDHits ;
}

//
// const member functions
//

//
// static member functions
//
