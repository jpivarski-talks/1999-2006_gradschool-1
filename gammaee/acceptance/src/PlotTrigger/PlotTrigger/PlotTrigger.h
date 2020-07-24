// -*- C++ -*-
#if !defined(PLOTTRIGGER_PLOTTRIGGER_H)
#define PLOTTRIGGER_PLOTTRIGGER_H
//
// Package:     <PlotTrigger>
// Module:      PlotTrigger
//
/**\class PlotTrigger PlotTrigger.h PlotTrigger/PlotTrigger.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Apr  5 14:28:55 EDT 2004
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

// forward declarations

class PlotTrigger : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      PlotTrigger( void );                      // anal1 
      virtual ~PlotTrigger();                   // anal5 

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
      PlotTrigger( const PlotTrigger& );

      // ------------ assignment operator(s) ---------------------
      const PlotTrigger& operator=( const PlotTrigger& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (PlotTrigger::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HIHist1D* m_axial;
      HIHist1D* m_stereo;
      HIHist1D* m_cblo;
      HIHist1D* m_cbmd;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PLOTTRIGGER_PLOTTRIGGER_H */
