// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawMUHitsProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawMUHitsProxy.cc,v 1.9 2003/01/29 19:31:06 cleo3 Exp $
//
// Revision history
//
// $Log: MCRawMUHitsProxy.cc,v $
// Revision 1.9  2003/01/29 19:31:06  cleo3
// changes needed to compile using g++
//
// Revision 1.8  2002/09/27 20:23:11  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.7  2001/05/03 20:58:48  savinov
// Now using FortranInterface to pass reference to the frame to c++ classes called from Fortran mu routines called from c++ MCRawData fault handler for mu hits
//
// Revision 1.6  2001/05/01 22:18:29  swnam
// previous dummy skelecton codes now filled with codes calling
// murawd_noz.F for muon detector digitization and filling MUDatum table
//
// Revision 1.5  2001/04/30 17:05:23  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.4  2000/01/25 14:26:36  bkh
// Fix bug allowing return of empty container
//
// Revision 1.3  1999/10/24 20:37:23  cdj
// removed inappropriate use of typename
//
// Revision 1.2  1999/06/04 21:38:53  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:53  bkh
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

#include "MCRawData/MCRawMUHitsProxy.h"
#include "MCResponse/MCMUResponse.h" 
#include "RawData/RawHits.h" 
#include "FortranInterface/FortranInterfacer.h"


// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

#include "FortranInterface/FortranInterfacer.h"

//
// constants, enums and typedefs
//

static const char* const kReport = "MCRawData.MCRawMUHitsProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
MCRawMUHitsProxy::MCRawMUHitsProxy( 
   const Parameter<DABoolean>& aMakeMCRawMUHits ) :
   m_RawMUHits( 0 ) ,
   m_words    (  ) ,
   m_makeMCRawMUHits ( aMakeMCRawMUHits )
{
   report( DEBUG, kReport ) 
      << "MakeMCRawMUHits: " << m_makeMCRawMUHits.value() << endl;

   m_words.reserve( 500 ) ; // allocate reasonable length just once!
}

// MCRawMUHitsProxy::MCRawMUHitsProxy( const MCRawMUHitsProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRawMUHitsProxy::~MCRawMUHitsProxy()
{
   delete m_RawMUHits ;
}

//
// assignment operators
//
// const MCRawMUHitsProxy& MCRawMUHitsProxy::operator=( const MCRawMUHitsProxy& iproxy )
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
MCRawMUHitsProxy::invalidateCache()
{
   delete m_RawMUHits ;
   m_RawMUHits = 0 ;
   if( !m_words.empty() ) 
   { 
      m_words.erase( m_words.begin(), m_words.end() ) ; 
   }
}


extern "C" void 
murawd_noz_(FInteger daqId_in[],
            FReal    x01[],
            FReal    x02[],
            FReal    beta1[],
            FReal    beta2[],
            FInteger& muonhitsinput,
            FInteger& muonhitsoutput,
            FInteger daqId_out[],
            FReal    digi1[],
            FReal    digi2[]);


const MCRawMUHitsProxy::value_type*
MCRawMUHitsProxy::faultHandler( const Record& iRecord,
				const DataKey& iKey )
{
   report( DEBUG, kReport ) << "faultHandler called !!" << endl;

   assert( 0 == m_RawMUHits ) ;
   assert( m_words.empty()  ) ; // always start out empty
   
   // check if MCRawMUHits are wanted at all; otherwise leave m_RawSVHits empty 
   if( m_makeMCRawMUHits.value() ) 
   {
      FATable< MCMUResponse > responses ; 
      extract( iRecord, responses ); 
      if( !responses.valid() ) 
      {
	 report( WARNING, kReport ) << "No MU Responses found" << endl;
	 return 0 ;
      }

      report(DEBUG, kReport) << "There are " << responses.size() << " MU Responses" << endl;

      static const FInteger maxinmuonhits (100);
      FInteger daqId_in[maxinmuonhits];
      FReal    x01[maxinmuonhits];
      FReal    x02[maxinmuonhits];
      FReal    beta1[maxinmuonhits];
      FReal    beta2[maxinmuonhits];
      FInteger muonhitsinput = 0;
      FInteger muonhitsoutput;
      static const FInteger maxoutmuonhits (600);
      FInteger daqId_out[maxoutmuonhits];
      FReal    digi1[maxoutmuonhits];
      FReal    digi2[maxoutmuonhits];
      
      // extract all hits from MCMUResponse 
      for ( FATable<MCMUResponse>::const_iterator responseIter = responses.begin() ;
	    responseIter != responses.end() ; ++responseIter )
      {
	 int ihit = muonhitsinput++;
	 daqId_in[ihit] = responseIter->cellId();
	 x01[ihit]      = responseIter->x01();
	 x02[ihit]      = responseIter->x02();
	 beta1[ihit]    = responseIter->beta1();
	 beta2[ihit]    = responseIter->beta2();
	 
	 report(DEBUG, kReport) << "input to murawd_noz " 
				<< x01[ihit] << " " << x02[ihit] << " " 
				<< beta1[ihit] << " " << beta2[ihit] << endl;
      }

      // prepare to hand the frame to c/c++ called from Fortran
      FortranInterfacer::instance().useFrame( iRecord.frame() ); 

      // this routine does all readout simulation
      murawd_noz_(daqId_in,x01,x02,beta1,beta2,muonhitsinput,
		  muonhitsoutput,daqId_out,digi1,digi2);
      
      // release handle to the frame
      FortranInterfacer::instance().releaseFrame();

      // stores finalized muon hits to <MUDatum>
      for (int ihit=0;ihit<muonhitsoutput;ihit++) {
	 const MUDatum::DaqIdType   daqId   (daqId_out[ihit]);
	 
	 const MUDatum::DaqIdType   daqId1  (daqId*2-1);
	 const MUDatum::ControlType control ( 0 ) ;
	 const MUDatum::DigiType    ph1    (digi1[ihit]);
	 m_words.push_back(RawHits<MUDatum>::packRawWord(daqId1, control, ph1)) ;
	 
	 report(DEBUG, kReport) << "Adding MU raw hit daqid " << daqId1 
				<< " adc1 " << ph1
				<< " control " << control << endl;
	 
	 
	 const MUDatum::DaqIdType   daqId2  (daqId*2);
	 const MUDatum::DigiType    ph2    (digi2[ihit]);
	 m_words.push_back(RawHits<MUDatum>::packRawWord(daqId2, control, ph2)) ;
	 
	 report(DEBUG, kReport) << "Adding MU raw hit daqid " << daqId2 
				<< " adc2 " << ph2
				<< " control " << control << endl;
	 
      }   
   }  // continue here in case no MCRawMUHits were wanted (above)
   m_RawMUHits = new RawMUHits( &(*(m_words.begin())), m_words.size() );
   
   return m_RawMUHits ;
}

//
// const member functions
//

//
// static member functions
//


