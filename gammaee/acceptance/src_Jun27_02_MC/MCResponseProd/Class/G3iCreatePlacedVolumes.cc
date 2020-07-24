// -*- C++ -*-
//
// Package:     MCResponseProd
// Module:      G3iCreatePlacedVolumes
// 
// Description: Details of DGDetectorStore + G3iExtraVolSpecs
//                -----------> GEANT3 volume specifications
//
// Implementation:
//                  We traverse the DetectorGeometry hierarchy,
//                  defining & positioning any DGVolumeShaped
//                  that is encountered. Much of the code here
//                  is purely for the purpose of getting the
//                  fortran arguments filled in the right types,
//                  so is very tedious. We use the CLEO3 official 
//                  fortran types as defined in the header for this class.
//                  
//
//        The transform stored in DetectorGeometry is from the daughter
//        ref frame to the mother. The GEANT3 translation in gspos_
//        follows this convention, but the GEANT3 rotation matrix in IROT
//        goes in the opposite direction!! Hence in the implementation 
//        a crucial inversion of the rotation matrix is made before 
//        calling GEANT3.
//
//        We avoid reproducing the Identity rotation in calls to gsrotm_.
//
//        We keep track of created volumes locally & globally;
//        (i.e. in this instantiation & for all such )
//        & placed volumes just globally, avoiding duplications.
//
// Author:      Brian K. Heltsley
// Created:     Mon Oct 19 16:10:42 EDT 1998
// $Id: G3iCreatePlacedVolumes.cc,v 1.1 2001/09/25 21:38:07 bkh Exp $
//
// Revision history
//
// $Log: G3iCreatePlacedVolumes.cc,v $
// Revision 1.1  2001/09/25 21:38:07  bkh
// Moved routine here to solve solaris-8 linking problems
//
// Revision 1.10  2000/03/02 22:24:02  bkh
// Reduce size limit of number of params to 50 (GEANT limit) & improve err msg
//
// Revision 1.9  1999/12/15 18:46:37  bkh
// No longer make CLEO volume here, so remove related code from volume creation.
// Removed files moved to new other library (Geant3MaterialsMediaProd).
//
// Revision 1.8  1999/11/15 19:46:38  bkh
// Allow same sensitive volume to exist in different paths
//
// Revision 1.7  1999/10/29 20:38:41  bkh
// Use parent-placed name instead of bounding volume name
// Allow interation over volume specs for cloning purposes
//
// Revision 1.6  1999/08/31 21:29:21  bkh
// Add coil tracking media & fix some problems with volume creation
//
// Revision 1.5  1999/08/25 16:39:20  bkh
// Increase max #pars per volume from 200 to 700 to accomodate DR3
//
// Revision 1.4  1999/07/01 15:02:05  bkh
// Change check of repeated volume/copy to volume/copy/mother
//
// Revision 1.3  1999/03/24 17:29:29  bkh
// Add interface to DGVolumeHyperbolicTube
//
// Revision 1.2  1999/03/23 19:25:11  bkh
// Make Mother of all Mothers (CLEO) once
//
// Revision 1.1.1.1  1999/01/19 22:02:29  bkh
// imported Geant3Interface sources
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <set>
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

#include <string>
#include <utility>
#include <vector>

template class pair< string, UInt16 > ;

// user include files
#include "Experiment/report.h"
#include "Experiment/cleo_math.h"

#include "Geant3Interface/G3iExtraVolSpecs.h"
#include "Geant3Interface/G3iExtraVolSpecsStore.h"
#include "Geant3Interface/G3iSensitiveVolume.h"
#include "Geant3Interface/G3iTrackingMedium.h"
#include "MCResponseProd/G3iCreatePlacedVolumes.h"
#include "Geant3Interface/G3iFortran.h"

#include "CLHEP/Geometry/Transform3D.h"

#include "DetectorGeometry/DGDetectorStore.h"
#include "DetectorGeometry/DGVolumeShaped.h"
#include "DetectorGeometry/DGConstVolumeType.h"
#include "DetectorGeometry/DGConstPlacedVolumePtr.h"
#include "DetectorGeometry/DGVolumeParentPlaced.h"
#include "DetectorGeometry/DGPlacedVolume.h"

#include "DetectorGeometry/DGTrapezoidParameters.h"
#include "DetectorGeometry/DGVolumeBox.h"
#include "DetectorGeometry/DGVolumeTrapezoidSymX.h"
#include "DetectorGeometry/DGVolumePolygon.h"
#include "DetectorGeometry/DGVolumePolygonalTube.h"
#include "DetectorGeometry/DGVolumePolygonalCone.h"
#include "DetectorGeometry/DGVolumePolyCone.h"
#include "DetectorGeometry/DGVolumeCone.h"
#include "DetectorGeometry/DGVolumeTube.h"
#include "DetectorGeometry/DGVolumeSphere.h"
#include "DetectorGeometry/DGVolumeHyperbolicTube.h"

