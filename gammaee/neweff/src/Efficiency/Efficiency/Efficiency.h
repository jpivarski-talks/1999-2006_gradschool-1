// -*- C++ -*-
#if !defined(EFFICIENCY_EFFICIENCY_H)
#define EFFICIENCY_EFFICIENCY_H
//
// Package:     <Efficiency>
// Module:      Efficiency
//
/**\class Efficiency Efficiency.h Efficiency/Efficiency.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu May 29 15:24:55 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "KinematicTrajectory/KTHelix.h"
#include "HistogramInterface/HistogramPackage.h"
#include "HistogramInterface/HINtuple.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class Efficiency : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 kRun,
	 kEvent,
	 kDecay3S,
	 kDecay2P,
	 kDecay2S,
	 kDecay1P,
	 kDecay1S,
	 kLastUpsilonPPerp,
	 kLastUpsilonPPhi,
	 kLastUpsilonPZ,
// 	 kL1AxialTracks,
// 	 kL1LowClusters,
	 kL3Showers,
	 kL3TotalCCEnergy,
	 kL3BiggestShower,
	 kL3zPosCCEnergy,
	 kL3zNegCCEnergy,
	 kL4Tracks,
	 kL5Tracks,
	 kL5VisibleEnergy,
	 kL5CCEnergy,
	 kL5BiggestShower,
	 kL5BeamEnergy,
	 kNeutralEnergy,
	 kCharge,
	 kPperp,
	 kPphi,
	 kPz,
	 kBiggestTrack,
	 kBiggestMatched,
	 kShowersOver10,
	 kShowersOver20,
	 kShowersOver30,
	 kShowersOver50,
	 kShowersOver200,
	 kShowersOver300,
	 kShowersOver500,
	 kShowersOver1000,
	 kL6RPhi,
	 kL6Z,
	 kL1Decision,
	 kL3Decision,
	 kL3AcceptCode,
	 kL3ClassCode,
	 kL4Decision,
	 kL5Decision,
	 kL6Decision,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      Efficiency( void );                      // anal1 
      virtual ~Efficiency();                   // anal5 

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

      Parameter<DABoolean> m_isMC;

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      Efficiency( const Efficiency& );

      // ------------ assignment operator(s) ---------------------
      const Efficiency& operator=( const Efficiency& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Efficiency::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
				   KTHelix& a, KTHelix& b );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* EFFICIENCY_EFFICIENCY_H */
