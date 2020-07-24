// -*- C++ -*-
#if !defined(SHOWERSTUDY_SHOWERSTUDY_H)
#define SHOWERSTUDY_SHOWERSTUDY_H
//
// Package:     <ShowerStudy>
// Module:      ShowerStudy
//
/**\class ShowerStudy ShowerStudy.h ShowerStudy/ShowerStudy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu Aug 12 12:47:43 EDT 2004
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

// forward declarations

class ShowerStudy : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_trigger, k_ebeam, k_p1, k_p2, k_e1, k_e2,
	 k_visen, k_neue, k_tracks, k_d0close, k_wz, k_z0close, k_showers, k_first,
	 k_ok, k_energy, k_theta, k_phi, k_e9oe25,
	 k_m_eop, k_m_dist, k_m_p, k_m_d0, k_m_z0,
	 k_cellid,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      ShowerStudy( void );                      // anal1 
      virtual ~ShowerStudy();                   // anal5 

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
      ShowerStudy( const ShowerStudy& );

      // ------------ assignment operator(s) ---------------------
      const ShowerStudy& operator=( const ShowerStudy& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ShowerStudy::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* SHOWERSTUDY_SHOWERSTUDY_H */