// STL classes
#include <string>
#include <set>
#include <vector>
#include <map>

//
// constants, enums & typedefs
//

static const double k_radDeg ( 180./M_PI ) ;

static const double k_MtoCM ( 100. ) ;

static const char* const kReport = "Geant3Interface.G3iCreatePlacedVolumes" ;

//
// static data member definitions
//

typedef STL_SET( string ) SetString ;  // the following line doesn't
                                       // compile on solaris without typedef
                                       // unless one uses = instead of ()

STL_SET( string )&           
G3iCreatePlacedVolumes::m_globalCreatedVolumeNames  
= *new SetString  ;

STL_SET( G3iCreatePlacedVolumes::TripletStringUInt32String )& 
G3iCreatePlacedVolumes::m_globalPlacedVolumeNames  
= *new STL_SET( TripletStringUInt32String ) ;

//
// constructors & destructor
//

G3iCreatePlacedVolumes::G3iCreatePlacedVolumes(
   const DGDetectorStore&       aDetStore ,
   const G3iExtraVolSpecsStore& aExtra 
   ) :
   m_vsStore              ( aExtra                           ) ,
   m_createdVolumeNames   ( *new STL_SET( string )           ) ,
   m_traversedParentNames ( *new STL_SET( string )           )
{

   if( aDetStore.root().isNull() )
   {
      report( WARNING, kReport ) << "Null root for DetectorStore" << endl ;
   }
   else
   {
      traverse( aDetStore.root() ) ; // gsvolu_ & gspos_

      setVolAtts()      ;          // gssatt_
      //setVolOrder()     ;          // gsord_   // obsolete!
      setVolSensitive() ;          // gsdetv_ & gsdeth_
   }
}

G3iCreatePlacedVolumes::~G3iCreatePlacedVolumes()
{
   delete &m_traversedParentNames ;
   delete &m_createdVolumeNames ;
}

//
// member functions
//

void
G3iCreatePlacedVolumes::traverse( const DGConstVolumePtr& aParent )
{
   // this function traverses a volume hierarchy, 
   // making & positioning GEANT3 volumes along the way as 
   // desired side effects


   DGConstVolumeType< DGVolumeParentPlaced > parent ( aParent ) ;

   const string& parentName ( parent->name() ) ;

   //cout << "....... Traversing parent named =" << parentName << endl ;

   if( !parent.isValid() )
   {
      report( EMERGENCY, kReport ) << "traverse(): "
				   << "Argument is not a parent, exiting ..."
				   << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }
   else
   {
      // set a flag if this is traversed yet
      const DABoolean notTraversed ( 
	 m_traversedParentNames.find( parentName ) ==
	 m_traversedParentNames.end() ) ;

      if( notTraversed )
      {
	 m_traversedParentNames.insert( parentName ) ;

	 const DGConstVolumePtr& mother ( parent->boundingVolume() ) ;

	 createVolume( parentName, mother ) ; // create the mother volume

	 // loop over the children
	 for( unsigned int iChild ( 0 ) ;
	      iChild != parent->numberOfChildren() ; ++iChild )
	 {
	    // this is the child placed volume
	    const DGPlacedVolume& childPlaced 
	       ( *( parent->getChild( iChild ) ) ) ;

	    // this is the DGVolume in the child
	    const DGConstVolumePtr& childVol ( childPlaced.volume() ) ;

	    // cast it to a parent type to check if it is a parent itself
	    const DGConstVolumeType< DGVolumeParentPlaced >
	       pNextParent ( childVol ) ;

	    if( pNextParent.isValid() )
	    {  
	       traverse( childVol ) ; // is a parent itself, so be recursive!
	    }
	    else
	    {
	       // cast to a shaped volume, which it must be!
	       const DGConstVolumeType< DGVolumeShaped >
		  pChildShaped ( childVol ) ;

	       // if not a parent, must be a shaped volume
	       if( pChildShaped.isValid() )
	       {
		  // is a shaped volume: create & place
		  createVolume( childVol->name(), childVol ) ;
	       }
	       else
	       {  // error condition
		  report( EMERGENCY, kReport ) << "traverse(): "
					       << "Child Volume # " << iChild
					       << " of Parent = "
					       << aParent->name()
					       << " is neither shaped nor "
					       << "parent, exiting ..." 
					       << endl ;
		  assert( false ) ;
		  ::exit( 1 ) ;
	       }
	    }
	    placeVolumeInMother( childPlaced , parentName, mother ) ;
	 }
      }
   }
}

