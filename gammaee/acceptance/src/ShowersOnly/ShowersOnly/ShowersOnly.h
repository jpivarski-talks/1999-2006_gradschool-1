// -*- C++ -*-
#if !defined(SHOWERSONLY_SHOWERSONLY_H)
#define SHOWERSONLY_SHOWERSONLY_H
//
// Package:     <ShowersOnly>
// Module:      ShowersOnly
//
/**\class ShowersOnly ShowersOnly.h ShowersOnly/ShowersOnly.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri May 21 10:28:57 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "CommandPattern/Parameter.h"
#include "HistogramInterface/HistogramPackage.h"
#include "HistogramInterface/HINtuple.h"

// forward declarations

class ShowersOnly : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_t1had, k_t1rad, k_t1el, k_t1tt,
	 k_tracks, k_visen, k_ccen, k_e1,
	 k_neue, k_q,
	 k_ebeam,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      ShowersOnly( void );                      // anal1 
      virtual ~ShowersOnly();                   // anal5 

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
      ShowersOnly( const ShowersOnly& );

      // ------------ assignment operator(s) ---------------------
      const ShowersOnly& operator=( const ShowersOnly& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ShowersOnly::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<double> m_eBeam;
      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* SHOWERSONLY_SHOWERSONLY_H */
