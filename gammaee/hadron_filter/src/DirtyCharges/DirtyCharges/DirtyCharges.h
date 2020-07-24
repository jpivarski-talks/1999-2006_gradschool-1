// -*- C++ -*-
#if !defined(DIRTYCHARGES_DIRTYCHARGES_H)
#define DIRTYCHARGES_DIRTYCHARGES_H
//
// Package:     <DirtyCharges>
// Module:      DirtyCharges
//
/**\class DirtyCharges DirtyCharges.h DirtyCharges/DirtyCharges.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Wed Nov 13 10:30:28 EST 2002
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
#include "CommandPattern/Parameter.h"
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class DirtyCharges : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      DirtyCharges( void );                      // anal1 
      virtual ~DirtyCharges();                   // anal5 

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
      DirtyCharges( const DirtyCharges& );

      // ------------ assignment operator(s) ---------------------
      const DirtyCharges& operator=( const DirtyCharges& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (DirtyCharges::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      DABoolean calc_intersection(
	 double& x, double& y, double& z, double& sig2z, double& zsep,
	 KTHelix& a, KTHelix& b );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      double m_beam_x;
      double m_beam_y;
      double m_beam_z;

      HIHist1D* m_spreadPerp;
      HIHist1D* m_spreadZSep;

      HIHist1D* m_charge;
      HIHistProf* m_charge_perp;
      HIHist1D* m_charge_perp_2mm;
      HIHist1D* m_charge_perp_4mm;
      HIHist1D* m_charge_perp_1cm;
      HIHist1D* m_charge_perp_5cm;
      HIHistProf* m_charge_z;
      HIHist1D* m_charge_z_5mm;
      HIHist1D* m_charge_z_1cm;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* DIRTYCHARGES_DIRTYCHARGES_H */
