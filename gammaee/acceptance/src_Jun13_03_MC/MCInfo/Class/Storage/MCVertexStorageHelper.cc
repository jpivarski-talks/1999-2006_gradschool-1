// -*- C++ -*-
//
// Package:     MCInfo
// Module:      MCVertexStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: MCVertexStorageHelper.cc,v 1.5 2001/12/19 18:10:37 lkg Exp $
//
// Revision history
//
// $Log: MCVertexStorageHelper.cc,v $
// Revision 1.5  2001/12/19 18:10:37  lkg
// white space cleanup or other minor tweaks
//
// Revision 1.4  2001/01/16 04:20:00  lkg
// remove instantiation of SMFillContents<back_insert_iterator<STL_VECTOR( QQ_id )> >, which is now instantiated in StorageManagement
//
// Revision 1.3  2000/07/07 01:41:33  lkg
// Bug fix for unpacking particles w/ multiple vertices: need to use a stack to hold the current particle having vertices added
//
// Revision 1.2  2000/05/05 20:01:59  cdj
// manual instantiations now use correct 'const'ness of parameter
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
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#include <stack>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// don't allow this SMStorageHelper to be included to stop auto instantiation
// (that is currently ignorning specialization of the "make" function for
// MCVertex)
#define STORAGEMANAGEMENT_SMSTORAGEHELPER_CC

// user include files
#include "MCInfo/Storage/MCParticleStorageHelper.h"
#include "MCInfo/Storage/MCVertexStorageHelper.h"
#include "MCInfo/Storage/MCDecayTreeStorageHelper.h"
#include "MCInfo/Storage/DeliverDummyMCDT.h"

#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMPackInfo.h" //defines sm_pack*
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMContentsBuiltIn.h"
#include "StorageManagement/SMMakeContents.h"
#include "StorageManagement/SMFillContents.h"

#include "Experiment/units.h"
#include "Experiment/report.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#include <stack>

//
// constants, enums and typedefs
//
/*
class StorageBackInsertItr : public  back_insert_iterator<STL_VECTOR( MCParticle* )>
{
  public:
     typedef MCParticle value_type;
     StorageBackInsertItr( STL_VECTOR( MCParticle* )& storageContainer ) :
	back_insert_iterator<STL_VECTOR( MCParticle* )>( storageContainer ) {}
};
*/
	
static const char* const kFacilityString = "MCInfo.MCVertexStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCVertexStorageHelper.cc,v 1.5 2001/12/19 18:10:37 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
MCVertexStorageHelper::MCVertexStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &MCVertexStorageHelper::deliverV1 );
}

// MCVertexStorageHelper::MCVertexStorageHelper( const MCVertexStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//MCVertexStorageHelper::~MCVertexStorageHelper()
//{
//}

//
// assignment operators
//
// const MCVertexStorageHelper& MCVertexStorageHelper::operator=( const MCVertexStorageHelper& rhs )
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
MCVertexStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const MCVertex& iData ) 
{
   iSink 
      << sm_pack( sm_field( "x",  iData.position().x() ), -3*k_m, 3*k_m, 1*k_um )
      << sm_pack( sm_field( "y",  iData.position().y() ), -3*k_m, 3*k_m, 1*k_um )
      << sm_pack( sm_field( "z",  iData.position().z() ), -3*k_m, 3*k_m, 1*k_um )
      << sm_pack( sm_field( "time", iData.time() ), 0, 4.e6, 0.1 )
      << sm_pack( sm_field( "px", iData.localParentMomentum().px() ), -32*k_GeV, +32*k_GeV, 1*k_keV )
      << sm_pack( sm_field( "py", iData.localParentMomentum().py() ), -32*k_GeV, +32*k_GeV, 1*k_keV )
      << sm_pack( sm_field( "pz", iData.localParentMomentum().pz() ), -32*k_GeV, +32*k_GeV, 1*k_keV )
      << sm_pack( sm_field( "e",  iData.localParentMomentum().e()  ), 0, +32*k_GeV, 1*k_keV )
      << sm_pack( sm_field( "type", iData.type() ), 0, 100, 1 )
      ;

   // save the specific types for this decay so that we can
   // always determine the correct decay mode (sometimes
   // the mode is indeterminate, and we cannot match decay mode
   // to the final list of particles).
   STL_VECTOR( QQ_id ) packList;
   if ( iData.type() == kiDecay ) {
      packList = iData.decayMode().childList();
   } else {
      packList.clear();
   }

   iSink 
     << SMPackInfoFixedTemplate<Integer>( 
              sm_field( "decayModechildTypeList", 
			sm_contents_builtin( packList.begin(), 
					     packList.end() ) ), 
	      -500, +1000, 1 )
     ;

   // now save the particles
   iSink
     << sm_field( "particleList", 
		  sm_contents( iData.pBegin(), iData.pEnd() ) )
     ;
}

