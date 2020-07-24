#if !defined(MCRAWDATA_MCRAWRICHHITSPROXY_H)
#define MCRAWDATA_MCRAWRICHHITSPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawRichHitsProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawRichHitsProxy.h,v 1.7 2002/06/18 16:41:23 ajm36 Exp $
//
// Revision history
//
// $Log: MCRawRichHitsProxy.h,v $
// Revision 1.7  2002/06/18 16:41:23  ajm36
// add code for daq id mismapping
//
// Revision 1.6  2001/11/29 23:13:56  ts
// add parameters to control noise merging in Rich
//
// Revision 1.5  2001/04/30 17:05:29  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.4  1999/10/10 14:34:13  cdj
// removed BDLclient dirctory from include
//
// Revision 1.3  1999/07/08 06:17:09  ts
// first actual implementation of Rich digitization
//
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
#include "ProxyBind/ProxyBindableTemplate.h"
#include "RawData/RawRichHits.h"
#include "FrameAccess/FAConstants.h"
#include "DBRICHPedestals.hh"
#include "DBRICHGains.hh"
#include "CommandPattern/Parameter.h"
#include "RichGeom/RichNum_const.h"
#include "DataHandler/SyncValue.h"

#include "Experiment/fortran_types.h"

// forward declarations

#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"
#include <map>

class MCRawRichHitsProxy : public ProxyBindableTemplate< RawRichHits >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawRichHits value_type;

      typedef FAConstants<DBRICHPedestals> RICHDBPedestals;
      typedef FAConstants<DBRICHGains> RICHDBGains;

      // Constructors and destructor
      MCRawRichHitsProxy( const Parameter<DABoolean>&,
		          const Parameter<DABoolean>& ,
		          const Parameter<float>& );
      virtual ~MCRawRichHitsProxy();

      // member functions

       void updatePedestals( const Record& iRecord );
       void updateGains    ( const Record& iRecord );


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
      MCRawRichHitsProxy( const MCRawRichHitsProxy& );
      // assignment operator(s)
      const MCRawRichHitsProxy& operator=( const MCRawRichHitsProxy& );
      // private member functions

      //this function has already been written for you
      void bind( void (MCRawRichHitsProxy::*iMethod)( const Record& ),
		 const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_RawRichHits ;

      STL_VECTOR( UInt32 )& m_words ; // this proxy owns the data words!

      RICHDBPedestals m_RICHDBPedestals; 
      RICHDBGains     m_RICHDBGains;
      float m_averageDBGain;

      DABoolean iMakeMCRawRichHits;

      DABoolean m_useFakeMerge;
      FReal m_NoiseScaleFactor;

      SyncValue m_channelMapSync;
      STL_MAP(int, int) m_reverseMap;
      STL_MAP(int, int)::const_iterator m_reverseMapEnd;

      // static data members
};

// inline function definitions
#endif /* MCRAWDATA_MCRAWRICHHITSPROXY_H */
