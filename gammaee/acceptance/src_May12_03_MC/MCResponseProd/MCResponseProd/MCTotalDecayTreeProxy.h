#if !defined(MCRESPONSEPROD_MCTOTALDECAYTREEPROXY_H)
#define MCRESPONSEPROD_MCTOTALDECAYTREEPROXY_H
// -*- C++ -*-
//
// Package:     <MCResponseProd>
// Module:      MCTotalDecayTreeProxy
//
/*
 
 Description: Proxy that delivers an MCDecayTree (as an FAItem< MCDecayTree >)
              that has been modified to include all particles created
              during the GEANT tracing

 Usage:

*/
//
// Author:      Lawrence Gibbons
// Created:     Wed Oct 27 15:58:22 EDT 1999
// $Id: MCTotalDecayTreeProxy.h,v 1.2 2000/04/19 17:28:04 lkg Exp $
//
// Revision history
//
// $Log: MCTotalDecayTreeProxy.h,v $
// Revision 1.2  2000/04/19 17:28:04  lkg
// No longer explicitly holds the decay tree pointer explicity.  Communicates
// with MCResponseProd for access/deletion of the tree.  Avoids memory
// leak that occurred when a tree was created by MCResponseProd, but no one
// extracted a tree from the frame, so the MCTotalDecayTreeProxy's pointer
// was never set. Hence, the tree was never deleted.
//
// Revision 1.1  2000/01/26 23:43:06  lkg
// A proxy that conforms to the behaviour of the MCResponse-type proxies
// that trigger GEANT.  It supplies the geant-modified decay tree that
// gets formed in MCResponseProd::triggerGeantEvent.
//
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "MCInfo/MCDecayTree/MCDecayTree.h"

// forward declarations
class MCResponseProd;

class MCTotalDecayTreeProxy : public ProxyBindableTemplate< MCDecayTree >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef MCDecayTree value_type;

      // Constructors and destructor
      // MC Response Proxy needs ptr to MCResponseProd
      MCTotalDecayTreeProxy( MCResponseProd& iProducer );

      virtual ~MCTotalDecayTreeProxy();

      // member functions
      void updateBeginRun( const Record& iRecord );

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
      MCTotalDecayTreeProxy( const MCTotalDecayTreeProxy& );

      // assignment operator(s)
      const MCTotalDecayTreeProxy& operator=( const MCTotalDecayTreeProxy& );

      // private member functions

      //this function has already been written for you
      void bind( void (MCTotalDecayTreeProxy::*iMethod)( const Record& ),
		 const Stream::Type& iStream );

      // private const member functions

      // ptr to producer that calls the proxy
      MCResponseProd* m_producer;

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "MCResponseProd/Template/MCTotalDecayTreeProxy.cc"
//#endif

#endif /* MCRESPONSEPROD_MCTOTALDECAYTREEPROXY_H */
