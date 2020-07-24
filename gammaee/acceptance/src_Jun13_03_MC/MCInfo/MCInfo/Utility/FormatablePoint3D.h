#if !defined(MCINFO_FORMATABLE3VECTOR_H)
#define MCINFO_FORMATABLE3VECTOR_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      FormatablePoint3D
// 
// Description: Point3D that allows user to "pass in" formatting for the values
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar 20 17:15:34 EST 1999
// $Id: FormatablePoint3D.h,v 1.1 2003/05/19 20:21:15 lkg Exp $
//
// Revision history
//
// $Log: FormatablePoint3D.h,v $
// Revision 1.1  2003/05/19 20:21:15  lkg
// vector and point classes that ARE the corresponding CLHEP classes, but specify a << operator that allows the user to specify the floating point format for the components
//
//

// system include files

// user include files
#include "CLHEP/Geometry/Point3D.h"

class FormatablePoint3D : public HepPoint3D
{
   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FormatablePoint3D() : HepPoint3D() {}
      FormatablePoint3D( const HepPoint3D& aVector ) :
         HepPoint3D( aVector ) {}

   virtual ~FormatablePoint3D() {}

   private:
      // ---------- private member functions ---------------------------
      FormatablePoint3D( const FormatablePoint3D& rhs ); // stop default

      // ---------- assignment operator ---------------------
      const FormatablePoint3D& operator=( const FormatablePoint3D& rhs ); // stop default

      // ---------- data members -------------------------------
};

// inline function definitions

// define output operator formatting in a nice fashion
inline ostream& operator <<(ostream& s, const FormatablePoint3D &q)
{
   int userWidth = s.width();
   return s << setw(0) << "("
      << setw(userWidth) << q.x() << ","
      << setw(userWidth) << q.y() << ","
      << setw(userWidth) << q.z() << ")";
}
#endif /* MCINFO_FORMATABLE3VECTOR_H */
