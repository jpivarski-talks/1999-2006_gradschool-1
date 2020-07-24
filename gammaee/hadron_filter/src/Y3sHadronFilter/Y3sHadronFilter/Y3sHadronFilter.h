// -*- C++ -*-
#if !defined(Y3SHADRONFILTER_Y3SHADRONFILTER_H)
#define Y3SHADRONFILTER_Y3SHADRONFILTER_H
//
// Package:     <Y3sHadronFilter>
// Module:      Y3sHadronFilter
//
/**\class Y3sHadronFilter Y3sHadronFilter.h Y3sHadronFilter/Y3sHadronFilter.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim McCann
// Created:     Tue Jan 15 12:48:50 EST 2002
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

#include "HbookHistogram/HbookNtuple.h"

// forward declarations

class Y3sHadronFilter : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      Y3sHadronFilter( void );                      // anal1 
      virtual ~Y3sHadronFilter();                   // anal5 

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
      Y3sHadronFilter( const Y3sHadronFilter& );

      // ------------ assignment operator(s) ---------------------
      const Y3sHadronFilter& operator=( const Y3sHadronFilter& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Y3sHadronFilter::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter< double > m_beamspot_x;
      Parameter< double > m_beamspot_y;

      HINtuple* m_eventvars;
      HINtuple* m_twotrack_eventvars;

      HIHist1D* m_hist_showers;
      HIHist1D* m_hist_unmatched_showers;
      HIHist1D* m_hist_tracks;
      HIHist1D* m_hist_showers_and_tracks;
      HIHist1D* m_hist_unmatched_showers_and_tracks;
      HIHist1D* m_hist_shower_mass;
      HIHist1D* m_hist_shower_energy;
      HIHist1D* m_hist_charge;
      HIHist2D* m_hist_charge_vs_tracks;
      HIHist2D* m_hist_momentum_xy;
      HIHist2D* m_hist_twotrack_momentum_xy;
      HIHist1D* m_hist_momentum_z;
      HIHist1D* m_hist_twotrack_momentum_z;
      HIHist1D* m_hist_energy;
      HIHist1D* m_hist_track_momentum;
      HIHist1D* m_hist_track_d0;
      HIHist2D* m_hist_track_d0_vs_phi0;
      HIHist1D* m_hist_track_z0;
      HIHist2D* m_hist_twotrack_Ep;
      HIHist2D* m_hist_twotrack_dpthmu;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* Y3SHADRONFILTER_Y3SHADRONFILTER_H */
