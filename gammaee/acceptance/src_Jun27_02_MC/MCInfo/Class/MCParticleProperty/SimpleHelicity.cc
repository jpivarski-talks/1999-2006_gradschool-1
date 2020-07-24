// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      SimpleHelicity
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar  6 18:05:17 EST 1999
// $Id: SimpleHelicity.cc,v 1.4 2001/12/19 18:12:17 lkg Exp $
//
// Revision history
//
// $Log: SimpleHelicity.cc,v $
// Revision 1.4  2001/12/19 18:12:17  lkg
// eliminate use of ReferenceCountingPointers. add operator[]
//
// Revision 1.3  1999/07/22 20:54:42  lkg
// Add a 3rd "special value" for helicity, since in .rp files the other 2
// special values get pegged at -63.5
//
// Revision 1.2  1999/07/07 00:12:54  lkg
// Improve some error messages
//
// Revision 1.1  1999/06/22 21:28:55  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <iomanip.h>
#include <assert.h>
#include <stdlib.h>  // for ::exit

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCParticleProperty/SimpleHelicity.h"

// STL classes
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

//
// constants, enums and typedefs
//
const Helicity SimpleHelicity::kUndefinedHelicity( -999. );
const Helicity SimpleHelicity::kTrueHelicity( -100. );
const Helicity SimpleHelicity::kRoarUndefinedHelicity( -63.5 );

static const char* const kFacilityString = "MCInfo.SimpleHelicity" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SimpleHelicity.cc,v 1.4 2001/12/19 18:12:17 lkg Exp $";
static const char* const kTagString = "$Name: v03_02_02 $";

//
// static data member definitions
//

//
// constructors and destructor
//
// the only constructor creates an empty list
SimpleHelicity::SimpleHelicity() :
   m_probabilitySum( 0 ),
   m_configurationList( *new STL_VECTOR( HelicityConfig )(0) ),
   m_configurationMap(  *new STL_MAP( Likelihood, ChildHelicities* ) ),
   m_numDaughtersExpected( 0 )
{
   if( 0 == &m_configurationList || 0 == &m_configurationMap ) {
      report( EMERGENCY, kFacilityString )
	 << "out of memory" << endl;  
      assert( false );  
      ::exit( 1 );  
   }  
}

SimpleHelicity::SimpleHelicity( const SimpleHelicity& rhs ) :
   m_probabilitySum( 0 ),
   m_configurationList( *new STL_VECTOR( HelicityConfig )(0) ),
   m_configurationMap(  *new STL_MAP( Likelihood, ChildHelicities* ) ),
   m_numDaughtersExpected( rhs.m_numDaughtersExpected )
{
   if( 0 == &m_configurationList || 0 == &m_configurationMap ) {
      report( EMERGENCY, kFacilityString )
	 << "out of memory" << endl;  
      assert( false );  
      ::exit( 1 );  
   }  

   // iterate over rhs, adding its information to this list so that
   // this object owns all of the helicities
   typedef STL_VECTOR( HelicityConfig )::const_iterator hcIter;
   hcIter done = rhs.m_configurationList.end();
   for ( hcIter rhsConfig = rhs.m_configurationList.begin(); 
	 rhsConfig != done; ++rhsConfig ) {
      addHelicityConfig( rhsConfig->configProbability, 
			 rhsConfig->helicities );
   }
}

SimpleHelicity::~SimpleHelicity()
{

   // rid ourselves of the containers
   delete &m_configurationList;
   delete &m_configurationMap;
}

