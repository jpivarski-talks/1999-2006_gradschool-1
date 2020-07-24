#if !defined(MCINFODELIVERY_STANDARDMCPARTICLEPROPPROXY_H)
#define MCINFODELIVERY_STANDARDMCPARTICLEPROPPROXY_H
// -*- C++ -*-
//
// Package:     <MCInfoDelivery>
// Module:      StandardMCParticlePropProxy
// 
// Description: Proxy to create a standard store of particle property objects
//
// Usage:
//    The MCInfoDelivery producer, which holds this proxy, has as a
//    parameter the name of the standard CLEO decay.dec file (systemDecayDec
//    below).  In general this will point at a file in a fixed reference
//    area for CLEO 3, but this can be changed at run time for purposes of
//    testing updates to decay.dec.
//
//    This proxy parses that decay.dec file, creating a store of particle
//    property objects for insertion into the frame.
//
// Author:      Lawrence Gibbons
// Created:     Mon Nov 23 17:55:49 EST 1998
// $Id: StandardMCParticlePropProxy.h,v 1.1.1.1 1999/07/07 01:51:22 lkg Exp $
//
// Revision history
//
// $Log: StandardMCParticlePropProxy.h,v $
// Revision 1.1.1.1  1999/07/07 01:51:22  lkg
// initial MCInfoDelivery
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

// forward declarations
#include "C++Std/fwd_string.h"

class StandardMCParticlePropProxy : public ProxyTemplate< MCParticlePropertyStore >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef MCParticlePropertyStore value_type;

      // Constructors and destructor
      StandardMCParticlePropProxy( const string& systemDecayDec );
      virtual ~StandardMCParticlePropProxy();

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );

      // protected const member functions

   private:
      // Constructors and destructor
      StandardMCParticlePropProxy(); // stop default
      StandardMCParticlePropProxy( const StandardMCParticlePropProxy& );

      // assignment operator(s)
      const StandardMCParticlePropProxy& operator=( const StandardMCParticlePropProxy& );

      // data members
      value_type* m_StandardMCParticleProp ;
      string& m_standardDecayDecFile;
};

#endif /* MCINFODELIVERY_STANDARDMCPARTICLEPROPPROXY_H */
