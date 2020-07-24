// -*- C++ -*-
#if !defined(TUNEBEAMSPOT_TUNEBEAMSPOT_H)
#define TUNEBEAMSPOT_TUNEBEAMSPOT_H
//
// Package:     <TuneBeamspot>
// Module:      TuneBeamspot
//
/**\class TuneBeamspot TuneBeamspot.h TuneBeamspot/TuneBeamspot.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Apr  6 17:47:33 EDT 2005
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

class TuneBeamspot : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      TuneBeamspot( void );                      // anal1 
      virtual ~TuneBeamspot();                   // anal5 

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
      TuneBeamspot( const TuneBeamspot& );

      // ------------ assignment operator(s) ---------------------
      const TuneBeamspot& operator=( const TuneBeamspot& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TuneBeamspot::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TUNEBEAMSPOT_TUNEBEAMSPOT_H */
