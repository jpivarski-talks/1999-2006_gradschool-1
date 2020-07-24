#if !defined(MCRESPONSEPROD_MCCCRESPONSEPROXY_H)
#define MCRESPONSEPROD_MCCCRESPONSEPROXY_H
// -*- C++ -*-
//
// Package:     MCResponseProd
// Module:      MCCCResponseProxy
// 
// Description: Bindable proxy to "handle" MCCCResponse
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCCCResponseProxy.h,v 1.4 2000/03/24 23:15:12 bkh Exp $
//
// Revision history
//
// $Log: MCCCResponseProxy.h,v $
// Revision 1.4  2000/03/24 23:15:12  bkh
// Modify for access to constants (gradients & geant-cellid mapping)
//
// Revision 1.3  1999/10/24 20:52:38  cdj
// removed inappropriate use of typename
//
// Revision 1.2  1999/05/14 17:16:24  bkh
// Changes to make CC Responses work
//
// Revision 1.1.1.1  1999/04/16 20:07:31  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/23 14:21:18  bkh
// Flesh out MCResponse classes
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "ProxyBind/ProxyBindableTemplate.h"

#include "MCResponse/MCCCResponse.h"
#include "Experiment/fortran_types.h"


#include "FrameAccess/FAConstants.h"
#include "FrameAccess/FATable.h"

#include "DBCCMCCrystal.hh"

#include "CcGeom/CcDGIdToCellId.h"

#include "Experiment/fortran_types.h"


// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */

class MCResponseProd;

class MCCCResponseProxy : public ProxyBindableTemplate< FAPtrTable< MCCCResponse > >
{
      // friend classes and functions
   public:
      // constants, enums and typedefs
      typedef FAPtrTable< MCCCResponse > value_type ;

      // Constructors and destructor
      // MC Response Proxy needs ptr to MCResponseProd
      MCCCResponseProxy( MCResponseProd& iProducer );
      
      virtual ~MCCCResponseProxy();

      // member functions
      void updateBeginRun( const Record& iRecord );
	 
      void addResponse( const FInteger aCellId     ,
			const FInteger aParticleId ,
			const FReal    aEnergy       ) ;

      // const member functions
      // static member functions

      static MCCCResponseProxy* whoAmI() ;

      void beginRunProcessing( Frame& aFrame ) ;

      void fillGradients(  FReal           aGrad[] ,
			   const FInteger& aNGrad   ) const ;

      void accessGeantMap(  const CcDGId& aDGId    ,
			    FInteger&     aCellId   ) const ;

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );
      // protected const member functions

   private:
      // Constructors and destructor
      MCCCResponseProxy( const MCCCResponseProxy& );
      // assignment operator(s)
      const MCCCResponseProxy& operator=( const MCCCResponseProxy& );
      // private member functions

      // bind methods to a stream
      void bind( void (MCCCResponseProxy::*iMethod)( const Record& ),
		 const Stream::Type& iStream );
      
      // private const member functions

      // data members

      value_type* m_ptrTable ;

      MCCCResponse::Identifier m_howMany ;

      // ptr to producer that calls the proxy
      MCResponseProd* m_producer;

      FAConstants< DBCCMCCrystal > m_mcCrystals ;

      FATable< CcDGIdToCellId > m_DGIdToCellIds ;

      // static data members
      static MCCCResponseProxy* k_whoAmI ;
};

// inline function definitions

#endif /* MCRESPONSEPROD_MCCCRESPONSEPROXY_H */
