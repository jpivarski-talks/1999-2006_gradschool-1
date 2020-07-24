// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawEventDataProxy
// 
// Description: Fill RawEventData in proper format with raw data
//
// Implementation:
//
//                We use the alternate RawEventData constructor
//                to avoid copying the data. Each raw unit
//                is in an STL vector whose address is passed
//                to the RawEventData constructor.
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawEventDataProxy.cc,v 1.9 2003/04/15 22:07:35 bkh Exp $
//
// Revision history
//
// $Log: MCRawEventDataProxy.cc,v $
// Revision 1.9  2003/04/15 22:07:35  bkh
// Check for basegeometry record not beginrun
//
// Revision 1.8  2003/04/11 20:38:06  bkh
// Get DetectorConfiguration from basegeometry now not beginrun
//
// Revision 1.7  2002/10/01 20:30:40  bkh
// Event: Do not ask for beginrun while in an endrun
// Cathodes: move local arrays to member data to avoid stack load
//
// Revision 1.6  2002/09/27 20:23:09  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.5  2000/12/15 21:32:50  mahlke
// Return Event Type / header field Version instead of 0
//
// Revision 1.4  2000/04/17 20:07:57  bkh
// Elim checks of ptr after new
//
// Revision 1.3  1999/06/15 14:56:08  bkh
// Improve CC simulation with MC gain;
//       allow missing detectors in MCRawEventDataProxy
//
// Revision 1.2  1999/03/11 20:16:23  bkh
// Update raw event proxy for new raw event features
//
// Revision 1.1  1999/02/25 22:02:51  bkh
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
#include <string>
#include <vector>
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

#include "MCRawData/MCRawEventDataProxy.h"

#include "RawData/RawCCHits.h"
#include "RawData/RawCathodes.h"
#include "RawData/RawDRHits.h"
#include "RawData/RawZDHits.h"
#include "RawData/RawHeader.h"
#include "RawData/RawMUHits.h"
#include "RawData/RawPrelude.h"
#include "RawData/RawRichHits.h"
#include "RawData/RawSVHits.h"
#include "RawData/RawTrigger.h"
#include "RawData/RawWafer.h"
#include "DAException/DANoDataException.h"

#include "DetectorConfiguration/DetectorConfiguration.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kReport = "MCRawData.MCRawEventDataProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawEventDataProxy::MCRawEventDataProxy() :
   m_RawEventData ( 0 )
{
}

// MCRawEventDataProxy::MCRawEventDataProxy( const MCRawEventDataProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawEventDataProxy::~MCRawEventDataProxy()
{
   delete m_RawEventData ;
}

//
// assignment operators
//
// const MCRawEventDataProxy& MCRawEventDataProxy::operator=( const MCRawEventDataProxy& iproxy )
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
MCRawEventDataProxy::invalidateCache()
{
   delete m_RawEventData ;
   m_RawEventData = 0 ;
}

const MCRawEventDataProxy::value_type*
MCRawEventDataProxy::faultHandler( const Record&  iRecord ,
				   const DataKey& iKey      )
{
   assert( 0 == m_RawEventData ) ;

   STL_VECTOR( const BaseRawData* ) bases ;
   bases.reserve( 20 ) ;

   FAItem< RawPrelude > prelude ; 
   extract( iRecord, prelude ); 
   bases.push_back( &(*prelude) ) ;

   FAItem< RawHeader > header ; 
   extract( iRecord, header ); 
   bases.push_back( &(*header) ) ;

   try { 
     FAItem< RawCCHits > ccHits ; 
     extract( iRecord, ccHits ); 
     bases.push_back( &(*ccHits) ) ;
   } catch ( DANoDataException<FAItem<RawCCHits>::contents> &iException ){};

   try { 
     FAItem< RawCathodes > cathodes ; 
     extract( iRecord, cathodes ); 
     bases.push_back( &(*cathodes) ) ;
   } catch ( DANoDataException<FAItem<RawCathodes>::contents> &iException ){};

   try { 
     FAItem< RawDRHits > drHits ; 
     extract( iRecord, drHits ); 
     bases.push_back( &(*drHits) ) ;
   } catch ( DANoDataException<FAItem<RawDRHits>::contents> &iException ){};

   try { 
     FAItem< RawMUHits > muHits ; 
     extract( iRecord, muHits ); 
     bases.push_back( &(*muHits) ) ;
   } catch ( DANoDataException<FAItem<RawMUHits>::contents> &iException ){};

   try { 
     FAItem< RawRichHits > richHits ; 
     extract( iRecord, richHits ); 
     bases.push_back( &(*richHits) ) ;
   } catch ( DANoDataException<FAItem<RawRichHits>::contents> &iException ){};


   if( iRecord.frame().contains( Stream::kBaseGeometry ) )
   {
      FAItem< DetectorConfiguration >                           iConfig ; 
      extract( iRecord.frame().record( Stream::kBaseGeometry ), iConfig ); 
      if( iConfig->useSInotZD() )
      {
	 try { 
	    FAItem< RawSVHits > svHits ; 
	    extract( iRecord, svHits ); 
	    bases.push_back( &(*svHits) ) ;
	 } catch ( DANoDataException<FAItem<RawSVHits>::contents> &iException ){};
      }

      if( iConfig->useZDnotSI() )
      {
	 try { 
	    FAItem< RawZDHits > zdHits ; 
	    extract( iRecord,   zdHits ); 
	    bases.push_back( &(*zdHits) ) ;
	 } catch ( DANoDataException<FAItem<RawZDHits>::contents> &iException ){};
      }
   }

   try { 
     FAItem< RawTrigger > trigger ; 
     extract( iRecord, trigger ); 
     bases.push_back( &(*trigger) ) ;
   } catch ( DANoDataException<FAItem<RawTrigger>::contents> &iException ){};

   try { 
     FAItem< RawWafer > wafer ; 
     extract( iRecord, wafer ); 
     bases.push_back( &(*wafer) ) ;
   } catch ( DANoDataException<FAItem<RawWafer>::contents> &iException ){};

   m_RawEventData = new RawEventData( bases ) ;

   if( !m_RawEventData->valid() )
   {
      report( ERROR, kReport ) << "Invalid RawEventData object" << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }

   return m_RawEventData ;
}

//
// const member functions
//

//
// static member functions
//


