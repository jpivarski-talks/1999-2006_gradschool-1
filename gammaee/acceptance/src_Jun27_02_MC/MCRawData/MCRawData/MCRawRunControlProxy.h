#if !defined(MCRAWDATA_MCRAWRUNCONTROLPROXY_H)
#define MCRAWDATA_MCRAWRUNCONTROLPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawRunControlProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Mon Apr 19 17:35:15 EST 1999
// $Id: MCRawRunControlProxy.h,v 1.2 1999/06/04 21:39:07 bkh Exp $
//
// Revision history
//
// $Log: MCRawRunControlProxy.h,v $
// Revision 1.2  1999/06/04 21:39:07  bkh
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
#include "RawData/RawRunControl.h"

// forward declarations

#include "STLUtility/fwd_vector.h"

class MCRawRunControlProxy : public ProxyTemplate< RawRunControl >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawRunControl value_type;

      // Constructors and destructor
      MCRawRunControlProxy();
      virtual ~MCRawRunControlProxy();

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
      MCRawRunControlProxy( const MCRawRunControlProxy& );
      // assignment operator(s)
      const MCRawRunControlProxy& operator=( const MCRawRunControlProxy& );
      // private member functions
      // private const member functions

      // data members
      value_type* m_RawRunControl ;

      STL_VECTOR( UInt32 )& m_words ; // this proxy owns the data words!

      // static data members
};

// inline function definitions
#endif /* MCRAWDATA_MCRAWRUNCONTROLPROXY_H */
