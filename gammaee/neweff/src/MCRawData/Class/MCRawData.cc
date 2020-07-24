// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawData
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:24:00 EST 1999
// $Id: MCRawData.cc,v 1.16 2002/09/27 20:23:09 bkh Exp $
//
// Revision history
//
// $Log: MCRawData.cc,v $
// Revision 1.16  2002/09/27 20:23:09  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.15  2002/06/13 19:53:35  bkh
// Implement use of ccmcpeeldaqmap in the calorimeter processing
// Implement parameter to turn off trigger simulation as with other detectors
//
// Revision 1.14  2002/02/04 22:37:53  bkh
// Undo previous change
//
// Revision 1.13  2002/02/04 22:11:15  bkh
// Do not register RawLevel3TriggerProxy -- it is a dummy
//
// Revision 1.12  2001/12/20 17:11:19  bkh
// Install fake merge flag for Cathodes as with other detectors
// Use fake merge flag for Cathodes
// Fix SV proxy fcn to avoid compiler warning about
//      argument overriding member data
//
// Revision 1.11  2001/12/18 22:33:09  bkh
// Institute CC "fake merge" flag like other detectors
// Force trigger to get CalibratedDRHits not raw data
//
// Revision 1.10  2001/11/29 23:13:47  ts
// add parameters to control noise merging in Rich
//
// Revision 1.9  2001/11/20 04:57:10  victor
// introduced two parameters for SV
//
// Revision 1.8  2001/04/30 17:05:23  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.7  2001/02/26 00:49:19  cdj
// Now delivers data on StartRun
//
// Revision 1.6  1999/11/03 00:00:23  lyon
// Removed TQT proxy
//
// Revision 1.5  1999/10/26 22:15:25  lyon
// Added MCRawDRTQTProxy
//
// Revision 1.4  1999/06/10 20:22:26  bkh
// Better stab at CC simulation
//
// Revision 1.3  1999/04/20 01:43:06  bkh
// update for new raw data objects
//
// Revision 1.2  1999/02/25 22:02:51  bkh
// fix name conflicts
//
// Revision 1.1.1.1  1999/02/25 20:29:11  bkh
// imported MCRawData sources
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
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
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCRawData/MCRawData.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"
#include "DataHandler/ProxyFactoryArgument.h"

#include "MCRawData/MCRawCCHitsProxy.h"
#include "MCRawData/MCRawCathodesProxy.h"
#include "MCRawData/MCRawDRHitsProxy.h"
#include "MCRawData/MCRawZDHitsProxy.h"
#include "MCRawData/MCRawEventDataProxy.h"
#include "MCRawData/MCRawHeaderProxy.h"
#include "MCRawData/MCRawLevel3TriggerProxy.h"
#include "MCRawData/MCRawMUHitsProxy.h"
#include "MCRawData/MCRawPreludeProxy.h"
#include "MCRawData/MCRawRichHitsProxy.h"
#include "MCRawData/MCRawSVHitsProxy.h"
#include "MCRawData/MCRawTriggerProxy.h"
#include "MCRawData/MCRawWaferProxy.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
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
static const char* const kReport = "MCRawData.MCRawData" ;


//
// static data member definitions
//


