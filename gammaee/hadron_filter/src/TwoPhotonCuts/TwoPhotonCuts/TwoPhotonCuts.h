// -*- C++ -*-
#if !defined(TWOPHOTONCUTS_TWOPHOTONCUTS_H)
#define TWOPHOTONCUTS_TWOPHOTONCUTS_H
//
// Package:     <TwoPhotonCuts>
// Module:      TwoPhotonCuts
//
/**\class TwoPhotonCuts TwoPhotonCuts.h TwoPhotonCuts/TwoPhotonCuts.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Sep 17 15:51:56 EDT 2002
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

class TwoPhotonCuts : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      TwoPhotonCuts( void );                      // anal1 
      virtual ~TwoPhotonCuts();                   // anal5 

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
      TwoPhotonCuts( const TwoPhotonCuts& );

      // ------------ assignment operator(s) ---------------------
      const TwoPhotonCuts& operator=( const TwoPhotonCuts& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TwoPhotonCuts::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HIHist1D* m_num_tracks;
      HIHist1D* m_closest_intersection;
      HIHist1D* m_weighted_z0;
      HIHist1D* m_visible_energy;
      HIHist1D* m_cc_energy;
      HIHist1D* m_neutral_energy;
      HIHist1D* m_biggest_shower;
      HIHist1D* m_second_biggest_shower;
      HIHist1D* m_third_biggest_shower;
      HIHist1D* m_biggest_match;
      HIHist1D* m_second_biggest_match;
      HIHist1D* m_biggest_track;
      HIHist1D* m_second_track;
      HIHist1D* m_sphericity;
      HIHist1D* m_acoplanarity;
      HIHist1D* m_num_showers;
      HIHist1D* m_totalMomentum_mag;
      HIHist1D* m_totalMomentum_perp;
      HIHist1D* m_totalMomentum_z;
      HIHist1D* m_reconstructed_mass;
      HIHist1D* m_chargedMomentum_mag;
      HIHist1D* m_chargedMomentum_perp;
      HIHist1D* m_chargedMomentum_z;
      HIHist1D* m_charge;
      HIHist1D* m_track_z0;
      HIHist1D* m_shifted_track_z0;
      HIHist1D* m_track_momentum_mag;
      HIHist1D* m_track_momentum_perp;
      HIHist1D* m_track_momentum_z;
      HIHist1D* m_shower_energy;
      HIHist1D* m_second_closest_intersection;
      HIHist1D* m_third_closest_intersection;

      HIHist1D* m_num_tracks_failed;
      HIHist1D* m_closest_intersection_failed;
      HIHist1D* m_weighted_z0_failed;
      HIHist1D* m_visible_energy_failed;
      HIHist1D* m_cc_energy_failed;
      HIHist1D* m_neutral_energy_failed;
      HIHist1D* m_biggest_shower_failed;
      HIHist1D* m_second_biggest_shower_failed;
      HIHist1D* m_third_biggest_shower_failed;
      HIHist1D* m_biggest_match_failed;
      HIHist1D* m_second_biggest_match_failed;
      HIHist1D* m_biggest_track_failed;
      HIHist1D* m_second_track_failed;
      HIHist1D* m_sphericity_failed;
      HIHist1D* m_acoplanarity_failed;
      HIHist1D* m_num_showers_failed;
      HIHist1D* m_totalMomentum_mag_failed;
      HIHist1D* m_totalMomentum_perp_failed;
      HIHist1D* m_totalMomentum_z_failed;
      HIHist1D* m_reconstructed_mass_failed;
      HIHist1D* m_chargedMomentum_mag_failed;
      HIHist1D* m_chargedMomentum_perp_failed;
      HIHist1D* m_chargedMomentum_z_failed;
      HIHist1D* m_charge_failed;
      HIHist1D* m_track_z0_failed;
      HIHist1D* m_shifted_track_z0_failed;
      HIHist1D* m_track_momentum_mag_failed;
      HIHist1D* m_track_momentum_perp_failed;
      HIHist1D* m_track_momentum_z_failed;
      HIHist1D* m_shower_energy_failed;
      HIHist1D* m_second_closest_intersection_failed;
      HIHist1D* m_third_closest_intersection_failed;

      HIHist1D* m_weighted_z0_mezzo;
      HIHist1D* m_visible_energy_mezzo;
      HIHist1D* m_biggest_shower_mezzo;
      HIHist1D* m_second_biggest_shower_mezzo;
      HIHist1D* m_biggest_track_mezzo;
      HIHist1D* m_totalMomentum_perp_mezzo;

      int m_passed;
      int m_allevents;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TWOPHOTONCUTS_TWOPHOTONCUTS_H */
