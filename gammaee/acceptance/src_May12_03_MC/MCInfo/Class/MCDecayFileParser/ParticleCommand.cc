// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      ParticleCommand
// 
// Description: Parse the decay.dec PARTICLE command
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: ParticleCommand.cc,v 1.2 2003/01/16 21:07:43 cdj Exp $
//
// Revision history
//
// $Log: ParticleCommand.cc,v $
// Revision 1.2  2003/01/16 21:07:43  cdj
// use stringstream if available
//
// Revision 1.1  1999/06/22 21:28:44  lkg
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
#include "MCInfo/MCTypes.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCDecayFileParser/ParticleCommand.h"

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

static const char* const kFacilityString = "MCInfo.ParticleCommand" ;

static const string kCommandName = "PARTICLE";

//
// static data member definitions
//

//
// constructors and destructor
//
ParticleCommand::ParticleCommand() : CommandParser( kCommandName )
{
}

ParticleCommand::~ParticleCommand()
{
}

//
// member functions
//

void
ParticleCommand::run( const CommandParser::Command& theCommand, 
                      MCParticlePropertyStore& theStore, 
                      ifstream& theStream,
		      CommandParser::ExtraInfo* xInfo ) const
{
   // we will be creating a new MCParticleProperty object with the 
   // decay.dec PARTICLE command
   MCParticleProperty aNewProperty;
   
   // for the PARTICLE COMMAND, this is the list of arguments
   //           ID stable                                      min    max
   //   name   code code   mass  charge spin   c*tau    width  mass   mass
   // The first seven arguments are mandatory, the last 3 are optional,
   // but if one is given, all 3 must be given

   // remove any trailing spaces from the string
   string::size_type noTrailingSpaceLength = 
      theCommand.parameterList.find_last_not_of(" ") + 1;
   string parameterList = 
      theCommand.parameterList.substr( 0, noTrailingSpaceLength );

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   // length of the parameterList, used below a couple of times
   Integer cStringLength = parameterList.length() + 1;
   // count the number of parameters passed in the list
   istrstream countStream( parameterList.c_str(), cStringLength );
#else
   istringstream countStream( parameterList );
#endif

   string junk;
   Integer nParam = 0;
   while ( countStream >> junk )  nParam++;

   // check that a valid number of parameters were passed
   switch ( nParam )
   {
      case  7:
      case 10:
         // valid number of arguments, proceed
         break;
      case 8:
      case 9:
         // too few arguments specified to determine width parameters
         report( ERROR, kFacilityString )
	    << "In the following PARTICLE command parameter list, a particle"
	    << '\n'
	    << "with a width has been specified without min/max mass for "
	    << "simulation"
	    << '\n'
	    << '"' << parameterList << '"' << endl;
	 break;
      default:
         // invalid # of arguments in general
         report( ERROR, kFacilityString )
	    << "The following PARTICLE command parameter list has an "
	    << "invalid number of parameters"
	    << '\n'
	    << '"' << parameterList << '"' << endl;
	 break;
   }

   // attach a stream so that we can read the properties from the parameter
   // string
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   istrstream propStream( parameterList.c_str(), cStringLength );
#else
   istringstream propStream( parameterList );
#endif

   string theName;
   propStream >> theName;
   aNewProperty.setName( theName );
   
   QQ_id qqId;
   propStream >> qqId;
   aNewProperty.setQQId( qqId );
   
   Stable_id stableId;
   propStream >> stableId;
   aNewProperty.setStableId( stableId );
   
   double mass;
   propStream >> mass;
   aNewProperty.setMass( mass );
   
   double charge;
   propStream >> charge;
   aNewProperty.setCharge( charge );
   
   double spin;
   propStream >> spin;
   aNewProperty.setSpin( spin );
   
   double ctau;
   propStream >> ctau;
   aNewProperty.setCtau( ctau );
   
   if ( nParam == 10 )
   {
      double width;
      propStream >> width;
      aNewProperty.setWidth( width );
   
      double minMass;
      propStream >> minMass;
      aNewProperty.setMinMass( minMass );
   
      double maxMass;
      propStream >> maxMass;
      aNewProperty.setMaxMass( maxMass );
   }

   // OK, we've parsed that line.  Let's add in the property to the store
   theStore.addProperty( aNewProperty );
}