//
// constructors and destructor
//
MCRawData::MCRawData( void )               // anal1
   : Producer                 ( "MCRawData" ),
     m_getMCRawSVHits         ( "MCRawSVHits"            , this, true ),    
     m_getMCRawDRHits         ( "MCRawDRHits"            , this, true ),
     m_getMCRawZDHits         ( "MCRawZDHits"            , this, true ),
     m_getMCRawCathodesHits   ( "MCRawCathodesHits"      , this, true ),
     m_getMCRawRichHits       ( "MCRawRichHits"          , this, true ),
     m_getMCRawCCHits         ( "MCRawCCHits"            , this, true ),
     m_getMCRawMUHits         ( "MCRawMUHits"            , this, true ),
     m_getMCRawTrigger        ( "MCRawTrigger"           , this, true ),
     m_useCCFakeMerge         ( "useCCFakeMerge"         , this, true ),
     m_useCathodesFakeMerge   ( "useCathodesFakeMerge"   , this, true ),
     m_useSVFakeMerge         ( "useSVFakeMerge"         , this, true ),
     m_useSVCMNoiseValue      ( "useSVCMNoiseValue"      , this, 0.8  ),
     m_useRichFakeMerge       ( "useRichFakeMerge"       , this, true ),
     m_useRichNoiseScaleFactor( "useRichNoiseScaleFactor", this, 1.0  )
{
   report( DEBUG, kReport ) << "here in ctor()" << endl;

   // add help texts for Suez run-time parameters
   m_getMCRawSVHits.setHelpString(
      " Boolean parm stating whether MCRawSVHits are wanted; default: true \n "); 
   m_getMCRawDRHits.setHelpString(
      " Boolean parm stating whether MCRawDRHits are wanted; default: true \n "); 
   m_getMCRawZDHits.setHelpString(
      " Boolean parm stating whether MCRawZDHits are wanted; default: true \n "); 
   m_getMCRawCathodesHits.setHelpString(
      " Boolean parm stating whether MCRawCathodesHits are wanted;default: true \n "); 
   m_getMCRawRichHits.setHelpString(
      " Boolean parm stating whether MCRawRichHits are wanted; default: true \n "); 
   m_getMCRawCCHits.setHelpString(
      " Boolean parm stating whether MCRawCCHits are wanted; default: true \n "); 
   m_getMCRawMUHits.setHelpString(
      " Boolean parm stating whether MCRawMUHits are wanted; default: true \n ");
   m_getMCRawTrigger.setHelpString(
      " Boolean parm stating whether MCRawTrigger is wanted; default: true \n ");
   m_useCCFakeMerge.setHelpString(
      " A boolean parameter asking whether Fake Merge for CC is wanted (default: true) \n ");
   m_useCathodesFakeMerge.setHelpString(
      " A boolean parameter asking whether Fake Merge for Cathodes is wanted (default: true) \n ");
   m_useSVFakeMerge.setHelpString(
      " A boolean parameter asking whether Fake Merge for SV is wanted (default: true) \n ");
   m_useSVCMNoiseValue.setHelpString(
      " A float parameter setting the value of Common Mode Noise for SV (default: 0.8) \n");
   m_useRichFakeMerge.setHelpString(
      " A boolean parameter asking whether Fake Merge for Rich is wanted (default: true) \n ");
   m_useRichNoiseScaleFactor.setHelpString(
      " A float parameter setting the scale factor for Rich noise (if useRichFakeMerege is true) (default: 1.0) \n");
   
   // ----- register proxy factories ------------------
   // (Please see the "ProxyExample" library for examples!)
   //
   // Two steps: 1) use "registerProxyFactory" to register
   //            2) instantiate ProxyFactory/Function
   //               (if you're using the standard templated factories;
   //                you may of course roll your own!)

   // Proxy Registration Step 1:
   // either
   //    register default-ctor proxy

   registerProxyFactory( Stream::kEvent, 
                         new ProxyFactoryFunction
                         < MCRawData , MCRawCCHitsProxy > 
                         ( *this, &MCRawData::makeMCRawCCHitsProxy ),
                         UsageTag() );
   registerProxyFactory( Stream::kEvent, 
                         new ProxyFactoryFunction
                         < MCRawData , MCRawCathodesProxy > 
                         ( *this, &MCRawData::makeMCRawCathodesProxy ),
                         UsageTag() );
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactoryArgument< MCRawDRHitsProxy,
                           const Parameter<DABoolean>& >(m_getMCRawDRHits), 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactoryArgument< MCRawZDHitsProxy,
                           const Parameter<DABoolean>& >(m_getMCRawZDHits), 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< MCRawEventDataProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kBeginRun, 
			 new ProxyFactory< MCRawEventDataProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kStartRun, 
			 new ProxyFactory< MCRawEventDataProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEndRun, 
			 new ProxyFactory< MCRawEventDataProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< MCRawHeaderProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kBeginRun, 
			 new ProxyFactory< MCRawHeaderProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kStartRun, 
			 new ProxyFactory< MCRawHeaderProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEndRun, 
			 new ProxyFactory< MCRawHeaderProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< MCRawLevel3TriggerProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactoryArgument< MCRawMUHitsProxy,
                           const Parameter<DABoolean>& >(m_getMCRawMUHits), 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< MCRawPreludeProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kBeginRun, 
			 new ProxyFactory< MCRawPreludeProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kStartRun, 
			 new ProxyFactory< MCRawPreludeProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEndRun, 
			 new ProxyFactory< MCRawPreludeProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEvent, 
                         new ProxyFactoryFunction
                         < MCRawData , MCRawRichHitsProxy > 
                         ( *this, &MCRawData::makeMCRawRichHitsProxy ),
                         UsageTag() );
   registerProxyFactory( Stream::kEvent, 
                         new ProxyFactoryFunction
                         < MCRawData , MCRawSVHitsProxy > 
                         ( *this, &MCRawData::makeMCRawSVHitsProxy ),
                         UsageTag() );
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactoryArgument< MCRawTriggerProxy,
			 const Parameter<DABoolean>& >(m_getMCRawTrigger),
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< MCRawWaferProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
}

