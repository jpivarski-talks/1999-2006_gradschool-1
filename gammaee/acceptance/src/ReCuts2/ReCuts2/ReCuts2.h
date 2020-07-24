// -*- C++ -*-
#if !defined(RECUTS2_RECUTS2_H)
#define RECUTS2_RECUTS2_H
//
// Package:     <ReCuts2>
// Module:      ReCuts2
//
/**\class ReCuts2 ReCuts2.h ReCuts2/ReCuts2.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Jul  6 14:18:22 EDT 2004
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

class ReCuts2 : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      ReCuts2( void );                      // anal1 
      virtual ~ReCuts2();                   // anal5 

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
      ReCuts2( const ReCuts2& );

      // ------------ assignment operator(s) ---------------------
      const ReCuts2& operator=( const ReCuts2& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ReCuts2::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      void summarize();
      DABoolean calc_intersection(double& x, double& y, double& z,
				  double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      int m_run;
      int m_pass;
      int m_fail;
      int m_passtrack;
      double m_eBeam;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* RECUTS2_RECUTS2_H */
