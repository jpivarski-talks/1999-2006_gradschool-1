#if !defined(MCRAWDATA_MCRAWLUMINOSITYPROXY_H)
#define MCRAWDATA_MCRAWLUMINOSITYPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawLuminosityProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Mon Apr 19 17:35:15 EST 1999
// $Id: MCRawLuminosityProxy.h,v 1.2 1999/06/04 21:39:05 bkh Exp $
//
// Revision history
//
// $Log: MCRawLuminosityProxy.h,v $
// Revision 1.2  1999/06/04 21:39:05  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/04/20 01:43:40  bkh
// update for new raw data objects
//
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "RawData/RawLuminosity.h"

// forward declarations

#include "STLUtility/fwd_vector.h"

class MCRawLuminosityProxy : public ProxyTemplate< RawLuminosity >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawLuminosity value_type;

      // Constructors and destructor
      MCRawLuminosityProxy();
      virtual ~MCRawLuminosityProxy();

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
      MCRawLuminosityProxy( const MCRawLuminosityProxy& );
      // assignment operator(s)
      const MCRawLuminosityProxy& operator=( const MCRawLuminosityProxy& );
      // private member functions
      // private const member functions

      // data members
      value_type* m_RawLuminosity ;

      STL_VECTOR( UInt32 )& m_words ; // this proxy owns the data words!

      // static data members
};

// inline function definitions
#endif /* MCRAWDATA_MCRAWLUMINOSITYPROXY_H */
