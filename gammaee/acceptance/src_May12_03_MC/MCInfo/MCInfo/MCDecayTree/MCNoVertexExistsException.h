// -*- C++ -*-
#if !defined(MCINFO_MCNOVERTEXEXISTSEXCEPTION_H)
#define MCINFO_MCNOVERTEXEXISTSEXCEPTION_H
//
// Package:     MCInfo
// Module:      MCNoVertexExistsException
// 
/**\class MCNoVertexExistsException MCNoVertexExistsException.h DAException/MCNoVertexExistsException.h

 Description: An exception that is thrown if a creation of an MCVertex
              is requested more than once for the same fortran-property
              vertex.  This situation is most likely a programming error.

*/
//
// Author:      Lawrence K Gibbons
// Created:     Fri Jan 18 09:10:34 EST 2002
// $Id: MCNoVertexExistsException.h,v 1.2 2002/12/06 16:51:54 cleo3 Exp $
//
// Revision history
//
// $Log: MCNoVertexExistsException.h,v $
// Revision 1.2  2002/12/06 16:51:54  cleo3
// deal with strstream/stringstream
//
// Revision 1.1  2002/01/20 19:26:54  lkg
// add some exceptions
//
//

// system include files
#include <string>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)	    
#include <strstream.h>
#else
#include <sstream>
#endif

// user include files
#include "DAException/DAException.h"

// forward declarations

class MCNoVertexExistsException : public DAExceptionBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      MCNoVertexExistsException( int treeId ) : 
         m_treeId( treeId ),
         m_message() {}
      //virtual ~MCNoVertexExistsException() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual const char* what () const { 
         if( m_message.size() == 0 ) {
            //should make m_message mutable
            string& message = 
               const_cast<MCNoVertexExistsException*>(this)->m_message;

            // convert ID numbers to character sequences
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)	    
            char buffer[10];
            ostrstream oStream1( buffer, 10 );
            oStream1 << m_treeId << ends;
            string treeIdString( buffer );
#else
	    stringstream oStream1;
	    oStream1 << m_treeId <<endl;
	    string treeIdString( oStream1.str() );
#endif

            message = string("Attempted to reference nonexistant vertex with ID ") 
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
      //MCNoVertexExistsException( const MCNoVertexExistsException& ) ; //allow default

      // ---------- assignment operator(s) ---------------------
      //const MCNoVertexExistsException& operator=( const MCNoVertexExistsException& ); // allow default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      int m_treeId;
      string m_message;
      
      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* MCINFO_MCNOVERTEXEXISTSEXCEPTION_H */