void 
G3iCreatePlacedVolumes::createVolume( const string&           aName  ,
				      const DGConstVolumePtr& aShape   )
{
   // this function takes a shaped volume and calls gsvolu_ with its specs

   // the full string name of the volume
//   const string& nameString ( aShape->name() ) ;
   const string& nameString ( aName ) ;

   //cout << " ..... creating volume named " << nameString << endl ;

   // get the volspecs object
   const G3iExtraVolSpecs& vs ( vSpec( nameString ) ) ;

   // set a flag if this is defined yet globally
   const DABoolean notDefined ( 
      m_globalCreatedVolumeNames.find( nameString ) ==
      m_globalCreatedVolumeNames.end() ) ;

   if( notDefined ) m_globalCreatedVolumeNames.insert( nameString ) ;

   if( notDefined )
   {
      // repackage info for arguments
      FChar volumeName[4] ;
      stringToChar4( vs.gName() , volumeName ) ;

      // check if GEANT3 has heard of it yet...
      const FInteger userNum  ( 1 ) ;
      const FInteger internal ( 1 ) ;
      FInteger nPar     ;
      FInteger nAtts    ;
      FReal    pars[100] ;
      FInteger atts[100] ;
      gfpara_( volumeName , userNum , internal , nPar , nAtts , pars , atts ) ;

      const DABoolean notDefinedGeant3 ( 0 == nPar ) ;

      if( !notDefinedGeant3 )
      {  // already defined in GEANT3?
	 report( EMERGENCY, kReport ) 
	    << "createVolume(): GEANT3 thinks this volume = "
	    << string( volumeName, 4 )
	    << " already exists"
	    << endl ;
	 assert( false ) ;
	 ::exit( 1 ) ;
      }
      else
      {
	 // get shape-name & parameters of shape
	 string shapeNameString ;
	 STL_VECTOR( float ) parVec ;
	 getShapeInfo( aShape, shapeNameString, parVec ) ;

	 FChar shapeName[4] ; // convert to FChar
	 stringToChar4( shapeNameString , shapeName ) ;

	 // put params in FReal array
	 const FInteger nPar ( parVec.size() ) ;
	 static const UInt16 maxPars ( 50 ) ; // avoid slow "new"
	 FReal par[ maxPars ] ;
	 if( nPar >= maxPars )
	 {
	    report( EMERGENCY, kReport ) << "createVolume(): "
					 << "exiting on too many pars = "
					 << nPar 
					 << " for volume =" << nameString
					 << endl ;
	    assert( false ) ;
	    ::exit( 1 ) ;
	 }

	 for( UInt16 i ( 0 ) ; i != nPar ; ++i )
	 {
	    par[i] = parVec[i] ;
	 }

	 // put material in FInteger
	 const FInteger medium ( vs.medium()->index() ) ;

	 // flag is output flag
	 FInteger flag ( 1 ) ;

	 //cout << " ,,,,,,, calling gsvolu for " << vs.gName()
	 //<< " with params = " ;
	 //
	 //{for( UInt16 i ( 0 ) ; i != nPar ; ++i )
	 //{
	 //   cout << par[i] << ", " ;
	 //}}
	 //cout << endl ;

	 gsvolu_( volumeName , shapeName , medium , par , nPar , flag ) ;

	 if( flag <= 0 )
	 {
	    report( EMERGENCY, kReport ) << "createVolume(): "
					 << "exiting on bad return flag = "
					 << flag << endl ;
	    assert( false ) ;
	    ::exit( 1 ) ;
	 }

	 m_createdVolumeNames.insert(       nameString ) ;
      }
   }
}

void 
G3iCreatePlacedVolumes::placeVolumeInMother( const DGPlacedVolume&   aPlace  ,
					     const string&           aName   ,
					     const DGConstVolumePtr& aMother  )
{
   // this function takes a DGPlacedVolume & its bounding volume
   // as inputs & creates in GEANT3-space a placed volume
   // by calling the fortran routine gspos_.

   // string name of the mother
//   const string& motherString ( aMother->name() ) ;
   const string& motherString ( aName ) ;

   // vol specs of the mother
   const G3iExtraVolSpecs& vsMoth  ( vSpec( motherString ) ) ;

//   const DGConstVolumeType< DGVolumeParentPlaced > pParent
//      ( aPlace.volume() ) ;

   // string name of the child
   const string& childString ( aPlace.volume()->name() ) ;

   // vol specs of the child
   const G3iExtraVolSpecs& vsChild ( vSpec( childString ) ) ;

   const UInt32 copyNum ( aPlace.copyNumber() ) ; // copy number

   const TripletStringUInt32String placedVolume 
      ( childString, copyNum, motherString ) ;

   // flag to see if has been placed in this instantiation of this object
   const DABoolean placed   
      ( m_globalPlacedVolumeNames.find( placedVolume  ) !=
	m_globalPlacedVolumeNames.end() ) ;

   if( placed )  // if placed previously, error condition
   {
      report( ERROR, kReport ) << "placeVolumeInMother(): volume = "
			       << childString
			       << " has already been placed !! "
			       << " Exiting ..." << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }
   else
   {
      // now we check if it has been positioned yet in GEANT3
      FChar childName[4] ;
      stringToChar4( vsChild.gName() , childName ) ;

      FChar motherName[4] ;
      stringToChar4( vsMoth.gName() , motherName ) ;

      const FInteger copyNumber ( copyNum ) ; // get copy number

      const FInteger rotationNumber                  // get the rotation number
	 ( getRotation( aPlace.localAlignedToParent() ) ) ; 

      const HepVector3D translation 
	 ( aPlace.localAlignedToParent().getTranslation() );

      const FReal x ( k_MtoCM*translation.x() ) ;
      const FReal y ( k_MtoCM*translation.y() ) ;
      const FReal z ( k_MtoCM*translation.z() ) ;

      static const FChar onlyName[] = "ONLY" ;

      //cout << "xxxxxxxxxxxxx    Calling gspos for " << vsMoth.gName() 
      //<< ", copy# " << copyNumber << endl ;

      gspos_( childName      ,
	      copyNumber     ,
	      motherName     ,
	      x, y, z        ,
	      rotationNumber ,
	      onlyName         ) ; // hardwire ONLY be compatible w/GEANT4

      // insert in set
      m_globalPlacedVolumeNames.insert( placedVolume ) ;
   }
}

