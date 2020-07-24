// -*- C++ -*-
//
// Package:     MCInfo
// Module:      T_StandardMCParticlePropProxy
// 
// Description: Instantiate Classes for MCParticlePropertyStore
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Mon Nov 23 17:55:06 EST 1998
// $Id: T_MCParticlePropertyStore.cc,v 1.2 2001/12/19 18:12:50 lkg Exp $
//
// Revision history
//
// $Log: T_MCParticlePropertyStore.cc,v $
// Revision 1.2  2001/12/19 18:12:50  lkg
// instantiate storage helpers for particle properties
//
// Revision 1.1  1999/06/22 21:28:58  lkg
// First real version of MCInfo in repository
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCDecayTree/MCListItr.h"
#include "MCInfo/MCDecayTree/Template/MCListItr.cc"

// STL classes
#include <vector>


#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE( MCParticlePropertyStore )
//Use the following if 'MCParticlePropertyStore' contains a ','
// also make sure there are no blank spaces within 'MCParticlePropertyStore'
/* INSTANTIATE_ONE_1_COMMA( MCParticlePropertyStore ) */
#include "FrameAccess/instantiate_one.h"

// storage helpers
#include "MCInfo/Storage/MCParticlePropertyStoreStorageHelper.h"
#include "MCInfo/Storage/MCParticlePropertyStorageHelper.h"
//#include "MCInfo/Storage/MCDecayModeStorageHelper.h"
#include "MCInfo/Storage/MCParticlePropDecayModeStorageInterfaceStorageHelper.h"
#include "MCInfo/Storage/MCDecayModeStorageHelper.h"
#include "MCInfo/Storage/SimpleHelicityStorageHelper.h"
#include "MCInfo/Storage/SimpleAngularHelicityStorageHelper.h"

template class  MCListItr< STL_VECTOR(MCParticlePropDecayModeStorageInterface*)::iterator,
		            MCParticlePropDecayModeStorageInterface,
			    MCParticlePropDecayModeStorageInterface >;

SM_REGISTER_STORAGE(MCParticlePropertyStoreStorageHelper)
SM_REGISTER_STORAGE(MCParticlePropertyStorageHelper)
//SM_REGISTER_STORAGE(MCParticleDecayModeStorageHelper)
static MCParticlePropDecayModeStorageInterfaceStorageHelper  s_MCParticlePropDecayModeStorageInterfaceStorageHelper( &s_MCParticlePropertyStoreStorageHelper );
static MCDecayModeStorageHelper s_MCDecayModeStorageHelper( &s_MCParticlePropDecayModeStorageInterfaceStorageHelper );
SM_REGISTER_STORAGE(SimpleHelicityStorageHelper)
SM_REGISTER_STORAGE(SimpleAngularHelicityStorageHelper)
