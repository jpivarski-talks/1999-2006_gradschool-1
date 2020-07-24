// -*- C++ -*-
//
// Package:     MCResponseProd
// Module:      BuildGeantGeometry
// 
// Description: Class to create the Geant Geometry description
//              used by cleog by extracting the Detector geometry
//              (DGDetectorStore) store + extra Geant specific description
//              of the volumes (G3iExtraVolSpecsStore).  
//
//              This object is responsible to
//              - Manage map of synch values w/ different streams
//              - Creates Geant geometry
//              - Check that the geometry is consistent.
//
// TODO:
//      1) When the aligned detector geometry stores are available,
//      extract then instead of detector geometry w/ perfect alignment.
//      2) This class should be a singelton
//
//      This class is functional as is but when we want to run multi-run
//      cleog under suez, we need to add these features:
//      3) Check that the geometry is up to date:
//          - 1st time, save the synch value when we build the geometry
//            could be different for the different sub-detectors.
//              const SyncValue& syncValue = iRecord.syncValue();
//          - Put these in a STL map - stream type <-> synch values
//            1st time push into map, 2nd time through checking synch values
//          - see if the synch value changed, if so abort job
//            as you can only build the geometry 1 per job
//
//
// Implementation:
//     <Notes on implementation>
//
// Author:      John J O'Neill
// Created:     Fri Mar 12 13:21:48 EST 1999
// $Id: BuildGeantGeometry.cc,v 1.32 2003/04/11 20:39:25 bkh Exp $
//
// Revision history
//
// $Log: BuildGeantGeometry.cc,v $
// Revision 1.32  2003/04/11 20:39:25  bkh
// Get DetectorConfiguration from basegeometry now not beginrun
//
// Revision 1.31  2002/11/27 21:01:12  bkh
// Build ZD if in fact we should
// Improve error message in volume creation
//
// Revision 1.30  2002/09/27 20:27:56  bkh
// Add ZD
//
// Revision 1.29  2001/09/25 21:38:07  bkh
// Moved routine here to solve solaris-8 linking problems
//
// Revision 1.28  2001/05/01 22:06:14  swnam
// mc_mu_response_ has new arguments of muon hits, old codes were commented out.
//
// Revision 1.27  2001/04/14 06:06:16  mahlke
// changed handover of doXXGeom flags to BuildGeantGeometry; separate class now
//
// Revision 1.26  2001/04/11 15:17:03  dubrovin
// Add info-print to indicate nasty GEANT print out
//
// Revision 1.25  2001/04/09 14:23:46  mahlke
// introduce flag to switch off geometry or responses for single subdetectors
//
// Revision 1.24  2001/03/15 21:53:06  bkh
// Get Tracking Medium from Start Run
//
// Revision 1.23  2000/12/08 21:51:46  cdj
// made more exception safe
//
// Revision 1.22  2000/04/21 17:20:24  pg
// Extract DRAligned geometry when building Geant volumes
//
// Revision 1.21  2000/04/19 00:44:19  pg
// Added protection against TOO MANY HITS case. Extract Si geometry from SVAlignment stream.
//
// Revision 1.20  2000/03/26 21:22:49  lkg
// delete some old commented out code, some (now obsolete) valid() checks removed
//
// Revision 1.19  2000/03/08 22:38:36  pg
// Forgot to commit changes to Si hit production.
//
// Revision 1.18  2000/02/02 16:26:51  lkg
// Turn the code for building the IR geometry in GEANT back on
//
// Revision 1.17  2000/01/26 23:20:22  lkg
// Temporarily comment out building of Si geometry temporarily until PG fixes
// simulation.  One gets crashes otherwise.
//
// Revision 1.16  1999/12/15 18:51:18  bkh
// No creates CLEO volume here explicitly.
//
// Revision 1.15  1999/11/18 19:51:25  jjo
// put back DRWL volumes which previous submission removed
//
// Revision 1.14  1999/11/16 20:50:42  pg
// Added Si simulation
//
// Revision 1.13  1999/11/09 19:08:04  jjo
// Moved calls to print out Geant banks to MCResponseProd::updateCleogBeginRun()
// and reduce/improve report messages & comments.
//
// Revision 1.12  1999/10/29 20:43:28  bkh
// Implement DR (including wire layers) and MU geometries
//
// Revision 1.11  1999/10/20 22:41:58  jjo
// Improve report messages
//
// Revision 1.10  1999/10/19 16:27:47  jjo
// Update to call DR & DRWireLayer.  Building the Geant
// volumes for DRWireLayer doesn't work yet so it's commented out.
//
// Revision 1.9  1999/08/31 21:53:15  bkh
// Add Coil to geometry
//
// Revision 1.8  1999/08/31 20:49:33  jjo
// Comment out geometry systems that have problems
//
// Revision 1.7  1999/08/20 01:53:53  jjo
// Most cosmetic changes.  Have problems with IR, DR, DRWL
// Geant Xtra Vol specs so comment out for now
//
// Revision 1.6  1999/07/08 06:08:49  ts
// add building of Rich geometry
//
// Revision 1.5  1999/07/01 14:59:20  pg
// Added extraction calls for Si geometry and ExtraVolSpecs so Geant can build Si.
//
// Revision 1.4  1999/05/14 17:16:01  bkh
// Changes to make CC Responses work
//
// Revision 1.3  1999/05/10 14:54:49  jjo
// Added MuGeom calls (but are commented out due to problems
// linking with mugeom) and added a TODO list.
//
// Revision 1.2  1999/05/03 20:34:09  jjo
// Fix typo
//
// Revision 1.1  1999/05/03 20:21:15  jjo
// Reorganize code to make running Cleog under Suez more robust
//
#include "Experiment/Experiment.h"

