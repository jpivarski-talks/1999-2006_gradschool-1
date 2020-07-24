#if !defined(MCRAWDATA_MCRAWZDHITSPROXY_H)
#define MCRAWDATA_MCRAWZDHITSPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawZDHitsProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawZDHitsProxy.h,v 1.1 2002/09/27 20:23:45 bkh Exp $
//
// Revision history
//
//

// system include files

#include <vector>

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "RawData/RawZDHits.h"
#include "CommandPattern/Parameter.h"

// forward declarations
#include "STLUtility/fwd_vector.h"

class MCRawZDHitsProxy : public ProxyTemplate< RawZDHits >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawZDHits value_type;

      // Constructors and destructor
      MCRawZDHitsProxy( const Parameter<DABoolean>& );
      virtual ~MCRawZDHitsProxy();

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
      MCRawZDHitsProxy( const MCRawZDHitsProxy& );
      // assignment operator(s)
      const MCRawZDHitsProxy& operator=( const MCRawZDHitsProxy& );
      // private member functions
      // private const member functions

      // data members
      value_type* m_RawZDHits ;

      STL_VECTOR( UInt32 )  m_words ; // this proxy owns the data words!

      const Parameter<DABoolean>& m_makeMCRawZDHits;

      // static data members

};

// inline function definitions
#endif /* MCRAWDATA_MCRAWZDHITSPROXY_H */
