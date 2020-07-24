// -*- C++ -*-
#if !defined(RECUTS3_RECUTS3_H)
#define RECUTS3_RECUTS3_H
//
// Package:     <ReCuts3>
// Module:      ReCuts3
//
/**\class ReCuts3 ReCuts3.h ReCuts3/ReCuts3.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri Aug  6 13:21:06 EDT 2004
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

class ReCuts3 : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      ReCuts3( void );                      // anal1 
      virtual ~ReCuts3();                   // anal5 

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
      ReCuts3( const ReCuts3& );

      // ------------ assignment operator(s) ---------------------
      const ReCuts3& operator=( const ReCuts3& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ReCuts3::*iMethod)( Frame& ),
	      const Stream::Type& iStream );
      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* RECUTS3_RECUTS3_H */
