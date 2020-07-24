// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      AngularHelicityCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: AngularHelicityCommand.cc,v 1.2 2003/01/16 21:07:40 cdj Exp $
//
// Revision history
//
// $Log: AngularHelicityCommand.cc,v $
// Revision 1.2  2003/01/16 21:07:40  cdj
// use stringstream if available
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
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include<sstream>
#endif
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCDecayFileParser/DecayCommand.h"
#include "MCInfo/MCDecayFileParser/AngularHelicityCommand.h"

// STL classes
#include <vector>
#include <string>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include<sstream>
#endif


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.AngularHelicityCommand" ;

static const string kCommandName = "ANGULAR_HELICITY";

//
// static data member definitions
//

//
// constructors and destructor
//
AngularHelicityCommand::AngularHelicityCommand() : 
   CommandParser( kCommandName ) {}

AngularHelicityCommand::~AngularHelicityCommand() {}

//
// member functions
//

void
AngularHelicityCommand::run( const CommandParser::Command& theCommand, 
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

   // for the AngularHelicity COMMAND, this is the list of arguments
   //     helicity a0 a1 a2 ...
   // where for the given helicity, we want to have cos_theta distributed as
   // dN/dcos_theta = a0 + a1*cos_theta + a2*cos_theta^2 + ...
   // Get the arguments from the list -- first the helicity
   Double thisHelicity;
   propStream >> thisHelicity;

   // now the desired AngularHelicity configuration
   STL_VECTOR( Double ) angularConfig;
   Double cosCoefficient;
   while ( propStream >> cosCoefficient ) {
      angularConfig.push_back( cosCoefficient );
   }

   // store this information up for use in the next CHANNEL command
   DecayCommand::DecayModeInfo* dkInfo = 
      dynamic_cast<DecayCommand::DecayModeInfo*>(xInfo);
   assert( dkInfo != 0 );

   dkInfo->angularHelList().push_back( thisHelicity );
   dkInfo->angularHelParam().push_back( angularConfig );
}

