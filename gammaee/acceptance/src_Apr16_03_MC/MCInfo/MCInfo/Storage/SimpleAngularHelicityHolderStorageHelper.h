// -*- C++ -*-
#if !defined(MCINFO_SIMPLEANGULARHELICITYHOLDERSTORAGEHELPER_H)
#define MCINFO_SIMPLEANGULARHELICITYHOLDERSTORAGEHELPER_H
//
// Package:     <MCInfo>
// Module:      SimplyAngularHelicityHolderStorageHelper
// 
/*
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Wed May 30 11:51:02 EDT 2001
// $Id: SimpleAngularHelicityHolderStorageHelper.h,v 1.1 2001/12/19 18:20:24 lkg Exp $
//
// Revision history
//
// $Log: SimpleAngularHelicityHolderStorageHelper.h,v $
// Revision 1.1  2001/12/19 18:20:24  lkg
// add storage helpers for particle properties
//
//

// system include files

// user include files

// forward declarations
#include "MCInfo/MCParticleProperty/SimpleAngularHelicity.h"
#include "StorageManagement/SMPtrHolderStorageHelper.h"
 
typedef SMPtrHolderStorageHelper<SimpleAngularHelicity*, SimpleAngularHelicity> SimpleAngularHelicityHolderStorageHelper;


#endif /* MCINFO_SIMPLEANGULARHELICITYHOLDERSTORAGEHELPER_H */
