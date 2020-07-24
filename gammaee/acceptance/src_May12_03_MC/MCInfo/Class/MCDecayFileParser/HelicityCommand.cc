// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      HelicityCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: HelicityCommand.cc,v 1.2 2003/01/16 21:07:42 cdj Exp $
//
// Revision history
//
// $Log: HelicityCommand.cc,v $
// Revision 1.2  2003/01/16 21:07:42  cdj
// use stringstream if available
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
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCDecayFileParser/DecayCommand.h"
#include "MCInfo/MCDecayFileParser/HelicityCommand.h"

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

static const char* const kFacilityString = "MCInfo.HelicityCommand" ;

static const string kCommandName = "HELICITY";

//
// static data member definitions
//

//
// constructors and destructor
//
HelicityCommand::HelicityCommand() : CommandParser( kCommandName )
{
}

HelicityCommand::~HelicityCommand()
{
}

//
// member functions
//

void
HelicityCommand::run( const CommandParser::Command& theCommand, 
		      MCParticlePropertyStore& theStore,
		      ifstream& theStream,
		      CommandParser::ExtraInfo* xInfo ) const
{
   // remove any trailing spaces from the string
   string::size_type noTrailingSpaceLength = 
      theCommand.parameterList.find_last_not_of(" ") + 1;
   string parameterList = 
      theCommand.parameterList.substr( 0, noTrailingSpaceLength );


   // attach a stream so that we can read the properties from the parameter
   // string
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   Integer cStringLength = parameterList.length() + 1;
   istrstream propStream( parameterList.c_str(), cStringLength );
#else
   istringstream propStream( parameterList );
#endif

   // for the Helicity COMMAND, this is the list of arguments
   //     fraction daughterHelicity1 daughterHelicity2 ...
   // Get the arguments from the list -- first the fraction
   Double thisFraction;
   propStream >> thisFraction;

   // now the desired Helicity configuration
   STL_VECTOR( Double ) thisHelicityConfig;
   Double daughterHelicity;
   while ( (propStream>>daughterHelicity) ) {
      thisHelicityConfig.push_back( daughterHelicity );
   }

   // until we know the daughter types, we cannot store the helicity
   // info.  Store the information in the extra information object
   // for a CHANNEL command to use
   DecayCommand::DecayModeInfo* dkInfo = 
      dynamic_cast<DecayCommand::DecayModeInfo*>(xInfo);
   assert( dkInfo != 0 );

   dkInfo->helicityFraction().push_back( thisFraction );
   dkInfo->helicityConfig().push_back( thisHelicityConfig );
}

