// -*- C++ -*-
//
// Package:     <Geant3MaterialsMediaProd>
// Module:      G3iTrackingMediumProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec 14 11:06:36 EST 1999
// $Id: G3iTrackingMediumProxy.cc,v 1.2 2001/03/15 21:51:22 bkh Exp $
//
// Revision history
//
// $Log: G3iTrackingMediumProxy.cc,v $
// Revision 1.2  2001/03/15 21:51:22  bkh
// Get Magnetic Field from Start Run
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
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAPtrTable.h"

#include "Geant3MaterialsMediaProd/G3iTrackingMediumProxy.h"

#include "Geant3MaterialsMediaProd/G3iMakeTrackingMedia.h"

#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#include "MagField/MagneticField.h"

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
static const char* const kReport = "Geant3MaterialsMediaProd.G3iTrackingMediumProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: G3iTrackingMediumProxy.cc,v 1.2 2001/03/15 21:51:22 bkh Exp $";
static const char* const kTagString = "$Name: v01_01_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
G3iTrackingMediumProxy::G3iTrackingMediumProxy()
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
   //bind( &G3iTrackingMediumProxy::boundMethod, Stream::kBeginRun );
}

// G3iTrackingMediumProxy::G3iTrackingMediumProxy( const G3iTrackingMediumProxy& iproxy )
// {
//   *this = iproxy;
// }

G3iTrackingMediumProxy::~G3iTrackingMediumProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const G3iTrackingMediumProxy& G3iTrackingMediumProxy::operator=( const G3iTrackingMediumProxy& iproxy )
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
G3iTrackingMediumProxy::invalidateCache()
{
   if ( 0 != m_ptrTable ) {
      (*m_ptrTable).eraseAll() ;
   }
}

const G3iTrackingMediumProxy::value_type*
G3iTrackingMediumProxy::faultHandler( const Record& iRecord,
				      const DataKey& iKey )
{
   // be assertive: table should be empty 
   // else it's a programming error
   assert( 0 == (*m_ptrTable).size() );

   // ---------- fill FAPtrTable with new items ----------------

   FAItem< MagneticField >                                magField   ;
   extract( iRecord.frame().record( Stream::kStartRun ) , magField ) ;

   const double solField ( magField->BField().z() ) ;


   const STL_MAP( string, UInt16 )& stringIntMap
      ( G3iMakeTrackingMedia::instance( solField ).stringIntMap() ) ;

   for ( STL_MAP( string, UInt16 )::const_iterator
	    ip ( stringIntMap.begin() ) ; ip != stringIntMap.end() ; ++ ip )
   {
      const string& name  ( (*ip).first  ) ;

      const UInt16  index ( (*ip).second ) ;

      G3iTrackingMedium* tmp ( new G3iTrackingMedium( name, index ) ) ;

      if ( 0 == tmp ) 
      {
         report( EMERGENCY, kReport )
            << "No memory to allocate another composite object"
            << endl ;
         ::exit( 1 ) ;
      }
      
      (*m_ptrTable).insert( tmp ) ;
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
//G3iTrackingMediumProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kReport) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< FAPtrTable< G3iTrackingMedium > >;

PROXY_BIND_METHOD( G3iTrackingMediumProxy )
//-----------------------------------------------


