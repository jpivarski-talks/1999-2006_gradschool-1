// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCMUResponseProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCMUResponseProxy.cc,v 1.9 2001/05/14 00:56:53 swnam Exp $
//
// Revision history
//
// $Log: MCMUResponseProxy.cc,v $
// Revision 1.9  2001/05/14 00:56:53  swnam
// number of multiplet corrected to 576
//
// Revision 1.8  2001/05/06 16:02:23  swnam
// a message print type changed from EMERGENCY to DEBUG
//
// Revision 1.7  2001/05/01 22:06:15  swnam
// mc_mu_response_ has new arguments of muon hits, old codes were commented out.
//
// Revision 1.6  2001/04/16 05:16:42  savinov
// FortranInterfacer is used to hand the frame to muon c/c++ utilities called from Fortran
//
// Revision 1.5  2001/04/09 14:24:08  mahlke
// introduce flag to switch off geometry or responses for single subdetectors
//
// Revision 1.4  2000/04/17 20:12:02  bkh
// Elim checks of ptr after new
//
// Revision 1.3  1999/10/24 20:52:33  cdj
// removed inappropriate use of typename
//
// Revision 1.2  1999/06/10 20:07:32  bkh
// fix argument ordering problem in add_response usage
//
// Revision 1.1.1.1  1999/04/16 20:07:32  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/25 21:30:55  bkh
// Update
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

// Frame access
#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAPtrTable.h"

// needed for PROXY_BIND_METHOD
#include "ProxyBind/ProxyBoundMethodAction.h" 

// Producer that calls this proxy
#include "MCResponseProd/MCResponseProd.h"

#include "MCResponseProd/MCMUResponseProxy.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

#include "FortranInterface/FortranInterfacer.h"

//
// constants, enums and typedefs
//
static const char* const kReport = "MCResponse.MCMUResponseProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCMUResponseProxy.cc,v 1.9 2001/05/14 00:56:53 swnam Exp $";
static const char* const kTagString = "$Name: v05_03_01 $";

//
// static data member definitions
//

MCMUResponseProxy* MCMUResponseProxy::k_whoAmI ( 0 ) ;

//
// constructors and destructor
//

MCMUResponseProxy::MCMUResponseProxy( MCResponseProd& iProducer )
   : m_ptrTable ( new value_type ) ,
     m_howMany  ( 0 ) ,
     m_producer( &iProducer )    
{
   // bind `auxilliary' functions that you want called when a new record
   // on the particular stream appears
   bind( &MCMUResponseProxy::updateBeginRun, Stream::kBeginRun );
}

// MCMUResponseProxy::MCMUResponseProxy( const MCMUResponseProxy& iproxy )
// {
//   *this = iproxy;
// }

MCMUResponseProxy::~MCMUResponseProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const MCMUResponseProxy& MCMUResponseProxy::operator=( const MCMUResponseProxy& iproxy )
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

void MCMUResponseProxy::invalidateCache()
{
   // Tell the producer that we need to trigger geant for the next event
   m_producer->invalidateGeantEvent() ;

   // erase ptr table of MC Response objects
   if ( 0 != m_ptrTable ) 
   {
      (*m_ptrTable).eraseAll() ;
   }
   m_howMany = 0 ;
}

MCMUResponseProxy* MCMUResponseProxy::whoAmI()
{
   return k_whoAmI ;
}

// S. Nam : this is original one with arguments StrId and StripId that we do not at all

/*
void MCMUResponseProxy::addResponse( const FInteger aCellId     ,
				     const FInteger aParticleId ,
				     const FInteger aCtrId      ,
				     const FInteger aStripId    ,
				     const FReal    aCtrAngle   ,
				     const FReal    aStripAngle   )
{
   // just to be extra careful about conversions from fortran types
   const MCMUResponse::Identifier   identifier  ( ++m_howMany  ) ;
   const MCMUResponse::PartIdType   particleId  ( aParticleId  ) ;
   const MCMUResponse::CellIdType   cellId      ( aCellId      ) ;
   const MCMUResponse::CtrIdType    ctrId       ( aCtrId       ) ;
   const MCMUResponse::StripIdType  stripId     ( aStripId     ) ;
   const MCMUResponse::CtrAngType   ctrAngle    ( aCtrAngle    ) ;
   const MCMUResponse::StripAngType stripAngle  ( aStripAngle  ) ;

   MCMUResponse* tmp ( new MCMUResponse( identifier  ,
					 particleId  ,
					 cellId      ,
					 ctrId       ,
					 stripId     ,
					 ctrAngle    ,
					 stripAngle   ) ) ;

   (*m_ptrTable).insert( tmp ) ;

}
*/


