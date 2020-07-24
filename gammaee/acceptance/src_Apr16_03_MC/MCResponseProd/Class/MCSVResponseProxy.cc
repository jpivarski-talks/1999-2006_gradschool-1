// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCSVResponseProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCSVResponseProxy.cc,v 1.15 2003/04/15 22:03:58 bkh Exp $
//
// Revision history
//
// $Log: MCSVResponseProxy.cc,v $
// Revision 1.15  2003/04/15 22:03:58  bkh
// Throw no data exception for incorrect config
//
// Revision 1.14  2003/01/16 18:31:24  cleo3
// removed unnecessary include
//
// Revision 1.13  2001/12/04 04:09:33  victor
// applied SVEfficiencyCorrections, changed report level for edge cases
//
// Revision 1.12  2001/11/19 23:31:00  victor
// changed the way efficiencies are applied
//
// Revision 1.11  2001/04/09 14:24:09  mahlke
// introduce flag to switch off geometry or responses for single subdetectors
//
// Revision 1.10  2000/12/01 19:24:45  cja23
// added Si efficiencies lookup and use
//
// Revision 1.9  2000/07/25 20:19:50  pg
// Minor clean up in Si code
//
// Revision 1.8  2000/05/09 13:32:24  pg
// Fixed problems with Si simulation: offsets in charge deposition; Z-side charge sharing
//
// Revision 1.7  2000/04/19 00:44:20  pg
// Added protection against TOO MANY HITS case. Extract Si geometry from SVAlignment stream.
//
// Revision 1.6  2000/04/17 20:12:03  bkh
// Elim checks of ptr after new
//
// Revision 1.5  2000/03/08 22:38:37  pg
// Forgot to commit changes to Si hit production.
//
// Revision 1.4  1999/11/16 20:50:43  pg
// Added Si simulation
//
// Revision 1.3  1999/10/24 20:52:35  cdj
// removed inappropriate use of typename
//
// Revision 1.2  1999/06/10 20:07:36  bkh
// fix argument ordering problem in add_response usage
//
// Revision 1.1.1.1  1999/04/16 20:07:32  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/25 21:31:00  bkh
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

#include "FrameAccess/insert.h"         
#include "FrameAccess/extract.h"  
// Frame access
#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAPtrTable.h"
#include "FrameAccess/FAConstants.h"
#include "SiEfficiencyProc/SEIndexCalculator.h"
#include "DBSVEfficiency.hh"
#include "C3sv/SiStream.h"
#include "RandomModule/RandomGenerator.h"
#include "SiGeom/SiGeomDescription.h" 
#include "ASiStorePro/ASiStore.h" 
#include "ASiStorePro/ASiHybrid.h"
#include "ASiStorePro/ASiLadder.h" 
#include "ASiStorePro/ASiSensorInfo.h" 
#include "ASiStorePro/ASiStrip.h" 
#include "ASiStorePro/ASiSensorAddress.h"
// needed for PROXY_BIND_METHOD
#include "ProxyBind/ProxyBoundMethodAction.h" 

#include "ASiStorePro/ASiSensorAddress.h"
#include "Processor/Processor.h"
#include "CommandPattern/Parameter.h"
#include "HistogramInterface/HistogramPackage.h"
#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Geometry/Vector3D.h"
#include "STLUtility/fwd_vector.h"
#include "DBSVEfficiency.hh"
#include "FrameAccess/FAConstants.h"
#include "FrameAccess/FAInserter.h"
// user include files
#include <fstream>
#include "SiEfficiencyProc/SEIndexCalculator.h"

#include "MagField/MagneticField.h"

// Producer that calls this proxy
#include "MCResponseProd/MCResponseProd.h"

#include "MCResponseProd/MCSVResponseProxy.h"

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

#define SMALL_NUMBER 0.000001

static const char* const kReport = "MCResponse.MCSVResponseProxy" ;

//typedef STL_MAP(int,DBSVEfficiency) AuxConstMap;
typedef STL_MAP(int,float) AuxConstMap;

// ---- cvs-based strings (Id and Tag with which file was checked out)

static const char* const kIdString  = "$Id: MCSVResponseProxy.cc,v 1.15 2003/04/15 22:03:58 bkh Exp $";
static const char* const kTagString = "$Name: v06_02_06 $";


//
// static data member definitions
//

MCSVResponseProxy* MCSVResponseProxy::k_whoAmI ( 0 ) ;

