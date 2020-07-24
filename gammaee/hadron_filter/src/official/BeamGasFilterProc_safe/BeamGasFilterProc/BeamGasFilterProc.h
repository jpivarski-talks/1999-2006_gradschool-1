// -*- C++ -*-
#if !defined(BEAMGASFILTERPROC_BEAMGASFILTERPROC_H)
#define BEAMGASFILTERPROC_BEAMGASFILTERPROC_H
//
// Package:     <BeamGasFilterProc>
// Module:      BeamGasFilterProc
//
/**\class BeamGasFilterProc BeamGasFilterProc.h BeamGasFilterProc/BeamGasFilterProc.h
 
 Description: Cuts out a lot of beamgas, leaving hadron efficiency over 99%.

 Usage:

    Include this as a "proc sel" at the appropriate point in your suez
    job to filter out beamgas/beamwall/cosmic rays.  Naturally,
    it is the hadrons that will be ActionBase::kPassed.

    There are seven parameters:

        closestIntersectionCut (default 0.005)    cut value in meters
	weightedZCut (default 0.05)               cut value in meters
	neutralEnergyCut (default 0.01)           cut value in GeV

	explicitBeamSpot (default false)          if false, get
                                                  beamspot from Roy's
			          FAItem<BeamSpot>.  Otherwise, it
			          comes from the following:
	beamX (default 0.)
	beamY (default 0.)
	beamZ (default 0.)

	Note that Monte Carlo is generated with a zero beamspot, and
	data is generated with approximately (-1e-3, 6e-4, 0).

    An efficiency calculation is given by the terminate() method and
    intermittently to the INFO stream.

*/
//
// Author:      Jim Pivarski
// Created:     Thu Oct 31 15:55:25 EST 2002
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

class BeamGasFilterProc : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      BeamGasFilterProc( void );                      // anal1 
      virtual ~BeamGasFilterProc();                   // anal5 

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
      BeamGasFilterProc( const BeamGasFilterProc& );

      // ------------ assignment operator(s) ---------------------
      const BeamGasFilterProc& operator=( const BeamGasFilterProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (BeamGasFilterProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(
	 double& x, double& y, double& z, double& sig2z, double& zsep,
	 KTHelix& a, KTHelix& b );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter< double > m_closestIntersectionCut;
      Parameter< double > m_weightedZCut;
      Parameter< double > m_neutralEnergyCut;
      Parameter< DABoolean > m_explicitBeamSpot;
      Parameter< double > m_beamX;
      Parameter< double > m_beamY;
      Parameter< double > m_beamZ;
      int m_passed;
      int m_total;
      double m_beam_x;
      double m_beam_y;
      double m_beam_z;

      HIHist1D* m_hist_closest_inter;
      HIHist1D* m_histclose_closest_inter;
      HIHist1D* m_hist_weighted_z;
      HIHist1D* m_histclose_weighted_z;
      HIHist1D* m_hist_neutral_energy;
      HIHist1D* m_histclose_neutral_energy;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* BEAMGASFILTERPROC_BEAMGASFILTERPROC_H */
