// -*- C++ -*-
#if !defined(MCINFO_DELIVERDUMMYMCPPS_H)
#define MCINFO_DELIVERDUMMYMCPPS_H
//
// Package:     <MCInfo>
// Module:      DeliverDummyMCPPS
// 
/*

 Description: A singleton class that will serve up the dummy versions
              of MCParticlePropertyStore, MCDecayMode and 
	      MCParticleProperty needed for the storage helper

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Sun Apr  2 17:27:32 EDT 2000
// $Id: DeliverDummyMCPPS.h,v 1.1 2001/12/19 18:20:19 lkg Exp $
//
// Revision history
//
// $Log: DeliverDummyMCPPS.h,v $
// Revision 1.1  2001/12/19 18:20:19  lkg
// add storage helpers for particle properties
//
// Revision 1.1  2000/05/01 22:39:33  lkg
// added storage helpers to repository
//

// system include files

// user include files
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

// forward declarations
class MCParticleProperty;
class MCDecayMode;

class DeliverDummyMCPPS
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      DeliverDummyMCPPS();
      virtual ~DeliverDummyMCPPS();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      MCParticlePropertyStore&  dummyMCParticlePropertyStore();
      MCParticleProperty&       dummyMCParticleProperty();
      MCDecayMode&              dummyMCDecayMode();

      // ---------- static member functions --------------------
      // Singleton constructor-surrogate function
      static DeliverDummyMCPPS& instance( void );

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      DeliverDummyMCPPS( const DeliverDummyMCPPS& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const DeliverDummyMCPPS& operator=( const DeliverDummyMCPPS& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      MCParticlePropertyStore* m_dummyPropStore;
      MCDecayMode* m_dummyDecayMode;

      // ---------- static data members ------------------------
      static DeliverDummyMCPPS* m_instance;
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/DeliverDummyMCPPS.cc"
//#endif

#endif /* MCINFO_DELIVERDUMMYMCPPS_H */
