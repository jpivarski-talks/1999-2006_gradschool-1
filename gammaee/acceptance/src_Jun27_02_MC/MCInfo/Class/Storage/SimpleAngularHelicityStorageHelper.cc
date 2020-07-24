// -*- C++ -*-
//
// Package:     MCInfo
// Module:      SimpleAngularHelicityStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: SimpleAngularHelicityStorageHelper.cc,v 1.1 2001/12/19 18:20:09 lkg Exp $
//
// Revision history
//
// $Log: SimpleAngularHelicityStorageHelper.cc,v $
// Revision 1.1  2001/12/19 18:20:09  lkg
// add storage helpers for particle properties
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
#include "MCInfo/Storage/SimpleAngularHelicityStorageHelper.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMPackInfo.h" //defines sm_pack*
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMContentsBuiltIn.h"
#include "StorageManagement/SMMakeContents.h"
#include "StorageManagement/SMFillContents.h"

#include "Experiment/units.h"

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

static const char* const kFacilityString = "MCInfo.SimpleAngularHelicityStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SimpleAngularHelicityStorageHelper.cc,v 1.1 2001/12/19 18:20:09 lkg Exp $";
static const char* const kTagString = "$Name: v03_02_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
SimpleAngularHelicityStorageHelper::SimpleAngularHelicityStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &SimpleAngularHelicityStorageHelper::deliverV1 );
}

// SimpleAngularHelicityStorageHelper::SimpleAngularHelicityStorageHelper( const SimpleAngularHelicityStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//SimpleAngularHelicityStorageHelper::~SimpleAngularHelicityStorageHelper()
//{
//}

//
// assignment operators
//
// const SimpleAngularHelicityStorageHelper& SimpleAngularHelicityStorageHelper::operator=( const SimpleAngularHelicityStorageHelper& rhs )
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
SimpleAngularHelicityStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const SimpleAngularHelicity& iData ) 
{

   // simplify structures into three flat containers
   STL_VECTOR( double ) helicities;
   STL_VECTOR( int ) nTerms;
   STL_VECTOR( double ) cosThetaWeights;

   for ( int config = 0; config != iData.numberOfConfigs(); ++config ) {
      const SimpleAngularHelicity::HelicitySpec& aSpec( iData[config] );
      helicities.push_back( aSpec.first );
      nTerms.push_back( aSpec.second.size() );
      for ( SimpleAngularHelicity::CosThetaDep::const_iterator cItr = aSpec.second.begin();
	    cItr != aSpec.second.end(); ++cItr ) {
	 cosThetaWeights.push_back( *cItr );
      }

   }

   // now store the containers
   // use const versions to match up to the StorageManagement versions
   const STL_VECTOR( double )& cHelis( helicities );
   const STL_VECTOR( int )& cTerms( nTerms );
   const STL_VECTOR( double )& cWeights( cosThetaWeights );
   iSink
      << sm_field("helicities",
		  sm_contents_builtin( cHelis.begin(), cHelis.end() ) )
      << sm_field("number_cosThetaDep_terms",
		  sm_contents_builtin( cTerms.begin(), cTerms.end() ) )
      << sm_field("cosThetaWeights",
		  sm_contents_builtin( cWeights.begin(), cWeights.end() ) )
      ;
}

SimpleAngularHelicity* 
SimpleAngularHelicityStorageHelper::deliverV1( SMSourceStream& iSource )
{
   
   // retrieve the intermediate containers
   STL_VECTOR( double ) helicities;
   back_insert_iterator<STL_VECTOR( double )> helInsertItr( helicities );
   STL_VECTOR( int ) nTerms;
   back_insert_iterator<STL_VECTOR( int )> termsInsertItr( nTerms );
   STL_VECTOR( double ) cosThetaWeights;
   back_insert_iterator<STL_VECTOR( double )> weightInsertItr( cosThetaWeights );
   iSource
      >> sm_fill_contents( helInsertItr )
      >> sm_fill_contents( termsInsertItr )
      >> sm_fill_contents( weightInsertItr )
      ;

   // now recreate the angular helicity structures
   SimpleAngularHelicity* tmpAng = make( SimpleAngularHelicity() );

   STL_VECTOR( double )::const_iterator weight = cosThetaWeights.begin();
   STL_VECTOR( int )::const_iterator thisN = nTerms.begin();

   for ( STL_VECTOR( double )::const_iterator helicity = helicities.begin();
	 helicity != helicities.end(); ++helicity ) {
      
      SimpleAngularHelicity::CosThetaDep thisCosTheta;

      int limit = *thisN;
      ++thisN;

      for ( int term = 0; term != limit; ++term ) {
	 thisCosTheta.push_back( *weight );
	 ++weight;
      }

      tmpAng->addHelicityState( *helicity, thisCosTheta );
   }

   return tmpAng; 
}

//
// const member functions
//
const SimpleAngularHelicity& 
SimpleAngularHelicityStorageHelper::getDefault() const
{
   SimpleAngularHelicity* tmpAng = new SimpleAngularHelicity();
   SimpleAngularHelicity::CosThetaDep cosList;
   cosList.push_back( 1.0 );
   cosList.push_back( -2.0 );
   cosList.push_back( 3.0 );
   tmpAng->addHelicityState( 0.5, cosList );
   return *tmpAng;
}

DABoolean 
SimpleAngularHelicityStorageHelper::compare( 
   const SimpleAngularHelicity* iNewData, 
   const SimpleAngularHelicity& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for SimpleAngularHelicity
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//SimpleAngularHelicity*
//SMStorageHelper<SimpleAngularHelicity>::make( const SimpleAngularHelicity& iTempData ) const
//{
   //change this line if SimpleAngularHelicity does not have a copy constructor
//   return new SimpleAngularHelicity( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( SimpleAngularHelicityStorageHelper, SimpleAngularHelicity )

//------------------------------------------------------
