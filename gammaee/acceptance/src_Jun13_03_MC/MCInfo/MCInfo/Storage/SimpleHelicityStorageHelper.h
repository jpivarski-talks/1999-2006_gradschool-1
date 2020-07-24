// -*- C++ -*-
#if !defined(MCINFO_SIMPLEHELICITYSTORAGEHELPER_H)
#define MCINFO_SIMPLEHELICITYSTORAGEHELPER_H
//
// Package:     MCInfo
// Module:      SimpleHelicityStorageHelper
// 
// Description: StorageHelper to store a SimpleHelicity
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: SimpleHelicityStorageHelper.h,v 1.1 2001/12/19 18:20:25 lkg Exp $
//
// Revision history
//
// $Log: SimpleHelicityStorageHelper.h,v $
// Revision 1.1  2001/12/19 18:20:25  lkg
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
#include "MCInfo/MCParticleProperty/SimpleHelicity.h"

// forward declarations

class SimpleHelicityStorageHelper : public SMStorageHelper<SimpleHelicity>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SimpleHelicityStorageHelper() ;

      //virtual ~SimpleHelicityStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const SimpleHelicity& iData );

      //functions to deliver specific storage versions of SimpleHelicity
      SimpleHelicity* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const SimpleHelicity& getDefault() const;
      virtual DABoolean compare( const SimpleHelicity* iNewData, 
				 const SimpleHelicity& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      SimpleHelicityStorageHelper( const SimpleHelicityStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SimpleHelicityStorageHelper& operator=( const SimpleHelicityStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( SimpleHelicity* (SimpleHelicityStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* MCINFO_SIMPLEHELICITYSTORAGEHELPER_H */
