// -*- C++ -*-
#if !defined(LOOKFORWIERDTRIGGER_LOOKFORWIERDTRIGGER_H)
#define LOOKFORWIERDTRIGGER_LOOKFORWIERDTRIGGER_H
//
// Package:     <LookForWierdTrigger>
// Module:      LookForWierdTrigger
//
/**\class LookForWierdTrigger LookForWierdTrigger.h LookForWierdTrigger/LookForWierdTrigger.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Jun  7 11:57:04 EDT 2004
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

class LookForWierdTrigger : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      LookForWierdTrigger( void );                      // anal1 
      virtual ~LookForWierdTrigger();                   // anal5 

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
      LookForWierdTrigger( const LookForWierdTrigger& );

      // ------------ assignment operator(s) ---------------------
      const LookForWierdTrigger& operator=( const LookForWierdTrigger& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (LookForWierdTrigger::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      void summarize();

      // ------------ data members -------------------------------

      int m_run;
      int m_total;
      int m_03;
      int m_075;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* LOOKFORWIERDTRIGGER_LOOKFORWIERDTRIGGER_H */
