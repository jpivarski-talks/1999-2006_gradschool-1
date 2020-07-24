// -*- C++ -*-
//
// Package:     MCResponseProd
// Module:      MCCCResponseProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCCCResponseProxy.cc,v 1.7 2001/04/09 14:24:07 mahlke Exp $
//
// Revision history
//
// $Log: MCCCResponseProxy.cc,v $
// Revision 1.7  2001/04/09 14:24:07  mahlke
// introduce flag to switch off geometry or responses for single subdetectors
//
// Revision 1.6  2000/04/17 20:12:01  bkh
// Elim checks of ptr after new
//
// Revision 1.5  2000/03/24 23:14:25  bkh
// Get CC constants for use of gradients
//
// Revision 1.4  1999/10/24 20:52:32  cdj
// removed inappropriate use of typename
//
// Revision 1.3  1999/06/10 20:07:27  bkh
// fix argument ordering problem in add_response usage
//
// Revision 1.2  1999/05/14 17:16:02  bkh
// Changes to make CC Responses work
//
// Revision 1.1.1.1  1999/04/16 20:07:32  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/25 21:30:52  bkh
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
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAPtrTable.h"

// needed for PROXY_BIND_METHOD
#include "ProxyBind/ProxyBoundMethodAction.h" 

// Producer that calls this proxy
#include "MCResponseProd/MCResponseProd.h"

#include "MCResponseProd/MCCCResponseProxy.h"

#include "C3cc/CcStream.h"

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
static const char* const kReport = "MCResponseProd.MCCCResponseProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCCCResponseProxy.cc,v 1.7 2001/04/09 14:24:07 mahlke Exp $";
static const char* const kTagString = "$Name: v05_03_01 $";

//
// static data member definitions
//

MCCCResponseProxy* MCCCResponseProxy::k_whoAmI ( 0 ) ;

//
// constructors and destructor
//

MCCCResponseProxy::MCCCResponseProxy( MCResponseProd& iProducer )
   : m_ptrTable ( new value_type ) ,
     m_howMany  ( 0 ) ,
     m_producer( &iProducer )
{
   // bind `auxilliary' functions that you want called when a new record
   // on the particular stream appears
   bind( &MCCCResponseProxy::updateBeginRun, Stream::kBeginRun );

   k_whoAmI = this ;
}

// MCCCResponseProxy::MCCCResponseProxy( const MCCCResponseProxy& iproxy )
// {
//   *this = iproxy;
// }

MCCCResponseProxy::~MCCCResponseProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const MCCCResponseProxy& MCCCResponseProxy::operator=( const MCCCResponseProxy& iproxy )
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

void MCCCResponseProxy::invalidateCache()
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

MCCCResponseProxy* MCCCResponseProxy::whoAmI()
{
   if( 0 == k_whoAmI )
   {
      report( EMERGENCY, kReport ) << "Zero pointer in whoAmI!" << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }
   return k_whoAmI ;
}

void MCCCResponseProxy::addResponse( const FInteger aCellId     ,
				     const FInteger aParticleId ,
				     const FReal    aEnergy       ) 
{
   // just to be extra careful about conversions from fortran types
   const MCCCResponse::Identifier identifier ( ++m_howMany ) ;
   const MCCCResponse::CellIdType cellId     ( aCellId     ) ;
   const MCCCResponse::PartIdType particleId ( aParticleId ) ;
   const MCCCResponse::EnergyType energy     ( aEnergy     ) ;

   MCCCResponse* tmp( new MCCCResponse( identifier ,
					particleId ,
					cellId     ,
					energy       ) ) ;

   (*m_ptrTable).insert( tmp ) ;
}

// Header for Fortran subroutine called by faultHandler to fill MC Responses.
// Two ways to fill Responses: on-the-fly or bulk-insertion.
// On-the-fly: fills each Response individually
// Bulk-insertion: pass array with all Responses at once.
// Use fortran_types.h type definitions for cross-platform compatibility
//
// No arguments for on-the-fly method of filling MC responses
// extern "C" void mc_cc_responses_();

// bulk-insertion of MC responses
extern "C" 
void mc_cc_responses_( const FInteger& aMaxResponse  ,
		       FInteger&       aNResponse    ,
		       FInteger        aCellId[]     ,
		       FInteger        aParticleId[] ,
		       FReal           aEnergy[]       ) ;

