// -*- C++ -*-
#if !defined(DUPERCUTS2_DUPERCUTS2_H)
#define DUPERCUTS2_DUPERCUTS2_H
//
// Package:     <DuperCuts2>
// Module:      DuperCuts2
//
/**\class DuperCuts2 DuperCuts2.h DuperCuts2/DuperCuts2.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri Feb 13 15:57:08 EST 2004
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

class DuperCuts2 : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kShower1, kShower2, kMomentum1, kMomentum2, kQ2, kCosTheta,
	 kRawNumTracks, kEPNumTracks, kVisEn, kCCEn, kBGNumTracks, kBGRPhi, kBGZ, kBGD0, kBGZ0,
	 kNeuE, kQ, kNSh10, kNSh50, kNSh100, kNSh500,
	 kTrig1, kLevel4,
	 kPh1Px, kPh1Py, kPh1Pz, kPh2Px, kPh2Py, kPh2Pz,
	 kTr1Px, kTr1Py, kTr1Pz, kTr2Px, kTr2Py, kTr2Pz,
	 kMC,

	 kNumEntries};

      // ------------ Constructors and destructor ----------------
      DuperCuts2( void );                      // anal1 
      virtual ~DuperCuts2();                   // anal5 

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
      DuperCuts2( const DuperCuts2& );

      // ------------ assignment operator(s) ---------------------
      const DuperCuts2& operator=( const DuperCuts2& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (DuperCuts2::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<DABoolean> m_mcll;
      Parameter<DABoolean> m_mcchi;
      Parameter<DABoolean> m_mcother;

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* DUPERCUTS2_DUPERCUTS2_H */
