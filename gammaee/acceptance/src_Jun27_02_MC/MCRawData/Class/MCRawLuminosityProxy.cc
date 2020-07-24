// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawLuminosityProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Mon Apr 19 17:35:16 EST 1999
// $Id: MCRawLuminosityProxy.cc,v 1.2 1999/06/04 21:38:52 bkh Exp $
//
// Revision history
//
// $Log: MCRawLuminosityProxy.cc,v $
// Revision 1.2  1999/06/04 21:38:52  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/04/20 01:43:08  bkh
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

#include "MCRawData/MCRawLuminosityProxy.h"
#include "RawData/RawLuminosity.h"


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

static const char* const kReport = "MCRawData.MCRawLuminosityProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawLuminosityProxy::MCRawLuminosityProxy() :
   m_RawLuminosity( 0 ) ,
   m_words    ( *new STL_VECTOR( UInt32 ) ) 
{
   m_words.reserve( 1 ) ; // allocate reasonable length just once!
}

// MCRawLuminosityProxy::MCRawLuminosityProxy( const MCRawLuminosityProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawLuminosityProxy::~MCRawLuminosityProxy()
{
   delete m_RawLuminosity ;
   delete &m_words    ;
}

//
// assignment operators
//
// const MCRawLuminosityProxy& MCRawLuminosityProxy::operator=( const MCRawLuminosityProxy& iproxy )
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
MCRawLuminosityProxy::invalidateCache()
{
   delete m_RawLuminosity ;
   m_RawLuminosity = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}

const MCRawLuminosityProxy::value_type*
MCRawLuminosityProxy::faultHandler( const Record& iRecord,
				    const DataKey& iKey )
{
   assert( 0 == m_RawLuminosity ) ;
   assert( m_words.empty()  ) ; // always start out empty

   const UInt32 luminosityValue ( RawLuminosity::k_luminosityFactor*0. ) ;
   m_words.push_back( luminosityValue ) ; // luminosity

   m_RawLuminosity = new RawLuminosity( m_words.begin(), m_words.size() );

   return m_RawLuminosity ;
}

//
// const member functions
//

//
// static member functions
//


