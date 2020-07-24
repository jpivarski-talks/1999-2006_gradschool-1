// -*- C++ -*-
#if !defined(BIGNTUPLE_BIGNTUPLE_H)
#define BIGNTUPLE_BIGNTUPLE_H
//
// Package:     <BigNTuple>
// Module:      BigNTuple
//
/**\class BigNTuple BigNTuple.h BigNTuple/BigNTuple.h
 
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

// forward declarations

class BigNTuple : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------
      enum {
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

	 kEntries
      };

      // ------------ Constructors and destructor ----------------
      BigNTuple( void );                      // anal1 
      virtual ~BigNTuple();                   // anal5 

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
      BigNTuple( const BigNTuple& );

      // ------------ assignment operator(s) ---------------------
      const BigNTuple& operator=( const BigNTuple& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (BigNTuple::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      DABoolean calculate_crossing(
	 KTHelix& a, KTHelix& b,
	 double& x, double& sigx, double& y, double& sigy );
      double radial_deviations( KTHelix& a, KTHelix& b, double x, double y );
      DABoolean sol1( KTHelix& a, KTHelix& b, double& x, double& y );
      DABoolean errsol1( KTHelix& a, KTHelix& b, double& ex, double& ey );
      DABoolean sol2( KTHelix& a, KTHelix& b, double& x, double& y );
      DABoolean errsol2( KTHelix& a, KTHelix& b, double& ex, double& ey );
      DABoolean sol3( KTHelix& a, KTHelix& b, double& x, double& y );
      DABoolean errsol3( KTHelix& a, KTHelix& b, double& ex, double& ey );
      DABoolean sol4( KTHelix& a, KTHelix& b, double& x, double& y );
      DABoolean errsol4( KTHelix& a, KTHelix& b, double& ex, double& ey );

      // ------------ data members -------------------------------

      Parameter< DABoolean > m_lookForCosmics;
      Parameter< DABoolean > m_getBunchData;

      HINtuple* m_cosmic;
      HINtuple* m_other;

      HIHist1D* m_cosmic_energy;
      HIHist1D* m_cosmic_phi0diff;
      HIHist1D* m_cosmic_d0sum;
      HIHist1D* m_cosmic_z0diff;
      HIHist1D* m_cosmic_cotThetadiff;

      HIHist1D* m_cosmic_un_cosTh;
      HIHist1D* m_other_un_cosTh;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* BIGNTUPLE_BIGNTUPLE_H */