//
// const member functions
//

void 
G3iCreatePlacedVolumes::getShapeInfo( const DGConstVolumePtr& aShape  ,
				      string&                 aString ,
				      STL_VECTOR( float )&    aPar      ) const
{
   // returns shape name & dimensions in universal format

   // first guarantee we have a shaped volume
   const DGConstVolumeType< DGVolumeShaped > shap ( aShape ) ;
   if( !shap.isValid() ) 
   {
      aString  = "    " ;
      report( EMERGENCY, kReport ) << "getShapeInfo(): "
				   << " given a not-shaped-Volume"
				   << ", exiting ... " << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }
   else
   {
      // now cycle through the possibilities: order here is IMPORTANT!
      // for example DGVolumeBox inherits from DGVolumeTrapezoid, yet
      // we want the box to end up as a geant BOX not a TRAP (is faster)

      DGConstVolumeType< DGVolumeBox                     > box   ( aShape ) ;
      if( box.isValid() )
      {
	 aString = "BOX " ;
	 aPar.reserve( 3 ) ;

	 aPar.push_back( k_MtoCM*box->halfLengthX() ) ;
	 aPar.push_back( k_MtoCM*box->halfLengthY() ) ;
	 aPar.push_back( k_MtoCM*box->halfLengthZ() ) ;
	 return ;
      }

      DGConstVolumeType< DGVolumeParallelpiped           > para  ( aShape ) ;
      if( para.isValid() )
      {
	 aString = "PARA" ;
	 aPar.reserve( 6 ) ;
	 DGTrapezoidParameters traParm ( *para ) ;

	 aPar.push_back( k_MtoCM*para->halfLengthX() ) ;
	 aPar.push_back( k_MtoCM*para->halfLengthY() ) ;
	 aPar.push_back( k_MtoCM*para->halfLengthZ() ) ;
	 aPar.push_back( k_radDeg*para->angleAD() ) ;
	 aPar.push_back( k_radDeg*traParm.theta() ) ;
	 aPar.push_back( k_radDeg*traParm.phi()   ) ;
	 return ;
      }

      DGConstVolumeType< DGVolumeTrapezoidSymX           > symX  ( aShape ) ;
      if( symX.isValid() )
      {
	 aString = "TRD1" ;
	 aPar.reserve( 4 ) ;

	 aPar.push_back( k_MtoCM*symX->halfLengthXNegZ() ) ;
	 aPar.push_back( k_MtoCM*symX->halfLengthXPosZ() ) ;
	 aPar.push_back( k_MtoCM*symX->halfLengthY()     ) ;
	 aPar.push_back( k_MtoCM*symX->halfLengthZ()     ) ;
	 return ;
      }

      DGConstVolumeType< DGVolumeTrapezoidSymXY          > symXY ( aShape ) ;
      if( symXY.isValid() )
      {
	 aString = "TRD2" ;
	 aPar.reserve( 5 ) ;

	 aPar.push_back( k_MtoCM*symXY->halfLengthXNegZ() ) ;
	 aPar.push_back( k_MtoCM*symXY->halfLengthXPosZ() ) ;
	 aPar.push_back( k_MtoCM*symXY->halfLengthYNegZ() ) ;
	 aPar.push_back( k_MtoCM*symXY->halfLengthYPosZ() ) ;
	 aPar.push_back( k_MtoCM*symXY->halfLengthZ()     ) ;
	 return ;
      }

      //DGConstVolumeType< DGVolumeTrapezoidSym            > sym   ( aShape ) ;
      DGConstVolumeType< DGVolumeTrapezoid               > trap  ( aShape ) ;
      if( trap.isValid() ) // || sym.isValid() )
      {
	 aString = "TRAP" ;
	 aPar.reserve( 11 ) ;
	 DGTrapezoidParameters traParm ( *trap ) ;

	 aPar.push_back( k_MtoCM*traParm.dz() ) ;
	 aPar.push_back( k_radDeg*traParm.theta() ) ;
	 aPar.push_back( k_radDeg*traParm.phi()   ) ;
	 aPar.push_back( k_MtoCM*traParm.h1() ) ;
	 aPar.push_back( k_MtoCM*traParm.bl1() ) ;
	 aPar.push_back( k_MtoCM*traParm.tl1() ) ;
	 aPar.push_back( k_radDeg*traParm.alp1()   ) ;
	 aPar.push_back( k_MtoCM*traParm.h2() ) ;
	 aPar.push_back( k_MtoCM*traParm.bl2() ) ;
	 aPar.push_back( k_MtoCM*traParm.tl2() ) ;
	 aPar.push_back( k_radDeg*traParm.alp2()   ) ;
	 return ;
      }

      //DGConstVolumeType< DGVolumePolygonalTube           > pgTub ( aShape ) ;
      //DGConstVolumeType< DGVolumePolygonalTubePhiSegment > pgTPS ( aShape ) ;
      //DGConstVolumeType< DGVolumePolygonalCone           > pgCon ( aShape ) ;
      //DGConstVolumeType< DGVolumePolygonalConePhiSegment > pgCPS ( aShape ) ;
      //DGConstVolumeType< DGVolumePolygon                 > pgon  ( aShape ) ;
      DGConstVolumeType< DGVolumePolygonPhiSegment       > pgPS  ( aShape ) ;
      if( pgPS.isValid()  ) // || pgon.isValid()  || pgTub.isValid() ||
	 //pgTPS.isValid() || pgCon.isValid() || pgCPS.isValid()     )
      {
	 aString = "PGON" ;
	 const _vector_DGZrR_& list ( pgPS->zrRList().list() ) ; 
	 aPar.reserve( 4 + 3*( list.size() ) ) ;

	 aPar.push_back( k_radDeg*pgPS->phiMin()   ) ;
	 aPar.push_back( k_radDeg*pgPS->deltaPhi() ) ;
	 aPar.push_back( pgPS->nSides()            ) ;
	 aPar.push_back( list.size()               ) ;
	 for( _vector_DGZrR_::const_iterator iZrR ( list.begin() ) ;
	      iZrR != list.end() ; ++iZrR )
	 {
	    const DGZrR& zrR ( *iZrR ) ;
	    aPar.push_back( k_MtoCM*zrR.z()           ) ;
	    aPar.push_back( k_MtoCM*zrR.innerRadius() ) ;
	    aPar.push_back( k_MtoCM*zrR.outerRadius() ) ;
	 }
	 return ;
      }

      DGConstVolumeType< DGVolumeTube                    > tube  ( aShape ) ;
      if( tube.isValid() )
      {
	 aString = "TUBE" ;
	 aPar.reserve( 3 ) ;

	 aPar.push_back( k_MtoCM*tube->innerRadius() ) ;
	 aPar.push_back( k_MtoCM*tube->outerRadius() ) ;
	 aPar.push_back( k_MtoCM*tube->halfLengthZ() ) ;
	 return ;
      }

      DGConstVolumeType< DGVolumeTubePhiSegment          > tuPS  ( aShape ) ;
      if( tuPS.isValid() )
      {
	 aString = "TUBS" ;
	 aPar.reserve( 5 ) ;

	 aPar.push_back( k_MtoCM*tuPS->innerRadius()     ) ;
	 aPar.push_back( k_MtoCM*tuPS->outerRadius()     ) ;
	 aPar.push_back( k_MtoCM*tuPS->halfLengthZ()     ) ;
	 aPar.push_back( k_radDeg*tuPS->phiMin() ) ;
	 aPar.push_back( k_radDeg*( tuPS->phiMin() + tuPS->deltaPhi() ) ) ;
	 return ;
      }

      DGConstVolumeType< DGVolumeCone                    > cone  ( aShape ) ;
      if( cone.isValid() )
      {
	 aString = "CONE" ;
	 aPar.reserve( 5 ) ;

	 aPar.push_back( k_MtoCM*cone->halfLengthZ()     ) ;
	 aPar.push_back( k_MtoCM*cone->rPairLoZ().first  ) ;
	 aPar.push_back( k_MtoCM*cone->rPairLoZ().second ) ;
	 aPar.push_back( k_MtoCM*cone->rPairHiZ().first  ) ;
	 aPar.push_back( k_MtoCM*cone->rPairHiZ().second ) ;
	 return ;
      }

      DGConstVolumeType< DGVolumeConePhiSegment          > coPS  ( aShape ) ;
      if( coPS.isValid() )
      {
	 aString = "CONS" ;
	 aPar.reserve( 7 ) ;

	 aPar.push_back( k_MtoCM*coPS->halfLengthZ()     ) ;
	 aPar.push_back( k_MtoCM*coPS->rPairLoZ().first  ) ;
	 aPar.push_back( k_MtoCM*coPS->rPairLoZ().second ) ;
	 aPar.push_back( k_MtoCM*coPS->rPairHiZ().first  ) ;
	 aPar.push_back( k_MtoCM*coPS->rPairHiZ().second ) ;
	 aPar.push_back( k_radDeg*coPS->phiMin() ) ;
	 aPar.push_back( k_radDeg*( coPS->phiMin() + coPS->deltaPhi() ) ) ;
	 return ;
      }

      //DGConstVolumeType< DGVolumePolyCone                > poCon ( aShape ) ;
      DGConstVolumeType< DGVolumePolyConePhiSegment      > poCPS ( aShape ) ;
      if( poCPS.isValid() ) //|| poCon.isValid() )
      {
	 aString = "PCON" ;

	 const _vector_DGZrR_& list ( poCPS->zrRList().list() ) ; 
	 aPar.reserve( 3 + 3*( list.size() ) ) ;

	 aPar.push_back( k_radDeg*poCPS->phiMin()   ) ;
	 aPar.push_back( k_radDeg*poCPS->deltaPhi() ) ;
	 aPar.push_back( list.size()                ) ;
	 for( _vector_DGZrR_::const_iterator iZrR ( list.begin() ) ;
	      iZrR != list.end() ; ++iZrR )
	 {
	    const DGZrR& zrR ( *iZrR ) ;
	    aPar.push_back( k_MtoCM*zrR.z()           ) ;
	    aPar.push_back( k_MtoCM*zrR.innerRadius() ) ;
	    aPar.push_back( k_MtoCM*zrR.outerRadius() ) ;
	 }
	 return ;
      }

      DGConstVolumeType< DGVolumeHyperbolicTube          > hype ( aShape ) ;
      if( hype.isValid() )
      {
	 aString = "HYPE" ;
	 aPar.reserve( 4 ) ;

	 aPar.push_back( k_MtoCM*hype->innerRadiusCtr()  ) ;
	 aPar.push_back( k_MtoCM*hype->outerRadiusCtr()  ) ;
	 aPar.push_back( k_MtoCM*hype->halfLengthZ()     ) ;
	 aPar.push_back( k_radDeg*atan( hype->tanScd() ) ) ;
	 return ;
      }

      DGConstVolumeType< DGVolumeSphere                  > spher ( aShape ) ;
      if( spher.isValid() )
      {
	 aString = "SPHE" ;
	 aPar.reserve( 6 ) ;

	 aPar.push_back( k_MtoCM*spher->innerRadius()         ) ;
	 aPar.push_back( k_MtoCM*spher->outerRadius()         ) ;
	 aPar.push_back( k_radDeg*spher->lowerTheta() ) ;
	 aPar.push_back( k_radDeg*spher->upperTheta() ) ;
	 aPar.push_back( k_radDeg*spher->lowerPhi()   ) ;
	 aPar.push_back( k_radDeg*spher->upperPhi()   ) ;
	 return ;
      }
      else
      {
	 aString = "    " ;
	 report( ERROR, kReport ) << "getShapeInfo(): is not any real shape"
				  << ", exiting ... " << endl ;
	 assert( false ) ;
	 ::exit( 1 ) ;
      }
   }
}

