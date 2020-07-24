// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawPreludeProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawPreludeProxy.cc,v 1.4 2001/02/26 00:49:20 cdj Exp $
//
// Revision history
//
// $Log: MCRawPreludeProxy.cc,v $
// Revision 1.4  2001/02/26 00:49:20  cdj
// Now delivers data on StartRun
//
// Revision 1.3  2000/12/15 21:32:51  mahlke
// Return Event Type / header field Version instead of 0
//
// Revision 1.2  1999/06/04 21:38:53  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:54  bkh
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
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "EventDefs/EventTypes.h"

#include "MCRawData/MCRawPreludeProxy.h"


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

static const char* const kReport = "MCRawData.MCRawPreludeProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawPreludeProxy::MCRawPreludeProxy() :
   m_RawPrelude( 0 ) ,
   m_words    ( *new STL_VECTOR( UInt32 ) ) 
{
   m_words.reserve( 10 ) ; // allocate reasonable length just once!
}

// MCRawPreludeProxy::MCRawPreludeProxy( const MCRawPreludeProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawPreludeProxy::~MCRawPreludeProxy()
{
   delete m_RawPrelude ;
   delete &m_words     ;
}

//
// assignment operators
//
// const MCRawPreludeProxy& MCRawPreludeProxy::operator=( const MCRawPreludeProxy& iproxy )
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
MCRawPreludeProxy::invalidateCache()
{
   delete m_RawPrelude ;
   m_RawPrelude = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}

const MCRawPreludeProxy::value_type*
MCRawPreludeProxy::faultHandler( const Record& iRecord,
				 const DataKey& iKey )
{
   UInt16 recordType ;
   UInt16 kVersion = 1 ;

   assert( 0 == m_RawPrelude ) ;
   assert( m_words.empty()  ) ; // always start out empty

   recordType = 0 ;

   if( iRecord.stream() == Stream::kEvent) {recordType = ET_MCEVENT ;} ;
   if( iRecord.stream() == Stream::kStartRun) {recordType = ET_STARTRUN ;} ;
   if( iRecord.stream() == Stream::kBeginRun) {recordType = ET_BEGINMCRUN ;} ;

   UInt32 EvTypeVersion = ( recordType<<16 ) + kVersion ;
 
   m_words.push_back( EvTypeVersion ) ;

   m_RawPrelude = new RawPrelude( m_words.begin(), m_words.size() );

   return m_RawPrelude ;
}

//
// const member functions
//

//
// static member functions
//


