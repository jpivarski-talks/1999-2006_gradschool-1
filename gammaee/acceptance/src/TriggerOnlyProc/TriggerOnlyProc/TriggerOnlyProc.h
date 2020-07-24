// -*- C++ -*-
#if !defined(TRIGGERONLYPROC_TRIGGERONLYPROC_H)
#define TRIGGERONLYPROC_TRIGGERONLYPROC_H
//
// Package:     <TriggerOnlyProc>
// Module:      TriggerOnlyProc
//
/**\class TriggerOnlyProc TriggerOnlyProc.h TriggerOnlyProc/TriggerOnlyProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu May 20 02:31:16 EDT 2004
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
#include "HistogramInterface/HINtuple.h"

// forward declarations

class TriggerOnlyProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_t1had,
	 k_t1rad,
	 k_t1el,
	 k_t1tt,
	 k_axial,
	 k_stereo,
	 k_cblo,
	 k_cbmd,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      TriggerOnlyProc( void );                      // anal1 
      virtual ~TriggerOnlyProc();                   // anal5 

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
      TriggerOnlyProc( const TriggerOnlyProc& );

      // ------------ assignment operator(s) ---------------------
      const TriggerOnlyProc& operator=( const TriggerOnlyProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TriggerOnlyProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TRIGGERONLYPROC_TRIGGERONLYPROC_H */
