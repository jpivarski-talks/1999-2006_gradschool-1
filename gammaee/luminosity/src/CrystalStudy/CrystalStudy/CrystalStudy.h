// -*- C++ -*-
#if !defined(CRYSTALSTUDY_CRYSTALSTUDY_H)
#define CRYSTALSTUDY_CRYSTALSTUDY_H
//
// Package:     <CrystalStudy>
// Module:      CrystalStudy
//
/**\class CrystalStudy CrystalStudy.h CrystalStudy/CrystalStudy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Jim Pivarski
// Created:     Thu Apr 14 11:41:12 EDT 2005
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

class CrystalStudy : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      enum {
	 k_hot1,
	 k_en1,
	 k_ener1,
	 k_th1,
	 k_ther1,
	 k_phi1,
	 k_phier1,
	 k_d1,
	 k_e9251,
	 k_mass1,
	 k_wid1,
	 k_zwid1,
	 k_neff1,
	 k_nhit1,
	 k_nhitu1,
	 k_ring1,
	 k_cell1,
	 k_naive1,
	 k_thb1,
	 k_phb1,
	 k_thp1,
	 k_php1,
	 k_pock1,
	 k_hot2,
	 k_en2,
	 k_ener2,
	 k_th2,
	 k_ther2,
	 k_phi2,
	 k_phier2,
	 k_d2,
	 k_e9252,
	 k_mass2,
	 k_wid2,
	 k_zwid2,
	 k_neff2,
	 k_nhit2,
	 k_nhitu2,
	 k_ring2,
	 k_cell2,
	 k_naive2,
	 k_thb2,
	 k_phb2,
	 k_thp2,
	 k_php2,
	 k_pock2,

	 kNumEntries
      };

      // ------------ Constructors and destructor ----------------
      CrystalStudy( void );                      // anal1 
      virtual ~CrystalStudy();                   // anal5 

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
      CrystalStudy( const CrystalStudy& );

      // ------------ assignment operator(s) ---------------------
      const CrystalStudy& operator=( const CrystalStudy& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (CrystalStudy::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_ntuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CRYSTALSTUDY_CRYSTALSTUDY_H */
