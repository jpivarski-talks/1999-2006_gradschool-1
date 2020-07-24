// -*- C++ -*-
#if !defined(SUBCOLLECTIONCUTS_SUBCOLLECTIONCUTS_H)
#define SUBCOLLECTIONCUTS_SUBCOLLECTIONCUTS_H
//
// Package:     <SubcollectionCuts>
// Module:      SubcollectionCuts
//
/**\class SubcollectionCuts SubcollectionCuts.h SubcollectionCuts/SubcollectionCuts.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Mar 26 14:35:18 EST 2003
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
#include "HistogramInterface/HINtuple.h"

// forward declarations

class SubcollectionCuts : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      SubcollectionCuts( void );                      // anal1 
      virtual ~SubcollectionCuts();                   // anal5 

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
      SubcollectionCuts( const SubcollectionCuts& );

      // ------------ assignment operator(s) ---------------------
      const SubcollectionCuts& operator=( const SubcollectionCuts& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (SubcollectionCuts::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* SUBCOLLECTIONCUTS_SUBCOLLECTIONCUTS_H */