//
// constructors and destructor
//
MCSVResponseProxy::MCSVResponseProxy( MCResponseProd& iProducer ) 
   : m_ptrTable ( new value_type ) ,
     m_howMany  ( 0 ) ,
     m_producer( &iProducer )
{

   report(INFO, kReport ) << "In the constructor of MCSVResponseProxy ..."<<endl;

   checkConstants = true;

   // bind `auxilliary' functions that you want called when a new record
   // on the particular stream appears
   bind( &MCSVResponseProxy::updateBeginRun, Stream::kBeginRun );

   report( INFO, kReport ) << "Exiting the constructor of MCSVResponseProxy ..."<<endl;


}

// MCSVResponseProxy::MCSVResponseProxy( const MCSVResponseProxy& iproxy )
// {
//   *this = iproxy;
// }

MCSVResponseProxy::~MCSVResponseProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const MCSVResponseProxy& MCSVResponseProxy::operator=( const MCSVResponseProxy& iproxy )
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
MCSVResponseProxy::invalidateCache()
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

MCSVResponseProxy* 
MCSVResponseProxy::whoAmI()
{
   return k_whoAmI ;
}

void 
MCSVResponseProxy::addResponse( const FInteger aCellId     ,
				const FInteger aParticleId ,
				const FReal    aCharge       ) 
{
   // just to be extra careful about conversions from fortran types
   const MCSVResponse::Identifier identifier ( ++m_howMany ) ;
   const MCSVResponse::PartIdType particleId ( aParticleId ) ;
   const MCSVResponse::CellIdType cellId     ( aCellId     ) ;
   const MCSVResponse::ChargeType charge     ( aCharge     ) ;

   MCSVResponse* tmp( new MCSVResponse( identifier ,
					particleId ,
					cellId     ,
					charge       ) ) ;
   
   (*m_ptrTable).insert( tmp ) ;
}


// Header for Fortran subroutine called by faultHandler to fill MC Responses.
// Two ways to fill Responses: on-the-fly or bulk-insertion.
// On-the-fly: fills each Response individually
// Bulk-insertion: pass array with all Responses at once.
// Use fortran_types.h type definitions for cross-platform compatibility
//
// No arguments for on-the-fly method of filling MC responses
//extern "C" void mc_sv_responses_();
extern "C" void mc_sv_responses_(
    const FInteger& aMaxResponse  ,
    FInteger&       aNResponse    ,
    FInteger        aWafer[]      ,
    FInteger        aParticleId[] ,
    FReal           aCharge[]     ,      
    FReal           xin[]         ,      
    FReal           xout[]        ,      
    FReal           zin[]         ,      
    FReal           zout[]        ,
    FInteger        resetEfficiencies[]
    ) ;


