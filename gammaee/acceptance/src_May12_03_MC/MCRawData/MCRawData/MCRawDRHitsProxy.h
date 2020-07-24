#if !defined(MCRAWDATA_MCRAWDRHITSPROXY_H)
#define MCRAWDATA_MCRAWDRHITSPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawDRHitsProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawDRHitsProxy.h,v 1.4 2002/09/27 20:23:41 bkh Exp $
//
// Revision history
//
// $Log: MCRawDRHitsProxy.h,v $
// Revision 1.4  2002/09/27 20:23:41  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.3  2001/04/30 17:05:28  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.2  1999/06/04 21:39:03  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:10  bkh
// fix name conflicts
//
// Revision 1.1.1.1  1999/02/25 20:29:11  bkh
// imported MCRawData sources
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "RawData/RawDRHits.h"
#include "CommandPattern/Parameter.h"

// forward declarations

#include "STLUtility/fwd_vector.h"

class MCRawDRHitsProxy : public ProxyTemplate< RawDRHits >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawDRHits value_type;

      // Constructors and destructor
      MCRawDRHitsProxy( const Parameter<DABoolean>& );
      virtual ~MCRawDRHitsProxy();

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
      MCRawDRHitsProxy( const MCRawDRHitsProxy& );
      // assignment operator(s)
      const MCRawDRHitsProxy& operator=( const MCRawDRHitsProxy& );
      // private member functions
      // private const member functions

      // data members
      value_type* m_RawDRHits ;

      STL_VECTOR( UInt32 ) m_words ; // this proxy owns the data words!

      const Parameter<DABoolean>& m_makeMCRawDRHits;

      // static data members

};

// inline function definitions
#endif /* MCRAWDATA_MCRAWDRHITSPROXY_H */
