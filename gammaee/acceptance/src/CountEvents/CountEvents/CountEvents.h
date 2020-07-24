// -*- C++ -*-
#if !defined(COUNTEVENTS_COUNTEVENTS_H)
#define COUNTEVENTS_COUNTEVENTS_H
//
// Package:     <CountEvents>
// Module:      CountEvents
//
/**\class CountEvents CountEvents.h CountEvents/CountEvents.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Jul 14 16:37:23 EDT 2004
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
#include "MCInfo/MCDecayTree/MCParticle.h"

// forward declarations

class CountEvents : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      CountEvents( void );                      // anal1 
      virtual ~CountEvents();                   // anal5 

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
      CountEvents( const CountEvents& );

      // ------------ assignment operator(s) ---------------------
      const CountEvents& operator=( const CountEvents& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (CountEvents::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_goodEvents;
      int m_cosmicEvents;
      int m_bgpEvents;
      int m_bgeEvents;

      Parameter<unsigned int> m_run;

      HIHist1D* m_d0close;
      HIHist1D* m_e1;
      HIHist1D* m_p2;
      HIHist1D* m_wz;
      HIHist1D* m_z0close;
      HIHist1D* m_visen;
      HIHist1D* m_tracks;
      HIHist1D* m_ccen;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* COUNTEVENTS_COUNTEVENTS_H */
