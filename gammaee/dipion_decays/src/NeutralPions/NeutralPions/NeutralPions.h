// -*- C++ -*-
#if !defined(NEUTRALPIONS_NEUTRALPIONS_H)
#define NEUTRALPIONS_NEUTRALPIONS_H
//
// Package:     <NeutralPions>
// Module:      NeutralPions
//
/**\class NeutralPions NeutralPions.h NeutralPions/NeutralPions.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Apr 22 16:44:22 EDT 2003
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

class NeutralPions : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kPi1PX,
	 kPi1PY,
	 kPi1PZ,
	 kPi1Sigmas,
	 kPi1Chi2,
	 kPi1PullMass,
	 kPi2PX,
	 kPi2PY,
	 kPi2PZ,
	 kPi2Sigmas,
	 kPi2Chi2,
	 kPi2PullMass,
	 kEnergy,
	 kMomentumX,
	 kMomentumY,
	 kMomentumZ,
	 kMass,
	 kMass2,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      NeutralPions( void );                      // anal1 
      virtual ~NeutralPions();                   // anal5 

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
      NeutralPions( const NeutralPions& );

      // ------------ assignment operator(s) ---------------------
      const NeutralPions& operator=( const NeutralPions& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (NeutralPions::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_u1s;
      HINtuple* m_u2s;
      HIHist1D* m_piSigmas;
      HIHist1D* m_piChisq;
      HIHist1D* m_piPullMass;
      HIHist1D* m_mass;
      HIHist1D* m_mass_narrow;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* NEUTRALPIONS_NEUTRALPIONS_H */
