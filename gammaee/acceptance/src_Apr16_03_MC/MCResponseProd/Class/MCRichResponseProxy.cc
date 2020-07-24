// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCRichResponseProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCRichResponseProxy.cc,v 1.6 2001/04/09 14:24:08 mahlke Exp $
//
// Revision history
//
// $Log: MCRichResponseProxy.cc,v $
// Revision 1.6  2001/04/09 14:24:08  mahlke
// introduce flag to switch off geometry or responses for single subdetectors
//
// Revision 1.5  2000/04/17 20:12:02  bkh
// Elim checks of ptr after new
//
// Revision 1.4  1999/10/24 20:52:34  cdj
// removed inappropriate use of typename
//
// Revision 1.3  1999/07/08 06:07:47  ts
// first actual implementation of Rich Response
//
// Revision 1.2  1999/06/10 20:07:34  bkh
// fix argument ordering problem in add_response usage
//
// Revision 1.1.1.1  1999/04/16 20:07:32  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/25 21:30:59  bkh
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

#include "MCResponseProd/MCRichResponseProxy.h"


// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kReport = "MCResponse.MCRichResponseProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCRichResponseProxy.cc,v 1.6 2001/04/09 14:24:08 mahlke Exp $";
static const char* const kTagString = "$Name: v06_02_05 $";

//
// static data member definitions
//

MCRichResponseProxy* MCRichResponseProxy::k_whoAmI ( 0 ) ;

//
// constructors and destructor
//

MCRichResponseProxy::MCRichResponseProxy( MCResponseProd& iProducer )
   : m_ptrTable ( new value_type ) ,
     m_howMany  ( 0 ) ,
     m_producer( &iProducer )     
{
   // bind `auxilliary' functions that you want called when a new record
   // on the particular stream appears
   bind( &MCRichResponseProxy::updateBeginRun, Stream::kBeginRun );
}

// MCRichResponseProxy::MCRichResponseProxy( const MCRichResponseProxy& iproxy )
// {
//   *this = iproxy;
// }

MCRichResponseProxy::~MCRichResponseProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const MCRichResponseProxy& MCRichResponseProxy::operator=( const MCRichResponseProxy& iproxy )
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

void MCRichResponseProxy::invalidateCache()
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

MCRichResponseProxy* MCRichResponseProxy::whoAmI()
{
   return k_whoAmI ;
}

void MCRichResponseProxy::addResponse( const FInteger aCellId     ,
				       const FInteger aParticleId ,
                                       const FReal    aX,
                                       const FReal    aY,
                                       const FReal    aZ,
                                       const FReal    aPhotonEnergy,
                                       const FInteger aOrigin,
                                       const FInteger aNumberOfSurfacesPassed,
                                       const FReal    aMass,
                                       const FReal    aMomentum)
{
   // just to be extra careful about conversions from fortran types
   const  MCRichResponse::Identifier               identifier ( ++m_howMany ) ;
   const  MCRichResponse::PartIdType               particleId ( aParticleId ) ;
   const  MCRichResponse::CellIdType               cellId     ( aCellId     ) ;
   const  MCRichResponse::PositionType             x          ( aX );
   const  MCRichResponse::PositionType             y          ( aY );
   const  MCRichResponse::PositionType             z          ( aZ );
   const  MCRichResponse::CherenkovPhotonEnergyType 
      photonEnergy( aPhotonEnergy );
   const  MCRichResponse::PhotoElectronOriginType  origin  ( aOrigin );
   const  MCRichResponse::NumberOfSurfacesPassedType 
      numberOfSurfacesPassed( aNumberOfSurfacesPassed );
   const  MCRichResponse::MassOfParticleType       mass    ( aMass );
   const  MCRichResponse::MomentumOfParticleType   momentum( aMomentum );


   MCRichResponse* tmp( new MCRichResponse( identifier ,
					    particleId ,
					    cellId     ,
                                            x,
                                            y,
                                            z,
                                            photonEnergy,
                                            origin,
                                            numberOfSurfacesPassed,
                                            mass,
					    momentum       ) ) ;

   (*m_ptrTable).insert( tmp ) ;
}


