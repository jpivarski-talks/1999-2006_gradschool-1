// -*- C++ -*-
#if !defined(TESTBEAMGAS_TESTBEAMGAS_H)
#define TESTBEAMGAS_TESTBEAMGAS_H
//
// Package:     <TestBeamGas>
// Module:      TestBeamGas
//
/**\class TestBeamGas TestBeamGas.h TestBeamGas/TestBeamGas.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Feb  4 16:45:08 EST 2003
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
#include "DataHandler/Frame.h"
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class TestBeamGas : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kCharge,
	 kZ,
	 kNeutralenergy,
	 kVisibleenergy,
	 kMatched1,
	 kMatched2,
	 kNumShowers,
	 kShowerEnergy,
	 kShower1,
	 kShower2,
	 kShower3,
	 kShower4,
	 kShower5,
	 kNumTracks,
	 kBKHShowerEnergy,
	 kBKHShower1,
	 kTrack1,
	 kTrack2,
	 kEBeam,
	 kClosestIntersection,
	 kEventPMag,
	 kEventPPerp,
	 kEventPZ,

	 kNumEntries
      };

      enum {
	 kSHOWERHot,
	 kSHOWEREnergy,
	 kSHOWERStatus,
	 kSHOWERnoTrackMatch,
	 kSHOWERnoTrackMatchConReg,
	 kSHOWERbremTrackValid,
	 kSHOWERbremTrackShowerMatchValid,
	 kSHOWERbremTrackShowerMatchEoverP,

	 kSHOWERNumEntries
      };

      // ------------ Constructors and destructor ----------------
      TestBeamGas( void );                      // anal1 
      virtual ~TestBeamGas();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      virtual ActionBase::ActionResult beginRun( Frame& iFrame);
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
      TestBeamGas( const TestBeamGas& );

      // ------------ assignment operator(s) ---------------------
      const TestBeamGas& operator=( const TestBeamGas& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TestBeamGas::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      double calc_z(Frame& iFrame);
      double calc_ci(Frame& iFrame);
      DABoolean calc_intersection(
	 double& x, double& y, double& z, double& sig2z, double& zsep,
	 KTHelix& a, KTHelix& b );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<double> m_closestIntersectionCut;
      Parameter<double> m_weightedZCut;
      Parameter<double> m_weightedZCleverness;
      Parameter<DABoolean> m_explicitBeamSpot;
      Parameter<double> m_beamX;
      Parameter<double> m_beamY;
      Parameter<double> m_beamZ;

      double m_beam_x;
      double m_beam_y;
      double m_beam_z;

      HIHist1D* m_charge;

      HIHist1D* m_z;
      HIHist1D* m_z_p1;
      HIHist1D* m_z_m1;
      HIHist1D* m_z_p2;
      HIHist1D* m_z_m2;

      HIHist1D* m_track_z0;
      HIHist1D* m_track_z0_p1;
      HIHist1D* m_track_z0_m1;
      HIHist1D* m_track_z0_p2;
      HIHist1D* m_track_z0_m2;

      HIHist1D* m_track_z0_z;
      HIHist1D* m_track_z0_p1_z;
      HIHist1D* m_track_z0_m1_z;
      HIHist1D* m_track_z0_p2_z;
      HIHist1D* m_track_z0_m2_z;

      HIHist1D* m_track_pmag;
      HIHist1D* m_track_pmag_p1;
      HIHist1D* m_track_pmag_m1;
      HIHist1D* m_track_pmag_p2;
      HIHist1D* m_track_pmag_m2;

      HIHist1D* m_track_pperp;
      HIHist1D* m_track_pperp_p1;
      HIHist1D* m_track_pperp_m1;
      HIHist1D* m_track_pperp_p2;
      HIHist1D* m_track_pperp_m2;

      HIHist1D* m_track_pz;
      HIHist1D* m_track_pz_p1;
      HIHist1D* m_track_pz_m1;
      HIHist1D* m_track_pz_p2;
      HIHist1D* m_track_pz_m2;

      HIHist1D* m_shower_e;
      HIHist1D* m_shower_e_p1;
      HIHist1D* m_shower_e_m1;
      HIHist1D* m_shower_e_p2;
      HIHist1D* m_shower_e_m2;

      HINtuple* m_ntuple;
      HINtuple* m_shower_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TESTBEAMGAS_TESTBEAMGAS_H */
