// -*- C++ -*-
#if !defined(HADRONFILTERPROC_HADRONFILTERPROC_H)
#define HADRONFILTERPROC_HADRONFILTERPROC_H
//
// Package:     <HadronFilterProc>
// Module:      HadronFilterProc
//
/**\class HadronFilterProc HadronFilterProc.h HadronFilterProc/HadronFilterProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Oct 16 11:23:37 EDT 2002
// $Id: HadronFilterProc.h,v 1.2 2002/10/23 15:37:49 mccann Exp $
//
// Revision history
//
// $Log: HadronFilterProc.h,v $
// Revision 1.2  2002/10/23 15:37:49  mccann
// Replaced weighted z0 cut with a weighted z-of-intersection cut, which gains a factor of two in tightness. I also loosened closest_intersection cut because the 3mm vs 5mm gains little hadron/beamgas.
//
// Revision 1.1.1.1  2002/10/16 17:40:04  mccann
// A processor that uses tracking to filter out beam wall/beam gas.
//
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"
//  #include "HbookHistogram/HbookNtuple.h"
#include "CommandPattern/Parameter.h"
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class HadronFilterProc : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      HadronFilterProc( void );                      // anal1 
      virtual ~HadronFilterProc();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      //virtual ActionBase::ActionResult endRun( Frame& iFrame);
      //virtual ActionBase::ActionResult geometry( Frame& iFrame);
      //virtual ActionBase::ActionResult hardware( Frame& iFrame);
      //virtual ActionBase::ActionResult user( Frame& iFrame);

      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      HadronFilterProc( const HadronFilterProc& );

      // ------------ assignment operator(s) ---------------------
      const HadronFilterProc& operator=( const HadronFilterProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (HadronFilterProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
				   KTHelix& a, KTHelix& b );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter< double > m_closestIntersectionCut;
      Parameter< double > m_weightedZ0Cut;
      Parameter< double > m_neutralEnergyCut;
      Parameter< double > m_weightedCIZCut;
      Parameter< DABoolean > m_explicitBeamSpot;
      Parameter< double > m_beamX;
      Parameter< double > m_beamY;
      Parameter< double > m_beamZ;
      int m_passed;
      int m_total;
      double m_beam_x;
      double m_beam_y;
      double m_beam_z;

      HIHist1D* m_hist_closest_inter;
      HIHist1D* m_histclose_closest_inter;
      HIHist1D* m_hist_weighted_z0;
      HIHist1D* m_histclose_weighted_z0;
      HIHist1D* m_hist_neutral_energy;
      HIHist1D* m_histclose_neutral_energy;
      HIHist1D* m_hist_weighted_ciz;
      HIHist1D* m_histclose_weighted_ciz;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* HADRONFILTERPROC_HADRONFILTERPROC_H */
