#if !defined(STUPIDPROD_STUPIDSTORAGEHELPER_H)
#define STUPIDPROD_STUPIDSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     StupidProd
// Module:      StupidStorageHelper
// 
// Description: StorageHelper to store a Stupid
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: StupidStorageHelper.h,v 1.2 1999/10/18 18:14:37 cdj Exp $
//
// Revision history
//
// $Log: StupidStorageHelper.h,v $
// Revision 1.2  1999/10/18 18:14:37  cdj
// now inherits from SMStorageProxyHelper
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMStorageProxyHelper.h"
#include "StupidProd/Stupid.h"

// forward declarations

class StupidStorageHelper : public SMStorageProxyHelper<Stupid>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      StupidStorageHelper() ;
      //virtual ~StupidStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const Stupid& iData );

      //functions to deliver specific storage versions of Stupid
      Stupid* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const Stupid& getDefault() const;
      virtual DABoolean compare( const Stupid* iNewData, 
				 const Stupid& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      StupidStorageHelper( const StupidStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const StupidStorageHelper& operator=( const StupidStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( Stupid* (StupidStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* STUPIDPROD_STUPIDSTORAGEHELPER_H */
