// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      CParityCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: CParityCommand.cc,v 1.2 2001/12/19 18:10:50 lkg Exp $
//
// Revision history
//
// $Log: CParityCommand.cc,v $
// Revision 1.2  2001/12/19 18:10:50  lkg
// get modifiable version of propert rather than copy, avoiding many, many new's
//
// Revision 1.1  1999/06/22 21:28:39  lkg
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
#include <strstream.h>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCDecayFileParser/CParityCommand.h"

// STL classes
#include <vector>
#include <string>
#include <strstream.h>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.CParityCommand" ;

static const string kCommandName = "CPARITY";

//
// static data member definitions
//

//
// constructors and destructor
//
CParityCommand::CParityCommand() : CommandParser( kCommandName )
{
}

CParityCommand::~CParityCommand()
{
}

//
// member functions
//

void
CParityCommand::run( const CommandParser::Command& theCommand, 
		     MCParticlePropertyStore& theStore, 
		     ifstream& theStream,
		     CommandParser::ExtraInfo* xInfo ) const
{
   // attach a stream so that we can read the properties from the parameter
   // string
   int cStringLength = theCommand.parameterList.length() + 1;
   istrstream propStream( theCommand.parameterList.c_str(), cStringLength );

   // for the CParity COMMAND, this is the list of arguments
   //     name   CParity
   // Get the arguments from the list -- first name
   string theName;
   propStream >> theName;

   // now the desired CParity
   Integer CParity;
   propStream >> CParity;

   // To implement the CParity command, we need a pre-existing property object
   // with that name in the store.  The get will fail if the Name is
   // unknown, so currently we do not need to check for success
   MCParticleProperty& propertyToUpdate = theStore.getModifiableUsingName( theName );

   // set the CParity ID for the property
   propertyToUpdate.setCParity( CParity );
}

