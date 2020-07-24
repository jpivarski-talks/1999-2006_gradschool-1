// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawCathodesProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawCathodesProxy.cc,v 1.16 2003/01/29 19:31:04 cleo3 Exp $
//
// Revision history
//
// $Log: MCRawCathodesProxy.cc,v $
// Revision 1.16  2003/01/29 19:31:04  cleo3
// changes needed to compile using g++
//
// Revision 1.15  2002/10/01 20:30:40  bkh
// Event: Do not ask for beginrun while in an endrun
// Cathodes: move local arrays to member data to avoid stack load
//
// Revision 1.14  2002/09/27 20:23:08  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.13  2002/01/12 00:00:54  hennessy
// undoing most recent change
//
// Revision 1.12  2002/01/09 22:34:38  hennessy
// added flag to use fake noise when no merging is included
//
// Revision 1.11  2001/12/20 17:11:19  bkh
// Install fake merge flag for Cathodes as with other detectors
// Use fake merge flag for Cathodes
// Fix SV proxy fcn to avoid compiler warning about
//      argument overriding member data
//
// Revision 1.10  2001/04/30 17:05:22  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.9  2000/06/29 21:16:00  hennessy
// added access to DRCA pedestals
//
// Revision 1.8  2000/04/24 19:23:49  hennessy
// checks cell ID for validity
//
// Revision 1.7  2000/04/17 20:07:56  bkh
// Elim checks of ptr after new
//
// Revision 1.6  2000/03/28 16:06:50  hennessy
// changed integer to float in STL Vector
//
// Revision 1.5  2000/03/24 01:22:52  hennessy
// Implemented cathode raw data code
//
// Revision 1.4  2000/01/25 14:26:35  bkh
// Fix bug allowing return of empty container
//
// Revision 1.3  1999/10/24 20:37:22  cdj
// removed inappropriate use of typename
//
// Revision 1.2  1999/06/04 21:38:50  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:50  bkh
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
#include <algorithm>
#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "C3DRCA/DRCAStream.h"
#include "MCRawData/MCRawCathodesProxy.h"

#include "MCResponse/MCCathodesResponse.h" 

#include "RawData/RawHits.h" 
#include "RawData/CathodesDatum.h" 
#include "RandomModule/RandomGenerator.h"
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

static const char* const kReport = "MCRawData.MCRawCathodesProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawCathodesProxy::MCRawCathodesProxy( 
   const Parameter<DABoolean>& aMake ,
   const Parameter<DABoolean>& aFake   ) :
   m_RawCathodes( 0 ) ,
   m_words      ( ) ,
   m_make       ( aMake ) ,
   m_fake       ( aFake ) ,
   m_chargeTotal( 1537, (float)0),
   m_pedestal   ( 1537, (float)0),
   m_thresh     ( 1537, (int)  0),
   m_slope      ( 1537, (float)0),
   m_noise      ( 1537, (float)0),
   m_width      ( 1537, (float)0),
   m_adc        ( 1537, (int)  0),
   m_adcOut     ( 1537, (int)  0),
   m_idCell     ( 1537, (int)  0)
{
   m_words.reserve( 2000 ) ; // allocate reasonable length just once!
}

// MCRawCathodesProxy::MCRawCathodesProxy( const MCRawCathodesProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawCathodesProxy::~MCRawCathodesProxy()
{
   delete m_RawCathodes ;
}

//
// assignment operators
//
// const MCRawCathodesProxy& MCRawCathodesProxy::operator=( const MCRawCathodesProxy& iproxy )
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
MCRawCathodesProxy::invalidateCache()
{
   delete m_RawCathodes ;
   m_RawCathodes = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}

const MCRawCathodesProxy::value_type*
MCRawCathodesProxy::faultHandler( const Record&  iRecord,
				  const DataKey& iKey )
{
   assert( 0 == m_RawCathodes ) ;
   assert( m_words.empty()  ) ; // always start out empty

   // check if MCRawCathodesHits are wanted at all; otherwise leave m_RawCathodesHits empty 
 
   if ( m_make.value() ) 
   {

// get merge flag

//      const Parameter<DABoolean> & useFakeMerge;
//      m_useFakeMerge   = aFake.value();

// extract response objects
   FATable< MCCathodesResponse > responses ; 
   extract( iRecord, responses ); 
   
// extract constants
   Frame& iFrame=iRecord.frame();
   extract( iFrame.record( DRCAStream::kDRCAPedestal ), m_CnstDRCA );
   assert( m_CnstDRCA.valid() );


// 
   int i=0;
   float mean=0;

// create random number generator object
   //   STL_VECTOR( RandomGenerator::value_type ) gaussians ( 1, 0. );
   RandomGenerator& ran ( RandomGenerator::instance() ) ;


// channel based constants 
   for(i=1; i<1537; i++){ 
       m_chargeTotal[i]=0.; 
       m_slope[i]=2.0; 
       m_pedestal[i] =  m_CnstDRCA[i].get_Pedestal(); 
       m_thresh[i] = m_CnstDRCA[i].get_Threshold();  /* threshold == ped-1sig*/
       m_width[i] = m_pedestal[i]-m_thresh[i];
       const double myGaussianRandom ( ran.gauss( mean , m_width[i] ) ) ;
       //       ran.gauss( gaussians.begin(), gaussians.end(), mean, m_width[i] ) ; 
       m_noise[i] = myGaussianRandom;
                        }
    
// get response object
   int id=0;

   if( responses.valid() ) 
   {
    FATable < MCCathodesResponse >::const_iterator lasthit=responses.end();
  
    for (FATable < MCCathodesResponse >::const_iterator hit=responses.begin();
        hit != lasthit; ++hit )   
      { 
       id=(*hit).cellId();
      if( id > 0 & id < 1537 ) { m_chargeTotal[id] += (*hit).charge() ; }
      else{report( WARNING, kReport ) << "Invalid Cathode DAQID" << endl;}   
      }
    }
    

// digitize
   int iadc=0;

   for(i=1; i<1537; i++){
     iadc = (int) (m_chargeTotal[i]/m_slope[i]); 
     m_adc[i]=(int) m_pedestal[i]-iadc+m_noise[i];
     if(m_adc[i]<0){m_adc[i]=0;}    // saturate
   }

   
// sparsify

   UInt32 nHits ( 0 ) ;
   for(i=1; i<1537; i++)
   {
    if( ( m_adc[i] < m_thresh[i] ) &&
	( m_fake.value() || ( 0 < m_chargeTotal[i] ) ) ) // require real hit if no fakes
    {
      nHits++ ;
      m_adcOut[nHits]=m_adc[i];
      m_idCell[nHits]=i;
    }
   }
      
// Create raw data
   if( 0 < nHits )
   {
      for( UInt32 iWord ( 1 ) ; iWord < (nHits+1) ; ++iWord )
      {
       
	 // typical code to pack word
            
      	 const CathodesDatum::DaqIdType daqId     ( m_idCell[iWord] ) ;
	 const CathodesDatum::DigiType  digi      ( m_adcOut[iWord] ) ;
	 const CathodesDatum::ControlType control ( 0 ) ;

	 m_words.push_back(
	 RawHits< CathodesDatum >::packRawWord( daqId, control, digi ) ) ;
      }
   }

   // continue here in case no MCRawCathodesHits were wanted (above)
   }

   m_RawCathodes = new RawCathodes( &(*(m_words.begin())), m_words.size() );
   return m_RawCathodes; }

   