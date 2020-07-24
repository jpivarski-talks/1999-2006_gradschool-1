// -*- C++ -*-
#if !defined(WHATSWRONG_WHATSWRONG_H)
#define WHATSWRONG_WHATSWRONG_H
//
// Package:     <WhatsWrong>
// Module:      WhatsWrong
//
/**\class WhatsWrong WhatsWrong.h WhatsWrong/WhatsWrong.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Apr 19 10:04:15 EDT 2005
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

class WhatsWrong : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

//       enum {
// 	 k_t1had, k_t1rad, k_t1el, k_t1bb,
// 	 k_d0close, k_e1, k_p2, k_wz, k_z0close,
// 	 k_visen, k_tracks, k_l4dec, k_ccen, k_ebeam,
// 	 k_etwo, k_westphi, k_eastphi, k_cott, k_westcot,
// 	 k_tfit, k_tchi, k_thit, k_td0, k_tz0, k_tp, k_tcot, k_tert, k_terz, k_shot,
// 	 kNumEntries
//       };

//       enum {
// 	 k_tfit, k_tchi, k_thit, k_td0, k_tz0, k_tp, k_tcot, k_tert, k_terz,
// 	 kNumEntries
//       };

//       enum {
// 	 k_shot, k_senergy, k_stheta, k_sphi,
// 	 kNumEntries2
//       };

      enum {
	 k_t1had,
	 k_t1rad,
	 k_t1el,
	 k_t1bb,
	 k_d0close,
	 k_z0close,
	 k_wz,
	 k_e1,
	 k_e2,
	 k_u1,
	 k_p1,
	 k_p2,
	 k_pmiss,
	 k_pemiss,
	 k_visen,
	 k_cvisen,
	 k_tracks,
	 k_l4dec,
	 k_ccen,
	 k_ebeam,
	 k_westphi,
	 k_eastphi,
	 k_cott,
	 k_westcot,
	 k_fvisen,
	 k_fccen,
	 k_fe1,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      WhatsWrong( void );                      // anal1 
      virtual ~WhatsWrong();                   // anal5 

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
      WhatsWrong( const WhatsWrong& );

      // ------------ assignment operator(s) ---------------------
      const WhatsWrong& operator=( const WhatsWrong& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (WhatsWrong::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------


      // ------------ data members -------------------------------

      HINtuple *m_ntuple;
      HINtuple *m_ntuple2;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* WHATSWRONG_WHATSWRONG_H */
