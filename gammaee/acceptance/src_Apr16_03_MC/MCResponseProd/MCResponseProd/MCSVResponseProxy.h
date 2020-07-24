#if !defined(MCRESPONSE_MCSVRESPONSEPROXY_H)
#define MCRESPONSE_MCSVRESPONSEPROXY_H
// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCSVResponseProxy
// 
// Description: Bindable proxy to "handle" MCSVResponse
//
// Usage:
//    <usage>
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCSVResponseProxy.h,v 1.6 2001/12/04 04:11:01 victor Exp $
//
// Revision history
//
// $Log: MCSVResponseProxy.h,v $
// Revision 1.6  2001/12/04 04:11:01  victor
// applied SVEfficiencyCorrections
//
// Revision 1.5  2001/11/19 23:31:33  victor
// changed the way efficiencies are applied
//
// Revision 1.4  2000/05/09 13:32:27  pg
// Fixed problems with Si simulation: offsets in charge deposition; Z-side charge sharing
//
// Revision 1.3  1999/11/16 20:50:50  pg
// Added Si simulation
//
// Revision 1.2  1999/10/24 20:52:40  cdj
// removed inappropriate use of typename
//
// Revision 1.1.1.1  1999/04/16 20:07:31  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/23 14:21:25  bkh
// Flesh out MCResponse classes
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "ProxyBind/ProxyBindableTemplate.h"

#include "MCResponse/MCSVResponse.h"
#include "Experiment/fortran_types.h"

#include "ASiStorePro/ASiStore.h"
#include "DBSVEfficiency.hh"
#include "DBSVEfficiencyCorrections.hh"
#include "DataHandler/Frame.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAPtrTable.h"
#include "FrameAccess/FAConstants.h"
// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */

class MCResponseProd;


class MCSVResponseProxy : public ProxyBindableTemplate< FAPtrTable< MCSVResponse > >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef FAPtrTable< MCSVResponse > value_type ;
      enum {kHybrids = ASiSensorAddress::kAdNHybrids,
            kChannels = ASiSensorAddress::kAdNchannelSensor,
            kChannelsTotal = ASiSensorAddress::kAdNchannelTotal};

      // Constructors and destructor
      // MC Response Proxy needs ptr to MCResponseProd
      MCSVResponseProxy( MCResponseProd& iProducer );
      
      virtual ~MCSVResponseProxy();

      // member functions
      void updateBeginRun( const Record& iRecord );
	 
      void addResponse( const FInteger aCellId     ,
			const FInteger aParticleId ,
			const FReal    aCharge       ) ;

      void createResponses( const Record& iRecord,
			    const ASiStore& store,
			    const FInteger waferId,
			    const FInteger trackId,
			    const FReal charge,
			    const FReal xin,
			    const FReal xout,
			    const FReal zin,
			    const FReal zout);
      
      // const member functions
      FReal clipCoord( const FReal coord, const FReal limit) const;

      void clipCharge( const FReal charge,
		       const FReal xin_orig, const FReal xout_orig,
		       const FReal zin_orig, const FReal zout_orig,
		       FReal& clipped,
		       FReal& xin, FReal& xout,
		       FReal& zin, FReal& zout) const;
      void sharePhi(const FReal qtot,
		    const FReal x1,
		    const FReal x2,
		    FReal& q1,
		    FReal& q2); 
      void shareZ(const FReal qtot,
		  const FReal x1,
		  const FReal x2,
		  FReal& qdep); 
      // static member functions

      static MCSVResponseProxy* whoAmI() ;

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );
      // protected const member functions

   private:
      // Constructors and destructor
      MCSVResponseProxy( const MCSVResponseProxy& );

      // assignment operator(s)
      const MCSVResponseProxy& operator=( const MCSVResponseProxy& );

      // private member functions

      // bind methods to a stream
      void bind( void (MCSVResponseProxy::*iMethod)( const Record& ),
		 const Stream::Type& iStream );
      
      // private const member functions

      // data members
      value_type* m_ptrTable ;

      MCSVResponse::Identifier m_howMany ;

      // ptr to producer that calls the proxy
      MCResponseProd* m_producer;
      
      // static data members
      static MCSVResponseProxy* k_whoAmI ;

      FAConstants< DBSVEfficiency > efficiencies;
      FAConstants< DBSVEfficiencyCorrections > corrections;
      
      float efficiencyZ;
      float efficiencyPhi;

      DABoolean checkConstants ;
};

// inline function definitions

#endif /* MCRESPONSE_MCSVRESPONSEPROXY_H */
