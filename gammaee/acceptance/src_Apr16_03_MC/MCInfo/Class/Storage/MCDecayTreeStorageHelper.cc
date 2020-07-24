// -*- C++ -*-
//
// Package:     MCInfo
// Module:      MCDecayTreeStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: MCDecayTreeStorageHelper.cc,v 1.4 2002/06/04 18:56:04 lkg Exp $
//
// Revision history
//
// $Log: MCDecayTreeStorageHelper.cc,v $
// Revision 1.4  2002/06/04 18:56:04  lkg
// replaced SUNCC flags with specific bug flags
//
// Revision 1.3  2000/07/07 15:01:43  lkg
// add various include <stack> to fix OSF compilation
//
// Revision 1.2  2000/05/05 20:01:58  cdj
// manual instantiations now use correct 'const'ness of parameter
//
// Revision 1.1  2000/05/01 22:40:23  lkg
// added storage helpers to repository
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
#include <stack>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "MCInfo/Storage/DeliverDummyMCDT.h"
#include "MCInfo/Storage/MCDecayTreeStorageHelper.h"
#include "MCInfo/Storage/MCVertexStorageHelper.h"
#include "MCInfo/Storage/MCDecayTreeStorageHelper.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMPackInfo.h" //defines sm_pack*
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMMakeContents.h"

#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"

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
template<class T>
class PtrInsertItr
{
   public:
     PtrInsertItr( T** iValue ) : m_value(iValue) {}
     typedef T value_type;
     PtrInsertItr<T>& operator++() {return *this;}
     PtrInsertItr& operator*() {return *this;}
     void operator=( T* iValue) { *m_value = iValue; }
   private:
     T** m_value;
};

static const char* const kFacilityString = "MCInfo.MCDecayTreeStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCDecayTreeStorageHelper.cc,v 1.4 2002/06/04 18:56:04 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCDecayTreeStorageHelper::MCDecayTreeStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &MCDecayTreeStorageHelper::deliverV1 );
}

// MCDecayTreeStorageHelper::MCDecayTreeStorageHelper( const MCDecayTreeStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//MCDecayTreeStorageHelper::~MCDecayTreeStorageHelper()
//{
//}

//
// assignment operators
//
// const MCDecayTreeStorageHelper& MCDecayTreeStorageHelper::operator=( const MCDecayTreeStorageHelper& rhs )
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
MCDecayTreeStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const MCDecayTree& iData ) 
{
   iSink 
     << sm_field( "topParticle",
		  sm_contents( &(iData.topParticle()), 
			       (&(iData.topParticle()))+1 ) )
      ;
}

MCDecayTree* 
MCDecayTreeStorageHelper::deliverV1( SMSourceStream& iSource )
{
   const Record& thisRecord = iSource.record();
   FAItem< MCParticlePropertyStore > ppStore;
   extract( thisRecord.frame().record(Stream::kPhysics), 
	    ppStore, 
	    "UserMCParticleProperties" );
   m_propertyStore = &(*ppStore);

   // get the topmost Particle
   MCParticle* topParticle[1];
#if defined(USE_STORAGE_MANAGER_V03_12_01)
   PtrInsertItr<MCParticle> insertItr( &(topParticle[0] ) );
#else
   MCParticle** insertItr( &(topParticle[0]) );
#endif
   iSource 
     >> sm_make_contents( insertItr )
     ;
   
   return make( MCDecayTree( 
      topParticle[0]
      ) );
}

//
// const member functions
//
const MCDecayTree& 
MCDecayTreeStorageHelper::getDefault() const
{
   //give constructor unique values to allow test of store and deliver 
   // functions
   return DeliverDummyMCDT::instance().dummyMCDecayTree();
}

DABoolean 
MCDecayTreeStorageHelper::compare( 
   const MCDecayTree* iNewData, 
   const MCDecayTree& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for MCDecayTree
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//MCDecayTree*
//SMStorageHelper<MCDecayTree>::make( const MCDecayTree& iTempData ) const
//{
// //change this line if MCDecayTree does not have a copy constructor
//   return new MCDecayTree( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( MCDecayTreeStorageHelper, MCDecayTree )

typedef MCDecayTree _store_element_;
#include "StorageManagement/instantiate_proxyhelper.h"

#include "StorageManagement/Template/SMContents.cc"
#if defined(NO_ITERATOR_TRAITS_BUG)
//need an **different than CDJ's** iterator traits
template<>
struct iterator_traits<const MCParticle*> {
      typedef MCParticle value_type;
};
template<>
struct iterator_traits<MCParticle*> {
      typedef MCParticle value_type;
};
#endif
template class SMContents<const MCParticle* >;

#include "StorageManagement/Template/SMMakeContents.cc"
#if defined(USE_STORAGE_MANAGER_V03_12_01)
template class SMMakeContents<PtrInsertItr<MCParticle> >;
#else
#if defined(NO_ITERATOR_TRAITS_BUG)
//need an **different than CDJ's** iterator traits
template<>
struct iterator_traits<const MCParticle**> {
      typedef MCParticle* value_type;
};
template<>
struct iterator_traits<MCParticle**> {
      typedef MCParticle* value_type;
};
#endif
template class SMMakeContents<MCParticle** >;
#endif

//------------------------------------------------------
