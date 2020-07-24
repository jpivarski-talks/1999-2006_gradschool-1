// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawLevel3TriggerProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Mon Apr 19 17:35:16 EST 1999
// $Id: MCRawLevel3TriggerProxy.cc,v 1.4 2003/01/29 19:31:06 cleo3 Exp $
//
// Revision history
//
// $Log: MCRawLevel3TriggerProxy.cc,v $
// Revision 1.4  2003/01/29 19:31:06  cleo3
// changes needed to compile using g++
//
// Revision 1.3  2002/09/27 20:23:10  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.2  1999/06/04 21:38:52  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/04/20 01:43:07  bkh
// update for new raw data objects
//
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

#include "MCRawData/MCRawLevel3TriggerProxy.h"


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

static const char* const kReport = "MCRawData.MCRawLevel3TriggerProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawLevel3TriggerProxy::MCRawLevel3TriggerProxy() :
   m_RawLevel3Trigger( 0 ) ,
   m_words    ( ) 
{
   m_words.reserve( 10 ) ; // allocate reasonable length just once!
}

// MCRawLevel3TriggerProxy::MCRawLevel3TriggerProxy( const MCRawLevel3TriggerProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawLevel3TriggerProxy::~MCRawLevel3TriggerProxy()
{
   delete m_RawLevel3Trigger ;
}

//
// assignment operators
//
// const MCRawLevel3TriggerProxy& MCRawLevel3TriggerProxy::operator=( const MCRawLevel3TriggerProxy& iproxy )
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
MCRawLevel3TriggerProxy::invalidateCache()
{
   delete m_RawLevel3Trigger ;
   m_RawLevel3Trigger = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}

const MCRawLevel3TriggerProxy::value_type*
MCRawLevel3TriggerProxy::faultHandler( const Record& iRecord,
				       const DataKey& iKey )
{
   assert( 0 == m_RawLevel3Trigger ) ;
   assert( m_words.empty()  ) ; // always start out empty

   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;

   m_RawLevel3Trigger = new RawLevel3Trigger( &(*(m_words.begin())), m_words.size() );

   return m_RawLevel3Trigger ;
}

//
// const member functions
//

//
// static member functions
//


