// -*- C++ -*-
#if !defined(UPSILONGAMMAEECASCADESPROC_UPSILONGAMMAEECASCADESPROC_H)
#define UPSILONGAMMAEECASCADESPROC_UPSILONGAMMAEECASCADESPROC_H
//
// Package:     <UpsilonGammaEECascadesProc>
// Module:      UpsilonGammaEECascadesProc
//
/**\class UpsilonGammaEECascadesProc UpsilonGammaEECascadesProc.h UpsilonGammaEECascadesProc/UpsilonGammaEECascadesProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue May 17 19:49:06 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

// I PROMISE that the changes to this file after 12:04 PM 23 May 2005
// and before 4:42 PM 24 May 2005 ONLY AFFECT MONTE CARLO!  Therefore,
// the DATA that was ntupled before the last changes are NOT OUT OF DATE.

// system include files

// user include files
#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"
#include "HistogramInterface/HINtuple.h"
#include "KinematicTrajectory/KTHelix.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class UpsilonGammaEECascadesProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_m, k_x, k_y, k_z, k_zsep, k_p1x, k_p1y, k_p1z, k_p2x, k_p2y, k_p2z,
	 k_tracks, k_chen, k_neue, k_cneue, k_fneue, k_ccen, k_cccen, k_fccen,
	 k_p1, k_p2, k_eop1, k_eop2,
	 k_d0close, k_z0close, k_wz,
	 k_thad, k_trad, k_tel,
	 k_axish, k_sterish, k_cbloish, k_mctag,
	 k_axial, k_cblo, k_cbmd,
	 k_cblo1, k_cblo2, k_l4tracks, k_ebeam, k_tt,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      UpsilonGammaEECascadesProc( void );                      // anal1 
      virtual ~UpsilonGammaEECascadesProc();                   // anal5 

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
      UpsilonGammaEECascadesProc( const UpsilonGammaEECascadesProc& );

      // ------------ assignment operator(s) ---------------------
      const UpsilonGammaEECascadesProc& operator=( const UpsilonGammaEECascadesProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (UpsilonGammaEECascadesProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      bool calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      bool arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<DABoolean> m_twotrack;

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* UPSILONGAMMAEECASCADESPROC_UPSILONGAMMAEECASCADESPROC_H */
