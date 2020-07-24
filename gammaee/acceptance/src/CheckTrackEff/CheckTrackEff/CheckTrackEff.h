// -*- C++ -*-
#if !defined(CHECKTRACKEFF_CHECKTRACKEFF_H)
#define CHECKTRACKEFF_CHECKTRACKEFF_H
//
// Package:     <CheckTrackEff>
// Module:      CheckTrackEff
//
/**\class CheckTrackEff CheckTrackEff.h CheckTrackEff/CheckTrackEff.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri May 14 15:26:54 EDT 2004
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

// forward declarations

class CheckTrackEff : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      CheckTrackEff( void );                      // anal1 
      virtual ~CheckTrackEff();                   // anal5 

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
      CheckTrackEff( const CheckTrackEff& );

      // ------------ assignment operator(s) ---------------------
      const CheckTrackEff& operator=( const CheckTrackEff& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (CheckTrackEff::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      void initialize();
      void summarize();

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_run;

      int m_tracks;
      int m_trackFitOK;
      int m_reducedChi2;
      int m_hitFraction_low;
      int m_hitFraction_high;
      int m_adacd;
      int m_az0;
      int m_pTk_low;
      int m_pTk_high;
      int m_aCotTheta;
      int m_errCotTheta;
      int m_errz0;

      int m1_tracks;
      int m1_trackFitOK;
      int m1_reducedChi2;
      int m1_hitFraction_low;
      int m1_hitFraction_high;
      int m1_adacd;
      int m1_az0;
      int m1_pTk_low;
      int m1_pTk_high;
      int m1_aCotTheta;
      int m1_errCotTheta;
      int m1_errz0;

      int m2_tracks;
      int m2_trackFitOK;
      int m2_reducedChi2;
      int m2_hitFraction_low;
      int m2_hitFraction_high;
      int m2_adacd;
      int m2_az0;
      int m2_pTk_low;
      int m2_pTk_high;
      int m2_aCotTheta;
      int m2_errCotTheta;
      int m2_errz0;

      int m3_tracks;
      int m3_trackFitOK;
      int m3_reducedChi2;
      int m3_hitFraction_low;
      int m3_hitFraction_high;
      int m3_adacd;
      int m3_az0;
      int m3_pTk_low;
      int m3_pTk_high;
      int m3_aCotTheta;
      int m3_errCotTheta;
      int m3_errz0;

      int m4_tracks;
      int m4_trackFitOK;
      int m4_reducedChi2;
      int m4_hitFraction_low;
      int m4_hitFraction_high;
      int m4_adacd;
      int m4_az0;
      int m4_pTk_low;
      int m4_pTk_high;
      int m4_aCotTheta;
      int m4_errCotTheta;
      int m4_errz0;

      int m5_tracks;
      int m5_trackFitOK;
      int m5_reducedChi2;
      int m5_hitFraction_low;
      int m5_hitFraction_high;
      int m5_adacd;
      int m5_az0;
      int m5_pTk_low;
      int m5_pTk_high;
      int m5_aCotTheta;
      int m5_errCotTheta;
      int m5_errz0;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CHECKTRACKEFF_CHECKTRACKEFF_H */
