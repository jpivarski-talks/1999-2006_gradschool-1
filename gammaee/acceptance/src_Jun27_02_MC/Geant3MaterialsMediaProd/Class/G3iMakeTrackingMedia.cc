// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      G3iMakeTrackingMedia
// 
// Description: Defines GEANT3 "Tracking Media" & fills name-index structure
//
// Implementation:
//
//   Each tracking medium required has all its parameters set
//   & then these parameters are put in arrays which subsequently
//   are used as inputs to gstmed_ calls. Also, gstpar_ calls
//   are made when necessary to reduce cut values or eliminate
//   delta ray production.
//
//   Consult the GEANT3 manual for the meaning of the arguments.
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec  8 11:11:36 EST 1998
// $Id: G3iMakeTrackingMedia.cc,v 1.6 2002/01/23 21:07:40 lyon Exp $
//
// Revision history
//
// $Log: G3iMakeTrackingMedia.cc,v $
// Revision 1.6  2002/01/23 21:07:40  lyon
// Use inhomogenous magnetic field for HePr
//
// Revision 1.5  2001/04/17 20:18:04  bkh
// New materials/media for DR Endplate components
//
// Revision 1.4  2001/03/15 21:51:22  bkh
// Get Magnetic Field from Start Run
//
// Revision 1.3  2001/02/20 15:34:17  savinov
// Comments are included on inhomogeneous magnetic field. Also, default value is made positive. Does not matter: should be obtained on point by point basis anyway.
//
// Revision 1.2  2001/02/20 14:56:41  savinov
// Fixed a bug that reveresed the description of materials with homogeneous<-->inhomogeneous magnetic field (crucial for MC and MU reco)
//
// Revision 1.1.1.1  1999/12/15 18:35:50  bkh
// imported Geant3MaterialsMediaProd sources
//
// Revision 1.9  1999/08/31 21:29:22  bkh
// Add coil tracking media & fix some problems with volume creation
//
// Revision 1.8  1999/07/06 19:21:07  bkh
// Install SVCarbonFiber material and medium
//
// Revision 1.7  1999/07/05 14:22:49  bkh
// Install Beryllium Oxide Material and Tracking Medium
//
// Revision 1.6  1999/06/15 15:59:44  bkh
// Add diamond tracking medium
//
// Revision 1.5  1999/06/04 16:37:44  bkh
// Added kevlar material, and rohacell, kevlar, and dr3innertube tracking media
//
// Revision 1.4  1999/03/26 18:39:01  bkh
// Add muon iron TMed; allow for inhom B field in media
//
// Revision 1.3  1999/03/25 20:38:20  bkh
// Add Rich Materials/Media
//
// Revision 1.2  1999/02/01 22:25:51  bkh
// Update documentation & insert a cout<< until report works in cg3
//
// Revision 1.1.1.1  1999/01/19 22:02:29  bkh
// imported Geant3MaterialsMediaProd sources
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "MaterialDelivery/material_identifiers.h"
#include "Geant3MaterialsMediaProd/G3iSpecialMaterialIds.h"
#include "Geant3MaterialsMediaProd/G3iMakeMaterials.h"
#include "Geant3MaterialsMediaProd/G3iMakeTrackingMedia.h"
#include "Geant3Interface/G3iTrackingMediaIds.h"
#include "Geant3Interface/G3iFortran.h"

// STL classes
#include <map>

//
// constants, enums and typedefs
//

static const char* const kReport = "Geant3MaterialsMediaProd.G3iMakeTrackingMedia" ;


//
// static data member definitions
//

G3iMakeTrackingMedia* G3iMakeTrackingMedia::k_instance ( 0 ) ;

//
// constructors and destructor
//

