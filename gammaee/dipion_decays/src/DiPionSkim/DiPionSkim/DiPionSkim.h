// -*- C++ -*-
#if !defined(DIPIONSKIM_DIPIONSKIM_H)
#define DIPIONSKIM_DIPIONSKIM_H
//
// Package:     <DiPionSkim>
// Module:      DiPionSkim
//
/**\class DiPionSkim DiPionSkim.h DiPionSkim/DiPionSkim.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim McCann
// Created:     Wed May 29 15:19:48 EDT 2002
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

class DiPionSkim : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      DiPionSkim( void );                      // anal1 
      virtual ~DiPionSkim();                   // anal5 

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
      DiPionSkim( const DiPionSkim& );

      // ------------ assignment operator(s) ---------------------
      const DiPionSkim& operator=( const DiPionSkim& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (DiPionSkim::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter< double > m_initialmass;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* DIPIONSKIM_DIPIONSKIM_H */
