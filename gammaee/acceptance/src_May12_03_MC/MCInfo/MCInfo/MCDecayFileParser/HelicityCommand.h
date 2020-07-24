#if !defined(MCINFO_HELICITYCOMMAND_H)
#define MCINFO_HELICITYCOMMAND_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      HelicityCommand
// 
// Description: Class to parse the Helicity command in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: HelicityCommand.h,v 1.2 2002/11/21 21:12:00 cleo3 Exp $
//
// Revision history
//
// $Log: HelicityCommand.h,v $
// Revision 1.2  2002/11/21 21:12:00  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.1  1999/06/22 21:29:49  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:16:42  lkg
// Initial MCDecayFileParser sources
//

// system include files
#include "C++Std/fstream.h"

// user include files
#include "MCInfo/MCDecayFileParser/CommandParser.h"

// forward declarations
class MCParticlePropertStore;

class HelicityCommand : public CommandParser
{
   public:
      // ---------- Constructors and destructor ----------------
      HelicityCommand();
      virtual ~HelicityCommand();

      // ---------- const member functions ---------------------
      void run( const CommandParser::Command&, 
		MCParticlePropertyStore&,
		ifstream&,
		CommandParser::ExtraInfo* ) const;
      
   private:
      // ---------- Constructors and destructor ----------------
      HelicityCommand( const HelicityCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const HelicityCommand& operator=( const HelicityCommand& ); // stop default

};

#endif /* MCINFO_HELICITYCOMMAND_H */
