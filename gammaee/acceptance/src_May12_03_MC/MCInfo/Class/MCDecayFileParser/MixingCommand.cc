// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MixingCommand
// 
// Description: Parses the decay.dec Mixing command
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: MixingCommand.cc,v 1.3 2003/01/16 21:07:42 cdj Exp $
//
// Revision history
//
// $Log: MixingCommand.cc,v $
// Revision 1.3  2003/01/16 21:07:42  cdj
// use stringstream if available
//
// Revision 1.2  2001/12/19 18:10:50  lkg
// get modifiable version of propert rather than copy, avoiding many, many new's
//
// Revision 1.1  1999/10/19 21:23:48  lkg
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
#include "MCInfo/MCDecayFileParser/MixingCommand.h"

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

static const char* const kFacilityString = "MCInfo.MixingCommand" ;

static const string kCommandName = "MIXING";

//
// static data member definitions
//

//
// constructors and destructor
//
MixingCommand::MixingCommand() : CommandParser( kCommandName )
{
}

MixingCommand::~MixingCommand()
{
}

//
// member functions
//

void
MixingCommand::run( const CommandParser::Command& theCommand, 
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
   // for the Mixing COMMAND, this is the list of arguments
   //     name1   name2  x  y
   // Get the arguments from the list -- first, the names of the particles
   // that mix
   string mixName1;
   propStream >> mixName1;

   string mixName2;
   propStream >> mixName2;

   // now the mixing parameters -- *** NOT YET IMPLEMENTED ***

   // To implement the Mixing command, we need pre-existing property objects
   // with that name in the store.  The get will fail if the Name is
   // unknown, so currently we do not need to check for success
   MCParticleProperty& prop1ToUpdate = theStore.getModifiableUsingName( mixName1 );
   MCParticleProperty& prop2ToUpdate = theStore.getModifiableUsingName( mixName2 );

   // Make sure that these are neutral charge conjugates!
   if ((prop1ToUpdate.charge() != 0)  || 
       (theStore.conjugateQQ(prop1ToUpdate.QQId()) != prop2ToUpdate.QQId())) {
      report( CRITICAL, kFacilityString )
	 << "invalid request to mix two nonconjugate or charged particles"
	 << '\n' << "QQ Id's are " 
	 << prop1ToUpdate.QQId() 
	 << prop2ToUpdate.QQId()
	 << endl;
   }

   // set mixable to true for the particles
   prop1ToUpdate.setMixable( true );
   prop2ToUpdate.setMixable( true );
}
