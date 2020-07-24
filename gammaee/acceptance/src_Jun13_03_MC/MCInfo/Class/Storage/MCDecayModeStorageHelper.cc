// -*- C++ -*-
//
// Package:     MCInfo
// Module:      MCDecayModeStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: MCDecayModeStorageHelper.cc,v 1.3 2002/06/06 01:26:56 lkg Exp $
//
// Revision history
//
// $Log: MCDecayModeStorageHelper.cc,v $
// Revision 1.3  2002/06/06 01:26:56  lkg
// get rid of unneeded code that was formerly not used because of bad SUNCC1 flag
//
// Revision 1.2  2002/06/04 18:56:04  lkg
// replaced SUNCC flags with specific bug flags
//
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
//#include "Experiment/report.h"
#include "MCInfo/Storage/MCDecayModeStorageHelper.h"
#include "MCInfo/Storage/MCParticlePropDecayModeStorageInterfaceStorageHelper.h"
#include "MCInfo/Storage/DeliverDummyMCPPS.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMPackInfo.h" //defines sm_pack*
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMContentsBuiltIn.h"
#include "StorageManagement/SMMakeContents.h"
#include "StorageManagement/SMFillContents.h"

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

static const char* const kFacilityString = "MCInfo.MCDecayModeStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCDecayModeStorageHelper.cc,v 1.3 2002/06/06 01:26:56 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_02 $";

#if defined(NO_ITERATOR_TRAITS_BUG)
#include "StorageManagement/sm_iterator_traits.h"
template<>
class sm_iterator_traits<SimpleHelicity**> {
   public:
      typedef SimpleHelicity* value_type;
};
template<>
class sm_iterator_traits<SimpleAngularHelicity**> {
   public:
      typedef SimpleAngularHelicity* value_type;
};

#endif

//
// static data member definitions
//

//
// constructors and destructor
//
MCDecayModeStorageHelper::MCDecayModeStorageHelper( MCParticlePropDecayModeStorageInterfaceStorageHelper* anInterfaceHelper ) :
   m_interfaceHelper( anInterfaceHelper )
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &MCDecayModeStorageHelper::deliverV1 );
}

// MCDecayModeStorageHelper::MCDecayModeStorageHelper( const MCDecayModeStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//MCDecayModeStorageHelper::~MCDecayModeStorageHelper()
//{
//}

//
// assignment operators
//
// const MCDecayModeStorageHelper& MCDecayModeStorageHelper::operator=( const MCDecayModeStorageHelper& rhs )
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
MCDecayModeStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const MCDecayMode& iData ) 
{
// NOTE: Any change (adding/removing variable OR packing info) to this routine
//    MUST be accompanied by registering a new version deliver routine in
//    this class's constructor.  
//    If only the packing info is changes, you can register the same deliver
//    routine a second time.

   // get pointers to user-defined objects into a Holder that makes
   // the pointer look like a container 
   SimpleHelicity* configPtr = 
      const_cast<SimpleHelicity*>(iData.helicityConfigs());
   helHolder holdHelicity( configPtr );

   SimpleAngularHelicity* anglePtr = 
      const_cast<SimpleAngularHelicity*>(iData.angularDistribs());
   angHolder holdAngular( anglePtr );

   iSink 
      << SM_VAR( iData, branchingFraction )   
      << SM_VAR( iData, model )   
      << sm_field( "Children", 
		   sm_contents_builtin( iData.childList().begin(), 
					iData.childList().end() ) )
      ;
   iSink
      << sm_field( "helicityConfigs",
		   sm_contents( holdHelicity.begin(), holdHelicity.end() ) )
      ;
   iSink
      << sm_field( "angularDistribs",
		   sm_contents( holdAngular.begin(), holdAngular.end() ) )
      ;
}

MCDecayMode* 
MCDecayModeStorageHelper::deliverV1( SMSourceStream& iSource )
{
   Double branchingFraction; 
   Integer model; 
   iSource 
      >> branchingFraction
      >> model
	 ;

   STL_VECTOR( QQ_id ) childList;
   back_insert_iterator<STL_VECTOR( QQ_id )> childInserter( childList );
   iSource
      >> sm_fill_contents( childInserter )
      ;
   
   SimpleHelicity* helicityConfigs[1] = {0};
   SimpleHelicity** helItr = helicityConfigs;
   iSource
      >> sm_make_contents( helItr )
      ;

   SimpleAngularHelicity* angularDistribs[1] = {0};
   SimpleAngularHelicity** angItr = angularDistribs;
   iSource
      >> sm_make_contents( angItr )
      ;

   return make( MCDecayMode( 
      m_interfaceHelper->currentProperty(),
      branchingFraction,
      childList,  
      model,
      *helicityConfigs,
      *angularDistribs ) ); 
}

//
// const member functions
//
const MCDecayMode& 
MCDecayModeStorageHelper::getDefault() const
{
   return DeliverDummyMCPPS::instance().dummyMCDecayMode();
}

DABoolean 
MCDecayModeStorageHelper::compare( 
   const MCDecayMode* iNewData, 
   const MCDecayMode& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for MCDecayMode
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//MCDecayMode*
//SMStorageHelper<MCDecayMode>::make( const MCDecayMode& iTempData ) const
//{
   //change this line if MCDecayMode does not have a copy constructor
//   return new MCDecayMode( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( MCDecayModeStorageHelper, MCDecayMode )

//#include "StorageManagement/Template/SMContentsBuiltIn.cc"
//template class SMContentsBuiltIn<STL_VECTOR( QQ_id )::iterator >;

//#include "StorageManagement/Template/SMContents.cc"
//template class SMContents<SMPtrHolder<SimpleHelicity*, SimpleHelicity>::const_iterator >;
//template class SMContents<SMPtrHolder<SimpleAngularHelicity*, SimpleAngularHelicity>::const_iterator >;

#include "StorageManagement/Template/SMMakeContents.cc"
template class SMMakeContents<SimpleHelicity**>;
template class SMMakeContents<SimpleAngularHelicity**>;


//------------------------------------------------------
