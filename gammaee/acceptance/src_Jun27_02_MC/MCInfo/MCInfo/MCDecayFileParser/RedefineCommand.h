#if !defined(MCINFO_REDEFINECOMMAND_H)
#define MCINFO_REDEFINECOMMAND_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      RedefineCommand
// 
// Description: Class to parse the REDEFINE command in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: RedefineCommand.h,v 1.1 2001/10/25 18:56:56 lkg Exp $
//
// Revision history
//
// $Log: RedefineCommand.h,v $
// Revision 1.1  2001/10/25 18:56:56  lkg
// Added REDEFINE command to decay.dec parsing to allow user to tweak properties of a pre-existing particle
//
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

class RedefineCommand : public CommandParser
{
   public:
      // ---------- Constructors and destructor ----------------
      RedefineCommand();
      virtual ~RedefineCommand();

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
      RedefineCommand( const RedefineCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const RedefineCommand& operator=( const RedefineCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCDecayFileParser/Template/RedefineCommand.cc"
//#endif

#endif /* MCINFO_REDEFINECOMMAND_H */
