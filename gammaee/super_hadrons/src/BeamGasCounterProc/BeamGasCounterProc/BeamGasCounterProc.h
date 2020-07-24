// -*- C++ -*-
#if !defined(BEAMGASCOUNTERPROC_BEAMGASCOUNTERPROC_H)
#define BEAMGASCOUNTERPROC_BEAMGASCOUNTERPROC_H
//
// Package:     <BeamGasCounterProc>
// Module:      BeamGasCounterProc
//
/**\class BeamGasCounterProc BeamGasCounterProc.h BeamGasCounterProc/BeamGasCounterProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Jan 29 16:23:19 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "Experiment/report.h"
#include "HistogramInterface/HistogramPackage.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class BeamGasCounterProc : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      BeamGasCounterProc( void );                      // anal1 
      virtual ~BeamGasCounterProc();                   // anal5 

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
      //virtual ActionBase::ActionResult geometry( Frame& iFrame);
      //virtual ActionBase::ActionResult hardware( Frame& iFrame);
      //virtual ActionBase::ActionResult user( Frame& iFrame);

      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      BeamGasCounterProc( const BeamGasCounterProc& );

      // ------------ assignment operator(s) ---------------------
      const BeamGasCounterProc& operator=( const BeamGasCounterProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (BeamGasCounterProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      void howmany(Severity severity);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<double> m_factor;
      Parameter<double> m_factorUncert;
      int m_events;
      int m_pos;
      int m_neg;

      HIHist1D* m_ne;
      HIHist1D* m_ne_pos;
      HIHist1D* m_ne_neg;
      HIHist1D* m_pz;
      HIHist1D* m_pz_pos;
      HIHist1D* m_pz_neg;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* BEAMGASCOUNTERPROC_BEAMGASCOUNTERPROC_H */
