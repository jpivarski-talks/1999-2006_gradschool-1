// -*- C++ -*-
//
// Package:     StupidProd
// Module:      StupidStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: StupidStorageHelper.cc,v 1.6 2003/04/04 21:34:46 cdj Exp $
//
// Revision history
//
// $Log: StupidStorageHelper.cc,v $
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
#include "StupidProd/StupidStorageHelper.h"
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

static const char* const kFacilityString = "StupidProd.StupidStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: StupidStorageHelper.cc,v 1.6 2003/04/04 21:34:46 cdj Exp $";
static const char* const kTagString = "$Name: v05_15_04 $";

//
// static data member definitions
//

//
// constructors and destructor
//
StupidStorageHelper::StupidStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &StupidStorageHelper::deliverV1 );
}

// StupidStorageHelper::StupidStorageHelper( const StupidStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//StupidStorageHelper::~StupidStorageHelper()
//{
//}

//
// assignment operators
//
// const StupidStorageHelper& StupidStorageHelper::operator=( const StupidStorageHelper& rhs )
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
StupidStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const Stupid& iData ) 
{
// NOTE: Any change (adding/removing variable OR packing info) to this routine
//    MUST be accompanied by registering a new version deliver routine in
//    this class's constructor.  
//    If only the packing info is changes, you can register the same deliver
//    routine a second time.

   iSink 
      << SM_VAR( iData, tracks0 )   
      << SM_VAR( iData, tracks1 )   
      << SM_VAR( iData, tracks2 )   
      << SM_VAR( iData, tracks3 )   
      ;
}

Stupid* 
StupidStorageHelper::deliverV1( SMSourceStream& iSource )
{
   //NOTE: variable type must match type used to store data
   int tracks0; TEST_RETURN_TYPE(Stupid,tracks0); 
   int tracks1; TEST_RETURN_TYPE(Stupid,tracks1); 
   int tracks2; TEST_RETURN_TYPE(Stupid,tracks2); 
   int tracks3; TEST_RETURN_TYPE(Stupid,tracks3); 

   iSource 
      >> tracks0 
      >> tracks1 
      >> tracks2 
      >> tracks3 
	 ;
   
   return make( Stupid( 
      tracks0,  
      tracks1,  
      tracks2,  
      tracks3 ) ); 
}

//
// const member functions
//
const Stupid& 
StupidStorageHelper::getDefault() const
{
   //give constructor unique values to allow test of store and deliver 
   // functions
   static const Stupid temp(
      int ( 1 ), // tracks0 
      int ( 2 ), // tracks1 
      int ( 3 ), // tracks2 
      int ( 4 ) ); // tracks3 
   return temp;
}

DABoolean 
StupidStorageHelper::compare( 
   const Stupid* iNewData, 
   const Stupid& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for Stupid
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//Stupid*
//SMStorageHelper<Stupid>::make( const Stupid& iTempData ) const
//{
   //change this line if Stupid does not have a copy constructor
//   return new Stupid( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( StupidStorageHelper, Stupid )

typedef Stupid _store_element_;
#include "StorageManagement/instantiate_proxyhelper.h"
//------------------------------------------------------
