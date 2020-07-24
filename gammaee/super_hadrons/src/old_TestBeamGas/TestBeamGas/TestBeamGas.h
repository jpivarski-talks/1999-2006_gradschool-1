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
	 kRawCharge,
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

	 kNumEntries
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
      HIHist1D* m_raw_charge;

      HIHist1D* m_z;
      HIHist1D* m_z_p1;
      HIHist1D* m_z_m1;
      HIHist1D* m_z_p2;
      HIHist1D* m_z_m2;
      HIHist1D* m_z_rp1;
      HIHist1D* m_z_rm1;
      HIHist1D* m_z_rp2;
      HIHist1D* m_z_rm2;

      HIHist1D* m_neutralEnergy;
      HIHist1D* m_neutralEnergy_p1;
      HIHist1D* m_neutralEnergy_m1;
      HIHist1D* m_neutralEnergy_p2;
      HIHist1D* m_neutralEnergy_m2;
      HIHist1D* m_neutralEnergy_rp1;
      HIHist1D* m_neutralEnergy_rm1;
      HIHist1D* m_neutralEnergy_rp2;
      HIHist1D* m_neutralEnergy_rm2;

      HIHist1D* m_visibleEnergy;
      HIHist1D* m_visibleEnergy_p1;
      HIHist1D* m_visibleEnergy_m1;
      HIHist1D* m_visibleEnergy_p2;
      HIHist1D* m_visibleEnergy_m2;
      HIHist1D* m_visibleEnergy_rp1;
      HIHist1D* m_visibleEnergy_rm1;
      HIHist1D* m_visibleEnergy_rp2;
      HIHist1D* m_visibleEnergy_rm2;

      HIHist1D* m_shower_energy;
      HIHist1D* m_shower_energy_p1;
      HIHist1D* m_shower_energy_m1;
      HIHist1D* m_shower_energy_p2;
      HIHist1D* m_shower_energy_m2;
      HIHist1D* m_shower_energy_rp1;
      HIHist1D* m_shower_energy_rm1;
      HIHist1D* m_shower_energy_rp2;
      HIHist1D* m_shower_energy_rm2;

      HIHist1D* m_num_showers;
      HIHist1D* m_num_showers_p1;
      HIHist1D* m_num_showers_m1;
      HIHist1D* m_num_showers_p2;
      HIHist1D* m_num_showers_m2;
      HIHist1D* m_num_showers_rp1;
      HIHist1D* m_num_showers_rm1;
      HIHist1D* m_num_showers_rp2;
      HIHist1D* m_num_showers_rm2;

      HIHist1D* m_matched1;
      HIHist1D* m_matched1_p1;
      HIHist1D* m_matched1_m1;
      HIHist1D* m_matched1_p2;
      HIHist1D* m_matched1_m2;
      HIHist1D* m_matched1_rp1;
      HIHist1D* m_matched1_rm1;
      HIHist1D* m_matched1_rp2;
      HIHist1D* m_matched1_rm2;

      HIHist1D* m_matched2;
      HIHist1D* m_matched2_p1;
      HIHist1D* m_matched2_m1;
      HIHist1D* m_matched2_p2;
      HIHist1D* m_matched2_m2;
      HIHist1D* m_matched2_rp1;
      HIHist1D* m_matched2_rm1;
      HIHist1D* m_matched2_rp2;
      HIHist1D* m_matched2_rm2;

      HIHist1D* m_shower1;
      HIHist1D* m_shower1_p1;
      HIHist1D* m_shower1_m1;
      HIHist1D* m_shower1_p2;
      HIHist1D* m_shower1_m2;
      HIHist1D* m_shower1_rp1;
      HIHist1D* m_shower1_rm1;
      HIHist1D* m_shower1_rp2;
      HIHist1D* m_shower1_rm2;

      HIHist1D* m_shower2;
      HIHist1D* m_shower2_p1;
      HIHist1D* m_shower2_m1;
      HIHist1D* m_shower2_p2;
      HIHist1D* m_shower2_m2;
      HIHist1D* m_shower2_rp1;
      HIHist1D* m_shower2_rm1;
      HIHist1D* m_shower2_rp2;
      HIHist1D* m_shower2_rm2;

      HIHist1D* m_shower3;
      HIHist1D* m_shower3_p1;
      HIHist1D* m_shower3_m1;
      HIHist1D* m_shower3_p2;
      HIHist1D* m_shower3_m2;
      HIHist1D* m_shower3_rp1;
      HIHist1D* m_shower3_rm1;
      HIHist1D* m_shower3_rp2;
      HIHist1D* m_shower3_rm2;

      HIHist1D* m_shower4;
      HIHist1D* m_shower4_p1;
      HIHist1D* m_shower4_m1;
      HIHist1D* m_shower4_p2;
      HIHist1D* m_shower4_m2;
      HIHist1D* m_shower4_rp1;
      HIHist1D* m_shower4_rm1;
      HIHist1D* m_shower4_rp2;
      HIHist1D* m_shower4_rm2;

      HIHist1D* m_shower5;
      HIHist1D* m_shower5_p1;
      HIHist1D* m_shower5_m1;
      HIHist1D* m_shower5_p2;
      HIHist1D* m_shower5_m2;
      HIHist1D* m_shower5_rp1;
      HIHist1D* m_shower5_rm1;
      HIHist1D* m_shower5_rp2;
      HIHist1D* m_shower5_rm2;

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TESTBEAMGAS_TESTBEAMGAS_H */
