// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCDRResponseProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCDRResponseProxy.cc,v 1.13 2001/04/09 14:24:07 mahlke Exp $
//
// Revision history
//
// $Log: MCDRResponseProxy.cc,v $
// Revision 1.13  2001/04/09 14:24:07  mahlke
// introduce flag to switch off geometry or responses for single subdetectors
//
// Revision 1.12  2000/08/11 20:05:29  dubrovin
// Change DR3 hits arrays dimension k_maxResponce from 2500 to 5000
//
// Revision 1.11  2000/07/07 02:22:15  lkg
// Handle addition of x,y positions to MCDRResponse
//
// Revision 1.10  2000/04/17 20:12:02  bkh
// Elim checks of ptr after new
//
// Revision 1.9  2000/02/15 00:50:54  jjo
// Comment out the code that fills responses 'on the fly' as we don't use it now
//
// Revision 1.8  1999/12/09 22:49:32  jjo
// Call addResponse from faultHandler - previously only for DEBUG_RESPONSE
//
// Revision 1.7  1999/11/18 19:50:53  jjo
// only dump responses if CPP flag  DEBUG_RESPONSE is set
//
// Revision 1.6  1999/10/27 22:59:40  jjo
// Added HitIsEff which was added to DR response object
//
// Revision 1.5  1999/10/24 20:52:33  cdj
// removed inappropriate use of typename
//
// Revision 1.4  1999/10/19 16:19:11  jjo
// Remove Frame cast that isn't needed anymore and mostly
// cosmetic changes.
//
// Revision 1.3  1999/10/13 17:03:17  jjo
// Update because DR Responses now include charge deposited
//
// Revision 1.2  1999/06/10 20:07:30  bkh
// fix argument ordering problem in add_response usage
//
// Revision 1.1.1.1  1999/04/16 20:07:32  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/25 21:30:54  bkh
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

#include "MCResponseProd/MCDRResponseProxy.h"


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
static const char* const kReport = "MCResponseProd.MCDRResponseProxy";

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCDRResponseProxy.cc,v 1.13 2001/04/09 14:24:07 mahlke Exp $";
static const char* const kTagString = "$Name: v05_03_01 $";

//
// static data member definitions
//

MCDRResponseProxy* MCDRResponseProxy::k_whoAmI ( 0 );

//
// constructors and destructor
//

MCDRResponseProxy::MCDRResponseProxy( MCResponseProd& iProducer )
   : m_ptrTable ( new value_type ) ,
     m_howMany  ( 0 ) ,
     m_producer( &iProducer )   
{
   // bind `auxilliary' functions that you want called when a new record
   // on the particular stream appears
   bind( &MCDRResponseProxy::updateBeginRun, Stream::kBeginRun );
}

// MCDRResponseProxy::MCDRResponseProxy( const MCDRResponseProxy& iproxy )
// {
//   *this = iproxy;
// }

MCDRResponseProxy::~MCDRResponseProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable;
}

//
// assignment operators
//
// const MCDRResponseProxy& MCDRResponseProxy::operator=( const MCDRResponseProxy& iproxy )
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

void MCDRResponseProxy::invalidateCache()
{
   // Tell the producer that we need to trigger geant for the next event
   m_producer->invalidateGeantEvent();

   // erase ptr table of MC Response objects
   if ( 0 != m_ptrTable ) 
   {
      (*m_ptrTable).eraseAll();
   }
   m_howMany = 0;
}

MCDRResponseProxy* MCDRResponseProxy::whoAmI()
{
   return k_whoAmI;
}

