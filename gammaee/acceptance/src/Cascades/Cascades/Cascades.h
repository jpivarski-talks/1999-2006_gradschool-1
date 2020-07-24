// -*- C++ -*-
#if !defined(CASCADES_CASCADES_H)
#define CASCADES_CASCADES_H
//
// Package:     <Cascades>
// Module:      Cascades
//
/**\class Cascades Cascades.h Cascades/Cascades.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Apr  6 13:37:00 EDT 2004
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

class Cascades : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_mass, // k_ahits1, k_ahits2, k_shits1, k_shits2,
	 k_p1x, k_p1y, k_p1z,
	 k_p2x, k_p2y, k_p2z,
//	 k_photon, k_e9e25, k_e1e9,
	 k_she1, k_she2,
//	 k_dist1, k_dist2,
	 k_tre1, k_tre2,
	 k_tracks, k_visen, k_ccen,
	 k_p2, k_p2drop, k_e1, k_e1drop,
//	 k_ci, k_cidrop, k_wz, k_wzdrop,
	 k_run, k_ebeam, k_neue, k_q,
	 k_hadron, k_radtau, k_eltrack, k_twotrack,
//	 k_axial, k_stereo, k_cblo, k_cbmd,
	 k_rawtk, k_pmiss, k_tr1, k_tr2, k_trperp1, k_trperp2, k_e2,
//	 k_l4dec, k_l4tracks,
//	 k_mcpipx, k_mcpipy, k_mcpipz, k_mcpimx, k_mcpimy, k_mcpimz, k_mcupsx, k_mcupsy, k_mcupsz, 
//	 k_mctype,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      Cascades( void );                      // anal1 
      virtual ~Cascades();                   // anal5 

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
      Cascades( const Cascades& );

      // ------------ assignment operator(s) ---------------------
      const Cascades& operator=( const Cascades& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Cascades::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

//       Parameter<DABoolean> m_triggerInfo;
//       Parameter<DABoolean> m_mcInfo;
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

#endif /* CASCADES_CASCADES_H */
