// -*- C++ -*-
//
// Package:     MCInfo
// Module:      MCParticlePropDecayModeStorageInterfaceStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: MCParticlePropDecayModeStorageInterfaceStorageHelper.cc,v 1.1 2001/12/19 18:20:07 lkg Exp $
//
// Revision history
//
// $Log: MCParticlePropDecayModeStorageInterfaceStorageHelper.cc,v $
// Revision 1.1  2001/12/19 18:20:07  lkg
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
#include "Experiment/report.h"
#include "MCInfo/Storage/MCParticlePropDecayModeStorageInterfaceStorageHelper.h"
#include "MCInfo/Storage/MCParticlePropertyStoreStorageHelper.h"
#include "MCInfo/Storage/DeliverDummyMCPPS.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMMakeContents.h"
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

static const char* const kFacilityString = "MCInfo.MCParticlePropDecayModeStorageInterfaceStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCParticlePropDecayModeStorageInterfaceStorageHelper.cc,v 1.1 2001/12/19 18:20:07 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_02 $";


class DecayModeInsertIterator :
#if defined(OLD_ITERATOR_CLASSES_BUG)
   public output_iterator 
#else
   public iterator<output_iterator_tag, MCDecayMode* >
#endif
{
   public:
      DecayModeInsertIterator( MCParticlePropDecayModeStorageInterface* theProperty ) :
#if defined(OLD_ITERATOR_CLASSES_BUG)
	 output_iterator(),
#else
	 iterator<output_iterator_tag, MCDecayMode* >(),
#endif
	 m_theProperty( theProperty ) {}
      typedef MCDecayMode* value_type;
      DecayModeInsertIterator& operator++() {return *this;}
      DecayModeInsertIterator& operator*() {return *this;}
      void operator=( MCDecayMode* aDecayMode) { 
	 m_theProperty->addDecayMode( *aDecayMode );
	 delete aDecayMode; // prevent memory leaks!
      }
   private:
      MCParticlePropDecayModeStorageInterface* m_theProperty;
};

//
// static data member definitions
//

//
// constructors and destructor
//
MCParticlePropDecayModeStorageInterfaceStorageHelper::MCParticlePropDecayModeStorageInterfaceStorageHelper( MCParticlePropertyStoreStorageHelper* storeHelper ) :
   m_storeStorageHelper( storeHelper )
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &MCParticlePropDecayModeStorageInterfaceStorageHelper::deliverV1 );
}

// MCParticlePropDecayModeStorageInterfaceStorageHelper::MCParticlePropDecayModeStorageInterfaceStorageHelper( const MCParticlePropDecayModeStorageInterfaceStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//MCParticlePropDecayModeStorageInterfaceStorageHelper::~MCParticlePropDecayModeStorageInterfaceStorageHelper()
//{
//}

//
// assignment operators
//
// const MCParticlePropDecayModeStorageInterfaceStorageHelper& MCParticlePropDecayModeStorageInterfaceStorageHelper::operator=( const MCParticlePropDecayModeStorageInterfaceStorageHelper& rhs )
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
MCParticlePropDecayModeStorageInterfaceStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const MCParticlePropDecayModeStorageInterface& iData ) 
{
// NOTE: Any change (adding/removing variable OR packing info) to this routine
//    MUST be accompanied by registering a new version deliver routine in
//    this class's constructor.  
//    If only the packing info is changes, you can register the same deliver
//    routine a second time.

   iSink 
      << SM_VAR( iData, QQId )   
      << sm_field( "DecayModeList",
		   sm_contents( iData.begin(), iData.end() ) )
      ;
}

MCParticlePropDecayModeStorageInterface* 
MCParticlePropDecayModeStorageInterfaceStorageHelper::deliverV1( SMSourceStream& iSource )
{
   QQ_id qqId; 

   iSource 
      >> qqId 
      ;

   MCParticlePropDecayModeStorageInterface* tmpInterface =  
      make( MCParticlePropDecayModeStorageInterface( 
	 m_storeStorageHelper->currentPropertyStore(),
	 qqId
	 ) );

   m_currentProperty = tmpInterface->theProperty();
   DecayModeInsertIterator inserter( tmpInterface );
   iSource
      >> sm_make_contents( inserter )
      ;

   return tmpInterface;
}

MCParticleProperty*
MCParticlePropDecayModeStorageInterfaceStorageHelper::currentProperty() {
   return m_currentProperty;
}

//
// const member functions
//
const MCParticlePropDecayModeStorageInterface& 
MCParticlePropDecayModeStorageInterfaceStorageHelper::getDefault() const
{
   MCParticlePropDecayModeStorageInterface* dummyInterface = 
      new MCParticlePropDecayModeStorageInterface( &(DeliverDummyMCPPS::instance().dummyMCParticleProperty()) );

   return *dummyInterface;
}

DABoolean 
MCParticlePropDecayModeStorageInterfaceStorageHelper::compare( 
   const MCParticlePropDecayModeStorageInterface* iNewData, 
   const MCParticlePropDecayModeStorageInterface& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for MCParticlePropDecayModeStorageInterface
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//MCParticlePropDecayModeStorageInterface*
//SMStorageHelper<MCParticlePropDecayModeStorageInterface>::make( const MCParticlePropDecayModeStorageInterface& iTempData ) const
//{
   //change this line if MCParticlePropDecayModeStorageInterface does not have a copy constructor
//   return new MCParticlePropDecayModeStorageInterface( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( MCParticlePropDecayModeStorageInterfaceStorageHelper, MCParticlePropDecayModeStorageInterface )

#include "StorageManagement/Template/SMContents.cc"
template class SMContents<MCParticleProperty::const_iterator>;

#include "StorageManagement/Template/SMMakeContents.cc"
template class SMMakeContents<DecayModeInsertIterator >;

#if defined(NO_ITERATOR_TRAITS_BUG)
template<>
struct iterator_traits<MCParticleProperty::const_iterator> {
public:
     typedef MCDecayMode value_type;
};
#endif

//------------------------------------------------------
