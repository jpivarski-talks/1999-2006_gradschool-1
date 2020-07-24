// -*- C++ -*-
#if !defined(CHARGEDISTRIBUTIONSPROC_CHARGEDISTRIBUTIONSPROC_H)
#define CHARGEDISTRIBUTIONSPROC_CHARGEDISTRIBUTIONSPROC_H
//
// Package:     <ChargeDistributionsProc>
// Module:      ChargeDistributionsProc
//
/**\class ChargeDistributionsProc ChargeDistributionsProc.h ChargeDistributionsProc/ChargeDistributionsProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Oct 28 11:11:58 EST 2002
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
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class ChargeDistributionsProc : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      ChargeDistributionsProc( void );                      // anal1 
      virtual ~ChargeDistributionsProc();                   // anal5 

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
      ChargeDistributionsProc( const ChargeDistributionsProc& );

      // ------------ assignment operator(s) ---------------------
      const ChargeDistributionsProc& operator=( const ChargeDistributionsProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ChargeDistributionsProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      double get_weighted_ciz( Frame& iFrame );
      DABoolean calc_intersection(
	 double& x, double& y, double& z, double& sig2z, double& zsep,
	 KTHelix& a, KTHelix& b );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter< DABoolean > m_explicitBeamSpot;
      Parameter< double > m_beamX;
      Parameter< double > m_beamY;
      Parameter< double > m_beamZ;
      double m_beam_x;
      double m_beam_y;
      double m_beam_z;

      HIHist1D* m_track_z0;
      HIHist1D* m_track_z0_far;
      HIHist1D* m_track_z0_minus_wciz;
      HIHist1D* m_track_z0_minus_wciz_far;
      HIHist1D* m_track_d0;
      HIHist1D* m_track_d0_far;
      HIHist1D* m_track_p;
      HIHist1D* m_track_pperp;
      HIHist1D* m_track_pz;
      HIHist1D* m_track_chi2;
      HIHist1D* m_track_chi2_close;
      HIHist1D* m_track_chi2dof;
      HIHist1D* m_track_hitfrac;
      HIHist1D* m_track_hitexp;
      HIHist1D* m_track_fitabort;

      HIHist1D* m_track_z0_pos;
      HIHist1D* m_track_z0_far_pos;
      HIHist1D* m_track_z0_minus_wciz_pos;
      HIHist1D* m_track_z0_minus_wciz_far_pos;
      HIHist1D* m_track_d0_pos;
      HIHist1D* m_track_d0_far_pos;
      HIHist1D* m_track_p_pos;
      HIHist1D* m_track_pperp_pos;
      HIHist1D* m_track_pz_pos;
      HIHist1D* m_track_chi2_pos;
      HIHist1D* m_track_chi2_close_pos;
      HIHist1D* m_track_chi2dof_pos;
      HIHist1D* m_track_hitfrac_pos;
      HIHist1D* m_track_hitexp_pos;
      HIHist1D* m_track_fitabort_pos;

      HIHist1D* m_track_z0_neg;
      HIHist1D* m_track_z0_far_neg;
      HIHist1D* m_track_z0_minus_wciz_neg;
      HIHist1D* m_track_z0_minus_wciz_far_neg;
      HIHist1D* m_track_d0_neg;
      HIHist1D* m_track_d0_far_neg;
      HIHist1D* m_track_p_neg;
      HIHist1D* m_track_pperp_neg;
      HIHist1D* m_track_pz_neg;
      HIHist1D* m_track_chi2_neg;
      HIHist1D* m_track_chi2_close_neg;
      HIHist1D* m_track_chi2dof_neg;
      HIHist1D* m_track_hitfrac_neg;
      HIHist1D* m_track_hitexp_neg;
      HIHist1D* m_track_fitabort_neg;

      HIHist1D* m_charge;
      HIHist1D* m_charge_z0_20cm;
      HIHist1D* m_charge_z0_10cm;
      HIHist1D* m_charge_z0_5cm;
      HIHist1D* m_charge_z0_minus_wciz_10cm;
      HIHist1D* m_charge_z0_minus_wciz_5cm;
      HIHist1D* m_charge_z0_minus_wciz_25mm;
      HIHist1D* m_charge_d0_20mm;
      HIHist1D* m_charge_d0_10mm;
      HIHist1D* m_charge_d0_5mm;
      HIHist1D* m_charge_p_100MeV;
      HIHist1D* m_charge_p_200MeV;
      HIHist1D* m_charge_p_300MeV;
      HIHist1D* m_charge_p_10GeV;
      HIHist1D* m_charge_p_6GeV;
      HIHist1D* m_charge_p_5GeV;
      HIHist1D* m_charge_pperp_100MeV;
      HIHist1D* m_charge_pperp_200MeV;
      HIHist1D* m_charge_pperp_300MeV;
      HIHist1D* m_charge_pperp_3GeV;
      HIHist1D* m_charge_pperp_2GeV;
      HIHist1D* m_charge_pperp_1GeV;
      HIHist1D* m_charge_pz_200MeV;
      HIHist1D* m_charge_pz_100MeV;
      HIHist1D* m_charge_pz_50MeV;
      HIHist1D* m_charge_chi2_300;
      HIHist1D* m_charge_chi2_200;
      HIHist1D* m_charge_chi2_100;
      HIHist1D* m_charge_chi2_0;
      HIHist1D* m_charge_chi2_0_01;
      HIHist1D* m_charge_chi2dof_10;
      HIHist1D* m_charge_chi2dof_5;
      HIHist1D* m_charge_chi2dof_2p5;
      HIHist1D* m_charge_hitfrac_notinf;
      HIHist1D* m_charge_hitfrac_notinf_5;
      HIHist1D* m_charge_hitfrac_notinf_5_12;
      HIHist1D* m_charge_hitexp_0;
      HIHist1D* m_charge_hitexp_10;
      HIHist1D* m_charge_hitexp_20;
      HIHist1D* m_charge_fitabort_no;

      HIHistProf* m_asycharge;
      HIHistProf* m_asycharge_z0_20cm;
      HIHistProf* m_asycharge_z0_10cm;
      HIHistProf* m_asycharge_z0_5cm;
      HIHistProf* m_asycharge_z0_minus_wciz_10cm;
      HIHistProf* m_asycharge_z0_minus_wciz_5cm;
      HIHistProf* m_asycharge_z0_minus_wciz_25mm;
      HIHistProf* m_asycharge_d0_20mm;
      HIHistProf* m_asycharge_d0_10mm;
      HIHistProf* m_asycharge_d0_5mm;
      HIHistProf* m_asycharge_p_100MeV;
      HIHistProf* m_asycharge_p_200MeV;
      HIHistProf* m_asycharge_p_300MeV;
      HIHistProf* m_asycharge_p_10GeV;
      HIHistProf* m_asycharge_p_6GeV;
      HIHistProf* m_asycharge_p_5GeV;
      HIHistProf* m_asycharge_pperp_100MeV;
      HIHistProf* m_asycharge_pperp_200MeV;
      HIHistProf* m_asycharge_pperp_300MeV;
      HIHistProf* m_asycharge_pperp_3GeV;
      HIHistProf* m_asycharge_pperp_2GeV;
      HIHistProf* m_asycharge_pperp_1GeV;
      HIHistProf* m_asycharge_pz_200MeV;
      HIHistProf* m_asycharge_pz_100MeV;
      HIHistProf* m_asycharge_pz_50MeV;
      HIHistProf* m_asycharge_chi2_300;
      HIHistProf* m_asycharge_chi2_200;
      HIHistProf* m_asycharge_chi2_100;
      HIHistProf* m_asycharge_chi2_0;
      HIHistProf* m_asycharge_chi2_0_01;
      HIHistProf* m_asycharge_chi2dof_10;
      HIHistProf* m_asycharge_chi2dof_5;
      HIHistProf* m_asycharge_chi2dof_2p5;
      HIHistProf* m_asycharge_hitfrac_notinf;
      HIHistProf* m_asycharge_hitfrac_notinf_5;
      HIHistProf* m_asycharge_hitfrac_notinf_5_12;
      HIHistProf* m_asycharge_hitexp_0;
      HIHistProf* m_asycharge_hitexp_10;
      HIHistProf* m_asycharge_hitexp_20;
      HIHistProf* m_asycharge_fitabort_no;

      HIHist2D* m_nposneg;
      HIHist2D* m_nposneg_z0_20cm;
      HIHist2D* m_nposneg_z0_10cm;
      HIHist2D* m_nposneg_z0_5cm;
      HIHist2D* m_nposneg_z0_minus_wciz_10cm;
      HIHist2D* m_nposneg_z0_minus_wciz_5cm;
      HIHist2D* m_nposneg_z0_minus_wciz_25mm;
      HIHist2D* m_nposneg_d0_20mm;
      HIHist2D* m_nposneg_d0_10mm;
      HIHist2D* m_nposneg_d0_5mm;
      HIHist2D* m_nposneg_p_100MeV;
      HIHist2D* m_nposneg_p_200MeV;
      HIHist2D* m_nposneg_p_300MeV;
      HIHist2D* m_nposneg_p_10GeV;
      HIHist2D* m_nposneg_p_6GeV;
      HIHist2D* m_nposneg_p_5GeV;
      HIHist2D* m_nposneg_pperp_100MeV;
      HIHist2D* m_nposneg_pperp_200MeV;
      HIHist2D* m_nposneg_pperp_300MeV;
      HIHist2D* m_nposneg_pperp_3GeV;
      HIHist2D* m_nposneg_pperp_2GeV;
      HIHist2D* m_nposneg_pperp_1GeV;
      HIHist2D* m_nposneg_pz_200MeV;
      HIHist2D* m_nposneg_pz_100MeV;
      HIHist2D* m_nposneg_pz_50MeV;
      HIHist2D* m_nposneg_chi2_300;
      HIHist2D* m_nposneg_chi2_200;
      HIHist2D* m_nposneg_chi2_100;
      HIHist2D* m_nposneg_chi2_0;
      HIHist2D* m_nposneg_chi2_0_01;
      HIHist2D* m_nposneg_chi2dof_10;
      HIHist2D* m_nposneg_chi2dof_5;
      HIHist2D* m_nposneg_chi2dof_2p5;
      HIHist2D* m_nposneg_hitfrac_notinf;
      HIHist2D* m_nposneg_hitfrac_notinf_5;
      HIHist2D* m_nposneg_hitfrac_notinf_5_12;
      HIHist2D* m_nposneg_hitexp_0;
      HIHist2D* m_nposneg_hitexp_10;
      HIHist2D* m_nposneg_hitexp_20;
      HIHist2D* m_nposneg_fitabort_no;


      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CHARGEDISTRIBUTIONSPROC_CHARGEDISTRIBUTIONSPROC_H */
