// -*- C++ -*-
#if !defined(RELATIVITY_RELATIVITY_H)
#define RELATIVITY_RELATIVITY_H
//
// Package:     <Relativity>
// Module:      Relativity
//
/**\class Relativity Relativity.h Relativity/Relativity.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Mar 22 14:51:54 EST 2005
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

class Relativity : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      Relativity( void );                      // anal1 
      virtual ~Relativity();                   // anal5 

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
      Relativity( const Relativity& );

      // ------------ assignment operator(s) ---------------------
      const Relativity& operator=( const Relativity& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Relativity::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      void print();

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_run;
      int m_event;
      int m_gamgams;
      int m_bhabhas;
      int m_phi1[64];
      int m_phi2[64];
      int m_phi3[64];
      int m_phi4[64];
      int m_phi5[64];
      int m_numer[100][64];
      int m_denom[100][64];
      int m_numer_region;
      int m_denom_region;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* RELATIVITY_RELATIVITY_H */
