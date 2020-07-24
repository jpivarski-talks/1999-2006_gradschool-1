// -*- C++ -*-
#if !defined(CHIBMC_CHIBMC_H)
#define CHIBMC_CHIBMC_H
//
// Package:     <ChiBMC>
// Module:      ChiBMC
//
/**\class ChiBMC ChiBMC.h ChiBMC/ChiBMC.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Feb 16 18:51:32 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class ChiBMC : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      ChiBMC( void );                      // anal1 
      virtual ~ChiBMC();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      //virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      //virtual ActionBase::ActionResult endRun( Frame& iFrame);

      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      ChiBMC( const ChiBMC& );

      // ------------ assignment operator(s) ---------------------
      const ChiBMC& operator=( const ChiBMC& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ChiBMC::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<unsigned int> m_mc;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CHIBMC_CHIBMC_H */
