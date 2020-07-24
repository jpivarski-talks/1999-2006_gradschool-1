// -*- C++ -*-
#if !defined(CCENFAILURESFILTER_CCENFAILURESFILTER_H)
#define CCENFAILURESFILTER_CCENFAILURESFILTER_H
//
// Package:     <CcenFailuresFilter>
// Module:      CcenFailuresFilter
//
/**\class CcenFailuresFilter CcenFailuresFilter.h CcenFailuresFilter/CcenFailuresFilter.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Jul 26 17:01:24 EDT 2004
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

class CcenFailuresFilter : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      CcenFailuresFilter( void );                      // anal1 
      virtual ~CcenFailuresFilter();                   // anal5 

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
      CcenFailuresFilter( const CcenFailuresFilter& );

      // ------------ assignment operator(s) ---------------------
      const CcenFailuresFilter& operator=( const CcenFailuresFilter& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (CcenFailuresFilter::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<double> m_ebeam;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CCENFAILURESFILTER_CCENFAILURESFILTER_H */
