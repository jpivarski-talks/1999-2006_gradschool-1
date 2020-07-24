// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      RedefineCommand
// 
// Description: Parse the decay.dec REDEFINE command.
//
// Implementation:
//     MODIFY a pre-existing MCParticleProperty object with the 
//    decay.dec REDEFINE command.  The QQ ID is the identifier used to do
//    identify the MCParticleProperty whose basic properties will be
//    modified.  ANY PRE-EXISTING DECAY MODES ARE LEFT THE SAME for backwards
//    compatibility with the standalone QQ behaviour.
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: RedefineCommand.cc,v 1.3 2001/12/19 18:10:51 lkg Exp $
//
// Revision history
//
// $Log: RedefineCommand.cc,v $
// Revision 1.3  2001/12/19 18:10:51  lkg
// get modifiable version of propert rather than copy, avoiding many, many new's
//
// Revision 1.2  2001/11/01 21:28:51  lkg
// Issue warning when replacing an MCParticleProperty
//
// Revision 1.1  2001/10/25 18:56:52  lkg
// Added REDEFINE command to decay.dec parsing to allow user to tweak properties of a pre-existing particle
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
#include <strstream.h>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCTypes.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCInfo/MCDecayFileParser/RedefineCommand.h"

// STL classes
#include <vector>
#include <string>
#include <strstream.h>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.RedefineCommand" ;

static const string kCommandName = "REDEFINE";

//
// static data member definitions
//

//
// constructors and destructor
//
RedefineCommand::RedefineCommand() : CommandParser( kCommandName )
{
}

RedefineCommand::~RedefineCommand()
{
}

//
// member functions
//

void
RedefineCommand::run( const CommandParser::Command& theCommand, 
                      MCParticlePropertyStore& theStore, 
                      ifstream& theStream,
		      CommandParser::ExtraInfo* xInfo ) const
{
   // for the REDEFINE COMMAND, this is the list of arguments
   //           ID stable                                      min    max
   //   name   code code   mass  charge spin   c*tau    width  mass   mass
   // The first seven arguments are mandatory, the last 3 are optional,
   // but if one is given, all 3 must be given

   // remove any trailing spaces from the string
   string::size_type noTrailingSpaceLength = 
      theCommand.parameterList.find_last_not_of(" ") + 1;
   string parameterList = 
      theCommand.parameterList.substr( 0, noTrailingSpaceLength );

   // length of the parameterList, used below a couple of times
   Integer cStringLength = parameterList.length() + 1;

   // count the number of parameters passed in the list
   istrstream countStream( parameterList.c_str(), cStringLength );
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
	    << "In the following REDEFINE command parameter list, a particle"
	    << '\n'
	    << "with a width has been specified without min/max mass for "
	    << "simulation"
	    << '\n'
	    << '"' << parameterList << '"' << endl;
	 break;
      default:
         // invalid # of arguments in general
         report( ERROR, kFacilityString )
	    << "The following REDEFINE command parameter list has an "
	    << "invalid number of parameters"
	    << '\n'
	    << '"' << parameterList << '"' << endl;
	 break;
   }

   // attach a stream so that we can read the properties from the parameter
   // string
   istrstream propStream( parameterList.c_str(), cStringLength );

   string theName;
   propStream >> theName;
   
   QQ_id qqId;
   propStream >> qqId;

   // we will be MODIFYING a pre-existing MCParticleProperty object with the 
   // decay.dec REDEFINE command.  The QQ ID is the identifier used to do
   // identify the MCParticleProperty whose basic properties will be
   // modified.  ANY PRE-EXISTING DECAY MODES ARE LEFT THE SAME for backwards
   // compatibility with the standalone QQ behaviour.
   
   // Check whether a property exists that we can redefine.
   if ( ! theStore.propertyExists( qqId ) ) {
   	report( WARNING, kFacilityString )
   	   << "No MCParticleProperty with QQ ID " << qqId
   	   << " exists in the particle property store.  Ignoring the"
   	   << kCommandName << "command:\n"
   	   << kCommandName << " " << parameterList << endl;
   } else {
   	report( WARNING, kFacilityString )
   	   << "Redefining the MCParticleProperty with QQ ID " << qqId
   	   << endl;
   }
   
   // It exists, get a copy of it that we can modify
   MCParticleProperty& aProperty = theStore.getModifiableUsingQQId(qqId);
   aProperty.setName( theName );

   
   Stable_id stableId;
   propStream >> stableId;
   aProperty.setStableId( stableId );
   
   double mass;
   propStream >> mass;
   aProperty.setMass( mass );
   
   double charge;
   propStream >> charge;
   aProperty.setCharge( charge );
   
   double spin;
   propStream >> spin;
   aProperty.setSpin( spin );
   
   double ctau;
   propStream >> ctau;
   aProperty.setCtau( ctau );
   
   if ( nParam == 10 )
   {
      double width;
      propStream >> width;
      aProperty.setWidth( width );
   
      double minMass;
      propStream >> minMass;
      aProperty.setMinMass( minMass );
   
      double maxMass;
      propStream >> maxMass;
      aProperty.setMaxMass( maxMass );
   }

}

