// -*- C++ -*-
//
// Package:     <MCInfoDelivery>
// Module:      UserMCParticlePropProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Mon Nov 23 17:55:36 EST 1998
// $Id: UserMCParticlePropProxy.cc,v 1.4 2002/01/20 20:20:38 lkg Exp $
//
// Revision history
//
// $Log: UserMCParticlePropProxy.cc,v $
// Revision 1.4  2002/01/20 20:20:38  lkg
// communicate the file names to MCParticlePropertyStore
//
// Revision 1.3  2000/01/26 23:08:17  lkg
// add DEBUG report statement to flag beginning of user decay.dec parsing
//
// Revision 1.2  1999/07/22 14:16:48  lkg
// Add the usage tag for extracting the standard particle property store
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

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FAItem.h"

#include "MCInfoDelivery/UserMCParticlePropProxy.h"
#include "MCInfo/MCDecayFileParser/MCDecayFileParser.h"

// STL files
#include <map>
#include <vector>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfoDelivery.UserMCParticlePropProxy" ;

//
// constructors and destructor
//
UserMCParticlePropProxy::UserMCParticlePropProxy( const string& userDecayDec )
   : m_UserMCParticleProp( 0 ),
     m_userDecayDecFile( *new string( userDecayDec ) )
{
      if( 0 == &m_userDecayDecFile )
      {
	 report( EMERGENCY, kFacilityString )
	    << "out of memory" << endl;
	 assert( false );
	 ::exit( 1 );
      }  
}

UserMCParticlePropProxy::~UserMCParticlePropProxy()
{
   delete m_UserMCParticleProp ;
   delete &m_userDecayDecFile;
}

//
// member functions
//
void
UserMCParticlePropProxy::invalidateCache()
{
   delete m_UserMCParticleProp ;
   m_UserMCParticleProp = 0 ;
}

const UserMCParticlePropProxy::value_type*
UserMCParticlePropProxy::faultHandler( const Record& iRecord,
			      const DataKey& iKey )
{
   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_UserMCParticleProp );

   // ---------- create the new object --------------------

   // Get the standard list of particle properties from the frame
   FAItem< MCParticlePropertyStore > standardPropertyStore; 
   extract( iRecord, standardPropertyStore, "StandardMCParticleProperties" ); 

   if( !standardPropertyStore.valid() ) {
      report( WARNING, kFacilityString ) 
         << "Could not extract the standard Particle Property store" << endl;
      return ( 0 ) ;
   }

   // create the user Store based on a copy of the standard store
   m_UserMCParticleProp =
      new MCParticlePropertyStore( *standardPropertyStore );
   if( 0 == m_UserMCParticleProp )
   {
      report( EMERGENCY, kFacilityString )
	 << "can't allocate memory; aborting" << endl;
      assert( false );
      ::exit( 1 );
   }

   // We only need to modify the copy we've made if the user has specified
   // a non-null file name.
   if ( m_userDecayDecFile != "" ) 
   {
   // store the file name
      m_UserMCParticleProp->setUserDecayFile( m_userDecayDecFile ); 

      report( DEBUG, kFacilityString )
	 << "Parsing user dec" << endl;

      // Create a decay file parser for the user-specified decay file.
      MCDecayFileParser userDecParser( m_userDecayDecFile );

      // parse the file, modifying the user store
      userDecParser.parse( *m_UserMCParticleProp );
   }

   // Done.  Return the pointer to our user store
   return ( m_UserMCParticleProp ) ;
}


