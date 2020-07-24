// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawRichHitsProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawRichHitsProxy.cc,v 1.10 2002/06/21 20:19:23 cdj Exp $
//
// Revision history
//
// $Log: MCRawRichHitsProxy.cc,v $
// Revision 1.10  2002/06/21 20:19:23  cdj
// now extract RichMCDaqID constant from the correct stream
//
// Revision 1.9  2002/06/18 16:41:20  ajm36
// add code for daq id mismapping
//
// Revision 1.8  2001/11/29 23:13:48  ts
// add parameters to control noise merging in Rich
//
// Revision 1.7  2001/11/06 21:39:08  ts
// Switch to use of RandomGenerator in Rich code
//
// Revision 1.6  2001/04/30 17:05:23  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.5  2000/07/17 20:26:41  ts
// add background simulation in RICH
//
// Revision 1.4  1999/10/24 20:37:23  cdj
// removed inappropriate use of typename
//
// Revision 1.3  1999/07/08 06:17:29  ts
// first actual implementation of Rich digitization
//
// Revision 1.2  1999/06/04 21:38:53  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:55  bkh
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
#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "Experiment/fortran_types.h"
#include "ToolBox/TBFortranArrays.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAConstants.h"
#include "FrameAccess/FANonSeqConstants.h"

#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#include "MCRawData/MCRawRichHitsProxy.h"

#include "MCResponse/MCRichResponse.h" 

#include "RawData/RawHits.h" 
#include "RichGeom/RichNum.h"
#include "RichGeom/RichNum_const.h"

#include "C3Rich/RichStream.h"
#include "RichCalibratedHits/RichGainCurve.h"
#include "RichCalibratedHits/RichPedestal.h"

#include "RandomModule/RandomGenerator.h"
#include "DBRICHMCDaqIdMap.hh"

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

static const char* const kReport = "MCRawData.MCRawRichHitsProxy" ;
static const char* const kFacilityString = kReport ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawRichHitsProxy::MCRawRichHitsProxy( const Parameter<DABoolean>& m_makeMCRawRichHits,
				        const Parameter<DABoolean> & useFakeMerge ,
				        const Parameter<float> & useNoiseScaleFactor 
) :
   m_RawRichHits ( 0 ) ,
   m_words       ( *new STL_VECTOR( UInt32 ) ),
   m_RICHDBPedestals(),
   m_RICHDBGains(),
   m_averageDBGain(0)
{
   iMakeMCRawRichHits = m_makeMCRawRichHits.value();
   m_useFakeMerge   = useFakeMerge.value();
   m_NoiseScaleFactor = useNoiseScaleFactor.value();

   report( DEBUG, kReport ) << "iMakeMCRawRichHits: " << iMakeMCRawRichHits << endl;

   m_words.reserve( 10000 ) ; // allocate reasonable length just once!

   if (iMakeMCRawRichHits != 0) 
   {
     bind( &MCRawRichHitsProxy::updatePedestals, RichStream::kRichPedestals );
     bind( &MCRawRichHitsProxy::updateGains    , RichStream::kRichGains );
   }
}

// MCRawRichHitsProxy::MCRawRichHitsProxy( const MCRawRichHitsProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawRichHitsProxy::~MCRawRichHitsProxy()
{
   delete m_RawRichHits ;
   delete &m_words      ;
}

//
// assignment operators
//
// const MCRawRichHitsProxy& MCRawRichHitsProxy::operator=( const MCRawRichHitsProxy& iproxy )
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

void MCRawRichHitsProxy::updatePedestals( const Record& iRecord )
{  
//  report(NOTICE,kFacilityString ) << " ++++ updatePedestals called ++++ " << endl; 

   extract( iRecord, m_RICHDBPedestals ); 
   if( !m_RICHDBPedestals.valid() ){
       report( WARNING, kFacilityString ) 
	 << " Pedestals not found by extract " << endl;
       } 
   else if( m_RICHDBPedestals.size() < RichNum::MAX_PADS_TOTAL ) {
       report( WARNING, kFacilityString ) 
	 << " Pedestals too short expect problems " << endl;
       }; 
        
   RICHDBPedestals::const_iterator itEnd = m_RICHDBPedestals.end();
   for( RICHDBPedestals::const_iterator itConstant = m_RICHDBPedestals.begin();
       itConstant != itEnd;
	++itConstant )
   { RICHDBPedestals::const_reference DBPed = (*itConstant);
      if( DBPed.get_RICHPadID() < 10 )
      report( DEBUG, kFacilityString )
	 << " Id " << DBPed.get_RICHPadID() 
         << " Pedestal " << DBPed.get_PedestalX16()/16.0
         << " Total Noise " << int(DBPed.get_NoiseTotalX8())/8.0
         << " Incoherent Noise " << int(DBPed.get_NoiseIncoherentX8())/8.0 << endl;
   };

}


