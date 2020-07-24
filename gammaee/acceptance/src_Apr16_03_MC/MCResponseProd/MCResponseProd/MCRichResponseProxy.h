#if !defined(MCRESPONSE_MCRICHRESPONSEPROXY_H)
#define MCRESPONSE_MCRICHRESPONSEPROXY_H
// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCRichResponseProxy
// 
// Description: Bindable proxy to "handle" MCRichResponse
//
// Usage:
//    <usage>
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCRichResponseProxy.h,v 1.3 1999/10/24 20:52:40 cdj Exp $
//
// Revision history
//
// $Log: MCRichResponseProxy.h,v $
// Revision 1.3  1999/10/24 20:52:40  cdj
// removed inappropriate use of typename
//
// Revision 1.2  1999/07/08 06:09:19  ts
// first actual implementation of Rich Response
//
// Revision 1.1.1.1  1999/04/16 20:07:31  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/23 14:21:24  bkh
// Flesh out MCResponse classes
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "ProxyBind/ProxyBindableTemplate.h"

#include "MCResponse/MCRichResponse.h"
#include "Experiment/fortran_types.h"

// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */

class MCResponseProd;

class MCRichResponseProxy : public ProxyBindableTemplate< FAPtrTable< MCRichResponse > >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef FAPtrTable< MCRichResponse > value_type ;

      // Constructors and destructor
      // MC Response Proxy needs ptr to MCResponseProd
      MCRichResponseProxy( MCResponseProd& iProducer );
      
      virtual ~MCRichResponseProxy();

      // member functions
      void updateBeginRun( const Record& iRecord );

      void addResponse( const FInteger aCellId     ,
			const FInteger aParticleId ,
                        const FReal    aX,
                        const FReal    aY,
                        const FReal    aZ,
                        const FReal    aPhotonEnergy,
                        const FInteger aOrigin,
                        const FInteger aNumberOfSurfacesPassed,
                        const FReal    aMass,
                        const FReal    aMomentum);

      // const member functions
      // static member functions

      static MCRichResponseProxy* whoAmI() ;

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );
      // protected const member functions

   private:
      // Constructors and destructor
      MCRichResponseProxy( const MCRichResponseProxy& );

      // assignment operator(s)
      const MCRichResponseProxy& operator=( const MCRichResponseProxy& );

      // private member functions

      // bind methods to a stream
      void bind( void (MCRichResponseProxy::*iMethod)( const Record& ),
		 const Stream::Type& iStream );
      
      // private const member functions

      // data members
      value_type* m_ptrTable ;

      MCRichResponse::Identifier m_howMany ;

      // ptr to producer that calls the proxy
      MCResponseProd* m_producer;
      
      // static data members
      static MCRichResponseProxy* k_whoAmI ;
};

// inline function definitions

#endif /* MCRESPONSE_MCRICHRESPONSEPROXY_H */
