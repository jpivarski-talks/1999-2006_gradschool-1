// -*- C++ -*-
//
// Package:     <MCInfoDelivery>
// Module:      MCInfoDelivery
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Mon Dec  7 17:05:28 EST 1998
// $Id: MCInfoDelivery.cc,v 1.4 1999/07/22 14:15:54 lkg Exp $
//
// Revision history
//
// $Log: MCInfoDelivery.cc,v $
// Revision 1.4  1999/07/22 14:15:54  lkg
// Activate various DEBUG statements only if CLEO_DEBUG is defined
//
// Revision 1.3  1999/07/22 14:09:16  lkg
// format tweak in error message
//
// Revision 1.2  1999/07/07 14:40:52  lkg
// * change default system decay.dec file to $C3_LIB/data/decay/dec
// * parse environment variable preceding system/usr decay.dec file names
//
// Revision 1.1.1.1  1999/07/07 01:51:22  lkg
// initial MCInfoDelivery
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "MCInfoDelivery/MCInfoDelivery.h"
#include "MCInfoDelivery/StandardMCParticlePropProxy.h"
#include "MCInfoDelivery/UserMCParticlePropProxy.h"

#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"

// STL classes
#include <string>
#include <map>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "MCInfoDelivery.MCInfoDelivery" ;
static const string kDefaultCLEODecayDec = "$C3_LIB/data/decay.dec";

//
// static data member definitions
//

//
// constructors and destructor
//
MCInfoDelivery::MCInfoDelivery( void )               // anal1
   : Producer( "MCInfoDelivery" ),
     m_systemDecayDecFile( "standardDecayDec", this, 
			   kDefaultCLEODecayDec ),
     m_userDecayDecFile( "userDecayDec", this, "" )
{
#if defined(CLEO_DEBUG)
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;
#endif

   // set defaults for parameters
   m_systemDecayDecFile.setHelpString( 
      "Standard CLEO particle definition file" );
   m_userDecayDecFile.setHelpString( 
      "User particle definition file" );

   // ----- register proxy factories ------------------

   // Proxy Registration Step 1:
   registerProxyFactory( 
      Stream::kPhysics,
      new ProxyFactoryFunction< MCInfoDelivery, 
      StandardMCParticlePropProxy >( 
	 *this, 
	 &MCInfoDelivery::makeStandardMCParticlePropProxy ),
      UsageTag( "StandardMCParticleProperties" ) );

   registerProxyFactory( 
      Stream::kPhysics, 
      new ProxyFactoryFunction< MCInfoDelivery, 
      UserMCParticlePropProxy >( 
	 *this, 
	 &MCInfoDelivery::makeUserMCParticlePropProxy ),
      UsageTag( "UserMCParticleProperties" ) );
}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class 
ProxyFactoryFunction< MCInfoDelivery, StandardMCParticlePropProxy >;
template class 
ProxyFactoryFunction< MCInfoDelivery, UserMCParticlePropProxy >;

//
// Destructor
//
MCInfoDelivery::~MCInfoDelivery()                    // anal5
{}

//
// member functions
//

// non-trivial proxyfactory producer method used above
ProxyBase*
MCInfoDelivery::makeStandardMCParticlePropProxy() {
   // parse any environment variable that preceeds the file name
   const string& defaultFile( m_systemDecayDecFile.value() );
   string fullName( defaultFile );
   if ( defaultFile[0] == '$' ) {
      Integer firstSlash( defaultFile.find('/') );
      string envExpand( getenv( defaultFile.substr(1,--firstSlash).c_str() ) );
      Integer restLength = defaultFile.length() - ++firstSlash;
      fullName = envExpand + defaultFile.substr(firstSlash,restLength);
   }
   report( VERIFY, kFacilityString )
      << "Using file " << '\n' 
      << " ## '" << fullName << "'" << '\n' 
      << " ## " << "for standard particle properties" << endl;
   return new StandardMCParticlePropProxy( fullName );
}

// non-trivial proxyfactory producer method used above
ProxyBase*
MCInfoDelivery::makeUserMCParticlePropProxy() { 
   const string& defaultFile( m_userDecayDecFile.value() );
   string fullName( defaultFile );
   if ( fullName.length() > 0 && defaultFile[0] == '$' ) {
      Integer firstSlash( defaultFile.find('/') );
      string envExpand( getenv( defaultFile.substr(1,--firstSlash).c_str() ) );
      Integer restLength = defaultFile.length() - ++firstSlash;
      fullName = envExpand + defaultFile.substr(firstSlash,restLength);
   }
   report( VERIFY, kFacilityString )
      << "Using file " << '\n' 
      << " ## '" << fullName << "'" << '\n' 
      << " ## " << "for user's particle properties" << endl;
   return new UserMCParticlePropProxy( fullName );
}


// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
MCInfoDelivery::init( void )          // anal1 "Interactive"
{
#if defined(CLEO_DEBUG)
   report( DEBUG, kFacilityString ) << "here in init()" << endl;
#endif

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)
}

// -------------------- terminate method ----------------------------
void
MCInfoDelivery::terminate( void )     // anal5 "Interactive"
{
   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
}

// ---------------- standard place to book histograms ---------------
void
MCInfoDelivery::hist_book( TBHistoManager& )
{
   // book your histograms here
}

//
// const member functions
//

//
// static member functions
//
