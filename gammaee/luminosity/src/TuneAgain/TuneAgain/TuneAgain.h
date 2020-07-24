// -*- C++ -*-
#if !defined(TUNEAGAIN_TUNEAGAIN_H)
#define TUNEAGAIN_TUNEAGAIN_H
//
// Package:     <TuneAgain>
// Module:      TuneAgain
//
/**\class TuneAgain TuneAgain.h TuneAgain/TuneAgain.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Apr  6 17:59:16 EDT 2005
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

class TuneAgain : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      TuneAgain( void );                      // anal1 
      virtual ~TuneAgain();                   // anal5 

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
      TuneAgain( const TuneAgain& );

      // ------------ assignment operator(s) ---------------------
      const TuneAgain& operator=( const TuneAgain& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TuneAgain::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      bool excludeBlockA(double westphi, double cotTheta);
      bool excludeBlockBC(double westphi, double cotTheta);
      bool safeb2b(double cotTheta1, double cotTheta2);
      bool ggacop(double phi1, double phi2);
      bool bbacop(double phi1, double phi2);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TUNEAGAIN_TUNEAGAIN_H */
