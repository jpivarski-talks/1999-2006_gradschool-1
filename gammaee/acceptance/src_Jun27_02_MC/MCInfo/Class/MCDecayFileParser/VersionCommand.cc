// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      VersionCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: VersionCommand.cc,v 1.1 1999/06/22 21:28:45 lkg Exp $
//
// Revision history
//
// $Log: VersionCommand.cc,v $
// Revision 1.1  1999/06/22 21:28:45  lkg
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
#include "MCInfo/MCDecayFileParser/VersionCommand.h"

// STL classes
#include <vector>
#include <string>
#include <strstream.h>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.VersionCommand" ;

static const string kCommandName = "VERSION";

//
// static data member definitions
//

//
// constructors and destructor
//
VersionCommand::VersionCommand() : CommandParser( kCommandName )
{
}

VersionCommand::~VersionCommand()
{
}

//
// member functions
//

void
VersionCommand::run( const CommandParser::Command& theCommand, 
		     MCParticlePropertyStore& theStore, 
		     ifstream& theStream,
		     CommandParser::ExtraInfo* xInfo ) const
{
   // attach a stream so that we can read the properties from the parameter
   // string
   int cStringLength = theCommand.parameterList.length() + 1;
   istrstream propStream( theCommand.parameterList.c_str(), cStringLength );

   // the VERSION command takes an integer argument
   Integer theVersion;
   propStream >> theVersion;

   // OK, we've parsed that line.  Let's add in the property to the store
   theStore.setVersion( theVersion );
}

