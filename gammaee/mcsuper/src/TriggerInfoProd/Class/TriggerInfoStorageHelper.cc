// -*- C++ -*-
//
// Package:     TriggerInfoProd
// Module:      TriggerInfoStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: TriggerInfoStorageHelper.cc,v 1.6 2003/04/04 21:34:46 cdj Exp $
//
// Revision history
//
// $Log: TriggerInfoStorageHelper.cc,v $
// Revision 1.6  2003/04/04 21:34:46  cdj
// added compile time checking of data in deliver function matches type stored
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
#include "TriggerInfoProd/TriggerInfoStorageHelper.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMPackInfo.h" //defines sm_pack*
#include "StorageManagement/smTestReturnTypeMatchesVariable.h"

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

static const char* const kFacilityString = "TriggerInfoProd.TriggerInfoStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: TriggerInfoStorageHelper.cc,v 1.6 2003/04/04 21:34:46 cdj Exp $";
static const char* const kTagString = "$Name: v05_15_04 $";

//
// static data member definitions
//

//
// constructors and destructor
//
TriggerInfoStorageHelper::TriggerInfoStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &TriggerInfoStorageHelper::deliverV1 );
}

// TriggerInfoStorageHelper::TriggerInfoStorageHelper( const TriggerInfoStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//TriggerInfoStorageHelper::~TriggerInfoStorageHelper()
//{
//}

//
// assignment operators
//
// const TriggerInfoStorageHelper& TriggerInfoStorageHelper::operator=( const TriggerInfoStorageHelper& rhs )
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
TriggerInfoStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const TriggerInfo& iData ) 
{
// NOTE: Any change (adding/removing variable OR packing info) to this routine
//    MUST be accompanied by registering a new version deliver routine in
//    this class's constructor.  
//    If only the packing info is changes, you can register the same deliver
//    routine a second time.

   iSink 
      << SM_VAR( iData, axial )   
      << SM_VAR( iData, stereo )   
      << SM_VAR( iData, cblo )   
      << SM_VAR( iData, cbmd )   
      ;
}

TriggerInfo* 
TriggerInfoStorageHelper::deliverV1( SMSourceStream& iSource )
{
   //NOTE: variable type must match type used to store data
   int axial; TEST_RETURN_TYPE(TriggerInfo,axial); 
   int stereo; TEST_RETURN_TYPE(TriggerInfo,stereo); 
   int cblo; TEST_RETURN_TYPE(TriggerInfo,cblo); 
   int cbmd; TEST_RETURN_TYPE(TriggerInfo,cbmd); 

   iSource 
      >> axial 
      >> stereo 
      >> cblo 
      >> cbmd 
	 ;
   
   return make( TriggerInfo( 
      axial,  
      stereo,  
      cblo,  
      cbmd ) ); 
}

//
// const member functions
//
const TriggerInfo& 
TriggerInfoStorageHelper::getDefault() const
{
   //give constructor unique values to allow test of store and deliver 
   // functions
   static const TriggerInfo temp(
      int ( 1 ), // axial 
      int ( 2 ), // stereo 
      int ( 3 ), // cblo 
      int ( 4 ) ); // cbmd 
   return temp;
}

DABoolean 
TriggerInfoStorageHelper::compare( 
   const TriggerInfo* iNewData, 
   const TriggerInfo& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for TriggerInfo
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//TriggerInfo*
//SMStorageHelper<TriggerInfo>::make( const TriggerInfo& iTempData ) const
//{
   //change this line if TriggerInfo does not have a copy constructor
//   return new TriggerInfo( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( TriggerInfoStorageHelper, TriggerInfo )

typedef TriggerInfo _store_element_;
#include "StorageManagement/instantiate_proxyhelper.h"
//------------------------------------------------------
