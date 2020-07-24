#if !defined(MCRESPONSE_MCCATHODESRESPONSEPROXY_H)
#define MCRESPONSE_MCCATHODESRESPONSEPROXY_H
// -*- C++ -*-
//
// Package:     MCResponse
// Module:      MCCathodesResponseProxy
// 
// Description: Bindable proxy to "handle" MCCathodesResponse
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Fri Feb 19 12:09:35 EST 1999
// $Id: MCCathodesResponseProxy.h,v 1.5 2001/05/18 23:18:00 hennessy Exp $
//
// Revision history
//
// $Log: MCCathodesResponseProxy.h,v $
// Revision 1.5  2001/05/18 23:18:00  hennessy
// Problems with OSF fixed
//
// Revision 1.4  2000/03/24 01:21:36  hennessy
// Implemented cathode response proxy code
//
// Revision 1.3  1999/10/24 20:52:38  cdj
// removed inappropriate use of typename
//
// Revision 1.2  1999/10/20 22:43:14  jjo
// Remove time as cleo3 doesn't have time for cathodes
//
// Revision 1.1.1.1  1999/04/16 20:07:31  jjo
// Move MCxxResponseProxy from MCResponse library to this library.
// Make Geant calls from this library as fetching the hits (via GFHITS)
// currently couples this library to Geant.  Also, use bindable proxies. (jjo)
//
// Revision 1.1  1999/02/23 14:21:19  bkh
// Flesh out MCResponse classes
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "ProxyBind/ProxyBindableTemplate.h"

#include "MCResponse/MCCathodesResponse.h"
#include "Experiment/fortran_types.h"
#include "ADRGeom/ADRSenseWireStore.h"
#include "ADRGeomProd/ADRSenseWireProxy.h"
#include "DRMCUtil/DRCAGuru.h"
#include "MCResponse/MCDRResponse.h"
//#include "FrameAccess/FAConstants.h"
//#include "DBMCDRCASimulation.hh"
// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */

class MCResponseProd;


class MCCathodesResponseProxy : public ProxyBindableTemplate< FAPtrTable< MCCathodesResponse > >
{
      // friend classes and functions
   public:
      // constants, enums and typedefs
      typedef FAPtrTable< MCCathodesResponse > value_type ;
      typedef pair<unsigned short, unsigned short> LayerWire ;
      // Constructors and destructor
      // MC Response Proxy needs ptr to MCResponseProd
      MCCathodesResponseProxy( MCResponseProd& iProducer );
      
      virtual ~MCCathodesResponseProxy();

      // member functions

      void updateBeginRun( const Record& iRecord );
      

      // const member functions

      // static member functions

      static MCCathodesResponseProxy* whoAmI() ;

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );
      // protected const member functions

   private:
      // Constructors and destructor
      MCCathodesResponseProxy( const MCCathodesResponseProxy& );

      // assignment operator(s)
      const MCCathodesResponseProxy& operator=( const MCCathodesResponseProxy& );

      // private member functions

      // bind methods to a stream
      void bind( void (MCCathodesResponseProxy::*iMethod)( const Record& ),
		 const Stream::Type& iStream );
      
      // private const member functions

      // data members
      value_type* m_ptrTable ;

      MCCathodesResponse::Identifier m_howMany ;

      // ptr to producer that calls the proxy
      MCResponseProd* m_producer;
      
      // static data members
      static MCCathodesResponseProxy* k_whoAmI ;
};

//      FAConstants< DBMCDRCASimulation > m_SimDRCA; 
// inline function definitions

#endif /* MCRESPONSE_MCCATHODESRESPONSEPROXY_H */
