// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCDecayFileParser
// 
// Description: Parser object to turn a decay.dec file into a property store
//
// Implementation:
//    The MCDecayFileParser maintains a pointer to the various
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 13:30:59 EST 1998
// $Id: MCDecayFileParser.cc,v 1.7 2003/01/12 19:22:11 cdj Exp $
//
// Revision history
//
// $Log: MCDecayFileParser.cc,v $
// Revision 1.7  2003/01/12 19:22:11  cdj
// missed some strstream changes
//
// Revision 1.6  2002/12/06 16:51:54  cleo3
// deal with strstream/stringstream
//
// Revision 1.5  2002/06/03 20:30:54  cleo3
// replaced cpp switch NO_GETLINE_WITH_STRING_BUG to NO_GETLINE_ISTREAM_STRING_BUG
//
// Revision 1.4  2001/10/25 18:56:51  lkg
// Added REDEFINE command to decay.dec parsing to allow user to tweak properties of a pre-existing particle
//
// Revision 1.3  1999/10/19 21:23:46  lkg
// Add the GEANT command, and a **PRELIMINARY** version of the mixing command
//
// Revision 1.2  1999/07/22 14:04:26  lkg
// protect against lines w/ no characters
//
// Revision 1.1  1999/06/22 21:28:42  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:16:41  lkg
// Initial MCDecayFileParser sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
//#include <list>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

#if !defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)	    
#include <sstream>
#else
#include <strstream.h>
#endif

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCDecayFileParser/MCDecayFileParser.h"
#include "MCInfo/MCDecayFileParser/AngularHelicityCommand.h"
#include "MCInfo/MCDecayFileParser/CParityCommand.h"
#include "MCInfo/MCDecayFileParser/ChannelCommand.h"
#include "MCInfo/MCDecayFileParser/DecayCommand.h"
#include "MCInfo/MCDecayFileParser/GeantCommand.h"
#include "MCInfo/MCDecayFileParser/HelicityCommand.h"
#include "MCInfo/MCDecayFileParser/MixingCommand.h"
#include "MCInfo/MCDecayFileParser/ParityCommand.h"
#include "MCInfo/MCDecayFileParser/ParticleCommand.h"
#include "MCInfo/MCDecayFileParser/RedefineCommand.h"
#include "MCInfo/MCDecayFileParser/PDGCommand.h"
#include "MCInfo/MCDecayFileParser/QQBarCommand.h"
#include "MCInfo/MCDecayFileParser/VersionCommand.h"

// STL classes
#include <map>
//#include <list>
#include <vector>
#include <algorithm>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.MCDecayFileParser";

static const char kCommentChar = ';';
static const string kEOFCommand = "EOF";

// ------------- Make the commands known here -------------
void
MCDecayFileParser::initializeCommands()
{
   // ----- add any termination commands here  -----
   // (no action taken on termination, so set function pointer to 0
   addTerminatorCommand( kEOFCommand );
   addTerminatorCommand( "ENDDECAY" );
   
   // ----- add commands with actions here  -----
   CommandParser* commandToAdd = 0;

   // add the ANGULAR_HELICITY command
   commandToAdd = new AngularHelicityCommand;
   addCommandFunction( commandToAdd );

   // add the CPARITY command
   commandToAdd = new CParityCommand;
   addCommandFunction( commandToAdd );

   // add the CHANNEL command
   commandToAdd = new ChannelCommand;
   addCommandFunction( commandToAdd );

   // add the DECAY command
   commandToAdd = new DecayCommand;
   addCommandFunction( commandToAdd );

   // add the GEANT command
   commandToAdd = new GeantCommand;
   addCommandFunction( commandToAdd );

   // add the HELICITY command
   commandToAdd = new HelicityCommand;
   addCommandFunction( commandToAdd );

   // add the Mixing command
   commandToAdd = new MixingCommand;
   addCommandFunction( commandToAdd );

   // add the PARITY command
   commandToAdd = new ParityCommand;
   addCommandFunction( commandToAdd );

   // add the PARTICLE command
   commandToAdd = new ParticleCommand;
   addCommandFunction( commandToAdd );

   // add the PARTICLE command
   commandToAdd = new RedefineCommand;
   addCommandFunction( commandToAdd );

   // add the PDG command
   commandToAdd = new PDGCommand;
   addCommandFunction( commandToAdd );

   // add the QQBAR command
   commandToAdd = new QQBarCommand;
   addCommandFunction( commandToAdd );

   // add the VERSION command
   commandToAdd = new VersionCommand;
   addCommandFunction( commandToAdd );
}


