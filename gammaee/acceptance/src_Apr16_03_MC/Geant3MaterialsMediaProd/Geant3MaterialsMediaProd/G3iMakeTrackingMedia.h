#if !defined(GEANT3MATERIALSMEDIAPROD_G3IMAKETRACKINGMEDIA_H)
#define GEANT3MATERIALSMEDIAPROD_G3IMAKETRACKINGMEDIA_H
// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      G3iMakeTrackingMedia
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec  8 11:11:31 EST 1998
// $Id: G3iMakeTrackingMedia.h,v 1.2 2001/03/15 21:51:38 bkh Exp $
//
// Revision history
//
// $Log: G3iMakeTrackingMedia.h,v $
// Revision 1.2  2001/03/15 21:51:38  bkh
// Get tracking media and mag field from start run
//
// Revision 1.1.1.1  1999/12/15 18:35:50  bkh
// imported Geant3MaterialsMediaProd sources
//
// Revision 1.1.1.1  1999/01/19 22:02:29  bkh
// imported Geant3MaterialsMediaProd sources
//

// system include files

// user include files

#include "Geant3MaterialsMediaProd/G3iMakeStuffBase.h"

// forward declarations

class G3iMakeTrackingMediaDummyFriend ;

class G3iMakeTrackingMedia : public G3iMakeStuffBase
{
      // ---------- friend classes and functions ---------------

      friend class G3iMakeTrackingMediaDummyFriend ;

   public:
      // ---------- constants, enums and typedefs --------------
      // ---------- Constructors and destructor ----------------
      virtual ~G3iMakeTrackingMedia();

      // ---------- member functions ---------------------------
      // ---------- const member functions ---------------------
      // ---------- static member functions --------------------

      static const G3iMakeTrackingMedia& instance( const double aMagField ) ;

   protected:
      // ---------- protected member functions -----------------
      // ---------- protected const member functions -----------
   private:
      // ---------- Constructors and destructor ----------------
      G3iMakeTrackingMedia( const double aMagField );
      G3iMakeTrackingMedia( const G3iMakeTrackingMedia& ); // stop default
      // ---------- assignment operator(s) ---------------------
      const G3iMakeTrackingMedia& operator=( const G3iMakeTrackingMedia& ) ;
      // ---------- private member functions -------------------
      // ---------- private const member functions -------------
      // ---------- data members -------------------------------
      // ---------- static data members ------------------------

      static G3iMakeTrackingMedia* k_instance ;
};

// inline function definitions

#endif /* GEANT3MATERIALSMEDIAPROD_G3IMAKETRACKINGMEDIA_H */
