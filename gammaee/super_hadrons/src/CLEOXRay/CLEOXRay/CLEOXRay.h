// -*- C++ -*-
#if !defined(CLEOXRAY_CLEOXRAY_H)
#define CLEOXRAY_CLEOXRAY_H
//
// Package:     <CLEOXRay>
// Module:      CLEOXRay
//
/**\class CLEOXRay CLEOXRay.h CLEOXRay/CLEOXRay.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri Nov 22 14:55:11 EST 2002
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
#include "HbookHistogram/HbookNtuple.h"
#include "CommandPattern/Parameter.h"
#include "KinematicTrajectory/KTHelix.h"

// forward declarations

class CLEOXRay : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------
      enum {
	 kX, kY, kZ, kZSep, kSig2Z, kCharge,
	 kEntries
      };

      // ------------ Constructors and destructor ----------------
      CLEOXRay( void );                      // anal1 
      virtual ~CLEOXRay();                   // anal5 

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

      DABoolean calc_intersection(
	 double& x, double& y, double& z, double& sig2z, double& zsep,
	 KTHelix& a, KTHelix& b );
      DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b );

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      CLEOXRay( const CLEOXRay& );

      // ------------ assignment operator(s) ---------------------
      const CLEOXRay& operator=( const CLEOXRay& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (CLEOXRay::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      HIHist1D* m_zsep;
      HIHist1D* m_sigz;
      HIHist1D* m_zsep_sig2z;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CLEOXRAY_CLEOXRAY_H */
