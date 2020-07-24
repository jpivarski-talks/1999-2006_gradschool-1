#if !defined(MCINFO_QQBARCOMMAND_H)
#define MCINFO_QQBARCOMMAND_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      QQbarCommand
// 
// Description: Class to parse the QQBAR command in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: QQBarCommand.h,v 1.2 2002/11/21 21:12:02 cleo3 Exp $
//
// Revision history
//
// $Log: QQBarCommand.h,v $
// Revision 1.2  2002/11/21 21:12:02  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.1  1999/06/22 21:29:52  lkg
// First real version of MCInfo in repository
//
//

// system include files
#include "C++Std/fstream.h"

// user include files
#include "MCInfo/MCDecayFileParser/CommandParser.h"
#include "MCInfo/MCParticleProperty/MCQQBar.h"

// forward declarations
class MCParticlePropertyStore;

class QQBarCommand : public CommandParser
{
   public:
      // ---------- Constructors and destructor ----------------
      QQBarCommand();
      virtual ~QQBarCommand();

      // ---------- const member functions ---------------------
      void run( const CommandParser::Command&,
		MCParticlePropertyStore&,
		ifstream&,
		CommandParser::ExtraInfo* ) const;

      // ---------- static member functions --------------------
      static MCQQBar::quarkNumber nameToNumber( char quarkName );

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      QQBarCommand( const QQBarCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const QQBarCommand& operator=( const QQBarCommand& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCDecayFileParser/Template/QQBarCommand.cc"
//#endif

#endif /* MCINFO_QQBARCOMMAND_H */
