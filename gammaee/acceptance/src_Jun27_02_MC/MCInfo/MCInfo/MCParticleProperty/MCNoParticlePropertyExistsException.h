// -*- C++ -*-
#if !defined(MCINFO_MCNOPARTICLEPROPERTYEXISTSEXCEPTION_H)
#define MCINFO_MCNOPARTICLEPROPERTYEXISTSEXCEPTION_H
//
// Package:     MCInfo
// Module:      MCNoParticlePropertyExistsException
// 
/**\class MCNoParticlePropertyExistsException MCNoParticlePropertyExistsException.h DAException/MCNoParticlePropertyExistsException.h

 Description: An exception that is thrown if a creation of an MCVertex
              is requested more than once for the same fortran-property
              vertex.  This situation is most likely a programming error.

*/
//
// Author:      Lawrence K Gibbons
// Created:     Fri Jan 18 09:10:34 EST 2002
// $Id: MCNoParticlePropertyExistsException.h,v 1.1 2002/01/20 19:34:52 lkg Exp $
//
// Revision history
//
// $Log: MCNoParticlePropertyExistsException.h,v $
// Revision 1.1  2002/01/20 19:34:52  lkg
// add an exception class
//
//

// system include files
#include <string>

// user include files
#include "DAException/DAException.h"

// forward declarations

class MCNoParticlePropertyExistsException : public DAExceptionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      MCNoParticlePropertyExistsException( int propertyId ) : 
         m_propertyId( propertyId ),
         m_message() {}
      //virtual ~MCNoParticlePropertyExistsException() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual const char* what () const { 
         if( m_message.size() == 0 ) {
            //should make m_message mutable
            string& message = 
               const_cast<MCNoParticlePropertyExistsException*>(this)->m_message;

            // convert ID numbers to character sequences
            char buffer[10];
            ostrstream oStream1( buffer, 10 );
            oStream1 << m_propertyId << ends;
            string propertyIdString( buffer );

            message = string("No property with ID ") 
                    + propertyIdString + string("exists.\n");
         }
         return m_message.c_str();
      }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //MCNoParticlePropertyExistsException( const MCNoParticlePropertyExistsException& ) ; //allow default

      // ---------- assignment operator(s) ---------------------
      //const MCNoParticlePropertyExistsException& operator=( const MCNoParticlePropertyExistsException& ); // allow default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      int m_propertyId;
      string m_message;
      
      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* MCINFO_MCNOPARTICLEPROPERTYEXISTSEXCEPTION_H */
