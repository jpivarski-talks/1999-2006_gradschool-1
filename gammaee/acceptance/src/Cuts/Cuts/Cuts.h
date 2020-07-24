// -*- C++ -*-
#if !defined(CUTS_CUTS_H)
#define CUTS_CUTS_H
//
// Package:     <Cuts>
// Module:      Cuts
//
/**\class Cuts Cuts.h Cuts/Cuts.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Apr 12 15:11:11 EDT 2004
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
#include "HistogramInterface/HINtuple.h"
#include "CommandPattern/Parameter.h"
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class Cuts : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_t1had, k_t1rad, k_t1el, k_t1tt,
	 k_tracks, k_visen, k_ccen,
	 k_p2, k_e1,
	 k_ci, k_wz, k_d0close, k_z0close,
	 k_run, k_ebeam, k_neue, k_q,
	 k_axial, k_stereo, k_cblo, k_cbmd,
	 k_rawtk, k_pmiss, k_tr1, k_tr2, k_trperp1, k_trperp2, k_e2,
	 k_shperp, k_shdot,
	 k_l4dec, k_l4tracks,
	 k_mctype, // k_mctrack, k_mcfid,
	 k_wpz, k_cotthp,
	 k_nbunch, k_bbunch,
	 k_cvisen, k_cccen, k_cneue,
	 k_avisen, k_accen, k_aneue,

	 kNumEntries
      };
	 
      // ------------ Constructors and destructor ----------------
      Cuts( void );                      // anal1 
      virtual ~Cuts();                   // anal5 

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
      Cuts( const Cuts& );

      // ------------ assignment operator(s) ---------------------
      const Cuts& operator=( const Cuts& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Cuts::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<DABoolean> m_triggerInfo;
      Parameter<DABoolean> m_mcInfo;
      Parameter<unsigned int> m_res;
      unsigned int m_tracks;
      unsigned int m_showers;

      HINtuple* m_ntuple;

//       HIHist1D* m_track_originUsed;
//       HIHist1D* m_track_hitfrac;
//       HIHist1D* m_track_cosTheta;
//       HIHist1D* m_track_seedredchi2;
//       HIHist1D* m_track_seedd0;
//       HIHist1D* m_track_seedz0;
//       HIHist1D* m_track_fit;
//       HIHist1D* m_track_fitAbort;
//       HIHist1D* m_track_reducedchi2;
//       HIHist1D* m_track_layerfrac_low;
//       HIHist1D* m_track_layerfrac_high;
//       HIHist1D* m_track_piond0;
//       HIHist1D* m_track_pionz;
//       HIHist1D* m_track_poeB_low;
//       HIHist1D* m_track_poeB_high;
//       HIHist1D* m_track_cotTheta;
//       HIHist1D* m_track_errcotTheta;
//       HIHist1D* m_track_errZ0;
//       HIHist1D* m_track_invcurvature;
//       HIHist1D* m_track_nullerrmat;
//       HIHist1D* m_shower_status;
//       HIHist1D* m_shower_energy;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CUTS_CUTS_H */
