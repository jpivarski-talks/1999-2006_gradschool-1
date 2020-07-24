#if !defined(MCINFO_VERSIONCOMMAND_H)
#define MCINFO_VERSIONCOMMAND_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      VersionCommand
// 
// Description: Class to parse the VERSION command in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: VersionCommand.h,v 1.2 2002/11/21 21:12:03 cleo3 Exp $
//
// Revision history
//
// $Log: VersionCommand.h,v $
// Revision 1.2  2002/11/21 21:12:03  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.1  1999/06/22 21:29:54  lkg
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

class VersionCommand : public CommandParser
{
   public:
      // ---------- Constructors and destructor ----------------
      VersionCommand();
      virtual ~VersionCommand();

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
      VersionCommand( const VersionCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const VersionCommand& operator=( const VersionCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCInfo/Template/VersionCommand.cc"
//#endif

#endif /* MCINFO_VERSIONCOMMAND_H */
