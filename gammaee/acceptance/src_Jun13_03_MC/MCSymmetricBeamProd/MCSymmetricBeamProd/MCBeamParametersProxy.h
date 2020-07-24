// -*- C++ -*-
#if !defined(MCSYMMETRICBEAMPROD_MCBEAMPARAMETERSPROXY_H)
#define MCSYMMETRICBEAMPROD_MCBEAMPARAMETERSPROXY_H
//
// Package:     <MCSymmetricBeamProd>
// Module:      MCBeamParametersProxy
//
/**\class MCBeamParametersProxy MCBeamParametersProxy.h MCSymmetricBeamProd/MCBeamParametersProxy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Lawrence Gibbons
// Created:     Thu Jan 11 16:07:36 EST 2001
// $Id: MCBeamParametersProxy.h,v 1.1.1.1 2001/01/31 21:10:49 lkg Exp $
//
// Revision history
//
// $Log: MCBeamParametersProxy.h,v $
// Revision 1.1.1.1  2001/01/31 21:10:49  lkg
// imported MCSymmetricBeamProd source
//
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "MCBeam/MCBeamParameters.h"

// forward declarations
class MCSymmetricBeamProd;

class MCBeamParametersProxy : public ProxyBindableTemplate< MCBeamParameters >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef MCBeamParameters value_type;

      // Constructors and destructor
      MCBeamParametersProxy( const MCSymmetricBeamProd* beamProducer );
      virtual ~MCBeamParametersProxy();

      // member functions

      // use this form of a function when calling 'bind'
      // void boundMethod( const Record& iRecord );

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
      MCBeamParametersProxy(); // stop default
      MCBeamParametersProxy( const MCBeamParametersProxy& );

      // assignment operator(s)
      const MCBeamParametersProxy& operator=( const MCBeamParametersProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (MCBeamParametersProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      const MCSymmetricBeamProd* m_beamProducer;
      value_type* m_mcBeamParameters ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "MCSymmetricBeamProd/Template/MCBeamParametersProxy.cc"
//#endif

#endif /* MCSYMMETRICBEAMPROD_MCBEAMPARAMETERSPROXY_H */
