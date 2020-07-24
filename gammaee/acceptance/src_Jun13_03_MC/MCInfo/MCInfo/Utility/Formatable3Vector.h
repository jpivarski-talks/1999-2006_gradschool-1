#if !defined(MCINFO_FORMATABLE3VECTOR_H)
#define MCINFO_FORMATABLE3VECTOR_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      Formatable3Vector
// 
// Description: 3 Vector that allows user to "pass in" formatting for the values
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar 20 17:15:34 EST 1999
// $Id: Formatable3Vector.h,v 1.1 2003/05/19 20:21:14 lkg Exp $
//
// Revision history
//
// $Log: Formatable3Vector.h,v $
// Revision 1.1  2003/05/19 20:21:14  lkg
// vector and point classes that ARE the corresponding CLHEP classes, but specify a << operator that allows the user to specify the floating point format for the components
//
//

// system include files

// user include files
#include "CLHEP/Vector/ThreeVector.h"

class Formatable3Vector : public Hep3Vector
{
   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      Formatable3Vector() : Hep3Vector() {}
      Formatable3Vector( const Hep3Vector& aVector ) :
         Hep3Vector( aVector ) {}

   virtual ~Formatable3Vector() {}

   private:
      // ---------- private member functions ---------------------------
      Formatable3Vector( const Formatable3Vector& rhs ); // stop default

      // ---------- assignment operator ---------------------
      const Formatable3Vector& operator=( const Formatable3Vector& rhs ); // stop default

      // ---------- data members -------------------------------
};

// inline function definitions

// define output operator formatting in a nice fashion
inline ostream& operator <<(ostream& s, const Formatable3Vector &q)
{
   int userWidth = s.width();
   return s << setw(0) << "("
      << setw(userWidth) << q.x() << ","
      << setw(userWidth) << q.y() << ","
      << setw(userWidth) << q.z() << ")";
}
#endif /* MCINFO_FORMATABLE3VECTOR_H */
