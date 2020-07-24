// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCZDResponseProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCZDResponseProxy.cc,v 1.3 2003/04/15 22:03:59 bkh Exp $
//
// Revision history
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

#include "MCResponseProd/MCZDResponseProxy.h"


#include "DetectorConfiguration/DetectorConfiguration.h"
#include "DAException/DANoDataException.h"

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
static const char* const kReport = "MCResponseProd.MCZDResponseProxy";

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCZDResponseProxy.cc,v 1.3 2003/04/15 22:03:59 bkh Exp $";
static const char* const kTagString = "$Name: v06_02_06 $";

//
// static data member definitions
//

MCZDResponseProxy* MCZDResponseProxy::k_whoAmI ( 0 );

//
// constructors and destructor
//

MCZDResponseProxy::MCZDResponseProxy( MCResponseProd& iProducer )
   : m_ptrTable ( new value_type ) ,
     m_howMany  ( 0 ) ,
     m_producer( &iProducer )   
{
   // bind `auxilliary' functions that you want called when a new record
   // on the particular stream appears
   bind( &MCZDResponseProxy::updateBeginRun, Stream::kBeginRun );
}

// MCZDResponseProxy::MCZDResponseProxy( const MCZDResponseProxy& iproxy )
// {
//   *this = iproxy;
// }

MCZDResponseProxy::~MCZDResponseProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable;
}

//
// assignment operators
//
// const MCZDResponseProxy& MCZDResponseProxy::operator=( const MCZDResponseProxy& iproxy )
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

void MCZDResponseProxy::invalidateCache()
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

MCZDResponseProxy* MCZDResponseProxy::whoAmI()
{
   return k_whoAmI;
}

void MCZDResponseProxy::addResponse( const FInteger aCellId,
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
   const MCZDResponse::Identifier    identifier  ( ++m_howMany );
   const MCZDResponse::PartIdType    particleId  ( aParticleId );
   const MCZDResponse::CellIdType    cellId      ( aCellId );
   const MCZDResponse::DistType      driftDist   ( aDriftDist );
   const MCZDResponse::TimeType      driftTime   ( aDriftTime );
   const MCZDResponse::LyrAngleType  sinLyrAngle ( aSinLyrAngle );
   const MCZDResponse::DipAngleType  dipAngle    ( aDipAngle );
   const MCZDResponse::PathType      pathLength  ( aPathLength );
   const MCZDResponse::AmbigType     ambiguity   ( aAmbiguity );
   const MCZDResponse::PosType       xPosition   ( aXPosition );
   const MCZDResponse::PosType       yPosition   ( aYPosition );
   const MCZDResponse::PosType       zPosition   ( aZPosition );
   const MCZDResponse::ChargeDepType chargeDep   ( aChargeDep );
   const MCZDResponse::ELossType     energyLoss  ( aEnergyLoss );
   const MCZDResponse::HitIsEffType  hitIsEff    ( ahitIsEff );

   MCZDResponse* tmp ( new MCZDResponse( identifier,
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
mc_zd_responses_( const FInteger& MaxResponse,
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


const MCZDResponseProxy::value_type*
MCZDResponseProxy::faultHandler( const Record&  iRecord,
				 const DataKey& iKey )
{
   FAItem<DetectorConfiguration>                              iConfig   ;
   extract( iRecord.frame().record( Stream::kBaseGeometry ) , iConfig ) ;
   if( iConfig->useSInotZD() )
   {
      throw DANoDataException< value_type >( iRecord.stream(),iKey ) ;
   }
   // Phase 1 - run (trigger) Geant for this event.
   // m_producer points to this producer (MCResponseProd) and call the 
   // function triggerGeantEvent() which will trigger Geant for this 
   // event if it hasn't been done yet.
   m_producer->triggerGeantEvent( iRecord.frame() );


   // Phase 2 - creation of MC Response objects
   // Initialize - require ptr table of MC Responses to be empty & initialize m_howMany
   assert( 0 == (*m_ptrTable).size() ); 
   m_howMany = 0; 

   // check whether ZDResponses are wanted at all
   report ( DEBUG, kReport) << "ZD Responses wanted: "
                 << m_producer->m_getZDResponses.value() << endl;
   // if not, skip filling responses into m_ptrTable 
  
   if (m_producer -> m_getZDResponses.value() != 0) {

     // Fill MC Responses objects using bulk-insertion method
     // variables for bulk-insertion of MC responses
     // particleIdF is decay tree identifier for geant track # that caused  hit

     // D.M. 08/11/00 changed k_maxResponse=2500 to 5000
     // If one needs to change this parameter, one have to care about
     // kMaxHitTotal in geant_zd_hit_def.inc in order to keep compatible
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
   
     mc_zd_responses_( k_maxResponse,
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
     report( DEBUG, kReport ) << "Number of ZD Responses =" << nResponse << endl;

     for ( FInteger iResponse ( 0 ); iResponse < nResponse; ++iResponse )
     {

      
//#if defined(DEBUG_RESPONSE)
        report( INFO, kReport )
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
//#endif   
      
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
// We use the bulk-insertion function - mc_zd_responses_ instead of this function.
// extern "C"
// void mc_ZD_add_response_( const FInteger& aCellId,
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
//    MCZDResponseProxy* who ( MCZDResponseProxy::whoAmI() );
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
void MCZDResponseProxy::updateBeginRun( const Record& iRecord )
{
   // Make sure Cleog begin run data is valid.
   // This bindable proxy is tied to the beginRun stream.
   // m_producer points to MCResponseProd producer which has the function
   // updateCleogBeginRun which checks if begin run is valid
   m_producer->updateCleogBeginRun( iRecord.frame() );
}


//-----------------------------------------------
// Bindable proxy - method to bind to other streams
PROXY_BIND_METHOD( MCZDResponseProxy )
//-----------------------------------------------
