// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      instantiate_MCListItr
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Tue Feb 23 21:59:23 EST 1999
// $Id: instantiate_MCDecayTreeItr.cc,v 1.1 1999/06/22 21:29:15 lkg Exp $
//
// Revision history
//
// $Log: instantiate_MCDecayTreeItr.cc,v $
// Revision 1.1  1999/06/22 21:29:15  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <vector>
#include <deque>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "MCInfo/MCDecayTree/MCDecayTreeItr.h"
#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCVertex.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCListItr.h"
#include "MCInfo/MCDecayTree/Template/MCDecayTreeItr.cc"

// STL classes
#include <vector>
#include <deque>


template class 
MCDecayTreeItr< const MCParticle, MCVertex::const_iterator >;

template class 
MCDecayTreeItr< const MCVertex, MCParticle::const_iterator >;

