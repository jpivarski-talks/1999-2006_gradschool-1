// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      PDGCommand
// 
// Description: Parses the decay.dec PDG command
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: PDGCommand.cc,v 1.3 2003/01/16 21:07:42 cdj Exp $
//
// Revision history
//
// $Log: PDGCommand.cc,v $
// Revision 1.3  2003/01/16 21:07:42  cdj
// use stringstream if available
//
// Revision 1.2  2001/12/19 18:10:51  lkg
// get modifiable version of propert rather than copy, avoiding many, many new's
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
#include "MCInfo/MCDecayFileParser/PDGCommand.h"

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

static const char* const kFacilityString = "MCInfo.PDGCommand" ;

static const string kCommandName = "PDG";

//
// static data member definitions
//

//
// constructors and destructor
//
PDGCommand::PDGCommand() : CommandParser( kCommandName )
{
}

PDGCommand::~PDGCommand()
{
}

//
// member functions
//

void
PDGCommand::run( const CommandParser::Command& theCommand, 
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

   // for the PDG COMMAND, this is the list of arguments
   //     name   PDG ID
   // Get the arguments from the list -- first name
   string theName;
   propStream >> theName;

   // now the desired PDG ID
   PDG_id pdgId;
   propStream >> pdgId;

   // To implement the PDG command, we need a pre-existing property object
   // with that name in the store.  The get will fail if the Name is
   // unknown, so currently we do not need to check for success
   MCParticleProperty& propertyToUpdate = theStore.getModifiableUsingName( theName );

   // set the PDG ID for the property
   propertyToUpdate.setPDGId( pdgId );
}