// S. Nam : changed for new arguments
void MCMUResponseProxy::addResponse( const FInteger aCellId     ,
				     const FInteger aParticleId ,
				     const FReal    ax01      ,
				     const FReal    ax02    ,
				     const FReal    abeta1   ,
				     const FReal    abeta2   )
{
   // just to be extra careful about conversions from fortran types
   const MCMUResponse::Identifier   identifier  ( ++m_howMany  ) ;
   const MCMUResponse::PartIdType   particleId  ( aParticleId  ) ;
   const MCMUResponse::CellIdType   cellId      ( aCellId      ) ;
   const MCMUResponse::X01Type      x01         ( ax01         ) ;
   const MCMUResponse::X02Type      x02         ( ax02         ) ;
   const MCMUResponse::Beta1Type    beta1       ( abeta1       ) ;
   const MCMUResponse::Beta2Type    beta2       ( abeta2       ) ;

   MCMUResponse* tmp ( new MCMUResponse( identifier  ,
					 particleId  ,
					 cellId      ,
					 x01         ,
					 x02         ,
					 beta1       ,
					 beta2     ) ) ;

   (*m_ptrTable).insert( tmp ) ;

   report ( DEBUG, kReport) << "MCMUreponseprod::addresponse called "
                 << aCellId << endl;
}


// Header for Fortran subroutine called by faultHandler to fill MC Responses.
// Two ways to fill Responses: on-the-fly or bulk-insertion.
// On-the-fly: fills each Response individually
// Bulk-insertion: pass array with all Responses at once.
// Use fortran_types.h type definitions for cross-platform compatibility
//
// No arguments for on-the-fly method of filling MC responses
// extern "C" void mc_mu_responses_() ;  

// S. Nam : old one
/*
 extern "C" void mc_mu_responses_(
    const FInteger& aMaxResponse   ,
    FInteger&       aNResponse     ,
    FInteger        aCellId[]      ,
    FInteger        aParticleId[]  ,
    FInteger        aCtrId[]       ,
    FInteger        aStripId[]     ,
    FReal           aCtrAngle[]    ,
    FReal           aStripAngle[]
    ) ;  
    */

// S. Nam : with new arguments
 extern "C" void mc_mu_responses_(
    const FInteger& aMaxResponse   ,
    FInteger&       aNResponse     ,
    FInteger        aCellId[]      ,
    FInteger        aParticleId[]  ,
    FReal           ax01[]         ,
    FReal           ax02[]         ,
    FReal           abeta1[]       ,
    FReal           abeta2[]
    ) ;  


