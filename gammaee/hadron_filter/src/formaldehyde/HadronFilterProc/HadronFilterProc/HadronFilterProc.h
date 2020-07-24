// -*- C++ -*-
#if !defined(HADRONFILTERPROC_HADRONFILTERPROC_H)
#define HADRONFILTERPROC_HADRONFILTERPROC_H
//
// Package:     <HadronFilterProc>
// Module:      HadronFilterProc
//
/**\class HadronFilterProc HadronFilterProc.h HadronFilterProc/HadronFilterProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim McCann
// Created:     Mon Aug  5 13:54:13 EDT 2002
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

class HadronFilterProc : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------
      enum {
	 kRa, kXa, kYa,
	 kRb, kXb, kYb,
	 kNumCirc
      };
      enum {
	 kCurva, kD0a, kPhi0a,
	 kCurvb, kD0b, kPhi0b,
	 kNumTrack
      };

      enum {
	 kRunNum,
	 kEventNum,
	 kX,
	 kSigX,
	 kY,
	 kSigY,
	 kSpread,

	 kNBeamSpotVars
      };

      enum {
	 kNumTracks,
	 kClosestIntersection,
	 kSecondClosestIntersection,
	 kWeightedZ0,
	 kBunchWeightMargin,

	 kNNtupleVars
      };

      // ------------ Constructors and destructor ----------------
      HadronFilterProc( void );                      // anal1 
      virtual ~HadronFilterProc();                   // anal5 

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
      HadronFilterProc( const HadronFilterProc& );

      // ------------ assignment operator(s) ---------------------
      const HadronFilterProc& operator=( const HadronFilterProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (HadronFilterProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      double closest_intersection( vector< KTHelix* > helix,
				   double beam_x, double beam_y, double veto = -1. );
      DABoolean event_vertex( double& x, double& y, double& sigx, double& sigy,
			      vector< KTHelix* > helix );
      DABoolean zsep_test( double x, double y, KTHelix& a, KTHelix& b );
      double calc_rms( vector< double >& trialx, vector< double >& trialy,
		       vector< int >& hindex1, vector< int >& hindex2,
		       int skip = -1 );
      DABoolean calc_intersection( double& x, double& y, double& sigx, double& sigy,
				   KTHelix& a, KTHelix& b, DABoolean calc_uncerts = false );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter< DABoolean > m_fillBuffer;
      Parameter< DABoolean > m_noBeamSpot;
      Parameter< DABoolean > m_noBunchWeight;
      Parameter< double > m_ntupleSize;

      Parameter< double > m_closestIntersectionCut;
      Parameter< double > m_tailCut;
      Parameter< double > m_weightedZ0Cut;
      Parameter< double > m_bunchWeightMarginCut;

      HINtuple* m_beamSpotVars;
      HINtuple* m_passNtuple;
      HINtuple* m_failNtuple;
      HIHist2D* m_centeredBeamSpot;
      HIHist1D* m_numTracks_passed;
      HIHist1D* m_numTracks_failed;
      HIHist1D* m_closestIntersection_passed;
      HIHist1D* m_closestIntersection_failed;
      HIHist1D* m_weightedZ0_passed;
      HIHist1D* m_weightedZ0_failed;
      HIHist1D* m_bunchWeightMargin_passed;
      HIHist1D* m_bunchWeightMargin_failed;

      int m_num_buffer_events;
      int m_buffer_pointer;
      vector< double > m_buf_x;
      vector< double > m_buf_sigx;
      vector< double > m_buf_y;
      vector< double > m_buf_sigy;

      int m_entriesInNtuple;

      int m_passed;
      int m_gt2tracks;
      int m_allevents;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* HADRONFILTERPROC_HADRONFILTERPROC_H */
