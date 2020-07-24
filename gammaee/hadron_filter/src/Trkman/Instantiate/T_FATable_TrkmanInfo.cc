// -*- C++ -*-
//
// File:    T_FATable_TrkmanInfo.cc
// Package: TrkmanInfo
// Module:  Trkman
// 
// Description: Instantiate FATable of TrkmanInfo
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Thomas Meyer
// Created:     Tue Jan 15 14:06:46 EST 2002
// $Id: T_FATable_TrkmanInfo.cc,v 1.1.1.1 2002/01/28 13:56:14 tom Exp $
//
// Revision history
//
// $Log: T_FATable_TrkmanInfo.cc,v $
// Revision 1.1.1.1  2002/01/28 13:56:14  tom
// Imported Trkman library sources
//
/* ******************************************************************** */

#include "Experiment/Experiment.h"

// USER INCLUDE FILES
#include "Trkman/TrkmanInfo.h"

#include "FrameAccess/FAPtrTable.h"

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_MANY( TrkmanInfo )
//Use the following if 'TrkmanInfo' contains a ','
// also make sure there are no blank spaces within 'TrkmanInfo'
/* INSTANTIATE_MANY_1_COMMA( TrkmanInfo ) */

//Uncomment the following if TrkmanInfo ::Identifier is not
// some type of unsigned integer
//#define INSTANTIATE_FATABLE_MAP
#include "FrameAccess/instantiate_many.h"

#include "Trkman/TrkmanInfoStorageHelper.h"
SM_REGISTER_STORAGE(TrkmanInfoStorageHelper)

#include "Trkman/ManyTrkmanInfoStorageHelper.h"
SM_REGISTER_STORAGE(ManyTrkmanInfoStorageHelper)
