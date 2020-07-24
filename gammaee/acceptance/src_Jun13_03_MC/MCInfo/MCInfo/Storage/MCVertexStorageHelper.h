#if !defined(MCINFO_MCVERTEXSTORAGEHELPER_H)
#define MCINFO_MCVERTEXSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     MCInfo
// Module:      MCVertexStorageHelper
// 
// Description: StorageHelper to store a MCVertex
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: MCVertexStorageHelper.h,v 1.3 2000/07/07 01:41:39 lkg Exp $
//
// Revision history
//
// $Log: MCVertexStorageHelper.h,v $
// Revision 1.3  2000/07/07 01:41:39  lkg
// Bug fix for unpacking particles w/ multiple vertices: need to use a stack to hold the current particle having vertices added
//
// Revision 1.2  2000/05/04 17:53:20  cdj
// make class is now inlined
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
#include <stack>

// user include files
#include "StorageManagement/SMStorageProxyHelper.h"
#include "MCInfo/MCDecayTree/MCVertex.h"

// forward declarations
class MCVertexStorageHelper;
class MCDecayTreeStorageHelper;

class MCVertexStorageHelper : public SMStorageHelper<MCVertex>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      MCVertexStorageHelper() ;

      //virtual ~MCVertexStorageHelper();

      // ---------- member functions ---------------------------
      void pushParticlePtr( MCParticle* aParticlePtr );
      void popParticlePtr();

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const MCVertex& iData );

      //functions to deliver specific storage versions of MCVertex
      MCVertex* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const MCVertex& getDefault() const;
      virtual DABoolean compare( const MCVertex* iNewData, 
				 const MCVertex& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      MCVertexStorageHelper( const MCVertexStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const MCVertexStorageHelper& operator=( const MCVertexStorageHelper& ); // stop default

      // ---------- private member functions -------------------
      void registerVersion( MCVertex* (MCVertexStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      stack< MCParticle*, deque< MCParticle* > > m_particlePtr;

      // ---------- static data members ------------------------

};

// inline function definitions

template<> 
inline
MCVertex*
SMStorageHelper<MCVertex>::make( const MCVertex& iTempData ) const
{
   //change this line if MCVertex does not have a copy constructor
   return iTempData.clone();
}


#endif /* MCINFO_MCVERTEXSTORAGEHELPER_H */