const G3iExtraVolSpecsStore& 
G3iCreatePlacedVolumes::vsStore() const 
{
   return m_vsStore ;
}

const G3iExtraVolSpecs& 
G3iCreatePlacedVolumes::vSpec( const string& aId ) const 
{
   G3iExtraVolSpecsStore::const_iterator pVS ( vsStore().find( aId ) ) ;

   if( pVS == vsStore().end() )
   {
      report( EMERGENCY, kReport ) << "vSpec(): "
				   << "No volume specs item found for id = "
				   << aId << ", exiting ..." << endl ;

      assert( false ) ;
      ::exit( 1 ) ;
   }
   return (*pVS).second ;
}

//void 
//G3iCreatePlacedVolumes::setVolOrder() const 
//{
//   for( STL_SET( string )::const_iterator iStr 
//	   ( m_createdVolumeNames.begin() ) ;
//	iStr !=  m_createdVolumeNames.end() ; ++iStr )
//   {
//      const G3iExtraVolSpecs& vs ( vSpec( *iStr ) ) ;
//
//      if( vs.gOrderIndex() != 0 )
//      {
//	 FChar name[4] ;
//	 stringToChar4( vs.gName() , name ) ;
//
//	 const FInteger orderIndex ( vs.gOrderIndex() ) ;
//	 gsord_( name , orderIndex ) ;
//      }
//   }
//}

