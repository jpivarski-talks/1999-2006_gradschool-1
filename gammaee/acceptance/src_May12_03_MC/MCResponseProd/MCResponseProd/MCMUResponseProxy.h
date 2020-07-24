#if !defined(MCRESPONSE_MCMURESPONSEPROXY_H)
#define MCRESPONSE_MCMURESPONSEPROXY_H
// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCMUResponseProxy
// 
// Description: Proxy to "handle" MCMUResponse
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCMUResponseProxy.h,v 1.3 2001/05/01 22:10:33 swnam Exp $
//
// Revision history
//
// $Log: MCMUResponseProxy.h,v $
// Revision 1.3  2001/05/01 22:10:33  swnam
// It is first version code to extract muon hits from Geant.
//
// Revision 1.2  1999/10/24 20:52:39  cdj
// removed inappropriate use of typename
//
// Revision 1.1.1.1  1999/04/16 20:07:31  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/23 14:21:21  bkh
// Flesh out MCResponse classes
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "ProxyBind/ProxyBindableTemplate.h"

#include "MCResponse/MCMUResponse.h"
#include "Experiment/fortran_types.h"

// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */

class MCResponseProd;

class MCMUResponseProxy : public ProxyBindableTemplate< FAPtrTable< MCMUResponse > >
{
      // friend classes and functions
   public:
      // constants, enums and typedefs
      typedef FAPtrTable< MCMUResponse > value_type ;

      // Constructors and destructor
      // MC Response Proxy needs ptr to MCResponseProd
      MCMUResponseProxy( MCResponseProd& iProducer );
      
      virtual ~MCMUResponseProxy();

      // member functions
      void updateBeginRun( const Record& iRecord );
	 
      // S. Nam : comment out old one 
      /*      void addResponse( const FInteger aCellId     ,
			const FInteger aParticleId ,
			const FInteger aCtrId      ,
			const FInteger aStripId    ,
			const FReal    aCtrAngle   ,
			const FReal    aStripAngle   ) ;
      */

      // S. Nam : for new arguments
      void addResponse( const FInteger aCellId     ,
			const FInteger aParticleId ,
			const FReal ax01    ,
			const FReal ax02    ,
			const FReal abeta1  ,
			const FReal abeta2   ) ;

      // const member functions

      // static member functions

      static MCMUResponseProxy* whoAmI() ;

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );
      // protected const member functions

   private:
      // Constructors and destructor
      MCMUResponseProxy( const MCMUResponseProxy& );

      // assignment operator(s)
      const MCMUResponseProxy& operator=(  const MCMUResponseProxy& );

      // private member functions

      // bind methods to a stream
      void bind( void (MCMUResponseProxy::*iMethod)( const Record& ),
		 const Stream::Type& iStream );
      

      // private const member functions

      // data members
      value_type* m_ptrTable ;

      MCMUResponse::Identifier m_howMany ;

      // ptr to producer that calls the proxy
      MCResponseProd* m_producer;
      
      // static data members
      static MCMUResponseProxy* k_whoAmI ;
};

// inline function definitions

#endif /* MCRESPONSE_MCMURESPONSEPROXY_H */
