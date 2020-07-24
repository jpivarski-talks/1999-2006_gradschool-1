#if !defined(MCINFO_CHANNELCOMMAND_H)
#define MCINFO_CHANNELCOMMAND_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      ChannelCommand
// 
// Description: Class to parse the Channel command in decay.dec
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:01 EST 1998
// $Id: ChannelCommand.h,v 1.2 2002/11/21 21:11:58 cleo3 Exp $
//
// Revision history
//
// $Log: ChannelCommand.h,v $
// Revision 1.2  2002/11/21 21:11:58  cleo3
// changed fstream.h to C++Std/fstream.h
//
// Revision 1.1  1999/06/22 21:29:48  lkg
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

class ChannelCommand : public CommandParser
{
   public:
      // ---------- Constructors and destructor ----------------
      ChannelCommand();
      virtual ~ChannelCommand();

      // ---------- const member functions ---------------------
      void run( const CommandParser::Command&, 
		MCParticlePropertyStore&,
		ifstream&,
		CommandParser::ExtraInfo* ) const;
      
   private:
      // ---------- Constructors and destructor ----------------
      ChannelCommand( const ChannelCommand& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const ChannelCommand& operator=( const ChannelCommand& ); // stop default

};

#endif /* MCINFO_CHANNELCOMMAND_H */
