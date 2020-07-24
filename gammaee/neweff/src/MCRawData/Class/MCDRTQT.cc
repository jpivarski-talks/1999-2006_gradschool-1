// -*- C++ -*-
//
// Package:     <MCRawData>
// Module:      MCDRTQT
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Adam Lyon
// Created:     Wed Oct 20 14:17:58 EDT 1999
// $Id: MCDRTQT.cc,v 1.1 1999/11/02 23:59:36 lyon Exp $
//
// Revision history
//
// $Log: MCDRTQT.cc,v $
// Revision 1.1  1999/11/02 23:59:36  lyon
// Moved from MCResponse
//
// Revision 1.1  1999/10/26 22:10:04  lyon
// Simulates a DR TQT board
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <map>
//#include <algorithm>
//#include <utility>
#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif /* MULTISET_IS_SEPARATE_FILE_BUG */ 
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "MCRawData/MCDRTQT.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <map>
//#include <algorithm>
//#include <utility>
#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif /* MULTISET_IS_SEPARATE_FILE_BUG */

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "MCRawData.MCDRTQT" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: MCDRTQT.cc,v 1.1 1999/11/02 23:59:36 lyon Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//
const float MCDRTQT::kTQTDeadTime = 400000.0;    // 400 ns (in ps)
const float MCDRTQT::kTQTMaxTime =  2500000.0;
const float MCDRTQT::kTQTMinTime = kTQTMaxTime - 32000000.0; 

//
// constructors and destructor
//
MCDRTQT::MCDRTQT(const MCDRResponse& aResponse) :
  m_id( aResponse.cellId() )
{
  addResponse(aResponse);
}

  
// MCDRTQT::MCDRTQT( const MCDRTQT& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

MCDRTQT::~MCDRTQT()
{}

//
// assignment operators
//
// const MCDRTQT& MCDRTQT::operator=( const MCDRTQT& rhs )
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
void MCDRTQT::addResponse(const MCDRResponse& aResponse)
{

  // Make a time and charge pair
  TimeChargePair timeChargePair(aResponse.driftTime(), 
				aResponse.chargeDep());

  
  // Put it into the set
  m_timeAndCharges.insert(timeChargePair);

}

//
// const member functions
//

STL_VECTOR(Real) MCDRTQT::driftTimesFromTQT() const
{
  STL_VECTOR(Real) tqtTimes;

  // If there are no times, return an empty vector
  if ( m_timeAndCharges.size() == 0 ) return tqtTimes;    

  STL_MULTISET(TimeChargePair)::const_iterator iter = m_timeAndCharges.begin();

  // Keep track of the early time
  Real earlyTime = (*iter).time();
  
  // Add this one to the return vector
  tqtTimes.push_back((*iter).time());

  // Current dead time (is the full dead time for the first hit)
  Real currentDeadTime = kTQTDeadTime;

  // Go to the next one
  ++iter;

    
  for ( ; iter != m_timeAndCharges.end() ; ++iter  )
  {

    Real time = (*iter).time();
    
    // Is this time within the dead time of the TQT?
    if ( (time - earlyTime) > currentDeadTime )
    {
      // This next hit comes outside of the dead time - so ok to add
      tqtTimes.push_back(time);
      earlyTime = time;

      // Calculate the dead time due to this hit (as per Karl Ecklund)
      // This affects the next hit (if there is one).
      currentDeadTime = time - earlyTime - kTQTDeadTime;
    }
  }
     
  return tqtTimes;
}


Real MCDRTQT::collectedChargeFromTQT() const
{
  Real totalCharge = 0.0;

  // If there are no times, return an empty vector
  if ( m_timeAndCharges.size() == 0 ) return totalCharge;

  STL_MULTISET(TimeChargePair)::const_iterator iter = m_timeAndCharges.begin();

  for ( ; iter != m_timeAndCharges.end() ; ++iter  )
  {
    totalCharge = totalCharge + chargeIntegrator((*iter).time(), 
						 (*iter).charge());
  }

  return totalCharge;
}

Real MCDRTQT::chargeIntegrator(Real time, Real chargeDeposited) const
{
 
  Real charge;

  if ( time > 0.0 ) 
  {
    // Apply a slope
    charge = chargeDeposited*(1-time*1.0/MCDRTQT::kTQTMaxTime);
  }
  else
  {
    // This is a hit from a previous bucket (or noise). The treatment 
    // here is very naive.
    charge = chargeDeposited*(1-time*(1.0/40000000.0));
  }
	
  return charge;
}  

void MCDRTQT::dump(ostream& out) const
{
  out << "MC TQT Simulation: CellID = " << cellId() << endl;
  out << "   Time,Charge observed within window " << kTQTMinTime 
      << " ps < time < " << kTQTMaxTime << " ps:" << endl;

  
  STL_MULTISET(TimeChargePair)::const_iterator iter = m_timeAndCharges.begin();

  for ( ; iter != m_timeAndCharges.end() ; ++iter  )
  {
    out << "       " << (*iter).time() << " ps, " 
	<< (*iter).charge() << " units of charge" << endl;
  }

  out << "   Simulated output stream from this TQT: " << endl;
  out << "   (TQT dead time is " << kTQTDeadTime << " ps)" << endl;

  STL_VECTOR(Real) timeout = driftTimesFromTQT();
  for ( unsigned int i = 0; i < timeout.size(); ++i )
  {
    out << "     " << timeout[i] << " ps" << endl;
  }
  
  Real totalCharge = collectedChargeFromTQT();

  out << "      " << totalCharge << " units of charge " << endl;

  out << '\n' << endl;
}
					     
//
// static member functions
//


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// Implementation of TimeChargePair


// C'tor
TimeChargePair::TimeChargePair(Real time, Real charge) :
  m_time(time),
  m_charge(charge)
{}

// Default C'tor
TimeChargePair::TimeChargePair() :
  m_time(0.0),
  m_charge(0.0)
{}

// Destructor
TimeChargePair::~TimeChargePair()
{}

// Copy constructor
TimeChargePair::TimeChargePair(const TimeChargePair& aTimeChargePair) :
  m_time(aTimeChargePair.time()),
  m_charge(aTimeChargePair.charge())
{}

// Assignment
void TimeChargePair::operator=(const TimeChargePair& rhs)
{
  m_time = rhs.time();
  m_charge = rhs.charge();
}


// Less than operator (for sorting)
DABoolean TimeChargePair::operator<(const TimeChargePair& rhs) const
{
  return ( m_time < rhs.time() );
}


//
// friend member functions
//
ostream& operator<<( ostream& s, const MCDRTQT& aResponse ) {

   aResponse.dump( s );
   return s;
}
