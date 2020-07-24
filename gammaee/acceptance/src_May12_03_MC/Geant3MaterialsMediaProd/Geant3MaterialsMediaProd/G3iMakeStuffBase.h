#if !defined(GEANT3MATERIALSMEDIAPROD_G3IMAKESTUFFBASE_H)
#define GEANT3MATERIALSMEDIAPROD_G3IMAKESTUFFBASE_H
// -*- C++ -*-
//
// Package:     Geant3MaterialsMediaProd
// Module:      G3iMakeStuffBase
// 
// Description: useful base class with map of string & integer
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Dec  8 11:11:31 EST 1998
// $Id: G3iMakeStuffBase.h,v 1.1.1.1 1999/12/15 18:35:49 bkh Exp $
//
// Revision history
//
// $Log: G3iMakeStuffBase.h,v $
// Revision 1.1.1.1  1999/12/15 18:35:49  bkh
// imported Geant3MaterialsMediaProd sources
//
// Revision 1.1.1.1  1999/01/19 22:02:29  bkh
// imported Geant3MaterialsMediaProd sources
//

// system include files

// user include files
#include <string>

// forward declarations

#include "STLUtility/fwd_map.h"

class G3iMakeStuffBase
{
      // ---------- friend classes and functions ---------------
   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      G3iMakeStuffBase();
      virtual ~G3iMakeStuffBase();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      const STL_MAP( string, UInt16 )& stringIntMap() const ;

      // ---------- static member functions --------------------
   protected:

      // ---------- protected member functions -----------------

      STL_MAP( string, UInt16 )& stringIntMap() ;

      // ---------- protected const member functions -----------
   private:
      // ---------- Constructors and destructor ----------------
      G3iMakeStuffBase( const G3iMakeStuffBase& ); // stop default
      // ---------- assignment operator(s) ---------------------
      const G3iMakeStuffBase& operator=( const G3iMakeStuffBase& );
      // ---------- private member functions -------------------
      // ---------- private const member functions -------------
      // ---------- data members -------------------------------

      STL_MAP( string, UInt16 )& m_stringIntMap ;

      // ---------- static data members ------------------------
};

// inline function definitions

#endif /* GEANT3MATERIALSMEDIAPROD_G3IMAKESTUFFBASE_H */
