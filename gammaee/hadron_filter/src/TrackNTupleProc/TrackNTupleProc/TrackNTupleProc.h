// -*- C++ -*-
#if !defined(TRACKNTUPLEPROC_TRACKNTUPLEPROC_H)
#define TRACKNTUPLEPROC_TRACKNTUPLEPROC_H
//
// Package:     <TrackNTupleProc>
// Module:      TrackNTupleProc
//
/**\class TrackNTupleProc TrackNTupleProc.h TrackNTupleProc/TrackNTupleProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Oct 21 10:30:05 EDT 2002
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
#include "CommandPattern/Parameter.h"
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class TrackNTupleProc : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kCurvature,
	 kPhi0,
	 kD0,
	 kCotTheta,
	 kZ0,
	 
	 kPPerp,
	 kPz,

	 kChi2,
	 kDOF,
	 kHitFraction,
	 kHitsExpected,
	 kFitAbort,

	 kAverageAxResidual,
	 kAverageStResidual,
	 kRMSAxResidual,
	 kRMSStResidual,

	 kEventMultiplicity,
	 kEventCharge,
	 kEventNeutralEnergy,
	 kEventClosestIntersection,
	 kEventWeightedZ0,
	 kEventWeightedCIZ,

	 kTrackVars
      };

      enum {
	 kNumTracks,
	 kCharge,
	 kNeutralEnergy,

	 kPosAborts,
	 kNegAborts,

	 kClosestIntersection,
	 kWeightedZ0,
	 kWeightedCIZ,

	 kPosTracks,
	 kNegTracks,
	 kPosGoodZ0Tracks,
	 kNegGoodZ0Tracks,
	 kPosGoodD0Tracks,
	 kNegGoodD0Tracks,
	 kPosTrkManTracks,
	 kNegTrkManTracks,

	 kEventVars
      };

      // ------------ Constructors and destructor ----------------
      TrackNTupleProc( void );                      // anal1 
      virtual ~TrackNTupleProc();                   // anal5 

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
      TrackNTupleProc( const TrackNTupleProc& );

      // ------------ assignment operator(s) ---------------------
      const TrackNTupleProc& operator=( const TrackNTupleProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TrackNTupleProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      double get_weighted_z0( Frame& iFrame );
      double get_closest_intersection( Frame& iFrame );
      double get_weighted_ciz( Frame& iFrame );
      DABoolean calc_intersection(
	 double& x, double& y, double& z, double& sig2z, double& zsep,
	 KTHelix& a, KTHelix& b );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter< double > m_beam_x;
      Parameter< double > m_beam_y;

      HINtuple* m_track;
      HINtuple* m_event;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TRACKNTUPLEPROC_TRACKNTUPLEPROC_H */