// Header for Fortran subroutine called by faultHandler to fill MC Responses.
// Two ways to fill Responses: on-the-fly or bulk-insertion.
// On-the-fly: fills each Response individually
// Bulk-insertion: pass array with all Responses at once.
// Use fortran_types.h type definitions for cross-platform compatibility
//
// No arguments for on-the-fly method of filling MC responses
extern "C" void mc_rich_responses_();

// uncomment for bulk-insertion of MC responses
// extern "C" void mc_rich_responses_(
//    const FInteger& aMaxResponse  ,
//    FInteger&       aNResponse    ,
//    FInteger        aCellId[]     ,
//    FInteger        aParticleId[] ,
//    FReal           aCharge[]      
//    ) ;


const MCRichResponseProxy::value_type*
MCRichResponseProxy::faultHandler( const Record&  iRecord,
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

   // check whether RichResponses are wanted at all
   report ( DEBUG, kReport) << "Rich Responses wanted: "
                 << m_producer->m_getRichResponses.value() << endl;
   // if not, skip filling responses into m_ptrTable 
  
   if (m_producer -> m_getRichResponses.value() != 0) {
   
     // Fill MC Responses objects (use either on-the-fly or bulk-insertion method)
     // on-the-fly method to add MC Responses to table
     //   set static pointer k_whoAmI so global fcn knows who I am
     //   call Fortran mc_xx_add_response_ for each response
     report( DEBUG, kReport ) << "Calling mc_rich_responses_" << endl;
     k_whoAmI = this ; 
     mc_rich_responses_() ; 

   // Uncomment for bulk-insertion of MC responses 
   //   static const FInteger k_maxResponse ( 1500 ) ; // max # hits to be processed
   //   FInteger cellIdF[     k_maxResponse ] ;        // cellId's
   //   FInteger particleIdF[ k_maxResponse ] ;        // particleId's
   //   FReal    chargeF[     k_maxResponse ] ;        // charges
   //   FInteger nResponse ( 0 ) ;                     // actual number sent
   //   mc_rich_responses_( k_maxResponse ,
   //		       nResponse     ,
   //		       cellIdF       ,
   //		       particleIdF   ,
   //		       chargeF        ) ;
   //
   //   if( k_maxResponse < nResponse )
   //   {
   //      report( EMERGENCY, kReport ) << "Responses exceeds max!" << endl ;
   //      assert( false ) ;
   //      ::exit( 1 ) ;
   //   }
   //
   //   for ( FInteger iResponse ( 0 ) ; iResponse < nResponse ; ++iResponse )
   //   {
   //      addResponse( cellIdF[     iResponse ] ,
   //		        particleIdF[ iResponse ] ,
   //		        chargeF[     iResponse ] ) ;
   //   }

   } 

   report( DEBUG, kReport ) << "Number of RICH Responses =" << (*m_ptrTable).size() << endl;
   
   return m_ptrTable ;
}

extern "C"
void mc_rich_add_response_( const FInteger& aCellId     ,
			    const FInteger& aParticleId ,
                            const FReal&    aX,
                            const FReal&    aY,
                            const FReal&    aZ,
                            const FReal&    aPhotonEnergy,
                            const FInteger& aOrigin,
                            const FInteger& aNumberOfSurfacesPassed,
                            const FReal&    aMass,
                            const FReal&    aMomentum)
{
   MCRichResponseProxy* who ( MCRichResponseProxy::whoAmI() ) ;
   if( 0 == who ) 
   {
      report( EMERGENCY, kReport ) << "Null whoAmI ptr, exiting!" << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }
   who->addResponse( aCellId     , 
		     aParticleId ,
                     aX,
                     aY,
                     aZ,
                     aPhotonEnergy,
                     aOrigin,
                     aNumberOfSurfacesPassed,
                     aMass,
	             aMomentum     ) ;
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
void MCRichResponseProxy::updateBeginRun( const Record& iRecord )
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
PROXY_BIND_METHOD( MCRichResponseProxy )
//-----------------------------------------------
