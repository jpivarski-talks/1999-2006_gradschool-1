// -*- C++ -*-
//
// Package:     MCInfo
// Module:      MCParticlePropertyStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: MCParticlePropertyStorageHelper.cc,v 1.2 2002/02/05 03:13:11 lkg Exp $
//
// Revision history
//
// $Log: MCParticlePropertyStorageHelper.cc,v $
// Revision 1.2  2002/02/05 03:13:11  lkg
// fix range for PDGId
//
// Revision 1.1  2001/12/19 18:20:08  lkg
// add storage helpers for particle properties
//
// Revision 1.5  2001/01/31 22:16:08  cdj
// added reminder to users in storage routine to register new versions
//
// Revision 1.4  2000/01/21 21:07:39  cdj
// helper skeletons now include SMPackInfo.h
//
// Revision 1.3  1999/10/18 18:15:05  cdj
// now uses instantiate_proxyhelper.h
//
// Revision 1.2  1999/09/30 22:38:33  cdj
// no longer need default constructor
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
// imported package
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "MCInfo/Storage/MCParticlePropertyStorageHelper.h"
#include "MCInfo/Storage/DeliverDummyMCPPS.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMPackInfo.h" //defines sm_pack*

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCParticlePropertyStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCParticlePropertyStorageHelper.cc,v 1.2 2002/02/05 03:13:11 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCParticlePropertyStorageHelper::MCParticlePropertyStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &MCParticlePropertyStorageHelper::deliverV1 );
   registerVersion( &MCParticlePropertyStorageHelper::deliverV1 );
}

// MCParticlePropertyStorageHelper::MCParticlePropertyStorageHelper( const MCParticlePropertyStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//MCParticlePropertyStorageHelper::~MCParticlePropertyStorageHelper()
//{
//}

//
// assignment operators
//
// const MCParticlePropertyStorageHelper& MCParticlePropertyStorageHelper::operator=( const MCParticlePropertyStorageHelper& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
void 
MCParticlePropertyStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const MCParticleProperty& iData ) 
{
// NOTE: Any change (adding/removing variable OR packing info) to this routine
//    MUST be accompanied by registering a new version deliver routine in
//    this class's constructor.  
//    If only the packing info is changes, you can register the same deliver
//    routine a second time.

   double charge3 = iData.charge()*3+0.5;
   int chg3;
   if (charge3 > 6.) chg3 = 6;
   else if (charge3 > 5.) chg3 = 5;
   else if (charge3 > 4.) chg3 = 4;
   else if (charge3 > 3.) chg3 = 3;
   else if (charge3 > 2.) chg3 = 2;
   else if (charge3 > 1.) chg3 = 1;
   else if (charge3 > 0.) chg3 = 0;
   else if (charge3 > -1.) chg3 = -1;
   else if (charge3 > -2.) chg3 = -2;
   else if (charge3 > -3.) chg3 = -3;
   else if (charge3 > -4.) chg3 = -4;
   else if (charge3 > -5.) chg3 = -5;
   else if (charge3 > -6.) chg3 = -6;
   else chg3 = 1000;

   iSink 
      << SM_VAR( iData, name )   
      << sm_pack( SM_VAR( iData, QQId ), -666, 1000, 1 )
      << sm_pack( SM_VAR( iData, stableId ), -1, 50, 1 )
      << sm_pack( SM_VAR( iData, PDGId ), -100000000, 100000000, 1 )
      << sm_pack( SM_VAR( iData, geantId ), -666, 100, 1 )
      << sm_pack( sm_field("charge3", chg3), -6, 6, 1)
      << sm_pack_fraction( SM_VAR( iData, ctau ), 1.0e-5, 1.0e3, 1.0e-4 )
      << sm_pack_fraction( SM_VAR( iData, mass ), 1.0e-4, 1.0e3, 1.0e-6 )
      << sm_pack_fraction( SM_VAR( iData, width ), 1.0e-4, 10., 1.0e-4 )
      << sm_pack_fraction( SM_VAR( iData, minMass ), 1.0e-3, 1.0e3, 1.0e-4 )
      << sm_pack_fraction( SM_VAR( iData, maxMass ),  1.0e-3, 1.0e3, 1.0e-4 )
      << sm_pack( SM_VAR( iData, spin ), 0, 5.0, 0.5 )
      << sm_pack( SM_VAR( iData, parity ), -1, 1, 1 )
      << sm_pack( SM_VAR( iData, cParity ), -1, 1, 1 )
      << sm_pack( sm_field( "mixable", 
                            static_cast<unsigned char>(iData.mixable()) ), 0, 1, 1 )
      ;
}

MCParticleProperty* 
MCParticlePropertyStorageHelper::deliverV1( SMSourceStream& iSource )
{
   
   string name; 
   QQ_id qqId; 
   Stable_id stableId; 
   PDG_id pdgId; 
   Geant_id geantId; 
   int charge; 
   Double ctau; 
   Double mass; 
   Double width; 
   Double minMass; 
   Double maxMass; 
   Double spin; 
   Integer parity; 
   Integer cParity; 
   unsigned char mixable_as_char;
   DABoolean mixable; 

   iSource 
      >> name 
      >> qqId 
      >> stableId 
      >> pdgId 
      >> geantId 
      >> charge 
      >> ctau 
      >> mass 
      >> width 
      >> minMass 
      >> maxMass 
      >> spin 
      >> parity 
      >> cParity 
      >> mixable_as_char
	 ;

   mixable = mixable_as_char;

   return make( MCParticleProperty( 
      name,  
      qqId,  
      stableId,  
      pdgId,  
      geantId,  
      charge/3.0,  
      ctau,  
      mass,  
      width,  
      minMass,  
      maxMass,  
      spin,  
      parity,  
      cParity,  
      mixable ) ); 
}

//
// const member functions
//
const MCParticleProperty& 
MCParticlePropertyStorageHelper::getDefault() const
{
   return DeliverDummyMCPPS::instance().dummyMCParticleProperty();
}

DABoolean 
MCParticlePropertyStorageHelper::compare( 
   const MCParticleProperty* iNewData, 
   const MCParticleProperty& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for MCParticleProperty
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//MCParticleProperty*
//SMStorageHelper<MCParticleProperty>::make( const MCParticleProperty& iTempData ) const
//{
   //change this line if MCParticleProperty does not have a copy constructor
//   return new MCParticleProperty( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( MCParticlePropertyStorageHelper, MCParticleProperty )

//------------------------------------------------------
