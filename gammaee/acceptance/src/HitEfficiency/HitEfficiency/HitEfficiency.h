// -*- C++ -*-
#if !defined(HITEFFICIENCY_HITEFFICIENCY_H)
#define HITEFFICIENCY_HITEFFICIENCY_H
//
// Package:     <HitEfficiency>
// Module:      HitEfficiency
//
/**\class HitEfficiency HitEfficiency.h HitEfficiency/HitEfficiency.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Mon Sep 20 12:49:12 EDT 2004
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

class HitEfficiency : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      HitEfficiency( void );                      // anal1 
      virtual ~HitEfficiency();                   // anal5 

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
      HitEfficiency( const HitEfficiency& );

      // ------------ assignment operator(s) ---------------------
      const HitEfficiency& operator=( const HitEfficiency& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (HitEfficiency::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

//       HIHistProf* m_lit;
//       HIHistProf* m_blobs;
//       HIHistProf* m_axial;

      int m_axial[31][31];
      int m_stereo[31][31];

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* HITEFFICIENCY_HITEFFICIENCY_H */
