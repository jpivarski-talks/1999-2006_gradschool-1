// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawSVHitsProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawSVHitsProxy.cc,v 1.21 2003/04/11 20:38:06 bkh Exp $
//
// Revision history
//
// $Log: MCRawSVHitsProxy.cc,v $
// Revision 1.21  2003/04/11 20:38:06  bkh
// Get DetectorConfiguration from basegeometry now not beginrun
//
// Revision 1.20  2003/03/19 18:33:09  bkh
// Change exception thrown to be a no data exception
//
// Revision 1.19  2003/03/18 23:09:20  bkh
// Explicitly disallow SV when running ZD and vice versa
//
// Revision 1.18  2003/01/29 19:31:07  cleo3
// changes needed to compile using g++
//
// Revision 1.17  2002/09/27 20:23:12  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.16  2002/09/13 20:52:16  bkh
// Stop not sparsifying every 50th event
// Put in safeguards against writing bad data
//
// Revision 1.15  2001/12/20 17:11:20  bkh
// Install fake merge flag for Cathodes as with other detectors
// Use fake merge flag for Cathodes
// Fix SV proxy fcn to avoid compiler warning about
//      argument overriding member data
//
// Revision 1.14  2001/12/04 04:41:07  victor
// adjusted values of constants
//
// Revision 1.13  2001/11/21 00:11:07  victor
// added a symbolic constant
//
// Revision 1.12  2001/11/20 05:05:56  victor
// switched to a bindable proxy, introduced online (VME CPU) sparsifier, revised back-end chip level sparsification/decisions, simulated wire-bonding bugs (for jammed channels), attempted to speed up the code (many thanks to ajm36), other small changes
//
// Revision 1.11  2001/04/30 17:05:24  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.10  2000/12/01 19:19:43  cja23
// jammed channels, intrinsic and common mode noise, and chip level decisions (nearest neighbor/read all/threshold) all added
//
// Revision 1.9  2000/08/07 13:40:38  ajm36
// convert energy to charge for si hits
//
// Revision 1.8  2000/07/25 20:22:22  pg
// Minor clean up of Si code
//
// Revision 1.7  2000/05/09 13:28:19  pg
// Added realistic gain for Si, extract DR active element from DRAlignment
//
// Revision 1.6  1999/12/17 15:57:22  cdj
// removed inappropriate use of typename, again
//
// Revision 1.5  1999/11/19 20:28:21  pg
// Removed excessive printout from MCRawSVHitsProxy
//
// Revision 1.4  1999/11/16 20:55:43  pg
// Added Si simulation
//
// Revision 1.3  1999/10/24 20:37:24  cdj
// removed inappropriate use of typename
//
// Revision 1.2  1999/06/04 21:38:54  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:56  bkh
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
#include <memory>  //for auto_ptr



#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */




// user include files
#include "Experiment/report.h"

#include "DataHandler/Frame.h"
#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FAConstants.h"
#include "FrameAccess/FANonSeqConstants.h"

#include "MCResponse/MCSVResponse.h" 
#include "C3sv/SiStream.h"
#include "SiGeom/SiGeomDescription.h"
#include "SiHits/SVChannelStatus.h"
#include "ASiStorePro/ASiStore.h"
#include "ASiStorePro/ASiStoreConstants.h"
#include "RawData/RawHits.h" 
#include "DBSVChannel.hh"
#include "DBSVChipSet.hh"
#include "MCRawData/MCRawSVHitsProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD
#include "DBSVChannelOnline.hh" 
#include "DetectorConfiguration/DetectorConfiguration.h"
#include "DAException/DANoDataException.h"

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "MCRawData.MCRawSVHitsProxy" ;

#define HELLO_WORLD_VERSION  112310 //111532 //a version that suppresses jammed channels only
#define VERSION_1            114334 //a version that involves cmn computations and nn considerations 
#define   TOTAL_NUMBER_OF_CHIPS  976  

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCRawSVHitsProxy.cc,v 1.21 2003/04/11 20:38:06 bkh Exp $";
static const char* const kTagString = "$Name: v05_02_05 $";
static const char* const kReport = "MCRawData.MCRawSVHitsProxy" ;

static const UInt32 kMagicNumber ( 55555555 ) ;
//
// static data member definitions
//

float    CopySiSparsifierAccessories::SVSparNSigmaUp            = 0; 
float    CopySiSparsifierAccessories::SVSparNSigmaDown          = 0; 
float    CopySiSparsifierAccessories::SVSparThresholdWindowUp   = 0; 
float    CopySiSparsifierAccessories::SVSparThresholdWindowDown = 0; 
float    CopySiSparsifierAccessories::SVSparNeighborWindowUp    = 0;
float    CopySiSparsifierAccessories::SVSparNeighborWindowDown  = 0; 
float    CopySiSparsifierAccessories::SVSparNoisyChannel        = 0; 
float    CopySiSparsifierAccessories::SVSparLatched             = 0; 
UInt32   CopySiSparsifierAccessories::SVSparNKeep               = 0; 
float    CopySiSparsifierAccessories::CMN_ADCDown               = 0; 
float    CopySiSparsifierAccessories::CMN_ADCUp                 = 0; 
float    CopySiSparsifierAccessories::CMN_NoiseDown             = 0; 
float    CopySiSparsifierAccessories::CMN_NoiseUp               = 0; 
float    CopySiSparsifierAccessories::CMN_NSigmaChip            = 0; 
float    CopySiSparsifierAccessories::CMN_NSigmaSide            = 0; 
float    CopySiSparsifierAccessories::CMN_DeltaSideCut          = 0; 

