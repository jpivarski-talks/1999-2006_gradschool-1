#if !defined(GEANT3MATERIALSMEDIAPROD_G3IMAKEMATERIALS_H)
#define GEANT3MATERIALSMEDIAPROD_G3IMAKEMATERIALS_H
// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      G3iMakeMaterials
// 
// Description: Singleton class that makes GEANT3 materials
//
// Usage: through the instance() fcn and the base class functions
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec  8 11:11:31 EST 1998
// $Id: G3iMakeMaterials.h,v 1.1.1.1 1999/12/15 18:35:49 bkh Exp $
//
// Revision history
//
// $Log: G3iMakeMaterials.h,v $
// Revision 1.1.1.1  1999/12/15 18:35:49  bkh
// imported Geant3MaterialsMediaProd sources
//
// Revision 1.1.1.1  1999/01/19 22:02:29  bkh
// imported Geant3MaterialsMediaProd sources
//

// system include files

// user include files

#include "DetectorGeometry/DGMaterial.h"

#include "Geant3Interface/G3iFortran.h"
#include "Geant3MaterialsMediaProd/G3iMakeStuffBase.h"

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"

class G3iMakeMaterialsDummyFriend ;

class G3iMakeMaterials : public G3iMakeStuffBase
{
      // ---------- friend classes and functions ---------------

      friend class G3iMakeMaterialsDummyFriend ; // suppress compiler warnings

   public:
      // ---------- constants, enums and typedefs --------------

      typedef DGMaterial::WeightedElement WtdElt ;
      typedef STL_VECTOR( WtdElt )        VecWt ;

      // ---------- Constructors and destructor ----------------

      virtual ~G3iMakeMaterials();

      // ---------- member functions ---------------------------
      // ---------- const member functions ---------------------

      const STL_MAP( string, VecWt )& wtdElt() const ;

      // ---------- static member functions --------------------

      static const G3iMakeMaterials& instance() ;

   protected:
      // ---------- protected member functions -----------------
      // ---------- protected const member functions -----------
   private:
      // ---------- Constructors and destructor ----------------
      G3iMakeMaterials();
      G3iMakeMaterials( const G3iMakeMaterials& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const G3iMakeMaterials& operator=( const G3iMakeMaterials& );
      // ---------- private member functions -------------------
      // ---------- private const member functions -------------
      // ---------- data members -------------------------------

      STL_MAP( string, VecWt )& m_wtdElt ;

      // ---------- static data members ------------------------

      static G3iMakeMaterials* k_instance ;
};

// inline function definitions

#endif /* GEANT3MATERIALSMEDIAPROD_G3IMAKEMATERIALS_H */
