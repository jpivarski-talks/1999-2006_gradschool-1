// -*- C++ -*-
#if !defined(MCINFO_MCPARTICLESTORAGEHELPER_H)
#define MCINFO_MCPARTICLESTORAGEHELPER_H
//
// Package:     MCInfo
// Module:      MCParticleStorageHelper
// 
// Description: StorageHelper to store a MCParticle
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: MCParticleStorageHelper.h,v 1.2 2001/12/19 18:12:39 lkg Exp $
//
// Revision history
//
// $Log: MCParticleStorageHelper.h,v $
// Revision 1.2  2001/12/19 18:12:39  lkg
// change location of emacs mode hint
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
#include "MCInfo/MCDecayTree/MCParticle.h"

// forward declarations
class MCVertexStorageHelper;
class MCDecayTreeStorageHelper;

class MCParticleStorageHelper : public SMStorageHelper<MCParticle>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      MCParticleStorageHelper( MCDecayTreeStorageHelper&, 
			       MCVertexStorageHelper& ) ;

      //virtual ~MCParticleStorageHelper();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const MCParticle& iData );

      //functions to deliver specific storage versions of MCParticle
      MCParticle* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const MCParticle& getDefault() const;
      virtual DABoolean compare( const MCParticle* iNewData, 
				 const MCParticle& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      MCParticleStorageHelper( const MCParticleStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      MCParticleStorageHelper() ; // stop default
      const MCParticleStorageHelper& operator=( const MCParticleStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( MCParticle* (MCParticleStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      MCDecayTreeStorageHelper* m_dkTreeStorageHelper;
      MCVertexStorageHelper*    m_vtxStorageHelper;

      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* MCINFO_MCPARTICLESTORAGEHELPER_H */
