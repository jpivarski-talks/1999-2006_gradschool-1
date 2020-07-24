#if !defined(MCRESPONSEPROD_G3ICREATEPLACEDVOLUMES_H)
#define MCRESPONSEPROD_G3ICREATEPLACEDVOLUMES_H
// -*- C++ -*-
//
// Package:     MCResponseProd
// Module:      G3iCreatePlacedVolumes
// 
// Description: DGDetectorStore + G3iExtraVolSpecs = GEANT3 placed volumes
//
// Usage:
//        A class which, when instantiated, converts a
//        DGDetectorStore hierarchy plus a table of 
//        G3iExtraVolSpecs into GEANT3 placed volumes.
//        This must be used only in a GEANT3-initialized
//        environment, as its only purpose is to create 
//        "side effects", namely, to alter the contents
//        of GEANT3 fortran common blocks. After instantiation,
//        an object of this class holds nothing useful & may be 
//        discarded.
//
//        The primary purpose of the DetectorGeometry package
//        is to provide a uniform geometry for use in display,
//        reconstruction, & simulation. In order for it
//        to be useful, an interface to the simulation package
//        geometry code must be in place. This class provides
//        most of such an interface for GEANT3.
//
//        For GEANT3 veterans, with this class you will never
//        again have to call GSVOLU, GSPOS(P), GSROTM, GSATT, 
//        GSDETV, GSDETH.
//
//        Be wary, the "ONLY" option in GEANT3 gsvolu_ is 
//        hardwired to prevent "MANY" from ever being used, 
//        because it slows down performance & will not be 
//        allowed in GEANT4. Solve such problems now!
//
//        Similarly, this class assume GEANT3 DIGI structures
//        are not used & the arg NWDI to gsdetv_ is set to zero.
//
//        While modified for CLEO3 & DetectorGeometry, the smarts
//        of this code were composed while working at KEK in Japan,
//        under funding by KEK.
//
//
// Author:      Brian K. Heltsley
// Created:     Mon Oct 19 16:10:35 EDT 1998
// $Id: G3iCreatePlacedVolumes.h,v 1.1 2001/09/25 21:38:16 bkh Exp $
//
// Revision history
//
// $Log: G3iCreatePlacedVolumes.h,v $
// Revision 1.1  2001/09/25 21:38:16  bkh
// Moved routine here to solve solaris-8 linking problems
//
// Revision 1.4  1999/10/29 20:38:51  bkh
// Use parent-placed name instead of bounding volume name
// Allow interation over volume specs for cloning purposes
//
// Revision 1.3  1999/07/01 15:02:14  bkh
// Change check of repeated volume/copy to volume/copy/mother
//
// Revision 1.2  1999/03/23 19:25:14  bkh
// Make Mother of all Mothers (CLEO) once
//
// Revision 1.1.1.1  1999/01/19 22:02:28  bkh
// imported Geant3Interface sources
//

// system include files

// user include files
#include "Experiment/fortran_types.h"

// forward declarations

#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_set.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"
#include "ToolBox/Triplet.h"

class G3iExtraVolSpecs ;
class G3iExtraVolSpecsStore ;

class DGDetectorStore  ;
class DGConstVolumePtr ;
class DGVolumeShaped   ;
class DGPlacedVolume   ;

class HepTransform3D   ;

class G3iCreatePlacedVolumes
{
      // ---------- friend classes and functions ---------------
   public:
      // ---------- constants, enums and typedefs --------------

      typedef Triplet< string, UInt32, string > TripletStringUInt32String ;

      // ---------- Constructors and destructor ----------------

      G3iCreatePlacedVolumes(
	 const DGDetectorStore&       aDetStore ,
	 const G3iExtraVolSpecsStore& aExtra      ) ;

      virtual ~G3iCreatePlacedVolumes();

      // ---------- member functions ---------------------------
      // ---------- const member functions ---------------------
      // ---------- static member functions --------------------
   protected:
      // ---------- protected member functions -----------------
      // ---------- protected const member functions -----------
   private:
      // ---------- Constructors and destructor ----------------
      G3iCreatePlacedVolumes(); // stop default
      G3iCreatePlacedVolumes( const G3iCreatePlacedVolumes& ); // stop default
      // ---------- assignment operator(s) ---------------------
      const G3iCreatePlacedVolumes& operator=( const G3iCreatePlacedVolumes& );
      // ---------- private member functions -------------------

      // traverses a volume hierarchy, making/positioning geant3 volumes
      void traverse( const DGConstVolumePtr& aParent ) ;

      // volume definition a la gsvolu_
      void createVolume( const string&           aName  ,
			 const DGConstVolumePtr& aShape  ) ;  
	
      // volume placement a la gspos_
      void placeVolumeInMother( const DGPlacedVolume&   aPlace  ,
				const string&           aName   ,
				const DGConstVolumePtr& aMother   ) ;

      // ---------- private const member functions -------------

      const G3iExtraVolSpecsStore& vsStore()                  const ;

      const G3iExtraVolSpecs&      vSpec( const string& aId ) const ;

      void getShapeInfo( const DGConstVolumePtr& aShape  ,
			 string&                 aString ,
			 STL_VECTOR( float )&    aPar      )  const ;

      void setVolOrder()      const ;

      void setVolAtts()       const ;

      void setVolSensitive()  const ;

      // ---------- static member functions --------------------

      // converts transform to a rotation matrix & offset
      static UInt32 getRotation( const HepTransform3D& aTransform ) ;

      static void stringToChar4( const string& aString , FChar* aChar4 ) ;

      // ---------- data members -------------------------------

      const G3iExtraVolSpecsStore& m_vsStore              ;
      STL_SET( string )&           m_createdVolumeNames   ;
      STL_SET( string )&           m_traversedParentNames ;

      // ---------- static data members ------------------------
      static STL_SET( string )&                    m_globalCreatedVolumeNames ;
      static STL_SET( TripletStringUInt32String )& m_globalPlacedVolumeNames  ;

      static DABoolean k_madeCLEO ;
};

// inline function definitions

#endif /* MCRESPONSEPROD_G3ICREATEPLACEDVOLUMES_H */
