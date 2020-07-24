#if !defined(MCRAWDATA_MCRAWCCHITSPROXY_H)
#define MCRAWDATA_MCRAWCCHITSPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawCCHitsProxy
// 
// Description: transform responses into raw data w/help of constants
//
// Usage: as a proxy
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawCCHitsProxy.h,v 1.11 2002/06/13 19:53:45 bkh Exp $
//
// Revision history
//
// $Log: MCRawCCHitsProxy.h,v $
// Revision 1.11  2002/06/13 19:53:45  bkh
// Implement use of ccmcpeeldaqmap in the calorimeter processing
// Implement parameter to turn off trigger simulation as with other detectors
//
// Revision 1.10  2001/12/18 22:33:20  bkh
// Institute CC "fake merge" flag like other detectors
// Force trigger to get CalibratedDRHits not raw data
//
// Revision 1.9  2001/09/21 16:38:24  bkh
// Fix bug in which a negative fluctuation would becine positive
// Fix sparsification for early run numbers
// Just read mc gain constants from file now instead of mucking with them
//
// Revision 1.8  2001/06/04 03:22:21  bkh
// Tune CC
//
// Revision 1.7  2001/04/30 17:05:27  mahlke
// implement parameters to turn off MCRawXXData production
//
// Revision 1.6  2000/04/04 21:17:52  bkh
// Add coherent noise
//
// Revision 1.5  1999/10/10 14:34:12  cdj
// removed BDLclient dirctory from include
//
// Revision 1.4  1999/06/15 14:56:17  bkh
// Improve CC simulation with MC gain
//
// Revision 1.3  1999/06/10 20:22:40  bkh
// Better stab at CC simulation
//
// Revision 1.2  1999/06/04 21:39:02  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:09  bkh
// fix name conflicts
//
// Revision 1.1.1.1  1999/02/25 20:29:11  bkh
// imported MCRawData sources
//
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"

#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAConstants.h"
#include "FrameAccess/FANonSeqConstants.h"

#include "DBCCMCPeelDaqMap.hh"
#include "DBCCDaqPeelMap.hh"
#include "DBCCECalChannel.hh"
#include "DBCCFBUSChannel.hh"
#include "DBCCMCCrystal.hh"
#include "DBCCCoherentNoise.hh"

#include "RawData/RawCCHits.h"
#include "MCResponse/MCCCResponse.h" 
#include "C3cc/CcGainProducts.h"
#include "CcGeom/CcNbr.h"
#include "CcGeom/CcGeometrySpec.h"

#include "CLHEP/config/CLHEP.h" // for HepDouble
#include "CommandPattern/Parameter.h"


// forward declarations

#include "STLUtility/fwd_vector.h"

class MCRawCCHitsProxy : public ProxyBindableTemplate< RawCCHits >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef RawCCHits value_type;

      // Constructors and destructor
      MCRawCCHitsProxy( const Parameter<DABoolean>& aMake ,
			const Parameter<DABoolean>& aFake  );
      virtual ~MCRawCCHitsProxy();

      // member functions

      void boundMethodECalChannel(  const Record& iRecord ) ;
      void boundMethodDaqPeelMap(   const Record& iRecord ) ;
      void boundMethodPeelDaqMap(   const Record& iRecord ) ;
      void boundMethodGainProducts( const Record& iRecord ) ;
      void boundMethodBaseGeometry( const Record& iRecord ) ;
      void boundMethodFBUSChannel(  const Record& iRecord ) ;
      void boundMethodMCCrystal(    const Record& iRecord ) ;
      void boundMethodCohNoise(     const Record& iRecord ) ;

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
      MCRawCCHitsProxy( const MCRawCCHitsProxy& );
      // assignment operator(s)
      const MCRawCCHitsProxy& operator=( const MCRawCCHitsProxy& );
      // private member functions

      void sparsify( const CcDaqIdType  aDaqId  ,
		     const CcCellIdType aCellId  ) ;// simulates sparsification

      DABoolean realEnergy( const CcDaqIdType aDaqId ) const ;

      //this function has already been written for you
      void bind( void (MCRawCCHitsProxy::*iMethod)( const Record& ),
		 const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_RawCCHits ; // ptr to object this proxy creates

      STL_VECTOR( UInt32 )                    m_words     ; // output raw data

      STL_VECTOR( MCCCResponse::EnergyType )  m_energies  ; // energies
      STL_VECTOR( CcRangeType )               m_ranges    ; // ranges
      STL_VECTOR( CcDigiType )                m_digis     ; // digitizations
      STL_VECTOR( HepDouble )                 m_gaussInc  ; // gaussian rndms
      STL_VECTOR( HepDouble )                 m_gaussCoh  ; // gaussian rndms
      STL_VECTOR( DABoolean )                 m_seedFlags ; // seed flags
      STL_VECTOR( DABoolean )                 m_keepFlags ; // kept flags
      STL_VECTOR( CcDigiType )                m_seedThr   ; // seed thresholds
      STL_VECTOR( CcDigiType )                m_nbrThr    ; // nbr  thresholds
//      STL_VECTOR( Double )                    m_smc       ; // smeared mc gains

      FAItem< CcGainProducts             >    m_gains     ; // gain products
      FAConstants< DBCCECalChannel       >    m_elec      ; // elec constants
      FAConstants< DBCCDaqPeelMap        >    m_peelIds   ; // daqId-peelId map
      FAConstants< DBCCMCPeelDaqMap      >    m_daqIds    ; // peelId-daqId map
      FAConstants< DBCCMCCrystal         >    m_mc        ; // mc gains
      FAConstants< DBCCCoherentNoise     >    m_cohNoise  ; // coh noise
      FANonSeqConstants< DBCCFBUSChannel >    m_fbus      ; // spars thresholds
      FATable< CcNbr                     >    m_neighbors ; // nbr lists
      FAItem< CcGeometrySpec             >    m_geomSpec  ; // geom spec

      DABoolean                               m_make      ;
      DABoolean                               m_fake      ;

      // static data members
};

// inline function definitions
#endif /* MCRAWDATA_MCRAWCCHITSPROXY_H */

