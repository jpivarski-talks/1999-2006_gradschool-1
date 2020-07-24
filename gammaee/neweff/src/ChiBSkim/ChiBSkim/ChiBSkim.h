// -*- C++ -*-
#if !defined(CHIBSKIM_CHIBSKIM_H)
#define CHIBSKIM_CHIBSKIM_H
//
// Package:     <ChiBSkim>
// Module:      ChiBSkim
//
/**\class ChiBSkim ChiBSkim.h ChiBSkim/ChiBSkim.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Feb 16 18:51:22 EST 2004
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
#include "HistogramInterface/HINtuple.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class ChiBSkim : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------
      
      enum {
	 kntk, kepntk,
	 ktr1, ktr2, keop1, keop2,
	 kmass1s,
	 kd1, kd2, kz1, kz2,
	 kcosth1, kcosth2, kphi1, kphi2,
	 kph1, kph2,
	 kmasschib,
	 kcosth3, kcosth4, kphi3, kphi4,
	 kallp, kallpt, kalle,
	 ktype,

	 kNumEntries};

      // ------------ Constructors and destructor ----------------
      ChiBSkim( void );                      // anal1 
      virtual ~ChiBSkim();                   // anal5 

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
      ChiBSkim( const ChiBSkim& );

      // ------------ assignment operator(s) ---------------------
      const ChiBSkim& operator=( const ChiBSkim& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ChiBSkim::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      
      Parameter<DABoolean> m_cut;

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CHIBSKIM_CHIBSKIM_H */
