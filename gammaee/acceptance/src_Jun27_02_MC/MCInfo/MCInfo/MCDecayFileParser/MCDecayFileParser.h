#if !defined(MCINFO_MCDECAYFILEPARSER_H)
#define MCINFO_MCDECAYFILEPARSER_H

// Package:     <MCInfo>
// Module:      MCDecayFileParser
// 
// Description: Parse a decay.dec-style file, modifying an 
//              MCParticlePropertyStore
//
// Usage:

//    To read in a decay specification file MyDecayFile and modify
//    MyPropertyStore based on the contents, create a MCDecayFileParser and
//    execute its parseFile member function, passing in references to the
//    file name and the property store to be modified:
//    
//       string myDecayFile = "mySpecialDecays.dec";
//       MCParticlePropertyStore myPropertyStore;
//    
//       MCDecayFileParser aParser( myDecayFile );
//       aParser.parseFile( myDecayFile, myPropertyStore );
//    
//    For ease of maintenance, one can request the parser to list the
//    decay.dec commands it knows.
//    
//    The parser operates in two different states.  When the user invokes a
//    new parser, it is in its primary state, where it is expected to
//    create/modify particles in the particle property store.  In this
//    state, each command read should specify
//       1) the command name
//       2) a particle ID -- name, qq id, whatever it would like
//       3) an (optional) parameter list -- that specify how to modify the
//          particle
//    
//    Each command encountered in this state is passed the particle store to
//    be modified, allowing it to add, modify or delete particles as
//    specified.
//    
//    The DECAY command, however, has subcommands that modify various decay
//    modes.  The DECAY command can create a new parser in the
//    modifyDecayMode state.  In this state, each command is passed a
//    DecayMode object that should be modified.

//
// Author:      Lawrence Gibbons
// Created:     Wed Nov  4 13:13:36 EDT 1998
// $Id: MCDecayFileParser.h,v 1.1 1999/06/22 21:29:50 lkg Exp $
//
// Revision history
//
// $Log: MCDecayFileParser.h,v $
// Revision 1.1  1999/06/22 21:29:50  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:16:42  lkg
// Initial MCDecayFileParser sources
//

// system include files
#include <string>
#include <map>
#include <vector>
#include <fstream.h>

// user include files
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCDecayFileParser/CommandParser.h"

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"


class MCDecayFileParser 
{
      
      // ---------- constants, enums and typedefs --------------
      enum parseState { processCommand, processSubcommand };

   public:
            
      // constructor and destructor
      // create a parser that will parse the file pointed to by fileName
      MCDecayFileParser( const string& fileName );
      // create a parser that will parse an open stream until a specific
      // terminator command is reached.  This allows commands with
      // subcommands to cause the parser to change state
      MCDecayFileParser( ifstream& decayFileStream,
			 const string& terminatorCommand );
      virtual ~MCDecayFileParser();
      
      
      // ---------- const member functions ---------------------
      
      // parse the information until, modifying the property store passed in
      // (in the modifyParticles state)
      void parse( MCParticlePropertyStore& aStore, 
		  CommandParser::ExtraInfo* info = 0 );
      
      // output a list of the known commands
      // void listKnownCommands() const;
      
      // ---------- static member functions --------------------
      
      
      
   private:
      // no default copy or assignment operator
      MCDecayFileParser( const MCDecayFileParser& ); // stop default
      const MCDecayFileParser& 
      operator=( const MCDecayFileParser& ); // stop default
      
      // utility routine to read a line from the file, creating a new
      // command object, and returning a pointer to that object
      CommandParser::Command readCommand();
      
      // -------------------- private typedefs -------------------------
      // to be used only for implementing the containers of known and
      // unknown commands for the parsers.
      typedef STL_MAP( string, CommandParser* ) CommandMap;
      typedef STL_VECTOR( string ) UnknownCommandList;

      // ---------- private static member functions --------------------

      // a function to initialize all the known commands
      static void initializeCommands();
      
      // check if this is the first time an object of this time has been
      // created
      static DABoolean isFirstInstance( void );
      
      // add a new command parser function to the CommandMap
      static void addCommandFunction( CommandParser* );
      
      // add terminator commands that indicate end of parsing of a
      // file or subcommand, but take no action
      static void addTerminatorCommand( const string& commandName );

      // maintain static list of commands that will be common to all
      // instantiated decay file parsers.
      static CommandMap& commandMap() {
	 static CommandMap commandMap;
	 return commandMap;
      }

      // maintain a static list of unknown commands that will be common
      // to all instantiated decay file parsers
      static UnknownCommandList& unknownCommandList() {
	 static UnknownCommandList unknownCommandList;
	 return unknownCommandList;
      }

      // 
      // ---------- data members -------------------------------
      
      // the stream being parsed
      ifstream& m_fileStream;
      
      // the command that will terminate parsing
      string m_terminateParsingCommand;
      
      // the state in which this parser operates
      parseState m_parseState;
};
#endif /* MCINFO_MCDECAYFILEPARSER_H */
