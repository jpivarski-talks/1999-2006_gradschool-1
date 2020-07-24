// -*- C++ -*-
//
// Package:     <package>
// Module:      TrkmanLatticeStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Oct  6 10:45:44 EDT 1999
// $Id: LatticeLinkTrkmanLatticeStorageHelper.cc,v 1.1 2002/11/04 18:31:26 nea9 Exp $
//
// Revision history
//
// $Log: LatticeLinkTrkmanLatticeStorageHelper.cc,v $
// Revision 1.1  2002/11/04 18:31:26  nea9
// New CleoIII Trkman
//
// Revision 1.4  2001/01/31 22:16:03  cdj
// added reminder to users in storage routine to register new versions
//
// Revision 1.3  2000/01/21 21:07:34  cdj
// helper skeletons now include SMPackInfo.h
//
// Revision 1.2  2000/01/08 19:18:08  cdj
// updated Lattice code to work with new cxx compiler
//
// Revision 1.1  1999/10/18 21:30:18  cdj
// renamed files
//
// Revision 1.2  1999/10/18 18:16:45  cdj
// easier to use and maintain
//
// Revision 1.1  1999/10/11 22:00:36  cdj
// added Lattice storage code
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <iterator>

// user include files
#include "Experiment/report.h"
#include "Trkman/LatticeLinkTrkmanLatticeStorageHelper.h"

#include "StorageManagement/SMLatticeLinkInfoIn.h"
#include "StorageManagement/SMLatticeLinkInfoOut.h"
#include "StorageManagement/SMLatticeLinkInfoDefault.h"

#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMContentsBuiltIn.h"
#include "StorageManagement/SMFillContents.h"

#include "StorageManagement/SMPackInfo.h" //defines sm_pack*

#include "StorageManagement/SMDeliverer.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "package.LatticeLinkTrkmanLatticeStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: LatticeLinkTrkmanLatticeStorageHelper.cc,v 1.1 2002/11/04 18:31:26 nea9 Exp $";
static const char* const kTagString = "$Name:  $";

//Simplify some names
typedef TrkmanLattice::VectorLeftID LeftIDs;
typedef TrkmanLattice::VectorRightID RightIDs;

//
// static data member definitions
//

//
// constructors and destructor
//
LatticeLinkTrkmanLatticeStorageHelper::LatticeLinkTrkmanLatticeStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &LatticeLinkTrkmanLatticeStorageHelper::deliverV1 );
}

// LatticeLinkTrkmanLatticeStorageHelper::LatticeLinkTrkmanLatticeStorageHelper( const LatticeLinkTrkmanLatticeStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

LatticeLinkTrkmanLatticeStorageHelper::~LatticeLinkTrkmanLatticeStorageHelper()
{
}

//
// assignment operators
//
// const LatticeLinkTrkmanLatticeStorageHelper& LatticeLinkTrkmanLatticeStorageHelper::operator=( const LatticeLinkTrkmanLatticeStorageHelper& rhs )
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
LatticeLinkTrkmanLatticeStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const SMLatticeLinkInfoBase< TrkmanLattice >& iData ) 
{
// NOTE: Any change (adding/removing variable OR packing info) to this routine
//    MUST be accompanied by registering a new version deliver routine in
//    this class's constructor.  
//    If only the packing info is changes, you can register the same deliver
//    routine a second time.

   const LeftIDs& leftIDs = iData.vLeftID();
   const RightIDs& rightIDs = iData.vRightID();

   //store the left and right ids
   iSink << sm_field( "leftIDs", sm_contents_builtin( leftIDs.begin(), 
						      leftIDs.end() ))
	 << sm_field( "rightIDs", sm_contents_builtin( rightIDs.begin(), 
						       rightIDs.end() ) )
      //store info from link data
	 << SM_VAR( iData, linkData().groupId )  
	 << SM_VAR( iData, linkData().groupCode )  
	 << SM_VAR( iData, linkData().numTracks )  
      ;
}

SMLatticeLinkInfoBase< TrkmanLattice >* 
LatticeLinkTrkmanLatticeStorageHelper::deliverV1( SMSourceStream& iSource )
{
   SMLatticeLinkInfoBase< TrkmanLattice >* link = 
      new SMLatticeLinkInfoIn< TrkmanLattice>();

   //first read the left and right IDs
   TrkmanLattice::VectorLeftID leftIDs;
   TrkmanLattice::VectorRightID rightIDs;
   
   back_insert_iterator<LeftIDs> leftInsertIterator( leftIDs );
   back_insert_iterator<RightIDs> rightInsertIterator( rightIDs );

   iSource >> sm_fill_contents( leftInsertIterator )
	   >> sm_fill_contents( rightInsertIterator ) ;

   //now read data for the LinkData
   int groupId; 
   int groupCode; 
   int numTracks; 

   iSource 
      >> groupId 
      >> groupCode 
      >> numTracks 
      ;
   TrkmanLattice::LinkData linkData = 
      TrkmanLattice::LinkData( 
	 groupId,   
	 groupCode,   
	 numTracks  
	 );
   //Add all the information to the link
   link->set( leftIDs, linkData, rightIDs );
   return link;
}

//
// const member functions
//
const SMLatticeLinkInfoBase< TrkmanLattice >& 
LatticeLinkTrkmanLatticeStorageHelper::getDefault() const
{
   static const SMLatticeLinkInfoDefault< TrkmanLattice > 
      temp(  LeftIDs(1,LeftIDs::value_type(1)),
	     TrkmanLattice::LinkData(
		int ( 1 ), // groupId 
		int ( 2 ), // groupCode 
		int ( 3 )  // numTracks 
		),
	     RightIDs(1,RightIDs::value_type(1)) );
   return temp;
}

DABoolean 
LatticeLinkTrkmanLatticeStorageHelper::compare( 
   const SMLatticeLinkInfoBase< TrkmanLattice >* iNewData, 
   const SMLatticeLinkInfoBase< TrkmanLattice >& iOldData ) const
{
   //need to compare contents
   return ( 
            (iNewData->linkData() == iOldData.linkData() ) &&
// comment out the line above and uncomment the lines below if operator==
// does not exist for the link data
      //    (iNewData->linkData().groupId() == iOldData.linkData().groupId() ) && 
      //    (iNewData->linkData().groupCode() == iOldData.linkData().groupCode() ) && 
      //    (iNewData->linkData().numTracks() == iOldData.linkData().numTracks() ) && 
	    (iNewData->vLeftID() == iOldData.vLeftID() ) &&
	    (iNewData->vRightID() == iOldData.vRightID() ) );
}

//
// static member functions
//

//------------------------------------------------------------------------
// DO NOT DELETE
SM_REGISTER_STORAGE( LatticeLinkTrkmanLatticeStorageHelper );

//this is done to create a TypeTag and its name
#include "FrameAccess/instantiate_macros.h"
typedef SMLatticeLinkInfoBase< TrkmanLattice > TrkmanLatticeLink;
INSTANTIATE_ONE( TrkmanLatticeLink )
#include "StorageManagement/instantiate_one_typetag.h"

#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( LatticeLinkTrkmanLatticeStorageHelper, SMLatticeLinkInfoBase< TrkmanLattice > )

typedef TrkmanLattice _lattice_element_;
#include "StorageManagement/instantiate_latticelinkhelper.h"



