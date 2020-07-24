// -*- C++ -*-
#if !defined(TRIGGERSIMULATOR_TRIGGERSIMULATOR_H)
#define TRIGGERSIMULATOR_TRIGGERSIMULATOR_H
//
// Package:     <TriggerSimulator>
// Module:      TriggerSimulator
//
/**\class TriggerSimulator TriggerSimulator.h TriggerSimulator/TriggerSimulator.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Apr 23 13:51:01 EDT 2003
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
#include "Experiment/report.h"

// forward declarations

class TriggerSimulator : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      TriggerSimulator( void );                      // anal1 
      virtual ~TriggerSimulator();                   // anal5 

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
      TriggerSimulator( const TriggerSimulator& );

      // ------------ assignment operator(s) ---------------------
      const TriggerSimulator& operator=( const TriggerSimulator& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TriggerSimulator::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      void printout(Severity severity);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_total;
      int m_passMe;
      int m_passOfficial;
      int m_disagreements;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TRIGGERSIMULATOR_TRIGGERSIMULATOR_H */
