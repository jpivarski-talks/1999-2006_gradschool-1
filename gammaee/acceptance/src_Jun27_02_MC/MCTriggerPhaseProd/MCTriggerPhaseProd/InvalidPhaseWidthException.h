// -*- C++ -*-
#if !defined(MCTRIGGERPHASEPROD_INVALIDPHASEWIDTHEXCEPTION_H)
#define MCTRIGGERPHASEPROD_INVALIDPHASEWIDTHEXCEPTION_H
//
// Package:     <MCTriggerPhaseProd>
// Module:      InvalidPhaseWidthException
// 
/**\class InvalidPhaseWidthException InvalidPhaseWidthException.h MCTriggerPhaseProd/InvalidPhaseWidthException.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Wed Jan 24 21:58:56 EST 2001
// $Id: InvalidPhaseWidthException.h,v 1.1 2001/02/07 02:49:08 lkg Exp $
//
// Revision history
//
// $Log: InvalidPhaseWidthException.h,v $
// Revision 1.1  2001/02/07 02:49:08  lkg
// Added a parameter to allow a specification of a width for gaussian smearing
// of the trigger phase.  Defaults to 0, in which case smearing code is
// short circuited.  Conveniently cures stupid compilation problem at the
// same time.
//
// Revision 1.2  2001/02/04 20:35:22  lkg
// move C++ emacs declaration to first line
//
// Revision 1.1.1.1  2001/01/31 21:09:31  lkg
// imported MCTriggerPhaseProd source
//

// system include files
#include <strstream.h>

// user include files
#include "DAException/DAException.h"
#include "DataHandler/Stream.h"
#include "DataHandler/DurableDataKey.h"

// forward declarations

class InvalidPhaseWidthException : public DAExceptionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      InvalidPhaseWidthException( double badWidth ) : 
	 m_badWidth( badWidth ),
	 m_message() {}

      InvalidPhaseWidthException( const InvalidPhaseWidthException & rhs ) : 
	 m_badWidth( rhs.m_badWidth ),
	 m_message( rhs.m_message ) {}

      virtual ~InvalidPhaseWidthException() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual const char* what () const { 
	 if( m_message.size() == 0 ) {

	    // convert run number to a character sequence
	    char buffer[20];
	    ostrstream oStream( buffer, 20 );
	    oStream << m_badWidth << " " << ends;
	    string badWidthString( buffer );

	    //should make m_message mutable
	    string& message = 
	       const_cast<InvalidPhaseWidthException*>(this)->m_message;
	    message = 
	       string("An invalid width of ")
	       + badWidthString
	    + string("was specified for smearing the trigger phase");
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
      const InvalidPhaseWidthException& operator=( const InvalidPhaseWidthException& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      double m_badWidth;
      string m_message;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "MCTriggerPhaseProd/Template/InvalidPhaseWidthException.cc"
//#endif

#endif /* MCTRIGGERPHASEPROD_INVALIDPHASEWIDTHEXCEPTION_H */
