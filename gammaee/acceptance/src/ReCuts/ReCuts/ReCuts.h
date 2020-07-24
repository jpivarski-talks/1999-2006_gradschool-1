// -*- C++ -*-
#if !defined(RECUTS_RECUTS_H)
#define RECUTS_RECUTS_H
//
// Package:     <ReCuts>
// Module:      ReCuts
//
/**\class ReCuts ReCuts.h ReCuts/ReCuts.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Jul  6 12:17:22 EDT 2004
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

class ReCuts : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      ReCuts( void );                      // anal1 
      virtual ~ReCuts();                   // anal5 

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
      ReCuts( const ReCuts& );

      // ------------ assignment operator(s) ---------------------
      const ReCuts& operator=( const ReCuts& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ReCuts::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);
      void recurse(bool space, const MCParticle& particle);
      void summarize();

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<unsigned int> m_mode;
      int m_run;
      double m_e1;
      double m_p2;
      double m_visen;
      double m_ccen;
      double m_ntracks;
      int m_events;
      int m_cosmicEvents;
      int m_bgpEvents;
      int m_bgeEvents;
      int m_ttnumer;
      int m_ttdenom;
      int m_layerhit[16];
      int m_tracks;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* RECUTS_RECUTS_H */
