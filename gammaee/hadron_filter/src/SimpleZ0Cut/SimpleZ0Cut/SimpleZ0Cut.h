// -*- C++ -*-
#if !defined(SIMPLEZ0CUT_SIMPLEZ0CUT_H)
#define SIMPLEZ0CUT_SIMPLEZ0CUT_H
//
// Package:     <SimpleZ0Cut>
// Module:      SimpleZ0Cut
//
/**\class SimpleZ0Cut SimpleZ0Cut.h SimpleZ0Cut/SimpleZ0Cut.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim McCann
// Created:     Mon Mar 25 09:42:08 EST 2002
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

class SimpleZ0Cut : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      SimpleZ0Cut( void );                      // anal1 
      virtual ~SimpleZ0Cut();                   // anal5 

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
      SimpleZ0Cut( const SimpleZ0Cut& );

      // ------------ assignment operator(s) ---------------------
      const SimpleZ0Cut& operator=( const SimpleZ0Cut& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (SimpleZ0Cut::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_bhabhas;
      int m_gamgams;
      int m_hadrons;

      HIHist1D* m_z0;
      HIHist1D* m_event_z0;
      HIHist1D* m_norm_event_z0;
      HIHist1D* m_type;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* SIMPLEZ0CUT_SIMPLEZ0CUT_H */
