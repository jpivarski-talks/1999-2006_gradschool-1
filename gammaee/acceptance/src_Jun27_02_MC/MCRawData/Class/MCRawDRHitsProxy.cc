// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawDRHitsProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawDRHitsProxy.cc,v 1.11 2001/04/30 17:05:22 mahlke Exp $
//
// Revision history
//
// $Log: MCRawDRHitsProxy.cc,v $
// Revision 1.11  2001/04/30 17:05:22  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.10  2000/05/09 13:28:19  pg
// Added realistic gain for Si, extract DR active element from DRAlignment
//
// Revision 1.9  2000/01/21 14:39:51  bkh
// Update name of hitIsEff() fcn as per MCDRResponse
//
// Revision 1.8  1999/12/21 23:44:36  jjo
// Add CellId to cdoffcal calls
//
// Revision 1.7  1999/12/17 15:57:21  cdj
// removed inappropriate use of typename, again
//
// Revision 1.6  1999/12/13 02:10:45  jjo
// Require Response hits to be efficient & calc fraction of
// efficient responses, remove valid() checks from extracts
// (not needed anymore).
//
// Revision 1.5  1999/11/03 00:00:14  lyon
// Revamped to remove TQT proxy
//
// Revision 1.4  1999/10/26 22:16:25  lyon
// uses TQT objects
//
// Revision 1.2  1999/06/04 21:38:51  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:50  bkh
// fix name conflicts
//
// Revision 1.1.1.1  1999/02/25 20:29:11  bkh
// imported MCRawData sources
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

#include "MCRawData/MCRawDRHitsProxy.h"

#include "MCResponse/MCDRResponse.h" 
#include "MCRawData/MCDRTQT.h"

#include "RawData/RawHits.h" 

#include "ADRGeom/ADRSenseWireStore.h"
#include "CDOffCal/DriftFunction.h"

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

static const char* const kReport = "MCRawData.MCRawDRHitsProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawDRHitsProxy::MCRawDRHitsProxy( const Parameter<DABoolean>& m_makeMCRawDRHits) :
   m_RawDRHits( 0 ) ,
   m_words    ( *new STL_VECTOR( UInt32 ) ) 
{
   iMakeMCRawDRHits = m_makeMCRawDRHits.value();

   report ( DEBUG, kReport) << "iMakeMCRawDRHits: " << iMakeMCRawDRHits << endl;
   m_words.reserve( 2000 ) ; // allocate reasonable length just once!
}

// MCRawDRHitsProxy::MCRawDRHitsProxy( const MCRawDRHitsProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawDRHitsProxy::~MCRawDRHitsProxy()
{
   delete m_RawDRHits ;
   delete &m_words    ;
}

//
// assignment operators
//
// const MCRawDRHitsProxy& MCRawDRHitsProxy::operator=( const MCRawDRHitsProxy& iproxy )
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
MCRawDRHitsProxy::invalidateCache()
{
   delete m_RawDRHits ;
   m_RawDRHits = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}

const MCRawDRHitsProxy::value_type*
MCRawDRHitsProxy::faultHandler( const Record&  iRecord ,
				const DataKey& iKey      )
{
   assert( 0 == m_RawDRHits ) ;
   assert( m_words.empty()  ) ; // always start out empty


   // check if MCRawDRHits are wanted at all; otherwise leave m_RawDRHits empty 
 
   if (iMakeMCRawDRHits != 0) 
   {


   /////// Here we create TQT objects from the responses

   // Make a vector of TQT pointers (one for each wire)
   // The vector index corresponds to cellId-1.
   STL_VECTOR(MCDRTQT*) tqts(ADRSenseWireStore::kNumberOfWiresTotal);
  
   // Extract MCDRResponses
   FATable< MCDRResponse > responses ; 
   extract( iRecord, responses ); 
   report(DEBUG, kReport) << "There are " << responses.size() << " DR Responses" << endl;

   // count number of responses that were efficient
   Count numEffResponses = 0;

   // Loop over the responses
   for ( FATable<MCDRResponse>::const_iterator responseIter = responses.begin() ;
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
	    tqts[cellId-1] = new MCDRTQT(*responseIter);
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
      report(DEBUG, kReport) << "Average efficiency of DR Responses = "
			     <<  float(numEffResponses)/float(numResponses) << endl
			     << "numEffResponses=" << numEffResponses
			     << " numResponses="<< numResponses
			     << endl;
   }

   
   //// Now we use the responses to make raw DR hits.
   //// If you want to add noise/embed events, you should turn
   //// their raw hits into MCDRResponse objects and add them to the
   //// appropriate TQT's here. The TQT's will then correctly simulate
   //// how times and charges for multiple hits are read out.
   
   // Extract the active DR geometry
   FAItem< ADRSenseWireStore > senseWireStore;
   extract( (iRecord.frame()).record(Stream::kDRAlignment), senseWireStore);

   // Extract the drift function
   FAItem<DriftFunction> calibration;
   extract( (iRecord.frame()).record(Stream::kBeginRun), calibration);
   
   // Loop over the TQT responses
   for ( unsigned int i = 0 ; i < ADRSenseWireStore::kNumberOfWiresTotal;
	 ++i )
   {

     // Does this cell have a TQT (if not, then the cell wasn't hit)
     if ( tqts[i] == 0 ) continue;  // go to the next one

     // Get the TQT
     MCDRTQT* pTqt = tqts[i];

     // Tell it to dump
     //pTqt->dump(report(INFO, kReport));

     // Get the cell ID from this TQT
     int cellId = pTqt->cellId();

     // Get the daqId for this cell id (should use map)
     const DRDatum::DaqIdType daqId = cellId;

     // Let's get the charge from this TQT
     float totalCharge = pTqt->collectedChargeFromTQT();

     // Let's get the times from the TQT
     STL_VECTOR(float) times = pTqt->driftTimesFromTQT();
     
     // Determine the ADC value for the charge
     DRDatum::DigiType adc = calibration->charge2adc(cellId, totalCharge );

     // Now we build the raw data words for these hits
     // First the charge:
     DRDatum::IsTimeType isTime = false;
      DRDatum::ControlType control = DRDatum::packControl(isTime);

     // pack and add to the word list
     m_words.push_back(RawHits<DRDatum>::packRawWord(daqId, control, adc));

     //report(INFO, kReport) << "Adding raw hit daqid " << daqId 
     //                            << " adc " << adc
     //				   << " tdc: ";

     // Now add the times
     isTime = true;
     control = DRDatum::packControl(isTime);

     // Determine the radius of the layer where this cell resides
     // (from the cell id)
     ADRSenseWireStore::LayerWire layerWire 
       = senseWireStore->layerWire(cellId);
     double layerRadius = senseWireStore->radiusNominal(layerWire.first);
     
     for ( unsigned int j = 0; j < times.size(); ++j )
     {
       
       // Convert the time to tdc
       DRDatum::DigiType tdc = calibration->time2tdc(cellId, times[j], layerRadius);
       
       m_words.push_back(
			 RawHits<DRDatum>::packRawWord(daqId, control, tdc));

       //report(INFO, kReport) << tdc << " ";
     }

     //report(INFO, kReport) << endl;

     // We no longer need this TQT - delete it
     delete pTqt;
     tqts[i] = 0;

   } // Loop over TQTs
   
   // continue here in case no MCRawDRHits were wanted (above)
   }


   m_RawDRHits = new RawDRHits( m_words.begin(), m_words.size() );
   
   return m_RawDRHits ;
}

//
// const member functions
//

//
// static member functions
//


