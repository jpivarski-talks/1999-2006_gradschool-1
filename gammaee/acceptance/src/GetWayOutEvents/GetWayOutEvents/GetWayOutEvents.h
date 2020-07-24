// -*- C++ -*-
#if !defined(GETWAYOUTEVENTS_GETWAYOUTEVENTS_H)
#define GETWAYOUTEVENTS_GETWAYOUTEVENTS_H
//
// Package:     <GetWayOutEvents>
// Module:      GetWayOutEvents
//
/**\class GetWayOutEvents GetWayOutEvents.h GetWayOutEvents/GetWayOutEvents.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu Jun  3 15:30:14 EDT 2004
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
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class GetWayOutEvents : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      GetWayOutEvents( void );                      // anal1 
      virtual ~GetWayOutEvents();                   // anal5 

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
      GetWayOutEvents( const GetWayOutEvents& );

      // ------------ assignment operator(s) ---------------------
      const GetWayOutEvents& operator=( const GetWayOutEvents& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (GetWayOutEvents::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      DABoolean calc_intersection(double& x, double& y, double& z, double& sig2z, double& zsep,
				  KTHelix& a, KTHelix& b);
      DABoolean arclength_test(double x, double y, KTHelix& a, KTHelix& b);

      // ------------ data members -------------------------------
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* GETWAYOUTEVENTS_GETWAYOUTEVENTS_H */
