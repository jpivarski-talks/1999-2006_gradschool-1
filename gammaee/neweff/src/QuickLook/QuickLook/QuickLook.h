// -*- C++ -*-
#if !defined(QUICKLOOK_QUICKLOOK_H)
#define QUICKLOOK_QUICKLOOK_H
//
// Package:     <QuickLook>
// Module:      QuickLook
//
/**\class QuickLook QuickLook.h QuickLook/QuickLook.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Feb 11 16:26:03 EST 2004
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

class QuickLook : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      QuickLook( void );                      // anal1 
      virtual ~QuickLook();                   // anal5 

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
      QuickLook( const QuickLook& );

      // ------------ assignment operator(s) ---------------------
      const QuickLook& operator=( const QuickLook& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (QuickLook::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* QUICKLOOK_QUICKLOOK_H */