// system include files
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
//#include "FrameAccess/FATable.h"
#include "FrameAccess/FAItem.h"


#include "DetectorGeometry/DGDetectorStore.h"
#include "CoilGeom/CoilNames.h"
#include "SiGeom/SiGeomDescription.h"
#include "ZDWireLayerProd/ZDWireLayerParams.h"
#include "DRGeom/DRGeometryParams.h"
#include "CcGeom/CcGNames.h"
#include "RichGeom/RichGeom.h"
#include "DRWireLayer/DRWireLayerParams.h"
#include "IRGeom/IRGeomParameters.h"
//#include "MUGeom/MUGeomParams.h"

#include "Geant3Interface/G3iExtraVolSpecsStore.h"
#include "MCResponseProd/G3iCreatePlacedVolumes.h"

#include "MCResponseProd/BuildGeantGeometry.h"

//----------- these for making CLEO ---------------------
#include "ToolBox/Triplet.h"

#include "DetectorGeometry/DGConstMaterialPtr.h"
#include "DetectorGeometry/DGVolumeParentPlaced.h"
#include "DetectorGeometry/DGVolumeBox.h"

#include "Geant3Interface/G3iExtraVolSpecs.h"
#include "Geant3Interface/G3iExtraVolSpecsStore.h"
#include "Geant3Interface/G3iTrackingMediaStore.h"
#include "Geant3Interface/G3iTrackingMediaIds.h"


#include "DetectorConfiguration/DetectorConfiguration.h"
//-----------------------------------------------------------

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
#include <set>
#include <map>
//#include <algorithm>
//#include <utility>


// ggclos_ - Geant routine ggclos - end Geant geometry initialization.
// gphysi_ - Geant routine - compute energy loss and cross-section tables
extern "C" {
   extern void ggclos_();     
   extern void gphysi_();     
}
//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCResponseProd.BuildGeantGeometry" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: BuildGeantGeometry.cc,v 1.32 2003/04/11 20:39:25 bkh Exp $";
static const char* const kTagString = "$Name: v06_02_06 $";

//
// static data member definitions
//

//
// constructors and destructor
//
BuildGeantGeometry::BuildGeantGeometry()
{
}

// BuildGeantGeometry::BuildGeantGeometry( const BuildGeantGeometry& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

BuildGeantGeometry::~BuildGeantGeometry()
{
}

//
// assignment operators
//
// const BuildGeantGeometry& BuildGeantGeometry::operator=( const BuildGeantGeometry& rhs )
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

//
// const member functions
//