G3iMakeTrackingMedia::G3iMakeTrackingMedia( const double aMagField )
   : G3iMakeStuffBase()
{
   // make sure material calls have been made & get names/indices
   const STL_MAP( string, UInt16 )& matMap
      ( G3iMakeMaterials::instance().stringIntMap() ) ;

   report( INFO, kReport ) 
      << "Start defining CLEO3 GEANT3 tracking media" << endl ;

   enum 
   {
      kVacuumTMedIndex = 1        , //  1
      kVacuumPrecTMedIndex        ,
      kAirTMedIndex               ,
      kAirFieldTMedIndex          ,
      kAirLoCutTMedIndex          ,
      kAirLoCutFieldTMedIndex     ,
      kAirLoCutFieldPrecTMedIndex ,
      kBerylliumTMedIndex         ,
      kSilverTMedIndex            ,
      kGoldTMedIndex              , // 10
      kTungstenTMedIndex          ,
      kWaterTMedIndex             ,
      kStainless316TMedIndex      ,
      kRecQuadTMedIndex           ,
      kAluminum6061TMedIndex      ,
      kEpoxyTMedIndex             ,
      kAluminumLoCutTMedIndex     ,
      kHeProTMedIndex             ,
      kMylarTMedIndex             ,
      kKevlarTMedIndex            , // 20
      kDR3InnerTubeTMedIndex      ,
      kRohacellTMedIndex          ,
      kCsITMedIndex               ,
      kLuciteTMedIndex            ,
      kAluminumTMedIndex          ,
      kCopperTMedIndex            ,
      kG10TMedIndex               ,
      kIronMuonOuterTMedIndex     ,
      kIronMuonInnerTMedIndex     ,
      kIronMuonReturnTMedIndex    , // 30
      kIronMuonInhomBTMedIndex    ,
      kAluminumMuonTMedIndex      ,
      kPVCMuonTMedIndex           ,
      kSiliconWaferTMedIndex      ,
      kDiamondTMedIndex           ,
      kNitrogenGasTMedIndex       ,
      kLithiumFluorideTMedIndex   ,
      kCalciumFluorideTMedIndex   ,
      kMethaneTEATMedIndex        ,
      kCarbonFiberTMedIndex       , // 40
      kBerylliumOxideTMedIndex    ,
      kSVCarbonFiberTMedIndex     ,
      kVacuumCoilTMedIndex        ,
      kMylarCoilTMedIndex         ,
      kAluminumCoilTMedIndex      ,
      kStainlessCoilTMedIndex     ,
      kVacuumCoilNFTMedIndex      ,
      kMylarCoilNFTMedIndex       ,
      kAluminumCoilNFTMedIndex    ,
      kStainlessCoilNFTMedIndex   ,// 50
      kDREndplateHoleyMedIndex    ,
      kDRPreampVaporMedIndex      ,
      kDRNoPreampVaporMedIndex    ,
      kDROnEndplateMedIndex       
   } ;

   const FReal solBField       ( aMagField ) ; // use the passed value now!
//   const FReal solBField       ( -14.876 ) ; // BAD! get one actually used!
//
//  02/20/01: comments by Vladimir Savinov:
//
//    1) The only regions of inhomogeneous magnetic field 
//       are in return and inner iron (at least that what we assume)
//
//    2) muInhomBField can be obtained from mubcal (C3Mu) 
//       Fortran call OR from direct c++ extract 
//       (MuConsProd would be needed in either case) 
//       on POINT BY POINT BASIS
//    
//    3) If anything, muInhomBField is rather positive 
//       than negative
//
//    4) muInhomBField is 3-dim vector!
//
//    5) muReturnBField and muInnerBField can 
//       be either from Fortran call to mugfld
//       or from c++ extract (see 1) above - same rules apply).
//
//    6) gufld from MutrReconProd (or, in near future, from 
//       C3Mu package can be used to get field value for 
//       each 3-D space point
//
// OLD   const FReal muInhomBField   (  solBField ) ;
//
   const FReal muInhomBField   (  -solBField ) ;
//
   const FReal muReturnBField  (  12.5*solBField/(-15) ) ;
   const FReal muInnerBField   (  10.6*solBField/(-15) ) ;
   const FReal muOuterBField   (   0   ) ;
//
   const FReal stdAngle        ( 10.   ) ;
   const FReal stdTrkPrec      ( 0.01  ) ;
   const FReal stdMScat        ( -1    ) ;
   const FReal stdELossMx      ( -1    ) ;
   const FReal stdELossMn      ( -1    ) ;

   // Vacuum
   const FInteger  kVacuumMatIndex  
      ( ( *(matMap.find( kVacuumMatID ) ) ).second ) ;
   const FInteger  kVacuumSensitive ( 1          ) ;
   const FReal     kVacuumBFieldMax ( solBField  ) ;
   const FReal     kVacuumAngleMax  ( stdAngle   ) ;
   const FReal     kVacuumTrkPrec   ( 0.1        ) ;
   const FReal     kVacuumMScatMax  ( stdMScat   ) ;
   const FReal     kVacuumELossMax  ( stdELossMx ) ;
   const FReal     kVacuumELossMin  ( stdELossMn ) ;
   const DABoolean kVacuumLoCuts    ( true       ) ;
   const DABoolean kVacuumNoDelta   ( false      ) ;
   const DABoolean kVacuumUserParm  ( false      ) ;

   // VacuumPrec
   const FInteger  kVacuumPrecMatIndex  
      ( ( *(matMap.find( kVacuumLoCutMatID ) ) ).second ) ;
   const FInteger  kVacuumPrecSensitive ( 1          ) ;
   const FReal     kVacuumPrecBFieldMax ( solBField  ) ;
   const FReal     kVacuumPrecAngleMax  ( stdAngle   ) ;
   const FReal     kVacuumPrecTrkPrec   ( 0.0001     ) ;
   const FReal     kVacuumPrecMScatMax  ( stdMScat   ) ;
   const FReal     kVacuumPrecELossMax  ( stdELossMx ) ;
   const FReal     kVacuumPrecELossMin  ( stdELossMn ) ;
   const DABoolean kVacuumPrecLoCuts    ( true       ) ;
   const DABoolean kVacuumPrecNoDelta   ( false      ) ;
   const DABoolean kVacuumPrecUserParm  ( false      ) ;

   // Air, no field
   const FInteger  kAirMatIndex  
      ( ( *(matMap.find( kAirMatID )) ).second ) ;
   const FInteger  kAirSensitive ( 1          ) ;
   const FReal     kAirBFieldMax ( 0          ) ;
   const FReal     kAirAngleMax  ( stdAngle   ) ;
   const FReal     kAirTrkPrec   ( 0.1        ) ;
   const FReal     kAirMScatMax  ( stdMScat   ) ;
   const FReal     kAirELossMax  ( stdELossMx ) ;
   const FReal     kAirELossMin  ( stdELossMn ) ;
   const DABoolean kAirLoCuts    ( true       ) ;
   const DABoolean kAirNoDelta   ( false      ) ;
   const DABoolean kAirUserParm  ( false      ) ;

   // Air, field
   const FInteger  kAirFieldMatIndex  
      ( ( *(matMap.find( kAirFieldMatID )) ).second ) ;
   const FInteger  kAirFieldSensitive ( 1          ) ;
   const FReal     kAirFieldBFieldMax ( solBField  ) ;
   const FReal     kAirFieldAngleMax  ( stdAngle   ) ;
   const FReal     kAirFieldTrkPrec   ( 0.1        ) ;
   const FReal     kAirFieldMScatMax  ( stdMScat   ) ;
   const FReal     kAirFieldELossMax  ( stdELossMx ) ;
   const FReal     kAirFieldELossMin  ( stdELossMn ) ;
   const DABoolean kAirFieldLoCuts    ( true       ) ;
   const DABoolean kAirFieldNoDelta   ( false      ) ;
   const DABoolean kAirFieldUserParm  ( false      ) ;

   // Air, lo cuts, no field
   const FInteger  kAirLoCutMatIndex  
      ( ( *(matMap.find( kAirLoCutMatID )) ).second ) ;
   const FInteger  kAirLoCutSensitive ( 1          ) ;
   const FReal     kAirLoCutBFieldMax ( 0          ) ;
   const FReal     kAirLoCutAngleMax  ( stdAngle   ) ;
   const FReal     kAirLoCutTrkPrec   ( 0.1        ) ;
   const FReal     kAirLoCutMScatMax  ( stdMScat   ) ;
   const FReal     kAirLoCutELossMax  ( stdELossMx ) ;
   const FReal     kAirLoCutELossMin  ( stdELossMn ) ;
   const DABoolean kAirLoCutLoCuts    ( true       ) ;
   const DABoolean kAirLoCutNoDelta   ( false      ) ;
   const DABoolean kAirLoCutUserParm  ( false      ) ;

   // Air, lo cuts, field
   const FInteger  kAirLoCutFieldMatIndex  
      ( ( *(matMap.find( kAirLCFieldMatID )) ).second ) ;
   const FInteger  kAirLoCutFieldSensitive ( 1          ) ;
   const FReal     kAirLoCutFieldBFieldMax ( solBField  ) ;
   const FReal     kAirLoCutFieldAngleMax  ( stdAngle   ) ;
   const FReal     kAirLoCutFieldTrkPrec   ( 0.1        ) ;
   const FReal     kAirLoCutFieldMScatMax  ( stdMScat   ) ;
   const FReal     kAirLoCutFieldELossMax  ( stdELossMx ) ;
   const FReal     kAirLoCutFieldELossMin  ( stdELossMn ) ;
   const DABoolean kAirLoCutFieldLoCuts    ( true       ) ;
   const DABoolean kAirLoCutFieldNoDelta   ( false      ) ;
   const DABoolean kAirLoCutFieldUserParm  ( false      ) ;

   // Air, lo cuts, field, prec
   const FInteger  kAirLoCutFieldPrecMatIndex  
      ( ( *(matMap.find( kAirLCFPrecMatID )) ).second ) ;
   const FInteger  kAirLoCutFieldPrecSensitive ( 1          ) ;
   const FReal     kAirLoCutFieldPrecBFieldMax ( solBField  ) ;
   const FReal     kAirLoCutFieldPrecAngleMax  ( stdAngle   ) ;
   const FReal     kAirLoCutFieldPrecTrkPrec   ( 0.0005     ) ;
   const FReal     kAirLoCutFieldPrecMScatMax  ( stdMScat   ) ;
   const FReal     kAirLoCutFieldPrecELossMax  ( stdELossMx ) ;
   const FReal     kAirLoCutFieldPrecELossMin  ( stdELossMn ) ;
   const DABoolean kAirLoCutFieldPrecLoCuts    ( true       ) ;
   const DABoolean kAirLoCutFieldPrecNoDelta   ( false      ) ;
   const DABoolean kAirLoCutFieldPrecUserParm  ( false      ) ;

   // Beryllium
   const FInteger  kBerylliumMatIndex  
      ( ( *(matMap.find( kBerylliumMatID )) ).second ) ;
   const FInteger  kBerylliumSensitive ( 1          ) ;
   const FReal     kBerylliumBFieldMax ( solBField  ) ;
   const FReal     kBerylliumAngleMax  ( stdAngle   ) ;
   const FReal     kBerylliumTrkPrec   ( 0.005      ) ;
   const FReal     kBerylliumMScatMax  ( stdMScat   ) ;
   const FReal     kBerylliumELossMax  ( stdELossMx ) ;
   const FReal     kBerylliumELossMin  ( stdELossMn ) ;
   const DABoolean kBerylliumLoCuts    ( true       ) ;
   const DABoolean kBerylliumNoDelta   ( false      ) ;
   const DABoolean kBerylliumUserParm  ( false      ) ;

   // Silver
   const FInteger  kSilverMatIndex  
      ( ( *(matMap.find( kSilverMatID )) ).second ) ;
   const FInteger  kSilverSensitive ( 1          ) ;
   const FReal     kSilverBFieldMax ( solBField  ) ;
   const FReal     kSilverAngleMax  ( stdAngle   ) ;
   const FReal     kSilverTrkPrec   ( 0.0001     ) ;
   const FReal     kSilverMScatMax  ( stdMScat   ) ;
   const FReal     kSilverELossMax  ( stdELossMx ) ;
   const FReal     kSilverELossMin  ( stdELossMn ) ;
   const DABoolean kSilverLoCuts    ( true       ) ;
   const DABoolean kSilverNoDelta   ( false      ) ;
   const DABoolean kSilverUserParm  ( false      ) ;

   // Gold
   const FInteger  kGoldMatIndex  
      ( ( *(matMap.find( kGoldMatID )) ).second ) ;
   const FInteger  kGoldSensitive ( 1          ) ;
   const FReal     kGoldBFieldMax ( solBField  ) ;
   const FReal     kGoldAngleMax  ( stdAngle   ) ;
   const FReal     kGoldTrkPrec   ( 0.0001     ) ;
   const FReal     kGoldMScatMax  ( stdMScat   ) ;
   const FReal     kGoldELossMax  ( stdELossMx ) ;
   const FReal     kGoldELossMin  ( stdELossMn ) ;
   const DABoolean kGoldLoCuts    ( true       ) ;
   const DABoolean kGoldNoDelta   ( false      ) ;
   const DABoolean kGoldUserParm  ( false      ) ;

   // Tungsten
   const FInteger  kTungstenMatIndex  
      ( ( *(matMap.find( kTungstenMatID )) ).second ) ;
   const FInteger  kTungstenSensitive ( 1          ) ;
   const FReal     kTungstenBFieldMax ( solBField  ) ;
   const FReal     kTungstenAngleMax  ( stdAngle   ) ;
   const FReal     kTungstenTrkPrec   ( 0.001      ) ;
   const FReal     kTungstenMScatMax  ( stdMScat   ) ;
   const FReal     kTungstenELossMax  ( stdELossMx ) ;
   const FReal     kTungstenELossMin  ( stdELossMn ) ;
   const DABoolean kTungstenLoCuts    ( true       ) ;
   const DABoolean kTungstenNoDelta   ( false      ) ;
   const DABoolean kTungstenUserParm  ( false      ) ;

   // Water
   const FInteger  kWaterMatIndex  
      ( ( *(matMap.find( kWaterMatID ) ) ).second ) ;
   const FInteger  kWaterSensitive ( 1          ) ;
   const FReal     kWaterBFieldMax ( solBField  ) ;
   const FReal     kWaterAngleMax  ( stdAngle   ) ;
   const FReal     kWaterTrkPrec   ( stdTrkPrec ) ;
   const FReal     kWaterMScatMax  ( stdMScat   ) ;
   const FReal     kWaterELossMax  ( stdELossMx ) ;
   const FReal     kWaterELossMin  ( stdELossMn ) ;
   const DABoolean kWaterLoCuts    ( true       ) ;
   const DABoolean kWaterNoDelta   ( false      ) ;
   const DABoolean kWaterUserParm  ( false      ) ;

   // Stainless316
   const FInteger  kStainless316MatIndex  
      ( ( *(matMap.find( kStainless316MatID ) ) ).second ) ;
   const FInteger  kStainless316Sensitive ( 2          ) ;
   const FReal     kStainless316BFieldMax ( solBField  ) ;
   const FReal     kStainless316AngleMax  ( stdAngle   ) ;
   const FReal     kStainless316TrkPrec   ( stdTrkPrec ) ;
   const FReal     kStainless316MScatMax  ( stdMScat   ) ;
   const FReal     kStainless316ELossMax  ( stdELossMx ) ;
   const FReal     kStainless316ELossMin  ( stdELossMn ) ;
   const DABoolean kStainless316LoCuts    ( false      ) ;
   const DABoolean kStainless316NoDelta   ( false      ) ;
   const DABoolean kStainless316UserParm  ( false      ) ;

   // RecQuad
   const FInteger  kRecQuadMatIndex  
      ( ( *(matMap.find( kRecQuadMatID ) ) ).second ) ;
   const FInteger  kRecQuadSensitive ( 2          ) ;
   const FReal     kRecQuadBFieldMax ( solBField  ) ;
   const FReal     kRecQuadAngleMax  ( stdAngle   ) ;
   const FReal     kRecQuadTrkPrec   ( stdTrkPrec ) ;
   const FReal     kRecQuadMScatMax  ( stdMScat   ) ;
   const FReal     kRecQuadELossMax  ( stdELossMx ) ;
   const FReal     kRecQuadELossMin  ( stdELossMn ) ;
   const DABoolean kRecQuadLoCuts    ( false      ) ;
   const DABoolean kRecQuadNoDelta   ( false      ) ;
   const DABoolean kRecQuadUserParm  ( false      ) ;

   // Aluminum6061
   const FInteger  kAluminum6061MatIndex  
      ( ( *(matMap.find( kAluminum6061MatID ) ) ).second ) ;
   const FInteger  kAluminum6061Sensitive ( 1          ) ;
   const FReal     kAluminum6061BFieldMax ( solBField  ) ;
   const FReal     kAluminum6061AngleMax  ( stdAngle   ) ;
   const FReal     kAluminum6061TrkPrec   ( stdTrkPrec ) ;
   const FReal     kAluminum6061MScatMax  ( stdMScat   ) ;
   const FReal     kAluminum6061ELossMax  ( stdELossMx ) ;
   const FReal     kAluminum6061ELossMin  ( stdELossMn ) ;
   const DABoolean kAluminum6061LoCuts    ( true       ) ;
   const DABoolean kAluminum6061NoDelta   ( false      ) ;
   const DABoolean kAluminum6061UserParm  ( false      ) ;

   // Epoxy
   const FInteger  kEpoxyMatIndex  
      ( ( *(matMap.find( kEpoxyMatID ) ) ).second ) ;
   const FInteger  kEpoxySensitive ( 1          ) ;
   const FReal     kEpoxyBFieldMax ( solBField  ) ;
   const FReal     kEpoxyAngleMax  ( stdAngle   ) ;
   const FReal     kEpoxyTrkPrec   ( stdTrkPrec ) ;
   const FReal     kEpoxyMScatMax  ( stdMScat   ) ;
   const FReal     kEpoxyELossMax  ( stdELossMx ) ;
   const FReal     kEpoxyELossMin  ( stdELossMn ) ;
   const DABoolean kEpoxyLoCuts    ( true       ) ;
   const DABoolean kEpoxyNoDelta   ( false      ) ;
   const DABoolean kEpoxyUserParm  ( false      ) ;

   // AluminumLoCut
   const FInteger  kAluminumLoCutMatIndex  
      ( ( *(matMap.find( kAluminumLoCutMatID ) ) ).second ) ;
   const FInteger  kAluminumLoCutSensitive ( 1          ) ;
   const FReal     kAluminumLoCutBFieldMax ( solBField  ) ;
   const FReal     kAluminumLoCutAngleMax  ( stdAngle   ) ;
   const FReal     kAluminumLoCutTrkPrec   ( stdTrkPrec ) ;
   const FReal     kAluminumLoCutMScatMax  ( stdMScat   ) ;
   const FReal     kAluminumLoCutELossMax  ( stdELossMx ) ;
   const FReal     kAluminumLoCutELossMin  ( stdELossMn ) ;
   const DABoolean kAluminumLoCutLoCuts    ( true       ) ;
   const DABoolean kAluminumLoCutNoDelta   ( false      ) ;
   const DABoolean kAluminumLoCutUserParm  ( false      ) ;

   // HePro
   const FInteger  kHeProMatIndex  
      ( ( *(matMap.find( kHeliumPropaneMatID )) ).second ) ;
   const FInteger  kHeProSensitive ( 2          ) ;
   const FReal     kHeProBFieldMax ( solBField  ) ;
   const FReal     kHeProAngleMax  ( stdAngle   ) ;
   const FReal     kHeProTrkPrec   ( stdTrkPrec ) ;
   const FReal     kHeProMScatMax  ( stdMScat   ) ;
   const FReal     kHeProELossMax  ( stdELossMx ) ;
   const FReal     kHeProELossMin  ( stdELossMn ) ;
   const DABoolean kHeProLoCuts    ( true       ) ;
   const DABoolean kHeProNoDelta   ( false      ) ;
   const DABoolean kHeProUserParm  ( false      ) ;

   // Mylar
   const FInteger  kMylarMatIndex  
      ( ( *(matMap.find( kMylarMatID ) ) ).second ) ;
   const FInteger  kMylarSensitive ( 1          ) ;
   const FReal     kMylarBFieldMax ( solBField  ) ;
   const FReal     kMylarAngleMax  ( stdAngle   ) ;
   const FReal     kMylarTrkPrec   ( stdTrkPrec ) ;
   const FReal     kMylarMScatMax  ( stdMScat   ) ;
   const FReal     kMylarELossMax  ( stdELossMx ) ;
   const FReal     kMylarELossMin  ( stdELossMn ) ;
   const DABoolean kMylarLoCuts    ( true       ) ; // LoCuts!
   const DABoolean kMylarNoDelta   ( false      ) ;
   const DABoolean kMylarUserParm  ( false      ) ;

   // Kevlar
   const FInteger  kKevlarMatIndex  
      ( ( *(matMap.find( kKevlarMatID ) ) ).second ) ;
   const FInteger  kKevlarSensitive ( 1          ) ;
   const FReal     kKevlarBFieldMax ( solBField  ) ;
   const FReal     kKevlarAngleMax  ( stdAngle   ) ;
   const FReal     kKevlarTrkPrec   ( stdTrkPrec ) ;
   const FReal     kKevlarMScatMax  ( stdMScat   ) ;
   const FReal     kKevlarELossMax  ( stdELossMx ) ;
   const FReal     kKevlarELossMin  ( stdELossMn ) ;
   const DABoolean kKevlarLoCuts    ( true       ) ; // LoCuts!
   const DABoolean kKevlarNoDelta   ( false      ) ;
   const DABoolean kKevlarUserParm  ( false      ) ;

   // DR3InnerTube
   const FInteger  kDR3InnerTubeMatIndex  
      ( ( *(matMap.find( kDR3InnerTubeMaterialMatID ) ) ).second ) ;
   const FInteger  kDR3InnerTubeSensitive ( 1          ) ;
   const FReal     kDR3InnerTubeBFieldMax ( solBField  ) ;
   const FReal     kDR3InnerTubeAngleMax  ( stdAngle   ) ;
   const FReal     kDR3InnerTubeTrkPrec   ( stdTrkPrec ) ;
   const FReal     kDR3InnerTubeMScatMax  ( stdMScat   ) ;
   const FReal     kDR3InnerTubeELossMax  ( stdELossMx ) ;
   const FReal     kDR3InnerTubeELossMin  ( stdELossMn ) ;
   const DABoolean kDR3InnerTubeLoCuts    ( true       ) ; // LoCuts!
   const DABoolean kDR3InnerTubeNoDelta   ( false      ) ;
   const DABoolean kDR3InnerTubeUserParm  ( false      ) ;

   // Rohacell
   const FInteger  kRohacellMatIndex  
      ( ( *(matMap.find( kRohacellMatID ) ) ).second ) ;
   const FInteger  kRohacellSensitive ( 1          ) ;
   const FReal     kRohacellBFieldMax ( solBField  ) ;
   const FReal     kRohacellAngleMax  ( stdAngle   ) ;
   const FReal     kRohacellTrkPrec   ( stdTrkPrec ) ;
   const FReal     kRohacellMScatMax  ( stdMScat   ) ;
   const FReal     kRohacellELossMax  ( stdELossMx ) ;
   const FReal     kRohacellELossMin  ( stdELossMn ) ;
   const DABoolean kRohacellLoCuts    ( true       ) ; // LoCuts!
   const DABoolean kRohacellNoDelta   ( false      ) ;
   const DABoolean kRohacellUserParm  ( false      ) ;

   // CsI
   const FInteger  kCsIMatIndex  
      ( ( *(matMap.find( kCesiumIodideMatID ) ) ).second ) ;
   const FInteger  kCsISensitive ( 2          ) ;
   const FReal     kCsIBFieldMax ( solBField  ) ;
   const FReal     kCsIAngleMax  ( stdAngle   ) ;
   const FReal     kCsITrkPrec   ( stdTrkPrec ) ;
   const FReal     kCsIMScatMax  ( stdMScat   ) ;
   const FReal     kCsIELossMax  ( stdELossMx ) ;
   const FReal     kCsIELossMin  ( stdELossMn ) ;
   const DABoolean kCsILoCuts    ( true       ) ;
   const DABoolean kCsINoDelta   ( false      ) ;
   const DABoolean kCsIUserParm  ( false      ) ;

   // Lucite
   const FInteger  kLuciteMatIndex  
      ( ( *(matMap.find( kLuciteMatID ) ) ).second ) ;
   const FInteger  kLuciteSensitive ( 2          ) ;
   const FReal     kLuciteBFieldMax ( solBField  ) ;
   const FReal     kLuciteAngleMax  ( stdAngle   ) ;
   const FReal     kLuciteTrkPrec   ( stdTrkPrec ) ;
   const FReal     kLuciteMScatMax  ( stdMScat   ) ;
   const FReal     kLuciteELossMax  ( stdELossMx ) ;
   const FReal     kLuciteELossMin  ( stdELossMn ) ;
   const DABoolean kLuciteLoCuts    ( false      ) ;
   const DABoolean kLuciteNoDelta   ( false      ) ;
   const DABoolean kLuciteUserParm  ( false      ) ;

   // Aluminum
   const FInteger  kAluminumMatIndex  
      ( ( *(matMap.find( kAluminumMatID ) ) ).second ) ;
   const FInteger  kAluminumSensitive ( 2          ) ;
   const FReal     kAluminumBFieldMax ( solBField  ) ;
   const FReal     kAluminumAngleMax  ( stdAngle   ) ;
   const FReal     kAluminumTrkPrec   ( stdTrkPrec ) ;
   const FReal     kAluminumMScatMax  ( stdMScat   ) ;
   const FReal     kAluminumELossMax  ( stdELossMx ) ;
   const FReal     kAluminumELossMin  ( stdELossMn ) ;
   const DABoolean kAluminumLoCuts    ( false      ) ;
   const DABoolean kAluminumNoDelta   ( false      ) ;
   const DABoolean kAluminumUserParm  ( false      ) ;

   // Copper
   const FInteger  kCopperMatIndex  
      ( ( *(matMap.find( kCopperMatID ) ) ).second ) ;
   const FInteger  kCopperSensitive ( 2          ) ;
   const FReal     kCopperBFieldMax ( solBField  ) ;
   const FReal     kCopperAngleMax  ( stdAngle   ) ;
   const FReal     kCopperTrkPrec   ( stdTrkPrec ) ;
   const FReal     kCopperMScatMax  ( stdMScat   ) ;
   const FReal     kCopperELossMax  ( stdELossMx ) ;
   const FReal     kCopperELossMin  ( stdELossMn ) ;
   const DABoolean kCopperLoCuts    ( false      ) ;
   const DABoolean kCopperNoDelta   ( false      ) ;
   const DABoolean kCopperUserParm  ( false      ) ;

   // G10
   const FInteger  kG10MatIndex  
      ( ( *(matMap.find( kG10MatID ) ) ).second ) ;
   const FInteger  kG10Sensitive ( 2          ) ;
   const FReal     kG10BFieldMax ( solBField  ) ;
   const FReal     kG10AngleMax  ( stdAngle   ) ;
   const FReal     kG10TrkPrec   ( stdTrkPrec ) ;
   const FReal     kG10MScatMax  ( stdMScat   ) ;
   const FReal     kG10ELossMax  ( stdELossMx ) ;
   const FReal     kG10ELossMin  ( stdELossMn ) ;
   const DABoolean kG10LoCuts    ( false      ) ;
   const DABoolean kG10NoDelta   ( false      ) ;
   const DABoolean kG10UserParm  ( false      ) ;

   // IronMuonOuter
   const FInteger  kIronMuonOuterMatIndex  
      ( ( *(matMap.find( kIronMatID ) ) ).second ) ;
   const FInteger  kIronMuonOuterSensitive ( 3          ) ;
   const FReal     kIronMuonOuterBFieldMax ( muOuterBField ) ;
   const FReal     kIronMuonOuterAngleMax  ( stdAngle   ) ;
   const FReal     kIronMuonOuterTrkPrec   ( stdTrkPrec ) ;
   const FReal     kIronMuonOuterMScatMax  ( stdMScat   ) ;
   const FReal     kIronMuonOuterELossMax  ( stdELossMx ) ;
   const FReal     kIronMuonOuterELossMin  ( stdELossMn ) ;
   const DABoolean kIronMuonOuterLoCuts    ( false      ) ;
   const DABoolean kIronMuonOuterNoDelta   ( true       ) ;
   const DABoolean kIronMuonOuterUserParm  ( false      ) ;

   // IronMuonInner
   const FInteger  kIronMuonInnerMatIndex  
      ( ( *(matMap.find( kIronMatID ) ) ).second ) ;
   const FInteger  kIronMuonInnerSensitive ( 3          ) ;
   const FReal     kIronMuonInnerBFieldMax ( muInnerBField ) ;
   const FReal     kIronMuonInnerAngleMax  ( stdAngle   ) ;
   const FReal     kIronMuonInnerTrkPrec   ( stdTrkPrec ) ;
   const FReal     kIronMuonInnerMScatMax  ( stdMScat   ) ;
   const FReal     kIronMuonInnerELossMax  ( stdELossMx ) ;
   const FReal     kIronMuonInnerELossMin  ( stdELossMn ) ;
   const DABoolean kIronMuonInnerLoCuts    ( false      ) ;
   const DABoolean kIronMuonInnerNoDelta   ( true       ) ;
   const DABoolean kIronMuonInnerUserParm  ( false      ) ;

   // IronMuonReturn
   const FInteger  kIronMuonReturnMatIndex  
      ( ( *(matMap.find( kIronMatID ) ) ).second ) ;
   const FInteger  kIronMuonReturnSensitive ( 3          ) ;
   const FReal     kIronMuonReturnBFieldMax ( muReturnBField ) ;
   const FReal     kIronMuonReturnAngleMax  ( stdAngle   ) ;
   const FReal     kIronMuonReturnTrkPrec   ( stdTrkPrec ) ;
   const FReal     kIronMuonReturnMScatMax  ( stdMScat   ) ;
   const FReal     kIronMuonReturnELossMax  ( stdELossMx ) ;
   const FReal     kIronMuonReturnELossMin  ( stdELossMn ) ;
   const DABoolean kIronMuonReturnLoCuts    ( false      ) ;
   const DABoolean kIronMuonReturnNoDelta   ( true       ) ;
   const DABoolean kIronMuonReturnUserParm  ( false      ) ;

   // IronMuon Inhom field
   const FInteger  kIronMuonInhomBMatIndex  
      ( ( *(matMap.find( kIronMatID ) ) ).second ) ;
   const FInteger  kIronMuonInhomBSensitive ( 3          ) ;
   const FReal     kIronMuonInhomBBFieldMax ( muInhomBField ) ;
   const FReal     kIronMuonInhomBAngleMax  ( stdAngle   ) ;
   const FReal     kIronMuonInhomBTrkPrec   ( stdTrkPrec ) ;
   const FReal     kIronMuonInhomBMScatMax  ( stdMScat   ) ;
   const FReal     kIronMuonInhomBELossMax  ( stdELossMx ) ;
   const FReal     kIronMuonInhomBELossMin  ( stdELossMn ) ;
   const DABoolean kIronMuonInhomBLoCuts    ( false      ) ;
   const DABoolean kIronMuonInhomBNoDelta   ( true       ) ;
   const DABoolean kIronMuonInhomBUserParm  ( false      ) ;

   // Aluminum Muon
   const FInteger  kAluminumMuonMatIndex  
      ( ( *(matMap.find( kAluminumMuonMatID ) ) ).second ) ;
   const FInteger  kAluminumMuonSensitive ( 3          ) ;
   const FReal     kAluminumMuonBFieldMax ( 0          ) ;
   const FReal     kAluminumMuonAngleMax  ( stdAngle   ) ;
   const FReal     kAluminumMuonTrkPrec   ( stdTrkPrec ) ;
   const FReal     kAluminumMuonMScatMax  ( stdMScat   ) ;
   const FReal     kAluminumMuonELossMax  ( stdELossMx ) ;
   const FReal     kAluminumMuonELossMin  ( stdELossMn ) ;
   const DABoolean kAluminumMuonLoCuts    ( false      ) ;
   const DABoolean kAluminumMuonNoDelta   ( true       ) ;
   const DABoolean kAluminumMuonUserParm  ( false      ) ;

   // PVC Muon
   const FInteger  kPVCMuonMatIndex  
      ( ( *(matMap.find( kPVCMatID ) ) ).second ) ;
   const FInteger  kPVCMuonSensitive ( 3          ) ;
   const FReal     kPVCMuonBFieldMax ( 0          ) ;
   const FReal     kPVCMuonAngleMax  ( stdAngle   ) ;
   const FReal     kPVCMuonTrkPrec   ( stdTrkPrec ) ;
   const FReal     kPVCMuonMScatMax  ( stdMScat   ) ;
   const FReal     kPVCMuonELossMax  ( stdELossMx ) ;
   const FReal     kPVCMuonELossMin  ( stdELossMn ) ;
   const DABoolean kPVCMuonLoCuts    ( false      ) ;
   const DABoolean kPVCMuonNoDelta   ( true       ) ;
   const DABoolean kPVCMuonUserParm  ( false      ) ;

   // Silicon Wafer
   const FInteger  kSiliconWaferMatIndex  
      ( ( *(matMap.find( kSiliconMatID ) ) ).second ) ;
   const FInteger  kSiliconWaferSensitive ( 1          ) ;
   const FReal     kSiliconWaferBFieldMax ( solBField  ) ;
   const FReal     kSiliconWaferAngleMax  ( 0.02666667 ) ; // !!!
   const FReal     kSiliconWaferTrkPrec   ( 0.0001     ) ;
   const FReal     kSiliconWaferMScatMax  ( 0.012      ) ; // !!!
   const FReal     kSiliconWaferELossMax  ( 0.000000833) ; // !!!
   const FReal     kSiliconWaferELossMin  ( 0.008      ) ; // !!!
   const DABoolean kSiliconWaferLoCuts    ( true       ) ; // !!!
   const DABoolean kSiliconWaferNoDelta   ( false      ) ;
   const DABoolean kSiliconWaferUserParm  ( true       ) ;

//* Include file for determining the Si tracking parameters given a desired
//* number of steps
//
//* The number of steps
//      REAL SVNSTP
//      PARAMETER ( SVNSTP = 3.0 )
//
//* -------------------------------------------------------------------
//* The base numbers for 1 STEP, ie. our extremes for a 300 micron step size
//
//* SVUBND - the Unit BeND angle (in degrees) for a particle with 50 MeV Pperp
//*          over a 300 micron step is about 0.08 degrees
//      REAL SVUBND
//      PARAMETER ( SVUBND = 0.08 )
//
//* SVUNMS - maximum displacement for multiple scattering.  For one step allow
//*          up to 20% over 300 microns (0.03 cm)
//      REAL SVUNMS
//      PARAMETER ( SVUNMS = 1.2 * 0.03 )
//
//* SVUDEX - maximum fractional energy loss.  Minimum ionizing loss for Si
//*          through 300 microns is 0.12 MeV.  So that mu pairs and bhabha's
//*          are mocked up, assume the extreme of an incoming particle of
//*          about 5 GeV.  The fractional energy loss would then be about
//*          2.5e-6
//      REAL SVUDEX
//      PARAMETER ( SVUDEX = 2.5E-6 )
//
//* SVUSTP - the minimum step size for dE/dx and mult. scatt..  Take this to be
//*          80% of the wafer thickness.
//      REAL SVUSTP
//      PARAMETER ( SVUSTP = 0.8 * 0.03 )
//
//* ------- now make the real parameters for the call to GSTMED -------
//      REAL SVBEND, SVMSDS, SVDEMX, SVSTEP
//      PARAMETER ( SVBEND = SVUBND / SVNSTP )
//      PARAMETER ( SVMSDS = SVUNMS / SVNSTP )
//      PARAMETER ( SVDEMX = SVUDEX / SVNSTP )
//      PARAMETER ( SVSTEP = SVUSTP / SVNSTP )

   // Diamond
   const FInteger  kDiamondMatIndex  
      ( ( *(matMap.find( kDiamondMatID ) ) ).second ) ;
   const FInteger  kDiamondSensitive ( 1          ) ;
   const FReal     kDiamondBFieldMax ( solBField  ) ;
   const FReal     kDiamondAngleMax  ( stdAngle   ) ;
   const FReal     kDiamondTrkPrec   ( stdTrkPrec ) ;
   const FReal     kDiamondMScatMax  ( stdMScat   ) ;
   const FReal     kDiamondELossMax  ( stdELossMx ) ;
   const FReal     kDiamondELossMin  ( stdELossMn ) ;
   const DABoolean kDiamondLoCuts    ( true       ) ;
   const DABoolean kDiamondNoDelta   ( false      ) ;
   const DABoolean kDiamondUserParm  ( false      ) ;

   // Nitrogen gas
   const FInteger  kNitrogenGasMatIndex  
      ( ( *(matMap.find( kNitrogenGasMatID ) ) ).second ) ;
   const FInteger  kNitrogenGasSensitive ( 1          ) ;
   const FReal     kNitrogenGasBFieldMax ( solBField  ) ;
   const FReal     kNitrogenGasAngleMax  ( 0.6        ) ; // 10mrad
   const FReal     kNitrogenGasTrkPrec   ( stdTrkPrec ) ;
   const FReal     kNitrogenGasMScatMax  ( stdMScat   ) ;
   const FReal     kNitrogenGasELossMax  ( stdELossMx ) ;
   const FReal     kNitrogenGasELossMin  ( stdELossMn ) ;
   const DABoolean kNitrogenGasLoCuts    ( true       ) ;
   const DABoolean kNitrogenGasNoDelta   ( false      ) ;
   const DABoolean kNitrogenGasUserParm  ( false      ) ;

   // Lithium Fluoride
   const FInteger  kLithiumFluorideMatIndex  
      ( ( *(matMap.find( kLithiumFluorideMatID ) ) ).second ) ;
   const FInteger  kLithiumFluorideSensitive ( 1          ) ;
   const FReal     kLithiumFluorideBFieldMax ( solBField  ) ;
   const FReal     kLithiumFluorideAngleMax  ( 0.06       ) ; // 1mrad
   const FReal     kLithiumFluorideTrkPrec   ( stdTrkPrec ) ;
   const FReal     kLithiumFluorideMScatMax  ( stdMScat   ) ;
   const FReal     kLithiumFluorideELossMax  ( stdELossMx ) ;
   const FReal     kLithiumFluorideELossMin  ( stdELossMn ) ;
   const DABoolean kLithiumFluorideLoCuts    ( true       ) ;
   const DABoolean kLithiumFluorideNoDelta   ( false      ) ;
   const DABoolean kLithiumFluorideUserParm  ( false      ) ;

   // Calcium Fluoride
   const FInteger  kCalciumFluorideMatIndex  
      ( ( *(matMap.find( kCalciumFluorideMatID ) ) ).second ) ;
   const FInteger  kCalciumFluorideSensitive ( 1          ) ;
   const FReal     kCalciumFluorideBFieldMax ( solBField  ) ;
   const FReal     kCalciumFluorideAngleMax  ( 0.06       ) ; // 1mrad
   const FReal     kCalciumFluorideTrkPrec   ( stdTrkPrec ) ;
   const FReal     kCalciumFluorideMScatMax  ( stdMScat   ) ;
   const FReal     kCalciumFluorideELossMax  ( stdELossMx ) ;
   const FReal     kCalciumFluorideELossMin  ( stdELossMn ) ;
   const DABoolean kCalciumFluorideLoCuts    ( true       ) ;
   const DABoolean kCalciumFluorideNoDelta   ( false      ) ;
   const DABoolean kCalciumFluorideUserParm  ( false      ) ;

   // Methane-TEA
   const FInteger  kMethaneTEAMatIndex  
      ( ( *(matMap.find( kMethaneTEAMatID ) ) ).second ) ;
   const FInteger  kMethaneTEASensitive ( 1          ) ;
   const FReal     kMethaneTEABFieldMax ( solBField  ) ;
   const FReal     kMethaneTEAAngleMax  ( 0.6        ) ; // 10mrad
   const FReal     kMethaneTEATrkPrec   ( stdTrkPrec ) ;
   const FReal     kMethaneTEAMScatMax  ( stdMScat   ) ;
   const FReal     kMethaneTEAELossMax  ( stdELossMx ) ;
   const FReal     kMethaneTEAELossMin  ( stdELossMn ) ;
   const DABoolean kMethaneTEALoCuts    ( true       ) ;
   const DABoolean kMethaneTEANoDelta   ( false      ) ;
   const DABoolean kMethaneTEAUserParm  ( false      ) ;

   // Carbon Fiber
   const FInteger  kCarbonFiberMatIndex  
      ( ( *(matMap.find( kCarbonFiberMatID ) ) ).second ) ;
   const FInteger  kCarbonFiberSensitive ( 1          ) ;
   const FReal     kCarbonFiberBFieldMax ( solBField  ) ;
   const FReal     kCarbonFiberAngleMax  ( 0.6        ) ; // 10mrad
   const FReal     kCarbonFiberTrkPrec   ( stdTrkPrec ) ;
   const FReal     kCarbonFiberMScatMax  ( stdMScat   ) ;
   const FReal     kCarbonFiberELossMax  ( stdELossMx ) ;
   const FReal     kCarbonFiberELossMin  ( stdELossMn ) ;
   const DABoolean kCarbonFiberLoCuts    ( true       ) ;
   const DABoolean kCarbonFiberNoDelta   ( false      ) ;
   const DABoolean kCarbonFiberUserParm  ( false      ) ;

   // BerylliumOxide
   const FInteger  kBerylliumOxideMatIndex  
      ( ( *(matMap.find( kBerylliumOxideMatID ) ) ).second ) ;
   const FInteger  kBerylliumOxideSensitive ( 1          ) ;
   const FReal     kBerylliumOxideBFieldMax ( solBField  ) ;
   const FReal     kBerylliumOxideAngleMax  ( stdAngle   ) ;
   const FReal     kBerylliumOxideTrkPrec   ( stdTrkPrec ) ;
   const FReal     kBerylliumOxideMScatMax  ( stdMScat   ) ;
   const FReal     kBerylliumOxideELossMax  ( stdELossMx ) ;
   const FReal     kBerylliumOxideELossMin  ( stdELossMn ) ;
   const DABoolean kBerylliumOxideLoCuts    ( true       ) ;
   const DABoolean kBerylliumOxideNoDelta   ( false      ) ;
   const DABoolean kBerylliumOxideUserParm  ( false      ) ;

   // SV Carbon Fiber
   const FInteger  kSVCarbonFiberMatIndex  
      ( ( *(matMap.find( kSVCarbonFiberMatID ) ) ).second ) ;
   const FInteger  kSVCarbonFiberSensitive ( 1          ) ;
   const FReal     kSVCarbonFiberBFieldMax ( solBField  ) ;
   const FReal     kSVCarbonFiberAngleMax  ( stdAngle   ) ; // 10mrad
   const FReal     kSVCarbonFiberTrkPrec   ( stdTrkPrec ) ;
   const FReal     kSVCarbonFiberMScatMax  ( stdMScat   ) ;
   const FReal     kSVCarbonFiberELossMax  ( stdELossMx ) ;
   const FReal     kSVCarbonFiberELossMin  ( stdELossMn ) ;
   const DABoolean kSVCarbonFiberLoCuts    ( true       ) ;
   const DABoolean kSVCarbonFiberNoDelta   ( false      ) ;
   const DABoolean kSVCarbonFiberUserParm  ( false      ) ;

   // Vacuum Coil
   const FInteger  kVacuumCoilMatIndex  
      ( ( *(matMap.find( kVacuumCoilMatID ) ) ).second ) ;
   const FInteger  kVacuumCoilSensitive ( 3          ) ;
   const FReal     kVacuumCoilBFieldMax ( solBField  ) ;
   const FReal     kVacuumCoilAngleMax  ( stdAngle   ) ;
   const FReal     kVacuumCoilTrkPrec   ( 0.1        ) ;
   const FReal     kVacuumCoilMScatMax  ( stdMScat   ) ;
   const FReal     kVacuumCoilELossMax  ( stdELossMx ) ;
   const FReal     kVacuumCoilELossMin  ( stdELossMn ) ;
   const DABoolean kVacuumCoilLoCuts    ( false      ) ;
   const DABoolean kVacuumCoilNoDelta   ( true       ) ;
   const DABoolean kVacuumCoilUserParm  ( false      ) ;

   // Vacuum Coil NF
   const FInteger  kVacuumCoilNFMatIndex  
      ( ( *(matMap.find( kVacuumCoilNFMatID ) ) ).second ) ;
   const FInteger  kVacuumCoilNFSensitive ( 3          ) ;
   const FReal     kVacuumCoilNFBFieldMax ( 0          ) ;
   const FReal     kVacuumCoilNFAngleMax  ( stdAngle   ) ;
   const FReal     kVacuumCoilNFTrkPrec   ( 0.1        ) ;
   const FReal     kVacuumCoilNFMScatMax  ( stdMScat   ) ;
   const FReal     kVacuumCoilNFELossMax  ( stdELossMx ) ;
   const FReal     kVacuumCoilNFELossMin  ( stdELossMn ) ;
   const DABoolean kVacuumCoilNFLoCuts    ( false      ) ;
   const DABoolean kVacuumCoilNFNoDelta   ( true       ) ;
   const DABoolean kVacuumCoilNFUserParm  ( false      ) ;

   // Mylar Coil
   const FInteger  kMylarCoilMatIndex  
      ( ( *(matMap.find( kMylarCoilMatID ) ) ).second ) ;
   const FInteger  kMylarCoilSensitive ( 3          ) ;
   const FReal     kMylarCoilBFieldMax ( solBField  ) ;
   const FReal     kMylarCoilAngleMax  ( stdAngle   ) ;
   const FReal     kMylarCoilTrkPrec   ( stdTrkPrec ) ;
   const FReal     kMylarCoilMScatMax  ( stdMScat   ) ;
   const FReal     kMylarCoilELossMax  ( stdELossMx ) ;
   const FReal     kMylarCoilELossMin  ( stdELossMn ) ;
   const DABoolean kMylarCoilLoCuts    ( false      ) ;
   const DABoolean kMylarCoilNoDelta   ( true       ) ;
   const DABoolean kMylarCoilUserParm  ( false      ) ;

   // Mylar Coil NF
   const FInteger  kMylarCoilNFMatIndex  
      ( ( *(matMap.find( kMylarCoilNFMatID ) ) ).second ) ;
   const FInteger  kMylarCoilNFSensitive ( 3          ) ;
   const FReal     kMylarCoilNFBFieldMax ( 0          ) ;
   const FReal     kMylarCoilNFAngleMax  ( stdAngle   ) ;
   const FReal     kMylarCoilNFTrkPrec   ( stdTrkPrec ) ;
   const FReal     kMylarCoilNFMScatMax  ( stdMScat   ) ;
   const FReal     kMylarCoilNFELossMax  ( stdELossMx ) ;
   const FReal     kMylarCoilNFELossMin  ( stdELossMn ) ;
   const DABoolean kMylarCoilNFLoCuts    ( false      ) ;
   const DABoolean kMylarCoilNFNoDelta   ( true       ) ;
   const DABoolean kMylarCoilNFUserParm  ( false      ) ;

   // Aluminum Coil
   const FInteger  kAluminumCoilMatIndex  
      ( ( *(matMap.find( kAluminumCoilMatID ) ) ).second ) ;
   const FInteger  kAluminumCoilSensitive ( 3          ) ;
   const FReal     kAluminumCoilBFieldMax ( solBField  ) ;
   const FReal     kAluminumCoilAngleMax  ( stdAngle   ) ;
   const FReal     kAluminumCoilTrkPrec   ( stdTrkPrec ) ;
   const FReal     kAluminumCoilMScatMax  ( stdMScat   ) ;
   const FReal     kAluminumCoilELossMax  ( stdELossMx ) ;
   const FReal     kAluminumCoilELossMin  ( stdELossMn ) ;
   const DABoolean kAluminumCoilLoCuts    ( false      ) ;
   const DABoolean kAluminumCoilNoDelta   ( true       ) ;
   const DABoolean kAluminumCoilUserParm  ( false      ) ;

   // Aluminum Coil NF
   const FInteger  kAluminumCoilNFMatIndex  
      ( ( *(matMap.find( kAluminumCoilNFMatID ) ) ).second ) ;
   const FInteger  kAluminumCoilNFSensitive ( 3          ) ;
   const FReal     kAluminumCoilNFBFieldMax ( 0          ) ;
   const FReal     kAluminumCoilNFAngleMax  ( stdAngle   ) ;
   const FReal     kAluminumCoilNFTrkPrec   ( stdTrkPrec ) ;
   const FReal     kAluminumCoilNFMScatMax  ( stdMScat   ) ;
   const FReal     kAluminumCoilNFELossMax  ( stdELossMx ) ;
   const FReal     kAluminumCoilNFELossMin  ( stdELossMn ) ;
   const DABoolean kAluminumCoilNFLoCuts    ( false      ) ;
   const DABoolean kAluminumCoilNFNoDelta   ( true       ) ;
   const DABoolean kAluminumCoilNFUserParm  ( false      ) ;

   // Stainless Coil
   const FInteger  kStainlessCoilMatIndex  
      ( ( *(matMap.find( kStainless316MatID ) ) ).second ) ;
   const FInteger  kStainlessCoilSensitive ( 3          ) ;
   const FReal     kStainlessCoilBFieldMax ( solBField  ) ;
   const FReal     kStainlessCoilAngleMax  ( stdAngle   ) ;
   const FReal     kStainlessCoilTrkPrec   ( stdTrkPrec ) ;
   const FReal     kStainlessCoilMScatMax  ( stdMScat   ) ;
   const FReal     kStainlessCoilELossMax  ( stdELossMx ) ;
   const FReal     kStainlessCoilELossMin  ( stdELossMn ) ;
   const DABoolean kStainlessCoilLoCuts    ( false      ) ;
   const DABoolean kStainlessCoilNoDelta   ( false      ) ;
   const DABoolean kStainlessCoilUserParm  ( false      ) ;

   // Stainless Coil NF
   const FInteger  kStainlessCoilNFMatIndex  
      ( ( *(matMap.find( kStainless316MatID ) ) ).second ) ;
   const FInteger  kStainlessCoilNFSensitive ( 3          ) ;
   const FReal     kStainlessCoilNFBFieldMax ( 0          ) ;
   const FReal     kStainlessCoilNFAngleMax  ( stdAngle   ) ;
   const FReal     kStainlessCoilNFTrkPrec   ( stdTrkPrec ) ;
   const FReal     kStainlessCoilNFMScatMax  ( stdMScat   ) ;
   const FReal     kStainlessCoilNFELossMax  ( stdELossMx ) ;
   const FReal     kStainlessCoilNFELossMin  ( stdELossMn ) ;
   const DABoolean kStainlessCoilNFLoCuts    ( false      ) ;
   const DABoolean kStainlessCoilNFNoDelta   ( false      ) ;
   const DABoolean kStainlessCoilNFUserParm  ( false      ) ;

   // Endplate Holey
   const FInteger  kDREndplateHoleyMatIndex  
      ( ( *(matMap.find( kDREndplateHoleyMatID ) ) ).second ) ;
   const FInteger  kDREndplateHoleySensitive ( 1          ) ;
   const FReal     kDREndplateHoleyBFieldMax ( solBField  ) ;
   const FReal     kDREndplateHoleyAngleMax  ( stdAngle   ) ;
   const FReal     kDREndplateHoleyTrkPrec   ( stdTrkPrec ) ;
   const FReal     kDREndplateHoleyMScatMax  ( stdMScat   ) ;
   const FReal     kDREndplateHoleyELossMax  ( stdELossMx ) ;
   const FReal     kDREndplateHoleyELossMin  ( stdELossMn ) ;
   const DABoolean kDREndplateHoleyLoCuts    ( false      ) ;
   const DABoolean kDREndplateHoleyNoDelta   ( false      ) ;
   const DABoolean kDREndplateHoleyUserParm  ( false      ) ;

   // DR Preamp Vapor
   const FInteger  kDRPreampVaporMatIndex  
      ( ( *(matMap.find( kDRPreampVaporMatID ) ) ).second ) ;
   const FInteger  kDRPreampVaporSensitive ( 1          ) ;
   const FReal     kDRPreampVaporBFieldMax ( solBField  ) ;
   const FReal     kDRPreampVaporAngleMax  ( stdAngle   ) ;
   const FReal     kDRPreampVaporTrkPrec   ( stdTrkPrec ) ;
   const FReal     kDRPreampVaporMScatMax  ( stdMScat   ) ;
   const FReal     kDRPreampVaporELossMax  ( stdELossMx ) ;
   const FReal     kDRPreampVaporELossMin  ( stdELossMn ) ;
   const DABoolean kDRPreampVaporLoCuts    ( false      ) ;
   const DABoolean kDRPreampVaporNoDelta   ( false      ) ;
   const DABoolean kDRPreampVaporUserParm  ( false      ) ;

   // DR NoPreamp Vapor
   const FInteger  kDRNoPreampVaporMatIndex  
      ( ( *(matMap.find( kDRNoPreampVaporMatID ) ) ).second ) ;
   const FInteger  kDRNoPreampVaporSensitive ( 1          ) ;
   const FReal     kDRNoPreampVaporBFieldMax ( solBField  ) ;
   const FReal     kDRNoPreampVaporAngleMax  ( stdAngle   ) ;
   const FReal     kDRNoPreampVaporTrkPrec   ( stdTrkPrec ) ;
   const FReal     kDRNoPreampVaporMScatMax  ( stdMScat   ) ;
   const FReal     kDRNoPreampVaporELossMax  ( stdELossMx ) ;
   const FReal     kDRNoPreampVaporELossMin  ( stdELossMn ) ;
   const DABoolean kDRNoPreampVaporLoCuts    ( true       ) ;
   const DABoolean kDRNoPreampVaporNoDelta   ( false      ) ;
   const DABoolean kDRNoPreampVaporUserParm  ( false      ) ;

   // DR OnEndplate
   const FInteger  kDROnEndplateMatIndex  
      ( ( *(matMap.find( kDROnEndplateMatID ) ) ).second ) ;
   const FInteger  kDROnEndplateSensitive ( 1          ) ;
   const FReal     kDROnEndplateBFieldMax ( solBField  ) ;
   const FReal     kDROnEndplateAngleMax  ( stdAngle   ) ;
   const FReal     kDROnEndplateTrkPrec   ( stdTrkPrec ) ;
   const FReal     kDROnEndplateMScatMax  ( stdMScat   ) ;
   const FReal     kDROnEndplateELossMax  ( stdELossMx ) ;
   const FReal     kDROnEndplateELossMin  ( stdELossMn ) ;
   const DABoolean kDROnEndplateLoCuts    ( true       ) ;
   const DABoolean kDROnEndplateNoDelta   ( false      ) ;
   const DABoolean kDROnEndplateUserParm  ( false      ) ;

   static const UInt16 nTMed ( 55 ) ;

   const FInteger  mediaIndex[    nTMed ] = { 
      kVacuumTMedIndex            ,
      kVacuumPrecTMedIndex        ,
      kAirTMedIndex               ,
      kAirFieldTMedIndex          ,
      kAirLoCutTMedIndex          ,
      kAirLoCutFieldTMedIndex     ,
      kAirLoCutFieldPrecTMedIndex ,
      kBerylliumTMedIndex         ,
      kSilverTMedIndex            ,
      kGoldTMedIndex              ,
      kTungstenTMedIndex          ,
      kWaterTMedIndex             ,
      kStainless316TMedIndex      ,
      kRecQuadTMedIndex           ,
      kAluminum6061TMedIndex      ,
      kEpoxyTMedIndex             ,
      kAluminumLoCutTMedIndex     ,
      kHeProTMedIndex             ,
      kMylarTMedIndex             ,
      kKevlarTMedIndex            ,
      kDR3InnerTubeTMedIndex      ,
      kRohacellTMedIndex          ,
      kCsITMedIndex               ,
      kLuciteTMedIndex            ,
      kAluminumTMedIndex          ,
      kCopperTMedIndex            ,
      kG10TMedIndex               ,
      kIronMuonOuterTMedIndex     ,
      kIronMuonInnerTMedIndex     ,
      kIronMuonReturnTMedIndex    ,
      kIronMuonInhomBTMedIndex    ,
      kAluminumMuonTMedIndex      ,
      kPVCMuonTMedIndex           ,
      kSiliconWaferTMedIndex      ,
      kDiamondTMedIndex           ,
      kNitrogenGasTMedIndex       ,
      kLithiumFluorideTMedIndex   ,
      kCalciumFluorideTMedIndex   ,
      kMethaneTEATMedIndex        ,
      kCarbonFiberTMedIndex       ,
      kBerylliumOxideTMedIndex    ,
      kSVCarbonFiberTMedIndex     ,
      kVacuumCoilTMedIndex        ,
      kMylarCoilTMedIndex         ,
      kAluminumCoilTMedIndex      ,
      kStainlessCoilTMedIndex     ,
      kVacuumCoilNFTMedIndex      ,
      kMylarCoilNFTMedIndex       ,
      kAluminumCoilNFTMedIndex    ,
      kStainlessCoilNFTMedIndex   ,
      kDREndplateHoleyMedIndex    ,
      kDRPreampVaporMedIndex      ,
      kDRNoPreampVaporMedIndex    ,
      kDROnEndplateMedIndex       ,
      -1 } ;

   const FInteger  materialIndex[ nTMed ] = {
      kVacuumMatIndex            ,
      kVacuumPrecMatIndex        ,
      kAirMatIndex               ,
      kAirFieldMatIndex          ,
      kAirLoCutMatIndex          ,
      kAirLoCutFieldMatIndex     ,
      kAirLoCutFieldPrecMatIndex ,
      kBerylliumMatIndex         ,
      kSilverMatIndex            ,
      kGoldMatIndex              ,
      kTungstenMatIndex          ,
      kWaterMatIndex             ,
      kStainless316MatIndex      ,
      kRecQuadMatIndex           ,
      kAluminum6061MatIndex      ,
      kEpoxyMatIndex             ,
      kAluminumLoCutMatIndex     ,
      kHeProMatIndex             ,
      kMylarMatIndex             ,
      kKevlarMatIndex            ,
      kDR3InnerTubeMatIndex      ,
      kRohacellMatIndex          ,
      kCsIMatIndex               ,
      kLuciteMatIndex            ,
      kAluminumMatIndex          ,
      kCopperMatIndex            ,
      kG10MatIndex               ,
      kIronMuonOuterMatIndex     ,
      kIronMuonInnerMatIndex     ,
      kIronMuonReturnMatIndex    ,
      kIronMuonInhomBMatIndex    ,
      kAluminumMuonMatIndex      ,
      kPVCMuonMatIndex           ,
      kSiliconWaferMatIndex      ,
      kDiamondMatIndex           ,
      kNitrogenGasMatIndex       ,
      kLithiumFluorideMatIndex   ,
      kCalciumFluorideMatIndex   ,
      kMethaneTEAMatIndex        ,
      kCarbonFiberMatIndex       ,
      kBerylliumOxideMatIndex    ,
      kSVCarbonFiberMatIndex     ,
      kVacuumCoilMatIndex        ,
      kMylarCoilMatIndex         ,
      kAluminumCoilMatIndex      ,
      kStainlessCoilMatIndex     ,
      kVacuumCoilNFMatIndex      ,
      kMylarCoilNFMatIndex       ,
      kAluminumCoilNFMatIndex    ,
      kStainlessCoilNFMatIndex   ,
      kDREndplateHoleyMatIndex    ,
      kDRPreampVaporMatIndex      ,
      kDRNoPreampVaporMatIndex    ,
      kDROnEndplateMatIndex       ,
      -1 } ;

   const string    mediaString[   nTMed ] = {
      kVacuumTMedID            ,
      kVacuumPrecTMedID        ,
      kAirTMedID               ,
      kAirFieldTMedID          ,
      kAirLoCutTMedID          ,
      kAirLoCutFieldTMedID     ,
      kAirLoCutFieldPrecTMedID ,
      kBerylliumTMedID         ,
      kSilverTMedID            ,
      kGoldTMedID              ,
      kTungstenTMedID          ,
      kWaterTMedID             ,
      kStainless316TMedID      ,
      kRecQuadTMedID           ,
      kAluminum6061TMedID      ,
      kEpoxyTMedID             ,
      kAluminumLoCutTMedID     ,
      kHeProTMedID             ,
      kMylarTMedID             ,
      kKevlarTMedID            ,
      kDR3InnerTubeTMedID      ,
      kRohacellTMedID          ,
      kCsITMedID               ,
      kLuciteTMedID            ,
      kAluminumTMedID          ,
      kCopperTMedID            ,
      kG10TMedID               ,
      kIronMuonOuterTMedID     ,
      kIronMuonInnerTMedID     ,
      kIronMuonReturnTMedID    ,
      kIronMuonInhomBTMedID    ,
      kAluminumMuonTMedID      ,
      kPVCMuonTMedID           ,
      kSiliconWaferTMedID      ,
      kDiamondTMedID           ,
      kNitrogenGasTMedID       ,
      kLithiumFluorideTMedID   ,
      kCalciumFluorideTMedID   ,
      kMethaneTEATMedID        ,
      kCarbonFiberTMedID       ,
      kBerylliumOxideTMedID    ,
      kSVCarbonFiberTMedID     ,
      kVacuumCoilTMedID        ,
      kMylarCoilTMedID         ,
      kAluminumCoilTMedID      ,
      kStainlessCoilTMedID     ,
      kVacuumCoilNFTMedID      ,
      kMylarCoilNFTMedID       ,
      kAluminumCoilNFTMedID    ,
      kStainlessCoilNFTMedID   ,
      kDREndplateHoleyMedID    ,
      kDRPreampVaporMedID      ,
      kDRNoPreampVaporMedID    ,
      kDROnEndplateMedID       ,
      "Marker" } ;

   const FInteger  sensitive[     nTMed ] = {
      kVacuumSensitive            ,
      kVacuumPrecSensitive        ,
      kAirSensitive               ,
      kAirFieldSensitive          ,
      kAirLoCutSensitive          ,
      kAirLoCutFieldSensitive     ,
      kAirLoCutFieldPrecSensitive ,
      kBerylliumSensitive         ,
      kSilverSensitive            ,
      kGoldSensitive              ,
      kTungstenSensitive          ,
      kWaterSensitive             ,
      kStainless316Sensitive      ,
      kRecQuadSensitive           ,
      kAluminum6061Sensitive      ,
      kEpoxySensitive             ,
      kAluminumLoCutSensitive     ,
      kHeProSensitive             ,
      kMylarSensitive             ,
      kKevlarSensitive            ,
      kDR3InnerTubeSensitive      ,
      kRohacellSensitive          ,
      kCsISensitive               ,
      kLuciteSensitive            ,
      kAluminumSensitive          ,
      kCopperSensitive            ,
      kG10Sensitive               ,
      kIronMuonOuterSensitive     ,
      kIronMuonInnerSensitive     ,
      kIronMuonReturnSensitive    ,
      kIronMuonInhomBSensitive    ,
      kAluminumMuonSensitive      ,
      kPVCMuonSensitive           ,
      kSiliconWaferSensitive      ,
      kDiamondSensitive           ,
      kNitrogenGasSensitive       ,
      kLithiumFluorideSensitive   ,
      kCalciumFluorideSensitive   ,
      kMethaneTEASensitive        ,
      kCarbonFiberSensitive       ,
      kBerylliumOxideSensitive    ,
      kSVCarbonFiberSensitive     ,
      kVacuumCoilSensitive        ,
      kMylarCoilSensitive         ,
      kAluminumCoilSensitive      ,
      kStainlessCoilSensitive     ,
      kVacuumCoilNFSensitive      ,
      kMylarCoilNFSensitive       ,
      kAluminumCoilNFSensitive    ,
      kStainlessCoilNFSensitive   ,
      kDREndplateHoleySensitive    ,
      kDRPreampVaporSensitive      ,
      kDRNoPreampVaporSensitive    ,
      kDROnEndplateSensitive       ,
      -1 } ;

   const FReal     bFieldMax[     nTMed ] = {
      kVacuumBFieldMax            ,
      kVacuumPrecBFieldMax        ,
      kAirBFieldMax               ,
      kAirFieldBFieldMax          ,
      kAirLoCutBFieldMax          ,
      kAirLoCutFieldBFieldMax     ,
      kAirLoCutFieldPrecBFieldMax ,
      kBerylliumBFieldMax         ,
      kSilverBFieldMax            ,
      kGoldBFieldMax              ,
      kTungstenBFieldMax          ,
      kWaterBFieldMax             ,
      kStainless316BFieldMax      ,
      kRecQuadBFieldMax           ,
      kAluminum6061BFieldMax      ,
      kEpoxyBFieldMax             ,
      kAluminumLoCutBFieldMax     ,
      kHeProBFieldMax             ,
      kMylarBFieldMax             ,
      kKevlarBFieldMax            ,
      kDR3InnerTubeBFieldMax      ,
      kRohacellBFieldMax          ,
      kCsIBFieldMax               ,
      kLuciteBFieldMax            ,
      kAluminumBFieldMax          ,
      kCopperBFieldMax            ,
      kG10BFieldMax               ,
      kIronMuonOuterBFieldMax     ,
      kIronMuonInnerBFieldMax     ,
      kIronMuonReturnBFieldMax    ,
      kIronMuonInhomBBFieldMax    ,
      kAluminumMuonBFieldMax      ,
      kPVCMuonBFieldMax           ,
      kSiliconWaferBFieldMax      ,
      kDiamondBFieldMax           ,
      kNitrogenGasBFieldMax       ,
      kLithiumFluorideBFieldMax   ,
      kCalciumFluorideBFieldMax   ,
      kMethaneTEABFieldMax        ,
      kCarbonFiberBFieldMax       ,
      kBerylliumOxideBFieldMax    ,
      kSVCarbonFiberBFieldMax     ,
      kVacuumCoilBFieldMax        ,
      kMylarCoilBFieldMax         ,
      kAluminumCoilBFieldMax      ,
      kStainlessCoilBFieldMax     ,
      kVacuumCoilNFBFieldMax      ,
      kMylarCoilNFBFieldMax       ,
      kAluminumCoilNFBFieldMax    ,
      kStainlessCoilNFBFieldMax   ,
      kDREndplateHoleyBFieldMax    ,
      kDRPreampVaporBFieldMax      ,
      kDRNoPreampVaporBFieldMax    ,
      kDROnEndplateBFieldMax       ,
      -1 } ;

   const FReal     angleMax[      nTMed ] = {
      kVacuumAngleMax            ,
      kVacuumPrecAngleMax        ,
      kAirAngleMax               ,
      kAirFieldAngleMax          ,
      kAirLoCutAngleMax          ,
      kAirLoCutFieldAngleMax     ,
      kAirLoCutFieldPrecAngleMax ,
      kBerylliumAngleMax         ,
      kSilverAngleMax            ,
      kGoldAngleMax              ,
      kTungstenAngleMax          ,
      kWaterAngleMax             ,
      kStainless316AngleMax      ,
      kRecQuadAngleMax           ,
      kAluminum6061AngleMax      ,
      kEpoxyAngleMax             ,
      kAluminumLoCutAngleMax     ,
      kHeProAngleMax             ,
      kMylarAngleMax             ,
      kKevlarAngleMax            ,
      kDR3InnerTubeAngleMax      ,
      kRohacellAngleMax          ,
      kCsIAngleMax               ,
      kLuciteAngleMax            ,
      kAluminumAngleMax          ,
      kCopperAngleMax            ,
      kG10AngleMax               ,
      kIronMuonOuterAngleMax     ,
      kIronMuonInnerAngleMax     ,
      kIronMuonReturnAngleMax    ,
      kIronMuonInhomBAngleMax    ,
      kAluminumMuonAngleMax      ,
      kPVCMuonAngleMax           ,
      kSiliconWaferAngleMax      ,
      kDiamondAngleMax           ,
      kNitrogenGasAngleMax       ,
      kLithiumFluorideAngleMax   ,
      kCalciumFluorideAngleMax   ,
      kMethaneTEAAngleMax        ,
      kCarbonFiberAngleMax       ,
      kBerylliumOxideAngleMax    ,
      kSVCarbonFiberAngleMax     ,
      kVacuumCoilAngleMax        ,
      kMylarCoilAngleMax         ,
      kAluminumCoilAngleMax      ,
      kStainlessCoilAngleMax     ,
      kVacuumCoilNFAngleMax      ,
      kMylarCoilNFAngleMax       ,
      kAluminumCoilNFAngleMax    ,
      kStainlessCoilNFAngleMax   ,
      kDREndplateHoleyAngleMax    ,
      kDRPreampVaporAngleMax      ,
      kDRNoPreampVaporAngleMax    ,
      kDROnEndplateAngleMax       ,
      -1 } ;

   const FReal     mScatMax[      nTMed ] = {
      kVacuumMScatMax            ,
      kVacuumPrecMScatMax        ,
      kAirMScatMax               ,
      kAirFieldMScatMax          ,
      kAirLoCutMScatMax          ,
      kAirLoCutFieldMScatMax     ,
      kAirLoCutFieldPrecMScatMax ,
      kBerylliumMScatMax         ,
      kSilverMScatMax            ,
      kGoldMScatMax              ,
      kTungstenMScatMax          ,
      kWaterMScatMax             ,
      kStainless316MScatMax      ,
      kRecQuadMScatMax           ,
      kAluminum6061MScatMax      ,
      kEpoxyMScatMax             ,
      kAluminumLoCutMScatMax     ,
      kHeProMScatMax             ,
      kMylarMScatMax             ,
      kKevlarMScatMax            ,
      kDR3InnerTubeMScatMax      ,
      kRohacellMScatMax          ,
      kCsIMScatMax               ,
      kLuciteMScatMax            ,
      kAluminumMScatMax          ,
      kCopperMScatMax            ,
      kG10MScatMax               ,
      kIronMuonOuterMScatMax     ,
      kIronMuonInnerMScatMax     ,
      kIronMuonReturnMScatMax    ,
      kIronMuonInhomBMScatMax    ,
      kAluminumMuonMScatMax      ,
      kPVCMuonMScatMax           ,
      kSiliconWaferMScatMax      ,
      kDiamondMScatMax           ,
      kNitrogenGasMScatMax       ,
      kLithiumFluorideMScatMax   ,
      kCalciumFluorideMScatMax   ,
      kMethaneTEAMScatMax        ,
      kCarbonFiberMScatMax       ,
      kBerylliumOxideMScatMax    ,
      kSVCarbonFiberMScatMax     ,
      kVacuumCoilMScatMax        ,
      kMylarCoilMScatMax         ,
      kAluminumCoilMScatMax      ,
      kStainlessCoilMScatMax     ,
      kVacuumCoilNFMScatMax      ,
      kMylarCoilNFMScatMax       ,
      kAluminumCoilNFMScatMax    ,
      kStainlessCoilNFMScatMax   ,
      kDREndplateHoleyMScatMax    ,
      kDRPreampVaporMScatMax      ,
      kDRNoPreampVaporMScatMax    ,
      kDROnEndplateMScatMax       ,
      -1 } ;

   const FReal     eLossMax[      nTMed ] = {
      kVacuumELossMax            ,
      kVacuumPrecELossMax        ,
      kAirELossMax               ,
      kAirFieldELossMax          ,
      kAirLoCutELossMax          ,
      kAirLoCutFieldELossMax     ,
      kAirLoCutFieldPrecELossMax ,
      kBerylliumELossMax         ,
      kSilverELossMax            ,
      kGoldELossMax              ,
      kTungstenELossMax          ,
      kWaterELossMax             ,
      kStainless316ELossMax      ,
      kRecQuadELossMax           ,
      kAluminum6061ELossMax      ,
      kEpoxyELossMax             ,
      kAluminumLoCutELossMax     ,
      kHeProELossMax             ,
      kMylarELossMax             ,
      kKevlarELossMax            ,
      kDR3InnerTubeELossMax      ,
      kRohacellELossMax          ,
      kCsIELossMax               ,
      kLuciteELossMax            ,
      kAluminumELossMax          ,
      kCopperELossMax            ,
      kG10ELossMax               ,
      kIronMuonOuterELossMax     ,
      kIronMuonInnerELossMax     ,
      kIronMuonReturnELossMax    ,
      kIronMuonInhomBELossMax    ,
      kAluminumMuonELossMax      ,
      kPVCMuonELossMax           ,
      kSiliconWaferELossMax      ,
      kDiamondELossMax           ,
      kNitrogenGasELossMax       ,
      kLithiumFluorideELossMax   ,
      kCalciumFluorideELossMax   ,
      kMethaneTEAELossMax        ,
      kCarbonFiberELossMax       ,
      kBerylliumOxideELossMax    ,
      kSVCarbonFiberELossMax     ,
      kVacuumCoilELossMax        ,
      kMylarCoilELossMax         ,
      kAluminumCoilELossMax      ,
      kStainlessCoilELossMax     ,
      kVacuumCoilNFELossMax      ,
      kMylarCoilNFELossMax       ,
      kAluminumCoilNFELossMax    ,
      kStainlessCoilNFELossMax   ,
      kDREndplateHoleyELossMax    ,
      kDRPreampVaporELossMax      ,
      kDRNoPreampVaporELossMax    ,
      kDROnEndplateELossMax       ,
      -1 } ;

   const FReal     trkPrec[       nTMed ] = {
      kVacuumTrkPrec            ,
      kVacuumPrecTrkPrec        ,
      kAirTrkPrec               ,
      kAirFieldTrkPrec          ,
      kAirLoCutTrkPrec          ,
      kAirLoCutFieldTrkPrec     ,
      kAirLoCutFieldPrecTrkPrec ,
      kBerylliumTrkPrec         ,
      kSilverTrkPrec            ,
      kGoldTrkPrec              ,
      kTungstenTrkPrec          ,
      kWaterTrkPrec             ,
      kStainless316TrkPrec      ,
      kRecQuadTrkPrec           ,
      kAluminum6061TrkPrec      ,
      kEpoxyTrkPrec             ,
      kAluminumLoCutTrkPrec     ,
      kHeProTrkPrec             ,
      kMylarTrkPrec             ,
      kKevlarTrkPrec            ,
      kDR3InnerTubeTrkPrec      ,
      kRohacellTrkPrec          ,
      kCsITrkPrec               ,
      kLuciteTrkPrec            ,
      kAluminumTrkPrec          ,
      kCopperTrkPrec            ,
      kG10TrkPrec               ,
      kIronMuonOuterTrkPrec     ,
      kIronMuonInnerTrkPrec     ,
      kIronMuonReturnTrkPrec    ,
      kIronMuonInhomBTrkPrec    ,
      kAluminumMuonTrkPrec      ,
      kPVCMuonTrkPrec           ,
      kSiliconWaferTrkPrec      ,
      kDiamondTrkPrec           ,
      kNitrogenGasTrkPrec       ,
      kLithiumFluorideTrkPrec   ,
      kCalciumFluorideTrkPrec   ,
      kMethaneTEATrkPrec        ,
      kCarbonFiberTrkPrec       ,
      kBerylliumOxideTrkPrec    ,
      kSVCarbonFiberTrkPrec     ,
      kVacuumCoilTrkPrec        ,
      kMylarCoilTrkPrec         ,
      kAluminumCoilTrkPrec      ,
      kStainlessCoilTrkPrec     ,
      kVacuumCoilNFTrkPrec      ,
      kMylarCoilNFTrkPrec       ,
      kAluminumCoilNFTrkPrec    ,
      kStainlessCoilNFTrkPrec   ,
      kDREndplateHoleyTrkPrec    ,
      kDRPreampVaporTrkPrec      ,
      kDRNoPreampVaporTrkPrec    ,
      kDROnEndplateTrkPrec       ,
      -1 } ;

   const FReal     eLossMin[      nTMed ] = {
      kVacuumELossMin            ,
      kVacuumPrecELossMin        ,
      kAirELossMin               ,
      kAirFieldELossMin          ,
      kAirLoCutELossMin          ,
      kAirLoCutFieldELossMin     ,
      kAirLoCutFieldPrecELossMin ,
      kBerylliumELossMin         ,
      kSilverELossMin            ,
      kGoldELossMin              ,
      kTungstenELossMin          ,
      kWaterELossMin             ,
      kStainless316ELossMin      ,
      kRecQuadELossMin           ,
      kAluminum6061ELossMin      ,
      kEpoxyELossMin             ,
      kAluminumLoCutELossMin     ,
      kHeProELossMin             ,
      kMylarELossMin             ,
      kKevlarELossMin            ,
      kDR3InnerTubeELossMin      ,
      kRohacellELossMin          ,
      kCsIELossMin               ,
      kLuciteELossMin            ,
      kAluminumELossMin          ,
      kCopperELossMin            ,
      kG10ELossMin               ,
      kIronMuonOuterELossMin     ,
      kIronMuonInnerELossMin     ,
      kIronMuonReturnELossMin    ,
      kIronMuonInhomBELossMin    ,
      kAluminumMuonELossMin      ,
      kPVCMuonELossMin           ,
      kSiliconWaferELossMin      ,
      kDiamondELossMin           ,
      kNitrogenGasELossMin       ,
      kLithiumFluorideELossMin   ,
      kCalciumFluorideELossMin   ,
      kMethaneTEAELossMin        ,
      kCarbonFiberELossMin       ,
      kBerylliumOxideELossMin    ,
      kSVCarbonFiberELossMin     ,
      kVacuumCoilELossMin        ,
      kMylarCoilELossMin         ,
      kAluminumCoilELossMin      ,
      kStainlessCoilELossMin     ,
      kVacuumCoilNFELossMin      ,
      kMylarCoilNFELossMin       ,
      kAluminumCoilNFELossMin    ,
      kStainlessCoilNFELossMin   ,
      kDREndplateHoleyELossMin    ,
      kDRPreampVaporELossMin      ,
      kDRNoPreampVaporELossMin    ,
      kDROnEndplateELossMin       ,
      -1 } ;

   const DABoolean loCuts[        nTMed ] = {
      kVacuumLoCuts            ,
      kVacuumPrecLoCuts        ,
      kAirLoCuts               ,
      kAirFieldLoCuts          ,
      kAirLoCutLoCuts          ,
      kAirLoCutFieldLoCuts     ,
      kAirLoCutFieldPrecLoCuts ,
      kBerylliumLoCuts         ,
      kSilverLoCuts            ,
      kGoldLoCuts              ,
      kTungstenLoCuts          ,
      kWaterLoCuts             ,
      kStainless316LoCuts      ,
      kRecQuadLoCuts           ,
      kAluminum6061LoCuts      ,
      kEpoxyLoCuts             ,
      kAluminumLoCutLoCuts     ,
      kHeProLoCuts             ,
      kMylarLoCuts             ,
      kKevlarLoCuts            ,
      kDR3InnerTubeLoCuts      ,
      kRohacellLoCuts          ,
      kCsILoCuts               ,
      kLuciteLoCuts            ,
      kAluminumLoCuts          ,
      kCopperLoCuts            ,
      kG10LoCuts               ,
      kIronMuonOuterLoCuts     ,
      kIronMuonInnerLoCuts     ,
      kIronMuonReturnLoCuts    ,
      kIronMuonInhomBLoCuts    ,
      kAluminumMuonLoCuts      ,
      kPVCMuonLoCuts           ,
      kSiliconWaferLoCuts      ,
      kDiamondLoCuts           ,
      kNitrogenGasLoCuts       ,
      kLithiumFluorideLoCuts   ,
      kCalciumFluorideLoCuts   ,
      kMethaneTEALoCuts        ,
      kCarbonFiberLoCuts       ,
      kBerylliumOxideLoCuts    ,
      kSVCarbonFiberLoCuts     ,
      kVacuumCoilLoCuts        ,
      kMylarCoilLoCuts         ,
      kAluminumCoilLoCuts      ,
      kStainlessCoilLoCuts     ,
      kVacuumCoilNFLoCuts      ,
      kMylarCoilNFLoCuts       ,
      kAluminumCoilNFLoCuts    ,
      kStainlessCoilNFLoCuts   ,
      kDREndplateHoleyLoCuts    ,
      kDRPreampVaporLoCuts      ,
      kDRNoPreampVaporLoCuts    ,
      kDROnEndplateLoCuts       ,
      false } ;

   const DABoolean noDelta[       nTMed ] = {
      kVacuumNoDelta            ,
      kVacuumPrecNoDelta        ,
      kAirNoDelta               ,
      kAirFieldNoDelta          ,
      kAirLoCutNoDelta          ,
      kAirLoCutFieldNoDelta     ,
      kAirLoCutFieldPrecNoDelta ,
      kBerylliumNoDelta         ,
      kSilverNoDelta            ,
      kGoldNoDelta              ,
      kTungstenNoDelta          ,
      kWaterNoDelta             ,
      kStainless316NoDelta      ,
      kRecQuadNoDelta           ,
      kAluminum6061NoDelta      ,
      kEpoxyNoDelta             ,
      kAluminumLoCutNoDelta     ,
      kHeProNoDelta             ,
      kMylarNoDelta             ,
      kKevlarNoDelta            ,
      kDR3InnerTubeNoDelta      ,
      kRohacellNoDelta          ,
      kCsINoDelta               ,
      kLuciteNoDelta            ,
      kAluminumNoDelta          ,
      kCopperNoDelta            ,
      kG10NoDelta               ,
      kIronMuonOuterNoDelta     ,
      kIronMuonInnerNoDelta     ,
      kIronMuonReturnNoDelta    ,
      kIronMuonInhomBNoDelta    ,
      kAluminumMuonNoDelta      ,
      kPVCMuonNoDelta           ,
      kSiliconWaferNoDelta      ,
      kDiamondNoDelta           ,
      kNitrogenGasNoDelta       ,
      kLithiumFluorideNoDelta   ,
      kCalciumFluorideNoDelta   ,
      kMethaneTEANoDelta        ,
      kCarbonFiberNoDelta       ,
      kBerylliumOxideNoDelta    ,
      kSVCarbonFiberNoDelta     ,
      kVacuumCoilNoDelta        ,
      kMylarCoilNoDelta         ,
      kAluminumCoilNoDelta      ,
      kStainlessCoilNoDelta     ,
      kVacuumCoilNFNoDelta      ,
      kMylarCoilNFNoDelta       ,
      kAluminumCoilNFNoDelta    ,
      kStainlessCoilNFNoDelta   ,
      kDREndplateHoleyNoDelta    ,
      kDRPreampVaporNoDelta      ,
      kDRNoPreampVaporNoDelta    ,
      kDROnEndplateNoDelta       ,
      false } ;

   const DABoolean userParms[    nTMed ] = {
      kVacuumUserParm            ,
      kVacuumPrecUserParm        ,
      kAirUserParm               ,
      kAirFieldUserParm          ,
      kAirLoCutUserParm          ,
      kAirLoCutFieldUserParm     ,
      kAirLoCutFieldPrecUserParm ,
      kBerylliumUserParm         ,
      kSilverUserParm            ,
      kGoldUserParm              ,
      kTungstenUserParm          ,
      kWaterUserParm             ,
      kStainless316UserParm      ,
      kRecQuadUserParm           ,
      kAluminum6061UserParm      ,
      kEpoxyUserParm             ,
      kAluminumLoCutUserParm     ,
      kHeProUserParm             ,
      kMylarUserParm             ,
      kKevlarUserParm            ,
      kDR3InnerTubeUserParm      ,
      kRohacellUserParm          ,
      kCsIUserParm               ,
      kLuciteUserParm            ,
      kAluminumUserParm          ,
      kCopperUserParm            ,
      kG10UserParm               ,
      kIronMuonOuterUserParm     ,
      kIronMuonInnerUserParm     ,
      kIronMuonReturnUserParm    ,
      kIronMuonInhomBUserParm    ,
      kAluminumMuonUserParm      ,
      kPVCMuonUserParm           ,
      kSiliconWaferUserParm      ,
      kDiamondUserParm           ,
      kNitrogenGasUserParm       ,
      kLithiumFluorideUserParm   ,
      kCalciumFluorideUserParm   ,
      kMethaneTEAUserParm        ,
      kCarbonFiberUserParm       ,
      kBerylliumOxideUserParm    ,
      kSVCarbonFiberUserParm     ,
      kVacuumCoilUserParm        ,
      kMylarCoilUserParm         ,
      kAluminumCoilUserParm      ,
      kStainlessCoilUserParm     ,
      kVacuumCoilNFUserParm      ,
      kMylarCoilNFUserParm       ,
      kAluminumCoilNFUserParm    ,
      kStainlessCoilNFUserParm   ,
      kDREndplateHoleyUserParm    ,
      kDRPreampVaporUserParm      ,
      kDRNoPreampVaporUserParm    ,
      kDROnEndplateUserParm       ,
      true } ;

   // Also make Helium Propane inhomogeneous field
   const DABoolean inhom[     nTMed ] = {
      false, false, false, false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, true, false, false,
      false, false, false, false, false, false, false, false, false, false,
      true , false, false, false, false, false, false, false, false, false,
      false, false, false, false, false, false, false, false, false, false,
      false, false, false, false,
      -1 } ;

   assert( -1       == mediaIndex[    nTMed-1 ] ) ;
   assert( -1       == materialIndex[ nTMed-1 ] ) ;
   assert( "Marker" == mediaString[   nTMed-1 ] ) ;
   assert( -1       == sensitive[     nTMed-1 ] ) ;
   assert( -1       == bFieldMax[     nTMed-1 ] ) ;
   assert( -1       == angleMax[      nTMed-1 ] ) ;
   assert( -1       == mScatMax[      nTMed-1 ] ) ;
   assert( -1       == eLossMax[      nTMed-1 ] ) ;
   assert( -1       == trkPrec[       nTMed-1 ] ) ;
   assert( -1       == eLossMin[      nTMed-1 ] ) ;
   assert( false    == loCuts[        nTMed-1 ] ) ;
   assert( false    == noDelta[       nTMed-1 ] ) ;
   assert( true     == userParms[     nTMed-1 ] ) ;

   for( UInt16 iTMed ( 0 ) ; iTMed != nTMed-1 ; ++iTMed )
   {
      const FInteger index ( userParms[ iTMed ] ?
			     -mediaIndex[ iTMed ] :
			     mediaIndex[ iTMed ]   ) ;
      const FInteger absIndex ( abs( index ) ) ;

      assert( ( !userParms[    iTMed ] &&
		-1 == mScatMax[ iTMed ] &&
		-1 == eLossMax[ iTMed ] && 
		-1 == eLossMin[ iTMed ]      ) ||
	      (  userParms[    iTMed ] &&
		-1 != mScatMax[ iTMed ] &&
		-1 != eLossMax[ iTMed ] && 
		-1 != eLossMin[ iTMed ]      )  ) ;

      const string namePad ( mediaString[ iTMed ] + "                    " ) ;
      FChar mediumName[20] ;
      for( UInt16 i ( 0 ); i != 19 ; ++i ) { mediumName[i] = namePad[i] ; }
      mediumName[19] = '$' ;

      const FInteger bFieldIndex ( 0 == bFieldMax[ iTMed ] ? 0 : 
				   ( inhom[ iTMed ] ? 1 : 3 ) ) ;

      gstmed_( index                  ,
	       mediumName             ,
	       materialIndex[ iTMed ] ,
	       sensitive[     iTMed ] ,
	       bFieldIndex            ,
	       bFieldMax[     iTMed ] ,
	       angleMax[      iTMed ] ,
	       mScatMax[      iTMed ] ,
	       eLossMax[      iTMed ] ,
	       trkPrec[       iTMed ] ,
	       eLossMin[      iTMed ] ,
	       0 ,
	       0 ) ;

      static const FChar* chCUTNEU("CUTNEU");
      gstpar_( absIndex, chCUTNEU, 0.001, 6);

      if( loCuts[  iTMed ] )
      {
	 static const FChar* chCUTHAD ( "CUTHAD" ) ;
	 static const FChar* chCUTMUO ( "CUTMUO" ) ;

	 gstpar_( absIndex, chCUTHAD, 0.001 ,6) ;
	 gstpar_( absIndex, chCUTMUO, 0.001 ,6) ;
      }

      if( noDelta[ iTMed ] )
      {
	 static const FChar* chDRAY  ( "DRAY"  ) ;
	 static const FChar* chLOSS  ( "LOSS"  ) ;
	 static const FChar* chDCUTE ( "DCUTE" ) ;
	 static const FChar* chDCUTM ( "DCUTM" ) ;

	 gstpar_( absIndex, chDRAY , 0.0    ,4) ;
	 gstpar_( absIndex, chLOSS , 2.0    ,4) ;
	 gstpar_( absIndex, chDCUTE, 10000. ,5) ;
	 gstpar_( absIndex, chDCUTM, 10000. ,5) ;
      }

      stringIntMap()[ mediaString[ iTMed ] ] = absIndex ; // fill map
   }

   report( INFO, kReport ) 
      << "Finished defining CLEO3 GEANT3 tracking media" << endl ;
}

// G3iMakeTrackingMedia::G3iMakeTrackingMedia( const G3iMakeTrackingMedia& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

G3iMakeTrackingMedia::~G3iMakeTrackingMedia()
{
}

//
// assignment operators
//
// const G3iMakeTrackingMedia& G3iMakeTrackingMedia::operator=( const G3iMakeTrackingMedia& rhs )
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

const G3iMakeTrackingMedia& 
G3iMakeTrackingMedia::instance( const double aMagField ) 
{
   if( 0 == k_instance )
   {
      k_instance = new G3iMakeTrackingMedia( aMagField ) ;
      assert( 0 != k_instance ) ;
   }
   return *k_instance ;
}