void 
G3iCreatePlacedVolumes::setVolAtts()  const 
{
   for( STL_SET( string )::const_iterator iStr 
	   ( m_createdVolumeNames.begin() ) ;
	iStr !=  m_createdVolumeNames.end() ; ++iStr )
   {
      const G3iExtraVolSpecs& vs ( vSpec( *iStr ) ) ;

      FChar name[4] ;
      stringToChar4( vs.gName() , name ) ;

      if( vs.gAttributes().size() != 0 )
      {
	 for( STL_MAP( G3iExtraVolSpecs::AttributeId , Int16 )::const_iterator
		 iM ( vs.gAttributes().begin() ) ;
	      iM != vs.gAttributes().end() ; ++iM )
	 {
	    const G3iExtraVolSpecs::AttributeId id  ( (*iM).first  ) ;
	    const FInteger                      val ( (*iM).second ) ;
	    string att ;
	    if(      id == G3iExtraVolSpecs::k_work         ) att = "WORK" ;
	    else if( id == G3iExtraVolSpecs::k_seen         ) att = "SEEN" ;
	    else if( id == G3iExtraVolSpecs::k_lineStyle    ) att = "LSTY" ;
	    else if( id == G3iExtraVolSpecs::k_lineWidth    ) att = "LWID" ;
	    else if( id == G3iExtraVolSpecs::k_color        ) att = "COLO" ;
	    else if( id == G3iExtraVolSpecs::k_fillPattern  ) att = "FILL" ;
	    else if( id == G3iExtraVolSpecs::k_setNumber    ) att = "SET " ;
	    else if( id == G3iExtraVolSpecs::k_detNumber    ) att = "DET " ;
	    else if( id == G3iExtraVolSpecs::k_detectorType ) att = "DTYP" ;
	    else if( id == G3iExtraVolSpecs::k_node         ) att = "NODE" ;
	    else                                              att = "    " ;

	    FChar chAtt[4] ;
	    stringToChar4( att , chAtt ) ;
	    gsatt_( name , chAtt , val ) ;
	 }
      }
   }
}

