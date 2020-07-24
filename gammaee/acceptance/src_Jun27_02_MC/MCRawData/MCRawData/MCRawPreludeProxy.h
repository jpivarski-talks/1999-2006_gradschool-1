#if !defined(MCRAWDATA_MCRAWPRELUDEPROXY_H)
#define MCRAWDATA_MCRAWPRELUDEPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawPreludeProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawPreludeProxy.h,v 1.2 1999/06/04 21:39:06 bkh Exp $
//
// Revision history
//
// $Log: MCRawPreludeProxy.h,v $
// Revision 1.2  1999/06/04 21:39:06  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:12  bkh
// fix name conflicts
//
// Revision 1.1.1.1  1999/02/25 20:29:11  bkh
// imported MCRawData sources
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "RawData/RawPrelude.h"

// forward declarations

#include "STLUtility/fwd_vector.h"

class MCRawPreludeProxy : public ProxyTemplate< RawPrelude >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawPrelude value_type;

      // Constructors and destructor
      MCRawPreludeProxy();
      virtual ~MCRawPreludeProxy();

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
      MCRawPreludeProxy( const MCRawPreludeProxy& );
      // assignment operator(s)
      const MCRawPreludeProxy& operator=( const MCRawPreludeProxy& );
      // private member functions
      // private const member functions

      // data members
      value_type* m_RawPrelude ;

      STL_VECTOR( UInt32 )& m_words ; // this proxy owns the data words!

      // static data members
};

// inline function definitions
#endif /* MCRAWDATA_MCRAWPRELUDEPROXY_H */
