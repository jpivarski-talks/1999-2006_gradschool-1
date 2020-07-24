// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawWaferProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawWaferProxy.cc,v 1.4 2003/01/29 19:31:08 cleo3 Exp $
//
// Revision history
//
// $Log: MCRawWaferProxy.cc,v $
// Revision 1.4  2003/01/29 19:31:08  cleo3
// changes needed to compile using g++
//
// Revision 1.3  2002/09/27 20:23:13  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.2  1999/06/04 21:38:55  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:57  bkh
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
// You may have to uncomment some of these or other stl Wafers
// depending on what other Wafer files you include (e.g. FrameAccess etc.)!
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

#include "MCRawData/MCRawWaferProxy.h"


// STL classes
// You may have to uncomment some of these or other stl Wafers
// depending on what other Wafer files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kReport = "MCRawData.MCRawWaferProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawWaferProxy::MCRawWaferProxy() :
   m_RawWafer ( 0 ) ,
   m_words    ( ) 
{
   m_words.reserve( 100 ) ; // allocate reasonable length just once!
}

// MCRawWaferProxy::MCRawWaferProxy( const MCRawWaferProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawWaferProxy::~MCRawWaferProxy()
{
   delete m_RawWafer ;
}

//
// assignment operators
//
// const MCRawWaferProxy& MCRawWaferProxy::operator=( const MCRawWaferProxy& iproxy )
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
MCRawWaferProxy::invalidateCache()
{
   delete m_RawWafer ;
   m_RawWafer = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}

const MCRawWaferProxy::value_type*
MCRawWaferProxy::faultHandler( const Record& iRecord,
			       const DataKey& iKey )
{
   assert( 0 == m_RawWafer ) ;
   assert( m_words.empty()  ) ; // always start out empty

   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;
   m_words.push_back( 0 ) ;

   m_RawWafer = new RawWafer( &(*(m_words.begin())), m_words.size() );

   return m_RawWafer ;
}

//
// const member functions
//

//
// static member functions
//


