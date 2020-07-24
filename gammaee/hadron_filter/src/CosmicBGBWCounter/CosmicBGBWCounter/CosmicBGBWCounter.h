// -*- C++ -*-
#if !defined(COSMICBGBWCOUNTER_COSMICBGBWCOUNTER_H)
#define COSMICBGBWCOUNTER_COSMICBGBWCOUNTER_H
//
// Package:     <CosmicBGBWCounter>
// Module:      CosmicBGBWCounter
//
/**\class CosmicBGBWCounter CosmicBGBWCounter.h CosmicBGBWCounter/CosmicBGBWCounter.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Sep  4 15:19:30 EDT 2002
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

// forward declarations

class CosmicBGBWCounter : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      CosmicBGBWCounter( void );                      // anal1 
      virtual ~CosmicBGBWCounter();                   // anal5 

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
      CosmicBGBWCounter( const CosmicBGBWCounter& );

      // ------------ assignment operator(s) ---------------------
      const CosmicBGBWCounter& operator=( const CosmicBGBWCounter& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (CosmicBGBWCounter::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* COSMICBGBWCOUNTER_COSMICBGBWCOUNTER_H */
