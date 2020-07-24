// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      G3iMakeMaterials
// 
// Description: Define materials/mixtures for CLEO3 a la GEANT3
//
// Implementation:
//                  The implementation here might seem to the
//                  naive onlooker to be quite tedious. Well, it is.
//                  However, it was the opinion of the author that
//                  any such implementation would be tedious and
//                  typo-prone, so any choice introduces a tradeoff.
//
//                  Here the calls to GEANT3 (gsmate_, gsmixt_, gfmate_)
//                  are placed in a loop to avoid repeated calls.
//                  This in turn requires setting the input arguments
//                  in long array initializations.
//
//                  It was also decided here to require any material
//                  in a mixture to be first included in the
//                  non-mixture elements, so repeated (error-prone)
//                  definitions of Z & A & density of the element 
//                  would not be required.
//
//                  I have tried to remain faithful to the
//                  materials in cleo2 cleog, where applicable.
//
//                  As repeated calls to gsmate_ &/or gsmixt_ with
//                  the same inputs cause errors, this class is a singleton.
//
//                  This class is used by both the MaterialDelivery
//                  proxy and GEANT3 initialization in MC.
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec  8 11:11:36 EST 1998
// $Id: G3iMakeMaterials.cc,v 1.7 2001/05/09 16:21:35 bkh Exp $
//
// Revision history
//
// $Log: G3iMakeMaterials.cc,v $
// Revision 1.7  2001/05/09 16:21:35  bkh
// Modify full endplate material to include silicon cables
//
// Revision 1.6  2001/04/17 20:18:04  bkh
// New materials/media for DR Endplate components
//
// Revision 1.5  2000/10/24 21:34:33  bkh
// Improved Gas Wire vapor material specification
//
// Revision 1.4  2000/10/17 15:10:43  bkh
// Add Aluminum5056, GasWireVapor
//
// Revision 1.3  1999/12/29 16:26:24  bkh
// Vacuum atomic properties must be non-zero in a mix
//
// Revision 1.2  1999/12/15 21:06:21  bkh
// Give the vacuum a (small) non-zero density
//
// Revision 1.1.1.1  1999/12/15 18:35:50  bkh
// imported Geant3MaterialsMediaProd sources
//
// Revision 1.8  1999/07/06 19:21:06  bkh
// Install SVCarbonFiber material and medium
//
// Revision 1.7  1999/07/05 14:22:49  bkh
// Install Beryllium Oxide Material and Tracking Medium
//
// Revision 1.6  1999/06/04 16:37:43  bkh
// Added kevlar material, and rohacell, kevlar, and dr3innertube tracking media
//
// Revision 1.5  1999/06/01 20:55:14  bkh
// Remove proportion-->weight calculation because GEANT already did it for us
//
// Revision 1.4  1999/04/13 17:32:12  bkh
// Use measured density of Rich Tube for carbon fiber
//
// Revision 1.3  1999/03/25 20:38:19  bkh
// Add Rich Materials/Media
//
// Revision 1.2  1999/01/21 22:46:47  bkh
// Add Diamond material, documentation
//
// Revision 1.1.1.1  1999/01/19 22:02:29  bkh
// imported Geant3MaterialsMediaProd sources
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "Experiment/units.h"
#include "Geant3MaterialsMediaProd/G3iMakeMaterials.h"
#include "MaterialDelivery/material_identifiers.h"
#include "Geant3MaterialsMediaProd/G3iSpecialMaterialIds.h"

// STL classes

#include <string>
#include <vector>
#include <map>

//
// constants, enums and typedefs
//

static const char* const kReport = "Geant3MaterialsMediaProd.G3iMakeMaterials" ;

//
// static data member definitions
//

G3iMakeMaterials* G3iMakeMaterials::k_instance ( 0 ) ;

//
// constructors and destructor
//

