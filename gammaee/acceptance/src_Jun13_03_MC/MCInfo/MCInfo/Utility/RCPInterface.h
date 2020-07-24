#if !defined(MCINFO_RCPINTERFACE_H)
#define MCINFO_RCPINTERFACE_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      RCPInterface
// 
// Description: Interface a class needs to use a the reference-counting
//              pointer template
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Wed May 19 18:10:17 EDT 1999
// $Id: RCPInterface.h,v 1.1 1999/06/22 21:30:19 lkg Exp $
//
// Revision history
//
// $Log: RCPInterface.h,v $
// Revision 1.1  1999/06/22 21:30:19  lkg
// First real version of MCInfo in repository
//

// system include files
#include <assert.h>

// user include files

// forward declarations

class RCPInterface
{
   public:
      // ---------- Constructors and destructor ----------------
      RCPInterface() : m_refCount( 0 ) {};
      RCPInterface( const RCPInterface& ) : m_refCount( 0 ) {};
      virtual ~RCPInterface() {};

      // ---------- member functions ---------------------------
      void addReference() { ++m_refCount; };
      void removeReference() {
	 // we should have at least 1 reference remaining if we are being
	 // asked to remove a reference
	 assert( m_refCount > 0 );
	 --m_refCount;
      };

      // ---------- const member functions ---------------------
      DABoolean hasRefs() const { return ( 0 != m_refCount ); };

   private:
      // ---------- assignment operator(s) ---------------------
      const RCPInterface& operator=( const RCPInterface& ); // stop default

      // reference count
      Count m_refCount;
};
#endif /* MCINFO_RCPINTERFACE_H */