UInt32   CopySiSparsifierAccessories::constantSize              = 0;
int      CopySiSparsifierAccessories::eventCount                = 0;


const UInt32 MCRawSVHitsProxy::maxNumberOfWords = 124928;
const UInt32 MCRawSVHitsProxy::crateOffset      = 1952;  

//
// constructors and destructor
//
MCRawSVHitsProxy::MCRawSVHitsProxy(Parameter< DABoolean > & getMCRawSVHits,
				   Parameter< DABoolean > & useFakeMerge ,
				   Parameter< float > & CMNoiseValue )
   : m_RawSVHits( 0 ) ,
     m_words    ( ) ,
     unique     ( *new StripMap ),
     kSiBandGap ( SiGeomDescription::kSiBandGap ),
     kElectronsPerADC ( SiGeomDescription::kElectronsPerADC ),
     ran ( RandomGenerator::instance() ) ,
     m_makeMCRawSVHits ( getMCRawSVHits ) ,
     m_useFakeMerge   ( useFakeMerge   ) ,
     m_CMNScaleFactor ( CMNoiseValue   )
{
   report( INFO, kReport ) 
      << "In the constructor of  MCRawSVHitsProxy..."<<endl;

   //allocate reasonable length just once!
   m_words.reserve( maxNumberOfWords ) ;

   //The data words are read out and sparsified by two crates in the detector.
   //In order to use the online sparsification code here - we split MC data  
   //into two big chunks - one for each crate according to channel numbers.
   pCrate1 = new UInt32[maxNumberOfWords+crateOffset];
   pCrate2 = new UInt32[maxNumberOfWords+crateOffset];

   for(UInt32 ii (0); ii<maxNumberOfWords+crateOffset; ++ii )
   {
      pCrate1[ii]=kMagicNumber ;
      pCrate2[ii]=kMagicNumber ;
   }

   //the myAlgorithms is created and/or updated at SiStream::kSVCalibOnline stops
   myAlgorithm1 = NULL;
   myAlgorithm2 = NULL;

   //pointer to channel constant for the two silicon crates
   crate1Constants = NULL;
   crate2Constants = NULL;

   runNumber      = 0;   
   doesSparExist  = FALSE;

   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &MCRawSVHitsProxy::boundMethod, Stream::kBeginRun );
   //bind( &MCRawSVHitsProxy::updateSparAlgorithm, SiStream::kSVCalibOnline );
   bind( &MCRawSVHitsProxy::updateSparAlgorithm, Stream::kBeginRun );

   areAddressesFilled = FALSE;
   AddressesOfJammedChannels = new UInt32[2*NUMBERJAMMEDCHANNELSPERCRATE];


   backEndChipThreshold = new UInt8[TOTAL_NUMBER_OF_CHIPS];
   backEndChipMode = new UInt8[TOTAL_NUMBER_OF_CHIPS];

   m_chipSetSync = SyncValue::kBeginningOfTime;

   report( INFO, kReport ) << "MCRawSVHitsProxy is constructed ..."<<endl;
}

// MCRawSVHitsProxy::MCRawSVHitsProxy( const MCRawSVHitsProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawSVHitsProxy::~MCRawSVHitsProxy()
{
   delete m_RawSVHits ;
 
   if(pCrate1 != NULL)         delete [] pCrate1;
   if(pCrate2 != NULL)         delete [] pCrate2;
   if(myAlgorithm1 != NULL)    delete myAlgorithm1;
   if(myAlgorithm2 != NULL)    delete myAlgorithm2;
   if(crate1Constants != NULL) delete  crate1Constants;
   if(crate2Constants != NULL) delete  crate2Constants;
   if(AddressesOfJammedChannels != NULL) delete [] AddressesOfJammedChannels;  
   if(backEndChipThreshold != NULL) delete [] backEndChipThreshold;
   if(backEndChipMode      != NULL) delete [] backEndChipMode;

   report( INFO, kReport ) << "In the destructor of  MCRawSVHitsProxy..."<<endl;
}

//
// assignment operators
//
// const MCRawSVHitsProxy& MCRawSVHitsProxy::operator=( const MCRawSVHitsProxy& iproxy )
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
MCRawSVHitsProxy::invalidateCache()
{
   delete m_RawSVHits ;
   m_RawSVHits = NULL ;

   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
   if( !unique.empty() )
   {
      unique.erase( unique.begin(), unique.end() );
   }
}

void
MCRawSVHitsProxy::addToMap( const UInt32 wAddress,
                            const float commonNoise )
{
   const DBSVChannel& myChannel = myChannelConsts[wAddress];
   float pedestal = myChannel.get_Pedestal();
   float noise = myChannel.get_Noise();
   int adc;
   if(wAddress <= NUM_SVX_CHANNELS_RPHI)
   {
      adc = pedestal + ran.gauss(0, noise) + commonNoise + 0.5;
   }
   else
   {
      adc = pedestal + ran.gauss(0, noise) - commonNoise + 0.5;
   }
   if(adc > SiGeomDescription::kADCRange) adc=SiGeomDescription::kADCRange;
   if(adc < 0) adc=0;
   unique.insert(StripMap::value_type(wAddress,adc));
}   