G3iMakeMaterials::G3iMakeMaterials() :
   G3iMakeStuffBase () ,
   m_wtdElt ( *new STL_MAP( string,
			    G3iMakeMaterials::VecWt ) ) 
{
   report( INFO, kReport ) << "Defining CLEO3 materials" << endl ;

   static const FInteger nameLength ( 20 ) ;

   enum
   {
      kHydrogenMatIndex = 1         , // must start at 1 here for GEANT3
      kDeuteriumMatIndex            ,
      kHeliumMatIndex               ,
      kLithiumMatIndex              ,
      kBerylliumMatIndex            ,
      kCarbonMatIndex               ,
      kNitrogenMatIndex             ,
      kNeonMatIndex                 ,
      kAluminumMatIndex             ,
      kIronMatIndex                 ,
      kCopperMatIndex               ,
      kTungstenMatIndex             ,
      kLeadMatIndex                 ,
      kUraniumMatIndex              ,
      kAirMatIndex                  ,
      kVacuumMatIndex, // 16 above internal to GEANT3 (CANNOT CHANGE!!)
      
      kSilverMatIndex               ,   // next bunch are "mixtures" of one
      kGoldMatIndex                 ,
      kSiliconMatIndex              ,
      kOxygenMatIndex               ,
      kMagnesiumMatIndex            ,
      kPhosphorusMatIndex           ,
      kSulfurMatIndex               ,
      kChromiumMatIndex             ,
      kManganeseMatIndex            ,
      kNickelMatIndex               ,
      kMolybdenumMatIndex           ,
      kCesiumMatIndex               ,
      kIodineMatIndex               ,
      kNeodymiumMatIndex            ,
      kBoronMatIndex                ,
      kChlorineMatIndex             ,
      kDiamondMatIndex              ,
      kCalciumMatIndex              ,
      kFluorineMatIndex             ,
      kNitrogenGasMatIndex          ,
      kBromineMatIndex              ,
      kTinMatIndex                  ,
      kZincMatIndex                 ,
                                     // mixtures from here on down
      kHeliumPropaneMatIndex        ,
      kAluminum6061MatIndex         ,
      kStainless316MatIndex         ,
      kRohacellMatIndex             ,
      kEpoxyMatIndex                ,
      kDR3InnerTubeMaterialMatIndex ,
      kCesiumIodideMatIndex         ,
      kG10MatIndex                  ,
      kRecQuadMatIndex              ,
      kMylarMatIndex                ,
      kKevlarMatIndex               ,
      kLuciteMatIndex               ,
      kPVCMatIndex                  ,
      kCableMatIndex                ,
      kWaterMatIndex                ,
      kLithiumFluorideMatIndex      ,
      kCalciumFluorideMatIndex      ,
      kMethaneTEAMatIndex           ,
      kCarbonFiberMatIndex          ,

      kBerylliumOxideMatIndex       ,
      kSVCarbonFiberMatIndex        ,

      kVacuumLoCutMatIndex          ,
      kVacuumCoilMatIndex           ,
      kVacuumCoilNFMatIndex         ,
      kAirFieldMatIndex             ,
      kAirLoCutMatIndex             ,
      kAirLCFieldMatIndex           ,
      kAirLCFPrecMatIndex           ,
      kAluminumLoCutMatIndex        ,
      kAluminumMuonMatIndex         ,
      kAluminumCoilMatIndex         ,
      kAluminumCoilNFMatIndex       ,
      kMylarCoilMatIndex            ,
      kMylarCoilNFMatIndex          ,
      kAluminum5056MatIndex         ,
      kGasWireVaporMatIndex         ,
      kDREndplateHoleyMatIndex      ,
      kDRPreampVaporMatIndex        ,
      kDRNoPreampVaporMatIndex      ,
      kDROnEndplateMatIndex     
   };

   gmate_() ; // internal GEANT3 material initialization

   static const UInt16 maxMaterials ( 200 ) ;
   FReal xAtomicWeight[ maxMaterials ] ;
   FReal xAtomicNumber[ maxMaterials ] ;
   FReal xDensity[      maxMaterials ] ;

   // const access to the above
   const FReal* atomicWeight ( xAtomicWeight ) ;
   const FReal* atomicNumber ( xAtomicNumber ) ;
   const FReal* density      ( xDensity      ) ;

   const FReal kSilverAtomicWt     ( 107.8682  ) ;
   const FReal kSilverAtomicNo     ( 47        ) ;
   const FReal kSilverDensity      ( 10.5      ) ;

   const FReal kGoldAtomicWt       ( 196.96655 ) ;
   const FReal kGoldAtomicNo       ( 79        ) ;
   const FReal kGoldDensity        ( 19.3      ) ;

   const FReal kSiliconAtomicWt    ( 28.0855   ) ;
   const FReal kSiliconAtomicNo    ( 14        ) ;
   const FReal kSiliconDensity     ( 2.33      ) ;

   const FReal kOxygenAtomicWt     ( 15.9994   ) ;
   const FReal kOxygenAtomicNo     ( 8         ) ;
   const FReal kOxygenDensity      ( .001428   ) ;

   const FReal kMagnesiumAtomicWt  ( 24.3050   ) ;
   const FReal kMagnesiumAtomicNo  ( 12        ) ;
   const FReal kMagnesiumDensity   ( 1.738     ) ;

   const FReal kPhosphorusAtomicWt ( 30.973761 ) ;
   const FReal kPhosphorusAtomicNo ( 15        ) ;
   const FReal kPhosphorusDensity  ( 1.82      ) ; // white phosphorus

   const FReal kSulfurAtomicWt     ( 32.066    ) ;
   const FReal kSulfurAtomicNo     ( 16        ) ;
   const FReal kSulfurDensity      ( 2.07      ) ; // rhombic

   const FReal kChromiumAtomicWt   ( 51.9961   ) ;
   const FReal kChromiumAtomicNo   ( 24        ) ;
   const FReal kChromiumDensity    ( 7.19      ) ; // middle of range

   const FReal kManganeseAtomicWt  ( 54.938049 ) ;
   const FReal kManganeseAtomicNo  ( 25        ) ;
   const FReal kManganeseDensity   ( 7.32      ) ; // middle of range

   const FReal kNickelAtomicWt     ( 58.6934   ) ;
   const FReal kNickelAtomicNo     ( 28        ) ;
   const FReal kNickelDensity      ( 8.902     ) ;

   const FReal kMolybdenumAtomicWt ( 95.94     ) ;
   const FReal kMolybdenumAtomicNo ( 42        ) ;
   const FReal kMolybdenumDensity  ( 10.22     ) ;

   const FReal kCesiumAtomicWt     ( 132.90545 ) ;
   const FReal kCesiumAtomicNo     ( 55        ) ;
   const FReal kCesiumDensity      ( 1         ) ;

   const FReal kIodineAtomicWt     ( 126.90447 ) ;
   const FReal kIodineAtomicNo     ( 53        ) ;
   const FReal kIodineDensity      ( 1         ) ;

   const FReal kNeodymiumAtomicWt  ( 144.24    ) ;
   const FReal kNeodymiumAtomicNo  ( 60        ) ;
   const FReal kNeodymiumDensity   ( 1         ) ;

   const FReal kBoronAtomicWt      ( 10.811    ) ;
   const FReal kBoronAtomicNo      ( 5         ) ;
   const FReal kBoronDensity       ( 1         ) ;

   const FReal kChlorineAtomicWt   ( 35.4527   ) ;
   const FReal kChlorineAtomicNo   ( 17        ) ;
   const FReal kChlorineDensity    ( 1         ) ;

   const FReal kDiamondAtomicWt    ( 12.011    ) ;
   const FReal kDiamondAtomicNo    (  6        ) ;
   const FReal kDiamondDensity     ( 3.52      ) ; // from J.Fast 11/20/99

   const FReal kCalciumAtomicWt    ( 40.078    ) ;
   const FReal kCalciumAtomicNo    ( 20        ) ;
   const FReal kCalciumDensity     ( 1         ) ;

   const FReal kFluorineAtomicWt   ( 18.9984032) ;
   const FReal kFluorineAtomicNo   ( 9         ) ;
   const FReal kFluorineDensity    ( 1         ) ;

   // correction to gas density from STP to 25degC & 900' above sea level
   const FReal    kSTPtoCLEODensityCorrection ( 0.895    ) ;

   const FReal kNitrogenGasAtomicWt( 14.00674  ) ;
   const FReal kNitrogenGasAtomicNo( 7         ) ;
   const FReal kNitrogenGasDensity ( 0.001250*kSTPtoCLEODensityCorrection ) ;

   const FReal kBromineAtomicWt   ( 79.904    ) ;
   const FReal kBromineAtomicNo   ( 35        ) ;
   const FReal kBromineDensity    ( 1         ) ;

   const FReal kTinAtomicWt   ( 118.7     ) ;
   const FReal kTinAtomicNo   ( 50        ) ;
   const FReal kTinDensity    ( 1         ) ;

   const FReal kZincAtomicWt   ( 65.39     ) ;
   const FReal kZincAtomicNo   ( 30        ) ;
   const FReal kZincDensity    ( 1         ) ;

   //------------------ Done with single component materials ----------------

   static const UInt16   nElement ( 40 ) ; // single component mixtures

   // we do single component mixtures to guarantee correct rad lengths
   // which otherwise would have to be typed in and therefore be error-prone.

   const FInteger elementIndex[   nElement] = {
      kHydrogenMatIndex   ,
      kDeuteriumMatIndex  ,
      kHeliumMatIndex     ,
      kLithiumMatIndex    ,
      kBerylliumMatIndex  ,
      kCarbonMatIndex     ,
      kNitrogenMatIndex   ,
      kNeonMatIndex       ,
      kAluminumMatIndex   ,
      kIronMatIndex       ,
      kCopperMatIndex     ,
      kTungstenMatIndex   ,
      kLeadMatIndex       ,
      kUraniumMatIndex    ,
      kAirMatIndex        ,
      kVacuumMatIndex     ,
      kSilverMatIndex     ,
      kGoldMatIndex       ,
      kSiliconMatIndex    ,
      kOxygenMatIndex     , 
      kMagnesiumMatIndex  , 
      kPhosphorusMatIndex ,
      kSulfurMatIndex     ,
      kChromiumMatIndex   , 
      kManganeseMatIndex  ,
      kNickelMatIndex     ,
      kMolybdenumMatIndex , 
      kCesiumMatIndex     ,
      kIodineMatIndex     ,
      kNeodymiumMatIndex  ,
      kBoronMatIndex      ,
      kChlorineMatIndex   ,
      kDiamondMatIndex    ,
      kCalciumMatIndex    ,
      kFluorineMatIndex   ,
      kNitrogenGasMatIndex,
      kBromineMatIndex    ,
      kTinMatIndex        ,
      kZincMatIndex       ,
      -1 } ;

   const string   elementString[  nElement] = { 
      kHydrogenMatID   ,
      kDeuteriumMatID  ,
      kHeliumMatID     ,
      kLithiumMatID    ,
      kBerylliumMatID  ,
      kCarbonMatID     ,
      kNitrogenMatID   ,
      kNeonMatID       ,
      kAluminumMatID   ,
      kIronMatID       ,
      kCopperMatID     ,
      kTungstenMatID   ,
      kLeadMatID       ,
      kUraniumMatID    ,
      kAirMatID        ,
      kVacuumMatID     ,
      kSilverMatID     ,
      kGoldMatID       ,
      kSiliconMatID    ,
      kOxygenMatID     ,
      kMagnesiumMatID  ,
      kPhosphorusMatID ,
      kSulfurMatID     ,
      kChromiumMatID   ,
      kManganeseMatID  ,
      kNickelMatID     ,
      kMolybdenumMatID ,
      kCesiumMatID     ,
      kIodineMatID     , 
      kNeodymiumMatID  ,
      kBoronMatID      ,
      kChlorineMatID   ,
      kDiamondMatID    ,
      kCalciumMatID    ,
      kFluorineMatID   ,
      kNitrogenGasMatID,
      kBromineMatID    ,
      kTinMatID        ,
      kZincMatID       ,
      "Marker" } ;

   const FReal    elementAtomicWt[nElement] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      kSilverAtomicWt     ,
      kGoldAtomicWt       , 
      kSiliconAtomicWt    ,
      kOxygenAtomicWt     ,
      kMagnesiumAtomicWt  ,
      kPhosphorusAtomicWt ,
      kSulfurAtomicWt     , 
      kChromiumAtomicWt   , 
      kManganeseAtomicWt  ,
      kNickelAtomicWt     ,
      kMolybdenumAtomicWt ,
      kCesiumAtomicWt     ,
      kIodineAtomicWt     ,
      kNeodymiumAtomicWt  ,
      kBoronAtomicWt      ,
      kChlorineAtomicWt   ,
      kDiamondAtomicWt    ,
      kCalciumAtomicWt    ,
      kFluorineAtomicWt   ,
      kNitrogenGasAtomicWt,
      kBromineAtomicWt    ,
      kTinAtomicWt        ,
      kZincAtomicWt       ,
      -1 } ;

   const FReal    elementAtomicNo[nElement] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      kSilverAtomicNo     ,
      kGoldAtomicNo       , 
      kSiliconAtomicNo    ,
      kOxygenAtomicNo     ,
      kMagnesiumAtomicNo  ,
      kPhosphorusAtomicNo ,
      kSulfurAtomicNo     ,
      kChromiumAtomicNo   ,
      kManganeseAtomicNo  ,
      kNickelAtomicNo     , 
      kMolybdenumAtomicNo , 
      kCesiumAtomicNo     ,
      kIodineAtomicNo     ,
      kNeodymiumAtomicNo  ,
      kBoronAtomicNo      ,
      kChlorineAtomicNo   ,
      kDiamondAtomicNo    ,
      kCalciumAtomicNo    ,
      kFluorineAtomicNo   ,
      kNitrogenGasAtomicNo,
      kBromineAtomicNo    ,
      kTinAtomicNo        ,
      kZincAtomicNo       ,
      -1 } ;

   const FReal    elementDensity[ nElement] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      kSilverDensity     ,
      kGoldDensity       , 
      kSiliconDensity    ,
      kOxygenDensity     ,
      kMagnesiumDensity  ,
      kPhosphorusDensity ,
      kSulfurDensity     ,
      kChromiumDensity   ,
      kManganeseDensity  ,
      kNickelDensity     ,
      kMolybdenumDensity ,
      kCesiumDensity     ,
      kIodineDensity     , 
      kNeodymiumDensity  , 
      kBoronDensity      ,
      kChlorineDensity   , 
      kDiamondDensity    , 
      kCalciumDensity    ,
      kFluorineDensity   ,
      kNitrogenGasDensity,
      kBromineDensity    ,
      kTinDensity        ,
      kZincDensity       ,
      -1 } ;

   // the purpose of these asserts is to check that the
   // arrays initialized above have the "right" last element,
   // a non-definitive check for typo-type errors
   assert( -1       == elementIndex[    nElement-1 ] ) ;
   assert( "Marker" == elementString[   nElement-1 ] ) ;
   assert( -1       == elementAtomicWt[ nElement-1 ] ) ;
   assert( -1       == elementAtomicNo[ nElement-1 ] ) ;
   assert( -1       == elementDensity[  nElement-1 ] ) ;

   if( nElement > maxMaterials )
   {
      report( EMERGENCY, kReport ) << "Exceeded maxMaterials ="
				   << maxMaterials << ", quitting ..." 
				   << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }

   for( UInt16 iElement ( 0 ) ; iElement != nElement-1 ; ++iElement )
   {
      const FInteger index ( elementIndex[ iElement ] ) ;

      const string& stringName ( elementString[iElement] ) ;

      if( 0 != elementAtomicWt[iElement] )
      {
	 const string name ( stringName + "                    " ) ;

	 FChar elementName[20] ;
	 for( UInt16 i ( 0 ); i != 19 ; ++i ) 
	 { elementName[i] = name[i] ; }
	 elementName[19] = '$' ;

	 static const FInteger elementNumber ( 1 ) ;
	 FReal elementWeight                 ( 1. ) ; // also return variable

	 gsmixt_(
	    index                        ,
	    elementName                  ,
	    &elementAtomicWt[ iElement ] ,
	    &elementAtomicNo[ iElement ] ,
	    elementDensity[   iElement ] ,
	    elementNumber                ,
	    &elementWeight               ,
	    nameLength
	    );
      }

      stringIntMap()[ stringName ] = index ;

      // now fill up atomic wts, numbers, densities

      FChar gName[20]          ;
      FReal radiationLength    ;
      FReal absorptionLength   ;
      static const UInt32 kG3BUFSIZE ( 1000 ) ;
      static FReal uBuf[  kG3BUFSIZE ] ;

      FInteger nBuf            ;

      gfmate_( index                   , 
	       gName                   , 
	       xAtomicWeight[  index ] , 
	       xAtomicNumber[  index ] ,
	       xDensity[       index ] , 
	       radiationLength         , 
	       absorptionLength        , 
	       uBuf                    , 
	       nBuf                    ,
	       nameLength               ) ;

      VecWt vecWt ;
      vecWt.reserve( 1 ) ;
      vecWt.push_back( DGMaterial::WeightedElement(
	 DGMaterial::Element( atomicWeight[ index ],
			      atomicNumber[ index ] ), 1. ) ) ;
      m_wtdElt[ stringName ] = vecWt ;

      if( kG3BUFSIZE < nBuf )
      {
	 report( EMERGENCY, kReport ) 
	    << "Default buffer size overfilled, exiting" << endl ;
	 assert( false ) ;
	 ::exit( 1 ) ;
      }
   }

   xAtomicWeight[ kVacuumMatIndex ] = 1.e-5 ;
   xAtomicNumber[ kVacuumMatIndex ] = 1.e-5 ;

   const FReal kCarbonAtomicWt   ( atomicWeight[ kCarbonMatIndex   ] ) ;
   const FReal kHydrogenAtomicWt ( atomicWeight[ kHydrogenMatIndex ] ) ;

   // now on to mixed materials -------- first specific details of mixtures

   // note that mixtures should not be made of other mixtures
   // as only approximate rad lengths can be computed from the
   // average Z and A that can be input to gsmixt_ ...
   // unless one does not care about the smallish differences.

   const FReal    kHeliumDensity 
      ( .0001786*kSTPtoCLEODensityCorrection ) ; // at STP (PDG98) * correction

   const FReal    kPropaneDensity 
      ( 0.002017* kSTPtoCLEODensityCorrection ) ; // at STP: PDG98 * correction

   const FInteger kHeliumPropaneMixNumber        ( 3 ) ;
   const FInteger kHeliumPropaneAtomicIndex[3] = { kHeliumMatIndex   ,
						   kCarbonMatIndex   ,
						   kHydrogenMatIndex   } ;

   const FReal    cHeliumPropaneWeights[2]     = { 0.6, 0.4 } ;

   const FReal    kHeliumPropaneDensity        
      ( ( kHeliumDensity *cHeliumPropaneWeights[0] +
	  kPropaneDensity*cHeliumPropaneWeights[1] )/
	( cHeliumPropaneWeights[0] +
	  cHeliumPropaneWeights[1]     ) ) ;

   const FReal kPropaneWt ( 3*kCarbonAtomicWt + 8*kHydrogenAtomicWt ) ;
   const FReal kPropaneFactor 
      ( cHeliumPropaneWeights[1]*kPropaneDensity/kHeliumPropaneDensity ) ;
   const FReal    kHeliumPropaneWeights[3]     = { // 60:40 by partial pressure
      cHeliumPropaneWeights[0]*kHeliumDensity /kHeliumPropaneDensity ,
      kPropaneFactor*3*kCarbonAtomicWt  /kPropaneWt ,
      kPropaneFactor*8*kHydrogenAtomicWt/kPropaneWt  } ;


   const FInteger kGasWireVaporMixNumber        ( 9 ) ;
   const FInteger kGasWireVaporAtomicIndex[9] = { kHeliumMatIndex     ,
						  kCarbonMatIndex     ,
						  kHydrogenMatIndex   ,
						  kTungstenMatIndex   ,
						  kGoldMatIndex       ,
						  kMagnesiumMatIndex  ,
						  kManganeseMatIndex  ,
						  kChromiumMatIndex   ,
						  kAluminumMatIndex     } ;
   const FReal    kGasWireVaporWeights[    9] = { 0.0744,
						  0.4580,
						  0.1026,
						  0.0230,
						  0.0570,
						  0.0143,
						  0.00034,
						  0.00034,
						  0.27002   } ;

   const FReal    kGasWireVaporDensity          ( .001288 ) ; 


   const FInteger kAluminum6061MixNumber        ( 5 ) ;
   const FInteger kAluminum6061AtomicIndex[5] = { kSiliconMatIndex    ,
						  kCopperMatIndex     ,
						  kMagnesiumMatIndex  ,
						  kChromiumMatIndex   ,
						  kAluminumMatIndex     } ;
   const FReal    kAluminum6061Weights[    5] = {
      .006, .0028, .01, .002, .9792 } ;
   const FReal    kAluminum6061Density          ( 2.7 ) ; 


   const FInteger kAluminum5056MixNumber        ( 4 ) ;
   const FInteger kAluminum5056AtomicIndex[4] = { kMagnesiumMatIndex  ,
						  kManganeseMatIndex  ,
						  kChromiumMatIndex   ,
						  kAluminumMatIndex     } ;
   const FReal    kAluminum5056Weights[    4] = {
      .05, .0012, .0012, .9476 } ;
   const FReal    kAluminum5056Density          ( 2.64 ) ; 

   const FInteger kStainless316MixNumber         (  5 ) ; // from DPP
   const FInteger kStainless316AtomicIndex[5]  = { kCarbonMatIndex     ,
						   kChromiumMatIndex   ,
						   kNickelMatIndex     ,
						   kMolybdenumMatIndex ,
						   kIronMatIndex         } ;
   const FReal    kStainless316Weights[   5  ] = {
      .0008, .17, .12, .025, .6842 } ;
   const FReal    kStainless316Density          ( 7.98 ) ; // From DPP

   const FInteger kRohacellMixNumber        ( 3 ) ;
   const FInteger kRohacellAtomicIndex[3] = { kCarbonMatIndex   ,
					      kOxygenMatIndex   ,
					      kHydrogenMatIndex   } ;
   const FReal    kRohacellWeights[    3] = { .77, .16, .07 } ;
   const FReal    kRohacellDensity          ( 0.05 ) ;

   const FInteger kEpoxyMixNumber        ( 3 ) ;
   const FInteger kEpoxyAtomicIndex[3] = { kCarbonMatIndex   ,
					   kOxygenMatIndex   ,
					   kHydrogenMatIndex   } ;
   const FReal    kEpoxyWeights[    3] = { .77, .16, .07 } ;
   const FReal    kEpoxyDensity          ( 1.4 ) ;

   // Inner tube material
   // Dimensions of final tube are:
   //       9.532" OD, 9.321" ID, 27.6" long ---> 1413.1 cc
   //
   // The numbers below from Steve Glenn's  lab notebook called "DR III 1996"
   // Pg 105: Rohacell has density 0.05 g/cc, thickness 0.105"
   //         Total mass is .05 x (27.6" x 29.6" x 0.105")*2.54^3 = 70.3g 
   // Pg 103-104: Epoxy total is 43.3 + 65.3 + 0.8 = 109.4 g
   //             Al foil: 11 strips x 2" x 49.3" = 12.44cc = 33.18g
   //             Outer will be 0.89 x (inner) [ see pg 105 : 1.09/1.22 ]
   //             So outer Al is 29.5g. Total Al = 62.7g.

   // Summary: 70.3g Rohacell, 62.7g Al, 109.4g Epoxy --> total = 242.4g
   //          Density = 242.4g/1413.1 cc = 0.1715 g/cc
   // So...
   //    Since Rohacell and epoxy are same material just diff density
   //    treat as same: 70.3 + 109.4 = 179.7, 179.7/242.4 = 74.1%; Al = 25.9%
   //

   const FInteger kDR3InnerTubeMaterialMixNumber      ( 4 ) ;
   const FInteger kDR3InnerTubeMaterialAtomicIndex[4] = { kCarbonMatIndex   ,
							  kOxygenMatIndex   ,
							  kHydrogenMatIndex ,
							  kAluminumMatIndex };
   const FReal    kDR3InnerTubeMaterialWeights[    4] = {
      .571, .119, .052, .258 } ;
   const FReal    kDR3InnerTubeMaterialDensity ( 0.1715 ) ;

   const FInteger kCesiumIodideMixNumber        ( -2 ) ;
   const FInteger kCesiumIodideAtomicIndex[2] = { kCesiumMatIndex   ,
						  kIodineMatIndex     } ;
   const FReal    kCesiumIodideWeights[    2] = { 1, 1 } ;
   const FReal    kCesiumIodideDensity          ( 4.53 ) ;

   // comments below from cgmate in cleo2 cleog
   // - G10   = 60% SiO2, 40% epoxy : Rev.Mod.Phys. 56 No2(1984)S35
   //   Epoxy = 77% C, 16% O, 7% H by weight : Modern Plastic
   //           Encyclopedia 58(1981-82)10A p.18
   //      DATA DG10 /  1.7 /
   //      DATA AG10 / 16.00, 12.01, 28.09, 1.01  /
   //      DATA ZG10 /  8.08,  6.00, 14.00, 1.00  /
   //      DATA WG10 / 0.384, 0.308, 0.280, 0.028 /

   const FInteger kG10MixNumber        ( 4 ) ;
   const FInteger kG10AtomicIndex[4] = { kOxygenMatIndex    ,
					 kCarbonMatIndex    , 
                                         kSiliconMatIndex   ,
					 kHydrogenMatIndex     } ;

   const FReal    kG10Weights[    4] = { .384, .308, .280, .028 } ;
   const FReal    kG10Density          ( 1.7 ) ;

   // D.Cinabro 9 Jan 1998, Numbers from Weiran Lou 
   // CESR 3 Recs are Nd(2)-Fe(14)-B(1)
   //      DATA DREC /  7.5 /
   //      DATA AREC / 144.24, 55.85, 10.81 /
   //      DATA ZREC / 60.0  , 26.0 ,  5.0  /
   //      DATA WREC /  2.0,   14.0 ,  1.0  /

   const FInteger kRecQuadMixNumber        ( -3 ) ;
   const FInteger kRecQuadAtomicIndex[3] = { kNeodymiumMatIndex ,
					     kIronMatIndex      ,
					     kBoronMatIndex       } ;
   const FReal    kRecQuadWeights[    3] = { 2, 14, 1 } ;
   const FReal    kRecQuadDensity          ( 7.5 ) ;

   // Mylar, C5-H4-O2
   //      DATA DMYL /1.39/
   //      DATA AMYL /12.01, 1.01, 16.00/
   //      DATA ZMYL / 6.0,  1.0,   8.0/
   //      DATA WMYL / 5.0,  4.0,   2.0/
 
   const FInteger kMylarMixNumber        ( -3 ) ;
   const FInteger kMylarAtomicIndex[3] = { kCarbonMatIndex   ,
					   kHydrogenMatIndex ,
					   kOxygenMatIndex       } ;
   const FReal    kMylarWeights[    3] = { 5, 4, 2 } ;
   const FReal    kMylarDensity          ( 1.39 ) ;   
 
   // Kevlar
   // DATA DKVL / 1.41 /
   // DATA AKVL / 1.01, 12.01, 14.01, 16.00  /
   // DATA ZKVL / 1.0 , 6.0  , 7.0  , 8.08  /
   // DATA WKVL / 0.042, 0.706, 0.118 , 0.134 /

   const FInteger kKevlarMixNumber        ( 4 ) ;
   const FInteger kKevlarAtomicIndex[4] = { kCarbonMatIndex   ,
					    kHydrogenMatIndex ,
					    kNitrogenMatIndex ,
					    kOxygenMatIndex       } ;
   const FReal    kKevlarWeights[    4] = { 0.706, 0.042, 0.118, 0.134 } ;
   const FReal    kKevlarDensity          ( 1.41 ) ;   

   //  - Lucite C6-H8-O2,
   //   
   //      DATA DLUC /1.20/
   //      DATA ALUC /12.01, 1.01, 16.00/
   //      DATA ZLUC / 6.0,  1.0,   8.0/
   //      DATA WLUC / 6.0,  8.0,   2.0/

   const FInteger kLuciteMixNumber        ( -3 ) ;
   const FInteger kLuciteAtomicIndex[3] = { kCarbonMatIndex   ,
					    kHydrogenMatIndex ,
					    kOxygenMatIndex       } ;
   const FReal    kLuciteWeights[    3] = { 6, 8, 2 } ;
   const FReal    kLuciteDensity ( 1.2 ) ;

   // Polyvinylchloride: [CH2 Cl CH]n        ( for muons )
   // DATA DPVC /1.39/
   // DATA APVC /12.01, 1.01, 35.45/
   // DATA ZPVC / 6.0,  1.0,  17.0 /
   // DATA WPVC / 2.0,  3.0,   1.0 /
 
   const FInteger kPVCMixNumber        ( -3 ) ;
   const FInteger kPVCAtomicIndex[3] = { kCarbonMatIndex   ,
					 kHydrogenMatIndex ,
					 kChlorineMatIndex       } ;
   const FReal    kPVCWeights[    3] = { 2, 3, 1 } ;
   const FReal    kPVCDensity          ( 1.39 ) ;   

   // signal cable wires; made of copper, polyethylene and PVC.  
   // DATA ACAB /12.01, 1.01, 35.45, 63.55, 14.01/
   // DATA ZCAB /6.0, 1.0, 17.0, 29.0, 7.0/
   // DATA WCAB /0.191, 0.028, 0.12, 0.658, 0.003/
   // DATA DCAB /1.170 /

   const FInteger kCableMixNumber        ( 5 ) ;
   const FInteger kCableAtomicIndex[5] = { kCopperMatIndex   ,
					   kCarbonMatIndex   ,
					   kChlorineMatIndex ,
					   kHydrogenMatIndex ,
					   kNitrogenMatIndex 
      } ;
   const FReal    kCableWeights[5] = { .658, .191, .12, .028, .003 } ;
   const FReal    kCableDensity          ( 1.17 ) ; // !!!! too small !!!!????

   // water for the beam pipe

   const FInteger kWaterMixNumber        ( -2 ) ;
   const FInteger kWaterAtomicIndex[2] = {  kHydrogenMatIndex ,
					    kOxygenMatIndex       } ;
   const FReal    kWaterWeights[    2] = { 2, 1 } ;
   const FReal    kWaterDensity ( 1. ) ; // effect from Pressure??

   // LiF for Rich

   const FInteger kLithiumFluorideMixNumber        ( -2 ) ;
   const FInteger kLithiumFluorideAtomicIndex[2] = {  kLithiumMatIndex ,
						      kFluorineMatIndex     } ;
   const FReal    kLithiumFluorideWeights[    2] = { 1, 1 } ;
   const FReal    kLithiumFluorideDensity ( 2.64 ) ;

   // CaF for Rich

   const FInteger kCalciumFluorideMixNumber        ( -2 ) ;
   const FInteger kCalciumFluorideAtomicIndex[2] = {  kCalciumMatIndex ,
						      kFluorineMatIndex     } ;
   const FReal    kCalciumFluorideWeights[    2] = { 1, 2 } ;
   const FReal    kCalciumFluorideDensity ( 3.18 ) ;

   // Methane-TEA for Rich (Methane = CH4, TEA=C6-H15-N)

   const FInteger kMethaneTEAMixNumber        ( -3 ) ;
   const FInteger kMethaneTEAAtomicIndex[3] = {  kCarbonMatIndex   ,
						 kHydrogenMatIndex ,
						 kNitrogenMatIndex  } ;
