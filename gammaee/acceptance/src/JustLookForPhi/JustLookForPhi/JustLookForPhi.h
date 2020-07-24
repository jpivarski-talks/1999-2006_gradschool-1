// -*- C++ -*-
#if !defined(JUSTLOOKFORPHI_JUSTLOOKFORPHI_H)
#define JUSTLOOKFORPHI_JUSTLOOKFORPHI_H
//
// Package:     <JustLookForPhi>
// Module:      JustLookForPhi
//
/**\class JustLookForPhi JustLookForPhi.h JustLookForPhi/JustLookForPhi.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Oct 26 12:54:04 EDT 2004
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

class JustLookForPhi : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      JustLookForPhi( void );                      // anal1 
      virtual ~JustLookForPhi();                   // anal5 

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
      JustLookForPhi( const JustLookForPhi& );

      // ------------ assignment operator(s) ---------------------
      const JustLookForPhi& operator=( const JustLookForPhi& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (JustLookForPhi::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HIHist1D* m_phi1;
      HIHist1D* m_phip;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* JUSTLOOKFORPHI_JUSTLOOKFORPHI_H */
