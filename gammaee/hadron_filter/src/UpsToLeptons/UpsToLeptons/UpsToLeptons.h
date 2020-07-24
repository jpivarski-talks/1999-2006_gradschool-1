// -*- C++ -*-
#if !defined(UPSTOLEPTONS_UPSTOLEPTONS_H)
#define UPSTOLEPTONS_UPSTOLEPTONS_H
//
// Package:     <UpsToLeptons>
// Module:      UpsToLeptons
//
/**\class UpsToLeptons UpsToLeptons.h UpsToLeptons/UpsToLeptons.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Sep 11 13:15:33 EDT 2002
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

class UpsToLeptons : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      UpsToLeptons( void );                      // anal1 
      virtual ~UpsToLeptons();                   // anal5 

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
      UpsToLeptons( const UpsToLeptons& );

      // ------------ assignment operator(s) ---------------------
      const UpsToLeptons& operator=( const UpsToLeptons& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (UpsToLeptons::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter< string > m_parent;
      Parameter< DABoolean > m_passElectrons;
      Parameter< DABoolean > m_passMuons;
      Parameter< DABoolean > m_passTaus;

      int m_total;
      int m_electrons;
      int m_muons;
      int m_taus;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* UPSTOLEPTONS_UPSTOLEPTONS_H */
