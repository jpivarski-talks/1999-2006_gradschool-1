// -*- C++ -*-
#if !defined(TWOPHOTONFILTEROUTPROC_TWOPHOTONFILTEROUTPROC_H)
#define TWOPHOTONFILTEROUTPROC_TWOPHOTONFILTEROUTPROC_H
//
// Package:     <TwoPhotonFilterOutProc>
// Module:      TwoPhotonFilterOutProc
//
/**\class TwoPhotonFilterOutProc TwoPhotonFilterOutProc.h TwoPhotonFilterOutProc/TwoPhotonFilterOutProc.h
 
 Description: Cuts OUT two-photon (non-annihilation hadronic) background, leaving over 99% of the collision events.

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Nov  5 12:06:52 EST 2002
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
#include "FrameAccess/FAItem.h"

// forward declarations

class TwoPhotonFilterOutProc : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------
      
      enum {
	 kPz,
	 kAbsPz,
	 kEnergy,
	 kAbsPPerp,
	 kWestEnergy,
	 kEastEnergy,
	 kBigEnergy,
	 kLittleEnergy,

	 kNPos,
	 kNNeg,
	 kNNeut,

	 kEntries
      };

      // ------------ Constructors and destructor ----------------
      TwoPhotonFilterOutProc( void );                      // anal1 
      virtual ~TwoPhotonFilterOutProc();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      virtual ActionBase::ActionResult beginRun( Frame& iFrame);
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
      TwoPhotonFilterOutProc( const TwoPhotonFilterOutProc& );

      // ------------ assignment operator(s) ---------------------
      const TwoPhotonFilterOutProc& operator=( const TwoPhotonFilterOutProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TwoPhotonFilterOutProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_passed;
      int m_total;

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TWOPHOTONFILTEROUTPROC_TWOPHOTONFILTEROUTPROC_H */
