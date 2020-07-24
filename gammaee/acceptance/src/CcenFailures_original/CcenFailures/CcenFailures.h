// -*- C++ -*-
#if !defined(CCENFAILURES_CCENFAILURES_H)
#define CCENFAILURES_CCENFAILURES_H
//
// Package:     <CcenFailures>
// Module:      CcenFailures
//
/**\class CcenFailures CcenFailures.h CcenFailures/CcenFailures.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Jul 14 13:51:29 EDT 2004
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
#include "MCInfo/MCDecayTree/MCParticle.h"

// forward declarations

class CcenFailures : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      CcenFailures( void );                      // anal1 
      virtual ~CcenFailures();                   // anal5 

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
      CcenFailures( const CcenFailures& );

      // ------------ assignment operator(s) ---------------------
      const CcenFailures& operator=( const CcenFailures& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (CcenFailures::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      Parameter<unsigned int> m_run;
      int m_count;
      int m_last;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CCENFAILURES_CCENFAILURES_H */