const MCCCResponseProxy::value_type*
MCCCResponseProxy::faultHandler( const Record&  iRecord ,
				 const DataKey& iKey     )
{
   // Phase 1 - run Geant
   // Trigger Geant for this event.
   // m_producer points to the producer that provides this proxy (MCResponseProd)
   // and call the function triggerGeantEvent to trigger Geant if it hasn't been
   // done for this event.
   report( DEBUG, kReport ) << "Calling triggerGeantEvent" << endl;
   m_producer->triggerGeantEvent( iRecord.frame() );

   // Phase 2 - creation of MC Response objects
   // Initialize - require ptr table of MC Responses to be empty
   //              & initialize m_howMany
   assert( 0 == (*m_ptrTable).size() ); 
   m_howMany = 0 ;


   // check whether CCResponses are wanted at all
   report ( DEBUG, kReport) << "CC Responses wanted: "
                 << m_producer->m_getCCResponses.value() << endl;
   // if not, skip filling responses into m_ptrTable 
  
   if (m_producer -> m_getCCResponses.value() != 0) {

     // Fill MC Responses objects 
     //   (use either on-the-fly or bulk-insertion method)

     // on-the-fly method to add MC Responses to table
     //   set static pointer k_whoAmI so global fcn knows who I am
     //   call Fortran mc_xx_add_response_ for each response
     report( DEBUG, kReport ) << "Calling mc_cc_responses_" << endl;
     //k_whoAmI = this ; 
     //mc_cc_responses_() ; 


     // bulk-insertion of MC responses 
     static const FInteger k_maxResponse ( 1500 ) ; // max # hits to be processed
     FInteger cellIdF[     k_maxResponse ] ;        // cellId's
     FInteger particleIdF[ k_maxResponse ] ;        // particleId's
     FReal    energyF[     k_maxResponse ] ;        // energies
     FInteger nResponse ( 0 ) ;                     // actual number sent
     mc_cc_responses_( k_maxResponse ,
	               nResponse     ,
		       cellIdF       ,
		       particleIdF   ,
		       energyF        ) ;

     if( k_maxResponse < nResponse )
     {
        report( EMERGENCY, kReport ) << "Responses exceeds max!" << endl ;
        assert( false ) ;
        ::exit( 1 ) ;
     }
     else
     {
        report( DEBUG, kReport ) << " # of CC Responses = " 
	                         << nResponse << endl ;
     }

     for ( FInteger iResponse ( 0 ) ; iResponse < nResponse ; ++iResponse )
     {
        addResponse( cellIdF[     iResponse ] ,
	  	     particleIdF[ iResponse ] ,
		     energyF[     iResponse ] ) ;
     }

   } 

   return m_ptrTable ;
}

extern "C"
void
mc_cc_add_response_( const FInteger& aCellId     ,
		     const FInteger& aParticleId ,
		     const FReal&    aEnergy       ) 
{
   MCCCResponseProxy::whoAmI()->addResponse( aCellId     , 
					     aParticleId ,
					     aEnergy      ) ;
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

void 
MCCCResponseProxy::updateBeginRun( const Record& iRecord )
{
   // Make sure Cleog begin run data is valid.
   // This bindable proxy is tied to the beginRun stream.
   // m_producer points to MCResponseProd producer which has the function
   // updateCleogBeginRun which checks if begin run is valid

   m_producer->updateCleogBeginRun(  iRecord.frame() );
}

void 
MCCCResponseProxy::beginRunProcessing( Frame& aFrame ) 
{
   extract( aFrame.record( Stream::kBaseGeometry ) , m_DGIdToCellIds );
   extract( aFrame.record( CcStream::kMCCrystal  ) , m_mcCrystals    ) ;
}


extern "C"
void
cc_get_gradients_( FReal           aGrad[] ,
		   const FInteger& aNGrad  ) 
{
   MCCCResponseProxy::whoAmI()->fillGradients( aGrad, aNGrad ) ;
}

extern "C"
void
cc_dgid_to_cellid_( const FInteger aDGId[] ,
		    FInteger&      aCellId   )
{
   const CcDGId dgId ( aDGId[0],  aDGId[1],  aDGId[2] ) ;
   MCCCResponseProxy::whoAmI()->accessGeantMap( dgId, aCellId ) ;
}

void
MCCCResponseProxy::fillGradients( FReal           aGrad[] ,
				  const FInteger& aNGrad    ) const
{
   if( !m_mcCrystals.valid() )
   {
      report( EMERGENCY, kReport ) << "No valid CCMCCrystals constants!" 
				   << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }

   if( aNGrad < m_mcCrystals.size() )
   {
      report( EMERGENCY, kReport ) << "Size provided for gradients = "
				   << aNGrad << " is not big enough ="
				   << m_mcCrystals.size() << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }

   UInt32 index ( 0 ) ;
   for( FAConstants< DBCCMCCrystal >::const_iterator iMC 
	   ( m_mcCrystals.begin() ) ; iMC != m_mcCrystals.end() ; ++iMC )
   {
      aGrad[ index++ ] = (*iMC).get_Gradient() ;
   }
}

void
MCCCResponseProxy::accessGeantMap( const CcDGId& aDGId ,
				   FInteger&     aCellId    ) const
{
   if( !m_DGIdToCellIds.valid() )
   {
      report( EMERGENCY, kReport ) << "No valid DGId to CellId mapping!" 
				   << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }

   FATable< CcDGIdToCellId >::const_iterator found
      ( m_DGIdToCellIds.find( aDGId ) ) ;

   if( found == m_DGIdToCellIds.end() )
   {
      report( EMERGENCY, kReport ) << "CcDGId = " << aDGId 
				   << " not found in mapping!" << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }
   else
   {
      aCellId = (*found).cellId() ;
   }
}


//-----------------------------------------------
// Bindable proxy - method to bind to other streams
PROXY_BIND_METHOD( MCCCResponseProxy )
//-----------------------------------------------
