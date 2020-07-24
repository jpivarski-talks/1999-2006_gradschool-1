// -*- C++ -*-
#if !defined(BIGGESTSYSTEMATIC_BIGGESTSYSTEMATIC_H)
#define BIGGESTSYSTEMATIC_BIGGESTSYSTEMATIC_H
//
// Package:     <BiggestSystematic>
// Module:      BiggestSystematic
//
/**\class BiggestSystematic BiggestSystematic.h BiggestSystematic/BiggestSystematic.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Nov 30 16:20:36 EST 2004
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
#include "KinematicTrajectory/KTHelix.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class BiggestSystematic : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_rawtk, k_tracks, k_pmiss, k_tr1, k_tr2, k_visen, k_ccen, k_d0close, k_z0close,
	 k_t1px, k_t1py, k_t1pz, k_t1e,
	 k_t2px, k_t2py, k_t2pz, k_t2e,
	 k_t3px, k_t3py, k_t3pz, k_t3e,
	 k_t4px, k_t4py, k_t4pz, k_t4e,
	 k_u1px, k_u1py, k_u1pz, k_u1e,
	 k_u2px, k_u2py, k_u2pz, k_u2e,
	 k_u3px, k_u3py, k_u3pz, k_u3e,
	 k_u4px, k_u4py, k_u4pz, k_u4e,
	 k_neue, k_vecpx, k_vecpy, k_vecpz, k_scapt, k_scapz, k_goodtk,
	 k_trig, k_wz, k_e1, k_p2, k_tttrig, k_mctype,
	 k_mcinv, k_mccas, k_mult,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      BiggestSystematic( void );                      // anal1 
      virtual ~BiggestSystematic();                   // anal5 

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
      BiggestSystematic( const BiggestSystematic& );

      // ------------ assignment operator(s) ---------------------
      const BiggestSystematic& operator=( const BiggestSystematic& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (BiggestSystematic::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<unsigned int> m_mc;
      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* BIGGESTSYSTEMATIC_BIGGESTSYSTEMATIC_H */