//
// constructors and destructor
//
MCDecayFileParser::MCDecayFileParser( const string& fileName ) : 
      m_fileStream( *new ifstream( fileName.c_str() ) ),
      m_terminateParsingCommand( kEOFCommand )
{
   // check that the file is ok
   if ( ! m_fileStream.good() )
   {
      report( ERROR, kFacilityString )
	    << "Problems with decay.dec file " << fileName << endl;
      assert( false );
      ::exit( 1 );
   }

   // initialize the command list
   if ( isFirstInstance() ) 
   {
      initializeCommands();
   }

   // this type of constructor puts us in the primary, modifyParticles state
   m_parseState = processCommand;
}

MCDecayFileParser::MCDecayFileParser( ifstream& decayFileStream, 
                                      const string& terminatorCommand ) : 
      m_fileStream( decayFileStream ),
      m_terminateParsingCommand( terminatorCommand )
{
   // initialize the command list if need be (shouldn't happen here!)
   if ( isFirstInstance() )
   {
      initializeCommands();
   }

   // this type of constructor puts us in the modifyDecayModes state
   m_parseState = processSubcommand;
}

MCDecayFileParser::~MCDecayFileParser()
{
   // if we are in the primary state, we should close our input stream
   if ( m_parseState == processCommand )
   {
      delete &m_fileStream;
   }
}


//
// member functions
//

void
MCDecayFileParser::parse( MCParticlePropertyStore& theStore,
			  CommandParser::ExtraInfo* subInfo )
{
   // read commands until we hit the terminator command
   
   string lastCommand = "fhuiqqqghufiew"; // initialize to unlikely garbage
   do {
      // read in the next command from the file
      CommandParser::Command nextCommand = readCommand();
      
      // see if we understand this command
      CommandMap::iterator theCommand = commandMap().find( nextCommand.name );
      if ( theCommand != commandMap().end() ) {

         // we found the command, so run it (if it is not a NULL command,
	 // like a termination command, with no action associated with it
	 if ( (*theCommand).second != 0 ) {
	    (*theCommand).second->run( nextCommand, theStore, 
				       m_fileStream, subInfo );
	 }
      } else {
         // we didn't find the command, issue warning the first time we 
         // encounter an unknown command, issue a warning and add to the 
         // list of unknown commands
	 UnknownCommandList::const_iterator inList = 
	    find( unknownCommandList().begin(),
		  unknownCommandList().end(), nextCommand.name );
	 if ( inList == unknownCommandList().end() ) {
            report( WARNING, kFacilityString )
               << "The decay.dec command " << nextCommand.name
               << " is not yet parsed outside of QQ." << endl;
	    unknownCommandList().push_back( nextCommand.name );
         }
      } // theCommand != commandMap().end()
      
      // save the name of the last command
      lastCommand = nextCommand.name;
      
   } while ( lastCommand != m_terminateParsingCommand );
}