//
// assignment operators
//
// const SimpleHelicity& SimpleHelicity::operator=( const SimpleHelicity& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
void
SimpleHelicity::addHelicityConfig( 
   Likelihood theProb, 
   const SimpleHelicity::ChildHelicities& theConfig )
{
   // make sure that the probability is valid
   if ( theProb <= 0. || theProb > 1. ) {
      report( NOTICE, kFacilityString )
	 << "probability " << theProb
	 << " => " << "configuration will be IGNORED" << endl;
      return;
   }

   // make sure that the number of daughters implied is consistent w/
   // previous configurations, if any
   if ( m_numDaughtersExpected == 0 ) {
      m_numDaughtersExpected = theConfig.size();
   } else if ( theConfig.size() != m_numDaughtersExpected ) {
      report( ERROR, kFacilityString )
	 << "Adding a new daughter helicity configuration" << '\n'
	 << " ## Expected a " << m_numDaughtersExpected 
	 << " daughter configuration, " << '\n'
	 << " ## Received a " << theConfig.size() << " daugher configuration"
	 << endl;
      assert( false );
      ::exit(1);
   }
   
   // update the sum of probabilities for the normalization
   m_probabilitySum += theProb;

   // add the new configuration to the list
   HelicityConfig tmpConfig(theProb,theConfig);
   m_configurationList.push_back(tmpConfig);


   //
   // remake the map.  
   //
   // Since the keys are the integrated, normalized probability, all 
   // the keys will change.  Therefore we must clear the map and 
   // start afresh
   m_configurationMap.clear();

   // now actually build our map from the information stored in the list
   typedef STL_VECTOR( HelicityConfig )::iterator hcIter;
   Likelihood runningProb( 0 );
   hcIter done = m_configurationList.end();
   for( hcIter itConf = m_configurationList.begin();
	itConf != done; ++itConf ) {

      // get the normalized running probability, which acts as a key into
      // the map
      runningProb += itConf->configProbability;
      Double integratedProb = runningProb / m_probabilitySum;

      // add this key/config to the map
      m_configurationMap[integratedProb] = &(itConf->helicities);
   }
}
  
//
// const member functions
//
const SimpleHelicity::ChildHelicities&
SimpleHelicity::throwConfig() const
{
   report( WARNING, kFacilityString )
      << "Needs a random number generator for proper implementation" << "\n"
      << "Returning list that would correspond to a random number = 0.5"
      << endl;

   // get a random number -- right now it's not so random!
   Likelihood diceThrow( 0.5 );

   // look for the first occurence in the map of a key that's
   // >= our random number.  To do this, we need to stick the random
   // number into the pair<> used by map for the comparison
   typedef pair<const Likelihood,ChildHelicities*> LCPair;
   LCPair dicePair( diceThrow, static_cast<ChildHelicities*>(0) );
   typedef STL_MAP( Likelihood, 
		    SimpleHelicity::ChildHelicities* )::iterator mapItr;
   mapItr theConfig = find_if( m_configurationMap.begin(),
			       m_configurationMap.end(),
			       bind2nd(greater_equal<LCPair>(), dicePair) );

   return *((*theConfig).second);
}

DABoolean 
SimpleHelicity::operator==( const SimpleHelicity& rhs ) const {
   return m_configurationList == rhs.m_configurationList;
}

int
SimpleHelicity::numberOfConfigs() const {
  return m_configurationList.size();
}

const SimpleHelicity::HelicityConfig& 
SimpleHelicity::operator[]( int configIndex ) const {
  return m_configurationList[configIndex];
}

//
// friend functions
//

// default output operator for the particle property object
ostream& operator<<(ostream& s, const SimpleHelicity& aMode ) {

   // if we're empty just return
   if ( aMode.m_configurationList.empty() ) { 
      return s;
   }

   // Output the helicity configuration
//   typedef STL_VECTOR( HelicityConfig )::const_iterator 
   typedef STL_VECTOR( SimpleHelicity::HelicityConfig )::const_iterator 
      configIter;
   configIter done = aMode.m_configurationList.end();
   for ( configIter itConfig = aMode.m_configurationList.begin();
	 itConfig != done; ++itConfig ) {

      // dump the probability and configuration information
      s << '\n' << " ## "
	<< "Helicity config: fraction = " << setw(6) << setprecision(4) 
	<< itConfig->configProbability << "; "
	<< itConfig->helicities;

   } // itConfig loop

   return s;
}

ostream& 
operator<<( ostream& s, const SimpleHelicity::ChildHelicities& aConfig ) {

   typedef SimpleHelicity::ChildHelicities::const_iterator helIter;

   // dump the list of helicities
   helIter helDone = aConfig.end();
   for ( helIter itHel = aConfig.begin(); itHel != helDone; ++itHel ) {
      s << (*itHel).first << ": " << (*itHel).second << "  ";
   }

   return s;
}

//
// static member functions
//
