// -*- C++ -*-
#if !defined(TESTFACTOR_TESTFACTOR_H)
#define TESTFACTOR_TESTFACTOR_H
//
// Package:     <TestFactor>
// Module:      TestFactor
//
/**\class TestFactor TestFactor.h TestFactor/TestFactor.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Jan 29 14:23:43 EST 2003
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

class TestFactor : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      TestFactor( void );                      // anal1 
      virtual ~TestFactor();                   // anal5 

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
      TestFactor( const TestFactor& );

      // ------------ assignment operator(s) ---------------------
      const TestFactor& operator=( const TestFactor& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TestFactor::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int 	m_pos;
      int 	m_neg;
      HIHist1D* m_ne_pos;
      HIHist1D* m_ne_neg;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TESTFACTOR_TESTFACTOR_H */
