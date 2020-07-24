// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      ChannelCommand
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: ChannelCommand.cc,v 1.2 2003/01/16 21:07:41 cdj Exp $
//
// Revision history
//
// $Log: ChannelCommand.cc,v $
// Revision 1.2  2003/01/16 21:07:41  cdj
// use stringstream if available
//
// Revision 1.1  1999/06/22 21:28:40  lkg
// First real version of MCInfo in repository
//
// Revision 1.1.1.1  1998/11/21 23:16:41  lkg
// Initial MCDecayFileParser sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
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
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/SimpleHelicity.h"
#include "MCInfo/MCParticleProperty/SimpleAngularHelicity.h"
#include "MCInfo/MCParticleProperty/MCDecayMode.h"
#include "MCInfo/MCDecayFileParser/DecayCommand.h"
#include "MCInfo/MCDecayFileParser/ChannelCommand.h"

// STL classes
#include <vector>
#include <map>
#include <string>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.ChannelCommand" ;

static const string kCommandName = "CHANNEL";

//
// static data member definitions
//

//
// constructors and destructor
//
ChannelCommand::ChannelCommand() : CommandParser( kCommandName ) {}

ChannelCommand::~ChannelCommand() {}

//
// member functions
//

void
ChannelCommand::run( const CommandParser::Command& theCommand, 
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

   // for the Channel COMMAND, this is the list of arguments
   //     model_number branching_fraction daughter1 daughter1 ...
   // Get the arguments from the list -- first the model
   Integer decayModel;
   propStream >> decayModel;

   // next the branching fraction
   Double thisFraction;
   propStream >> thisFraction;

   // not all of the models have an explicit daughter list.  Unfortunately,
   // at least on solaris, continued reading still produces one daughter
   // with a null name.  For now, read a single character from the stream.
   // If there are real daughters, this character must be white space and
   // we will have no problem.  If there are no more characters, the
   // stream state should change to ! propStream.good().  Of course, make
   // sure that the compiler writer will let the next read occur...
   if ( propStream.good() ) {
      char c;
      propStream.get( c );
   }

   // finally, the list of daughters
   STL_VECTOR( string ) daughters;
   if ( propStream.good() ) {
      string aDaughter;
      while ( propStream >> aDaughter ) {
	 daughters.push_back( aDaughter );
      }
   }

   // Grrrrrrrrr....  With cxx, a trailing Null sometimes gets appended to the
   // string.  Hopefully when the compilers all support sstream, all this
   // pain will go away.  For now, fix this with the following kluge...
   STL_VECTOR( string )::reverse_iterator lastDaughter = daughters.rbegin();
   if ( lastDaughter != daughters.rend() ) {
      int dLength =  (*lastDaughter).length() - 1;
      if ( (*lastDaughter)[dLength] == 0 ) {
	 (*lastDaughter) = (*lastDaughter).substr(0,dLength);
      }
   }

   // store this information into the particleProperty passed in via
   // the xInfo object, synthesizing the information from any
   // preceding helicity or angular_helicity commands

   // get access to the decay information collected
   DecayCommand::DecayModeInfo* dkInfo = 
      dynamic_cast<DecayCommand::DecayModeInfo*>(xInfo);
   assert( dkInfo != 0 );

   // lets build up this decay mode
   MCDecayMode tempMode( dkInfo->parentProp() );
   tempMode.setChildrenTypes( daughters );
   tempMode.setBranchingFraction( thisFraction );
   tempMode.setModel( decayModel );

   //
   // if there is angular helicity information for this decay
   // mode, save it
   //
   if ( ! dkInfo->angularHelList().empty() ) {

      assert( dkInfo->angularHelList().size() == 
	      dkInfo->angularHelParam().size() );

      SimpleAngularHelicity angularDists;
      while( ! dkInfo->angularHelList().empty() ) {
	 // add the information first pushed onto our deque's
	 angularDists.addHelicityState( dkInfo->angularHelList().front(),
					dkInfo->angularHelParam().front() );
	 // get rid of the information we've used from our storage
	 dkInfo->angularHelList().pop_front();
	 dkInfo->angularHelParam().pop_front();
      }

      // now add this information to the decay mode
      tempMode.setAngularDistribs( angularDists );
   }

   //
   // if there is daughter helicity information for this decay
   // mode, save it
   //
   if ( ! dkInfo->helicityFraction().empty() ) {

      assert( dkInfo->helicityFraction().size() == 
	      dkInfo->helicityConfig().size() );

      // A temporary helicity configuration object
      SimpleHelicity configs;

      // loop until we've used up all of the helicity configurations
      while( ! dkInfo->helicityFraction().empty() ) {
	 //
	 // correlate the daughter names with the daughter helicities
	 //
	 SimpleHelicity::ChildHelicities aConfig;

	 // get the helicity information first pushed onto our deque
	 STL_VECTOR( Double )& theseHelicities =
	    dkInfo->helicityConfig().front();

	 // check that the number of daughters and the number of daughter
	 // helicities in this configuration are the same
	 if ( daughters.size() != theseHelicities.size() ) {
	    report( ERROR, kFacilityString )
	       << "Inconsistency between helicities specified = " 
	       << theseHelicities.size() << '\n' << " ## "
	       << "and number of daughters " << daughters.size()
	       << " for the decay " << '\n' << " ## "
	       << tempMode << endl;
	    assert( false );
	    ::exit( 1 );
	 }

	 // build the correlated daughter/helicity map
	 STL_VECTOR( string ) tmpDaughters( daughters );
	 while ( ! tmpDaughters.empty() ) {
	    aConfig[tmpDaughters.back()] = theseHelicities.back();
	    tmpDaughters.pop_back();
	    theseHelicities.pop_back();
	 }

	 // add this configuration to the Helicity object
	 configs.addHelicityConfig( dkInfo->helicityFraction().front(),
				    aConfig );

	 dkInfo->helicityFraction().pop_front();
	 dkInfo->helicityConfig().pop_front();
      }
      
      //update the decay mode with this helicity information
      tempMode.setHelicityConfigs( configs );
   }


   // all of the decay mode properties are now established.
   // Tell the ParticleProperty pointed to by the extra information
   // to add this mode to its list
   dkInfo->parentProp().addDecayMode( tempMode );

   // We are all done with this channel!  At this point, all of the
   // DEQUE's in dkInfo should be cleared out.  ASSERT this
   // requirement
   assert( dkInfo->helicityFraction().empty() );
   assert( dkInfo->helicityConfig().empty() );
   assert( dkInfo->angularHelList().empty() );
   assert( dkInfo->angularHelParam().empty() );

}

