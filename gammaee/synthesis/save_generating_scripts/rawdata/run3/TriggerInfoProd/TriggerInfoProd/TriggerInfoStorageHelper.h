#if !defined(TRIGGERINFOPROD_TRIGGERINFOSTORAGEHELPER_H)
#define TRIGGERINFOPROD_TRIGGERINFOSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     TriggerInfoProd
// Module:      TriggerInfoStorageHelper
// 
// Description: StorageHelper to store a TriggerInfo
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: TriggerInfoStorageHelper.h,v 1.2 1999/10/18 18:14:37 cdj Exp $
//
// Revision history
//
// $Log: TriggerInfoStorageHelper.h,v $
// Revision 1.2  1999/10/18 18:14:37  cdj
// now inherits from SMStorageProxyHelper
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMStorageProxyHelper.h"
#include "TriggerInfoProd/TriggerInfo.h"

// forward declarations

class TriggerInfoStorageHelper : public SMStorageProxyHelper<TriggerInfo>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      TriggerInfoStorageHelper() ;
      //virtual ~TriggerInfoStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const TriggerInfo& iData );

      //functions to deliver specific storage versions of TriggerInfo
      TriggerInfo* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const TriggerInfo& getDefault() const;
      virtual DABoolean compare( const TriggerInfo* iNewData, 
				 const TriggerInfo& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      TriggerInfoStorageHelper( const TriggerInfoStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const TriggerInfoStorageHelper& operator=( const TriggerInfoStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( TriggerInfo* (TriggerInfoStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* TRIGGERINFOPROD_TRIGGERINFOSTORAGEHELPER_H */
