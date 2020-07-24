#if !defined(MCRAWDATA_MCRAWLEVEL3TRIGGERPROXY_H)
#define MCRAWDATA_MCRAWLEVEL3TRIGGERPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawLevel3TriggerProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawLevel3TriggerProxy.h,v 1.2 1999/06/04 21:39:04 bkh Exp $
//
// Revision history
//
// $Log: MCRawLevel3TriggerProxy.h,v $
// Revision 1.2  1999/06/04 21:39:04  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/04/20 01:43:39  bkh
// update for new raw data objects
//
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "RawData/RawLevel3Trigger.h"

// forward declarations

#include "STLUtility/fwd_vector.h"

class MCRawLevel3TriggerProxy : public ProxyTemplate< RawLevel3Trigger >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawLevel3Trigger value_type;

      // Constructors and destructor
      MCRawLevel3TriggerProxy();
      virtual ~MCRawLevel3TriggerProxy();

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
      MCRawLevel3TriggerProxy( const MCRawLevel3TriggerProxy& );
      // assignment operator(s)
      const MCRawLevel3TriggerProxy& operator=( const MCRawLevel3TriggerProxy& );
      // private member functions
      // private const member functions

      // data members
      value_type* m_RawLevel3Trigger ;

      STL_VECTOR( UInt32 )& m_words ; // this proxy owns the data words!

      // static data members
};

// inline function definitions
#endif /* MCRAWDATA_MCRAWLEVEL3TRIGGERPROXY_H */
