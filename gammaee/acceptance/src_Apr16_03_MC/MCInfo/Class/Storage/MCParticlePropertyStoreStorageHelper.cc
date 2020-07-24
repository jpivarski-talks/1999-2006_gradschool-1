// -*- C++ -*-
//
// Package:     MCInfo
// Module:      MCParticlePropertyStoreStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: MCParticlePropertyStoreStorageHelper.cc,v 1.1 2001/12/19 18:20:08 lkg Exp $
//
// Revision history
//
// $Log: MCParticlePropertyStoreStorageHelper.cc,v $
// Revision 1.1  2001/12/19 18:20:08  lkg
// add storage helpers for particle properties
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <stack>
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "Experiment/units.h"

#include "MCInfo/Storage/MCParticlePropertyStoreStorageHelper.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/Storage/MCParticlePropDecayModeStorageInterface.h"
#include "MCInfo/Storage/DeliverDummyMCPPS.h"
#include "MCInfo/MCDecayTree/MCListItr.h"

#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMPackInfo.h" //defines sm_pack*
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMMakeContents.h"

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
class PropertyInsertIterator :
#if defined(OLD_ITERATOR_CLASSES_BUG)
   public output_iterator 
#else
   public iterator<output_iterator_tag, MCParticleProperty* >
#endif
{
   public:
      PropertyInsertIterator( MCParticlePropertyStore* theStore ) :
#if defined(OLD_ITERATOR_CLASSES_BUG)
	 output_iterator(),
#else
	 iterator<output_iterator_tag, MCParticleProperty* >(),
#endif
	 m_theStore( theStore ) {}
      typedef MCParticleProperty* value_type;
      PropertyInsertIterator& operator++() {return *this;}
      PropertyInsertIterator& operator*() {return *this;}
      void operator=( MCParticleProperty* aProperty) { 
	 m_theStore->addProperty_noCopy( aProperty );
      }
   private:
      MCParticlePropertyStore* m_theStore;
};

typedef MCListItr< STL_VECTOR(MCParticlePropDecayModeStorageInterface*)::iterator,
		   MCParticlePropDecayModeStorageInterface,
		   MCParticlePropDecayModeStorageInterface > interItr;

#if defined(NO_ITERATOR_TRAITS_BUG)
#include "StorageManagement/sm_iterator_traits.h"
template<>
class sm_iterator_traits< STL_VECTOR(MCParticlePropDecayModeStorageInterface)::iterator > {
   public:
      typedef MCParticlePropDecayModeStorageInterface value_type;
};
template<>
class sm_iterator_traits< STL_VECTOR(MCParticlePropDecayModeStorageInterface)::const_iterator > {
   public:
      typedef MCParticlePropDecayModeStorageInterface value_type;
};
#endif

static const char* const kFacilityString = "MCInfo.MCParticlePropertyStoreStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCParticlePropertyStoreStorageHelper.cc,v 1.1 2001/12/19 18:20:08 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCParticlePropertyStoreStorageHelper::MCParticlePropertyStoreStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &MCParticlePropertyStoreStorageHelper::deliverV1 );
}

// MCParticlePropertyStoreStorageHelper::MCParticlePropertyStoreStorageHelper( const MCParticlePropertyStoreStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//MCParticlePropertyStoreStorageHelper::~MCParticlePropertyStoreStorageHelper()
//{
//}

