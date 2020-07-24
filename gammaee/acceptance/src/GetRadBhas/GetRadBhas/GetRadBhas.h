// -*- C++ -*-
#if !defined(GETRADBHAS_GETRADBHAS_H)
#define GETRADBHAS_GETRADBHAS_H
//
// Package:     <GetRadBhas>
// Module:      GetRadBhas
//
/**\class GetRadBhas GetRadBhas.h GetRadBhas/GetRadBhas.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Sep 21 15:12:33 EDT 2004
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

class GetRadBhas : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_e1, k_e2, k_e3,
	 k_p1x, k_p1y, k_p1z, k_p2x, k_p2y, k_p2z, k_p3x, k_p3y, k_p3z,
	 k_m1, k_m2, k_m3, k_tracks, k_ccen, k_ebeam, k_radtau,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      GetRadBhas( void );                      // anal1 
      virtual ~GetRadBhas();                   // anal5 

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
      GetRadBhas( const GetRadBhas& );

      // ------------ assignment operator(s) ---------------------
      const GetRadBhas& operator=( const GetRadBhas& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (GetRadBhas::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* GETRADBHAS_GETRADBHAS_H */