//
// static member functions
//
void BuildGeantGeometry::create( const Frame&        iFrame ,
				 const UseComponent& iUseComponent )
{
   report( INFO, kFacilityString ) << "Building Geant Geometry\n" << endl;

   FAItem<DetectorConfiguration>                     iConfig   ;
   extract( iFrame.record( Stream::kBaseGeometry ) , iConfig ) ;

   // step (1) - extracts Detector geometry stores for sub-detectors
   // step (2) - extracts GeantExtraVolSpecsStores for sub-detectors
   // step (3) - build Geant volumes via Geant3Interface's G3iCreatePlacedVolumes
   // step (4) - Finish Geant volume definitions
   
   // Coil - contains default B field so goes before inner detectors
   FAItem< DGDetectorStore > coilDetectorStore ;
   extract( iFrame.record( Stream::kBaseGeometry ), coilDetectorStore,
	    CoilNames::k_geometryUsageTag );
   report( DEBUG, kFacilityString ) 
      << "Extracted Coil Detector Geometry" << endl;

   // IR 
   FAItem< DGDetectorStore > irDetectorStore ;
   extract( iFrame.record( Stream::kBaseGeometry ), irDetectorStore,
   	    IRGeomParameters::kUsageTag );
   report(INFO, kFacilityString ) << "Extracted IR Detector Geometry" 
				  << endl;

   // --------
   // step (2) - extracts GeantExtraVolSpecsStores for sub-detectors
   // --------

   // Coil 
   FAItem< G3iExtraVolSpecsStore > coilGeantExtraVolSpecsStore;
   extract( iFrame.record( Stream::kStartRun ), coilGeantExtraVolSpecsStore,
 	    CoilNames::k_geometryUsageTag );
   report( INFO, kFacilityString ) << "Extracted Coil GeantExtraVolSpecsStore"
				   << endl;

   // IR
   FAItem< G3iExtraVolSpecsStore > irGeantExtraVolSpecsStore;
   extract( iFrame.record( Stream::kStartRun ), irGeantExtraVolSpecsStore,
   	    IRGeomParameters::kUsageTag );
   report(INFO, kFacilityString ) << "Extracted IR GeantExtraVolSpecsStore" 
				  << endl;

   // --------
   // step (3) - build Geant volumes via G3iCreatePlacedVolumes
   // --------

   //-------------- create CLEO mother volume ---------------------------
   //----------------------------------------------------------------------
   //----------------------------------------------------------------------
   const DGConstMaterialPtr k_nullMaterialPtr (  new DGMaterial() ) ;

   const DGConstVolumePtr pLab ( new DGVolumeBox( // big lab volume
      "lab", k_nullMaterialPtr,
      Triplet<double,double,double>( 3.70,3.70,3.70 ) ) ) ;

   DGVolumeParentPlaced* vpCleo ( new DGVolumeParentPlaced( "lab", pLab ) ) ;

   DGDetectorStore cleoDetStore ;
   cleoDetStore.setRoot( vpCleo ) ;

   G3iExtraVolSpecsStore cleoExtra ;

   G3iExtraVolSpecs* extra ( 0 ) ;

   G3iTrackingMediaStore media ;
   extract( iFrame.record( Stream::kStartRun ), media );

   extra = cleoExtra.insert( "lab" , "CLEO" , media[ kAirLoCutTMedID ] ) ;
   extra->insertAttribute( G3iExtraVolSpecs::k_seen ,
			   G3iExtraVolSpecs::k_seenUnseen ) ;

   const G3iCreatePlacedVolumes createCleoVolume ( cleoDetStore, cleoExtra );
   report( DEBUG, kFacilityString ) << "Created CLEO Geant Volume" << endl;
   //----------------------------------------------------------------------
   //----------------------------------------------------------------------
   //---------------------- Done making parent CLEO -----------------------

   
   // Coil 
   const G3iCreatePlacedVolumes
      createCoilVolumes ( *coilDetectorStore, *coilGeantExtraVolSpecsStore );
   report( DEBUG, kFacilityString ) << "Created Coil Geant Volumes" << endl;

   // IR
   const G3iCreatePlacedVolumes
      createIRVolumes ( *irDetectorStore, *irGeantExtraVolSpecsStore );
   report( DEBUG, kFacilityString ) << "Created IR Geant Volumes" << endl;

   // SI 
   // --
   report( DEBUG, kFacilityString ) << "Are SV Geant volumes to be created: " 
                                    << iUseComponent.doSVGeom()
                                    << endl;

   if( iConfig->useSInotZD()     &&
       iUseComponent.doSVGeom()     ) 
   {
      FAItem< DGDetectorStore > svDetectorStore ;
      extract( iFrame.record( Stream::kSVAlignment ), svDetectorStore,
	       SiGeomDescription::kSecondaryID );
      report( INFO, kFacilityString ) 
	 << "Extracted SV Detector Geometry" << endl;

      FAItem< G3iExtraVolSpecsStore > svGeantExtraVolSpecsStore;
      extract( iFrame.record( Stream::kStartRun ), svGeantExtraVolSpecsStore,
	       SiGeomDescription::kSecondaryID );
      report(INFO, kFacilityString ) << "Extracted SV GeantExtraVolSpecsStore"
				     << endl;
   
      const G3iCreatePlacedVolumes
	 createSIVolumes ( *svDetectorStore, *svGeantExtraVolSpecsStore );
      report( DEBUG, kFacilityString ) << "Created SV Geant Volumes" << endl;
   } 
   else 
   {
      report( INFO, kFacilityString ) 
	 << "SV Geant Volumes NOT CREATED" << endl;
   }

   // now ZDWL

   if( iConfig->useZDnotSI()    && 
       iUseComponent.doZDGeom()     ) 
   {
      FAItem< DGDetectorStore > zdwlDetectorStore ;
      extract( iFrame.record( Stream::kZDAlignment ), zdwlDetectorStore,
	       ZDWireLayerParams::kZDWLSecondaryID );
      report( INFO, kFacilityString ) 
         << "Extracted ZD Wire Layer Geometry " << endl;

      FAItem< G3iExtraVolSpecsStore > zdwlGeantExtraVolSpecsStore;
      extract( iFrame.record( Stream::kStartRun ), zdwlGeantExtraVolSpecsStore,
	       ZDWireLayerParams::kZDWLSecondaryID );
      report(INFO, kFacilityString ) << "Extracted ZD GeantExtraVolSpecsStore"
	 			     << endl;
   
      const G3iCreatePlacedVolumes
	 createZDVolumes ( *zdwlDetectorStore, *zdwlGeantExtraVolSpecsStore );
      report( DEBUG, kFacilityString ) << "Created ZD Geant Volumes" << endl;
   } 
   else 
   {
     report( INFO, kFacilityString ) << "ZD Geant Volumes NOT CREATED" << endl;
   }

   // DRWL
   // ----

   report( DEBUG, kFacilityString ) << "Are DR Geant volumes to be created: " 
                                    << iUseComponent.doDRGeom()
                                    << endl;

   if( iUseComponent.doDRGeom() ) 
   {
      FAItem< DGDetectorStore > drwlDetectorStore ;
      extract( iFrame.record( Stream::kDRAlignment ), drwlDetectorStore,
	       DRWireLayerParams::kDRWLSecondaryID );
      report( DEBUG, kFacilityString ) 
	 << "Extracted DRWL Detector Geometry" << endl;

      FAItem< G3iExtraVolSpecsStore > drwlGeantExtraVolSpecsStore;
      extract( iFrame.record( Stream::kStartRun ), drwlGeantExtraVolSpecsStore,
	       DRWireLayerParams::kDRWLSecondaryID );
      report( DEBUG, kFacilityString ) 
	 << "Extracted DRWL GeantExtraVolSpecsStore" << endl;

      const G3iCreatePlacedVolumes
	 createDRWLVolumes ( *drwlDetectorStore, *drwlGeantExtraVolSpecsStore);
      report( DEBUG, kFacilityString ) << "Created DRWL Geant Volumes" << endl;
   } 
   else 
   {
      report( INFO, kFacilityString ) 
	 << "DR Geant Volumes NOT CREATED" << endl;
   }   

   // RICH 
   // ----
   report( DEBUG, kFacilityString ) 
      << "Are Rich Geant volumes to be created: "
      << iUseComponent.doRichGeom() << endl;

   if( iUseComponent.doRichGeom() ) 
   {
      FAItem< DGDetectorStore > richDetectorStore ;
      extract( iFrame.record( Stream::kRICHAlignment ), richDetectorStore,
	       RichGeom::k_RichAlignedGeometryUsageTag );
      report( INFO, kFacilityString ) 
	 << "Extracted Rich Detector Geometry" << endl;

      FAItem< G3iExtraVolSpecsStore > richGeantExtraVolSpecsStore;
      extract( iFrame.record( Stream::kRICHAlignment ), 
	       richGeantExtraVolSpecsStore,
	       RichGeom::k_RichAlignedGeometryUsageTag );
      report(INFO, kFacilityString ) 
	 << "Extracted Rich GeantExtraVolSpecsStore" << endl;

      const G3iCreatePlacedVolumes
	 createRichVolumes ( *richDetectorStore, *richGeantExtraVolSpecsStore);
      report( DEBUG, kFacilityString ) << "Created RICH Geant Volumes" << endl;
   } 
   else 
   {
      report( INFO, kFacilityString ) 
	 << "Rich Geant Volumes NOT CREATED" << endl;
   }

   // CC 
   // --
   report( DEBUG, kFacilityString ) << "Are CC Geant volumes to be created: " 
                                    << iUseComponent.doCCGeom() << endl;

   if ( iUseComponent.doCCGeom() ) 
   {
      FAItem< DGDetectorStore > ccDetectorStore ;
      extract( iFrame.record( Stream::kBaseGeometry ), ccDetectorStore,
	       CcGNames::k_geometryUsageTag );
      report( INFO, kFacilityString ) << "Extracted CC Detector Geometry" 
				      << endl;

      FAItem< G3iExtraVolSpecsStore > ccGeantExtraVolSpecsStore;
      extract( iFrame.record( Stream::kStartRun ), ccGeantExtraVolSpecsStore,
	       CcGNames::k_geometryUsageTag );
      report(INFO, kFacilityString ) << "Extracted CC GeantExtraVolSpecsStore" 
				     << endl;

      const G3iCreatePlacedVolumes
	 createCcVolumes ( *ccDetectorStore, *ccGeantExtraVolSpecsStore );
      report( DEBUG, kFacilityString ) << "Created CC Geant Volumes" << endl;
   } 
   else 
   {
      report( INFO, kFacilityString ) 
	 << "CC Geant Volumes NOT CREATED" << endl;
   }

   // MU
   // --
   report( DEBUG, kFacilityString ) << "Are MU Geant volumes to be created: " 
                                    << iUseComponent.doMUGeom() << endl;

   if ( iUseComponent.doMUGeom() ) 
   {
      FAItem< DGDetectorStore > muDetectorStore ;
      extract( iFrame.record( Stream::kBaseGeometry ), muDetectorStore, "MU");
      report( INFO, kFacilityString ) 
	 << "Extracted MU Detector Geometry" << endl;

      FAItem< G3iExtraVolSpecsStore > muGeantExtraVolSpecsStore;
      extract( iFrame.record( Stream::kStartRun ),
	       muGeantExtraVolSpecsStore, 	    "MU" );
      report( INFO, kFacilityString ) 
	 << "Extracted MUON GeantExtraVolSpecsStore" << endl;

      const G3iCreatePlacedVolumes
	 createMUVolumes ( *muDetectorStore, *muGeantExtraVolSpecsStore );
      report( DEBUG, kFacilityString ) << "Created MUON Geant Volumes" << endl;
   } 
   else 
   {
      report( INFO, kFacilityString ) 
	 << "MU Geant Volumes NOT CREATED" << endl;
   }
   
   // --------
   // step (4) - Finish Geant volume definitions
   // --------
   // ggclos_ - Required Geant call to finish geometry definition
   // process all the geometrical information provided by the user and
   // prepare for particle transport.
   ggclos_();

   report( INFO, kFacilityString ) 
   << " All the next print out is coming from call to gphysi.F"  << endl;

   // Geant call to compute energy loss and cross-section tables 
   // and store them in the data structure JMATE (CONS, PHYS)
   gphysi_();

   report( INFO, kFacilityString ) 
      << " All previous print out is coming from call to gphysi.F"  << endl;
}













