// -*- C++ -*-
#if !defined(WIERDVISENTRIGGER_WIERDVISENTRIGGER_H)
#define WIERDVISENTRIGGER_WIERDVISENTRIGGER_H
//
// Package:     <WierdVisenTrigger>
// Module:      WierdVisenTrigger
//
/**\class WierdVisenTrigger WierdVisenTrigger.h WierdVisenTrigger/WierdVisenTrigger.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Aug  9 16:34:01 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "CommandPattern/Parameter.h"
#include "HistogramInterface/HistogramPackage.h"
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class WierdVisenTrigger : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      WierdVisenTrigger( void );                      // anal1 
      virtual ~WierdVisenTrigger();                   // anal5 

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
      WierdVisenTrigger( const WierdVisenTrigger& );

      // ------------ assignment operator(s) ---------------------
      const WierdVisenTrigger& operator=( const WierdVisenTrigger& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (WierdVisenTrigger::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<unsigned int> m_res;
      Parameter<DABoolean> m_evtgen;
      HIHist1D* m_e1_gggam;
      HIHist1D* m_gggam;
      HIHist1D* m_other_side;
      HIHist2D* m_gggam_vs_other_side;

      int m_passing;
      int m_total;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* WIERDVISENTRIGGER_WIERDVISENTRIGGER_H */
