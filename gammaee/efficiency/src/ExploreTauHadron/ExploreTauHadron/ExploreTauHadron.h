// -*- C++ -*-
#if !defined(EXPLORETAUHADRON_EXPLORETAUHADRON_H)
#define EXPLORETAUHADRON_EXPLORETAUHADRON_H
//
// Package:     <ExploreTauHadron>
// Module:      ExploreTauHadron
//
/**\class ExploreTauHadron ExploreTauHadron.h ExploreTauHadron/ExploreTauHadron.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu Jul 10 16:23:20 EDT 2003
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

class ExploreTauHadron : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      ExploreTauHadron( void );                      // anal1 
      virtual ~ExploreTauHadron();                   // anal5 

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
      ExploreTauHadron( const ExploreTauHadron& );

      // ------------ assignment operator(s) ---------------------
      const ExploreTauHadron& operator=( const ExploreTauHadron& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ExploreTauHadron::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* EXPLORETAUHADRON_EXPLORETAUHADRON_H */
