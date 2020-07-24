// -*- C++ -*-
#if !defined(EVENTNUMBER_EVENTNUMBER_H)
#define EVENTNUMBER_EVENTNUMBER_H
//
// Package:     <EventNumber>
// Module:      EventNumber
//
/**\class EventNumber EventNumber.h EventNumber/EventNumber.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Mar 10 13:41:46 EST 2004
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

class EventNumber : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      EventNumber( void );                      // anal1 
      virtual ~EventNumber();                   // anal5 

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
      EventNumber( const EventNumber& );

      // ------------ assignment operator(s) ---------------------
      const EventNumber& operator=( const EventNumber& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (EventNumber::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* EVENTNUMBER_EVENTNUMBER_H */
