// -*- C++ -*-
#if !defined(MCINFO_MCNOPARTICLEEXISTSEXCEPTION_H)
#define MCINFO_MCNOPARTICLEEXISTSEXCEPTION_H
//
// Package:     MCInfo
// Module:      MCNoParticleExistsException
// 
/**\class MCNoParticleExistsException MCNoParticleExistsException.h DAException/MCNoParticleExistsException.h

 Description: An exception that is thrown if a creation of an MCVertex
              is requested more than once for the same fortran-property
              vertex.  This situation is most likely a programming error.

*/
//
// Author:      Lawrence K Gibbons
// Created:     Fri Jan 18 09:10:34 EST 2002
// $Id: MCNoParticleExistsException.h,v 1.1 2002/01/20 19:26:53 lkg Exp $
//
// Revision history
//
// $Log: MCNoParticleExistsException.h,v $
// Revision 1.1  2002/01/20 19:26:53  lkg
// add some exceptions
//
//

// system include files
#include <string>

// user include files
#include "DAException/DAException.h"

// forward declarations

class MCNoParticleExistsException : public DAExceptionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      MCNoParticleExistsException( int treeId ) : 
         m_treeId( treeId ),
         m_message() {}
      //virtual ~MCNoParticleExistsException() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual const char* what () const { 
         if( m_message.size() == 0 ) {
            //should make m_message mutable
            string& message = 
               const_cast<MCNoParticleExistsException*>(this)->m_message;

            // convert ID numbers to character sequences
            char buffer[10];
            ostrstream oStream1( buffer, 10 );
            oStream1 << m_treeId << ends;
            string treeIdString( buffer );

            message = string("Attempted to reference nonexistant particle with ID ") 
                    + treeIdString + string("\n");
         }
         return m_message.c_str();
      }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //MCNoParticleExistsException( const MCNoParticleExistsException& ) ; //allow default

      // ---------- assignment operator(s) ---------------------
      //const MCNoParticleExistsException& operator=( const MCNoParticleExistsException& ); // allow default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      int m_treeId;
      string m_message;
      
      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* MCINFO_MCNOPARTICLEEXISTSEXCEPTION_H */