const MCSVResponseProxy::value_type*
MCSVResponseProxy::faultHandler( const Record&  iRecord,
				 const DataKey& iKey )
{
   FAItem<DetectorConfiguration>                              iConfig   ;
   extract( iRecord.frame().record( Stream::kBaseGeometry ) , iConfig ) ;
   if( iConfig->useZDnotSI() )
   {
      throw DANoDataException< value_type >( iRecord.stream(),iKey ) ;
   }

   // Phase 1 - run Geant
   // Trigger Geant for this event.
   // m_producer points to the producer that provides this proxy (MCResponseProd)
   // and call the function triggerGeantEvent to trigger Geant if it hasn't been
   // done for this event.
   // (4/11/99 Temp fix of (Frame&) (CHANGE WHEN CURRENT UPDATED))

   m_producer->triggerGeantEvent(  iRecord.frame() );

   // Phase 2 - creation of MC Response objects
   // Initialize - require ptr table of MC Responses to be empty & initialize m_howMany   
   assert( 0 == (*m_ptrTable).size() ); 
   m_howMany = 0 ;

   // check whether SVResponses are wanted at all
   // if not, skip filling responses into m_ptrTable 
   if (m_producer -> m_getSVResponses.value() != 0) {


// extract Si ActiveElement
     FAItem< ASiStore > ProSensor;
     extract( iRecord.frame().record( Stream::kSVAlignment ), ProSensor );
     if( !ProSensor.valid() )
     {
        report( ERROR, kReport ) 
           << "Couldn't extract ProSensor, so do nothing!" << endl;
        return 0;
     }

     //extract efficiencies 
     extract(iRecord.frame().record(SiStream::kSVEfficiency), efficiencies);
     if( ! efficiencies.valid() )
     {
	report(ERROR, kReport) << " Not valid SVEfficiency constants ..." << endl;
	return 0;
     }

     //extract corrections to efficiencies 
     extract(iRecord.frame().record(SiStream::kSVEfficiencyCorrections), corrections);
     if( ! corrections.valid() )
     {
	report(ERROR, kReport) << " Not valid SVEfficiencyCorrections constants ..." << endl;
	return 0;
     }

     // Fill MC Responses objects (use either on-the-fly or bulk-insertion method)
     // on-the-fly method to add MC Responses to table
     //   set static pointer k_whoAmI so global fcn knows who I am
     //   call Fortran mc_xx_add_response_ for each response
//   k_whoAmI = this ; 
//   mc_sv_responses_() ; 


     // Uncomment for bulk-insertion of MC responses 
     static const FInteger k_maxResponse ( 3000 ) ; // max # hits to be processed
     FInteger cellId;        // cellId's (LA)
     FReal    charge;        // charge on the strip

     FInteger particleIdF[ k_maxResponse ] ;        // particleId's
     FInteger waferIdF   [ k_maxResponse ] ;        // wafer in ladder #, 
     FInteger ladderIdF  [ k_maxResponse ] ;        // ladder in layer#, 
     FInteger layerIdF   [ k_maxResponse ] ;        // layer #, 
     FReal    edepF      [ k_maxResponse ] ;        // deposited energy
     FReal    xin        [ k_maxResponse ] ;        // entrance X
     FReal    xout       [ k_maxResponse ] ;        // exit X
     FReal    zin        [ k_maxResponse ] ;        // entrance Z
     FReal    zout       [ k_maxResponse ] ;        // exit Z
     FInteger resetEfficiencies[ k_maxResponse ];   
     FInteger nGeantHits ( 0 ) ;                    // number of Geant hits

// Receive Geant hit information
     mc_sv_responses_( k_maxResponse ,
   	   	       nGeantHits    ,
   		       waferIdF      ,
   		       particleIdF   ,
        	       edepF         ,
   	  	       xin           ,
   		       xout          ,
   		       zin           ,
   		       zout          ,
		       resetEfficiencies ) ;

     if( k_maxResponse < nGeantHits )
     {
        report( WARNING, kReport ) << "nGeantHits exceeds max, will keep only " 
	                           << k_maxResponse <<  endl ;
        nGeantHits = k_maxResponse;
     }
     
     RandomGenerator& ran ( RandomGenerator::instance() );

     for ( FInteger iGH ( 0 ) ; iGH < nGeantHits ; ++iGH )
     {

// Hits are tagged by the unique wafer ID (1-447), so hit is already
// in the right wafer (thanks to Geant numbering scheme which is derived from
// Si geometry tree).
// This function takes a Geant hit and creates all MCSVresponses it 
// produces.

	if( resetEfficiencies[iGH] )
	{
	   efficiencyZ   = ran.flat(0,1);
	   efficiencyPhi = ran.flat(0,1);
	}
	
        createResponses(iRecord,
	  	        *ProSensor,
		        waferIdF[iGH],
		        particleIdF[iGH],
		        edepF[iGH],
		        xin[iGH],
		        xout[iGH],
		        zin[iGH],
		        zout[iGH] );
     }
   }
   return m_ptrTable ;
}