void 
G3iCreatePlacedVolumes::setVolSensitive() const 
{
   // do sensitive volume definition with gsdetv_ and
   // specify its HITS structure with gsdeth_

   for( STL_SET( string )::const_iterator iStr 
	   ( m_createdVolumeNames.begin() ) ;
	iStr !=  m_createdVolumeNames.end() ; ++iStr )
   {
      const G3iExtraVolSpecs& vs ( vSpec( *iStr ) ) ;

      const G3iSensitiveVolume* pSensitive ( vs.sensitive() ) ;

      if( pSensitive != 0 )
      {
	 FChar setName[4] ;
	 stringToChar4( pSensitive->setName() , setName ) ;

	 FChar detName[4] ;
	 stringToChar4( vs.gName() , detName ) ;

	 const FInteger idType ( pSensitive->detectorType() ) ;
	 const FInteger nwhi   ( pSensitive->nWordAllocation() ) ;
	 const FInteger nwdi   ( 0 ) ; // we don't use digi
	 FInteger iSet ( 0 ) ;
	 FInteger iDet ( 0 ) ;

	 const STL_VECTOR( G3iSensitiveVolume::PathPair )& pairs 
	    ( pSensitive->pathPairs() ) ;
	 const FInteger nPathNames ( pairs.size() ) ;
	 if( 0 == nPathNames )
	 {
	    gsdetv_( setName, detName, idType, nwhi, nwdi, iSet, iDet ) ;
	 }
	 else
	 {
	    static const UInt16 kMaxNames ( 20 ) ;
	    FChar pathNames[ kMaxNames*4 ] ;
	    FInteger nBits[  kMaxNames ] ;
	    if( kMaxNames <= nPathNames ) 
	    {
	       report( EMERGENCY, kReport ) << "Number of path names = "
					    << nPathNames << " is too big!!"
					    << endl ;
	       assert( false ) ;
	       ::exit( 1 ) ;
	    }
	    for( UInt16 ii ( 0 ) ; ii < nPathNames ; ++ii )
	    {
	       const G3iSensitiveVolume::PathPair& pathPair ( pairs[ii] ) ;
	       stringToChar4( pathPair.first, &pathNames[ii*4] ) ;
	       nBits[ii] = pathPair.second ;
	    }
	    gsdet_( setName, detName, nPathNames, pathNames, nBits,
		    idType, nwhi, nwdi, iSet, iDet ) ;
	 }
	 //--------------------------------------------------------------------

	 const STL_VECTOR( G3iHitElementSpec)& hitEl (
	    pSensitive->hitElementSpecs() ) ;

	 const FInteger nElements ( hitEl.size() ) ;

	 static const UInt16 k_maxElements  ( 100 ) ;

	 if( k_maxElements < nElements )
	 {
	    report( EMERGENCY, kReport ) << "createVolume(): "
					 << "exiting on too many elements = "
					 << nElements << endl ;
	    assert( false ) ;
	    ::exit( 1 ) ;
	 }

	 FChar    namesH[k_maxElements*4] ;
	 FInteger nBitsH[k_maxElements]   ;
	 FReal    orig[  k_maxElements]   ;
	 FReal    fact[  k_maxElements]   ;

	 for( UInt16 i ( 0 ) ; i != nElements ; ++i )
	 {
	    stringToChar4( hitEl[i].name() , &namesH[4*i] ) ;
	    nBitsH[i] = hitEl[i].nBits()  ;
	    if( nBitsH[i] > 16 ) { nBitsH[i] = 32 ; }
	    orig[  i] = hitEl[i].offset() ;
	    fact[  i] = hitEl[i].factor() ;
	 }

	 gsdeth_( setName, detName, nElements, namesH, nBitsH , orig, fact ) ;
	 //--------------------------------------------------------------------
      }
   }
}

