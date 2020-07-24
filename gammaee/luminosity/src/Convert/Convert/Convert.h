// -*- C++ -*-
#if !defined(CONVERT_CONVERT_H)
#define CONVERT_CONVERT_H
//
// Package:     <Convert>
// Module:      Convert
//
/**\class Convert Convert.h Convert/Convert.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Fri Apr  8 15:23:52 EDT 2005
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

// forward declarations

class Convert : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_tracks,
	 k_oldtk,
	 k_trig,
	 k_eltrack,
	 k_ebeam,
	 k_e1,
	 k_e1cos,
	 k_e1cot,
	 k_e1phi,
	 k_e2,
	 k_e2cos,
	 k_e2cot,
	 k_e2phi,
	 k_acop,
	 k_cnum,
	 k_cen,
	 k_cbig,
	 k_cang,
	 k_ccos,
	 k_cacop,
	 k_epho,
	 k_mcvx,
	 k_mcvy,
	 k_mcvz,
	 k_vchi2,
	 k_vx,
	 k_vy,
	 k_vz,
	 k_t1px,
	 k_t1py,
	 k_t1pz,
	 k_t1d0,
	 k_t1z0,
	 k_t2px,
	 k_t2py,
	 k_t2pz,
	 k_t2d0,
	 k_t2z0,
	 k_t3px,
	 k_t3py,
	 k_t3pz,
	 k_t3d0,
	 k_t3z0,
	 k_svrad,
	 k_svphi,
	 k_svd,
	 k_visen,
	 k_known,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      Convert( void );                      // anal1 
      virtual ~Convert();                   // anal5 

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
      Convert( const Convert& );

      // ------------ assignment operator(s) ---------------------
      const Convert& operator=( const Convert& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Convert::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CONVERT_CONVERT_H */