void MCRawRichHitsProxy::updateGains( const Record& iRecord )
{  
//  report(NOTICE,kFacilityString ) << " ++++ updateGains called ++++ " << endl; 

   extract( iRecord, m_RICHDBGains ); 
   if( !m_RICHDBGains.valid() ){
       report( WARNING, kFacilityString ) 
	 << " Gains not found by extract " << endl;
       } 
   else if( m_RICHDBGains.size() < RichNum::MAX_PADS_TOTAL ) {
       report( WARNING, kFacilityString ) 
	 << " Gains too short expect problems " << endl;
       }; 
        
   int n=0;
   const int ninit=11;  // initialize with that many
   const double spread=0.9;  // relative spread of gains accepted in average
   double xsum=0; double xfirst[ninit+1];

   RICHDBGains::const_iterator itEnd = m_RICHDBGains.end();
   for( RICHDBGains::const_iterator itConstant = m_RICHDBGains.begin();
       itConstant != itEnd;
	++itConstant )
   { 

      RICHDBGains::const_reference DBGain = (*itConstant);

      double gain = double(DBGain.get_GainX256()/256.0);
      if( gain > 0 ){
	 if( n < ninit ){ 


            int i;
	    for( i=1; i<=n; ++i ){ if( gain < xfirst[i] ) {break;} };
            for( int j=n; j>=i; --j ){ xfirst[j+1]=xfirst[j]; };
            xfirst[i]=gain;
            ++n; 
            if( ninit==n ){ xsum=xfirst[ ninit/2 + 1 ]; } }
         else {
            double ave=xsum/(n-ninit+1);
   	    if( abs( ave - gain ) < spread*ave ){ xsum=xsum+gain; ++n; } }
      };

      if( DBGain.get_RICHPadID() < 10 )
      report( DEBUG, kFacilityString )
	 << " Id " << DBGain.get_RICHPadID() 
         << " Gain " << DBGain.get_GainX256()/256.0
         << " Saturation " << DBGain.get_SaturationX8()/8.0
         << " Pedestal " << DBGain.get_PedestalX16()/16.0
         << " Offset " << DBGain.get_OffsetX256()/256.0 << endl;

   };

   if( n > ninit ){ m_averageDBGain= xsum/(n-ninit+1); } else { m_averageDBGain=1.0; };

   report(INFO,kFacilityString ) << " average gain " <<  m_averageDBGain << endl; 

}


void
MCRawRichHitsProxy::invalidateCache()
{
   delete m_RawRichHits ;
   m_RawRichHits = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}


extern "C" void rich_add_pulse_(const FInteger& , const FReal& , const FReal& , 
                           const FInteger& , FReal* );

extern "C" void rich_add_background_s_(const FInteger& , const FInteger& , 
                                                FReal* , const FReal& );

extern "C" void rich_gauss_(FReal& , FReal& ); 


