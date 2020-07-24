// -*- C++ -*-
#if !defined(LOOKATRAWTRIGGER_LOOKATRAWTRIGGER_H)
#define LOOKATRAWTRIGGER_LOOKATRAWTRIGGER_H
//
// Package:     <LookAtRawTrigger>
// Module:      LookAtRawTrigger
//
/**\class LookAtRawTrigger LookAtRawTrigger.h LookAtRawTrigger/LookAtRawTrigger.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Feb 17 17:33:57 EST 2004
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

class LookAtRawTrigger : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      LookAtRawTrigger( void );                      // anal1 
      virtual ~LookAtRawTrigger();                   // anal5 

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
      LookAtRawTrigger( const LookAtRawTrigger& );

      // ------------ assignment operator(s) ---------------------
      const LookAtRawTrigger& operator=( const LookAtRawTrigger& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (LookAtRawTrigger::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* LOOKATRAWTRIGGER_LOOKATRAWTRIGGER_H */
