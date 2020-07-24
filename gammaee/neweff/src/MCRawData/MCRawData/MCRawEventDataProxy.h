#if !defined(MCRAWDATA_MCRAWEVENTDATAPROXY_H)
#define MCRAWDATA_MCRAWEVENTDATAPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawEventDataProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawEventDataProxy.h,v 1.2 1999/03/11 20:16:25 bkh Exp $
//
// Revision history
//
// $Log: MCRawEventDataProxy.h,v $
// Revision 1.2  1999/03/11 20:16:25  bkh
// Update raw event proxy for new raw event features
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
#include "RawData/RawEventData.h"

// forward declarations

#include "STLUtility/fwd_vector.h"

class MCRawEventDataProxy : public ProxyTemplate< RawEventData >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawEventData value_type;

      // Constructors and destructor
      MCRawEventDataProxy();
      virtual ~MCRawEventDataProxy();

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
      MCRawEventDataProxy( const MCRawEventDataProxy& );
      // assignment operator(s)
      const MCRawEventDataProxy& operator=( const MCRawEventDataProxy& );
      // private member functions
      // private const member functions

      // data members
      value_type* m_RawEventData ;

      // static data members

};

// inline function definitions
#endif /* MCRAWDATA_MCRAWEVENTDATAPROXY_H */
