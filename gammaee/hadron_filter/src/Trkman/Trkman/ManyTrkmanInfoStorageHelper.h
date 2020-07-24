#if !defined(TRKMAN_MANYTRKMANINFOSTORAGEHELPER_H)
#define TRKMAN_MANYTRKMANINFOSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     <Trkman>
// Module:      ManyTrkmanInfoStorageHelper
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Wed May 19 17:04:02 EDT 1999
// $Id: ManyTrkmanInfoStorageHelper.h,v 1.2 1999/09/30 22:38:57 cdj Exp $
//
// Revision history
//
// $Log: ManyTrkmanInfoStorageHelper.h,v $
// Revision 1.2  1999/09/30 22:38:57  cdj
// now actually works
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMFAPtrTableStorageHelper.h"
#include "Trkman/TrkmanInfo.h"

// forward declarations

typedef SMFAPtrTableStorageHelper<TrkmanInfo> ManyTrkmanInfoStorageHelper ;

#endif /* TRKMAN_MANYTRKMANINFOSTORAGEHELPER_H */