void MCDRResponseProxy::addResponse( const FInteger aCellId,
				     const FInteger aParticleId,
				     const FReal    aDriftDist,
				     const FReal    aDriftTime,
				     const FReal    aSinLyrAngle,
				     const FReal    aDipAngle,
				     const FReal    aPathLength,
				     const FInteger aAmbiguity,
				     const FReal    aXPosition,
				     const FReal    aYPosition,
				     const FReal    aZPosition,
				     const FReal    aChargeDep,
				     const FReal    aEnergyLoss,
				     const FLogical ahitIsEff   ) 
{
   // just to be extra careful about conversions from fortran types
   const MCDRResponse::Identifier    identifier  ( ++m_howMany );
   const MCDRResponse::PartIdType    particleId  ( aParticleId );
   const MCDRResponse::CellIdType    cellId      ( aCellId );
   const MCDRResponse::DistType      driftDist   ( aDriftDist );
   const MCDRResponse::TimeType      driftTime   ( aDriftTime );
   const MCDRResponse::LyrAngleType  sinLyrAngle ( aSinLyrAngle );
   const MCDRResponse::DipAngleType  dipAngle    ( aDipAngle );
   const MCDRResponse::PathType      pathLength  ( aPathLength );
   const MCDRResponse::AmbigType     ambiguity   ( aAmbiguity );
   const MCDRResponse::PosType       xPosition   ( aXPosition );
   const MCDRResponse::PosType       yPosition   ( aYPosition );
   const MCDRResponse::PosType       zPosition   ( aZPosition );
   const MCDRResponse::ChargeDepType chargeDep   ( aChargeDep );
   const MCDRResponse::ELossType     energyLoss  ( aEnergyLoss );
   const MCDRResponse::HitIsEffType  hitIsEff    ( ahitIsEff );

   MCDRResponse* tmp ( new MCDRResponse( identifier,
					 particleId,
					 cellId,
					 driftDist,
					 driftTime,
					 sinLyrAngle,
					 dipAngle,
					 pathLength,
					 ambiguity,
					 xPosition,
					 yPosition,
					 zPosition,
					 chargeDep,
					 energyLoss,
					 hitIsEff )      );

   if ( 0 == tmp ) 
   {
      report( EMERGENCY, kReport ) << "No memory!" << endl;
      assert( false );
      ::exit( 1 );
   }

   (*m_ptrTable).insert( tmp );
}


// Header for Fortran subroutine called by faultHandler to fill MC Responses.
// Two ways to fill Responses: on-the-fly or bulk-insertion.
// On-the-fly: fills each Response individually
// Bulk-insertion: pass array with all Responses at once.
// Use fortran_types.h type definitions for cross-platform compatibility

// bulk-insertion of MC responses 
extern "C" void
mc_dr_responses_( const FInteger& MaxResponse,
		  FInteger&       NResponse,
		  FInteger        cellId[],
		  FInteger        particleId[],
		  FInteger        ambiguity[],
		  FReal           driftDist[],
		  FReal           driftTime[],
		  FReal           sinLyrAngle[],
		  FReal           dipAngle[],
		  FReal           pathLength[],
		  FReal           xPosition[],
		  FReal           yPosition[],
		  FReal           zPosition[],
		  FReal           chargeDep[],
		  FReal           energyLoss[],
		  FLogical        hitIsEff[] );