const MCRawSVHitsProxy::value_type*
MCRawSVHitsProxy::faultHandler( const Record& iRecord,
				const DataKey& iKey )
{
   FAItem<DetectorConfiguration>                              iConfig   ;
   extract( iRecord.frame().record( Stream::kBaseGeometry ) , iConfig ) ;
   if( iConfig->useZDnotSI() )
   {
      throw DANoDataException< RawSVHits >(iRecord.stream(),iKey) ;
   }

   assert( 0 == m_RawSVHits );
   assert( m_words.empty()  ); // always start out empty
   assert( unique.empty()  );


   for(UInt32 ii (0); ii<crateOffset; ++ii )
   {
      pCrate1[ii]=kMagicNumber ;
      pCrate2[ii]=kMagicNumber ;
   }
   
   // check if MCRawSVHits are wanted at all; otherwise leave m_RawSVHits empty  
   if( m_makeMCRawSVHits.value() ) 
   {
      FATable< MCSVResponse > responses ; 
      extract( iRecord, responses );
      
      extract( iRecord.frame().record( Stream::kSVCalibration ), myChannelConsts);
      
      if( !responses.valid() || !myChannelConsts.valid() ) 
      {
	 report( ERROR, kReport ) << "Not valid SV Responses, SVChannel or "
				  << "SVChannelOnline constants ..." << endl;
	 return 0 ;
      }
      
      const SyncValue& sync = iRecord.frame().record( SiStream::kSVOnline).syncValue();
      if(m_chipSetSync != sync) 
      {
	 m_chipSetSync = sync;
	 if( upDateChipConstants(iRecord) ) 
	 {
	    report( ERROR, kReport ) << "Could not update chip constants..."<<endl;
	    return 0;
	 }
      }

      FAItem< DBEventHeader > eventHeader ;
      extract( iRecord.frame().record( Stream::kEvent ), eventHeader ) ;
      runNumber = (*eventHeader).run();

      StripMap::iterator istr;


      // loop over responses and accumulate deposited energies for each strip
      for( FATable<MCSVResponse>::const_iterator ir(responses.begin());
	   ir != responses.end() ; ++ir)
      {	 
	 const MCSVResponse& resp = *ir;
	 int cellId ( resp.cellId() ) ;
	 float energy ( resp.charge() ) ;
	 StripMap::iterator iMap = unique.find(cellId);
	 if( iMap == unique.end())
	 {
	    // New entry
	    unique.insert(StripMap::value_type(cellId,energy));
	 }
	 else
	 {
	    // Increment existing entry
	    (*iMap).second += energy;
	 }      
      }
      
      float commonNoise =  m_CMNScaleFactor.value()*ran.gauss(0, 1.0);

      // convert all these entries from energies to ADCs with noise 
      for( istr = unique.begin(); istr != unique.end(); ++istr)
      {
	 UInt32 wAddress = (*istr).first;
	 float charge = (*istr).second/kSiBandGap;
	 
	 const DBSVChannel& iChannel = myChannelConsts[wAddress];
	 float pedestal =   iChannel.get_Pedestal();
	 float gain =  iChannel.get_Gain();
	 float noise = iChannel.get_Noise();
	 int adc;
	 if(wAddress <= NUM_SVX_CHANNELS_RPHI)
	 {  // r-phi strips
	    adc = charge/gain + pedestal + ran.gauss(0, noise) + commonNoise + 0.5;
	 }
	 else
	 {  // z strips, common noise is anti-correlated
	    adc = charge/gain + pedestal + ran.gauss(0, noise) - commonNoise + 0.5;
	 }
	 if(adc > SiGeomDescription::kADCRange) adc=SiGeomDescription::kADCRange;
	 if(adc < 0) adc=0;
	 (*istr).second = adc;
      }


      FAItem< ASiStore > converter;
      extract( iRecord.frame().record( Stream::kSVAlignment ), converter );


      //Fake Merge 
      if(m_useFakeMerge.value())
      {
	 for( UInt32 ichannel = 1; ichannel <= ASiStoreConstants::kChannelsTotal;
	      ichannel++ )
	 {
	    if(unique.find(ichannel) != unique.end()) continue;
	    const DBSVChannel& iChannel = myChannelConsts[ichannel];
	    float pedestal   = iChannel.get_Pedestal();
	    float noise      = iChannel.get_Noise();
	    int adc;
	    UInt16 stripChip = converter->chipForLAddress(ichannel);
	    UInt8 threshold  = backEndChipThreshold[stripChip - 1]; 
	    if(ichannel < NUM_SVX_CHANNELS_RPHI)
	    {
	       if( (threshold - pedestal - commonNoise) < (4 * noise) )
	       {
		  adc = pedestal + ran.gauss(0, noise) + commonNoise + 0.5;
		  if(adc > SiGeomDescription::kADCRange) adc=SiGeomDescription::kADCRange;
		  if(adc < 0) adc=0;
	       }
	       else
	       {
		  continue;
	       }
	    }
	    else
	    {
	       if( (threshold - pedestal + commonNoise) < (4 * noise) )
	       {
		  adc = pedestal + ran.gauss(0, noise) - commonNoise + 0.5;
		  if(adc > SiGeomDescription::kADCRange) adc=SiGeomDescription::kADCRange;
		  if(adc < 0) adc=0;
	       }
	       else 
	       {
		  continue;
	       }
	    }
	    unique.insert(StripMap::value_type(ichannel, adc));
	 }
      }


      enum stripLocation{ firstOnHybrid, lastOnHybrid, firstOnChip, lastOnChip, normal };
      enum readoutMode{ NN=1, RA=2, TH=3 };
      

      // add in the chip back-end level decision process, strip by strip
      StripMap::iterator firstEnd ( unique.end() ) ;


      istr = unique.begin(); 
      while( istr != unique.end() )
      {
	 StripMap::iterator istr_help;
	 istr_help = istr;
	 istr++;

	 UInt32 wAddress = (*istr_help).first;
	 SVChannelStatus status( myChannelConsts[wAddress].get_Status() );
	
	 if( status.disconnected() ) 
	 {
	    unique.erase(istr_help);  
	    continue; 
	 }
	 
	 UInt16 stripChip = converter->chipForLAddress(wAddress);
	 UInt8  stripMode = backEndChipMode[stripChip - 1];

	 if(stripMode == TH)       // threshold mode
	 {
	    UInt8 threshold = backEndChipThreshold[stripChip - 1]; 
	    if( (*istr_help).second >= threshold )
	    {
	       continue;
	    }
	    else 
	    {
	       unique.erase(istr_help); 
	       continue; 
	    }
	 }
	 else if(stripMode == RA)       // read-all mode
	 {
	    StripMap::iterator RAptr;
	    StripMap::iterator last = istr_help;
	    

	    // fill all channels on chip before this one
	    for( RAptr = istr_help;
		 (  ((*RAptr).first - 1) >= 1) &&
		    (converter->chipForLAddress((*RAptr).first - 1) == stripChip); --RAptr )
	    {
	       if(unique.find((*RAptr).first - 1) != unique.end()) continue;
	       addToMap( (*RAptr).first - 1,  commonNoise);
	    }
	    
	    // fill all channels on chip after this one
	    for( RAptr = istr_help;
		 (((*RAptr).first + 1) <= ASiStoreConstants::kChannelsTotal) &&
		    (converter->chipForLAddress((*RAptr).first + 1) == stripChip); )
	    {
	       if(unique.find((*RAptr).first + 1) != unique.end())
	       { 
		  last = ++RAptr; 
		  continue; 
	       }
	       addToMap((*RAptr).first + 1, commonNoise);
	       last = ++RAptr;
	    }   
	    istr = ++last;
	 }	 
	 else if(stripMode == NN)       // nearest neighbor mode
	 {
	    UInt8 threshold = backEndChipThreshold[stripChip - 1]; 
	    int stripLocale;
	    
	    if( !((wAddress - 1) % 512) )
	       stripLocale = firstOnHybrid;
	    else if( !(wAddress % 512))
	       stripLocale = lastOnHybrid;
	    else if(!((wAddress - 1) % 128))
	       stripLocale = firstOnChip;
	    else if(!(wAddress % 128))
	       stripLocale = lastOnChip;
	    else
	       stripLocale = normal;
	    
	    if( (*istr_help).second >= threshold )        // above threshold
	    {
	       if(stripLocale == firstOnHybrid)
	       {
		  if(unique.find(wAddress + 1) == unique.end())
		  {
		     addToMap(wAddress + 1, commonNoise);
		     continue;
		  }
		  else 
		  {
		     continue;
		  }
	       }
	       else if(stripLocale == lastOnHybrid)
	       {
		  if(unique.find(wAddress - 1) == unique.end())
		  {
		     addToMap(wAddress - 1, commonNoise);
		     continue;
		  }
		  else 
		  {
		     continue;
		  }	       
	       }
	       else if( (stripLocale == firstOnChip) || 
			(stripLocale == lastOnChip)  ||
			(stripLocale == normal) )
	       {
		  if( unique.find(wAddress - 1) == unique.end())
		  {
		     addToMap(wAddress - 1,  commonNoise);
		  }
		  if( unique.find(wAddress + 1) == unique.end())
		  {
		     addToMap(wAddress + 1, commonNoise);
		  }
		  continue;
	       }
	    }
	    else
	    {
	       if(stripLocale == firstOnHybrid)
	       {   
		  if(unique.find(wAddress + 1) != unique.end())
		  {
		     StripMap::const_iterator nextIter = istr_help; ++nextIter;
		     if( (*nextIter).second < threshold )
		     { 
			unique.erase(istr_help);
			continue;
		     }
		     else
		     { 
			continue;
		     }
		  }
		  else 
		  { 
		     unique.erase(istr_help);
		     continue;
		  }
	       }
	       else if(stripLocale == lastOnHybrid)
	       {
		  if(unique.find(wAddress - 1) != unique.end())
		  {
		     StripMap::const_iterator prevIter = istr_help; --prevIter;
		     if((*(prevIter)).second < threshold)
		     {
			unique.erase(istr_help);
			continue; 
		     }
		     else 
		     {
			continue;
		     }
		  }
		  else 
		  {
		     unique.erase(istr_help);
		     continue; 
		  }
	       }
	       else if((stripLocale == firstOnChip) || 
		       (stripLocale == lastOnChip)  ||
		       (stripLocale == normal))
	       {
		  if(unique.find(wAddress - 1) != unique.end()) 
		  { 
		     StripMap::const_iterator prevIter = istr_help; 
		     --prevIter; 
		     if((*(prevIter)).second >= threshold)
		     {
			continue;
		     }
		  } 
		  if(unique.find(wAddress + 1) != unique.end())
		  {
		     StripMap::const_iterator nextIter = istr_help; 
		     ++nextIter;
		     if((*(nextIter)).second >= threshold)
		     {
			continue;
		     }
		     else  
		     {
			unique.erase(istr_help);
			continue; 
		     }
		  } 
		  else  
		  {
		     unique.erase(istr_help);
		     continue; 
		  }
	       }
	    }
	 }
      }

      if( !areAddressesFilled ) fillJammedChannelAddresses();

      //insert jammed channels into the data stream
      for(UInt32 iCounter = 0; iCounter < 2*NUMBERJAMMEDCHANNELSPERCRATE; iCounter++)
      {
	 UInt32 nextAddress = AddressesOfJammedChannels[iCounter];
	 if(   unique.find(nextAddress) == unique.end() )
	 {
	    //unique.insert(StripMap::value_type(nextAddress,0));
	    addToMap(nextAddress, commonNoise);
	 }
      }

      if( sparsifierVersion() == HELLO_WORLD_VERSION ||
	  sparsifierVersion() == VERSION_1   )
      {
	 
	 //////////////////////////////////////////////////////////////////////
	 //Two objects holding sparsification algorithms for the two data    //
	 //crates (re)created in updateSparAlgorithm(iRecord) function  which//
	 //is bound to Stream::kBeginRun. This function also prepares channel//
	 //constants for the two crates. Each event the data are split into  //
	 //two chunks and are given to the objects with algorithms.          // 
	 //////////////////////////////////////////////////////////////////////
	 
	 if( ! doesSparExist )
	 {
	    report( INFO, kReport )<< 
	       "SVX sparsifier has not been created yet => create it for run "<<runNumber<<endl;
	    updateSparAlgorithm(iRecord);
	 }
	 
	 CopySiSparsifierAccessories::increaseEventCount();
	 
	 UInt32  wordsWrittenCrate1 = 0;
	 UInt32  wordsWrittenCrate2 = 0;
	 
	 //split the data  
	 for( istr = unique.begin(); istr != unique.end() ; ++istr)
	 {
	    UInt32 wAddress = (*istr).first;
	    int adc = (*istr).second;
	    SVChannelStatus status( myChannelConsts[wAddress].get_Status() );
	    
	    if( status.disconnected() ) continue;
	    
	    const SVDatum::DaqIdType   daqId   ( wAddress ) ;
	    const SVDatum::ControlType control ( 0 ) ;
	    const SVDatum::DigiType    digi    ( adc ) ;
	    
	    UInt32 crateNum;
	    crateNum = crateNumber(wAddress);
	    
	    if( crateNum == 1 )
	    {
	       if( wordsWrittenCrate1 > maxNumberOfWords )
	       {
		  report( ERROR, kReport ) << "Too many SV Hits in cr1 ... not written out!" << endl ;
	       }
	       else
	       {
		  *(pCrate1+wordsWrittenCrate1+crateOffset) =
		     RawHits< SVDatum >::packRawWord( daqId, control, digi ) ;
		  wordsWrittenCrate1++;
	       }
	    }
	    else if ( crateNum == 2 ) 
	    {
	       if( wordsWrittenCrate2 > maxNumberOfWords )
	       {
		  report( ERROR, kReport ) << "Too many SV Hits in cr2 ... not written out!" << endl ;
	       }
	       else
	       {
		  *(pCrate2+wordsWrittenCrate2+crateOffset) = 
		     RawHits< SVDatum >::packRawWord( daqId, control, digi );
		  wordsWrittenCrate2++;
	       }
	    }
	    else
	    {
	       report( WARNING, kReport ) << 
		  "*****SVX: channel address out of range: " << crateNum 
					  <<" *****" << endl;
	    }
	 }

//bkh Skipping this block of code does bad things!
//bkh	 if(  CopySiSparsifierAccessories::getEventCount() % 
//bkh	      CopySiSparsifierAccessories::SVSparNKeep != 0 )
	 {
	    
	    UInt32 *dataWord; 
	    
	    UInt32 *readFromCrate1;
	    UInt32 *writeToCrate1;
	    UInt32  wordsToReadCrate1;
	    
	    //readFromCrate1     = NULL;
	    //writeToCrate1      = NULL;
	    //wordsToReadCrate1  = 0;
	    
	    UInt32 *readFromCrate2;
	    UInt32 *writeToCrate2;
	    UInt32  wordsToReadCrate2;
	    
	    //readFromCrate2     = NULL;
	    //writeToCrate2      = NULL;  
	    //wordsToReadCrate2  = 0;
	    
	    DABoolean first;
	    first = true;
	    
	    readFromCrate1 = pCrate1 + crateOffset;
	    readFromCrate2 = pCrate2 + crateOffset;
	    
	    //write to the same array ( reading is done first )
	    writeToCrate1  = pCrate1;
	    writeToCrate2  = pCrate2;
	    
	    wordsToReadCrate1  = wordsWrittenCrate1;
	    wordsToReadCrate2  = wordsWrittenCrate2;
	    
	    wordsWrittenCrate1 = 0;
	    wordsWrittenCrate2 = 0;
	    
	    
	    ///////////////////////////////////////////////
	    //sparsify data words using online algorithms//
	    ///////////////////////////////////////////////
	    
	    if( sparsifierVersion() == VERSION_1 ) 
	    {
	       //myAlgorithm1->myWordRegister->initialize();
	       //myAlgorithm2->myWordRegister->initialize();

	       //sparsify the first crate
	       myAlgorithm1->processData( readFromCrate1, wordsToReadCrate1,
					  writeToCrate1,  wordsWrittenCrate1 );
	       
	       //sparsify the second crate
	       myAlgorithm2->processData( readFromCrate2, wordsToReadCrate2,
					  writeToCrate2,  wordsWrittenCrate2 );
	       
	    }
	    else if ( sparsifierVersion() == HELLO_WORLD_VERSION  )
	    {
	       
	       //sparsify the first crate
	       myAlgorithm1->suppressJammedChannels(  readFromCrate1, wordsToReadCrate1,
						      writeToCrate1,  wordsWrittenCrate1 );
	       
	       //sparsify the second crate
	       myAlgorithm2->suppressJammedChannels(  readFromCrate2, wordsToReadCrate2,
						      writeToCrate2,  wordsWrittenCrate2 );
	    }
	    
	    
	    if( !m_words.empty() ) 
	    { 
	       m_words.erase( m_words.begin(), m_words.end() ) ; 
	    }
	 }   
	 
	 assert ( m_words.empty() );
	 
	 for( UInt32 crate1Counter = 0; crate1Counter < wordsWrittenCrate1; crate1Counter++)
	 {
	    const UInt32* ptr ( pCrate1+crate1Counter ) ; 
	    if( (*ptr) == kMagicNumber ) 
	    {
	       report( ERROR, kReport ) << "Bad SV data at cc1= " << crate1Counter << endl ;
	    }
	    else
	    {
	       m_words.push_back( *ptr ) ;
	    }
	 }
	 
	 for( UInt32 crate2Counter = 0; crate2Counter < wordsWrittenCrate2; crate2Counter++)
	 {
	    const UInt32* ptr ( pCrate2+crate2Counter ) ; 
	    if( (*ptr) == kMagicNumber ) 
	    {
	       report( ERROR, kReport ) << "Bad SV data at cc2= " << crate2Counter << endl ;
	    }
	    else
	    {
	       m_words.push_back( *ptr ) ;
	    }
	 }
      }
      else
      {
	 for( istr = unique.begin(); istr != unique.end() ; ++istr)
	 {
	    UInt32 wAddress = (*istr).first;
	    int adc = (*istr).second;
	    SVChannelStatus status( myChannelConsts[wAddress].get_Status() );
	    if( status.disconnected() ) continue;
	    const SVDatum::DaqIdType   daqId   ( wAddress ) ;
	    const SVDatum::ControlType control ( 0 ) ;
	    const SVDatum::DigiType    digi    ( adc ) ;
	    m_words.push_back(
	       RawHits< SVDatum >::packRawWord( daqId, control, digi ) ) ;
	 }
      }
   }

   m_RawSVHits = new RawSVHits( &(*(m_words.begin())), m_words.size() );
   return m_RawSVHits ;
   
}


