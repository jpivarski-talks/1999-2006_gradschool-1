#if !defined(MCINFO_ANGULARHELICITYCOMMAND_H)
#define MCINFO_ANGULARHELICITYCOMMAND_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      AngularHelicityCommand
// 
// Description: Class to parse the AngularHelicity command in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: AngularHelicityCommand.h,v 1.1 1999/06/22 21:29:46 lkg Exp $
//
// Revision history
//
// $Log: AngularHelicityCommand.h,v $
// Revision 1.1  1999/06/22 21:29:46  lkg
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

class AngularHelicityCommand : public CommandParser
{
   public:
      // ---------- Constructors and destructor ----------------
      AngularHelicityCommand();
      virtual ~AngularHelicityCommand();

      // ---------- const member functions ---------------------
      void run( const CommandParser::Command&, 
		MCParticlePropertyStore&,
		ifstream&,
		CommandParser::ExtraInfo* ) const;
      
   private:
      // ---------- Constructors and destructor ----------------
      AngularHelicityCommand( const AngularHelicityCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const AngularHelicityCommand& operator=( const AngularHelicityCommand& ); // stop default

};

#endif /* MCINFO_ANGULARHELICITYCOMMAND_H */
