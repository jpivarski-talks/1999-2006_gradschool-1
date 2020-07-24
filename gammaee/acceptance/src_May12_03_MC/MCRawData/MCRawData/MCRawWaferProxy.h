#if !defined(MCRAWDATA_MCRAWWAFERPROXY_H)
#define MCRAWDATA_MCRAWWAFERPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawWaferProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawWaferProxy.h,v 1.3 2002/09/27 20:23:45 bkh Exp $
//
// Revision history
//
// $Log: MCRawWaferProxy.h,v $
// Revision 1.3  2002/09/27 20:23:45  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.2  1999/06/04 21:39:09  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:13  bkh
// fix name conflicts
//
// Revision 1.1.1.1  1999/02/25 20:29:11  bkh
// imported MCRawData sources
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "RawData/RawWafer.h"

// forward declarations

#include "STLUtility/fwd_vector.h"

class MCRawWaferProxy : public ProxyTemplate< RawWafer >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawWafer value_type;

      // Constructors and destructor
      MCRawWaferProxy();
      virtual ~MCRawWaferProxy();

      // member functions
      // const member functions
      // static member functions
   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );
      // protected const member functions
   private:
      // Constructors and destructor
      MCRawWaferProxy( const MCRawWaferProxy& );
      // assignment operator(s)
      const MCRawWaferProxy& operator=( const MCRawWaferProxy& );
      // private member functions
      // private const member functions

      // data members
      value_type* m_RawWafer ;

      STL_VECTOR( UInt32 ) m_words ; // this proxy owns the data words!

      // static data members
};

// inline function definitions
#endif /* MCRAWDATA_MCRAWWAFERPROXY_H */