CommandParser::Command
MCDecayFileParser::readCommand()
{
   string kBlank = " ";
   CommandParser::Command nextCommand;
   nextCommand.name = kBlank;

   // loop until we find the first non-commented line, or we hit EOF
   // If we hit a command line, signalled by an alphanumeric character as
   // the first whitespace, we create a new command from the line and stop
   while( m_fileStream.good() && nextCommand.name == kBlank )
   {
      // read the next line from the stream
#if !defined(NO_GETLINE_ISTREAM_STRING_BUG)
      string nextLine;
      getline( m_fileStream, nextLine );
#else
      // while we are stuck with the old version of getline
      char nextLineTmp[2000];
      m_fileStream.getline( nextLineTmp, 2000 );
      string nextLine( nextLineTmp );
#endif

      // Grab the first non-whitspace character from the input stream.
      char testChar( kCommentChar );
      if ( nextLine.length() > 0 ) { testChar = nextLine[0]; }
      Integer tcjnk = testChar;

      // if it's a semicolon, do nothing; ignore non-alphanumeric chars,
      // effectively reading past them.  
      if ( isalnum( testChar ) && testChar != kCommentChar ) {

	 // attach an strstream to the line we just read.  When we can
	 // use sstreams, change to using that.
	 unsigned int cStringLength = nextLine.length();
// old	 int cStringLength = nextLine.length() + 1;
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)	    
	 istrstream lineStream( nextLine.c_str(), cStringLength );
#else
	 istringstream lineStream( nextLine );
#endif
         // get the command name
         lineStream >> nextCommand.name;

         // get the parameter list, if any
#if !defined(NO_GETLINE_ISTREAM_STRING_BUG)
	 char terminator( 0 );
         getline( lineStream, nextCommand.parameterList, terminator );
#else
	 char tempCharArray[2000];
	 lineStream.get( tempCharArray, 2000 );
	 nextCommand.parameterList = tempCharArray;
#endif

	 // check for and strip leading trailing whitespace
	 // ------------ find first nonspace character position
	 string::iterator sfIter = nextCommand.parameterList.begin();
	 string::iterator sfEnd  = nextCommand.parameterList.end();
	 Integer noLeadingStart( 0 );
	 while ( sfIter != sfEnd ) {
	    if ( isspace(*sfIter) || ! isgraph(*sfIter) ) {
	       ++noLeadingStart;
	       ++sfIter;
	    } else {
	       sfIter = sfEnd;
	    }
	 }
	 // ------------ find last nonspace character position
	 //              noTrailLength has length of string to that position
	 string::reverse_iterator srIter = nextCommand.parameterList.rbegin();
	 string::reverse_iterator srEnd  = nextCommand.parameterList.rend();
	 Integer noTrailLength( nextCommand.parameterList.length() );
	 while ( srIter != srEnd ) {
	    if ( isspace(*srIter) ) {
	       --noTrailLength;
	       ++srIter;
	    } else {
	       srIter = srEnd;
	    }
	 }
	 // ------------ get the substring, sans whitespace
	 if ( noTrailLength > noLeadingStart ) {
	    noTrailLength -= noLeadingStart;
	    nextCommand.parameterList =
	       nextCommand.parameterList.substr(noLeadingStart,noTrailLength);
	 } else {
	    nextCommand.parameterList = "";
	 }

         // convert the command to upper case
         string::iterator sEnd = nextCommand.name.end();
         for ( string::iterator sIter = nextCommand.name.begin();
               sIter != sEnd;
               ++sIter ) {
            *sIter = toupper( *sIter );
         }
      } // end of testChar tests
   } // end of while, looking for next non-comment line
   
   // if we've reached here without a command, then we've reached the end of
   // the stream
   if ( nextCommand.name == kBlank )
   {
      nextCommand.name = kEOFCommand;
   }

   return nextCommand;
}

//
// private static member functions
//
// -------- member functions for managing CommandMap
DABoolean
MCDecayFileParser::isFirstInstance( void )
{
   static unsigned numberOfInstances(0);
   return ( 1 == ++numberOfInstances );
}

void 
MCDecayFileParser::addCommandFunction( CommandParser* newParseCommand )
{
   commandMap()[newParseCommand->name()] = newParseCommand;
}

void 
MCDecayFileParser::addTerminatorCommand( const string& commandName )
{
   commandMap()[commandName] = (CommandParser*)0;
}
