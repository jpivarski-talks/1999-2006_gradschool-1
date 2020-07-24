#if !defined(MCINFO_GEANTCOMMAND_H)
#define MCINFO_GEANTCOMMAND_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      GeantCommand
// 
// Description: Class to parse the Geant command in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: GeantCommand.h,v 1.1 1999/10/19 21:24:48 lkg Exp $
//
// Revision history
//
// $Log: GeantCommand.h,v $
// Revision 1.1  1999/10/19 21:24:48  lkg
// Added geant Command, and **PRELIMINARY** version of mixing command
//
// Revision 1.1  1999/06/22 21:29:50  lkg
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

class GeantCommand : public CommandParser
{
   public:
      // ---------- Constructors and destructor ----------------
      GeantCommand();
      virtual ~GeantCommand();

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
      GeantCommand( const GeantCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const GeantCommand& operator=( const GeantCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCINFO/Template/GeantCommand.cc"
//#endif

#endif /* MCINFO_GEANTCOMMAND_H */