void MCRawSVHitsProxy::loadSparsifierConsts() 
{
   
//   if( runNumber >= sparConstsInstalled )
//   {
//      extract( iRecord.frame().record( Stream::kSVCalibOnline ), mySparConsts );
//      if( ! mySparConsts.valid() )
//      {

   CopySiSparsifierAccessories::SVSparNSigmaUp            =   3.5;
   CopySiSparsifierAccessories::SVSparNSigmaDown          =  10.0;
   CopySiSparsifierAccessories::SVSparThresholdWindowUp   =   2.5;
   CopySiSparsifierAccessories::SVSparThresholdWindowDown = 100.0;
   CopySiSparsifierAccessories::SVSparNeighborWindowUp    =   0.0;
   CopySiSparsifierAccessories::SVSparNeighborWindowDown  = 100.0;
   CopySiSparsifierAccessories::SVSparNoisyChannel        =  20.0;
   CopySiSparsifierAccessories::SVSparLatched             = 250.0;
   CopySiSparsifierAccessories::SVSparNKeep               =    50;
   CopySiSparsifierAccessories::CMN_ADCDown               =   1.0;
   CopySiSparsifierAccessories::CMN_ADCUp                 = 250.0;
   CopySiSparsifierAccessories::CMN_NoiseDown             =   0.4;
   CopySiSparsifierAccessories::CMN_NoiseUp               =  20.0;
   CopySiSparsifierAccessories::CMN_NSigmaChip            =   4.0;
   CopySiSparsifierAccessories::CMN_NSigmaSide            =   4.0;
   CopySiSparsifierAccessories::CMN_DeltaSideCut          =   2.0;

//      }
//      else
//      {
//	 CopySiSparsifierAccessories::SVSparNSigmaUp            = 
//	    (*mySparConsts)[0].get_SVSparNSigmaUp();
//	 CopySiSparsifierAccessories::SVSparNSigmaDown          = 
//	    (*mySparConsts)[0].get_SVSparNSigmaDown();
//	 CopySiSparsifierAccessories::SVSparThresholdWindowUp   = 
//	    (*mySparConsts)[0].get_SVSparThresholdWindowUp();
//	 CopySiSparsifierAccessories::SVSparThresholdWindowDown = 
//	    (*mySparConsts)[0].get_SVSparThresholdWindowDown();
//	 CopySiSparsifierAccessories::SVSparNeighborWindowUp    = 
//	    (*mySparConsts)[0].get_SVSparNeighborWindowUp();
//	 CopySiSparsifierAccessories::SVSparNeighborWindowDown  = 
//	    (*mySparConsts)[0].get_SVSparNeighborWindowDown();
//	 CopySiSparsifierAccessories::SVSparNoisyChannel        = 
//	    (*mySparConsts)[0].get_SVSparNoisyChannel();
//	 CopySiSparsifierAccessories::SVSparLatched             = 
//	    (*mySparConsts)[0].get_SVSparLatched();
//	 CopySiSparsifierAccessories:: SVSparNKeep              = 
//	    (*mySparConsts)[0].get_SVSparNKeep();
//	 CopySiSparsifierAccessories::CMN_ADCDown               = 
//	    (*mySparConsts)[0].get_CMN_ADCDown();
//	 CopySiSparsifierAccessories::CMN_ADCUp                 = 
//	    (*mySparConsts)[0].get_CMN_ADCUp();
//	 CopySiSparsifierAccessories::CMN_NoiseDown             = 
//	    (*mySparConsts)[0].get_CMN_ADCDown();
//	 CopySiSparsifierAccessories::CMN_NoiseUp               = 
//	    (*mySparConsts)[0].get_CMN_NoiseUp();
//	 CopySiSparsifierAccessories::CMN_NSigmaChip            = 
//	    (*mySparConsts)[0].get_CMN_NSigmaChip();
//	 CopySiSparsifierAccessories::CMN_NSigmaSide            = 
//	    (*mySparConsts)[0].get_CMN_NSigmaSide();
//	 CopySiSparsifierAccessories::CMN_DeltaSideCut          = 
//	    (*mySparConsts)[0].get_CMN_DeltaSideCut();
//      }
//   }
}

