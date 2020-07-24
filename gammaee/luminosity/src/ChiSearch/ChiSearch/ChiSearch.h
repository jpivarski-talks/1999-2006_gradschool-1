// -*- C++ -*-
#if !defined(CHISEARCH_CHISEARCH_H)
#define CHISEARCH_CHISEARCH_H
//
// Package:     <ChiSearch>
// Module:      ChiSearch
//
/**\class ChiSearch ChiSearch.h ChiSearch/ChiSearch.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Sat Apr 23 09:40:27 EDT 2005
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

class ChiSearch : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_x1,
	 k_y1,
	 k_z1,
	 k_x2,
	 k_y2,
	 k_z2,
	 k_x3,
	 k_y3,
	 k_z3,
	 k_x4,
	 k_y4,
	 k_z4,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      ChiSearch( void );                      // anal1 
      virtual ~ChiSearch();                   // anal5 

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
      ChiSearch( const ChiSearch& );

      // ------------ assignment operator(s) ---------------------
      const ChiSearch& operator=( const ChiSearch& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ChiSearch::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CHISEARCH_CHISEARCH_H */
