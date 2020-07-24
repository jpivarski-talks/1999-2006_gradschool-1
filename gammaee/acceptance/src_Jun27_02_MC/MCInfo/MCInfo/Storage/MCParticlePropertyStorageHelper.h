// -*- C++ -*-
#if !defined(MCINFO_MCPARTICLEPROPERTYSTORAGEHELPER_H)
#define MCINFO_MCPARTICLEPROPERTYSTORAGEHELPER_H
//
// Package:     MCInfo
// Module:      MCParticlePropertyStorageHelper
// 
// Description: StorageHelper to store a MCParticleProperty
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: MCParticlePropertyStorageHelper.h,v 1.1 2001/12/19 18:20:22 lkg Exp $
//
// Revision history
//
// $Log: MCParticlePropertyStorageHelper.h,v $
// Revision 1.1  2001/12/19 18:20:22  lkg
// add storage helpers for particle properties
//
// Revision 1.2  1999/10/18 18:14:37  cdj
// now inherits from SMStorageProxyHelper
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMStorageProxyHelper.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"

// forward declarations

class MCParticlePropertyStorageHelper : public SMStorageHelper<MCParticleProperty>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      MCParticlePropertyStorageHelper();
      //virtual ~MCParticlePropertyStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const MCParticleProperty& iData );

      //functions to deliver specific storage versions of MCParticleProperty
      MCParticleProperty* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const MCParticleProperty& getDefault() const;
      virtual DABoolean compare( const MCParticleProperty* iNewData, 
				 const MCParticleProperty& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      MCParticlePropertyStorageHelper( const MCParticlePropertyStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const MCParticlePropertyStorageHelper& operator=( const MCParticlePropertyStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( MCParticleProperty* (MCParticlePropertyStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* MCINFO_MCPARTICLEPROPERTYSTORAGEHELPER_H */
