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
// Created:     Fri Mar  5 11:36:58 EST 2004
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
	 k_d0Close,
	 k_z0Close,
	 k_eBeam,
	 k_ntracks,
	 k_e1,
	 k_e2,
	 k_p1,
	 k_p2,
	 k_pmiss,
	 k_pnext,
	 k_pfound,
	 k_shxy,
	 k_shz,
	 k_shphi1,
	 k_shphi2,
	 k_shcosth1,
	 k_shcosth2,
	 k_ephalf,
	 k_epwhole,
	 k_epdouble,
	 k_trxy,
	 k_trz,
	 k_d0miss,
	 k_z0miss,
	 k_trphi1,
	 k_trphi2,
	 k_trcosth1,
	 k_trcosth2,
	 k_trperp1,
	 k_trperp2,
	 k_trperp3,
	 k_trperp4,

	 k_rawntracks,
	 k_visen,
	 k_ccen,
	 k_neue,
	 k_q,
	 k_wrphi,
	 k_wz,
	 k_pass,
	 k_trigger,
	 k_trax,
	 
	 k_twopions,
	 k_pi1x,
	 k_pi1y,
	 k_pi1z,
	 k_pi2x,
	 k_pi2y,
	 k_pi2z,

	 kNumEntries
      };

      enum {
	 kTriggerHadron,
	 kTriggerRadTau,
	 kTriggerElTrack,
	 kTrigger4,
	 kTrAxial,
	 kTrStereo,
	 kCBLo,
	 kCBMid,

	 kNumTriggerEntries
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

      Parameter<DABoolean> m_usingQQ;
      Parameter<DABoolean> m_usingEvtGen;
      Parameter<DABoolean> m_wantLeptons;
      Parameter<DABoolean> m_lookForStupid;

      HINtuple* m_ntuple;
      HINtuple* m_ntupleBoth;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CUTS_CUTS_H */
