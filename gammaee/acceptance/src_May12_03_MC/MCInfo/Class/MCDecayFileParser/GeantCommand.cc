// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      GeantCommand
// 
// Description: Parses the decay.dec Geant command
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: GeantCommand.cc,v 1.3 2003/01/16 21:07:41 cdj Exp $
//
// Revision history
//
// $Log: GeantCommand.cc,v $
// Revision 1.3  2003/01/16 21:07:41  cdj
// use stringstream if available
//
// Revision 1.2  2001/12/19 18:10:50  lkg
// get modifiable version of propert rather than copy, avoiding many, many new's
//
// Revision 1.1  1999/10/19 21:23:47  lkg
// Add the GEANT command, and a **PRELIMINARY** version of the mixing command
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
#include <vector>
#include <string>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCDecayFileParser/GeantCommand.h"

// STL classes
#include <vector>
#include <string>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.GeantCommand" ;

static const string kCommandName = "GEANT";

//
// static data member definitions
//

//
// constructors and destructor
//
GeantCommand::GeantCommand() : CommandParser( kCommandName )
{
}

GeantCommand::~GeantCommand()
{
}

//
// member functions
//

void
GeantCommand::run( const CommandParser::Command& theCommand, 
		 MCParticlePropertyStore& theStore, 
		 ifstream& theStream,
		 CommandParser::ExtraInfo* xInfo ) const
{
   // attach a stream so that we can read the properties from the parameter
   // string
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   int cStringLength = theCommand.parameterList.length() + 1;
   istrstream propStream( theCommand.parameterList.c_str(), cStringLength );
#else
   istringstream propStream( theCommand.parameterList );
#endif
   // for the Geant COMMAND, this is the list of arguments
   //     name   Geant_ID   hadronic_interactions_like_GeantID
   // Get the arguments from the list -- first name
   string theName;
   propStream >> theName;

   // now the desired Geant ID
   Geant_id geantId;
   propStream >> geantId;

   // now the Geant ID of the particle whose hadronic interactions should
   // be mimicked by this particle
   Geant_id hadronicMimickId;
   propStream >> hadronicMimickId; // WE DON'T DO ANYTHING WITH THIS YET!

   // To implement the Geant command, we need a pre-existing property object
   // with that name in the store.  The get will fail if the Name is
   // unknown, so currently we do not need to check for success
   MCParticleProperty& propertyToUpdate = theStore.getModifiableUsingName( theName );

   // set the Geant ID for the property
   propertyToUpdate.setGeantId( geantId );
}