ProxyBase*
MCRawData::makeMCRawCCHitsProxy()
{
   return new MCRawCCHitsProxy( m_getMCRawCCHits,
				m_useCCFakeMerge );
}

ProxyBase*
MCRawData::makeMCRawCathodesProxy()
{
   return new MCRawCathodesProxy( m_getMCRawCathodesHits,  
				  m_useCathodesFakeMerge );
}

ProxyBase*
MCRawData::makeMCRawSVHitsProxy()
{
   return new MCRawSVHitsProxy( m_getMCRawSVHits, 
				m_useSVFakeMerge,
				m_useSVCMNoiseValue);
}

ProxyBase*
MCRawData::makeMCRawRichHitsProxy()
{
   return new MCRawRichHitsProxy(m_getMCRawRichHits,
				 m_useRichFakeMerge,
				 m_useRichNoiseScaleFactor);
}



// Proxy Registration Step 2:
// template instantiations for proxy factories

#include "DataHandler/Template/ProxyFactory.cc"
template class ProxyFactoryArgument< MCRawDRHitsProxy, const Parameter<DABoolean>&  >;
template class ProxyFactoryArgument< MCRawZDHitsProxy, const Parameter<DABoolean>&  >;
template class ProxyFactory        < MCRawEventDataProxy     >;
template class ProxyFactory        < MCRawHeaderProxy        >;
template class ProxyFactory        < MCRawLevel3TriggerProxy >;
template class ProxyFactoryArgument< MCRawMUHitsProxy, const Parameter<DABoolean>&  >;
template class ProxyFactory        < MCRawPreludeProxy       >;
template class ProxyFactoryArgument< MCRawTriggerProxy, const Parameter<DABoolean>& >;
template class ProxyFactory        < MCRawWaferProxy         >;

#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction<MCRawData, MCRawCCHitsProxy>;
template class ProxyFactoryFunction<MCRawData, MCRawCathodesProxy>;
template class ProxyFactoryFunction<MCRawData, MCRawSVHitsProxy>;
template class ProxyFactoryFunction<MCRawData, MCRawRichHitsProxy>;


// MCRawData::MCRawData( const MCRawData& iMCRawData )
// {
//    *this = iMCRawData;
// }

MCRawData::~MCRawData()                    // anal5
{
   report( DEBUG, kReport ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const MCRawData& MCRawData::operator=( const MCRawData& iMCRawData )
// {
//   if( this != &iMCRawData ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iMCRawData );
//   }
//
//   return *this;
// }

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
MCRawData::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kReport ) << "here in init()" << endl;
   report( INFO, kReport ) << "Parameter settings:" << endl;
   report( INFO, kReport ) << "==================" << endl;
   report( INFO, kReport ) << "MCRawSVHits =" << m_getMCRawSVHits.value() << endl;
   report( INFO, kReport ) << "MCRawDRHits =" << m_getMCRawDRHits.value() << endl;
   report( INFO, kReport ) << "MCRawZDHits =" << m_getMCRawZDHits.value() << endl;
   report( INFO, kReport ) << "MCRawCathodesHits =" << m_getMCRawCathodesHits.value() << endl;
   report( INFO, kReport ) << "MCRawRichHits =" << m_getMCRawRichHits.value() << endl;
   report( INFO, kReport ) << "MCRawCCHits =" << m_getMCRawCCHits.value() << endl;
   report( INFO, kReport ) << "MCRawMUHits =" << m_getMCRawMUHits.value() << endl;
   report( INFO, kReport ) << "useCCFakeMerge = "<<m_useCCFakeMerge.value()<<endl;
   report( INFO, kReport ) << "useCathodesFakeMerge = "<<m_useCathodesFakeMerge.value()<<endl;
   report( INFO, kReport ) << "useSVFakeMerge = "<<m_useSVFakeMerge.value()<<endl;
   report( INFO, kReport ) << "useSVCMNoiseValue = "<<m_useSVCMNoiseValue.value()<<endl; 
   report( INFO, kReport ) << "useRichFakeMerge = "<<m_useRichFakeMerge.value()<<endl;
   report( INFO, kReport ) << "useRichNoiseScaleFactor = "<<m_useRichNoiseScaleFactor.value()<<endl; 
   report( INFO, kReport ) << "==================" << endl;


   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
MCRawData::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kReport ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
MCRawData::hist_book( TBHistoManager& )
{
   report( DEBUG, kReport ) << "here in hist_book()" << endl;

   // book your histograms here

}

//
// const member functions
//

//
// static member functions
//
