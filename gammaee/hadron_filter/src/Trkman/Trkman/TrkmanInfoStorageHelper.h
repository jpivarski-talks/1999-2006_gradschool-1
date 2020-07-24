#if !defined(TRKMAN_TRKMANINFOSTORAGEHELPER_H)
#define TRKMAN_TRKMANINFOSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     Trkman
// Module:      TrkmanInfoStorageHelper
// 
// Description: StorageHelper to store a TrkmanInfo
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: TrkmanInfoStorageHelper.h,v 1.1 1999/10/18 18:13:05 cdj Exp $
//
// Revision history
//
// $Log: TrkmanInfoStorageHelper.h,v $
// Revision 1.1  1999/10/18 18:13:05  cdj
// first submission
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMStorageHelper.h"
#include "Trkman/TrkmanInfo.h"

// forward declarations

class TrkmanInfoStorageHelper : public SMStorageHelper<TrkmanInfo>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      TrkmanInfoStorageHelper() ;
      //virtual ~TrkmanInfoStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const TrkmanInfo& iData );

      //functions to deliver specific storage versions of TrkmanInfo
      TrkmanInfo* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const TrkmanInfo& getDefault() const;
      virtual DABoolean compare( const TrkmanInfo* iNewData, 
				 const TrkmanInfo& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      TrkmanInfoStorageHelper( const TrkmanInfoStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const TrkmanInfoStorageHelper& operator=( const TrkmanInfoStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( TrkmanInfo* (TrkmanInfoStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* TRKMAN_TRKMANINFOSTORAGEHELPER_H */
