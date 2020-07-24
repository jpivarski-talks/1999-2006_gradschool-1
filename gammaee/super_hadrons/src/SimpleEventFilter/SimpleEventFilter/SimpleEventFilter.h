// -*- C++ -*-
#if !defined(SIMPLEEVENTFILTER_SIMPLEEVENTFILTER_H)
#define SIMPLEEVENTFILTER_SIMPLEEVENTFILTER_H
//
// Package:     <SimpleEventFilter>
// Module:      SimpleEventFilter
//
/**\class SimpleEventFilter SimpleEventFilter.h SimpleEventFilter/SimpleEventFilter.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Mar  3 23:00:28 EST 2003
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
#include "CommandPattern/Parameter.h"

// forward declarations

class SimpleEventFilter : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      SimpleEventFilter( void );                      // anal1 
      virtual ~SimpleEventFilter();                   // anal5 

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
      SimpleEventFilter( const SimpleEventFilter& );

      // ------------ assignment operator(s) ---------------------
      const SimpleEventFilter& operator=( const SimpleEventFilter& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (SimpleEventFilter::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<double> m_start;
      Parameter<double> m_end;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* SIMPLEEVENTFILTER_SIMPLEEVENTFILTER_H */
