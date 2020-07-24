// -*- C++ -*-
#if !defined(LASTEVENT_LASTEVENT_H)
#define LASTEVENT_LASTEVENT_H
//
// Package:     <LastEvent>
// Module:      LastEvent
//
/**\class LastEvent LastEvent.h LastEvent/LastEvent.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Jun  9 13:46:28 EDT 2004
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

class LastEvent : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      LastEvent( void );                      // anal1 
      virtual ~LastEvent();                   // anal5 

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
      LastEvent( const LastEvent& );

      // ------------ assignment operator(s) ---------------------
      const LastEvent& operator=( const LastEvent& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (LastEvent::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_run;
      int m_number;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* LASTEVENT_LASTEVENT_H */
