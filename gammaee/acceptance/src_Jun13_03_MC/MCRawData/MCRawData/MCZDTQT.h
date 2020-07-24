#if !defined(MC_MCZDTQT_H)
#define MC_MCZDTQT_H
// -*- C++ -*-
//
// Package:     <MC>
// Module:      MCZDTQT
// 
/**\class MCZDTQT MCZDTQT.h MCRawData/MCZDTQT.h

 Description: This object simulates a ZD TQT card.

 Usage:
     MCZDResponse objects are collected by cell Id (wire) because
     there may be more than one MCZD per cell Id (wire).
     This object may be used to give the ingredients for making
     ZD TQT RawData objects (multihit tdc times and charges 
     as per Karl Ecklund and Dan Peterson). 

*/
//
// Author:      Guangshun Huang
// Created:     Thu Jan 23 2003
// $Id: MCZDTQT.h,v 1.1 2003/02/04 15:22:18 huanggs Exp $
//
// Revision history
//
// $Log: MCZDTQT.h,v $
// Revision 1.1  2003/02/04 15:22:18  huanggs
// first submission
//
//

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif /* MULTISET_IS_SEPARATE_FILE_BUG */ 
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// system include files
#include "Experiment/types.h"
#include "Experiment/Experiment.h"
#include "Experiment/report.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
#if defined(MULTISET_IS_SEPARATE_FILE_BUG)
#include <multiset.h>
#else
#include <set>
#endif /* MULTISET_IS_SEPARATE_FILE_BUG */ 
//#include <algorithm>
//#include <utility>

// user include files
#include "MCResponse/MCZDResponse.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_multiset.h"


// forward declarations


class TimeChargePair
{

  public:

    // C'tor
    TimeChargePair(Real time, Real charge);
  
    // Default C'tor
    TimeChargePair();

    // D'tor
    virtual ~TimeChargePair(); 

    // Copy Constructor
    TimeChargePair(const TimeChargePair& aTimeChargePair);
  
    // Assignment
    void operator=(const TimeChargePair& rhs);

    // Less than operator (for sorting)
    DABoolean operator<(const TimeChargePair& rhs) const;

    // Accessors
    inline Real time() const;
    inline Real charge() const;

  private:
  
    // Private member data
    Real m_time;
    Real m_charge;

};
  


class MCZDTQT
{
      // ---------- friend classes and functions ---------------
      friend ostream& operator<<(ostream& aStream, 
				 const MCZDTQT& aResponse);

   public:
      // ---------- constants, enums and typedefs --------------
      typedef Count Identifier;

      const static float kTQTDeadTime;
      const static float kTQTMaxTime;
      const static float kTQTMinTime;

      // More constants dealing with TQT's response to noise
      // should go here

      // ---------- Constructors and destructor ----------------
      
      // Main constructor
      MCZDTQT(const MCZDResponse& aResponse);

      // D'tor
      virtual ~MCZDTQT();

      // ---------- member functions ---------------------------

      // Add a response "hit" to this cell (wire) that the 
      // TQT must handle (this object worries about time gates,
      // etc. so you don't have to).
      //
      //  Hits coming BEFORE the main event should have
      // negative drift times (hits with times > kTQTMaxTime
      // will be lost).
      void addResponse(const MCZDResponse& aResponse);

      // ---------- const member functions ---------------------
      inline Count identifier() const;

      // Return the cell id (WARNING: The cellId -> daqId map
      // is NOT APPILED! So you get the actual cellId; NOT THE
      // DAQ ID.)
      inline Count cellId() const;

      // Return a vector of drift times as if coming from a TQT
      // card. This means the first time is the earliest and 
      // subsequent times are present only if they occur later
      // than the TQT dead time. Times past the TQT Max Time
      // are not present. Times are in PICOSECONDS!
      STL_VECTOR(Real) driftTimesFromTQT() const;
  
   
      // Return the total charge collected on this wire. Only
      // charge collected within time TQT Max Time are summed.
      Real collectedChargeFromTQT() const;

      // Print out contents of this TQT in a nice way
      void dump(ostream& out) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      MCZDTQT(const MCZDTQT& aTQT); // stop

      // ---------- assignment operator(s) ---------------------
      const MCZDTQT& operator=( const MCZDTQT& ); // stop 

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      Real chargeIntegrator(Real time, Real chargeDeposited) const;

      // ---------- data members -------------------------------

      // FATable identifier (is really the cell ID)
      Count  m_id;
  
      // Set of drift times
      STL_MULTISET(TimeChargePair) m_timeAndCharges;

      // ---------- static data members ------------------------

};

// inline function definitions
inline Count MCZDTQT::identifier() const 
{
  return m_id;
}

inline Count MCZDTQT::cellId() const 
{
  return m_id;
}


inline Real TimeChargePair::time() const { return m_time; }

inline Real TimeChargePair::charge() const { return m_charge; }


// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCRawData/Template/MCZDTQT.cc"
//#endif

#endif /* MC_MCZDTQT_H */
