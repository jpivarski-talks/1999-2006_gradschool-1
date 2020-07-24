#if !defined(MCINFODELIVERY_MCINFODELIVERY_H)
#define MCINFODELIVERY_MCINFODELIVERY_H
// -*- C++ -*-
//
// Package:     <MCInfoDelivery>
// Module:      MCInfoDelivery
// 
// Description: Producer to serve up various proxies regarding MC Information
//
// Usage:
//    This producer serves the following proxies
//      * StandardMCParticlePropProxy: creates the CLEO-standard particle
//        property store (MCParticlePropertyStore) based on the file specified
//        by the parameter "standardDecayDec"
//      * UserMCParticlePropProxy: creates the user-defined particle
//        property store based on the (1) the standard store plus (2) the
//        information in the file specified by the parameter "userDecayDec"
//
// Author:      Lawrence Gibbons
// Created:     Mon Dec  7 17:05:28 EST 1998
// $Id: MCInfoDelivery.h,v 1.1.1.1 1999/07/07 01:51:22 lkg Exp $
//
// Revision history
//
// $Log: MCInfoDelivery.h,v $
// Revision 1.1.1.1  1999/07/07 01:51:22  lkg
// initial MCInfoDelivery
//
//

// system include files

// user include files
#include "Processor/Producer.h"
#include "ToolBox/HistogramPackage.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class MCInfoDelivery : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      MCInfoDelivery( void );                      // anal1 
      virtual ~MCInfoDelivery();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( TBHistoManager& );                  

      // ------------ const member functions ----------------------

      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // methods for making the proxies, which take file name arguments
      // in their constructors
      ProxyBase* makeStandardMCParticlePropProxy();
      ProxyBase* makeUserMCParticlePropProxy();

      // ------------ Constructors and destructor -----------------
      MCInfoDelivery( const MCInfoDelivery& ); // stop default

      // ------------ assignment operator(s) ----------------------
      const MCInfoDelivery& operator=( const MCInfoDelivery& ); // stop default

      // ------------ private member functions --------------------

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      Parameter<string> m_systemDecayDecFile;
      Parameter<string> m_userDecayDecFile;

      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* MCINFODELIVERY_MCINFODELIVERY_H */
