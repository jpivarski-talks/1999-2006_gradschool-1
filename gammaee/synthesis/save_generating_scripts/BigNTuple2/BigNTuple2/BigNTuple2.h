// -*- C++ -*-
#if !defined(BIGNTUPLE2_BIGNTUPLE2_H)
#define BIGNTUPLE2_BIGNTUPLE2_H
//
// Package:     <BigNTuple2>
// Module:      BigNTuple2
//
/**\class BigNTuple2 BigNTuple2.h BigNTuple2/BigNTuple2.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim McCann
// Created:     Thu May 30 15:00:06 EDT 2002
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
#include "HbookHistogram/HbookNtuple.h"
#include "Navigation/NavTrack.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CommandPattern/Parameter.h"
#include "MCInfo/MCDecayTree/MCDecayTree.h"

// forward declarations

class BigNTuple2 : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------
      enum {
	 kEventNum,
	 kWeightedZ0,
	 kWeightedD0,
	 kCharge,
	 kChargedMomX,
	 kChargedMomY,
	 kChargedMomZ,
	 kNeutralMomX,
	 kNeutralMomY,
	 kNeutralMomZ,
	 kNumShowers,
	 kNumUnmatched,
	 kNumTracks,
	 kTotalShowerEnergy,
	 kMaxShowerEnergy,
	 kTotalUnmatchedEnergy,
	 kMaxUnmatchedEnergy,
	 kTotalTrackMomentum,
	 kTotalTrackMomentumTheta,
	 kTotalTrackMomentumPhi,
	 kMaxTrackMomentum,
	 kTotalTrackEnergy,
	 kMaxTrackEnergy,
	 kBunchWeightBest,
	 kBunchWeightNext,
	 kVertexX,
	 kVertexY,
	 kVertexZ,
	 kVertexChi2,
	 kVertexChi2perTrack,
	 k2DVertexX,
	 k2DVertexY,
	 k2DVertexSigX,
	 k2DVertexSigY,
	 kXYDistance,
	 kZSeparation,
	 kEnergyNeutral,

	 kEntries
      };

      // ------------ Constructors and destructor ----------------
      BigNTuple2( void );                      // anal1 
      virtual ~BigNTuple2();                   // anal5 

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
      BigNTuple2( const BigNTuple2& );

      // ------------ assignment operator(s) ---------------------
      const BigNTuple2& operator=( const BigNTuple2& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (BigNTuple2::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      void closest_intersection(
	 double& xydistance, double& zseparation, double x0, double y0, vector< KTHelix* >& helix );

      DABoolean event_vertex(
	 double& x, double& y, double& sig2x, double& sig2y, vector< KTHelix* >& original,
	 ostream& os, MCDecayTree* decaytree = NULL );

      DABoolean calc_intersection( double& x, double& y, double& sig2x, double& sig2y, double& sig2xy,
				   KTHelix& a, KTHelix& b, DABoolean no_uncertainties );
      DABoolean calc_closest( double& x, double& y, double& sig2x, double& sig2y, double& sig2xy,
			      KTHelix& a, KTHelix& b, DABoolean no_uncertainties );
      void calc_errors( double x, double y, double* dx_dcirc, double* dy_dcirc,
			KTHelix& a, KTHelix& b,
			double& sig2x, double& sig2y, double& sig2xy );

      // ------------ data members -------------------------------

      Parameter< DABoolean > m_lookForCosmics;
      Parameter< DABoolean > m_getBunchData;
      Parameter< DABoolean > m_showBad;
      Parameter< double > m_rmsCut;
      Parameter< double > m_tailCut;
      Parameter< DABoolean > m_interestingOnly;

      HINtuple* m_cosmic;
      HINtuple* m_other;

      HIHist1D* m_cosmic_energy;
      HIHist1D* m_cosmic_phi0diff;
      HIHist1D* m_cosmic_d0sum;
      HIHist1D* m_cosmic_z0diff;
      HIHist1D* m_cosmic_cotThetadiff;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* BIGNTUPLE2_BIGNTUPLE2_H */
