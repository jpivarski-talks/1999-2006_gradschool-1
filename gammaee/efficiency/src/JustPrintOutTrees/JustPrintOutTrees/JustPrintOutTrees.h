// -*- C++ -*-
#if !defined(JUSTPRINTOUTTREES_JUSTPRINTOUTTREES_H)
#define JUSTPRINTOUTTREES_JUSTPRINTOUTTREES_H
//
// Package:     <JustPrintOutTrees>
// Module:      JustPrintOutTrees
//
/**\class JustPrintOutTrees JustPrintOutTrees.h JustPrintOutTrees/JustPrintOutTrees.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri May  9 18:25:53 EDT 2003
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

class JustPrintOutTrees : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      JustPrintOutTrees( void );                      // anal1 
      virtual ~JustPrintOutTrees();                   // anal5 

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
      JustPrintOutTrees( const JustPrintOutTrees& );

      // ------------ assignment operator(s) ---------------------
      const JustPrintOutTrees& operator=( const JustPrintOutTrees& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (JustPrintOutTrees::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* JUSTPRINTOUTTREES_JUSTPRINTOUTTREES_H */
