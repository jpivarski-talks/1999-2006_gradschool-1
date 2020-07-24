// -*- C++ -*-
#if !defined(TWOPIONSPROC_TWOPIONSPROC_H)
#define TWOPIONSPROC_TWOPIONSPROC_H
//
// Package:     <TwoPionsProc>
// Module:      TwoPionsProc
//
/**\class TwoPionsProc TwoPionsProc.h TwoPionsProc/TwoPionsProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim McCann
// Created:     Wed Aug  7 13:49:11 EDT 2002
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

class TwoPionsProc : public Processor
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
	 kPSigma,
	 kNSigma,
	 kPZ0,
	 kPZ0err2,
	 kNZ0,
	 kNZ0err2,
	 kAbsX,
	 kShiftX,
	 kAbsY,
	 kShiftY,
	 kMRecoil,
	 kPRx,
	 kPRy,
	 kPRz,
	 kPPx,
	 kPPy,
	 kPPz,
	 kNPx,
	 kNPy,
	 kNPz,
	 kFitCriteria,

	 kNNtupleVars
      };

      // ------------ Constructors and destructor ----------------
      TwoPionsProc( void );                      // anal1 
      virtual ~TwoPionsProc();                   // anal5 

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
      TwoPionsProc( const TwoPionsProc& );

      // ------------ assignment operator(s) ---------------------
      const TwoPionsProc& operator=( const TwoPionsProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TwoPionsProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      double closest_intersection( vector< KTHelix* > helix, double beam_x, double beam_y );
      DABoolean event_vertex( double& x, double& y, double& sigx, double& sigy,
			      vector< KTHelix* > helix );
      DABoolean zsep_test( double x, double y, KTHelix& a, KTHelix& b );
      double calc_rms( vector< double >& trialx, vector< double >& trialy,
		       vector< int >& hindex1, vector< int >& hindex2,
		       int skip = -1 );
      DABoolean calc_intersection( double& x, double& y, double& sigx, double& sigy,
				   KTHelix& a, KTHelix& b, DABoolean calc_uncerts = false );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ data members -------------------------------

      Parameter< DABoolean > m_fillBuffer;
      Parameter< DABoolean > m_noBeamSpot;

      HINtuple* m_beamSpotVars;
      HIHist2D* m_centeredBeamSpot;
      HINtuple* m_ntuple;

      int m_num_buffer_events;
      int m_buffer_pointer;
      vector< double > m_buf_x;
      vector< double > m_buf_sigx;
      vector< double > m_buf_y;
      vector< double > m_buf_sigy;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TWOPIONSPROC_TWOPIONSPROC_H */
