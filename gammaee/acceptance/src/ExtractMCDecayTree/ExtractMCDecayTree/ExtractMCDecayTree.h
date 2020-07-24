// -*- C++ -*-
#if !defined(EXTRACTMCDECAYTREE_EXTRACTMCDECAYTREE_H)
#define EXTRACTMCDECAYTREE_EXTRACTMCDECAYTREE_H
//
// Package:     <ExtractMCDecayTree>
// Module:      ExtractMCDecayTree
//
/**\class ExtractMCDecayTree ExtractMCDecayTree.h ExtractMCDecayTree/ExtractMCDecayTree.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu May  6 14:32:16 EDT 2004
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

class ExtractMCDecayTree : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      ExtractMCDecayTree( void );                      // anal1 
      virtual ~ExtractMCDecayTree();                   // anal5 

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
      ExtractMCDecayTree( const ExtractMCDecayTree& );

      // ------------ assignment operator(s) ---------------------
      const ExtractMCDecayTree& operator=( const ExtractMCDecayTree& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ExtractMCDecayTree::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* EXTRACTMCDECAYTREE_EXTRACTMCDECAYTREE_H */
