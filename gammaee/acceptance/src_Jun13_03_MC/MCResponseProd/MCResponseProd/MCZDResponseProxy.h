#if !defined(MCRESPONSE_MCZDRESPONSEPROXY_H)
#define MCRESPONSE_MCZDRESPONSEPROXY_H
// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCZDResponseProxy
// 
// Description: Bindable proxy to "handle" MCZDResponse
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCZDResponseProxy.h,v 1.1 2002/09/27 20:28:10 bkh Exp $
//
// Revision history
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "ProxyBind/ProxyBindableTemplate.h"

#include "MCResponse/MCZDResponse.h"
#include "Experiment/fortran_types.h"

// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */

class MCResponseProd;

class MCZDResponseProxy : public ProxyBindableTemplate< FAPtrTable< MCZDResponse > >
{
      // friend classes and functions
   public:
      // constants, enums and typedefs
      typedef FAPtrTable< MCZDResponse > value_type;

      // Constructors and destructor
      // MC Response Proxy needs ptr to MCResponseProd
      MCZDResponseProxy( MCResponseProd& iProducer );
      
      virtual ~MCZDResponseProxy();

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
      static MCZDResponseProxy* whoAmI();

   protected:
      // protected member functions
      virtual void invalidateCache();
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );
      // protected const member functions

   private:
      // Constructors and destructor
      MCZDResponseProxy( const MCZDResponseProxy& );
      // assignment operator(s)
      const MCZDResponseProxy& operator=(  const MCZDResponseProxy& );
      // private member functions

      // bind methods to a stream
      void bind( void (MCZDResponseProxy::*iMethod)( const Record& ),
		 const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_ptrTable;

      MCZDResponse::Identifier m_howMany ;

      // ptr to producer that calls the proxy
      MCResponseProd* m_producer;

      // static data members
      static MCZDResponseProxy* k_whoAmI ;
};

// inline function definitions

#endif /* MCRESPONSE_MCZDRESPONSEPROXY_H */
