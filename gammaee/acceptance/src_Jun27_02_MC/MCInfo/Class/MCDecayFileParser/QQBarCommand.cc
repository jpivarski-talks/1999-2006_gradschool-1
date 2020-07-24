// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      QQBarCommand
// 
// Description: Parse the decay.dec QQBAR command
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Thu Nov  5 16:50:22 EST 1998
// $Id: QQBarCommand.cc,v 1.1 1999/06/22 21:28:44 lkg Exp $
//
// Revision history
//
// $Log: QQBarCommand.cc,v $
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
#include "MCInfo/MCParticleProperty/MCQQBar.h"
#include "MCInfo/MCDecayFileParser/QQBarCommand.h"

// STL classes
#include <vector>
#include <string>
#include <strstream.h>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.QQBarCommand" ;

static const string kCommandName = "QQBAR";

//
// static data member definitions
//

//
// constructors and destructor
//
QQBarCommand::QQBarCommand() : CommandParser( kCommandName ) {}

QQBarCommand::~QQBarCommand() {}

//
// member functions
//

void
QQBarCommand::run( const CommandParser::Command& theCommand, 
                      MCParticlePropertyStore& theStore, 
                      ifstream& theStream,
		      CommandParser::ExtraInfo* xInfo ) const
{
   // we will be creating a new MCQQBar object with the 
   // decay.dec PARTICLE command
   MCQQBar newQQ;
   
   // for the QQBAR COMMAND, this is the list of arguments
   //          
   //   name  QQBAR-ID-code
   // attach a stream so that we can read the properties from the parameter
   // string
   int cStringLength = theCommand.parameterList.length() + 1;
   istrstream propStream( theCommand.parameterList.c_str(), cStringLength );

   string theName;
   propStream >> theName;
   newQQ.setName( theName );
   
   Count qqBarId;
   propStream >> qqBarId;
   newQQ.setQQBarId( qqBarId );
   
   // get the quark/antiquark content of this QQBar pair, from which
   // we will derive several particle properties
   MCQQBar::quarkNumber     quark = MCQQBar::nameToNumber( theName[1] );
   MCQQBar::quarkNumber antiquark = MCQQBar::nameToNumber( theName[2] );
   
   // really, this is a minimum mass
   Double mass = MCQQBar::calculateMinMass( quark, antiquark );
   newQQ.setMass( mass );
   
   Double charge = MCQQBar::calculateCharge( quark, antiquark );
   newQQ.setCharge( charge );

   PDG_id pdg = MCQQBar::calculatePDGId( quark, antiquark );
   newQQ.setPDGId( pdg );

   // OK, we've parsed that command.  Let's add the property to the store
   theStore.addProperty( newQQ );
}


//
// static functions
//
