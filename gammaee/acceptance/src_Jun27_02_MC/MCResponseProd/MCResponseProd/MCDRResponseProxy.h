#if !defined(MCRESPONSE_MCDRRESPONSEPROXY_H)
#define MCRESPONSE_MCDRRESPONSEPROXY_H
// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCDRResponseProxy
// 
// Description: Bindable proxy to "handle" MCDRResponse
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCDRResponseProxy.h,v 1.5 2000/07/07 02:22:21 lkg Exp $
//
// Revision history
//
// $Log: MCDRResponseProxy.h,v $
// Revision 1.5  2000/07/07 02:22:21  lkg
// Handle addition of x,y positions to MCDRResponse
//
// Revision 1.4  1999/10/27 22:59:10  jjo
// Added HitIsEff which was added to DR response object
//
// Revision 1.3  1999/10/24 20:52:39  cdj
// removed inappropriate use of typename
//
// Revision 1.2  1999/10/13 17:02:58  jjo
// Update because DR Responses now include charge deposited
//
// Revision 1.1.1.1  1999/04/16 20:07:31  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/23 14:21:20  bkh
// Flesh out MCResponse classes
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "ProxyBind/ProxyBindableTemplate.h"

#include "MCResponse/MCDRResponse.h"
#include "Experiment/fortran_types.h"

// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */

class MCResponseProd;

class MCDRResponseProxy : public ProxyBindableTemplate< FAPtrTable< MCDRResponse > >
{
      // friend classes and functions
   public:
      // constants, enums and typedefs
      typedef FAPtrTable< MCDRResponse > value_type;

      // Constructors and destructor
      // MC Response Proxy needs ptr to MCResponseProd
      MCDRResponseProxy( MCResponseProd& iProducer );
      
      virtual ~MCDRResponseProxy();

      // member functions
      void updateBeginRun( const Record& iRecord );
	 
      void addResponse( const FInteger aCellId,
			const FInteger aParticleId,
			const FReal    aDriftDist,
			const FReal    aDriftTime,
			const FReal    aSinLyrAngle,
			const FReal    aDipAngle,
			const FReal    aPathLength,
			const FInteger aAmbiguity,
			const FReal    aXPosition,
			const FReal    aYPosition,
			const FReal    aZPosition,
			const FReal    aChargeDep,
			const FReal    aEnergyLoss,
			const FLogical aHitIsEff );

      // const member functions

      // static member functions
      static MCDRResponseProxy* whoAmI();

   protected:
      // protected member functions
      virtual void invalidateCache();
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );
      // protected const member functions

   private:
      // Constructors and destructor
      MCDRResponseProxy( const MCDRResponseProxy& );
      // assignment operator(s)
      const MCDRResponseProxy& operator=(  const MCDRResponseProxy& );
      // private member functions

      // bind methods to a stream
      void bind( void (MCDRResponseProxy::*iMethod)( const Record& ),
		 const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_ptrTable;

      MCDRResponse::Identifier m_howMany ;

      // ptr to producer that calls the proxy
      MCResponseProd* m_producer;

      // static data members
      static MCDRResponseProxy* k_whoAmI ;
};

// inline function definitions

#endif /* MCRESPONSE_MCDRRESPONSEPROXY_H */
