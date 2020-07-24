// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawHeaderProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawHeaderProxy.cc,v 1.7 2003/01/29 19:31:05 cleo3 Exp $
//
// Revision history
//
// $Log: MCRawHeaderProxy.cc,v $
// Revision 1.7  2003/01/29 19:31:05  cleo3
// changes needed to compile using g++
//
// Revision 1.6  2002/09/27 20:23:10  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.5  2002/01/24 19:05:28  bkh
// Prevent crash on endrun in timing comparison
//
// Revision 1.4  2001/06/04 03:21:57  bkh
// Tune CC
//
// Revision 1.3  1999/06/04 21:38:51  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.2  1999/03/11 20:16:23  bkh
// Update raw event proxy for new raw event features
//
// Revision 1.1  1999/02/25 22:02:53  bkh
// fix name conflicts
//
// Revision 1.1.1.1  1999/02/25 20:29:12  bkh
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

#include "MCRawData/MCRawHeaderProxy.h"

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

static const char* const kReport = "MCRawData.MCRawHeaderProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawHeaderProxy::MCRawHeaderProxy() :
   m_RawHeader( 0 ) ,
   m_words    () 
{
   m_words.reserve( 10 ) ; // allocate reasonable length just once!
}

// MCRawHeaderProxy::MCRawHeaderProxy( const MCRawHeaderProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawHeaderProxy::~MCRawHeaderProxy()
{
   delete m_RawHeader ;
}

//
// assignment operators
//
// const MCRawHeaderProxy& MCRawHeaderProxy::operator=( const MCRawHeaderProxy& iproxy )
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
MCRawHeaderProxy::invalidateCache()
{
   delete m_RawHeader ;
   m_RawHeader = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}

const MCRawHeaderProxy::value_type*
MCRawHeaderProxy::faultHandler( const Record& iRecord,
				const DataKey& iKey )
{
   assert( 0 == m_RawHeader ) ;
   assert( m_words.empty()  ) ; // always start out empty

   const SyncValue&    syncValue ( iRecord.syncValue() );
   const UInt64 time ( syncValue.time() ) ;

   if( iRecord.frame().contains( Stream::kEvent ) &&
       ( 1 >=
	 iRecord.frame().record( Stream::kEvent ).syncValue().time() ) ) 
   {
      report( EMERGENCY, kReport ) << "Bad MC time = " << time 
				   << ", should be " 
				   << DBEventHeader::k_MCTime 
				   << "\n\n Did you forget to select the "
				   << "proper source for Monte Carlo "
				   << "SyncValues ?" 
				   << endl ;
      assert( false ) ;
   }

   m_words.push_back( time >> 32 ) ; // first time word
   m_words.push_back( time & (~(UInt32)0) ) ; // second time word
   m_words.push_back( syncValue.runNumber()   ) ; // run number
   m_words.push_back( syncValue.eventNumber() ) ; // event number
   m_words.push_back( 0 ) ; // LVL3 tag word

   m_RawHeader = new RawHeader( &(*(m_words.begin())), m_words.size() );

   return m_RawHeader ;
}

//
// const member functions
//

//
// static member functions
//


