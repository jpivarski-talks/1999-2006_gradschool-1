// -*- C++ -*-
#if !defined(ISKNOWNOKAY_ISKNOWNOKAY_H)
#define ISKNOWNOKAY_ISKNOWNOKAY_H
//
// Package:     <IsKnownOkay>
// Module:      IsKnownOkay
//
/**\class IsKnownOkay IsKnownOkay.h IsKnownOkay/IsKnownOkay.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Apr 20 10:49:23 EDT 2005
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

class IsKnownOkay : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      IsKnownOkay( void );                      // anal1 
      virtual ~IsKnownOkay();                   // anal5 

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
      IsKnownOkay( const IsKnownOkay& );

      // ------------ assignment operator(s) ---------------------
      const IsKnownOkay& operator=( const IsKnownOkay& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (IsKnownOkay::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* ISKNOWNOKAY_ISKNOWNOKAY_H */
