#if !defined(MCINFO_MCQQBAR_H)
#define MCINFO_MCQQBAR_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCQQBar
// 
// Description: The particle property representing a QQbar state before
//              hadronization ( eg., *SU* in decay.dec)
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sun May  2 21:45:23 EDT 1999
// $Id: MCQQBar.h,v 1.2 1999/07/06 19:38:16 lkg Exp $
//
// Revision history
//
// $Log: MCQQBar.h,v $
// Revision 1.2  1999/07/06 19:38:16  lkg
// qqbar id changes from Count -> Integer
//
// Revision 1.1  1999/06/22 21:30:14  lkg
// First real version of MCInfo in repository
//

// system include files

// user include files
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"

// forward declarations

class MCQQBar : public MCParticleProperty
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum quarkNumber { q = 0, d = 1, u = 2, s = 3, c = 4, b = 5, t = 6 };
      static const Integer kQQBarIdToQQId;

      // ---------- Constructors and destructor ----------------
      MCQQBar();
      MCQQBar( const MCQQBar& ); // stop default
      virtual ~MCQQBar();

      // ---------- member functions ---------------------------
      void setQQBarId( Integer ); // automatically will set QQId as well

      // ---------- const member functions ---------------------
      Integer qqBarId() const;
      const MCQQBar& operator=( const MCQQBar& );

      // ---------- static member functions --------------------
      static DABoolean upType(   quarkNumber quark );
      static DABoolean downType( quarkNumber quark );

      static Double calculateCharge( quarkNumber     quark,
				     quarkNumber antiquark );

      static Integer calculatePDGId( quarkNumber     quark,
				     quarkNumber antiquark );

      static Double calculateMinMass( quarkNumber     quark,
				      quarkNumber antiquark );

      static quarkNumber nameToNumber( char quarkName );

   private:
      // ---------- data members -------------------------------
      Count m_qqBarId;
};

#endif /* MCINFO_MCQQBAR_H */
