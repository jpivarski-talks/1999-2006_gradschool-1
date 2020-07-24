// -*- C++ -*-
#if !defined(SUPERCUTS_SUPERCUTS_H)
#define SUPERCUTS_SUPERCUTS_H
//
// Package:     <SuperCuts>
// Module:      SuperCuts
//
/**\class SuperCuts SuperCuts.h SuperCuts/SuperCuts.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri Jan 30 13:33:32 EST 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "CommandPattern/Parameter.h"
#include "HistogramInterface/HistogramPackage.h"
#include "HistogramInterface/HINtuple.h"

// forward declarations

class SuperCuts : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------
      enum {
	 kMC,
	 kRawTk, kEPTk, kTMTk,
	 kCCEn, kVisEn, kACop, kECt30, kECt25, kECt20, kECt15,
	 kP1, kP2, kP3, kP4,
	 kD1, kD2, kD3, kD4,
	 kZ1, kZ2, kZ3, kZ4,
	 kT1, kT2, kT3, kT4,
	 kF1, kF2, kF3, kF4,
	 kME1, kME2, kME3, kME4,
	 kMD1, kMD2, kMD3, kMD4,
	 kE1, kE2, kE3, kE4,
	 kShT1, kShT2, kShT3, kShT4,
	 kP2x, kP2y, kP2z,
	 kP4x, kP4y, kP4z,
	 kPAllx, kPAlly, kPAllz,
	 kPEPx, kPEPy, kPEPz,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      SuperCuts( void );                      // anal1 
      virtual ~SuperCuts();                   // anal5 

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
      SuperCuts( const SuperCuts& );

      // ------------ assignment operator(s) ---------------------
      const SuperCuts& operator=( const SuperCuts& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (SuperCuts::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<DABoolean> m_mcrare;
      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* SUPERCUTS_SUPERCUTS_H */
