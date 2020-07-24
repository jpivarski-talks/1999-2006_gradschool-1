#if !defined(MCINFO_PDGCOMMAND_H)
#define MCINFO_PDGCOMMAND_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      PDGCommand
// 
// Description: Class to parse the PDG command in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: PDGCommand.h,v 1.1 1999/06/22 21:29:50 lkg Exp $
//
// Revision history
//
// $Log: PDGCommand.h,v $
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

class PDGCommand : public CommandParser
{
   public:
      // ---------- Constructors and destructor ----------------
      PDGCommand();
      virtual ~PDGCommand();

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
      PDGCommand( const PDGCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDGCommand& operator=( const PDGCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCINFO/Template/PDGCommand.cc"
//#endif

#endif /* MCINFO_PDGCOMMAND_H */
