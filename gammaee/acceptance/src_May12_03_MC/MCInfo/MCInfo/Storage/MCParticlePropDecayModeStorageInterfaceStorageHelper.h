// -*- C++ -*-
#if !defined(MCINFO_MCPARTICLEPROPDECAYMODESTORAGEINTERFACESTORAGEHELPER_H)
#define MCINFO_MCPARTICLEPROPDECAYMODESTORAGEINTERFACESTORAGEHELPER_H
//
// Package:     MCInfo
// Module:      MCParticlePropDecayModeStorageInterfaceStorageHelper
// 
// Description: StorageHelper to store a MCParticlePropDecayModeStorageInterface
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: MCParticlePropDecayModeStorageInterfaceStorageHelper.h,v 1.1 2001/12/19 18:20:20 lkg Exp $
//
// Revision history
//
// $Log: MCParticlePropDecayModeStorageInterfaceStorageHelper.h,v $
// Revision 1.1  2001/12/19 18:20:20  lkg
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
#include "MCInfo/Storage/MCParticlePropDecayModeStorageInterface.h"

// forward declarations
class MCParticlePropertyStoreStorageHelper;

class MCParticlePropDecayModeStorageInterfaceStorageHelper : public SMStorageHelper<MCParticlePropDecayModeStorageInterface>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      MCParticlePropDecayModeStorageInterfaceStorageHelper( MCParticlePropertyStoreStorageHelper* );
      //virtual ~MCParticlePropDecayModeStorageInterfaceStorageHelper();

      // ---------- member functions ---------------------------
      MCParticleProperty* currentProperty();

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const MCParticlePropDecayModeStorageInterface& iData );

      //functions to deliver specific storage versions of MCParticlePropDecayModeStorageInterface
      MCParticlePropDecayModeStorageInterface* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const MCParticlePropDecayModeStorageInterface& getDefault() const;
      virtual DABoolean compare( const MCParticlePropDecayModeStorageInterface* iNewData, 
				 const MCParticlePropDecayModeStorageInterface& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      MCParticlePropDecayModeStorageInterfaceStorageHelper(); // no default constructor
      MCParticlePropDecayModeStorageInterfaceStorageHelper( const MCParticlePropDecayModeStorageInterfaceStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const MCParticlePropDecayModeStorageInterfaceStorageHelper& operator=( const MCParticlePropDecayModeStorageInterfaceStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( MCParticlePropDecayModeStorageInterface* (MCParticlePropDecayModeStorageInterfaceStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      MCParticlePropertyStoreStorageHelper* m_storeStorageHelper;
      MCParticleProperty* m_currentProperty;

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* MCINFO_MCPARTICLEPROPERTYSTORAGEHELPER_H */
