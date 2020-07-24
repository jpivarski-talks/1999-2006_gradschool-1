// -*- C++ -*-
//
// Package:     MCInfo
// Module:      SimpleHelicityStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: SimpleHelicityStorageHelper.cc,v 1.1 2001/12/19 18:20:10 lkg Exp $
//
// Revision history
//
// $Log: SimpleHelicityStorageHelper.cc,v $
// Revision 1.1  2001/12/19 18:20:10  lkg
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
#include "MCInfo/Storage/SimpleHelicityStorageHelper.h"
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

static const char* const kFacilityString = "MCInfo.SimpleHelicityStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SimpleHelicityStorageHelper.cc,v 1.1 2001/12/19 18:20:10 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
SimpleHelicityStorageHelper::SimpleHelicityStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &SimpleHelicityStorageHelper::deliverV1 );
}

// SimpleHelicityStorageHelper::SimpleHelicityStorageHelper( const SimpleHelicityStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//SimpleHelicityStorageHelper::~SimpleHelicityStorageHelper()
//{
//}

//
// assignment operators
//
// const SimpleHelicityStorageHelper& SimpleHelicityStorageHelper::operator=( const SimpleHelicityStorageHelper& rhs )
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
SimpleHelicityStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const SimpleHelicity& iData ) 
{
   // create a container of the daughterNames from the 1st list
   STL_VECTOR( string ) names;
   const SimpleHelicity::ChildHelicities& firstHel = iData[0].helicities;
   for ( SimpleHelicity::ChildHelicities::const_iterator hItr = firstHel.begin(); 
	 hItr != firstHel.end(); ++hItr ) {
      names.push_back( (*hItr).first );
   }

   // create a container of the likelihoods for each configuration,
   // and a container of the helicity of each daughter in each configuration
   STL_VECTOR( double ) likelihoods;
   STL_VECTOR( double ) helicities;
   for ( int config = 0; config != iData.numberOfConfigs(); ++config ) {
      const SimpleHelicity::HelicityConfig& theConfig( iData[config] );
      
      likelihoods.push_back( theConfig.configProbability );
      
      STL_VECTOR( string )::const_iterator begin = names.begin();
      STL_VECTOR( string )::const_iterator end   = names.end();
      for ( STL_VECTOR( string )::const_iterator daughter = begin;
	    daughter != end;
	    ++daughter ) {
	 SimpleHelicity::ChildHelicities::const_iterator configPair
	    = theConfig.helicities.find( *daughter );
	 helicities.push_back( (*configPair).second );
      }
   }

   // write the actual info out
   // use a const reference to match the
   const STL_VECTOR( string )& cNames( names );
   const STL_VECTOR( double )& cLikes( likelihoods );
   const STL_VECTOR( double )& cHelis( helicities );
   iSink
      << sm_field( "names", 
		   sm_contents_builtin( cNames.begin(), cNames.end() ) )
      << sm_field( "likelihoods",
		   sm_contents_builtin( cLikes.begin(), cLikes.end() ) )
      << sm_field( "helicities",
		   sm_contents_builtin( cHelis.begin(), cHelis.end() ) )
      ;
}

SimpleHelicity* 
SimpleHelicityStorageHelper::deliverV1( SMSourceStream& iSource )
{
   
   // retrieve the names
   STL_VECTOR( string ) names;
   back_insert_iterator<STL_VECTOR( string )> nameInsertItr( names );
   iSource
      >> sm_fill_contents( nameInsertItr )
      ;
   
   // retrieve the likelihoods
   STL_VECTOR( double ) likes;
   back_insert_iterator<STL_VECTOR( double )> likeInsertItr( likes );
   iSource
      >> sm_fill_contents( likeInsertItr )
      ;
   
   // retrieve the helicities
   STL_VECTOR( double ) hels;
   back_insert_iterator<STL_VECTOR( double )> helInsertItr( hels );
   iSource
      >> sm_fill_contents( helInsertItr )
      ;
   
   SimpleHelicity* tmpHelicity = make( SimpleHelicity() );

   // reconstruct all of the actual helicity objects and add them to
   // tmpHelicity
   STL_VECTOR( double )::const_iterator helItr = hels.begin();
   for ( STL_VECTOR( double )::const_iterator likeItr = likes.begin();
	 likeItr != likes.end(); ++likeItr ) {

     // retrieve the likelihood (trivial)
     Double likelihood = *likeItr;

     // reconstruct the name -> helicity map
     SimpleHelicity::ChildHelicities helicityMap;
     for ( STL_VECTOR( string )::const_iterator nameItr = names.begin();
	   nameItr != names.end(); ++nameItr ) {
       helicityMap[*nameItr] = *helItr;
       ++helItr;
     }
     // add the configuration
     tmpHelicity->addHelicityConfig( likelihood, helicityMap );
   }

   return tmpHelicity; 
}

//
// const member functions
//
const SimpleHelicity& 
SimpleHelicityStorageHelper::getDefault() const
{
   SimpleHelicity* tmpHelicity = new SimpleHelicity();

   SimpleHelicity::ChildHelicities helicityMap;
   helicityMap["Joe"] = 0.5;
   helicityMap["babyJoe"] = 1.0;
   tmpHelicity->addHelicityConfig( 0.98, helicityMap );
   SimpleHelicity::ChildHelicities helicityMap2;
   helicityMap2["Joe"] = 0.0;
   helicityMap2["babyJoe"] = 0.0;
   tmpHelicity->addHelicityConfig( 0.02, helicityMap );

   return *tmpHelicity;
}

DABoolean 
SimpleHelicityStorageHelper::compare( 
   const SimpleHelicity* iNewData, 
   const SimpleHelicity& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for SimpleHelicity
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//SimpleHelicity*
//SMStorageHelper<SimpleHelicity>::make( const SimpleHelicity& iTempData ) const
//{
   //change this line if SimpleHelicity does not have a copy constructor
//   return new SimpleHelicity( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( SimpleHelicityStorageHelper, SimpleHelicity )

typedef STL_VECTOR( string ) _container_type_ ;
#include "StorageManagement/instantiate_contents_builtin.h"

//------------------------------------------------------
