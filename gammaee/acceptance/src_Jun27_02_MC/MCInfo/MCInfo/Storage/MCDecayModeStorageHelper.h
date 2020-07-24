// -*- C++ -*-
#if !defined(MCINFO_MCDECAYMODESTORAGEHELPER_H)
#define MCINFO_MCDECAYMODESTORAGEHELPER_H
//
// Package:     MCInfo
// Module:      MCDecayModeStorageHelper
// 
// Description: StorageHelper to store a MCDecayMode
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: MCDecayModeStorageHelper.h,v 1.1 2001/12/19 18:20:19 lkg Exp $
//
// Revision history
//
// $Log: MCDecayModeStorageHelper.h,v $
// Revision 1.1  2001/12/19 18:20:19  lkg
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
#include "StorageManagement/SMPtrHolder.h" 
#include "MCInfo/MCParticleProperty/MCDecayMode.h"

// forward declarations
class MCParticlePropDecayModeStorageInterfaceStorageHelper;

class MCDecayModeStorageHelper : public SMStorageHelper<MCDecayMode>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef SMPtrHolder<SimpleHelicity*, SimpleHelicity> helHolder;
      typedef SMPtrHolder<SimpleAngularHelicity*, SimpleAngularHelicity> angHolder;
      // ---------- Constructors and destructor ----------------
      MCDecayModeStorageHelper( MCParticlePropDecayModeStorageInterfaceStorageHelper* anInterfaceHelper );
      //virtual ~MCDecayModeStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const MCDecayMode& iData );

      //functions to deliver specific storage versions of MCDecayMode
      MCDecayMode* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const MCDecayMode& getDefault() const;
      virtual DABoolean compare( const MCDecayMode* iNewData, 
				 const MCDecayMode& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      MCDecayModeStorageHelper(); // stop default
      MCDecayModeStorageHelper( const MCDecayModeStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const MCDecayModeStorageHelper& operator=( const MCDecayModeStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( MCDecayMode* (MCDecayModeStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- data members -------------------------------
      MCParticlePropDecayModeStorageInterfaceStorageHelper* m_interfaceHelper;
};

// inline function definitions

#endif /* MCINFO_MCDECAYMODESTORAGEHELPER_H */
