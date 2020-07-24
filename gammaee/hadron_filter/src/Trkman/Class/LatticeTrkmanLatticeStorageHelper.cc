// -*- C++ -*-
//
// Package:     <package>
// Module:      LatticeTrkmanLatticeStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed Oct  6 10:38:22 EDT 1999
// $Id: LatticeTrkmanLatticeStorageHelper.cc,v 1.1 1999/10/18 21:30:20 cdj Exp $
//
// Revision history
//
// $Log: LatticeTrkmanLatticeStorageHelper.cc,v $
// Revision 1.1  1999/10/18 21:30:20  cdj
// renamed files
//
// Revision 1.2  1999/10/18 18:16:08  cdj
// no longer instantiates a SMLatticeStorageHelper in this file
//
// Revision 1.1  1999/10/11 22:00:37  cdj
// added Lattice storage code
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "Trkman/TrkmanLattice.h"

typedef TrkmanLattice _lattice_element_ ;
#include "StorageManagement/instantiate_latticehelper.h"

