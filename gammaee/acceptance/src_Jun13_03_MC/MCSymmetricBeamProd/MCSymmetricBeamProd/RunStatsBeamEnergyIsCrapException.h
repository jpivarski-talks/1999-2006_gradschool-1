#if !defined(MCSYMMETRICBEAMPROD_RUNSTATSBEAMENERGYISCRAPEXCEPTION_H)
#define MCSYMMETRICBEAMPROD_RUNSTATSBEAMENERGYISCRAPEXCEPTION_H
// -*- C++ -*-
//
// Package:     <MCSymmetricBeamProd>
// Module:      RunStatsBeamEnergyIsCrapException
// 
/**\class RunStatsBeamEnergyIsCrapException RunStatsBeamEnergyIsCrapException.h MCSymmetricBeamProd/RunStatsBeamEnergyIsCrapException.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Wed Jan 24 21:58:56 EST 2001
// $Id: RunStatsBeamEnergyIsCrapException.h,v 1.2 2003/01/13 20:15:39 cdj Exp $
//
// Revision history
//
// $Log: RunStatsBeamEnergyIsCrapException.h,v $
// Revision 1.2  2003/01/13 20:15:39  cdj
// use stringstream if available
//
// Revision 1.1.1.1  2001/01/31 21:10:49  lkg
// imported MCSymmetricBeamProd source
//

// system include files
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

// user include files
#include "DAException/DAException.h"
#include "DataHandler/Stream.h"
#include "DataHandler/DurableDataKey.h"

// forward declarations

class RunStatsBeamEnergyIsCrapException : public DAExceptionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      RunStatsBeamEnergyIsCrapException( int runNumber ) : 
	 m_runNumber( runNumber ),
	 m_message() {}

      RunStatsBeamEnergyIsCrapException( const RunStatsBeamEnergyIsCrapException & rhs ) : 
	 m_runNumber( rhs.m_runNumber ),
	 m_message( rhs.m_message ) {}

      virtual ~RunStatsBeamEnergyIsCrapException() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual const char* what () const { 
	 if( m_message.size() == 0 ) {

	    // convert run number to a character sequence
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
	    char buffer[20];
	    ostrstream oStream( buffer, 20 );
#else 
	    ostringstream oStream;
#endif
	    oStream << m_runNumber << ends;
	    string runNumberString( oStream.str() );

	    //should make m_message mutable
	    string& message = 
	       const_cast<RunStatsBeamEnergyIsCrapException*>(this)->m_message;
	    message = 
	       string("Beam energy information from RunStatistics ")
	       + string("is crap for run ") 
	       + runNumberString;
	 }
	 return m_message.c_str();
      }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------

      // ---------- assignment operator(s) ---------------------
      const RunStatsBeamEnergyIsCrapException& operator=( const RunStatsBeamEnergyIsCrapException& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      int m_runNumber;
      string m_message;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCSymmetricBeamProd/Template/RunStatsBeamEnergyIsCrapException.cc"
//#endif

#endif /* MCSYMMETRICBEAMPROD_RUNSTATSBEAMENERGYISCRAPEXCEPTION_H */