//
// const member functions
//

//
// static member functions
//

//
// 'bound' functions
//
//void
//MCRawSVHitsProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

void MCRawSVHitsProxy::updateSparAlgorithm(const Record& iRecord) 
{
   ///////////////////////////////////////////////////////////////////////////////
   //Channel constants and the sparsification algorithm may change from one run //
   //to another run. This function deletes the algorithm object for the previous// 
   //run and creates a new one for the current run with a pointer to channel    //
   //constants for the current run.                                             //
   ///////////////////////////////////////////////////////////////////////////////
   
   FAItem< DBEventHeader > eventHeader ;
   extract( iRecord.frame().record( Stream::kEvent ) ,
	    eventHeader ) ;
   
   runNumber = (*eventHeader).run();

   report( INFO, kReport )
      << "Updating SVX sparsification algorithm for run "
      <<runNumber<<"..."<<endl;

   if( runNumber >= HELLO_WORLD_VERSION )
   {
      //delete and recreate algorithm and constants arrays
      //(what comes first calib or begin run record?)
      if(myAlgorithm1 != NULL)    delete myAlgorithm1;
      if(myAlgorithm2 != NULL)    delete myAlgorithm2;

      if(crate1Constants != NULL) delete crate1Constants;
      if(crate2Constants != NULL) delete crate2Constants;

      //extract online channel calibration constants (is it ok to do that so)
      extract( iRecord.frame().record( SiStream::kSVCalibOnline ), myChannelOnlineConsts );
      if( ! myChannelOnlineConsts.valid() )
      {
	 report (ERROR, kReport ) 
	    << "Not valid SVChannelOnline constants!!!"
	    << endl;
      }
      else
      {
	 //get CLEOConstants 
	 const CLEOConstants< DBSVChannelOnline > *ptrChannels;
	 ptrChannels = myChannelOnlineConsts.getContents();
	 
	 CopySiSparsifierAccessories::constantSize = (*ptrChannels).size() / 2;
	 
	 if( (NUM_SVX_CHANNELS/2) != CopySiSparsifierAccessories::constantSize )
	 {
	    report (ERROR, kReport ) <<"Wrong size of channel constants: "
				     <<CopySiSparsifierAccessories::constantSize<<endl;
	 }
	 
	 DBSVChannelOnline *crate1Init = new 
	    DBSVChannelOnline[CopySiSparsifierAccessories::constantSize];
	 DBSVChannelOnline *crate2Init = new 
	    DBSVChannelOnline[CopySiSparsifierAccessories::constantSize];
	 
	 splitConstants(ptrChannels,crate1Init,crate2Init);
	 
	 if(crate1Init != NULL) delete [] crate1Init;
	 if(crate2Init != NULL) delete [] crate2Init;
	 
	 //create objects containig sparsification algorithms 
	 //one for each of the two online readout crates
	 myAlgorithm1 = new CopySiSparsifier(crate1Constants, OFF_LINE);
	 myAlgorithm2 = new CopySiSparsifier(crate2Constants, OFF_LINE);
	 
	 //fill jammed channel index arrays for myAlgorithm1 and myAlgorithm2
	 fillJammedChannelIndices( myAlgorithm1->get_jammedIdxPtr(),crate1Constants );
	 fillJammedChannelIndices( myAlgorithm2->get_jammedIdxPtr(),crate2Constants );

      }
      
      //load constants for the final version of sparsifier 
      loadSparsifierConsts();
      
      report( INFO, kReport )
	 << "SVX sparsification algorithm is updated."<<endl;
   }
   
   doesSparExist = TRUE;
}   


