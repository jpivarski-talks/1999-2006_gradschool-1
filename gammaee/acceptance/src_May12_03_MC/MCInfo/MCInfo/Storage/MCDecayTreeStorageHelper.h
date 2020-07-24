#if !defined(MCINFO_MCDECAYTREESTORAGEHELPER_H)
#define MCINFO_MCDECAYTREESTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     MCInfo
// Module:      MCDecayTreeStorageHelper
// 
// Description: StorageHelper to store a MCDecayTree
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: MCDecayTreeStorageHelper.h,v 1.1 2000/05/01 22:39:34 lkg Exp $
//
// Revision history
//
// $Log: MCDecayTreeStorageHelper.h,v $
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
#include "MCInfo/MCDecayTree/MCDecayTree.h"

// forward declarations
class MCVertexStorageHelper;
class MCDecayTreeStorageHelper;

class MCDecayTreeStorageHelper : public SMStorageProxyHelper<MCDecayTree>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      MCDecayTreeStorageHelper() ;

      //virtual ~MCDecayTreeStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      const MCParticlePropertyStore& propertyStore() const {return *m_propertyStore;}

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const MCDecayTree& iData );

      //functions to deliver specific storage versions of MCDecayTree
      MCDecayTree* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const MCDecayTree& getDefault() const;
      virtual DABoolean compare( const MCDecayTree* iNewData, 
				 const MCDecayTree& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      MCDecayTreeStorageHelper( const MCDecayTreeStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const MCDecayTreeStorageHelper& operator=( const MCDecayTreeStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( MCDecayTree* (MCDecayTreeStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const MCParticlePropertyStore* m_propertyStore;

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* MCINFO_MCDECAYTREESTORAGEHELPER_H */
