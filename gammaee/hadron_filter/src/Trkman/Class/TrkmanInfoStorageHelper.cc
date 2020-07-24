// -*- C++ -*-
//
// Package:     Trkman
// Module:      TrkmanInfoStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: TrkmanInfoStorageHelper.cc,v 1.3 2001/01/31 22:16:06 cdj Exp $
//
// Revision history
//
// $Log: TrkmanInfoStorageHelper.cc,v $
// Revision 1.3  2001/01/31 22:16:06  cdj
// added reminder to users in storage routine to register new versions
//
// Revision 1.2  2000/01/21 21:07:37  cdj
// helper skeletons now include SMPackInfo.h
//
// Revision 1.1  1999/10/18 18:13:04  cdj
// first submission
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
#include "Trkman/TrkmanInfoStorageHelper.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
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

static const char* const kFacilityString = "Trkman.TrkmanInfoStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: TrkmanInfoStorageHelper.cc,v 1.3 2001/01/31 22:16:06 cdj Exp $";
static const char* const kTagString = "$Name: v05_00_01 $";

//
// static data member definitions
//

//
// constructors and destructor
//
TrkmanInfoStorageHelper::TrkmanInfoStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &TrkmanInfoStorageHelper::deliverV1 );
}

// TrkmanInfoStorageHelper::TrkmanInfoStorageHelper( const TrkmanInfoStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//TrkmanInfoStorageHelper::~TrkmanInfoStorageHelper()
//{
//}

//
// assignment operators
//
// const TrkmanInfoStorageHelper& TrkmanInfoStorageHelper::operator=( const TrkmanInfoStorageHelper& rhs )
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
TrkmanInfoStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const TrkmanInfo& iData ) 
{
// NOTE: Any change (adding/removing variable OR packing info) to this routine
//    MUST be accompanied by registering a new version deliver routine in
//    this class's constructor.  
//    If only the packing info is changes, you can register the same deliver
//    routine a second time.

   iSink 
      << SM_VAR( iData, identifier )   
      << SM_VAR( iData, classificationCode )   
      << sm_field( "useForMatching", char( iData.useForMatching() ) )   
      << SM_VAR( iData, groupId )   
      ;
}

TrkmanInfo* 
TrkmanInfoStorageHelper::deliverV1( SMSourceStream& iSource )
{
   
   TrkmanInfo ::Identifier identifier; 
   int classificationCode; 
   char useForMatching; 
   int groupId; 

   iSource 
      >> identifier 
      >> classificationCode 
      >> useForMatching 
      >> groupId 
	 ;
   
   return make( TrkmanInfo( 
      identifier,  
      classificationCode,  
      useForMatching,  
      groupId ) ); 
}

//
// const member functions
//
const TrkmanInfo& 
TrkmanInfoStorageHelper::getDefault() const
{
   //give constructor unique values to allow test of store and deliver 
   // functions
   static const TrkmanInfo temp(
      TrkmanInfo ::Identifier ( 1 ), // identifier 
      int ( 2 ), // classificationCode 
      DABoolean ( 3 ), // useForMatching 
      int ( 4 ) ); // groupId 
   return temp;
}

DABoolean 
TrkmanInfoStorageHelper::compare( 
   const TrkmanInfo* iNewData, 
   const TrkmanInfo& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for TrkmanInfo
   return ( (*iNewData).identifier()         == iOldData.identifier() &&
	    (*iNewData).classificationCode() == iOldData.classificationCode() &&
	    (*iNewData).useForMatching()     == iOldData.useForMatching() && 
	    (*iNewData).groupId()            == iOldData.groupId() ) ;
}

//
// static member functions
//

//TrkmanInfo*
//SMStorageHelper<TrkmanInfo>::make( const TrkmanInfo& iTempData ) const
//{
   //change this line if TrkmanInfo does not have a copy constructor
//   return new TrkmanInfo( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
SM_REGISTER_STORAGE( TrkmanInfoStorageHelper );

#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( TrkmanInfoStorageHelper, TrkmanInfo )

//this is done to create a TypeTag and its name
#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE(TrkmanInfo)
#include "StorageManagement/instantiate_one_typetag.h"

#include "StorageManagement/Template/SMStorageHelper.cc"
template class SMStorageHelper<TrkmanInfo>;

//------------------------------------------------------
