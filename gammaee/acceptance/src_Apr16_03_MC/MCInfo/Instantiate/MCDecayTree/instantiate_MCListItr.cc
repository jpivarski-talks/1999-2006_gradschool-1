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
// $Id: instantiate_MCListItr.cc,v 1.3 2000/05/01 22:48:05 lkg Exp $
//
// Revision history
//
// $Log: instantiate_MCListItr.cc,v $
// Revision 1.3  2000/05/01 22:48:05  lkg
// added valueType as an additional template parameter to make this more STL-like for StorageHelper -- entire scheme should get reevaluated
//
// Revision 1.2  1999/07/07 00:14:08  lkg
// instantiate the new reverse iterators as well as the forward iterators
//
// Revision 1.1  1999/06/22 21:29:16  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "MCInfo/MCDecayTree/MCVertex.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCListItr.h"
#include "MCInfo/MCDecayTree/Template/MCListItr.cc"

// STL classes
#include <vector>

// forward iterators
template class 
MCListItr< STL_VECTOR( MCParticle* )::iterator,             MCParticle, MCParticle >;

template class 
MCListItr< STL_VECTOR( MCParticle* )::const_iterator, const MCParticle, MCParticle >;

template class 
MCListItr< STL_VECTOR( MCVertex* )::iterator,             MCVertex, MCVertex >;

template class 
MCListItr< STL_VECTOR( MCVertex* )::const_iterator, const MCVertex, MCVertex >;

// reverse iterators
template class 
MCListItr< STL_VECTOR(MCParticle*)::reverse_iterator,             MCParticle, MCParticle >;

template class 
MCListItr< STL_VECTOR(MCParticle*)::const_reverse_iterator, const MCParticle, MCParticle >;

template class 
MCListItr< STL_VECTOR(MCVertex*)::reverse_iterator,             MCVertex, MCVertex >;

template class 
MCListItr< STL_VECTOR(MCVertex*)::const_reverse_iterator, const MCVertex, MCVertex >;

