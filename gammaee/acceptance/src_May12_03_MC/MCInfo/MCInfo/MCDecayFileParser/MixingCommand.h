#if !defined(MCINFO_MIXINGCOMMAND_H)
#define MCINFO_MIXINGCOMMAND_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MixingCommand
// 
// Description: Class to parse the Mixing command in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: MixingCommand.h,v 1.2 2002/11/21 21:12:01 cleo3 Exp $
//
// Revision history
//
// $Log: MixingCommand.h,v $
// Revision 1.2  2002/11/21 21:12:01  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.1  1999/10/19 21:24:49  lkg
// Added geant Command, and **PRELIMINARY** version of mixing command
//
//

// system include files
#include "C++Std/fstream.h"

// user include files
#include "MCInfo/MCDecayFileParser/CommandParser.h"

// forward declarations
class MCParticlePropertStore;

class MixingCommand : public CommandParser
{
   public:
      // ---------- Constructors and destructor ----------------
      MixingCommand();
      virtual ~MixingCommand();

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
      MixingCommand( const MixingCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const MixingCommand& operator=( const MixingCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCINFO/Template/MixingCommand.cc"
//#endif

#endif /* MCINFO_MIXINGCOMMAND_H */
