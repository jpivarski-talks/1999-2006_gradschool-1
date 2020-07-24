// -*- C++ -*-
//
// Package:     <MCInfoDelivery>
// Module:      StandardMCParticlePropProxy
// 
// Description: Creates a standard system particle property store.
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Mon Nov 23 17:55:50 EST 1998
// $Id: StandardMCParticlePropProxy.cc,v 1.4 2002/01/20 20:20:38 lkg Exp $
//
// Revision history
//
// $Log: StandardMCParticlePropProxy.cc,v $
// Revision 1.4  2002/01/20 20:20:38  lkg
// communicate the file names to MCParticlePropertyStore
//
// Revision 1.3  1999/10/20 00:50:24  lkg
// Incorporate the kluges for handling info from QQ into the proxy for
// the standard particle property list
//
// Revision 1.2  1999/07/22 14:15:55  lkg
// Activate various DEBUG statements only if CLEO_DEBUG is defined
//
// Revision 1.1.1.1  1999/07/07 01:51:22  lkg
// initial MCInfoDelivery
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <string>

// user include files
#include "Experiment/report.h"
#include "MCInfoDelivery/StandardMCParticlePropProxy.h"
#include "MCInfo/MCDecayFileParser/MCDecayFileParser.h"

// STL files
#include <map>
#include <vector>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfoDelivery.StandardMCParticlePropProxy" ;

//
// constructors and destructor
//
StandardMCParticlePropProxy::StandardMCParticlePropProxy( 
   const string& systemDecayDec )
   : m_StandardMCParticleProp( 0 ),
     m_standardDecayDecFile( *new string( systemDecayDec ) )
{
      if( 0 == &m_standardDecayDecFile )
      {
	 report( EMERGENCY, kFacilityString )
	    << "out of memory" << endl;
	 assert( false );
	 ::exit( 1 );
      }  
}

StandardMCParticlePropProxy::~StandardMCParticlePropProxy()
{
   delete m_StandardMCParticleProp ;
   delete &m_standardDecayDecFile;
}

//
// member functions
//
void
StandardMCParticlePropProxy::invalidateCache()
{
   delete m_StandardMCParticleProp ;
   m_StandardMCParticleProp = 0 ;
}

const StandardMCParticlePropProxy::value_type*
StandardMCParticlePropProxy::faultHandler( const Record& iRecord,
			      const DataKey& iKey )
{
   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_StandardMCParticleProp );

   // create a parser for the system decay.dec file
   MCDecayFileParser systemDecParser( m_standardDecayDecFile );

   // create a new property store
   m_StandardMCParticleProp = new MCParticlePropertyStore;
   if( 0 == m_StandardMCParticleProp ) {
      report( EMERGENCY, kFacilityString )
	 << "can't allocate memory; aborting" << endl;
      assert( false );
      ::exit( 1 );
   }

   // store the file name
   m_StandardMCParticleProp->setStandardDecayFile( m_standardDecayDecFile ); 

   // parse the decay.dec file, filling our property store with the contents
#if defined(CLEO_DEBUG)   
   report( DEBUG, kFacilityString ) << "Beginning decay.dec parsing" << endl;
#endif
   systemDecParser.parse( *m_StandardMCParticleProp );
#if defined(CLEO_DEBUG)   
   report( DEBUG, kFacilityString ) << "Finished  decay.dec parsing" << endl;
#endif

   // add any special-purpose particles needed for handling production
   m_StandardMCParticleProp->addSpecialParticles();

   // add any special-purpose kluges needed to deal with QQ since
   // some decays, such as PSI radiatitive decays, are handled
   // differently than decay.dec would have you think!
   m_StandardMCParticleProp->handleQQKluges();

   // done.  Return the pointer to the beast we've created
   return ( m_StandardMCParticleProp );
}


