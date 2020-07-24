// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      DGConstMaterialPtrProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec 14 11:05:00 EST 1999
// $Id: DGConstMaterialPtrProxy.cc,v 1.2 2000/08/11 00:16:12 bkh Exp $
//
// Revision history
//
// $Log: DGConstMaterialPtrProxy.cc,v $
// Revision 1.2  2000/08/11 00:16:12  bkh
// Change a trivial message to DEBUG from INFO
//
// Revision 1.1.1.1  1999/12/15 18:35:50  bkh
// imported Geant3MaterialsMediaProd sources
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "Experiment/units.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAPtrTable.h"

#include "Geant3MaterialsMediaProd/DGConstMaterialPtrProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#include "Geant3Interface/G3iFortran.h"
#include "Geant3MaterialsMediaProd/G3iMakeMaterials.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kReport = "Geant3MaterialsMediaProd.DGConstMaterialPtrProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DGConstMaterialPtrProxy.cc,v 1.2 2000/08/11 00:16:12 bkh Exp $";
static const char* const kTagString = "$Name: v01_01_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
DGConstMaterialPtrProxy::DGConstMaterialPtrProxy()
   : m_ptrTable( new value_type )
{
   if ( 0 == m_ptrTable ) {
      report( EMERGENCY, kReport )
         << "Unable to allocate memory"
         << endl ;
      ::exit( 1 ) ;
   }

   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &DGConstMaterialPtrProxy::boundMethod, Stream::kBeginRun );
}

// DGConstMaterialPtrProxy::DGConstMaterialPtrProxy( const DGConstMaterialPtrProxy& iproxy )
// {
//   *this = iproxy;
// }

DGConstMaterialPtrProxy::~DGConstMaterialPtrProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const DGConstMaterialPtrProxy& DGConstMaterialPtrProxy::operator=( const DGConstMaterialPtrProxy& iproxy )
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
DGConstMaterialPtrProxy::invalidateCache()
{
   if ( 0 != m_ptrTable ) {
      (*m_ptrTable).eraseAll() ;
   }
}

const DGConstMaterialPtrProxy::value_type*
DGConstMaterialPtrProxy::faultHandler( const Record& iRecord,
				       const DataKey& iKey )
{
   // be assertive: table should be empty 
   // else it's a programming error
   assert( 0 == (*m_ptrTable).size() );

   // make calls to define GEANT materials & get list of names, indices

   report( DEBUG, kReport ) << "Here in faultHandler" << endl ;

   const STL_MAP( string, UInt16 )& stringIntMap
      ( G3iMakeMaterials::instance().stringIntMap() ) ;

   const STL_MAP( string, G3iMakeMaterials::VecWt )& wtdElt 
      ( G3iMakeMaterials::instance().wtdElt() ) ;

   // ---------- fill FAPtrTable with new items ----------------

   for( STL_MAP( string, UInt16 )::const_iterator iMap 
	   ( stringIntMap.begin() ) ;
	iMap != stringIntMap.end() ; ++iMap )
   {
      const string&  name  ( (*iMap).first  ) ;
      const FInteger index ( (*iMap).second ) ;

      static const UInt32 kG3BUFSIZE ( 100 ) ;      

      FChar gName[20]          ;
      FReal atomicWeight       ;
      FReal atomicNumber       ;
      FReal density            ;
      FReal radiationLength    ;
      FReal absorptionLength   ;
      FReal uBuf[ kG3BUFSIZE ] ;

      FInteger nBuf            ;

      static FInteger nameLength ( 20 ) ;

      gfmate_( index            , 
	       gName            , 
	       atomicWeight     , 
	       atomicNumber     ,
	       density          , 
	       radiationLength  , 
	       absorptionLength , 
	       uBuf             , 
	       nBuf             ,
	       nameLength        ) ;

      if( kG3BUFSIZE < nBuf )
      {
	 report( EMERGENCY, kReport ) 
	    << "Default buffer size overfilled, exiting" << endl ;
	 assert( false ) ;
	 ::exit( 1 ) ;
      }

      const DGMaterial::WeightType weightType  
	 ( 0 == nBuf ?
	   DGMaterial::kNumberOfAtoms : 
	   DGMaterial::kProportionByWeight ) ;

      DGMaterial* pMaterial = new DGMaterial( name                 ,
					      index                ,
					      weightType           ,
					      density*k_g_per_cm3  ,
					      radiationLength*k_cm   ) ;

      const G3iMakeMaterials::VecWt& vecWts 
	 ( (*wtdElt.find( name )).second ) ;

      float sumWt ( 0 ) ;
      for( G3iMakeMaterials::VecWt::const_iterator 
	      iV ( vecWts.begin() ) ; iV != vecWts.end() ; ++iV )
      {
	 pMaterial->addElement( (*iV).m_element , (*iV).m_weight );
	 sumWt +=  (*iV).m_weight ;
      }
      
      if(  0.000001 < fabs( sumWt - 1. ) )
      {
	 report( EMERGENCY, kReport ) << " For material = "
				      << name
				      << " sum of wts - " 
				      << sumWt
				      << ", exiting ..." 
				      << endl ;
	 assert( false ) ;
	 ::exit( 1 ) ;
      }

      DGConstMaterialPtr* newMat = new DGConstMaterialPtr ( pMaterial ) ;

      (*m_ptrTable).insert( newMat ) ;
   }

   return m_ptrTable ;
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
//DGConstMaterialPtrProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kReport) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< FAPtrTable< DGConstMaterialPtr > >;

PROXY_BIND_METHOD( DGConstMaterialPtrProxy )
//-----------------------------------------------


