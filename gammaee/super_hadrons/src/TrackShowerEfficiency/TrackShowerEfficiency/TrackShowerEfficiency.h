// -*- C++ -*-
#if !defined(TRACKSHOWEREFFICIENCY_TRACKSHOWEREFFICIENCY_H)
#define TRACKSHOWEREFFICIENCY_TRACKSHOWEREFFICIENCY_H
//
// Package:     <TrackShowerEfficiency>
// Module:      TrackShowerEfficiency
//
/**\class TrackShowerEfficiency TrackShowerEfficiency.h TrackShowerEfficiency/TrackShowerEfficiency.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Apr 28 15:28:41 EDT 2003
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

class TrackShowerEfficiency : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      TrackShowerEfficiency( void );                      // anal1 
      virtual ~TrackShowerEfficiency();                   // anal5 

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
      TrackShowerEfficiency( const TrackShowerEfficiency& );

      // ------------ assignment operator(s) ---------------------
      const TrackShowerEfficiency& operator=( const TrackShowerEfficiency& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TrackShowerEfficiency::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TRACKSHOWEREFFICIENCY_TRACKSHOWEREFFICIENCY_H */
