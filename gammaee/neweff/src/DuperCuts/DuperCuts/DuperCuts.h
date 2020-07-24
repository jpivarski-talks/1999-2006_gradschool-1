// -*- C++ -*-
#if !defined(DUPERCUTS_DUPERCUTS_H)
#define DUPERCUTS_DUPERCUTS_H
//
// Package:     <DuperCuts>
// Module:      DuperCuts
//
/**\class DuperCuts DuperCuts.h DuperCuts/DuperCuts.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Feb 11 10:30:06 EST 2004
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
#include "CommandPattern/Parameter.h"
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class DuperCuts : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kShower1, kShower2, kMomentum1, kMomentum2, kQ2, kCosTheta,
	 kRawNumTracks, kEPNumTracks, kVisEn, kCCEn, kBGNumTracks, kBGRPhi, kBGZ, kBGD0, kBGZ0,
	 kNeuE, kQ, kNSh10, kNSh50, kNSh100, kNSh500,
	 kTrig1, kLevel4,

	 kNumEntries};

      // ------------ Constructors and destructor ----------------
      DuperCuts( void );                      // anal1 
      virtual ~DuperCuts();                   // anal5 

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
      DuperCuts( const DuperCuts& );

      // ------------ assignment operator(s) ---------------------
      const DuperCuts& operator=( const DuperCuts& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (DuperCuts::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<DABoolean> m_mcll;
      Parameter<DABoolean> m_mcother;

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* DUPERCUTS_DUPERCUTS_H */
