// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      SimpleAngularHelicity
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Sat Mar  6 21:18:59 EST 1999
// $Id: SimpleAngularHelicity.cc,v 1.2 2001/12/19 18:12:17 lkg Exp $
//
// Revision history
//
// $Log: SimpleAngularHelicity.cc,v $
// Revision 1.2  2001/12/19 18:12:17  lkg
// eliminate use of ReferenceCountingPointers. add operator[]
//
// Revision 1.1  1999/06/22 21:28:55  lkg
// First real version of MCInfo in repository
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
//#include <task.h>
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "MCInfo/MCParticleProperty/SimpleAngularHelicity.h"

// STL classes
#include <vector>
#include <map>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCInfo.SimpleAngularHelicity" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: SimpleAngularHelicity.cc,v 1.2 2001/12/19 18:12:17 lkg Exp $";
static const char* const kTagString = "$Name: v03_09_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
SimpleAngularHelicity::SimpleAngularHelicity() :
   m_angularDistribs( *new STL_MAP( Helicity, CosThetaDep ) )
{
   // make sure we didn't run out of memory
   if ( &m_angularDistribs == 0 ) {
      report( ERROR, kFacilityString ) 
	 << "Out of memory in constructor" << endl;
   }
}

SimpleAngularHelicity::SimpleAngularHelicity(const SimpleAngularHelicity& rhs) :
   m_angularDistribs( 
      *new STL_MAP( Helicity, CosThetaDep )(rhs.m_angularDistribs) )
{
   // make sure we didn't run out of memory
   if ( &m_angularDistribs == 0 ) {
      report( ERROR, kFacilityString ) 
	 << "Out of memory in constructor" << endl;
   }
}

SimpleAngularHelicity::~SimpleAngularHelicity()
{
   delete &m_angularDistribs;
}

//
// assignment operators
//
// const SimpleAngularHelicity& SimpleAngularHelicity::operator=( const SimpleAngularHelicity& rhs )
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
SimpleAngularHelicity::addHelicityState( Helicity theHelicity,
					 const CosThetaDep& angularDepend ) {

   // issue warning if we are overwriting the dependence for a previously
   // assigned helicity
   if ( m_angularDistribs.find( theHelicity ) != m_angularDistribs.end() ) {
      report( INFO, kFacilityString )
	 << "Warning, overwriting existing Helicity parameterization."
	 << "  Helicity = " << theHelicity << endl;
   }

   m_angularDistribs[theHelicity] = angularDepend;
}

//
// const member functions
//

const SimpleAngularHelicity::CosThetaDep&
SimpleAngularHelicity::getHelicityParams( Helicity aHelicity ) const {

   // check that we have a parameterization for this helicity
   typedef STL_MAP( Helicity, CosThetaDep )::const_iterator distIter;
   distIter theParameterization( m_angularDistribs.find(aHelicity) );

   // if so, return that parameterization, if not, an empty list
   if ( theParameterization != m_angularDistribs.end() ) {
      return (*theParameterization).second;
   } else {
      return flatParameterization();
   }
}


Double
SimpleAngularHelicity::throwCosTheta( Helicity aHelicity ) const {

   // get the helicity configuration
   const CosThetaDep& theConfig = getHelicityParams( aHelicity );

   // warn that we are using throw a uniform random number uniform on (1,0)
   report( WARNING, kFacilityString )
      << "Needs the standard random number generator for proper "
      << "implementation" << "\n"
      << endl;

   // if the distribution is flat, we're done in one step
   Double cosTheta;
   if ( theConfig.size() == 1 ) {
      // throw a uniform random number between -1 and 1
      cosTheta = 2 * diceThrow() - 1;
      return cosTheta;
   } 
   // otherwise, we must throw dN/dCosTheta according to the parametrization
   else {

      // calculate the max value for dN/dCosTheta
      Double max_dNdCosTheta = 0.;
      Count paramLength = theConfig.size();
      for ( Count i=0; i < paramLength; i+=2 ) {
	 max_dNdCosTheta += (0<=theConfig[i]) ? theConfig[i] : 0;
      }
      for ( Count j=1; j < paramLength; j+=2 ) {
	 max_dNdCosTheta += abs(theConfig[j]);
      }
      
      // throw a cos theta
      Double dNdCosTheta;
      do {
	 // throw a trial cosTheta
	 cosTheta = 2 * diceThrow() - 1;
      
	 // calc. dN/dCosTheta = a0 + a1*cosTheta + a2*cosTheta^2 + ...
         // We reverse iterate over the list, ie, starting from the
	 // highest power of cosTheta
	 dNdCosTheta = 0.;
	 typedef CosThetaDep::const_reverse_iterator ctIter;
	 ctIter itDone = theConfig.rend();
	 for ( ctIter itWeight = theConfig.rbegin();
	       itWeight != itDone; ++itWeight ) {
	    dNdCosTheta += cosTheta*dNdCosTheta + *itWeight;
	 }

      } while ( (max_dNdCosTheta * diceThrow()) > dNdCosTheta );

      return cosTheta;
   }
}

DABoolean
SimpleAngularHelicity::operator==( const SimpleAngularHelicity& rhs ) const {
   return m_angularDistribs == rhs.m_angularDistribs;
}

const SimpleAngularHelicity::HelicitySpec&
SimpleAngularHelicity::operator[]( int spec ) const {

   STL_MAP( Helicity, CosThetaDep )::iterator itr;
   if ( spec < m_angularDistribs.size() ) {
      itr = m_angularDistribs.begin();
      Count count = 0;
      for ( ; count < spec; ++count, ++itr ) {}
   } else {
      report( WARNING, kFacilityString )
	 << "requested [] access beyond end of list.  Size/requested are "
	 << m_angularDistribs.size() << " / " << spec
	 << '\n' << "    Returning last element to avoid crash"
	 << endl;
      itr = m_angularDistribs.end();
      --itr;
   }

   return *itr;
}

//
// static member functions
//
const SimpleAngularHelicity::CosThetaDep&
SimpleAngularHelicity::flatParameterization() {

   static CosThetaDep flat(1,1.);
   return flat;
}

Double
SimpleAngularHelicity::diceThrow() {
//   static randint generator(987654321);

//   return generator.fdraw();
   return 0.5;
}

