// -*- C++ -*-
#if !defined(MCTRIGGERPHASEPROD_MCTRIGGERPHASEPROXY_H)
#define MCTRIGGERPHASEPROD_MCTRIGGERPHASEPROXY_H
//
// Package:     <MCTriggerPhaseProd>
// Module:      MCTriggerPhaseProxy
//
/**\class MCTriggerPhaseProxy MCTriggerPhaseProxy.h MCTriggerPhaseProd/MCTriggerPhaseProxy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Wed Jan 31 16:44:20 EST 2001
// $Id: MCTriggerPhaseProxy.h,v 1.2 2001/02/07 02:49:09 lkg Exp $
//
// Revision history
//
// $Log: MCTriggerPhaseProxy.h,v $
// Revision 1.2  2001/02/07 02:49:09  lkg
// Added a parameter to allow a specification of a width for gaussian smearing
// of the trigger phase.  Defaults to 0, in which case smearing code is
// short circuited.  Conveniently cures stupid compilation problem at the
// same time.
//
// Revision 1.1.1.1  2001/02/05 16:17:26  lkg
// imported MCTriggerPhaseProd source
//
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "MCTriggerPhase/MCTriggerPhase.h"

// forward declarations
class MCTriggerPhaseProd;

class MCTriggerPhaseProxy : public ProxyBindableTemplate< MCTriggerPhase >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef MCTriggerPhase value_type;

      // Constructors and destructor
      MCTriggerPhaseProxy( const MCTriggerPhaseProd* callingProducer );
      virtual ~MCTriggerPhaseProxy();

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );

   private:
      // Constructors and destructor
      MCTriggerPhaseProxy( const MCTriggerPhaseProxy& );

      // assignment operator(s)
      const MCTriggerPhaseProxy& operator=( const MCTriggerPhaseProxy& );

      // private member functions
      int smearTriggerPhase( int unsmearedTriggerPhase );

      //this function has already been written for you
      void bind(
		void (MCTriggerPhaseProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_MCTriggerPhase ;
      const MCTriggerPhaseProd* m_callingProducer;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "MCTriggerPhaseProd/Template/MCTriggerPhaseProxy.cc"
//#endif

#endif /* MCTRIGGERPHASEPROD_MCTRIGGERPHASEPROXY_H */
