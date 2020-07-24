// -*- C++ -*-
#if !defined(TRACKEFFICIENCY_TRACKEFFICIENCY_H)
#define TRACKEFFICIENCY_TRACKEFFICIENCY_H
//
// Package:     <TrackEfficiency>
// Module:      TrackEfficiency
//
/**\class TrackEfficiency TrackEfficiency.h TrackEfficiency/TrackEfficiency.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Jul  8 13:04:39 EDT 2003
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

// forward declarations

class TrackEfficiency : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kRun,
	 kEvent,
	 kFit,
	 kChi2,
	 kDOF,
	 kHitsExpected,
	 kLayersSeen,
	 kD0,
	 kZ0,
	 kMomentum,
	 kCotTheta,
	 kErrCotTheta,
	 kErrZ0,
	 kCurvature,
	 kPhi0,
	 kMCTag,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      TrackEfficiency( void );                      // anal1 
      virtual ~TrackEfficiency();                   // anal5 

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
      TrackEfficiency( const TrackEfficiency& );

      // ------------ assignment operator(s) ---------------------
      const TrackEfficiency& operator=( const TrackEfficiency& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TrackEfficiency::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<DABoolean> m_isMC;
      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TRACKEFFICIENCY_TRACKEFFICIENCY_H */
