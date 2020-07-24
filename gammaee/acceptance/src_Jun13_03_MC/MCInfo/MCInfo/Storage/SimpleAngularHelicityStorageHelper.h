// -*- C++ -*-
#if !defined(MCINFO_SIMPLEANGULARHELICITYSTORAGEHELPER_H)
#define MCINFO_SIMPLEANGULARHELICITYSTORAGEHELPER_H
//
// Package:     MCInfo
// Module:      SimpleAngularHelicityStorageHelper
// 
// Description: StorageHelper to store a SimpleAngularHelicity
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: SimpleAngularHelicityStorageHelper.h,v 1.1 2001/12/19 18:20:24 lkg Exp $
//
// Revision history
//
// $Log: SimpleAngularHelicityStorageHelper.h,v $
// Revision 1.1  2001/12/19 18:20:24  lkg
// add storage helpers for particle properties
//
// Revision 1.1  2000/05/01 22:39:34  lkg
// added storage helpers to repository
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
#include "MCInfo/MCParticleProperty/SimpleAngularHelicity.h"

// forward declarations

class SimpleAngularHelicityStorageHelper : public SMStorageHelper<SimpleAngularHelicity>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SimpleAngularHelicityStorageHelper() ;

      //virtual ~SimpleAngularHelicityStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const SimpleAngularHelicity& iData );

      //functions to deliver specific storage versions of SimpleAngularHelicity
      SimpleAngularHelicity* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const SimpleAngularHelicity& getDefault() const;
      virtual DABoolean compare( const SimpleAngularHelicity* iNewData, 
				 const SimpleAngularHelicity& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      SimpleAngularHelicityStorageHelper( const SimpleAngularHelicityStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SimpleAngularHelicityStorageHelper& operator=( const SimpleAngularHelicityStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( SimpleAngularHelicity* (SimpleAngularHelicityStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* MCINFO_SIMPLEANGULARHELICITYSTORAGEHELPER_H */