const MCRawRichHitsProxy::value_type*
MCRawRichHitsProxy::faultHandler( const Record& iRecord,
				  const DataKey& iKey )
{

   assert( 0 == m_RawRichHits ) ;
   assert( m_words.empty()  ) ; // always start out empty

   // check if MCRawRichHits are wanted at all; otherwise leave m_RawRichHits empty 
 
   if (iMakeMCRawRichHits != 0) 
   {

   FATable< MCRichResponse > responses ; 
   extract( iRecord, responses );

   if(iRecord.frame().record(RichStream::kMCRichMap).syncValue() != m_channelMapSync)
   {
      typedef FANonSeqConstants<DBRICHMCDaqIdMap> MapConstants;
      MapConstants channelMap;
      extract( iRecord.frame().record(RichStream::kMCRichMap), channelMap);

      MapConstants::const_iterator end = channelMap.end();
      MapConstants::const_iterator ch = channelMap.begin();
      for( ; ch != end; ++ch)
      {
         m_reverseMap[ch->get_LogicalId()] = ch->get_DaqId();
      }
      m_reverseMapEnd = m_reverseMap.end();
      m_channelMapSync = iRecord.frame().record(RichStream::kMCRichMap).syncValue();
   }

   if( !responses.valid() ) 
   {
      report( WARNING, kReport ) << "No Rich Responses found" << endl;
      return 0 ;
   }

   // loop over responses, accumulate energies, 
   // add noise, digitize, and sparsify in local variables
   // avoid lots of new's if possible using static vectors
   // with reasonable .reserve( size ) allocations.

   // Digitize in each chamber module separately to avoid dealing with
   // huge pad arrays

     RandomGenerator& ran ( RandomGenerator::instance() );

     for( FInteger is=1; is<=RichNum::MAX_SECTORS; ++is ){
        for ( FInteger im=1; im<=RichNum::MAX_MODULES_IN_SECTOR; ++im ){
        
           TBFortran2DArray<FReal, RichNum_MAX_PADS_X, RichNum_MAX_PADS_Y > ph;

	   // initialize ph
           FReal* pPh = &ph(1,1);            
           for( int i=0; i<RichNum::MAX_PADS_IN_MODULE; ++i){
	      *(pPh++)=0; };

           // process hits for this module -> convert to pulses
           FATable< MCRichResponse>::const_iterator itEnd=responses.end();
           for( FATable< MCRichResponse>::const_iterator it=responses.begin();
	      it!=itEnd; ++it){
             int padID= (*it).cellId();
             if( (RichNum::sector(padID) == is) && ( RichNum::module(padID) == im ) ){
                FInteger ichflg;
                if( MCRichResponse::k_chamber_gas == (*it).originMediumIndex() ) { ichflg=1; } else { ichflg=0; };
                rich_add_pulse_( padID, (*it).x(), (*it).y(), ichflg,
                                 ph.cArray() );
             }
	   };
  
           if(m_useFakeMerge){ 
           // add background ?
                rich_add_background_s_( is, im, ph.cArray(), m_NoiseScaleFactor);                
	   }

           // gain corrections
           {  // extra brace for SunOS CC compiler
           for( int iy=1; iy<=RichNum::MAX_PADS_Y; ++iy ){
              for( int ix=1; ix<=RichNum::MAX_PADS_X; ++ix ){

                 RichPulseHeightType adc =  ph(ix,iy);
                 if( adc>0 ){

                     const int riadd = RichNum::padID(is,im,iy,ix);
                     RichGainCurve gainCurve( m_RICHDBGains[riadd], m_averageDBGain );
                     ph(ix,iy) = gainCurve.pulseHeightInverseFullCorrection(adc);

		 }
	      }
	   }
	   }  

           // add pedestal and electronic noise 

           {  // extra brace for SunOS CC compiler
           for( int iy=1; iy<=RichNum::MAX_PADS_Y; ++iy ){
              for( int ix=1; ix<=RichNum::MAX_PADS_X; ++ix ){

                     const int riadd = RichNum::padID(is,im,iy,ix);
                     RichPedestal pedestal( m_RICHDBPedestals[riadd] );

                     // for now just use incoherent noise; when electronic-logical map is done
                     // will need to rewrite to generate coherent and incoherent noise separately

                     // FReal r1,r2;
                     // rich_gauss_(r1,r2);
                     // ph(ix,iy) = ph(ix,iy) + pedestal.pedestal() + pedestal.incoherentNoise()*r1;
                     ph(ix,iy) = ph(ix,iy) + pedestal.pedestal() + pedestal.incoherentNoise()*ran.gauss();

	      }
	   }
	   }

           // sparfify 

           //  this is also temporary; will need to replace by real sparsifier

           {  // extra brace for SunOS CC compiler
           for( int iy=1; iy<=RichNum::MAX_PADS_Y; ++iy ){
              for( int ix=1; ix<=RichNum::MAX_PADS_X; ++ix ){

                     const int riadd = RichNum::padID(is,im,iy,ix);
                     RichPedestal pedestal( m_RICHDBPedestals[riadd] );

                     ph(ix,iy) = ((ph(ix,iy)-pedestal.pedestal()) > (5.0*pedestal.incoherentNoise())) ? ph(ix,iy) : 0.0; 

	      }
	   }
	   }

           // loop over ph-array and store non-zero ph 
           {  // extra brace for SunOS CC compiler
           for( int iy=1; iy<=RichNum::MAX_PADS_Y; ++iy ){
              for( int ix=1; ix<=RichNum::MAX_PADS_X; ++ix ){

                 int adc =  ph(ix,iy);
                 if( adc>0 ){

                     const int riadd = RichNum::padID(is,im,iy,ix);

                     const int adcmax = 4095; // =2**12-1  (12 bit ADC)
                     adc = (adc<=adcmax) ? adc : adcmax;  

                     RichDatum::DaqIdType   daqId   ( riadd ) ;
	             const RichDatum::ControlType control ( 0 ) ;
     	             const RichDatum::DigiType    digi    ( adc ) ;

                     STL_MAP(int, int)::const_iterator find = m_reverseMap.find(daqId);
                     if(find != m_reverseMapEnd)
                     {
                        daqId = (*find).second;
                     }
  	             m_words.push_back(RawHits< RichDatum >::packRawWord( daqId, control, digi ) ) ;

		 }
	      }
	   }
	   }
	}
     }

   // continue here in case no MCRawRichHits were wanted (above)
   }

   m_RawRichHits = new RawRichHits( m_words.begin(), m_words.size() );

   return m_RawRichHits ;

}

//
// const member functions
//

//
// static member functions
//

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< RawRichHits >;

PROXY_BIND_METHOD( MCRawRichHitsProxy )
//-----------------------------------------------