//
// assignment operators
//
// const MCParticlePropertyStoreStorageHelper& MCParticlePropertyStoreStorageHelper::operator=( const MCParticlePropertyStoreStorageHelper& rhs )
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
MCParticlePropertyStoreStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const MCParticlePropertyStore& iData ) 
{
   // store the version number and the particle properties without the
   // decay modes.  The consistency checks requires that the daughter
   // particles in a decay mode all have a property that exists.  For
   // complete safety, we must handle the decay modes after al the
   // properties have had their basic information stored
   iSink 
      << SM_VAR( iData, version )
      << sm_field( "ParticlePropertyList", 
		   sm_contents( iData.begin(), iData.end() ) )
      ;

   // create a container of MCParticlePropDecayModeStorageInterface
   // objects, to fool the storage system into thinking there is a
   // store of objects that hold the decay modes
   STL_VECTOR(MCParticlePropDecayModeStorageInterface*) dmInterface;

   MCPPStoreItr pEnd = iData.end();
   for ( MCPPStoreItr pItr = iData.begin(); pItr != pEnd; ++pItr ) {
      // only do something for particle properties that have decay modes
      if ( ! pItr->empty() ) {
	 // cast away const
	 MCParticleProperty* prop = 
	    const_cast<MCParticleProperty*>( &(*pItr) );
	 dmInterface.push_back(new MCParticlePropDecayModeStorageInterface(prop));
      }
   }
   // now "store" the interface
   interItr begin( dmInterface.begin() );
   interItr end( dmInterface.end() );
   iSink
      << sm_field( "decayModeInterface",
		   sm_contents( begin, end ) )
      ;
}

MCParticlePropertyStore* 
MCParticlePropertyStoreStorageHelper::deliverV1( SMSourceStream& iSource )
{
   Integer version;

   // read the straightforward information
   iSource 
      >> version
      ;

   // create an MCParticlePropertyStore with its version number
   MCParticlePropertyStore* tmpStorePtr = make( MCParticlePropertyStore() );
   tmpStorePtr->setVersion( version );
   m_currentStore = tmpStorePtr;

   // create an insert iterator that uses the "addProperty" command to
   // add new properties to the store
   PropertyInsertIterator propertyInsertItr( tmpStorePtr );

   // now make all of the particle properties
   iSource
      >> sm_make_contents( propertyInsertItr )
      ;

   // now retrieve the decay modes.  We will do this by creating an
   // intermediate vector of  MCParticlePropDecayModeStorageInterface
   // objects
   STL_VECTOR(MCParticlePropDecayModeStorageInterface*) dmInterface;
   back_insert_iterator<STL_VECTOR(MCParticlePropDecayModeStorageInterface*)>
      interfaceInsertItr( dmInterface );

   iSource
      >> sm_make_contents( interfaceInsertItr )
      ;

   // we must rid ourselves of the interface ojects
   STL_VECTOR(MCParticlePropDecayModeStorageInterface*)::iterator dmBegin = dmInterface.begin();
   STL_VECTOR(MCParticlePropDecayModeStorageInterface*)::iterator dmEnd   = dmInterface.end();
   for(  STL_VECTOR(MCParticlePropDecayModeStorageInterface*)::iterator dmItr = dmBegin;
	 dmItr != dmEnd; ++dmItr ) {
      delete *dmItr;
   }

   return tmpStorePtr; 
}

//
// const member functions
//
const MCParticlePropertyStore& 
MCParticlePropertyStoreStorageHelper::getDefault() const
{
   return DeliverDummyMCPPS::instance().dummyMCParticlePropertyStore();
}

DABoolean 
MCParticlePropertyStoreStorageHelper::compare( 
   const MCParticlePropertyStore* iNewData, 
   const MCParticlePropertyStore& iOldData ) const
{
   return (*iNewData == iOldData ) ;
}

MCParticlePropertyStore& 
MCParticlePropertyStoreStorageHelper::currentPropertyStore() {
   return *m_currentStore;
}

//
// static member functions
//

//MCParticlePropertyStore*
//SMStorageHelper<MCParticlePropertyStore>::make( const MCParticle& iTempData ) const
//{
   //change this line if MCParticle does not have a copy constructor
//   return new MCParticle( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( MCParticlePropertyStoreStorageHelper, 
			 MCParticlePropertyStore )

typedef MCParticlePropertyStore _store_element_;
#include "StorageManagement/instantiate_proxyhelper.h"

#include "StorageManagement/Template/SMContents.cc"
template class SMContents<MCPPStoreItr>;
template class SMContents< interItr >;

#include "StorageManagement/Template/SMMakeContents.cc"
template class SMMakeContents<PropertyInsertIterator >;
template class SMMakeContents<back_insert_iterator<STL_VECTOR(MCParticlePropDecayModeStorageInterface*)> >;
//------------------------------------------------------