void MCRawSVHitsProxy::splitConstants(const CLEOConstants< DBSVChannelOnline > *ptrChannels,
				            DBSVChannelOnline  *crate1Init,
				            DBSVChannelOnline  *crate2Init)
{
   UInt32 crate1Counter = 0;
   UInt32 crate2Counter = 0;
   UInt32 mainCounter   = 0;
   UInt32 address;
   UInt32 crateId = 0;

   
   for( mainCounter = 0; mainCounter < 
	   (2*CopySiSparsifierAccessories::constantSize); mainCounter++)
   {
      address = (*ptrChannels)[mainCounter].get_DaqID();
      crateId = crateNumber(address);
      
      if(crateId == 1)
      {
	 
	 *(crate1Init+crate1Counter) =  (*ptrChannels)[mainCounter]; 
	 crate1Counter++;
      }
      else if (crateId == 2)
      {
	 *(crate2Init+crate2Counter) =  (*ptrChannels)[mainCounter]; 
	 crate2Counter++;
      }
      else
      {
	 report( ERROR, kReport ) << "Did not split channel constants between the crates properly: "
				  <<endl<<"got a wrong crate number = "<<crateId<<endl;
      }
   }

   crate1Constants = new CLEOConstants<DBSVChannelOnline>(crate1Init,
			 CopySiSparsifierAccessories::constantSize, 0);
   crate2Constants = new CLEOConstants<DBSVChannelOnline>(crate2Init,
			 CopySiSparsifierAccessories::constantSize, 0);

   if (crate1Counter != crate2Counter || crate1Counter != 
       CopySiSparsifierAccessories::constantSize)
   {
      report( ERROR, kReport )<<"Did not split channel constants between the crates properly: "
			      <<"crate constant counters are of wrong sizes..."  <<endl;
   }
}



	 
void MCRawSVHitsProxy::fillJammedChannelIndices(UInt32* jammedIdxPtr, 
			   CLEOConstants< DBSVChannelOnline > *crateConstants )
{
   UInt32 kJammedCounter = 0;
   DABoolean validConstants = TRUE; 
   
   for(int iCounter = 0 ; iCounter < CopySiSparsifierAccessories::constantSize; iCounter++ )
   {
      UInt32 addr;
      UInt32 idx;
      
      //check the constants for consistency, 
      //this indexing is used in the spar. algorithm
      addr = (*crateConstants)[iCounter].get_DaqID();
      idx = get_SVXIdx(addr);
      
      if(idx < CopySiSparsifierAccessories::constantSize)
      {
	 if( (*crateConstants)[idx].get_DaqID() != addr ) validConstants = FALSE;
	 if( idx != iCounter ) validConstants = FALSE;
	 if( (*crateConstants )[idx].get_Status() & SVChannelOnlineEnum::kJammed )
	 {
	    if(kJammedCounter < NUMBERJAMMEDCHANNELSPERCRATE)
	    {
	       *(jammedIdxPtr+kJammedCounter) = idx;
	       kJammedCounter++;
	    }
	 }
      }
      else
      {
	 report( ERROR, kReport ) <<"Out of range, idx = " << idx << endl;
	 validConstants = FALSE;
      }
   }
   
   if( !validConstants || kJammedCounter !=  NUMBERJAMMEDCHANNELSPERCRATE )
   {
      report( ERROR, kReport ) <<
	 "fillJammedChannelIndices: jammed channel index array is not filled properly..."<<endl;
   }

}  


