// -*- C++ -*-
#if !defined(MCINFO_MCPARTICLEPROPDECAYMODESTORAGEINTERFACE_H)
#define MCINFO_MCPARTICLEPROPDECAYMODESTORAGEINTERFACE_H
//
// Package:     <MCInfo>
// Module:      MCParticlePropDecayModeStorageInterface
// 
/**\class MCParticlePropDecayModeStorageInterface MCParticlePropDecayModeStorageInterface.h MCInfo/MCParticlePropDecayModeStorageInterface.h

 Description: Interface class to allow storage of MCDecayModes after
              storage of all particles

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Fri May 25 10:08:47 EDT 2001
// $Id: MCParticlePropDecayModeStorageInterface.h,v 1.1 2001/12/19 18:20:20 lkg Exp $
//
// Revision history
//
// $Log: MCParticlePropDecayModeStorageInterface.h,v $
// Revision 1.1  2001/12/19 18:20:20  lkg
// add storage helpers for particle properties
//

// system include files

// user include files
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCDecayMode.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

// forward declarations

class MCParticlePropDecayModeStorageInterface
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      MCParticlePropDecayModeStorageInterface( MCParticlePropertyStore& aStore,
					       QQ_id aParticleId ) :
	 m_property( &(aStore.getModifiableUsingQQId(aParticleId)) ) {}
      MCParticlePropDecayModeStorageInterface( MCParticleProperty* aProp ) :
	 m_property( aProp ) {}
	 
      virtual ~MCParticlePropDecayModeStorageInterface() {};

      MCParticlePropDecayModeStorageInterface( const MCParticlePropDecayModeStorageInterface& rhs ): m_property( rhs.m_property ) {} // for storage helper

      // ---------- member functions ---------------------------
      void addDecayMode( const MCDecayMode& aMode ) {
	 m_property->addDecayMode( aMode );
      }

      MCParticleProperty* theProperty() { return m_property; }

      // ---------- const member functions ---------------------
      QQ_id QQId() const {
	 return m_property->QQId();
      }

      // decay mode container access
      MCParticleProperty::const_iterator begin() const {
	 return m_property->begin();
      }
      MCParticleProperty::const_iterator end() const {
	 return m_property->end();
      }

      DABoolean operator==( const MCParticlePropDecayModeStorageInterface& rhs ) const {
	 return (m_property == rhs.m_property);
      }

   private:
      // ---------- Constructors and destructor ----------------
      MCParticlePropDecayModeStorageInterface(); // stop default

      // ---------- assignment operator(s) ---------------------
      MCParticlePropDecayModeStorageInterface& operator=( const MCParticlePropDecayModeStorageInterface& ); // stop default

      // ---------- data members -------------------------------
      MCParticleProperty* m_property;
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/MCParticlePropDecayModeStorageInterface.cc"
//#endif

#endif /* MCINFO_MCPARTICLEPROPDECAYMODESTORAGEINTERFACE_H */