//      p_tea = p0 * exp (dhr * (1/t0 - 1/tt))
   FReal ppM ( 760 ) ;
   FReal ppT ( 73.2*exp( 4299.*(1./300. - 1./288.) ) ) ; // from Tomasz S.
   const FReal sumMT ( ppM + ppT ) ;
   ppM = ppM/sumMT ; // normalize
   ppT = ppT/sumMT ;

   const FReal    kMethaneTEAWeights[    3] = { 
      ppM*1 + ppT*6, ppM*4 + ppT*15, ppM*0 + ppT*1 } ;

   const FReal    kMethaneTEADensity ( // modify density for TEA presence
      0.000717*(ppM+ppT*(101.22/16.05))*kSTPtoCLEODensityCorrection ) ;

   // carbon fiber for RICH
   //* DCFE  - Density of CARBONFIBER-EPOXY  (Epoxy= 50% DGEBA, 50% TETA)
   //* ACFE  - array of atomic numbers of CFE components
   //* ZCFE  - array of Z's of CFE components
   //* WCFE  - relative weights of CFE components
   //*
   //      DATA DCFE / 1.36 /
   //      DATA ACFE / 1.01, 12.01, 14.01, 16.00  /
   //      DATA ZCFE / 1.0 , 6.0  , 7.0  , 8.08  /
   //      DATA WCFE / 0.06, 0.795, 0.05 , 0.095 /

   const FInteger kCarbonFiberMixNumber        ( 4 ) ;
   const FInteger kCarbonFiberAtomicIndex[4] = {  kHydrogenMatIndex ,
						  kCarbonMatIndex   ,
						  kNitrogenMatIndex ,
						  kOxygenMatIndex    } ;
   const FReal    kCarbonFiberWeights[    4] = { .06, .795, .05, .095 } ;

   // this density is computed from an actual piece of the
   // fiber made as a prototype for RICH; measured 4/1/99 by Heltsley/Cherwinka
   const FReal    kCarbonFiberDensity ( 1.42 ) ;

   // BeO for SV Hybrids

   const FInteger kBerylliumOxideMixNumber        ( -2 ) ;
   const FInteger kBerylliumOxideAtomicIndex[2] = {  kBerylliumMatIndex ,
						     kOxygenMatIndex     } ;
   const FReal    kBerylliumOxideWeights[    2] = { 1, 1 } ;
   const FReal    kBerylliumOxideDensity ( 2.86 ) ;

   // carbon fiber for SV

   const FInteger kSVCarbonFiberMixNumber        ( 5 ) ;
   const FInteger kSVCarbonFiberAtomicIndex[5] = {  kHydrogenMatIndex ,
						    kCarbonMatIndex   ,
						    kNitrogenMatIndex ,
						    kOxygenMatIndex   ,
						    kBromineMatIndex   } ;

   // from J. Fast 7/6/99
   const FReal    kSVCarbonFiberWeights[    5] = { .028, .823, .011,
						   .023, .115 } ;
   const FReal    kSVCarbonFiberDensity ( 1.584 ) ;

   const FReal    kVacuumDensity  ( density[ kVacuumMatIndex ] ) ;

   //---------------------------------------------------------

   // same as aluminum6061 but account for holes by reducing density
   const FInteger kDREndplateHoleyMixNumber        ( 5 ) ;
   const FInteger kDREndplateHoleyAtomicIndex[5] = { kSiliconMatIndex    ,
						     kCopperMatIndex     ,
						     kMagnesiumMatIndex  ,
						     kChromiumMatIndex   ,
						     kAluminumMatIndex     } ;
   const FReal    kDREndplateHoleyWeights[    5] = {
      .006, .0028, .01, .002, .9792 } ;
   const FReal    kDREndplateHoleyDensity          ( 0.838*2.7 ) ; 

   // mix for preamp regions

   const FInteger kDRPreampVaporMixNumber        ( 11 ) ;
   const FInteger kDRPreampVaporAtomicIndex[11] = { 
                                                    kCopperMatIndex     ,
						    kCarbonMatIndex     ,
						    kOxygenMatIndex     ,
						    kAluminumMatIndex   ,
						    kTinMatIndex        ,
						    kLeadMatIndex       ,
						    kSiliconMatIndex    ,
						    kHydrogenMatIndex   ,
						    kZincMatIndex       ,
						    kNickelMatIndex     ,
						    kGoldMatIndex       
                                                                         } ;
   const FReal    kDRPreampVaporWeights[   11] = {
                                                   0.2568 ,
						   0.1947 ,
						   0.1511 ,
						   0.1243 ,
						   0.1054 ,
						   0.0701 ,
						   0.0651 ,
						   0.0269 ,
						   0.0046 ,
						   0.0006 ,
						   0.0004 
                                                                   } ;
   const FReal    kDRPreampVaporDensity ( 0.276 ) ;

   // mix for NOpreamp regions

   const FInteger kDRNoPreampVaporMixNumber        ( 7 ) ;
   const FInteger kDRNoPreampVaporAtomicIndex[7] = { 
						     kOxygenMatIndex     ,
						     kCarbonMatIndex     ,
						     kSiliconMatIndex    ,
						     kAluminumMatIndex   ,
						     kCopperMatIndex     ,
						     kHydrogenMatIndex   ,
						     kGoldMatIndex       
                                                                           } ;
   const FReal    kDRNoPreampVaporWeights[   7] = {
						    0.2653 ,
						    0.2342 ,
						    0.1934 ,
                                                    0.1608 ,
						    0.1242 ,
						    0.0213 ,
						    0.0008
                                                                   } ;
   const FReal    kDRNoPreampVaporDensity ( 0.048 ) ;


   // mix for DR endplate surface, includes DR3 and SI3 cables!

   const FInteger kDROnEndplateMixNumber        ( 6 ) ;
   const FInteger kDROnEndplateAtomicIndex[6] = { 
						     kCopperMatIndex     ,
						     kCarbonMatIndex     ,
						     kHydrogenMatIndex   ,
						     kChlorineMatIndex   ,
						     kFluorineMatIndex   ,
						     kAluminumMatIndex   
                                                                           } ;

   const FReal    kDROnEndplateWeights[   6] = {
                                                  0.4707 ,
						  0.4011 ,
						  0.0656 ,
						  0.0443 ,
						  0.0125 ,
						  0.0058
                                                                   } ;
   const FReal    kDROnEndplateDensity ( 0.655 ) ;

   // -------- array setup for mixed materials ---------------------------

   static const UInt16 nMix (   41 ) ;

   static const UInt16 maxMix ( 11 ) ;

   const FInteger mixIndex[     nMix ]           = {
      kHeliumPropaneMatIndex        ,
      kAluminum6061MatIndex         ,
      kStainless316MatIndex         ,
      kRohacellMatIndex             ,
      kEpoxyMatIndex                ,
      kDR3InnerTubeMaterialMatIndex ,
      kCesiumIodideMatIndex         ,
      kG10MatIndex                  ,
      kRecQuadMatIndex              ,
      kMylarMatIndex                ,
      kKevlarMatIndex               ,
      kLuciteMatIndex               ,
      kPVCMatIndex                  ,
      kCableMatIndex                ,
      kWaterMatIndex                ,
      kLithiumFluorideMatIndex      ,
      kCalciumFluorideMatIndex      ,
      kMethaneTEAMatIndex           ,
      kCarbonFiberMatIndex          ,
      kBerylliumOxideMatIndex       ,
      kSVCarbonFiberMatIndex        ,
      kVacuumLoCutMatIndex            ,
      kVacuumCoilMatIndex             ,
      kVacuumCoilNFMatIndex           ,
      kAirFieldMatIndex               ,
      kAirLoCutMatIndex               ,
      kAirLCFieldMatIndex             ,
      kAirLCFPrecMatIndex             ,
      kAluminumLoCutMatIndex          ,
      kAluminumMuonMatIndex           ,
      kAluminumCoilMatIndex           ,
      kAluminumCoilNFMatIndex         ,
      kMylarCoilMatIndex              ,
      kMylarCoilNFMatIndex            ,
      kAluminum5056MatIndex           ,
      kGasWireVaporMatIndex           ,
      kDREndplateHoleyMatIndex        ,
      kDRPreampVaporMatIndex          ,
      kDRNoPreampVaporMatIndex        ,
      kDROnEndplateMatIndex           ,
      -1 } ;

   const string   mixString[    nMix ]           = {
      kHeliumPropaneMatID        ,
      kAluminum6061MatID         ,
      kStainless316MatID         ,
      kRohacellMatID             ,
      kEpoxyMatID                ,
      kDR3InnerTubeMaterialMatID ,
      kCesiumIodideMatID         ,
      kG10MatID                  ,
      kRecQuadMatID              ,
      kMylarMatID                ,
      kKevlarMatID               ,
      kLuciteMatID               ,
      kPVCMatID                  ,
      kCableMatID                ,
      kWaterMatID                ,
      kLithiumFluorideMatID      ,
      kCalciumFluorideMatID      ,
      kMethaneTEAMatID           ,
      kCarbonFiberMatID          ,
      kBerylliumOxideMatID       ,
      kSVCarbonFiberMatID        ,
      kVacuumLoCutMatID            ,
      kVacuumCoilMatID             ,
      kVacuumCoilNFMatID           ,
      kAirFieldMatID               ,
      kAirLoCutMatID               ,
      kAirLCFieldMatID             ,
      kAirLCFPrecMatID             ,
      kAluminumLoCutMatID          ,
      kAluminumMuonMatID           ,
      kAluminumCoilMatID           ,
      kAluminumCoilNFMatID         ,
      kMylarCoilMatID              ,
      kMylarCoilNFMatID            ,
      kAluminum5056MatID           ,
      kGasWireVaporMatID           ,
      kDREndplateHoleyMatID        ,
      kDRPreampVaporMatID          ,
      kDRNoPreampVaporMatID        ,
      kDROnEndplateMatID           ,
      "Marker" } ;

   const UInt16   mixAtomicIndex[ nMix ][ maxMix ] = {
      kHeliumPropaneAtomicIndex[0]        , 
      kHeliumPropaneAtomicIndex[1]        , 
      kHeliumPropaneAtomicIndex[2]        , 0,0,0,0,0,0,0, 0,
      kAluminum6061AtomicIndex[0]         ,  
      kAluminum6061AtomicIndex[1]         , 
      kAluminum6061AtomicIndex[2]         ,   
      kAluminum6061AtomicIndex[3]         , 
      kAluminum6061AtomicIndex[4]         , 0,0,0,0,0, 0,
      kStainless316AtomicIndex[0]         ,  
      kStainless316AtomicIndex[1]         , 
      kStainless316AtomicIndex[2]         ,  
      kStainless316AtomicIndex[3]         , 
      kStainless316AtomicIndex[4]         , 0,0,0,0,0, 0,
      kRohacellAtomicIndex[0]             ,  
      kRohacellAtomicIndex[1]             , 
      kRohacellAtomicIndex[2]             , 0,0,0,0,0,0,0, 0, 
      kEpoxyAtomicIndex[0]                ,
      kEpoxyAtomicIndex[1]                , 
      kEpoxyAtomicIndex[2]                , 0,0,0,0,0,0,0, 0,
      kDR3InnerTubeMaterialAtomicIndex[0] , 
      kDR3InnerTubeMaterialAtomicIndex[1] ,
      kDR3InnerTubeMaterialAtomicIndex[2] ,
      kDR3InnerTubeMaterialAtomicIndex[3] , 0,0,0,0,0,0, 0,
      kCesiumIodideAtomicIndex[0]         ,  
      kCesiumIodideAtomicIndex[1]         , 0,0,0,0,0,0,0,0, 0,       
      kG10AtomicIndex[0]                  ,
      kG10AtomicIndex[1]                  ,
      kG10AtomicIndex[2]                  ,
      kG10AtomicIndex[3]                  , 0,0,0,0,0,0, 0,
      kRecQuadAtomicIndex[0]              ,
      kRecQuadAtomicIndex[1]              ,
      kRecQuadAtomicIndex[2]              , 0,0,0,0,0,0,0, 0,
      kMylarAtomicIndex[0]                ,
      kMylarAtomicIndex[1]                ,
      kMylarAtomicIndex[2]                , 0,0,0,0,0,0,0, 0,
      kKevlarAtomicIndex[0]               ,
      kKevlarAtomicIndex[1]               ,
      kKevlarAtomicIndex[2]               ,
      kKevlarAtomicIndex[3]               , 0,0,0,0,0,0, 0,
      kLuciteAtomicIndex[0]               ,
      kLuciteAtomicIndex[1]               , 
      kLuciteAtomicIndex[2]               , 0,0,0,0,0,0,0, 0,
      kPVCAtomicIndex[0]                  ,
      kPVCAtomicIndex[1]                  ,
      kPVCAtomicIndex[2]                  , 0,0,0,0,0,0,0, 0,
      kCableAtomicIndex[0]                ,
      kCableAtomicIndex[1]                ,
      kCableAtomicIndex[2]                ,
      kCableAtomicIndex[3]                ,
      kCableAtomicIndex[4]                , 0,0,0,0,0, 0,
      kWaterAtomicIndex[0]                ,  
      kWaterAtomicIndex[1]                , 0,0,0,0,0,0,0,0, 0,       
      kLithiumFluorideAtomicIndex[0]      ,  
      kLithiumFluorideAtomicIndex[1]      , 0,0,0,0,0,0,0,0,  0,    
      kCalciumFluorideAtomicIndex[0]      ,  
      kCalciumFluorideAtomicIndex[1]      , 0,0,0,0,0,0,0,0, 0,      
      kMethaneTEAAtomicIndex[0]           ,  
      kMethaneTEAAtomicIndex[1]           ,
      kMethaneTEAAtomicIndex[2]           , 0,0,0,0,0,0,0, 0,
      kCarbonFiberAtomicIndex[0]          ,  
      kCarbonFiberAtomicIndex[1]          ,       
      kCarbonFiberAtomicIndex[2]          ,       
      kCarbonFiberAtomicIndex[3]          , 0,0,0,0,0,0, 0,
      kBerylliumOxideAtomicIndex[0]       ,  
      kBerylliumOxideAtomicIndex[1]       , 0,0,0,0,0,0,0,0, 0,       
      kSVCarbonFiberAtomicIndex[0]        ,  
      kSVCarbonFiberAtomicIndex[1]        ,       
      kSVCarbonFiberAtomicIndex[2]        ,       
      kSVCarbonFiberAtomicIndex[3]        ,       
      kSVCarbonFiberAtomicIndex[4]        , 0,0,0,0,0, 0,
      kVacuumMatIndex,      0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
      kVacuumMatIndex,      0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
      kVacuumMatIndex,      0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
      kNitrogenGasMatIndex, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
      kNitrogenGasMatIndex, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
      kNitrogenGasMatIndex, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
      kNitrogenGasMatIndex, 0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
      kAluminumMatIndex,    0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
      kAluminumMatIndex,    0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
      kAluminumMatIndex,    0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
      kAluminumMatIndex,    0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
      kMylarAtomicIndex[0]                ,
      kMylarAtomicIndex[1]                ,
      kMylarAtomicIndex[2]                , 0,0,0,0,0,0,0,0,
      kMylarAtomicIndex[0]                ,
      kMylarAtomicIndex[1]                ,
      kMylarAtomicIndex[2]                , 0,0,0,0,0,0,0,0,
      kAluminum5056AtomicIndex[0] ,
      kAluminum5056AtomicIndex[1] ,
      kAluminum5056AtomicIndex[2] ,
      kAluminum5056AtomicIndex[3]         , 0,0,0,0,0,0,0,
      kGasWireVaporAtomicIndex[0],
      kGasWireVaporAtomicIndex[1],
      kGasWireVaporAtomicIndex[2],
      kGasWireVaporAtomicIndex[3],
      kGasWireVaporAtomicIndex[4],
      kGasWireVaporAtomicIndex[5],
      kGasWireVaporAtomicIndex[6],
      kGasWireVaporAtomicIndex[7],
      kGasWireVaporAtomicIndex[8]         , 0,0,
      kDREndplateHoleyAtomicIndex[0],
      kDREndplateHoleyAtomicIndex[1],
      kDREndplateHoleyAtomicIndex[2],
      kDREndplateHoleyAtomicIndex[3],
      kDREndplateHoleyAtomicIndex[4], 0,0,0,0,0,0,
      kDRPreampVaporAtomicIndex[0],
      kDRPreampVaporAtomicIndex[1],
      kDRPreampVaporAtomicIndex[2],
      kDRPreampVaporAtomicIndex[3],
      kDRPreampVaporAtomicIndex[4],
      kDRPreampVaporAtomicIndex[5],
      kDRPreampVaporAtomicIndex[6],
      kDRPreampVaporAtomicIndex[7],
      kDRPreampVaporAtomicIndex[8],
      kDRPreampVaporAtomicIndex[9],
      kDRPreampVaporAtomicIndex[10],
      kDRNoPreampVaporAtomicIndex[0],
      kDRNoPreampVaporAtomicIndex[1],
      kDRNoPreampVaporAtomicIndex[2],
      kDRNoPreampVaporAtomicIndex[3],
      kDRNoPreampVaporAtomicIndex[4],
      kDRNoPreampVaporAtomicIndex[5],
      kDRNoPreampVaporAtomicIndex[6], 0,0,0,0,
      kDROnEndplateAtomicIndex[0],
      kDROnEndplateAtomicIndex[1],
      kDROnEndplateAtomicIndex[2],
      kDROnEndplateAtomicIndex[3],
      kDROnEndplateAtomicIndex[4],
      kDROnEndplateAtomicIndex[5], 0,0,0,0,0,
      999,0,0,0,0,0,0,0,0,0,0 } ;

   FReal    mixWeight[          nMix ][ maxMix ] = {
      kHeliumPropaneWeights[0]        , 
      kHeliumPropaneWeights[1]        , 
      kHeliumPropaneWeights[2]        , 0,0,0,0,0,0,0,0,
      kAluminum6061Weights[0]         , 
      kAluminum6061Weights[1]         ,
      kAluminum6061Weights[2]         , 
      kAluminum6061Weights[3]         ,
      kAluminum6061Weights[4]         , 0,0,0,0,0,0,
      kStainless316Weights[0]         ,  
      kStainless316Weights[1]         ,
      kStainless316Weights[2]         ,
      kStainless316Weights[3]         ,
      kStainless316Weights[4]         , 0,0,0,0,0,0,
      kRohacellWeights[0]             , 
      kRohacellWeights[1]             , 
      kRohacellWeights[2]             , 0,0,0,0,0,0,0,0,
      kEpoxyWeights[0]                , 
      kEpoxyWeights[1]                , 
      kEpoxyWeights[2]                , 0,0,0,0,0,0,0,0,
      kDR3InnerTubeMaterialWeights[0] ,
      kDR3InnerTubeMaterialWeights[1] ,
      kDR3InnerTubeMaterialWeights[2] ,
      kDR3InnerTubeMaterialWeights[3] , 0,0,0,0,0,0,0,
      kCesiumIodideWeights[0]         ,
      kCesiumIodideWeights[1]         , 0,0,0,0,0,0,0,0,0,
      kG10Weights[0]                  ,
      kG10Weights[1]                  ,
      kG10Weights[2]                  ,
      kG10Weights[3]                  , 0,0,0,0,0,0,0,
      kRecQuadWeights[0]              ,
      kRecQuadWeights[1]              ,
      kRecQuadWeights[2]              , 0,0,0,0,0,0,0,0,
      kMylarWeights[0]                ,
      kMylarWeights[1]                ,
      kMylarWeights[2]                , 0,0,0,0,0,0,0,0,
      kKevlarWeights[0]               ,
      kKevlarWeights[1]               ,
      kKevlarWeights[2]               ,
      kKevlarWeights[3]               , 0,0,0,0,0,0,0,
      kLuciteWeights[0]               ,
      kLuciteWeights[1]               ,
      kLuciteWeights[2]               , 0,0,0,0,0,0,0,0,
      kPVCWeights[0]                  ,
      kPVCWeights[1]                  ,
      kPVCWeights[2]                  , 0,0,0,0,0,0,0,0,
      kCableWeights[0]                ,
      kCableWeights[1]                ,
      kCableWeights[2]                ,
      kCableWeights[3]                ,
      kCableWeights[4]                , 0,0,0,0,0,0,
      kWaterWeights[0]                ,
      kWaterWeights[1]                , 0,0,0,0,0,0,0,0,0,
      kLithiumFluorideWeights[0]      ,
      kLithiumFluorideWeights[1]      , 0,0,0,0,0,0,0,0,0,
      kCalciumFluorideWeights[0]      ,
      kCalciumFluorideWeights[1]      , 0,0,0,0,0,0,0,0,0,
      kMethaneTEAWeights[0]           ,
      kMethaneTEAWeights[1]           ,
      kMethaneTEAWeights[2]           , 0,0,0,0,0,0,0,0,
      kCarbonFiberWeights[0]          ,
      kCarbonFiberWeights[1]          ,
      kCarbonFiberWeights[2]          ,
      kCarbonFiberWeights[3]          , 0,0,0,0,0,0,0,
      kBerylliumOxideWeights[0]       ,
      kBerylliumOxideWeights[1]       , 0,0,0,0,0,0,0,0,0,
      kSVCarbonFiberWeights[0]        ,
      kSVCarbonFiberWeights[1]        ,
      kSVCarbonFiberWeights[2]        ,
      kSVCarbonFiberWeights[3]        ,
      kSVCarbonFiberWeights[4]        , 0,0,0,0,0,0,
      1, 0,0,0,0,0,0,0,0,0,0,
      1, 0,0,0,0,0,0,0,0,0,0,
      1, 0,0,0,0,0,0,0,0,0,0,
      1, 0,0,0,0,0,0,0,0,0,0,
      1, 0,0,0,0,0,0,0,0,0,0,
      1, 0,0,0,0,0,0,0,0,0,0,
      1, 0,0,0,0,0,0,0,0,0,0,
      1, 0,0,0,0,0,0,0,0,0,0,
      1, 0,0,0,0,0,0,0,0,0,0,
      1, 0,0,0,0,0,0,0,0,0,0,
      1, 0,0,0,0,0,0,0,0,0,0,
      kMylarWeights[0]                ,
      kMylarWeights[1]                ,
      kMylarWeights[2]                , 0,0,0,0,0,0,0,0,
      kMylarWeights[0]                ,
      kMylarWeights[1]                ,
      kMylarWeights[2]                , 0,0,0,0,0,0,0,0,
      kAluminum5056Weights[0]         ,
      kAluminum5056Weights[1]         ,
      kAluminum5056Weights[2]         ,
      kAluminum5056Weights[3]         , 0,0,0,0,0,0,0,
      kGasWireVaporWeights[0]         ,
      kGasWireVaporWeights[1]         ,
      kGasWireVaporWeights[2]         ,
      kGasWireVaporWeights[3]         ,
      kGasWireVaporWeights[4]         ,
      kGasWireVaporWeights[5]         ,
      kGasWireVaporWeights[6]         ,
      kGasWireVaporWeights[7]         ,
      kGasWireVaporWeights[8]         , 0,0,
      kDREndplateHoleyWeights[0]         ,
      kDREndplateHoleyWeights[1]         ,
      kDREndplateHoleyWeights[2]         ,
      kDREndplateHoleyWeights[3]         ,
      kDREndplateHoleyWeights[4]         , 0,0,0,0,0,0,
      kDRPreampVaporWeights[0]         ,
      kDRPreampVaporWeights[1]         ,
      kDRPreampVaporWeights[2]         ,
      kDRPreampVaporWeights[3]         ,
      kDRPreampVaporWeights[4]         ,
      kDRPreampVaporWeights[5]         ,
      kDRPreampVaporWeights[6]         ,
      kDRPreampVaporWeights[7]         ,
      kDRPreampVaporWeights[8]         ,
      kDRPreampVaporWeights[9]         ,
      kDRPreampVaporWeights[10]         ,
      kDRNoPreampVaporWeights[0]         ,
      kDRNoPreampVaporWeights[1]         ,
      kDRNoPreampVaporWeights[2]         ,
      kDRNoPreampVaporWeights[3]         ,
      kDRNoPreampVaporWeights[4]         ,
      kDRNoPreampVaporWeights[5]         ,
      kDRNoPreampVaporWeights[6]         , 0,0,0,0,
      kDROnEndplateWeights[0]         ,
      kDROnEndplateWeights[1]         ,
      kDROnEndplateWeights[2]         ,
      kDROnEndplateWeights[3]         ,
      kDROnEndplateWeights[4]         ,
      kDROnEndplateWeights[5]         , 0,0,0,0,0,
      -1,0,0,0,0,0,0,0,0,0,0 } ;

   const FReal    mixDensity[   nMix ]           = {
      kHeliumPropaneDensity , 
      kAluminum6061Density  , 
      kStainless316Density  , 
      kRohacellDensity      , 
      kEpoxyDensity         ,
      kDR3InnerTubeMaterialDensity ,
      kCesiumIodideDensity  ,
      kG10Density           ,
      kRecQuadDensity       ,
      kMylarDensity         ,
      kKevlarDensity        ,
      kLuciteDensity        ,
      kPVCDensity           ,
      kCableDensity         ,
      kWaterDensity         ,
      kLithiumFluorideDensity ,
      kCalciumFluorideDensity ,
      kMethaneTEADensity      ,
      kCarbonFiberDensity     ,
      kBerylliumOxideDensity  ,
      kSVCarbonFiberDensity   ,
      kVacuumDensity,
      kVacuumDensity,
      kVacuumDensity,
      kNitrogenGasDensity ,
      kNitrogenGasDensity ,
      kNitrogenGasDensity ,
      kNitrogenGasDensity ,
      density[kAluminumMatIndex],
      density[kAluminumMatIndex],
      density[kAluminumMatIndex],
      density[kAluminumMatIndex],
      kMylarDensity         ,
      kMylarDensity         ,
      kAluminum5056Density  ,
      kGasWireVaporDensity  ,
      kDREndplateHoleyDensity  ,
      kDRPreampVaporDensity  ,
      kDRNoPreampVaporDensity  ,
      kDROnEndplateDensity  ,
      -1 } ;

   const FInteger mixNumber[    nMix ]           = {
      kHeliumPropaneMixNumber        ,
      kAluminum6061MixNumber         , 
      kStainless316MixNumber         ,
      kRohacellMixNumber             ,
      kEpoxyMixNumber                ,
      kDR3InnerTubeMaterialMixNumber ,
      kCesiumIodideMixNumber         ,
      kG10MixNumber                  ,
      kRecQuadMixNumber              ,
      kMylarMixNumber                ,
      kKevlarMixNumber               ,
      kLuciteMixNumber               ,
      kPVCMixNumber                  ,
      kCableMixNumber                ,
      kWaterMixNumber                ,
      kLithiumFluorideMixNumber      ,
      kCalciumFluorideMixNumber      ,
      kMethaneTEAMixNumber           ,
      kCarbonFiberMixNumber          ,
      kBerylliumOxideMixNumber       ,
      kSVCarbonFiberMixNumber        ,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      1,
      kMylarMixNumber                ,
      kMylarMixNumber                ,
      kAluminum5056MixNumber         ,
      kGasWireVaporMixNumber         ,
      kDREndplateHoleyMixNumber         ,
      kDRPreampVaporMixNumber         ,
      kDRNoPreampVaporMixNumber         ,
      kDROnEndplateMixNumber         ,
      -1 }  ;

   // the purpose of these asserts is to check that the
   // arrays initialized above have the "right" last element,
   // a non-definitive check for typo-type errors
   assert( -1       == mixIndex[       nMix - 1 ]    ) ;
   assert( "Marker" == mixString[      nMix - 1 ]    ) ;
   assert( 999      == mixAtomicIndex[ nMix - 1 ][0] ) ;
   assert( -1       == mixWeight[      nMix - 1 ][0] ) ;
   assert( -1       == mixDensity[     nMix - 1 ]    ) ;
   assert( -1       == mixNumber[      nMix - 1 ]    ) ;

   if( nElement + nMix > maxMaterials )
   {
      report( EMERGENCY, kReport ) << "Exceeded maxMaterials ="
				   << maxMaterials << ", quitting ..." 
				   << endl ;
      assert( false ) ;
      ::exit( 1 ) ;
   }


   for( UInt16 iMix ( 0 ) ; iMix != nMix-1 ; ++iMix )
   {
      const FInteger index ( mixIndex[ iMix ] ) ;
      const string&  stringName ( mixString[iMix] ) ;

      //cout << "*********** Mix number=" << iMix << ", name=" << stringName << endl ;

      const string name ( stringName + "                    " ) ;
      FChar mixName[20] ;
      for( UInt16 i ( 0 ); i != 19 ; ++i ) { mixName[i] = name[i] ; }
      mixName[19] = '$' ;

      FReal mixAtomicWts[ maxMix ] ;
      FReal mixAtomicNos[ maxMix ] ;
      FReal mixWt[        maxMix ] ;

      FReal sum ( 0 ) ;

      // fill atomic weights, numbers; check proportions; compute density
      for( UInt16 iPart ( 0 ) ; iPart != abs( mixNumber[iMix] ) ; ++iPart )
      {
	 const UInt16 atomicIndex ( mixAtomicIndex[ iMix ][ iPart ] ) ;

	 mixAtomicWts[ iPart ] = atomicWeight[ atomicIndex ] ;
	 mixAtomicNos[ iPart ] = atomicNumber[ atomicIndex ] ;
	 mixWt[        iPart ] = mixWeight[ iMix ][ iPart ]  ;
	 sum += mixWt[iPart] ;
      }

      if( 0 < mixNumber[iMix] && 0.000001 < fabs( sum - 1. ) )
      {
	 report( EMERGENCY, kReport ) << "Bad proportions for material"
				      << name << ", sum=" << sum << endl ;
	 assert(false) ;
	 ::exit( 1 ) ;
      }

      //cout << "about to call gsmixt" << endl ;

      //cout << mixAtomicWts[0] << ", " << mixAtomicNos[0] << ", "
      //<< mixDensity[iMix] << ", " << mixNumber[iMix] << ", "
      //<< mixWt << endl ;

      gsmixt_(
	 index            ,
	 mixName          ,
	 mixAtomicWts     ,
	 mixAtomicNos     ,
	 mixDensity[iMix] ,
	 mixNumber[iMix]  ,
	 mixWt            ,
	 nameLength
	 );

      stringIntMap()[ stringName ] = index ;

      // now fill up atomic wts, numbers, densities --------------------------

      FChar gName[20]          ;
      FReal radiationLength    ;
      FReal absorptionLength   ;
      static const UInt32 kG3BUFSIZE ( 100 ) ;
      static FReal uBuf[  kG3BUFSIZE ] ;

      FInteger nBuf            ;
      //cout << "about to call gsmate" << endl ;

      gfmate_( index                   , 
	       gName                   , 
	       xAtomicWeight[  index ] , 
	       xAtomicNumber[  index ] ,
	       xDensity[       index ] , 
	       radiationLength         , 
	       absorptionLength        , 
	       uBuf                    , 
	       nBuf                    ,
	       nameLength               ) ;

// 6/1/99: bkh: geant already did this for me! so comment it out
//      if( 0 > mixNumber[iMix] ) // mixture by proportion: convert to by wt
//      {
//	 float partSum ( 0 ) ;
//	 for( UInt16 iPart ( 0 ) ; iPart != abs( mixNumber[iMix] ) ; ++iPart )
//	 {
//	    mixWt[iPart] = mixWt[iPart]*mixAtomicWts[iPart] ;
//	    partSum += mixWt[ iPart ] ;
//	 }
//	 for( UInt16 iPar1 ( 0 ) ; iPar1 != abs( mixNumber[iMix] ) ; ++iPar1 )
//	 {
//	    mixWt[iPar1] = mixWt[iPar1]/partSum ;
//	 }
//      }

      FReal sumWt ( 0 ) ;
      VecWt vecWt ;
      vecWt.reserve( abs( mixNumber[iMix] ) ) ;

      for( UInt16 iPar2 ( 0 ) ; iPar2 != abs( mixNumber[iMix] ) ; ++iPar2 )
      {
	 vecWt.push_back( DGMaterial::WeightedElement(
	    DGMaterial::Element( mixAtomicWts[ iPar2 ],
				 mixAtomicNos[ iPar2 ] ), mixWt[ iPar2 ] ) ) ;
	 sumWt += mixWt[iPar2] ;
      }

      if( 0.000001 < fabs( sumWt - 1. ) )
      {
	 report( EMERGENCY, kReport ) << "Bad proportions for material"
				      << name << ", sum=" << sumWt << endl ;
	 assert(false) ;
	 ::exit( 1 ) ;
      }

      m_wtdElt[ stringName ] = vecWt ;

      if( kG3BUFSIZE < nBuf )
      {
	 report( EMERGENCY, kReport ) 
	    << "Default buffer size overfilled, exiting" << endl ;
	 assert( false ) ;
	 ::exit( 1 ) ;
      }
   }
   
   report( INFO, kReport ) << "Finished defining CLEO3 materials" << endl ;
}

// G3iMakeMaterials::G3iMakeMaterials( const G3iMakeMaterials& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

G3iMakeMaterials::~G3iMakeMaterials()
{
}

//
// assignment operators
//
// const G3iMakeMaterials& G3iMakeMaterials::operator=( const G3iMakeMaterials& rhs )
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

const STL_MAP( string, G3iMakeMaterials::VecWt )&
G3iMakeMaterials::wtdElt() const 
{
   return m_wtdElt ;
}


// static member functions
//

const G3iMakeMaterials& 
G3iMakeMaterials::instance() 
{
   if( 0 == k_instance )
   {
      k_instance = new G3iMakeMaterials() ;
      assert( 0 != k_instance ) ;
   }
   return *k_instance ;
}
