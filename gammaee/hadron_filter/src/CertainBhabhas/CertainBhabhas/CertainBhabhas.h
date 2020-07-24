// -*- C++ -*-
#if !defined(CERTAINBHABHAS_CERTAINBHABHAS_H)
#define CERTAINBHABHAS_CERTAINBHABHAS_H
//
// Package:     <CertainBhabhas>
// Module:      CertainBhabhas
//
/**\class CertainBhabhas CertainBhabhas.h CertainBhabhas/CertainBhabhas.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim McCann
// Created:     Thu Jun  6 14:42:51 EDT 2002
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

class CertainBhabhas : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      CertainBhabhas( void );                      // anal1 
      virtual ~CertainBhabhas();                   // anal5 

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
      CertainBhabhas( const CertainBhabhas& );

      // ------------ assignment operator(s) ---------------------
      const CertainBhabhas& operator=( const CertainBhabhas& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (CertainBhabhas::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HIHist1D* m_showers_energy;
      HIHist1D* m_showers_momentum;
      HIHist1D* m_track_momentum;
      HIHist1D* m_weighted_d0;
      HIHist1D* m_weighted_z0;
      HIHist1D* m_bunchwt;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CERTAINBHABHAS_CERTAINBHABHAS_H */
