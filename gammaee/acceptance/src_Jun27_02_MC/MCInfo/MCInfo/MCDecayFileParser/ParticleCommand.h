#if !defined(MCINFO_PARTICLECOMMAND_H)
#define MCINFO_PARTICLECOMMAND_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      ParticleCommand
// 
// Description: Class to parse the PARTICLE command in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: ParticleCommand.h,v 1.1 1999/06/22 21:29:52 lkg Exp $
//
// Revision history
//
// $Log: ParticleCommand.h,v $
// Revision 1.1  1999/06/22 21:29:52  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:16:42  lkg
// Initial MCDecayFileParser sources
//

// system include files
#include <fstream.h>

// user include files
#include "MCInfo/MCDecayFileParser/CommandParser.h"

// forward declarations
class MCParticlePropertStore;

class ParticleCommand : public CommandParser
{
   public:
      // ---------- Constructors and destructor ----------------
      ParticleCommand();
      virtual ~ParticleCommand();

      // ---------- const member functions ---------------------
      void run( const CommandParser::Command&,
		MCParticlePropertyStore&,
		ifstream&,
		CommandParser::ExtraInfo* ) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      ParticleCommand( const ParticleCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ParticleCommand& operator=( const ParticleCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCDecayFileParser/Template/ParticleCommand.cc"
//#endif

#endif /* MCINFO_PARTICLECOMMAND_H */
