// -*- C++ -*-
#if !defined(MCINFO_MCPARTICLEPROPERTYSTORESTORAGEHELPER_H)
#define MCINFO_MCPARTICLEPROPERTYSTORESTORAGEHELPER_H
//
// Package:     MCInfo
// Module:      MCParticlePropertyStoreStorageHelper
// 
// Description: StorageHelper to store a MCParticlePropertyStore
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: MCParticlePropertyStoreStorageHelper.h,v 1.1 2001/12/19 18:20:23 lkg Exp $
//
// Revision history
//
// $Log: MCParticlePropertyStoreStorageHelper.h,v $
// Revision 1.1  2001/12/19 18:20:23  lkg
// add storage helpers for particle properties
//
//

// system include files

// user include files
#include "StorageManagement/SMStorageProxyHelper.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

// forward declarations

class MCParticlePropertyStoreStorageHelper : public SMStorageProxyHelper<MCParticlePropertyStore>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      MCParticlePropertyStoreStorageHelper() ;

      //virtual ~MCParticlePropertyStoreStorageHelper();

      // ---------- member functions ---------------------------
      MCParticlePropertyStore& currentPropertyStore();

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const MCParticlePropertyStore& iData );

      //functions to deliver specific storage versions of MCParticlePropertyStore
      MCParticlePropertyStore* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const MCParticlePropertyStore& getDefault() const;
      virtual DABoolean compare( const MCParticlePropertyStore* iNewData, 
				 const MCParticlePropertyStore& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      MCParticlePropertyStoreStorageHelper( const MCParticlePropertyStoreStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const MCParticlePropertyStoreStorageHelper& operator=( const MCParticlePropertyStoreStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( MCParticlePropertyStore* (MCParticlePropertyStoreStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      MCParticlePropertyStore* m_currentStore;

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* MCINFO_MCPARTICLEPROPERTYSTORESTORAGEHELPER_H */
