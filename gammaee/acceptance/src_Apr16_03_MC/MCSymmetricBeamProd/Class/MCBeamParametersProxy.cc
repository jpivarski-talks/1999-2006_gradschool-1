// -*- C++ -*-
//
// Package:     <MCSymmetricBeamProd>
// Module:      MCBeamParametersProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Jan 11 16:07:37 EST 2001
// $Id: MCBeamParametersProxy.cc,v 1.7 2002/10/29 21:14:30 bkh Exp $
//
// Revision history
//
// $Log: MCBeamParametersProxy.cc,v $
// Revision 1.7  2002/10/29 21:14:30  bkh
// Limits should be based on ctr of mass energy not beam energy! (fix bug)
//
// Revision 1.6  2002/10/28 23:02:56  bkh
// Make energy limit setting work
// Make resonance convolution with beam energy spread work
//
// Revision 1.5  2002/05/13 19:19:25  bkh
// Set min and max cm energy acc to spread and cm energy, not parameters
//
// Revision 1.4  2002/03/26 17:28:53  bkh
// Use BeamEnergy object not CesrBeamEnergy and remove related parameters
//
// Revision 1.3  2001/12/18 18:51:50  lkg
// Minor comment changes
//
// Revision 1.2  2001/02/26 01:02:01  cdj
// now gets CesrBeamEnergy from StartRun
//
// Revision 1.1.1.1  2001/01/31 21:10:50  lkg
// imported MCSymmetricBeamProd source
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#include <memory>  //for auto_ptr

// user include files
#include "Experiment/report.h"

#include "MCSymmetricBeamProd/MCBeamParametersProxy.h"
#include "MCSymmetricBeamProd/MCSymmetricBeamProd.h"
#include "MCSymmetricBeamProd/RunStatsBeamEnergyIsCrapException.h"
#include "MCBeamProdBase/FillCommonBeamParameters.h"

#include "DataHandler/Frame.h"
#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FAItem.h"

#include "BeamEnergy/BeamEnergy.h"

#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

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
static const char* const kFacilityString = "MCSymmetricBeamProd.MCBeamParametersProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCBeamParametersProxy.cc,v 1.7 2002/10/29 21:14:30 bkh Exp $";
static const char* const kTagString = "$Name: v01_02_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCBeamParametersProxy::MCBeamParametersProxy( const MCSymmetricBeamProd* beamProducer )
   : m_mcBeamParameters( 0 ),
     m_beamProducer( beamProducer )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &MCBeamParametersProxy::boundMethod, Stream::kBeginRun );
}

// MCBeamParametersProxy::MCBeamParametersProxy( const MCBeamParametersProxy& iproxy )
// {
//   *this = iproxy;
// }

MCBeamParametersProxy::~MCBeamParametersProxy()
{
   delete m_mcBeamParameters ;
}

//
// assignment operators
//
// const MCBeamParametersProxy& MCBeamParametersProxy::operator=( const MCBeamParametersProxy& iproxy )
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
MCBeamParametersProxy::invalidateCache()
{
   delete m_mcBeamParameters ;
   m_mcBeamParameters = 0 ;
}

const MCBeamParametersProxy::value_type*
MCBeamParametersProxy::faultHandler( const Record& iRecord,
				     const DataKey& iKey )
{

   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_mcBeamParameters );

   MCBeamParameters newParams;

   // -------------- beam energy and energy spread ----------------
   // mean energy for each beam

   FAItem< BeamEnergy >                                iBeamEnergy;
   extract( iRecord.frame().record(Stream::kStartRun), iBeamEnergy );

   const double beamEnergy ( iBeamEnergy->value() ) ;

   if ( 0 == beamEnergy ) 
   {
      report( EMERGENCY, kFacilityString ) << "Zero beam energy, "
					   << "throwing exception " << endl ;
      throw RunStatsBeamEnergyIsCrapException(iRecord.syncValue().runNumber());
   }

   newParams.setElectronBeamEnergy( beamEnergy );
   newParams.setPositronBeamEnergy( beamEnergy );

   // spread in beam energies
   const double energyScalingOfSpread ( pow((newParams.cofmEnergy()/10.0), 2));
   const double cofmSpread = m_beamProducer->totalEnergySpreadAt10GeV()
      * energyScalingOfSpread;

   const double spread ( cofmSpread * sqrt(0.5) ) ;

   newParams.setElectronBeamEnergySpread( spread );
   newParams.setPositronBeamEnergySpread( spread );

   // fill all the parameters common to symmetric and asymmetric beams
   FillCommonBeamParameters aFiller( m_beamProducer, iRecord.frame() );
   aFiller.fillErUp( newParams );

   const DABoolean bwResonance ( newParams.resonantProduction() ) ;
   const double    resMass     ( newParams.resonanceMass()      ) ;
   const double    resWidth    ( newParams.resonanceWidth()     ) ;

   const double    eMin        ( newParams.minimumCMEnergy()    ) ;
   const double    eMax        ( newParams.maximumCMEnergy()    ) ;
 
   double eLimitLow  ( eMin ) ; // default value is param
   double eLimitHigh ( eMax ) ; // default value is param

   if( bwResonance  &&
       0 < resMass  && 
       0 < resWidth    )
   {
      if( 0 >= eMax ) 
      {
	 eLimitHigh = resMass + 5*resWidth ;
      }
      if( resMass < 10.7 &&
	  resMass > 10.5    )
      {
	 if( 0 >= eMin )
	 {
	    eLimitLow = 10.5601 ; // 4S minimum for 2 B mesons
	 }
      }
      else
      {
	 if( 0 >= eMin )
	 {
	    eLimitLow = resMass - 5*resWidth ;
	 }
      }
   }
   else
   {
      if( 0 >= eMin )
      {
	 eLimitLow  = 2*beamEnergy - 5*cofmSpread ;
      }
      if( 0 >= eMax )
      {
	 eLimitHigh = 2*beamEnergy + 5*cofmSpread ;
      }

      if( bwResonance &&
	  ( 0 >= resMass ||
	    0 >= resWidth   ) )
      {
	 report( EMERGENCY, kFacilityString ) 
	    << "Specified resonance but resMass="
	    << resMass
	    << " and resWidth=" 
	    << resWidth
	    << " are illegal!" << endl ;
	 throw ;
      }
   }

   newParams.setMaximumCMEnergy( eLimitHigh ) ;
   newParams.setMinimumCMEnergy( eLimitLow  ) ;

   //if an exception is thrown during this function, p_mcBeamParameters will
   // automatically delete the object it is refering to
   auto_ptr<MCBeamParameters> p_mcBeamParameters;

   //have p_mcBeamParameters hold onto the new object
   p_mcBeamParameters.reset( new MCBeamParameters( newParams ) );

   //Since no exception happened, tell p_mcBeamParameters to give its pointer to
   // m_mcBeamParameters
   return ( m_mcBeamParameters = p_mcBeamParameters.release() ) ;
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
//MCBeamParametersProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< MCBeamParameters >;

PROXY_BIND_METHOD( MCBeamParametersProxy )
//-----------------------------------------------

