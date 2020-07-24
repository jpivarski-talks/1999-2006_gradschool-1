// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      DecayCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: DecayCommand.cc,v 1.3 2001/12/19 18:10:50 lkg Exp $
//
// Revision history
//
// $Log: DecayCommand.cc,v $
// Revision 1.3  2001/12/19 18:10:50  lkg
// get modifiable version of propert rather than copy, avoiding many, many new's
//
// Revision 1.2  1999/10/30 22:22:36  lkg
// If this particle has had decay modes defined previously, clear the decay
// mode list before starting to parse a new list of decay modes.  Needed for
// users to override the system's predefined decay modes.
//
// Revision 1.1  1999/06/22 21:28:41  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:16:41  lkg
// Initial MCDecayFileParser sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <string>
#include <map>
#include <strstream.h>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCDecayFileParser/MCDecayFileParser.h"
#include "MCInfo/MCDecayFileParser/DecayCommand.h"
#include "MCInfo/MCParticleProperty/MCDecayMode.h"

// STL classes
#include <vector>
#include <string>
#include <map>
#include <strstream.h>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.DecayCommand" ;

static const string kCommandName = "DECAY";

//
// static data member definitions
//

//
// constructors and destructor
//
DecayCommand::DecayCommand() : CommandParser( kCommandName ) {}

DecayCommand::~DecayCommand() {}

//
// member functions
//

void
DecayCommand::run( const CommandParser::Command& theCommand, 
		   MCParticlePropertyStore& theStore, 
		   ifstream& theStream,
		   CommandParser::ExtraInfo* xInfo ) const
{
   // attach a stream to theCommand's parameterList so that we can 
   //read the properties from the parameter string
   int cStringLength = theCommand.parameterList.length() + 1;
   istrstream propStream( theCommand.parameterList.c_str(), cStringLength );

   // for the Decay COMMAND, this is the list of arguments
   //     Parent_Particle_name
   // Get the arguments from the list -- first name
   string theParent;
   propStream >> theParent;

   // Grrrrrrrrr....  With cxx, the trailing Null get's appended to the
   // string.  Hopefully when the compilers all support sstream, all this
   // pain will go away.  For now, fix this with the following kluge...
   int parentLength =  theParent.length() - 1;
   if ( theParent[parentLength] == 0 ) {
      theParent = theParent.substr(0,parentLength);
   }

   // To implement the Decay command, we need a pre-existing property object
   // with that name in the store.  The get will fail if the Name is
   // unknown, so currently we do not need to check for success
   MCParticleProperty& propertyToUpdate = theStore.getModifiableUsingName(theParent);

   // If this particle already has its DECAY modes defined, clear them
   // out
   if ( propertyToUpdate.size() > 0 ) {
      report( DEBUG, kFacilityString )
	 << "Overriding decay modes for particle " << theParent << endl;
      propertyToUpdate.clearDecayModes();
   }

   // To accumulate the data from the DECAY subcommands, we need a
   // DecayModeInfo object
   DecayCommand::DecayModeInfo* infoHolder 
      = new DecayCommand::DecayModeInfo( propertyToUpdate );

   // We must create a new parser to deal with this subcommand
   MCDecayFileParser decayParser( theStream, "ENDDECAY" );

   // parse all the subcommands of this DECAY command
   decayParser.parse( theStore, infoHolder );

   // OK, we've parsed that command.  Let's 
   // cleanup our memory usage and quit
   delete infoHolder;
}

