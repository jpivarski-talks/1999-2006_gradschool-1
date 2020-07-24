//--------------------------------------------------------------------------
//
//
// Copyright Information: See EvtGen/COPYRIGHT
//
// Environment:
//      This software is part of the EvtGen package developed jointly
//      for the BaBar and CLEO collaborations.  If you use all or part
//      of it, please give an appropriate acknowledgement.
//
// Module: EvtItgThreeCoeffFcn.cc
//
// Description:
//      Class describing a function with three vectors of coefficients. 
//
// Modification history:
//
//    Jane Tinslay                March 21, 2001       Module created
//
//------------------------------------------------------------------------


#include "EvtGenModels/EvtItgThreeCoeffFcn.hh"

//-------------
// C Headers --
//-------------
extern "C" {
}

EvtItgThreeCoeffFcn::EvtItgThreeCoeffFcn( double (*theFunction)(double, const HepVector &, const HepVector &, const HepVector &), double lowerRange, double upperRange, const HepVector &coeffs1, const HepVector &coeffs2, const HepVector &coeffs3):
  EvtItgAbsFunction(lowerRange, upperRange),
  _coeffs1(coeffs1),
  _coeffs2(coeffs2), 
  _coeffs3(coeffs3),
  _myFunction(theFunction)
{}

EvtItgThreeCoeffFcn::~EvtItgThreeCoeffFcn( )
{}


double
EvtItgThreeCoeffFcn::myFunction(double x) const{
  return _myFunction(x, _coeffs1, _coeffs2, _coeffs3);
}

void
EvtItgThreeCoeffFcn::setCoeff(int vect, int which, double value)
{
  if (vect == 1) _coeffs1[which] = value;
  else if (vect == 2) _coeffs2[which] = value;
  else if (vect == 3) _coeffs3[which] = value;
}

double
EvtItgThreeCoeffFcn::getCoeff(int vect, int which)
{
  if (vect == 1) return _coeffs1[which];
  else if (vect == 2) return _coeffs2[which];
  else if (vect == 3) return _coeffs3[which];
  else {return 0;}
}
