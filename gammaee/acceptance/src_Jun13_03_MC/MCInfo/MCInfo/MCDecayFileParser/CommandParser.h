#if !defined(MCINFO_COMMANDPARSER_H)
#define MCINFO_COMMANDPARSER_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      CommandParser
// 
// Description: Base Class for implementing parsing commands in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: CommandParser.h,v 1.3 2001/09/11 17:49:32 cdj Exp $
//
// Revision history
//
// $Log: CommandParser.h,v $
// Revision 1.3  2001/09/11 17:49:32  cdj
// fixed compilation problems
//
// Revision 1.2  2001/09/10 20:06:29  cleo3
// removed forward declaration of ifstream
//
// Revision 1.1  1999/06/22 21:29:48  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:16:42  lkg
// Initial MCDecayFileParser sources
//
#include "C++Std/fwd_ifstream.h"
//
// forward declarations
//
class MCParticlePropertyStore;
class MCDecayMode;

class CommandParser
{
   public:
      // a base class to be used if commands with subcommands must pass
      // on extra information
      class ExtraInfo{
	 public :
	    virtual ~ExtraInfo() {};
      };

      // pack the command into this structure for passing around
      struct Command
      {
	    string name;
	    string parameterList;
      };
      
      // costructor and destructor
      CommandParser( const string& theName ) : 
	 m_commandName( theName ) {}
      
      // access the name of the command
      string& name() { return m_commandName; }
      
      // run the command -- each command must supply a form of one of 
      // these forms.  For decay.dec commands
      virtual void run( const CommandParser::Command&,
			MCParticlePropertyStore&,
			ifstream&,
			ExtraInfo* = 0 ) const = 0;

      virtual ~CommandParser() {}

   private:
      string m_commandName;
};

#endif /* MCINFO_COMMANDPARSER_H */
