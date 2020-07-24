// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawRunControlProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Mon Apr 19 17:35:16 EST 1999
// $Id: MCRawRunControlProxy.cc,v 1.2 1999/06/04 21:38:54 bkh Exp $
//
// Revision history
//
// $Log: MCRawRunControlProxy.cc,v $
// Revision 1.2  1999/06/04 21:38:54  bkh
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

#include "RawData/RawRunControl.h"
#include "RawData/RawEventData.h" // for string2Name
#include "MCRawData/MCRawRunControlProxy.h"


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

static const char* const kReport = "MCRawData.MCRawRunControlProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawRunControlProxy::MCRawRunControlProxy() :
   m_RawRunControl( 0 ) ,
   m_words    ( *new STL_VECTOR( UInt32 ) ) 
{
   m_words.reserve( 10 ) ; // allocate reasonable length just once!
}

// MCRawRunControlProxy::MCRawRunControlProxy( const MCRawRunControlProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawRunControlProxy::~MCRawRunControlProxy()
{
   delete m_RawRunControl ;
   delete &m_words    ;
}

//
// assignment operators
//
// const MCRawRunControlProxy& MCRawRunControlProxy::operator=( const MCRawRunControlProxy& iproxy )
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
MCRawRunControlProxy::invalidateCache()
{
   delete m_RawRunControl ;
   m_RawRunControl = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}

const MCRawRunControlProxy::value_type*
MCRawRunControlProxy::faultHandler( const Record& iRecord,
				    const DataKey& iKey )
{
   assert( 0 == m_RawRunControl ) ;
   assert( m_words.empty()  ) ; // always start out empty

   const UInt32 bFieldName  ( RawEventData::string2Name( 
      RawRunControl::k_cleoSolenoidFieldName ) ) ;
   const UInt32 bFieldValue ( 
      RawRunControl::k_cleoSolenoidFieldFactor*0. ) ;
   m_words.push_back( bFieldName  ) ;
   m_words.push_back( bFieldValue ) ; // solenoid B-Field

   const UInt32 beamEnergyName ( RawEventData::string2Name( 
      RawRunControl::k_beamEnergyName ) ) ;
   const UInt32 beamEnergyValue ( 
      RawRunControl::k_beamEnergyFactor*0. ) ;
   m_words.push_back( beamEnergyName  ) ;
   m_words.push_back( beamEnergyValue ) ; // beam energy

   const UInt32 crossingAngleName ( RawEventData::string2Name( 
      RawRunControl::k_crossingAngleName ) ) ;
   const UInt32 crossingAngleValue ( 
      RawRunControl::k_crossingAngleFactor*0. ) ;
   m_words.push_back( crossingAngleName  ) ;
   m_words.push_back( crossingAngleValue ) ; // crossing angle 

   const UInt32 cesrFillNumberName ( RawEventData::string2Name( 
      RawRunControl::k_cesrFillNumberName ) ) ;
   const UInt16 day  ( 0 ) ;
   const UInt16 fill ( 0 ) ;
   const UInt32 cesrFillNumberValue ( 100*day + fill ) ;
   m_words.push_back( cesrFillNumberName  ) ;
   m_words.push_back( cesrFillNumberValue ) ; // cesr fill number

   const UInt32 triggerVersionMajorName ( RawEventData::string2Name( 
      RawRunControl::k_triggerVersionNames.first ) ) ;
   const UInt32 triggerVersionMajorValue ( 0 ) ;
   m_words.push_back( triggerVersionMajorName  ) ;
   m_words.push_back( triggerVersionMajorValue ) ; // trigger version major

   const UInt32 triggerVersionMinorName ( RawEventData::string2Name( 
      RawRunControl::k_triggerVersionNames.second ) ) ;
   const UInt32 triggerVersionMinorValue ( 0 ) ;
   m_words.push_back( triggerVersionMinorName  ) ;
   m_words.push_back( triggerVersionMinorValue ) ; // trigger version minor

   const UInt32 quadCurrents0Name ( RawEventData::string2Name( 
      RawRunControl::k_quadCurrentsName + "0" ) ) ;
   const UInt32 quadCurrents0Value ( 
      RawRunControl::k_quadCurrentsFactor*0. ) ;
   m_words.push_back( quadCurrents0Name  ) ;
   m_words.push_back( quadCurrents0Value ) ; // quad current 0

   const UInt32 quadCurrents1Name ( RawEventData::string2Name( 
      RawRunControl::k_quadCurrentsName + "1" ) ) ;
   const UInt32 quadCurrents1Value ( 
      RawRunControl::k_quadCurrentsFactor*0. ) ;
   m_words.push_back( quadCurrents1Name  ) ;
   m_words.push_back( quadCurrents1Value ) ; // quad current 1

   const UInt32 quadCurrents2Name ( RawEventData::string2Name( 
      RawRunControl::k_quadCurrentsName + "2" ) ) ;
   const UInt32 quadCurrents2Value ( 
      RawRunControl::k_quadCurrentsFactor*0. ) ;
   m_words.push_back( quadCurrents2Name  ) ;
   m_words.push_back( quadCurrents2Value ) ; // quad current 2

   const UInt32 quadCurrents3Name ( RawEventData::string2Name( 
      RawRunControl::k_quadCurrentsName + "3" ) ) ;
   const UInt32 quadCurrents3Value ( 
      RawRunControl::k_quadCurrentsFactor*0. ) ;
   m_words.push_back( quadCurrents3Name  ) ;
   m_words.push_back( quadCurrents3Value ) ; // quad current 3

   const UInt32 quadCurrents4Name ( RawEventData::string2Name( 
      RawRunControl::k_quadCurrentsName + "4" ) ) ;
   const UInt32 quadCurrents4Value ( 
      RawRunControl::k_quadCurrentsFactor*0. ) ;
   m_words.push_back( quadCurrents4Name  ) ;
   m_words.push_back( quadCurrents4Value ) ; // quad current 4

   const UInt32 quadCurrents5Name ( RawEventData::string2Name( 
      RawRunControl::k_quadCurrentsName + "5" ) ) ;
   const UInt32 quadCurrents5Value ( 
      RawRunControl::k_quadCurrentsFactor*0. ) ;
   m_words.push_back( quadCurrents5Name  ) ;
   m_words.push_back( quadCurrents5Value ) ; // quad current 5


   m_RawRunControl = new RawRunControl( m_words.begin(), m_words.size() );

   return m_RawRunControl ;
}

//
// const member functions
//

//
// static member functions
//


