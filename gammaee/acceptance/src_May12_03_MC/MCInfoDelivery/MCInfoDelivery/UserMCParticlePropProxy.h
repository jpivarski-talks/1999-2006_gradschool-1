#if !defined(MCINFODELIVERY_USERMCPARTICLEPROPPROXY_H)
#define MCINFODELIVERY_USERMCPARTICLEPROPPROXY_H
// -*- C++ -*-
//
// Package:     <MCInfoDelivery>
// Module:      UserMCParticlePropProxy
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Mon Nov 23 17:55:35 EST 1998
// $Id: UserMCParticlePropProxy.h,v 1.1.1.1 1999/07/07 01:51:22 lkg Exp $
//
// Revision history
//
// $Log: UserMCParticlePropProxy.h,v $
// Revision 1.1.1.1  1999/07/07 01:51:22  lkg
// initial MCInfoDelivery
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

// forward declarations

class UserMCParticlePropProxy : public ProxyTemplate< MCParticlePropertyStore >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef MCParticlePropertyStore value_type;

      // Constructors and destructor
      UserMCParticlePropProxy(const string& userDecayDec );
      virtual ~UserMCParticlePropProxy();

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );

      // protected const member functions

   private:
      // Constructors and destructor
      UserMCParticlePropProxy(); // stop default
      UserMCParticlePropProxy( const UserMCParticlePropProxy& );

      // assignment operator(s)
      const UserMCParticlePropProxy& operator=( const UserMCParticlePropProxy& );

      // data members
      value_type* m_UserMCParticleProp ;
      string& m_userDecayDecFile;
};

#endif /* MCINFODELIVERY_USERMCPARTICLEPROPPROXY_H */