const MCMUResponseProxy::value_type*
MCMUResponseProxy::faultHandler( const Record&  iRecord,
				 const DataKey& iKey )
{
   // Phase 1 - run Geant
   // Trigger Geant for this event.
   // m_producer points to the producer that provides this proxy (MCResponseProd)
   // and call the function triggerGeantEvent to trigger Geant if it hasn't been
   // done for this event.
   // (4/11/99 Temp fix of (Frame&) (CHANGE WHEN CURRENT UPDATED))
   report( DEBUG, kReport ) << "Calling triggerGeantEvent" << endl;
   m_producer->triggerGeantEvent( (Frame&) iRecord.frame() );


   // Phase 2 - creation of MC Response objects
   // Initialize - require ptr table of MC Responses to be empty & initialize m_howMany
   assert( 0 == (*m_ptrTable).size() ); 
   m_howMany = 0 ; 

   // check whether MUResponses are wanted at all
   report ( DEBUG, kReport) << "MU Responses wanted: "
                 << m_producer->m_getMUResponses.value() << endl;

   // if not, skip filling responses into m_ptrTable 
   if (m_producer -> m_getMUResponses.value() != 0) {

      // Prepare to hand the frame to c++ classes accessed from Fortran
      FortranInterfacer::instance().useFrame( iRecord.frame() ); 
      
      // Fill MC Responses objects (use either on-the-fly or bulk-insertion method)
      // on-the-fly method to add MC Responses to table
      //   set static pointer k_whoAmI so global fcn knows who I am
      //   call Fortran mc_xx_add_response_ for each response
      report( DEBUG, kReport ) << "Calling mc_mu_responses_" << endl;
      k_whoAmI = this ; 
      
      //    S. Nam : original one
      //     mc_mu_responses_() ; 

      // declare variables for calling mc_mu_responses_
      static const FInteger k_maxResponse ( 100 ) ; // max # hits
      FInteger cellIdF[     k_maxResponse ] ;        // cellId's
      FInteger particleIdF[ k_maxResponse ] ;        // particleId's
      // S. Nam : old variables 
      //         FInteger ctrIdF[      k_maxResponse ] ;
      //         FInteger stripIdF[    k_maxResponse ] ;
      //         FReal    ctrAngleF[   k_maxResponse ] ;
      //         FReal    stripAngleF[ k_maxResponse ] ;
      // S. Nam : new variables 
      FReal x01F[      k_maxResponse ] ;
      FReal x02F[    k_maxResponse ] ;
      FReal beta1F[   k_maxResponse ] ;
      FReal beta2F[ k_maxResponse ] ;
      FInteger nResponse ( 0 ) ;                     // actual number sent

      // S. Nam : revceive muon hit list from Geant by mc_mu_response_
      //        : cellIdF is multiplet id 
      //        : a track leaves one hit per layer
      
      mc_mu_responses_( k_maxResponse ,
			nResponse     ,
			cellIdF       ,
			particleIdF   ,
			x01F        ,
			x02F      ,
			beta1F     ,
			beta2F    ) ;
      
      // S. Nam : old arguments. commenting out 
      /*
	ctrIdF        ,
	stripIdF      ,
	ctrAngleF     ,
	stripAngleF    ) ;
      */
      
      if( k_maxResponse < nResponse )
      {
	 report( EMERGENCY, kReport ) << "Responses exceeds max!" << endl ;
	 assert( false ) ;
	 ::exit( 1 ) ;
      }
      
      report ( DEBUG, kReport) << "swn: MCMUreponseprod: # of muon hits returned is" 
			       << nResponse << endl;
      
      for ( FInteger iResponse ( 0 ) ; iResponse < nResponse ; ++iResponse )
      {
	 if (cellIdF[     iResponse ] < 576 && cellIdF[     iResponse ] >0) {

	    // 
            /* S. Nam ; original one
	    addResponse( cellIdF[     iResponse ] ,
      		         particleIdF[ iResponse ] ,
      		         ctrIdF[      iResponse ] ,
      		         stripIdF[    iResponse ] ,
      		         ctrAngleF[   iResponse ] ,
      		         stripAngleF[ iResponse ]  ) ;
            */

	    report(DEBUG, kReport) << "output from mc_mu.. " 
				       << x01F[iResponse] << " " << x02F[iResponse] << " " 
				       << beta1F[iResponse] << " " << beta2F[iResponse] << endl;
	    
            // S. Nam : with new arguments 
            addResponse( cellIdF[     iResponse ] ,
      		         particleIdF[ iResponse ] ,
      		         x01F[        iResponse ] ,
      		         x02F[        iResponse ] ,
      		         beta1F[      iResponse ] ,
      		         beta2F[      iResponse ] ) ;
	 } else {
	    report ( ERROR, kReport) << "cellid is wrong " 
					 << cellIdF[     iResponse ]  << endl;
	    
	 }
      }

     // step N: we no longer need the Frame
     FortranInterfacer::instance().releaseFrame();
   }

   return m_ptrTable ;
}


// S. Nam : no change made. This function never called at all.
extern "C"
void mc_mu_add_response_( const FInteger& aCellId     ,
			  const FInteger& aParticleId ,
			  const FInteger& aCtrId      ,
			  const FInteger& aStripId    ,
			  const FReal&    aCtrAngle   ,
			  const FReal&    aStripAngle  )
{
   MCMUResponseProxy* who ( MCMUResponseProxy::whoAmI() ) ;
   if( 0 == who ) 
   {
      report( EMERGENCY, kReport ) << "Null whoAmI ptr, exiting!" << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }
   who->addResponse( aCellId      , 
		     aParticleId  , 
		     aCtrId       ,
		     aStripId     ,
		     aCtrAngle    ,
		     aStripAngle   ) ;
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
void MCMUResponseProxy::updateBeginRun( const Record& iRecord )
{
   // Make sure Cleog begin run data is valid.
   // This bindable proxy is tied to the beginRun stream.
   // m_producer points to MCResponseProd producer which has the function
   // updateCleogBeginRun which checks if begin run is valid
   // TODO: 4/11/99 - Temp fix of (Frame&) (CHANGE WHEN CURRENT UPDATED))
   m_producer->updateCleogBeginRun( (Frame&) iRecord.frame() );
}


//-----------------------------------------------
// Bindable proxy - method to bind to other streams
PROXY_BIND_METHOD( MCMUResponseProxy )
//-----------------------------------------------









