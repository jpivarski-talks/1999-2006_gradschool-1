// -*- C++ -*-
#if !defined(BEAMGASWALLTESTER_BEAMGASWALLTESTER_H)
#define BEAMGASWALLTESTER_BEAMGASWALLTESTER_H
//
// Package:     <BeamGasWallTester>
// Module:      BeamGasWallTester
//
/**\class BeamGasWallTester BeamGasWallTester.h BeamGasWallTester/BeamGasWallTester.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim McCann
// Created:     Fri Feb  8 10:50:41 EST 2002
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

// forward declarations

class BeamGasWallTester : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      BeamGasWallTester( void );                      // anal1 
      virtual ~BeamGasWallTester();                   // anal5 

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
      BeamGasWallTester( const BeamGasWallTester& );

      // ------------ assignment operator(s) ---------------------
      const BeamGasWallTester& operator=( const BeamGasWallTester& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (BeamGasWallTester::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HIHist1D* m_z0;
      HIHist1D* m_cotTheta;
      HIHist1D* m_event_z0;
      HIHist1D* m_ave_z0;
      HIHist1D* m_event_z0_restrict;
      HIHist1D* m_ave_z0_restrict;
      HIHist1D* m_event_charge;
      HIHistProf* m_event_charge_v_event_z0;
      HIHistProf* m_event_charge_v_ave_z0;
      HIHist2D* m_event_charge_v_ave_z0_2d;
      HIHist1D* m_cc_energy;
      HIHistProf* m_event_charge_v_cc_energy;
      HIHistProf* m_ave_z0_v_cc_energy;
      HIHist2D* m_ave_z0_v_cc_energy_2d;
      HIHist1D* m_total_energy;
      HIHistProf* m_event_charge_v_total_energy;
      HIHistProf* m_ave_z0_v_total_energy;
      HIHist2D* m_ave_z0_v_total_energy_2d;
      HIHist1D* m_event_z_momentum;
      HIHistProf* m_event_charge_v_event_z_momentum;
      HIHistProf* m_ave_z0_v_event_z_momentum;
      HIHist2D* m_ave_z0_v_event_z_momentum_2d;
      HIHist1D* m_event_mag_momentum;
      HIHistProf* m_event_charge_v_event_mag_momentum;
      HIHistProf* m_ave_z0_v_event_mag_momentum;
      HIHist2D* m_ave_z0_v_event_mag_momentum_2d;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* BEAMGASWALLTESTER_BEAMGASWALLTESTER_H */
