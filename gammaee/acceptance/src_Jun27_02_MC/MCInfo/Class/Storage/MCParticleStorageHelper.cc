// -*- C++ -*-
//
// Package:     MCInfo
// Module:      MCParticleStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: MCParticleStorageHelper.cc,v 1.6 2002/02/05 03:15:23 lkg Exp $
//
// Revision history
//
// $Log: MCParticleStorageHelper.cc,v $
// Revision 1.6  2002/02/05 03:15:23  lkg
// extract property store directly in case MCParticle not in a MCDecayTree
//
// Revision 1.5  2001/12/19 18:10:38  lkg
// white space cleanup or other minor tweaks
//
// Revision 1.4  2000/07/07 15:01:45  lkg
// add various include <stack> to fix OSF compilation
//
// Revision 1.3  2000/07/07 01:41:33  lkg
// Bug fix for unpacking particles w/ multiple vertices: need to use a stack to hold the current particle having vertices added
//
// Revision 1.2  2000/05/04 17:54:00  cdj
// DummyInsertIterator now inherits from proper iterator class
//
// Revision 1.1  2000/05/01 22:40:24  lkg
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
// don't allow this SMStorageHelper to be included to stop auto instantiation
// (that is currently ignorning specialization of the "make" function for
// MCVertex)
#define STORAGEMANAGEMENT_SMSTORAGEHELPER_CC
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/Storage/MCParticleStorageHelper.h"
#include "MCInfo/Storage/MCVertexStorageHelper.h"
#include "MCInfo/Storage/MCDecayTreeStorageHelper.h"
#include "MCInfo/Storage/DeliverDummyMCDT.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMPackInfo.h" //defines sm_pack*
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMMakeContents.h"

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
class DummyInsertIterator :
#if defined(OLD_ITERATOR_CLASSES_BUG)
   public output_iterator 
#else
   public iterator<output_iterator_tag, MCVertex* >
#endif
{
   public:
     typedef MCVertex* value_type;
     DummyInsertIterator& operator++() {return *this;}
     DummyInsertIterator& operator*() {return *this;}
     void operator=( MCVertex* ) {}
};


static const char* const kFacilityString = "MCInfo.MCParticleStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCParticleStorageHelper.cc,v 1.6 2002/02/05 03:15:23 lkg Exp $";
static const char* const kTagString = "$Name: v03_02_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCParticleStorageHelper::MCParticleStorageHelper( 
   MCDecayTreeStorageHelper& theMCDecayTreeStorageHelper,
   MCVertexStorageHelper&    theMCVertexStorageHelper ) :
   m_dkTreeStorageHelper( &theMCDecayTreeStorageHelper ),
   m_vtxStorageHelper(    &theMCVertexStorageHelper )
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &MCParticleStorageHelper::deliverV1 );
}

// MCParticleStorageHelper::MCParticleStorageHelper( const MCParticleStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//MCParticleStorageHelper::~MCParticleStorageHelper()
//{
//}

//
// assignment operators
//
// const MCParticleStorageHelper& MCParticleStorageHelper::operator=( const MCParticleStorageHelper& rhs )
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
MCParticleStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const MCParticle& iData ) 
{
   iSink 
      << sm_pack( sm_field("qqId", iData.properties().QQId()), -500, +1000, 1)
      << sm_pack( sm_field("px", iData.lorentzMomentum().px()), -32*k_GeV, +32*k_GeV, 1*k_keV )
      << sm_pack( sm_field("py", iData.lorentzMomentum().py()), -32*k_GeV, +32*k_GeV, 1*k_keV )
      << sm_pack( sm_field("pz", iData.lorentzMomentum().pz()), -32*k_GeV, +32*k_GeV, 1*k_keV )
      << sm_pack( sm_field("e",  iData.lorentzMomentum().e() ), 0, +32*k_GeV, 1*k_keV )
      << sm_pack( sm_field("x",  iData.position().x()), -3*k_m, 3*k_m, 1*k_um )
      << sm_pack( sm_field("y",  iData.position().y()), -3*k_m, 3*k_m, 1*k_um )
      << sm_pack( sm_field("z",  iData.position().z()), -3*k_m, 3*k_m, 1*k_um )
      << sm_pack( SM_VAR( iData, helicity ), -100, +100, 0.5 )
      << sm_field( "vertexList", 
		   sm_contents( iData.vBegin(), iData.vEnd() ) )
      ;
}

MCParticle* 
MCParticleStorageHelper::deliverV1( SMSourceStream& iSource )
{
   int qqId; 
   double px;
   double py;
   double pz;
   double e;
   double x;
   double y;
   double z;

   Helicity         helicity;

   // read the straightforward information
   iSource 
      >> qqId 
      >> px
      >> py
      >> pz
      >> e
      >> x
      >> y
      >> z
      >> helicity
      ;
   
   // convert position,four momenta components into objects
   HepLorentzVector lorentzMomentum( px, py, pz, e );
   HepPoint3D       position( x, y, z );
   
   // get the particle property
   const Record& thisRecord = iSource.record();
   FAItem< MCParticlePropertyStore > ppStore;
   extract( thisRecord.frame().record(Stream::kPhysics), 
	    ppStore, 
	    "UserMCParticleProperties" );
   const MCParticlePropertyStore& theStore( *ppStore );

   // create an MCParticle with everything but its interactions
   MCParticle* tmpPartPtr = make( MCParticle(
      theStore[qqId],
      lorentzMomentum,
      position
      ) );
   tmpPartPtr->setHelicity( helicity );

   // create a dummy insert iterator that does nothing.
   // The MCVertex newVertex command looks after (via the constructor) 
   // attaching itself its parent particle, so we don't need the overhead
   // of using a real container here.  Use DummyInsertIterator defined
   // above
   DummyInsertIterator vertexInsertItr;

   // inform the MCVertex storage helper of this particle, so that
   // the MCVertex constructor attaches the vertex properly
   m_vtxStorageHelper->pushParticlePtr( tmpPartPtr );

   // now make the vertices
   iSource
      >> sm_make_contents( vertexInsertItr )
      ;

   // inform the MCVertex storage that we are done attaching
   // vertices to this particle, so it should be popped off of
   // the stack of pointers
   m_vtxStorageHelper->popParticlePtr();

   return tmpPartPtr; 
}

//
// const member functions
//
const MCParticle& 
MCParticleStorageHelper::getDefault() const
{
   return DeliverDummyMCDT::instance().dummyMCParticle();
}

DABoolean 
MCParticleStorageHelper::compare( 
   const MCParticle* iNewData, 
   const MCParticle& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for MCParticle
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//MCParticle*
//SMStorageHelper<MCParticle>::make( const MCParticle& iTempData ) const
//{
   //change this line if MCParticle does not have a copy constructor
//   return new MCParticle( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( MCParticleStorageHelper, MCParticle )

#include "StorageManagement/Template/SMContents.cc"
template class SMContents<MCParticle::const_vIterator >;

#include "StorageManagement/Template/SMMakeContents.cc"
template class SMMakeContents<DummyInsertIterator >;

//------------------------------------------------------