//
// static member functions
//

UInt32
G3iCreatePlacedVolumes::getRotation( const HepTransform3D& aTransform  )
{
   // this function takes an input transform & returns
   // a GEANT3-rotation matrix number
   // corresponding to that transform. A desired side effect 
   // is that a GEANT3 rotation matrix is created in GEANT3-space.

   // We avoid replicating the identity rotation by creating
   // it only once & checking each rotation directly against it.

   static const HepRotation rotIdentity
      ( HepTransform3D::Identity.getRotation() ) ; // identity rotation

   static UInt32 k_identityRotationNumber ( 0 ) ; // index of identity rotation

   //!! key inverse here !!!! This is the GEANT3 convention for rotations
   const HepRotation rot ( (aTransform.getRotation() ).inverse() ) ;

   // below appears the recommended way to make a rotation matrix in GEANT3
   // hard to believe it's this hard, but apparently it's true!
   const FReal rowmat1[3] = { rot.xx(), rot.xy(), rot.xz() } ;
   const FReal rowmat2[3] = { rot.yx(), rot.yy(), rot.yz() } ;
   const FReal rowmat3[3] = { rot.zx(), rot.zy(), rot.zz() } ;

   FReal
      costh1, sinth1, cosph1, sinph1 ,
      costh2, sinth2, cosph2, sinph2 ,
      costh3, sinth3, cosph3, sinph3 ;

   FLogical brot ;
   gfang_( rowmat1, costh1, sinth1, cosph1, sinph1, brot ) ;
   gfang_( rowmat2, costh2, sinth2, cosph2, sinph2, brot ) ;
   gfang_( rowmat3, costh3, sinth3, cosph3, sinph3, brot ) ;

   const FReal theta1 ( atan2( sinth1, costh1 )*k_radDeg ) ;
   const FReal phi1   ( atan2( sinph1, cosph1 )*k_radDeg ) ;
   const FReal theta2 ( atan2( sinth2, costh2 )*k_radDeg ) ;
   const FReal phi2   ( atan2( sinph2, cosph2 )*k_radDeg ) ;
   const FReal theta3 ( atan2( sinth3, costh3 )*k_radDeg ) ;
   const FReal phi3   ( atan2( sinph3, cosph3 )*k_radDeg ) ;

   // we must now get a rotation matrix number *BUT* check if
   // it is the trivial identity rotation & if so, make it exactly once

   FInteger iRot ( 0 ) ;

   const DABoolean isIdentityRotation ( rotIdentity == rot ) ;

   if( !isIdentityRotation || 0 == k_identityRotationNumber )
   {
      const FChar* cName ( kReport ) ;
      cggrot_( iRot , cName ) ; // gets next available rotation matrix number

      if( 0 >= iRot )
      {
	 report( EMERGENCY, kReport ) << "getRotation(): "
				      << "No reasonable rotation matrix # "
				      << "available, exiting " << endl ;
	 assert( false ) ;
	 ::exit( 1 ) ;
      }

      // makes rotation matrix
      gsrotm_( iRot , theta1 , phi1 , theta2 , phi2 , theta3 , phi3 ) ;

      if( isIdentityRotation && 0 == k_identityRotationNumber )
      {
	 k_identityRotationNumber = iRot ;
      }
   }
   else
   {
      iRot = k_identityRotationNumber ; // use identity rotation number
   }

   if( 0 >= iRot )  // bad rotation number
   {
      report( ERROR, kReport ) << "getTranslationRotation(): "
			       << " Bad rotation matrix number = " << iRot
			       << " , exiting ... " << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }

   return iRot ;
}

void 
G3iCreatePlacedVolumes::stringToChar4( const string& aString , FChar* aChar4 ) 
{
   const UInt16 nChar ( 4 < aString.size() ? 4 : aString.size() ) ;
   for( UInt16 ic ( 0 ) ; ic != 4 ; ++ic )
   {
      if( ic+1 > nChar ) 
      {
	 aChar4[ ic ] = ' ' ;
      }
      else
      {
	 aChar4[ ic ] = aString[ ic ] ;
      }
   }
}

