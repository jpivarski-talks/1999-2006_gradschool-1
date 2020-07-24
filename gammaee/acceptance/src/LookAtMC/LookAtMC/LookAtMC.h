// -*- C++ -*-
#if !defined(LOOKATMC_LOOKATMC_H)
#define LOOKATMC_LOOKATMC_H
//
// Package:     <LookAtMC>
// Module:      LookAtMC
//
/**\class LookAtMC LookAtMC.h LookAtMC/LookAtMC.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Feb 14 11:44:38 EST 2005
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
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class LookAtMC : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      LookAtMC( void );                      // anal1 
      virtual ~LookAtMC();                   // anal5 

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
      LookAtMC( const LookAtMC& );

      // ------------ assignment operator(s) ---------------------
      const LookAtMC& operator=( const LookAtMC& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (LookAtMC::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HIHist1D* m_meas_thrust_dir;
      HIHist1D* m_meas_thrust_mag;
      HIHist1D* m_COMPlanarity;
      HIHist1D* m_TMomPlanarity;
      HIHist1D* m_thrust_mag;
      HIHist1D* m_thrust_dir;

      int m_even;
      int m_odd;
      int m_unknown;

      int m_failp;
      int m_allp;
      int m_failm;
      int m_allm;
      int m_fail0;
      int m_all0;

      HIHist1D* m_mesons;
      HIHist1D* m_baryons;
      HIHist1D* m_strangers;
      HIHist1D* m_charmers;
      HIHist1D* m_mesons_all;
      HIHist1D* m_baryons_all;
      HIHist1D* m_strangers_all;
      HIHist1D* m_charmers_all;

      HIHist1D* m_mass_failures;
      HIHist1D* m_mass2_failures;
      HIHist1D* m_mass_all;
      HIHist1D* m_mass2_all;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* LOOKATMC_LOOKATMC_H */
