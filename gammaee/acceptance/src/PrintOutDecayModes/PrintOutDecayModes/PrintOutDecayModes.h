// -*- C++ -*-
#if !defined(PRINTOUTDECAYMODES_PRINTOUTDECAYMODES_H)
#define PRINTOUTDECAYMODES_PRINTOUTDECAYMODES_H
//
// Package:     <PrintOutDecayModes>
// Module:      PrintOutDecayModes
//
/**\class PrintOutDecayModes PrintOutDecayModes.h PrintOutDecayModes/PrintOutDecayModes.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Jun  7 14:49:09 EDT 2004
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
#include "MCInfo/MCDecayTree/MCParticle.h"

// forward declarations

class PrintOutDecayModes : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      PrintOutDecayModes( void );                      // anal1 
      virtual ~PrintOutDecayModes();                   // anal5 

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
      PrintOutDecayModes( const PrintOutDecayModes& );

      // ------------ assignment operator(s) ---------------------
      const PrintOutDecayModes& operator=( const PrintOutDecayModes& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (PrintOutDecayModes::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      void recurse(bool space, const MCParticle& particle);

      // ------------ data members -------------------------------

      bool m_firsttime;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PRINTOUTDECAYMODES_PRINTOUTDECAYMODES_H */
