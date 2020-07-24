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
// Created:     Wed Dec 11 11:19:44 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Experiment/report.h"
#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"
#include "CommandPattern/Parameter.h"
#include "KinematicTrajectory/KTHelix.h"

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

      void calc_beamgas_events(Severity severity);
      DABoolean calc_intersection(
	 double& x, double& y, double& z, double& sig2z, double& zsep,
	 KTHelix& a, KTHelix& b );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_total;

      int m_Rpos_fore;
      int m_Rpos_back;
      int m_Rneg_fore;
      int m_Rneg_back;
      int m_Rpos_neut;
      int m_Rneg_neut;

      int m_Lpos_fore;
      int m_Lpos_back;
      int m_Lneg_fore;
      int m_Lneg_back;
      int m_Lpos_neut;
      int m_Lneg_neut;

      HIHist1D* m_vertex_zqual_neg;
      HIHist1D* m_vertex_zqual_pos;
      HIHist1D* m_vertex_perp_neg;
      HIHist1D* m_vertex_perp_pos;
      HIHist1D* m_perp_from_vertex_neg;
      HIHist1D* m_perp_from_vertex_pos;

      HIHist1D* m_event_charge;
      HIHist1D* m_event_charge_trkman;
      HIHist1D* m_event_charge_trkman_vertex;

      HIHist1D* m_event_pz_Rpos;
      HIHist1D* m_event_pz_Rneg;
      HIHist1D* m_event_neutral_energy_Rpos;
      HIHist1D* m_event_neutral_energy_Rneg;

      HIHist1D* m_event_pz_Lpos;
      HIHist1D* m_event_pz_Lneg;
      HIHist1D* m_event_neutral_energy_Lpos;
      HIHist1D* m_event_neutral_energy_Lneg;

      HIHist1D* m_num_tracks_Rpos;
      HIHist1D* m_weighted_z0_Rpos;
      HIHist1D* m_visible_energy_Rpos;
      HIHist1D* m_cc_energy_Rpos;
      HIHist1D* m_neutral_energy_Rpos;
      HIHist1D* m_biggest_shower_Rpos;
      HIHist1D* m_biggest_match_Rpos;
      HIHist1D* m_biggest_track_Rpos;
      HIHist1D* m_sphericity_Rpos;
      HIHist1D* m_acoplanarity_Rpos;
      HIHist1D* m_num_showers_Rpos;
      HIHist1D* m_totalMomentum_mag_Rpos;
      HIHist1D* m_totalMomentum_perp_Rpos;
      HIHist1D* m_totalMomentum_z_Rpos;
      HIHist1D* m_track_z0_Rpos;
      HIHist1D* m_shifted_track_z0_Rpos;
      HIHist1D* m_track_momentum_mag_Rpos;
      HIHist1D* m_track_momentum_perp_Rpos;
      HIHist1D* m_track_momentum_z_Rpos;
      HIHist1D* m_shower_energy_Rpos;

      HIHist1D* m_num_tracks_Rneg;
      HIHist1D* m_weighted_z0_Rneg;
      HIHist1D* m_visible_energy_Rneg;
      HIHist1D* m_cc_energy_Rneg;
      HIHist1D* m_neutral_energy_Rneg;
      HIHist1D* m_biggest_shower_Rneg;
      HIHist1D* m_biggest_match_Rneg;
      HIHist1D* m_biggest_track_Rneg;
      HIHist1D* m_sphericity_Rneg;
      HIHist1D* m_acoplanarity_Rneg;
      HIHist1D* m_num_showers_Rneg;
      HIHist1D* m_totalMomentum_mag_Rneg;
      HIHist1D* m_totalMomentum_perp_Rneg;
      HIHist1D* m_totalMomentum_z_Rneg;
      HIHist1D* m_track_z0_Rneg;
      HIHist1D* m_shifted_track_z0_Rneg;
      HIHist1D* m_track_momentum_mag_Rneg;
      HIHist1D* m_track_momentum_perp_Rneg;
      HIHist1D* m_track_momentum_z_Rneg;
      HIHist1D* m_shower_energy_Rneg;

      HIHist1D* m_num_tracks_Lpos;
      HIHist1D* m_weighted_z0_Lpos;
      HIHist1D* m_visible_energy_Lpos;
      HIHist1D* m_cc_energy_Lpos;
      HIHist1D* m_neutral_energy_Lpos;
      HIHist1D* m_biggest_shower_Lpos;
      HIHist1D* m_biggest_match_Lpos;
      HIHist1D* m_biggest_track_Lpos;
      HIHist1D* m_sphericity_Lpos;
      HIHist1D* m_acoplanarity_Lpos;
      HIHist1D* m_num_showers_Lpos;
      HIHist1D* m_totalMomentum_mag_Lpos;
      HIHist1D* m_totalMomentum_perp_Lpos;
      HIHist1D* m_totalMomentum_z_Lpos;
      HIHist1D* m_track_z0_Lpos;
      HIHist1D* m_shifted_track_z0_Lpos;
      HIHist1D* m_track_momentum_mag_Lpos;
      HIHist1D* m_track_momentum_perp_Lpos;
      HIHist1D* m_track_momentum_z_Lpos;
      HIHist1D* m_shower_energy_Lpos;

      HIHist1D* m_num_tracks_Lneg;
      HIHist1D* m_weighted_z0_Lneg;
      HIHist1D* m_visible_energy_Lneg;
      HIHist1D* m_cc_energy_Lneg;
      HIHist1D* m_neutral_energy_Lneg;
      HIHist1D* m_biggest_shower_Lneg;
      HIHist1D* m_biggest_match_Lneg;
      HIHist1D* m_biggest_track_Lneg;
      HIHist1D* m_sphericity_Lneg;
      HIHist1D* m_acoplanarity_Lneg;
      HIHist1D* m_num_showers_Lneg;
      HIHist1D* m_totalMomentum_mag_Lneg;
      HIHist1D* m_totalMomentum_perp_Lneg;
      HIHist1D* m_totalMomentum_z_Lneg;
      HIHist1D* m_track_z0_Lneg;
      HIHist1D* m_shifted_track_z0_Lneg;
      HIHist1D* m_track_momentum_mag_Lneg;
      HIHist1D* m_track_momentum_perp_Lneg;
      HIHist1D* m_track_momentum_z_Lneg;
      HIHist1D* m_shower_energy_Lneg;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* BEAMGASCOUNTERPROC_BEAMGASCOUNTERPROC_H */
