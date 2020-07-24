#if !defined(TRKMANLATTICELINKTrkmanLatticeSTORAGEHELPER_H)
#define TRKMANLATTICELINKTrkmanLatticeSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     Trkman
// Module:      LatticeLinkTrkmanLatticeStorageHelper
// 
// Description: Storage helper to store a TrkmanLink which is a Lattice link
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Wed Oct  6 10:46:26 EDT 1999
// $Id: LatticeLinkTrkmanLatticeStorageHelper.h,v 1.1 1999/10/18 21:30:19 cdj Exp $
//
// Revision history
//
// $Log: LatticeLinkTrkmanLatticeStorageHelper.h,v $
// Revision 1.1  1999/10/18 21:30:19  cdj
// renamed files
//
// Revision 1.1  1999/10/11 22:00:37  cdj
// added Lattice storage code
//

// system include files

// user include files
#include "StorageManagement/SMStorageHelper.h"
#include "Trkman/TrkmanLink.h"
#include "Trkman/TrkmanLattice.h"
#include "StorageManagement/SMLatticeLinkInfoBase.h"

// forward declarations

class LatticeLinkTrkmanLatticeStorageHelper :
   public SMStorageHelper< 
           SMLatticeLinkInfoBase< TrkmanLattice > >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef SMLatticeLinkInfoBase< TrkmanLattice > StoreType;

      // ---------- Constructors and destructor ----------------
      LatticeLinkTrkmanLatticeStorageHelper();
      virtual ~LatticeLinkTrkmanLatticeStorageHelper();

      // ---------- member functions ---------------------------
      virtual StoreType* deliverV1( SMSourceStream& iSource );

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const StoreType& iData );

      // ---------- protected const member functions -----------
      virtual const StoreType& getDefault() const;
      virtual DABoolean compare( const StoreType* iNewData, 
				 const StoreType& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      LatticeLinkTrkmanLatticeStorageHelper( const LatticeLinkTrkmanLatticeStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const LatticeLinkTrkmanLatticeStorageHelper& operator=( const LatticeLinkTrkmanLatticeStorageHelper& ); // stop default

      // ---------- private member functions -------------------
   void registerVersion( StoreType* (LatticeLinkTrkmanLatticeStorageHelper::*iMethod)( SMSourceStream&) );
      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/LatticeLinkTrkmanLatticeStorageHelper.cc"
//#endif

#endif /* TRKMANLATTICELINKTrkmanLatticeSTORAGEHELPER_H */
