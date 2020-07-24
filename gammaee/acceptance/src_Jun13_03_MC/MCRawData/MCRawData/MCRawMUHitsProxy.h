#if !defined(MCRAWDATA_MCRAWMUHITSPROXY_H)
#define MCRAWDATA_MCRAWMUHITSPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawMUHitsProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawMUHitsProxy.h,v 1.4 2002/09/27 20:23:42 bkh Exp $
//
// Revision history
//
// $Log: MCRawMUHitsProxy.h,v $
// Revision 1.4  2002/09/27 20:23:42  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.3  2001/04/30 17:05:29  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.2  1999/06/04 21:39:05  bkh
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
#include "RawData/RawMUHits.h"
#include "CommandPattern/Parameter.h"

// forward declarations

#include "STLUtility/fwd_vector.h"

class MCRawMUHitsProxy : public ProxyTemplate< RawMUHits >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawMUHits value_type;

      // Constructors and destructor
      MCRawMUHitsProxy( const Parameter<DABoolean>& );
      virtual ~MCRawMUHitsProxy();

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
      MCRawMUHitsProxy( const MCRawMUHitsProxy& );
      // assignment operator(s)
      const MCRawMUHitsProxy& operator=( const MCRawMUHitsProxy& );
      // private member functions
      // private const member functions

      // data members
      value_type* m_RawMUHits ;

      STL_VECTOR( UInt32 ) m_words ; // this proxy owns the data words!

      const Parameter<DABoolean>& m_makeMCRawMUHits;

      // static data members

};

// inline function definitions
#endif /* MCRAWDATA_MCRAWMUHITSPROXY_H */
