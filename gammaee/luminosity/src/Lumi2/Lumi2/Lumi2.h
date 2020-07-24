// -*- C++ -*-
#if !defined(LUMI2_LUMI2_H)
#define LUMI2_LUMI2_H
//
// Package:     <Lumi2>
// Module:      Lumi2
//
/**\class Lumi2 Lumi2.h Lumi2/Lumi2.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Mar  7 14:44:01 EST 2005
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

class Lumi2 : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_l1tt, k_l1rt, k_l1el, k_l1bb, k_l1eb, k_rawtk, k_ntrack, k_ebeam,
	 k_epe1, k_epe2, k_epp1, k_epp2, k_ccen, k_neue, k_chen, k_l4dec,
	 k_sh1e, k_sh1cos, k_sh1phi, k_sh1e925, k_sh1wide, k_sh1mat, k_sh1ang,
	 k_sh2e, k_sh2cos, k_sh2phi, k_sh2e925, k_sh2wide, k_sh2mat, k_sh2ang,
	 k_sh3e, k_sh3cos, k_sh3phi, k_sh3e925, k_sh3wide, k_sh3mat, k_sh3ang,
	 k_sh4e, k_sh4cos, k_sh4phi, k_sh4e925, k_sh4wide, k_sh4mat, k_sh4ang,
	 k_m12, k_m123, k_m1234,
	 k_hits,
	 k_tr1p, k_tr1cos, k_tr1phi,
	 k_tr2p, k_tr2cos, k_tr2phi,
	 k_tr3p, k_tr3cos, k_tr3phi,
	 k_tr4p, k_tr4cos, k_tr4phi,
	 k_c12r, k_c12z, k_c12z2, k_c12z3,
	 k_c13r, k_c13z, k_c13z2, k_c13z3,
	 k_c14r, k_c14z, k_c14z2, k_c14z3,
	 k_c23r, k_c23z, k_c23z2, k_c23z3,
	 k_c24r, k_c24z, k_c24z2, k_c24z3,
	 k_c34r, k_c34z, k_c34z2, k_c34z3,
	 k_nvxfit,
	 k_v1chi, k_v1x, k_v1y, k_v1z,
	 k_v2chi, k_v2x, k_v2y, k_v2z,
	 k_v3chi, k_v3x, k_v3y, k_v3z,
	 k_v4chi, k_v4x, k_v4y, k_v4z,
	 k_pmiss, k_d0close, k_z0close, k_myntk, k_run,
	 
	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      Lumi2( void );                      // anal1 
      virtual ~Lumi2();                   // anal5 

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
      Lumi2( const Lumi2& );

      // ------------ assignment operator(s) ---------------------
      const Lumi2& operator=( const Lumi2& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Lumi2::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;
      Parameter<DABoolean> m_haveL4;
      Parameter<DABoolean> m_smearOrigin;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* LUMI2_LUMI2_H */