void MCRawSVHitsProxy::fillJammedChannelAddresses()
{
   areAddressesFilled = TRUE;

   UInt32 kJammedCounter = 0;
   DABoolean validConstants = TRUE; 

   for(UInt32 iCounter = 1 ; iCounter < myChannelConsts.size(); iCounter++ )
   //for(UInt32 iCounter = 1 ; iCounter < myChannelOnlineConsts.size(); iCounter++ )
   {
      if( myChannelConsts[iCounter].get_ChannelNumber() != iCounter ) validConstants = FALSE;
      //if( myChannelOnlineConsts[iCounter].get_Status() & SVChannelOnlineEnum::kJammed )
      

      if( myChannelConsts[iCounter].get_Status() & SVChannelStatus::kHot /*kGoodJammedChannel*/)
      {
	 if (kJammedCounter < 2*NUMBERJAMMEDCHANNELSPERCRATE)
	 {
	    *(AddressesOfJammedChannels+kJammedCounter) = 
	       myChannelConsts[iCounter].get_ChannelNumber();
	    //*(AddressesOfJammedChannels+kJammedCounter) = 
	    //   myChannelOnlineConsts[iCounter].get_DaqID();

	    kJammedCounter++;
	 }
      }
   }
   
   if( validConstants && kJammedCounter ==  2*NUMBERJAMMEDCHANNELSPERCRATE )
   {
      report( INFO, kReport ) <<
	 "fillJammedChannelAddresses: jammed channel address array is filled..."<<endl;
      report(INFO, kReport ) <<"The number of jammed channels found is "<< kJammedCounter<<endl;
   }
   else
   {
      report( ERROR, kReport ) <<
	 "fillJammedChannelAddresses: jammed channel address array is not filled properly..."<<endl;
   }

}  


