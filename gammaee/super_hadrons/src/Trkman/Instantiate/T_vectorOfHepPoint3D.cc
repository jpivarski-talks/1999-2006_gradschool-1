// -*- C++ -*-
//
// Package:     CcP2ReconProd
// Module:      T_vector
// 
// Description: instantiate vector
//
// Implementation:
//
// Author:      Brian Heltsley
// Created:     Thu Apr 29 15:21:27 EST 1999
// $Id: T_vectorOfHepPoint3D.cc,v 1.1 2002/11/04 18:30:14 nea9 Exp $
//
// Revision history
//
// $Log: T_vectorOfHepPoint3D.cc,v $
// Revision 1.1  2002/11/04 18:30:14  nea9
// New CleoIII Trkman files added
//
// Revision 1.1.1.1  2001/01/17 22:21:37  bkh
// imported CcP2ReconProd sources
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
//#include <utility>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CLHEP/Geometry/Point3D.h"

// STL classes
#include <vector>

typedef HepPoint3D  _vector_contents_;

#include "STLUtility/instantiate_vector.h"