void 
MCSVResponseProxy::createResponses( const Record& iRecord,
				    const ASiStore& store,
				    const FInteger waferId,
				    const FInteger trackId,
				    const FReal    charge,
				    const FReal    xin_orig,
				    const FReal    xout_orig,
				    const FReal    zin_orig,
				    const FReal    zout_orig)
{
   FReal rpitch = SiGeomDescription::kSensorPitchX;
   FReal zpitch = SiGeomDescription::kSensorPitchZ;
   FReal ractive = 255*rpitch;
   FReal zactive = 255*zpitch;

   SEIndexCalculator calculator(1,1);
   calculator.setWafer(waferId);
   RandomGenerator& ran ( RandomGenerator::instance() );
   float efficiency = 0;
   float correction = 1;

// Get the wafer object
   const ASiSensorInfo& sensor = store.sensor(waferId);
// Correct for the finite active area.
   FReal xin,xout,zin,zout,clipped;
   clipCharge( charge,xin_orig,xout_orig,zin_orig,zout_orig,
	       clipped,xin,xout,zin,zout);
// Now all coordinates are within active area and charge is appropriately 
// reduced.
   
// R-Phi strips first
   FReal xmin = xin;
   FReal xmax = xout;
   if(xin > xout)
   {
      xmin = xout;
      xmax = xin;
   }
   FReal rstrip_in = sensor.rstrip(xmin);
   FReal rstrip_out = sensor.rstrip(xmax);
   FInteger istrip_in = rstrip_in + 0.5;
   FInteger istrip_out = rstrip_out + 0.5;
// variuos border cases.
   if(istrip_in < 1)
   {
      istrip_in = 1;
      rstrip_in = 0.5;
   }
   if(istrip_out < 1)
   {
      istrip_out = 1;
      rstrip_out = 0.5;
   }
   if(istrip_in > 511)
   {
      istrip_in = 511;
      rstrip_in = 511.5;
   }
   if(istrip_out >511)
   {
      istrip_out = 511;
      rstrip_out = 511.5;
   }

// Get local chip number(s) for efficiency lookup
// can get fancy later with multi-chip hits.  Right now, just use the
// chip in the middle of the Geant box
//   int ichip_in  = int((istrip_in  - 1)/128 + 1);
//   int ichip_out = int((istrip_out - 1)/128 + 1);
   FInteger middlestrip = (istrip_in + istrip_out) / 2;
// rphi chips are 1 - 4, counting from strip 1, 128 strips each.
   int ichip_ctr = int((middlestrip - 1)/128 + 1);
   
// Look up the efficiency for this chip/wafer combination now
   calculator.setChip(ichip_ctr);
   efficiency = efficiencies[calculator.index()].get_Efficiency();
   correction = corrections[calculator.index()].get_EfficiencyCorrection();

   if( correction > SMALL_NUMBER )
   {
      efficiency = efficiency/correction;
      if(efficiency > 1.0) efficiency = 1.0;
   }
   else
   {
      if(efficiency > SMALL_NUMBER) 
      {
	 efficiency = 1.0;
      }
      else
      {
	 efficiency = 0;
      }
   }

// Only do the rest of the work if we roll a number below efficiency
   if( efficiencyPhi <= efficiency)
   {
//   Figure out how to share charge.
      FReal x1(0.),x2(0.),q1(0.),q2(0.);
      FInteger istart=0;
      FInteger cellId=0;
      if( rstrip_in == rstrip_out ) //normal incidence
      {
         if(rstrip_in-istrip_in <= 0.5)
         {
           x1 = rstrip_in - istrip_in + 0.5;
           x2 = x1;
           istart = istrip_in;
         }
         else
         {
           x1 = rstrip_in - istrip_in - 0.5;
           x2 = x1;
           istart = istrip_in - 1;
         }
         sharePhi(clipped,x1,x2,q1,q2);
         if(istart > 0)
         {
            cellId = sensor.lAddress(0,istart-1); 
            addResponse( cellId, trackId, q1);
         }
         istart++;
         if(istart <= 511)
         {
            cellId = sensor.lAddress(0,istart-1);
            addResponse( cellId, trackId, q2);
         }
      } //end of normal incidence case
      else if( rstrip_in >= 511 )
      {
         report(DEBUG, kReport) << " Upper edge case not implemented yet!"
                               << endl;
      }
      else if( rstrip_out <= 0.5)
      {
         report(DEBUG, kReport) << " Lower edge case not implemented yet!"
                               << endl;
      }
      else // usual case
      {
         FReal qtmp = 0.;
         FInteger istrmin = istrip_in;
         if( (rstrip_in - istrip_in) < 0. && istrip_in>0 )
         {
            istrmin = istrip_in -1;
         }
         FInteger istrmax = istrip_out-1;
         if(rstrip_out - istrip_out > 0.)
         {
            istrmax = istrip_out;
         }
         for( int i = istrmin; i <= istrmax; ++i)
         {
            istart = i;
            x1 = rstrip_in - istart ;
            if( x1 < 0)
            {
               x1 = 0.;
            }

            x2 = rstrip_out - istart ;
            if( x2 > 1.)
            {
               x2 = 1.;
            }
            sharePhi(clipped/(rstrip_out-rstrip_in), x1, x2, q1, q2);
            qtmp = qtmp + q1;
            if(istart >0)
            {
               cellId = sensor.lAddress(0,istart-1);
               addResponse(cellId,trackId,qtmp);
            }
            qtmp = q2;
         }
         istart++;
         if(istart <= 511)
         {
            cellId = sensor.lAddress(0,istart-1);
            addResponse(cellId,trackId,qtmp);
         }
      }   
   }
          
// Now z-strips
   FReal zstrip_in = sensor.zstrip(zin);
   FReal zstrip_out = sensor.zstrip(zout);
// paranoid check
   if( zstrip_out < zstrip_in) {
      FReal ztemp = zstrip_in;
      zstrip_in = zstrip_out;
      zstrip_out = ztemp;
   }
   FReal pathlength = 1.;
   istrip_in = zstrip_in + 0.5;
   istrip_out = zstrip_out + 0.5;
// variuos border cases.
   if(istrip_in < 1)
   {
      istrip_in = 1;
      zstrip_in = 0.5;
   }
   if(istrip_out < 1)
   {
      istrip_out = 1;
      zstrip_out = 0.5;
   }
   if(istrip_in > 511)
   {
      istrip_in = 511;
      zstrip_in = 511.5;
   }
   if(istrip_out >511)
   {
      istrip_out = 511;
      zstrip_out = 511.5;
   }      
   if(zstrip_out != zstrip_in)
   {
      pathlength = abs(zstrip_out-zstrip_in);
   }
   
// Get local chip number(s) for efficiency lookup
// can get fancy later with multi-chip hits.  Right now, just use the
// chip in the middle of the Geant box
//   ichip_in  = int((istrip_in  - 1)/128 + 5);
//   ichip_out = int((istrip_out - 1)/128 + 5);
   middlestrip = (istrip_in + istrip_out) / 2;
// z chips are 5 - 8, counting from strip 1, 128 strips each.
   ichip_ctr = int((middlestrip - 1)/128 + 5);

// Look up the efficiency for this chip/wafer combination now

   calculator.setChip(ichip_ctr);
   efficiency = efficiencies[calculator.index()].get_Efficiency();
   correction = corrections[calculator.index()].get_EfficiencyCorrection();

   if( correction > SMALL_NUMBER )
   {
      efficiency = efficiency/correction;
      if(efficiency > 1.0) efficiency = 1.0;
   }
   else
   {
      if(efficiency > SMALL_NUMBER) 
      {
	 efficiency = 1.0;
      }
      else
      {
	 efficiency = 0;
      }
   }
   

// Only do the rest of the work if we roll a number below efficiency
   if( efficiencyZ <= efficiency)
   {
      
//  Figure out how to share charge.
      FReal z1=0.;
      FReal z2=0.;
      FReal qq=0.;
      FInteger istart=0;
      FInteger cellId=0;
      if( zstrip_in == zstrip_out ) //normal incidence
      {
         if(zstrip_in-istrip_in <= 0.5)
         {
           z1 = zstrip_in - istrip_in + 0.5;
           z2 = z1;
           istart = istrip_in;
         }
         else
         {
           z1 = zstrip_in - istrip_in - 0.5;
           z2 = z1;
           istart = istrip_in - 1;
         }
         shareZ(clipped/pathlength,z1,z2,qq);  
         if(istart > 0)
         {
            cellId = sensor.lAddress(1,istart-1);
            //report(DEBUG,kReport) << " 90-degree case for Z-side: "
            //                      << " cellId " << cellId
            //                      << " charge " << clipped
            //                      << " shared " << qq << endl;
            addResponse( cellId, trackId, qq);
         }
      } //end of normal incidence case 
      else if( zstrip_in >= 511 )
      {
         report(DEBUG, kReport) << " Upper edge Z case not implemented yet!"
                               << endl;
      }
      else if( zstrip_out <= 0.5)
      {
         report(DEBUG, kReport) << " Lower edge Z case not implemented yet!"
                               << endl;
      }
      else // usual case
      {   
         for( int i = istrip_in; i <= istrip_out; ++i)
         {
            istart = i;
            z1 = zstrip_in - i;
            if( z1 < -0.5)
            {
               z1 = -0.5;
            }
           
            z2 = zstrip_out - i;
            if( z2 > 0.5)
            {
               z2 = 0.5;
            }
// Z1 has to be smaller
            if( z2 < z1)
            {
               float ztmp = z1;
               z1=z2;
               z2=ztmp;
            }
      
            shareZ(clipped/pathlength, z1, z2, qq);
            if(istart>0)
            {
               cellId = sensor.lAddress(1,istart-1);
               //report(DEBUG,kReport) << " Usual case for Z-side: "
               //                      << " cellId " << cellId
               //                      << " charge " << clipped
               //                      << " z1 " << z1
               //                      << " z2 " << z2
               //                      << " shared " << qq << endl;
               addResponse(cellId,trackId,qq);
            }
         }
      }
   }
}

