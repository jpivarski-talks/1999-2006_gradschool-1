#if !defined(MCINFO_FORMATABLELORENTZVECTOR_H)
#define MCINFO_FORMATABLELORENTZVECTOR_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      FormatableLorentzVector
// 
// Description: Lorentz Vector that allows user to "pass in" formatting for the values
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar 20 17:15:34 EST 1999
// $Id: FormatableLorentzVector.h,v 1.1 2003/05/19 20:21:14 lkg Exp $
//
// Revision history
//
// $Log: FormatableLorentzVector.h,v $
// Revision 1.1  2003/05/19 20:21:14  lkg
// vector and point classes that ARE the corresponding CLHEP classes, but specify a << operator that allows the user to specify the floating point format for the components
//
//

// system include files

// user include files
#include "CLHEP/Vector/LorentzVector.h"

class FormatableLorentzVector : public HepLorentzVector
{
   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FormatableLorentzVector() : HepLorentzVector() {}
      FormatableLorentzVector( const HepLorentzVector& aVector ) :
         HepLorentzVector( aVector ) {}

   virtual ~FormatableLorentzVector() {}

   private:
      // ---------- private member functions ---------------------------
      FormatableLorentzVector( const FormatableLorentzVector& rhs ); // stop default

      // ---------- assignment operator ---------------------
      const FormatableLorentzVector& operator=( const FormatableLorentzVector& rhs ); // stop default

      // ---------- data members -------------------------------
};

// inline function definitions

// define output operator formatting in a nice fashion
inline ostream& operator <<(ostream& s, const FormatableLorentzVector &q)
{
   int userWidth = s.width();
   return s << setw(0) << "("
      << setw(userWidth) << q.x() << ","
      << setw(userWidth) << q.y() << ","
      << setw(userWidth) << q.z() << ";"
      << setw(userWidth) << q.t() << ")";
}
#endif /* MCINFO_FORMATABLELORENTZVECTOR_H */
