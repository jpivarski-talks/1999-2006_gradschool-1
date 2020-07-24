// -*- C++ -*-
#if !defined(LUMI_LUMI_H)
#define LUMI_LUMI_H
//
// Package:     <Lumi>
// Module:      Lumi
//
/**\class Lumi Lumi.h Lumi/Lumi.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Tue Nov  9 15:11:24 EST 2004
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

class Lumi : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_l1tt,
	 k_l1rt,
	 k_l1el,
	 k_l1bb,
	 k_l1eb,
// 	 k_l3acc,
// 	 k_l3class,
// 	 k_l4dec,
	 k_rawtk,
	 k_ntk,
	 k_ebeam,
	 k_e1,
	 k_e2,
	 k_p1,
	 k_p2,
	 k_ccen,
	 k_neue,
	 k_chen,
	 k_pos1,
	 k_pos2,
	 k_s1costh,
	 k_s2costh,
	 k_s1phi,
	 k_s2phi,
	 k_t1costh,
	 k_t2costh,
	 k_t1phi,
	 k_t2phi,
// 	 k_expect,
// 	 k_allhit,
// 	 k_chi2,
// 	 k_dof,
	 k_d0close,
	 k_z0close,
	 k_pmiss,
// 	 k_axlay,
// 	 k_stlay,
//  	 k_esig1,
//  	 k_esig2,
//  	 k_musig1,
//  	 k_musig2,
//  	 k_ell1,
//  	 k_ell2,
//  	 k_mull1,
//  	 k_mull2,
	 k_s1e925,
	 k_s2e925,
	 k_mccosth,
	 k_s1wide,
	 k_s2wide,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      Lumi( void );                      // anal1 
      virtual ~Lumi();                   // anal5 

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
      Lumi( const Lumi& );

      // ------------ assignment operator(s) ---------------------
      const Lumi& operator=( const Lumi& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Lumi::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* LUMI_LUMI_H */