FReal
MCSVResponseProxy::clipCoord( const FReal coord,
			      const FReal limit) const
{
// Clip it
   if(abs(coord)<=limit) return coord;
   if(coord < -limit) return -limit;
   if(coord > limit) return limit;
   return 0;
}

void
MCSVResponseProxy::clipCharge( const FReal    charge,
			       const FReal    xin_orig,
			       const FReal    xout_orig,
			       const FReal    zin_orig,
			       const FReal    zout_orig,
			       FReal& clipped,
			       FReal& xin,
			       FReal& xout,
			       FReal& zin,
			       FReal& zout) const
{
   // Avoid excessive typing
   float xactive = SiGeomDescription::kSensorActiveX;
   float zactive = SiGeomDescription::kSensorActiveZ;

// Clip Xin
   xin = clipCoord(xin_orig,xactive);
   xout = clipCoord(xout_orig,xactive);
   zin = clipCoord(zin_orig,zactive);
   zout = clipCoord(zout_orig,zactive);

   float orig_length = sqrt( (xin_orig-xout_orig)*(xin_orig-xout_orig) +
			     (zin_orig-zout_orig)*(zin_orig-zout_orig) );
   float length = sqrt( (xin-xout)*(xin-xout) + (zin-zout)*(zin-zout) );

   if(orig_length > 0.) {
      clipped = charge*length/orig_length;
   }
   else {
      clipped = (abs(xin_orig)>xactive) ? 0. : charge;
   }
//   "Clip" charge, since active are of the Si wafer is smaller than it's
// geometrical dimensions.
}