MCVertex* 
MCVertexStorageHelper::deliverV1( SMSourceStream& iSource )
{
   double x;
   double y;
   double z;
   Double time;
   double px;
   double py;
   double pz;
   double e;
   Count type;

   // read the straightforward information
   iSource 
      >> x
      >> y
      >> z
      >> time
      >> px
      >> py
      >> pz
      >> e
      >> type
      ;
   
   // convert position,four momenta components into objects
   HepLorentzVector localParentMomentum( px, py, pz, e );
   HepPoint3D       position( x, y, z );
   
#if defined( LKG_DEBUG )
   report( INFO, kFacilityString )
      << "Unpacking vertex, type " << type << endl;
   report( INFO, kFacilityString )
      << "Particle pointer value is " << m_particlePtr.top() << endl;
   if ( m_particlePtr.top() != 0 ) {
      report( INFO, kFacilityString )
	 << " will attach to particle" << '\n'
	 << *m_particlePtr.top()
	 << endl;
   }
#endif

   // create an MCVertex with everything but its children
   MCVertex* tmpVertPtr = MCVertex::newVertex(
      type,
      m_particlePtr.top(),
      position,
      time,
      localParentMomentum
      );

   // Unpack the list of daughters that would have appeared in decay.dec
   // for a decay.  This list will be empty for decays that are not
   // kiDecay
   STL_VECTOR( QQ_id ) cTypeList;
   back_insert_iterator<STL_VECTOR( QQ_id )> cTypeInsertItr( cTypeList );
   iSource
      >> sm_fill_contents( cTypeInsertItr )
      ;
   if ( type == kiDecay ) {
      if( cTypeList.empty() ) {
	 // assume the decay mode is unknown
	 tmpVertPtr->setDecayMode(MCDecayMode::unknown() );
      } else {
	 MCParticleProperty::const_iterator theDecayMode =
	    m_particlePtr.top()->properties().findDecayMode( cTypeList );
 
	 if( m_particlePtr.top()->properties().end() != theDecayMode ) {
	    tmpVertPtr->setDecayMode( *theDecayMode );
	 } else {
	    ostream& tempReport = report(ERROR,kFacilityString) ;
	    tempReport <<"unable to find decay mode for decay vertex of particle " <<*(m_particlePtr.top()) <<endl;
	 }
      }
   }

   // create the temporary vector-related items needed to get the
   // daughters out of storage.  
   STL_VECTOR( MCParticle* ) daughters; 
   back_insert_iterator<STL_VECTOR( MCParticle* )> particleInsertItr( daughters );
//   StorageBackInsertItr particleInsertItr( daughters );

   // now make the particles
   iSource
      >> sm_make_contents( particleInsertItr )
      ;

   // attach the daughters to the vertex
   tmpVertPtr->setChildren( daughters );

   // done!
   return tmpVertPtr; 
}

void
MCVertexStorageHelper::pushParticlePtr( MCParticle* workingParticle )
{
  m_particlePtr.push( workingParticle );
}

void
MCVertexStorageHelper::popParticlePtr()
{
  m_particlePtr.pop();
}

//
// const member functions
//
const MCVertex& 
MCVertexStorageHelper::getDefault() const
{
   //give constructor unique values to allow test of store and deliver 
   // functions

   return DeliverDummyMCDT::instance().dummyMCVertex();
}

DABoolean 
MCVertexStorageHelper::compare( 
   const MCVertex* iNewData, 
   const MCVertex& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for MCVertex
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//------------------------------------------------------
// DO NOT DELETE 
template class stack< MCParticle*, deque< MCParticle* > >;

#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( MCVertexStorageHelper, MCVertex )

#include "StorageManagement/Template/SMContents.cc"
template class SMContents<MCVertex::const_pIterator >;

#include "StorageManagement/Template/SMMakeContents.cc"
//template class SMMakeContents<StorageBackInsertItr >;
template class SMMakeContents<back_insert_iterator<STL_VECTOR( MCParticle* )> >;

#include "StorageManagement/Template/SMContentsBuiltIn.cc"
template class SMContentsBuiltIn<STL_VECTOR( QQ_id )::iterator >;

//#include "StorageManagement/Template/SMFillContents.cc"
//template class SMFillContents<StorageBackInsertItr >;
//template class SMFillContents<back_insert_iterator<STL_VECTOR( QQ_id )> >;
//------------------------------------------------------
