#if !defined(MCRAWDATA_MCRAWCATHODESPROXY_H)
#define MCRAWDATA_MCRAWCATHODESPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawCathodesProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawCathodesProxy.h,v 1.7 2002/10/01 20:30:50 bkh Exp $
//
// Revision history
//
// $Log: MCRawCathodesProxy.h,v $
// Revision 1.7  2002/10/01 20:30:50  bkh
// Cathodes: move local arrays to member data to avoid stack load
//
// Revision 1.6  2002/09/27 20:23:40  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.5  2001/12/20 17:11:29  bkh
// Install fake merge flag for Cathodes as with other detectors
// Use fake merge flag for Cathodes
// Fix SV proxy fcn to avoid compiler warning about
//      argument overriding member data
//
// Revision 1.4  2001/04/30 17:05:28  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.3  2000/06/29 21:16:27  hennessy
// added access to DRCA pedestals
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
#include "RawData/RawCathodes.h"
#include "FrameAccess/FAConstants.h"
#include "DBDRCAPedestal.hh"
#include "CommandPattern/Parameter.h"

// forward declarations

#include "STLUtility/fwd_vector.h"

class MCRawCathodesProxy : public ProxyTemplate< RawCathodes >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawCathodes value_type;

      // Constructors and destructor
      MCRawCathodesProxy( const Parameter<DABoolean>& aMake ,
			  const Parameter<DABoolean>& aFake );
      virtual ~MCRawCathodesProxy();

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
      MCRawCathodesProxy( const MCRawCathodesProxy& );
      // assignment operator(s)
      const MCRawCathodesProxy& operator=( const MCRawCathodesProxy& );
      // private member functions
      // private const member functions

      // data members
      value_type* m_RawCathodes ;

      FAConstants< DBDRCAPedestal > m_CnstDRCA;      
      STL_VECTOR( UInt32 )  m_words ; // this proxy owns the data words!

      const Parameter<DABoolean>& m_make ;
      const Parameter<DABoolean>& m_fake ;

      STL_VECTOR( float ) m_chargeTotal ;
      STL_VECTOR( float ) m_pedestal ;
      STL_VECTOR( int   ) m_thresh ;
      STL_VECTOR( float ) m_slope ;
      STL_VECTOR( float ) m_noise ;
      STL_VECTOR( float ) m_width ;
      STL_VECTOR( int   ) m_adc ;
      STL_VECTOR( int   ) m_adcOut ;
      STL_VECTOR( int   ) m_idCell ;

      // static data members

};

// inline function definitions
#endif /* MCRAWDATA_MCRAWCATHODESPROXY_H */
