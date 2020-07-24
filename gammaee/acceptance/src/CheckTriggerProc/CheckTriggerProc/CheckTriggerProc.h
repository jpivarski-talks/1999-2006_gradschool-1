// -*- C++ -*-
#if !defined(CHECKTRIGGERPROC_CHECKTRIGGERPROC_H)
#define CHECKTRIGGERPROC_CHECKTRIGGERPROC_H
//
// Package:     <CheckTriggerProc>
// Module:      CheckTriggerProc
//
/**\class CheckTriggerProc CheckTriggerProc.h CheckTriggerProc/CheckTriggerProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Apr  5 13:04:19 EDT 2004
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

class CheckTriggerProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_axial,
	 k_stereo,
	 k_cblo,
	 k_cbmd,
	 k_hadron,
	 k_radtau,
	 k_eltrack,
	 k_twotrack,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      CheckTriggerProc( void );                      // anal1 
      virtual ~CheckTriggerProc();                   // anal5 

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
      CheckTriggerProc( const CheckTriggerProc& );

      // ------------ assignment operator(s) ---------------------
      const CheckTriggerProc& operator=( const CheckTriggerProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (CheckTriggerProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      int m_total;
      int m_invalidTriggerInfo;
      int m_invalidTriggerL1Data;
      int m_badbucket;

      int m_hadrons;
      int m_wronghadrons;
      int m_nonhadrons;
      int m_wrongnonhadrons;

      int m_radtaus;
      int m_wrongradtaus;
      int m_nonradtaus;
      int m_wrongnonradtaus;

      int m_eltracks;
      int m_wrongeltracks;
      int m_noneltracks;
      int m_wrongnoneltracks;

      int m_twotracks;
      int m_wrongtwotracks;
      int m_nontwotracks;
      int m_wrongnontwotracks;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CHECKTRIGGERPROC_CHECKTRIGGERPROC_H */