void
MCSVResponseProxy::shareZ( const FReal charge,
			   const FReal    xi1,
			   const FReal    xi2,
			   FReal&    qdep)
{
   FReal teff(0.8);
   FReal deleff(0.2);
   FReal a = 12.*teff*deleff/(3.-2.*deleff);
   FReal c = 3.*teff/(3.-2.*deleff);
   FReal x1;
   FReal x2;
   if( xi1 == xi2) 
   {
      //report(DEBUG,kReport) << "x1 = " << xi1 << " x2 = " << xi2
      //		    << " Charge = " << charge << endl;
      
      x1 = abs(xi1);
      qdep = charge*(a*x1*x1-a*x1+c);
   }
   else
   {
      FReal si=1.;
      FReal so=1.;
      x1 = abs(xi1);
      x2 = abs(xi2);
      if(xi1 < 0.)
      {
	 si = -1.;
      }
      if(xi2 < 0.)
      {
	 so = -1.;
      }
      
      qdep = charge*(so*(a*x2*x2*x2/3. - a*x2*x2/2. + c*x2) -
		     si*(a*x1*x1*x1/3. - a*x1*x1/2. + c*x1));
   }
}

void
MCSVResponseProxy::sharePhi( const FReal charge,
			     const FReal    x1,
			     const FReal    x2,
			     FReal&    q1,
			     FReal&    q2) 
{
   
   FReal teff(0.8);
   FReal deleff(0.2);
   FReal a = 12.*teff*deleff/(3.-2.*deleff);
   FReal c = 3.*teff/(3.-2.*deleff);
   if( x1 == x2) 
   {
      q2 = charge*x1*(a*x1*x1 - a*x1 + c);
      q1 = charge*(1-x1)*(a*x1*x1-a*x1+c);
   }
   else
   {
        q2 = charge*((a*x2*x2*x2*x2/4. - a*x2*x2*x2/3. + c*x2*x2/2.)-
		     (a*x1*x1*x1*x1/4. - a*x1*x1*x1/3. + c*x1*x1/2.));
        q1 = charge*((a*x2*x2*x2/3. - a*x2*x2/2. + c*x2)-
		     (a*x1*x1*x1/3. - a*x1*x1/2. + c*x1)) - q2;
   }
}

extern "C"
void mc_sv_add_response_( const FInteger& aCellId     ,
			  const FInteger& aParticleId ,
			  const FReal&    aCharge       ) 
{
   MCSVResponseProxy* who ( MCSVResponseProxy::whoAmI() ) ;
   if( 0 == who ) 
   {
      report( EMERGENCY, kReport ) << "Null whoAmI ptr, exiting!" << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }
   who->addResponse( aCellId     , 
		     aParticleId ,
		     aCharge      ) ;
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
MCSVResponseProxy::updateBeginRun( const Record& iRecord )
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
PROXY_BIND_METHOD( MCSVResponseProxy )
//-----------------------------------------------
