// -*- C++ -*-
#if !defined(PRINTOUTPROC_PRINTOUTPROC_H)
#define PRINTOUTPROC_PRINTOUTPROC_H
//
// Package:     <PrintOutProc>
// Module:      PrintOutProc
//
/**\class PrintOutProc PrintOutProc.h PrintOutProc/PrintOutProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Aug 26 14:23:18 EDT 2002
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
#include "HbookHistogram/HbookNtuple.h"
#include "CommandPattern/Parameter.h"
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class PrintOutProc : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      PrintOutProc( void );                      // anal1 
      virtual ~PrintOutProc();                   // anal5 

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
      PrintOutProc( const PrintOutProc& );

      // ------------ assignment operator(s) ---------------------
      const PrintOutProc& operator=( const PrintOutProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (PrintOutProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      double smallest_dca( vector< KTHelix* > helix,
			   double beam_x, double beam_y, double veto = -1. );
      double closest_intersection( vector< KTHelix* > helix,
				   double beam_x, double beam_y, double veto = -1. );
      DABoolean calc_intersection( double& x, double& y, double& sigx, double& sigy,
				   KTHelix& a, KTHelix& b, DABoolean calc_uncerts = false );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PRINTOUTPROC_PRINTOUTPROC_H */