int MCRawSVHitsProxy::upDateChipConstants(const Record& iRecord)
{

   report (INFO, kReport )<<"Updating back-end chip constants for SVX ..."<<endl;

   FAConstants< DBSVChipSet > chipConsts;
   extract( iRecord.frame().record( SiStream::kSVOnline ), chipConsts);
   
   if( !chipConsts.valid() )
   {
      report (ERROR, kReport ) 
	 << "Not valid SVChipSet constants ... " << endl;
      return 1; //error return
   }
   
   for(int iCounter = 1; iCounter <= TOTAL_NUMBER_OF_CHIPS; iCounter++)
   {
      backEndChipThreshold[iCounter - 1] = 
	 chipConsts[iCounter].get_BackEndThreshold();
      backEndChipMode[iCounter - 1] = 
	 chipConsts[iCounter].get_BackEndMode();
   }
   
   report (INFO, kReport )<<"Back-end chip constants for SVX are updated."<<endl;

   return 0;  //normal return
}

int MCRawSVHitsProxy::sparsifierVersion()
{


  if( runNumber  <  HELLO_WORLD_VERSION)
  {
     return -1;
  }
  else if( runNumber < VERSION_1 )
  {
     if( (runNumber >= 111532 && runNumber <= 111581) ||
	 (runNumber >= 111648 && runNumber <= 111829) ||
	 (runNumber >= 111852 && runNumber <= 111874) ||
	 (runNumber >= 112310 && runNumber <= 114333) )
     {
	return HELLO_WORLD_VERSION;
     }
     else
     {
	return -1;
     }
  }
  else
  {
      if( ( runNumber >= 114334 && runNumber <= 114341 ) ||
            runNumber >= 114365   )
     {
	return VERSION_1;
     }
     else
     {
        return HELLO_WORLD_VERSION;
     }
  }

}
//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< RawSVHits >;

PROXY_BIND_METHOD( MCRawSVHitsProxy )
//-----------------------------------------------