const MCDRResponseProxy::value_type*
MCDRResponseProxy::faultHandler( const Record&  iRecord,
				 const DataKey& iKey )
{
   // Phase 1 - run (trigger) Geant for this event.
   // m_producer points to this producer (MCResponseProd) and call the 
   // function triggerGeantEvent() which will trigger Geant for this 
   // event if it hasn't been done yet.
   m_producer->triggerGeantEvent( iRecord.frame() );


   // Phase 2 - creation of MC Response objects
   // Initialize - require ptr table of MC Responses to be empty & initialize m_howMany
   assert( 0 == (*m_ptrTable).size() ); 
   m_howMany = 0; 

   // check whether DRResponses are wanted at all
   report ( DEBUG, kReport) << "DR Responses wanted: "
                 << m_producer->m_getDRResponses.value() << endl;
   // if not, skip filling responses into m_ptrTable 
  
   if (m_producer -> m_getDRResponses.value() != 0) {

     // Fill MC Responses objects using bulk-insertion method
     // variables for bulk-insertion of MC responses
     // particleIdF is decay tree identifier for geant track # that caused  hit

     // D.M. 08/11/00 changed k_maxResponse=2500 to 5000
     // If one needs to change this parameter, one have to care about
     // kMaxHitTotal in geant_dr_hit_def.inc in order to keep compatible
     // arrays dimernsion between F77 and C++

     static const FInteger  k_maxResponse ( 5000 ); // max # hits
     FInteger nResponse ( 0 );                      // number of responses returned from Fortran
     FInteger cellIdF[k_maxResponse];             
     FInteger particleIdF[k_maxResponse];        
     FInteger ambiguityF[k_maxResponse];
     FReal driftDistF[k_maxResponse];
     FReal driftTimeF[k_maxResponse];
     FReal sinLyrAngleF[k_maxResponse];
     FReal dipAngleF[k_maxResponse];
     FReal pathLengthF[k_maxResponse];
     FReal xPositionF[k_maxResponse];
     FReal yPositionF[k_maxResponse];
     FReal zPositionF[k_maxResponse];
     FReal chargeDepF[k_maxResponse];
     FReal energyLossF[k_maxResponse];
     FLogical hitIsEffF[k_maxResponse];
   
     mc_dr_responses_( k_maxResponse,
	     	       nResponse,
		       cellIdF,
		       particleIdF,
		       ambiguityF,
		       driftDistF,
		       driftTimeF,
		       sinLyrAngleF,
		       dipAngleF,
		       pathLengthF,
		       xPositionF,
		       yPositionF,
		       zPositionF,
		       chargeDepF,
		       energyLossF,
		       hitIsEffF );

     if( k_maxResponse < nResponse )
     {
        report( EMERGENCY, kReport ) << "Responses exceeds max!" << endl;
        assert( k_maxResponse > nResponse );
        ::exit( 1 );
     }
     report( DEBUG, kReport ) << "Number of DR Responses =" << nResponse << endl;

     for ( FInteger iResponse ( 0 ); iResponse < nResponse; ++iResponse )
     {

      
#if defined(DEBUG_RESPONSE)
        report( DEBUG, kReport )
	   << "iResponse ="     <<  iResponse 
	   << "\t cellId="      << cellIdF[iResponse] << endl
	   << "particleId="     << particleIdF[iResponse] 
	   << "\t ambiguity="   << ambiguityF[iResponse] << endl 
	   << "driftDist="      << driftDistF[iResponse]
	   << "\t driftTime="   << driftTimeF[iResponse]  << endl
	   << "sinLyrAngle="    << sinLyrAngleF[iResponse] 
	   << "\t dipAngle="    << dipAngleF[iResponse] << endl 
	   << "pathLength="     << pathLengthF[iResponse] 
	   << "\t xPosition="   << xPositionF[iResponse] << endl
	   << "yPosition="      << yPositionF[iResponse] << endl
	   << "\t zPosition="   << zPositionF[iResponse] << endl
	   << "chargeDep="      << chargeDepF[iResponse] 
	   << "\t energyLoss="  << energyLossF[iResponse] 
	   << "\t IsEff="       << hitIsEffF[iResponse] << endl;
#endif   
      
        addResponse( cellIdF[iResponse],
	  	     particleIdF[iResponse],
		     driftDistF[iResponse],
		     driftTimeF[iResponse],
		     sinLyrAngleF[iResponse],
		     dipAngleF[iResponse],
		     pathLengthF[iResponse],
		     ambiguityF[iResponse],
		     xPositionF[iResponse],
		     yPositionF[iResponse],
		     zPositionF[iResponse],
		     chargeDepF[iResponse],
		     energyLossF[iResponse],
      		     hitIsEffF[iResponse] );
     }

   }

   return m_ptrTable;
}

// This function would be used to fill responses from Fortran
// 'on the fly' (called for each response instead of the bulk-insertion method)
// We use the bulk-insertion function - mc_dr_responses_ instead of this function.
// extern "C"
// void mc_dr_add_response_( const FInteger& aCellId,
// 			  const FInteger& aParticleId,
// 			  const FReal&    aDriftDist,
// 			  const FReal&    aDriftTime,
// 			  const FReal&    aSinLyrAngle,
// 			  const FReal&    aDipAngle,
// 			  const FReal&    aPathLength,
// 			  const FInteger& aAmbiguity,
// 			  const FReal&    aXPosition,
// 			  const FReal&    aYPosition,
// 			  const FReal&    aZPosition,
// 			  const FReal&    aChargeDep,
// 			  const FReal&    aEnergyLoss,
// 			  const FLogical& ahitIsEff )
// {
//    MCDRResponseProxy* who ( MCDRResponseProxy::whoAmI() );
//    if( 0 == who ) 
//    {
//       report( EMERGENCY, kReport ) << "Null whoAmI ptr, exiting!" << endl;
//       assert( false );
//       ::exit( 1 );
//    }
//    who->addResponse( aCellId, 
// 		     aParticleId, 
// 		     aDriftDist,
// 		     aDriftTime,
// 		     aSinLyrAngle,
// 		     aDipAngle,
// 		     aPathLength,
// 		     aAmbiguity,
// 		     aXPosition,
// 		     aYPosition,
// 		     aZPosition,
// 		     aChargeDep,
// 		     aEnergyLoss,
// 		     ahitIsEff );
// }

//
// const member functions
//

//
// static member functions
//


//
// 'bound' functions
//
void MCDRResponseProxy::updateBeginRun( const Record& iRecord )
{
   // Make sure Cleog begin run data is valid.
   // This bindable proxy is tied to the beginRun stream.
   // m_producer points to MCResponseProd producer which has the function
   // updateCleogBeginRun which checks if begin run is valid
   m_producer->updateCleogBeginRun( iRecord.frame() );
}


//-----------------------------------------------
// Bindable proxy - method to bind to other streams
PROXY_BIND_METHOD( MCDRResponseProxy )
//-----------------------------------------------
