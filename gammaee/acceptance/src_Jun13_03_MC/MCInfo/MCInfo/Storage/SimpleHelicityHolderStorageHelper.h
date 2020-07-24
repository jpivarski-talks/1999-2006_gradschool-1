// -*- C++ -*-
#if !defined(MCINFO_SIMPLEHELICITYHOLDERSTORAGEHELPER_H)
#define MCINFO_SIMPLEHELICITYHOLDERSTORAGEHELPER_H
//
// Package:     <MCInfo>
// Module:      SimpleHelicityHolderStorageHelper
// 
/*
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Wed May 30 11:51:02 EDT 2001
// $Id: SimpleHelicityHolderStorageHelper.h,v 1.1 2001/12/19 18:20:25 lkg Exp $
//
// Revision history
//
// $Log: SimpleHelicityHolderStorageHelper.h,v $
// Revision 1.1  2001/12/19 18:20:25  lkg
// add storage helpers for particle properties
//
//

// system include files

// user include files

// forward declarations
#include "MCInfo/MCParticleProperty/SimpleHelicity.h"
#include "StorageManagement/SMPtrHolderStorageHelper.h"
 
typedef SMPtrHolderStorageHelper<SimpleHelicity*, SimpleHelicity> SimpleHelicityHolderStorageHelper;


#endif /* MCINFO_SIMPLEHELICITYHOLDERSTORAGEHELPER_H */
